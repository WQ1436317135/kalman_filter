#include "include.h"
#include "math.h"
#include "kalman_filter.h"
#include "keyboard16.h"
/**************************�������˲�������λ��ʾ����������������*****************************/
void main(void)
{
#if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
#endif 
    
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 ��λ��ad
    uart_init(UART0,115200);//����0  UART0_RX_PIN    PTD6   UART0_TX_PIN    PTD7 
    key16_init();

    kalman1_state rp;//�ṹ��
    kalman1_init(&rp, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 10);//�������˲���ʼ��
   
    kalman1_state rp2;//�ṹ��
    kalman1_init(&rp2, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 10);//�������˲���ʼ��
    
    uint16 x_16[3];//������λ������ʾ����������
    uint16 key_num=16;
    
    while(1)
    {             
      uint16 adc = adc_once(ADC0_SE10, ADC_16bit);//�ӵ�λ����ȡ����ֵ
      kalman1_filter(&rp, adc); //�������˲���ֵ����(&rp)->x   
      kalman1_filter(&rp2, adc);
      
      key_num=key16_scan();
//      Display(key_num, 0, 6);//����
      
      switch(key_num)
      {
      case 0:((&rp)->q)-=10;break;//��Сq�н����Ա仯�������ܼ���0��������Ӧʱ�伱������
      case 1:((&rp)->p)+=10;break;
      case 2:((&rp)->p)-=10;break;
      case 3:((&rp)->r)+=10;break;//����rЩ��仯
      case 4:((&rp)->A)+=0.005;break;//A��H���ܸ�
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
      
      x_16[0] = (uint16)((&rp)->x);//��һ������,�������˲��󣬰��������������
      x_16[1] = adc; //�ڶ������ߣ�δ�˲�������
      x_16[2] = (uint16)((&rp2)->x);//����������,�������˲��������
      
      Display(x_16[0], 0, 0);
      Display((uint16)((&rp)->p), 0, 2);
      Display((uint16)((&rp)->q), 0, 4);
      Display((uint16)((&rp)->r), 0, 6);
      
      Display((uint16)((&rp)->A*1000), 64, 2);
      Display((uint16)((&rp)->H*1000), 64, 4);
      
      vcan_sendware((uint8_t *)(x_16),sizeof(x_16));//������λ������ʾ����   ���� VCAN_PORT   Ϊ UART0 
//      uart_putbuff(UART0,x_16,5);
//      DELAY_MS(2);
    }
}
/**************************����*****************************/
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
/**************************�������˲�������λ��ʾ�����汾*****************************/
/*
void main(void)
{
#if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
#endif 
    
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 ��λ��ad
    uart_init(UART0,115200);//����0  UART0_RX_PIN    PTD6   UART0_TX_PIN    PTD7      

    kalman1_state rp;//�ṹ��
    kalman1_init(&rp, (float)(adc_once(ADC0_SE10, ADC_16bit)) , 10);//�������˲���ʼ��
    
    uint16 x_16[2];//������λ������ʾ����������
    
    while(1)
    {       
      uint16 adc = adc_once(ADC0_SE10, ADC_16bit);//�ӵ�λ����ȡ����ֵ
      kalman1_filter(&rp, adc); //�������˲���ֵ����(&rp)->x
      x_16[0] = (uint16)((&rp)->x);//��һ������,�������˲��������
      x_16[1] = adc; //�ڶ������ߣ�δ�˲�������
      Display(x_16[0], 0, 0);
      vcan_sendware((uint8_t *)(x_16),sizeof(x_16));//������λ������ʾ����   ���� VCAN_PORT   Ϊ UART0 
//      uart_putbuff(UART0,x_16,5);
      DELAY_MS(100);
    }
}
*/
/**************************�������˲�*****************************/
/*
void main(void)
{
    #if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
    #endif 
    
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 ��λ��ad
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
/************************�����˲�***************************/
/*
void  main(void)
{  
    //�����FXоƬ��Ҫ����Ӳ�����㵥Ԫ����5��
    #if  MK60F15 
    SCB->CPACR |=((3UL << 10*2)|(3UL << 11*2));    
    #endif  
    
    uint16 sample;//��λ���Ĳ���ֵ
    uint16 effect;//��Чֵ
    uint16 count=0;//����
    const uint16 MaxOfCount=10;//��������
 
    LCD_Init();
    adc_init(ADC0_SE10);// PTA7 ��λ��ad
    
    DELAY_MS(1000);
    
    effect=adc_once(ADC0_SE10, ADC_16bit);//��λ��effectֵ
    
    while(1)
    {      
      { //��λ���˲����� �ή��������
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