#include "include.h"
#include "Pid.h"
//方向PD参数
float Dir_P=3.0;//舵机的pd       4 ，，，3.2    120    2.4，，，1.4  
float Dir_D=2.1;
float Dir_D1=0.8;
//2.0 ，1.8，，原始
int AnglePID=0;
int Dir_D_Value=0.0;
int Last1_AngleError=0,Last2_AngleError=0;
int Fina_Angle=0;
extern int Driection_error;
extern int Driection_error_Line;
extern  char serach_hang_end;
char Zhangai_Count=0;
char Black_Angle=0;
extern char Black_flag;
extern unsigned char Black_Count;
extern unsigned char Black_Error;
extern int Sum;
/*************************/
/*************************/
int SpeedNow=0;
float Speed_P=3.1,Speed_I=0.3;//140..7.3
int  SpeedError=0,  Last_SpeedError=0; 
int SpeedEpt=160,Speed_Out=0;
extern int16 wheel;
char Speed_Driection=0;

void duoji_Pd()//舵机PD
{  
  /****************如何防止突然的误差..在图像抖动的时候，不好用*************/
  if(Sum!=0) 
  { AnglePID=Driection_error* Dir_P+Dir_D*(Driection_error-2*Last1_AngleError+Last2_AngleError)
            +Dir_D1*Driection_error_Line;
    Last2_AngleError=Last1_AngleError;
    Last1_AngleError=Driection_error;
    /*******************障碍物的处理****************/
    if(Black_flag==1) 
        {Zhangai_Count=Black_Count;
        Black_Angle=1;
        gpio_set(PTC1,1);
        }
    else if(Black_flag==-1) 
        {Zhangai_Count=Black_Count;
         Black_Angle=-1;
        gpio_set(PTC1,1);
         }
   
    Zhangai_Count--;  
    if(Zhangai_Count<0)     
      {
        Zhangai_Count=0;
         Black_Angle=0;
       gpio_set(PTC1,0);
      }
    Fina_Angle= Midle_Angle+ AnglePID+ Black_Angle*Black_Error;
 }
    /**********舵机的限值**********/
    if( Fina_Angle>Max_Angle)      Fina_Angle=Max_Angle;
    else if( Fina_Angle<Min_Angle) Fina_Angle=Min_Angle;         
 ftm_pwm_duty(FTM1,FTM_CH0, Fina_Angle);
 //  ftm_pwm_duty(FTM1,FTM_CH0,Midle_Angle);
}
void   speed_Control()//速度调整PI
{  
  Speed_Driection=GPIO_GET_NBIT(1,PTB18);
  if( Speed_Driection==0)
           SpeedNow = wheel;
  else 
            SpeedNow = -wheel;
    wheel=0;   //必要不可
  /***************************/
   SpeedError=SpeedEpt-SpeedNow;
   if(SpeedError>40)     SpeedError=40;
   Speed_Out=Speed_Out+(int)Speed_P*( SpeedError-Last_SpeedError)+Speed_I*SpeedError;
   if(Speed_Out>500)    Speed_Out=500;
   if(Speed_Out<-600)      Speed_Out=-600;
if(Speed_Out>=0)
{
  
  ftm_pwm_duty(FTM0,FTM_CH2, Speed_Out);  //240_170   250_180
  ftm_pwm_duty(FTM0,FTM_CH4,0);
}
else if(Speed_Out<0)
{
  ftm_pwm_duty(FTM0,FTM_CH2, 0);  //240_170   250_180
  ftm_pwm_duty(FTM0,FTM_CH4,0-Speed_Out); 
}

Last_SpeedError= SpeedError; 

  
  
 
 
}