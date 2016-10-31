#include "include.h"
#include "math.h"
#include "kalman_filter.h"
#include "keyboard16.h"
/**************************卡尔曼滤波——上位机示波器，按键调参数*****************************/
void main(void)
{
#if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
#endif 
    
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 电位器ad
    uart_init(UART0,115200);//串口0  UART0_RX_PIN    PTD6   UART0_TX_PIN    PTD7 
    key16_init();

    kalman1_state rp;//结构体
    kalman1_init(&rp, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 10);//卡尔曼滤波初始化
   
    kalman1_state rp2;//结构体
    kalman1_init(&rp2, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 10);//卡尔曼滤波初始化
    
    uint16 x_16[3];//传给上位机虚拟示波器的数组
    uint16 key_num=16;
    
    while(1)
    {             
      uint16 adc = adc_once(ADC0_SE10, ADC_16bit);//从电位器读取ＡＤ值
      kalman1_filter(&rp, adc); //卡尔曼滤波，值传给(&rp)->x   
      kalman1_filter(&rp2, adc);
      
      key_num=key16_scan();
//      Display(key_num, 0, 6);//按键
      
      switch(key_num)
      {
      case 0:((&rp)->q)-=10;break;//减小q有较明显变化，但不能减至0，否则响应时间急剧增大
      case 1:((&rp)->p)+=10;break;
      case 2:((&rp)->p)-=10;break;
      case 3:((&rp)->r)+=10;break;//增大r些许变化
      case 4:((&rp)->A)+=0.005;break;//A和H不能改
      case 5:((&rp)->A)-=0.005;break;
      case 6:break;
      case 7:((&rp)->H)+=0.005;break;
      case 8:((&rp)->H)-=0.005;break;
      case 9:break;
      case 10:((&rp)->q)+=10;break;
      case 11:break;
      case 12:break;
      case 13:break;
      case 14:break;
      case 15:((&rp)->r)-=10;break;
      case 16:break;
      default:break;       
      }
      
      x_16[0] = (uint16)((&rp)->x);//第一条曲线,卡尔曼滤波后，按键调整后的曲线
      x_16[1] = adc; //第二条曲线，未滤波的曲线
      x_16[2] = (uint16)((&rp2)->x);//第三条曲线,卡尔曼滤波后的曲线
      
      Display(x_16[0], 0, 0);
      Display((uint16)((&rp)->p), 0, 2);
      Display((uint16)((&rp)->q), 0, 4);
      Display((uint16)((&rp)->r), 0, 6);
      
      Display((uint16)((&rp)->A*1000), 64, 2);
      Display((uint16)((&rp)->H*1000), 64, 4);
      
      vcan_sendware((uint8_t *)(x_16),sizeof(x_16));//传给上位机，显示波形   改了 VCAN_PORT   为 UART0 
//      uart_putbuff(UART0,x_16,5);
//      DELAY_MS(2);
    }
}
/**************************按键*****************************/
/*
void main(void)
{
#if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
#endif 

  LCD_Init();
 // uart_init(UART0,115200);
  key16_init();
  unsigned int key_num=16;
  while(1)
  {
    key_num=key16_scan();
    Display(key_num, 0, 6);
  //  uart_putbuff(UART0,x_16,5);   
  }
}
*/
/**************************卡尔曼滤波——上位机示波器版本*****************************/
/*
void main(void)
{
#if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
#endif 
    
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 电位器ad
    uart_init(UART0,115200);//串口0  UART0_RX_PIN    PTD6   UART0_TX_PIN    PTD7      

    kalman1_state rp;//结构体
    kalman1_init(&rp, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 10);//卡尔曼滤波初始化
    
    uint16 x_16[2];//传给上位机虚拟示波器的数组
    
    while(1)
    {       
      uint16 adc = adc_once(ADC0_SE10, ADC_16bit);//从电位器读取ＡＤ值
      kalman1_filter(&rp, adc); //卡尔曼滤波，值传给(&rp)->x
      x_16[0] = (uint16)((&rp)->x);//第一条曲线,卡尔曼滤波后的曲线
      x_16[1] = adc; //第二条曲线，未滤波的曲线
      Display(x_16[0], 0, 0);
      vcan_sendware((uint8_t *)(x_16),sizeof(x_16));//传给上位机，显示波形   改了 VCAN_PORT   为 UART0 
//      uart_putbuff(UART0,x_16,5);
      DELAY_MS(100);
    }
}
*/
/**************************卡尔曼滤波*****************************/
/*
void main(void)
{
    #if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
    #endif 
    
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 电位器ad
    kalman1_state rp;
    kalman1_init(&rp, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 2e2);
      
    while(1)
    {       
      kalman1_filter(&rp, adc_once(ADC0_SE10, ADC_16bit));   
      Display((uint16)((&rp)->x),0,0);
      
      DELAY_MS(100);
    }
}
*/
/************************消抖滤波***************************/
/*
void  main(void)
{  
    //如果是FX芯片则要开启硬件浮点单元，快5倍
    #if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
    #endif  
    
    uint16 sample;//电位器的采样值
    uint16 effect;//有效值
    uint16 count=0;//计数
    const uint16 MaxOfCount=10;//计数上限
 
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 电位器ad
    
    DELAY_MS(1000);
    
    effect=adc_once(ADC0_SE10, ADC_16bit);//电位器effect值
    
    while(1)
    {      
      { //电位器滤波程序 会降低灵敏度
          sample=adc_once(ADC0_SE10, ADC_16bit);
          if((sample >= effect*1.01)&&(sample <= effect*0.99))
            count=0;
          else// if((sample < effect+50)||(sample > effect-50))  
          {  
            count++;
            if(count >= MaxOfCount)
            {
              effect=sample;
              count=0;
            }
          }     
        }  

      Display(sample,0,0);
      Display(effect,64,0);
      DELAY_MS(100);
    }
}
*/