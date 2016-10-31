#include "Mutily_Line.h"
#include "include.h"
#define ArryNum 15
int Driection_error=0;
extern char Cross_flag;
extern char Cross_center;
extern int SpeedEpt;
extern int SpeedNow;
extern char L_Correct;
extern char R_Correct;
char CountStop=0;
char StopFlag=0;
extern unsigned char ImageData[60][80]; 
extern unsigned char Speed_Flag1;
extern unsigned char Speed_Flag2;
extern unsigned char  Final_Flag;
extern unsigned char Stop_start;
extern unsigned char AverRateth;
int AverRate[ArryNum][20]=
{
  
  {0,0,0,0,0,3,4,5,6,7,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,7,6,6,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,7,6,6,3,3,2,0,0,0,},
  
  {0,0,0,0,0,3,4,5,7,9,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,4,5,7,8,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,8,6,6,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,3,5,8,7,6,6,5,4,3,2,0,0,0,},
  {0,0,0,0,0,3,3,5,6,7,7,6,5,4,3,2,0,0,0,},
 
  

  {0,0,0,0,0,3,4,5,7,9,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,4,5,7,8,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,8,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,8,7,6,6,5,4,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,7,7,6,6,4,3,2,0,0,0,},
  
  
  /* 
  {0,0,0,0,0,3,4,5,6,7,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,7,6,6,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,7,6,6,3,3,2,0,0,0,},
  
   {0,0,0,0,0,3,4,5,6,7,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,6,5,4,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,7,6,6,3,3,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,6,7,6,6,3,3,2,0,0,0,},
  
  {0,0,0,0,0,3,5,6,9,7,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,5,6,7,9,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,5,5,6,8,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,4,5,7,8,7,6,6,3,2,2,0,0,0,},
  {0,0,0,0,0,3,4,5,6,7,7,6,6,3,2,2,0,0,0,},
  
  
   {0,0,0,0,0,3,5,6,9,7,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,5,6,9,7,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,5,6,7,8,6,5,4,3,2,2,0,0,0,},
  {0,0,0,0,0,3,5,6,7,8,7,6,6,3,2,2,0,0,0,},
  {0,0,0,0,0,3,5,6,6,7,7,6,6,3,2,2,0,0,0,},
  
  */
/*
  */
  

  

};
int Sum=0;
int  MiddeSum=0;
/*****************************/
extern char  center[];
extern char  serach_hang_end;
extern float Dir_P;//舵机的pd       4 ，，，3.2    120    2.4，，，1.4  
extern float Dir_D;
extern float Dir_D1;
extern char Black_flag;
extern char Zhangai_Count;
extern char podao_flag;
char  podao_flag_count=0;
float Dir_P_last;//舵机的pd       4 ，，，3.2    120    2.4，，，1.4  
float Dir_D_last;
float Dir_D1_last;
int Averge_Driection_error=0;
int Driection_error_Line=0;
int Speed_control=0,Speed_control_last=0;
char Speed_switch=0;
int   Switch[10]={0};
int Line_error=0;
char Average_Switch=0;
char ControlSpeed=0;
float Fit_R=0, Fit_K=0;
char Fit_X[OV7725_EAGLE_H],Fit_Y[OV7725_EAGLE_H];
void Block();
void SpeedMax();
void SpeedMiddle();
void SpeedMin();
void Line_Fit(signed char* x,signed char* y,uint8 n)
{
	float x_sum_average=0;   //数组 X[N] 个元素求和 并求平均值
	float y_sum_average=0;   //数组 Y[N] 个元素求和 并求平均值
	float x_square_sum=0;    //数组 X[N] 个个元素的平均值
	float x_multiply_y=0;    //数组 X[N]和Y[N]对应元素的乘积
	uint8 i=0;
	float z=0;
	z=0;
	for(i=0;i<n;i++)
	{
		z = z + x[i];
	}
	x_sum_average = z/n;
	
	z=0;
	for(i=0;i<n;i++)
	{
		z = z + y[i];
	}
	y_sum_average = z/n;
	
	z=0;
	for(i=0;i<n;i++)
	{
		z = z + x[i]*x[i];
	}
	x_square_sum = z;
	
	z=0;
	for(i=0;i<n;i++)
	{
		z = z + x[i]*y[i];
	}
	x_multiply_y = z;
	
	
	Fit_K = ( x_multiply_y - n * x_sum_average * y_sum_average)/( x_square_sum - n * x_sum_average*x_sum_average );
  	Fit_R = y_sum_average - Fit_K * x_sum_average;
}
void finalout()
{
MiddeSum=0;
Line_error=0;
Sum =0;
int k=0;
int y=0;
/***************************/
for(int hang=54;hang>serach_hang_end;hang--)
      {      
           Fit_X[k] = OV7725_EAGLE_H - 1 - hang;
           Fit_Y[k] = center[hang];		
           k++;
         
      }
Line_Fit(Fit_X,Fit_Y,k);  
Speed_control=Fit_K*10;
if(Speed_control<0)                            Speed_control=-Speed_control;
if(Average_Switch-Speed_control>3)            Speed_control=Average_Switch-3;
else if( Speed_control -Average_Switch>4)    Speed_control=Average_Switch+4;

/**************************************/
 if(Speed_control<3&&podao_flag==1)
      {
       podao_flag_count=80;
      } 
 podao_flag_count--;
if(podao_flag_count<0)    {podao_flag_count=0;}
 else                     {Black_flag=0; Zhangai_Count=0;}
/************************/
if(Stop_start==1&&Speed_control<3&&podao_flag_count==0&&serach_hang_end<12)
                         Block();


/*********速度的控制***********************/
if(Speed_Flag1==1)          SpeedMin();     
else if(Speed_Flag2==1)     SpeedMax(); 
else                        SpeedMiddle();    
if(StopFlag>0)
{
 if (SpeedNow>30)      SpeedEpt-=50;
 else if(SpeedNow>10)  SpeedEpt=4;
 if(SpeedNow<11)       SpeedEpt=0;
gpio_set(PTC1,1);
}

/************************/
if(serach_hang_end<54) 
{
  for(int hang=59;hang>serach_hang_end;hang--)
      { 
          MiddeSum= MiddeSum+center[hang]*AverRate[AverRateth*5+Speed_switch][hang/3];
          Sum =Sum+AverRate[AverRateth*5+Speed_switch][hang/3];
      }
if(Sum!=0)   
      {
        Driection_error= MiddeSum/Sum-39;
       Driection_error_Line=12*Fit_K;
        //Driection_error_Line=center[serach_hang_end]-center[serach_hang_end/2];
      }
if(Cross_flag==1)  
            {  Driection_error=Cross_center-39;
              Driection_error_Line=0;
           }
if( Driection_error_Line<-20)   Driection_error_Line=-20;
else if( Driection_error_Line>20)   Driection_error_Line=20;
}
 //Display4( Driection_error,84,0);
Average_Switch=0;
for(int i=0;i<4;i++)
    {
     Average_Switch+=Switch[i];
     Switch[i]=Switch[i+1];
    }
Average_Switch=Average_Switch/9;
Switch[9]=Speed_control;
}
/***************/
void SpeedMax()
{
int y=0;
for(y=59;y>=1;y--)
    { 
       if(ImageData[y][32]==0)  break;  
       if(ImageData[y][39]==0)  break;  /* 0为黑线，，255为白线*/
       if(ImageData[y][46]==0)  break;  
    }
y=y+5;
if(serach_hang_end<54&&Black_flag==0)
{
    if(Speed_control<4&&y<30)//100
               {   
                 
                  if (SpeedNow<75)          SpeedEpt+=30;
                  else if (SpeedNow<85)      SpeedEpt+=20;
                  else if (SpeedNow<95)      SpeedEpt+=10;
                  else if (SpeedNow<105)      SpeedEpt=100;
                  else                        SpeedEpt=100;
                  if(SpeedEpt>105)            SpeedEpt=105;
                  Speed_switch=0;
                 } 
     else if(Speed_control<4&&y<50)//95
               {
                   
               
                  if (SpeedNow<72)           SpeedEpt+=25;
                  else if (SpeedNow<82)      SpeedEpt+=15;
                  else if (SpeedNow<92)      SpeedEpt+=10;
                  else if (SpeedNow<100)     SpeedEpt=95;
                  else if (SpeedNow>100)     SpeedEpt-=10;
                  else                       SpeedEpt=95;
                  if(SpeedEpt>100)           SpeedEpt=100;
                  Speed_switch=0; 
                 } 
 /******************************************/
        else if(Speed_control<8&&y<28)          //90
               {    
                   if (SpeedNow<75)           SpeedEpt+=20;
                  else if (SpeedNow<85)      SpeedEpt+=10;
                  else if (SpeedNow<95)      SpeedEpt=90;
                  else if (SpeedNow>95)     SpeedEpt-=20;
                  else                       SpeedEpt=90;
                  if(SpeedEpt>95)           SpeedEpt=95;
                   Speed_switch=1;
                  }
       else if(Speed_control<8&&y<41)//85
             {
                  
                  if (SpeedNow<75)          SpeedEpt+=15;
                  else if (SpeedNow<80)      SpeedEpt+=5;
                  else if (SpeedNow<90)      SpeedEpt=85;
                  else if (SpeedNow>100)     SpeedEpt-=20;
                  else if (SpeedNow>90)      SpeedEpt-=10;
                  else                       SpeedEpt=85;
                  if(SpeedEpt>90)            SpeedEpt=90;
                  Speed_switch=1;
                }
                  
      else if(Speed_control<8&&y<50)//80
             {
                 
                   if (SpeedNow<70)            SpeedEpt+=15;
                  else if (SpeedNow<80)      SpeedEpt+=5;
                  else if (SpeedNow<85)      SpeedEpt=80;
                   else if (SpeedNow>100)     SpeedEpt-=20;
                  else if (SpeedNow>85)      SpeedEpt-=10;
                  else                        SpeedEpt=80;
                  if(SpeedEpt>90)            SpeedEpt=90;
                 Speed_switch=1;
                }
 /***************************************/
 
      else if(Speed_control<11&&y<12)//80
           {
                  if (SpeedNow<70)            SpeedEpt+=15;
                  else if (SpeedNow<80)      SpeedEpt+=5;
                  else if (SpeedNow<85)      SpeedEpt=80;
                  else if (SpeedNow>100)     SpeedEpt-=20;
                  else if (SpeedNow>85)      SpeedEpt-=10;
                  else                        SpeedEpt=80;
                  if(SpeedEpt>90)            SpeedEpt=90;  
                  Speed_switch=2;

              }
     else if(y>50)//75
           {
                 if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<80)      SpeedEpt=75;
                   else if (SpeedNow>100)    SpeedEpt-=40;
                  else if (SpeedNow>90)      SpeedEpt-=30;
                  else if (SpeedNow>80)      SpeedEpt-=20;
                  else                        SpeedEpt=75;
                  if(SpeedEpt>85)            SpeedEpt=85;  
                 Speed_switch=2;

           }
   else 
          {
                 if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<80)      SpeedEpt=75;
                 else if (SpeedNow>100)    SpeedEpt-=40;
                  else if (SpeedNow>90)      SpeedEpt-=30;
                  else if (SpeedNow>80)      SpeedEpt-=20;
                  else                        SpeedEpt=75;
                  if(SpeedEpt>85)            SpeedEpt=85;      
                 Speed_switch=3;

          }
}
else 
{              if (SpeedNow<70)            SpeedEpt+=5;
                else if (SpeedNow<80)      SpeedEpt=75;
                else if (SpeedNow>100)    SpeedEpt-=60;
                else if (SpeedNow>90)      SpeedEpt-=30;
                else if (SpeedNow>80)      SpeedEpt-=20;
                else                        SpeedEpt=75;
                if(SpeedEpt>85)            SpeedEpt=85;  
                 Speed_switch=4;
}
if(Speed_switch==0)
        {
         Dir_P=1.7;Dir_D=2.4; Dir_D1=0;
        }
else if(Speed_switch==1)
       {
       Dir_P=1.8;Dir_D=3.0; Dir_D1=0.3;
    
       }
else if(Speed_switch==2)
      {
       Dir_P=1.95;Dir_D=3.0;Dir_D1=0.5; 

      }
else  if(Speed_switch==3)
      {
       Dir_P=2.1;Dir_D=3.0;Dir_D1=0.6;     //大弯
       
      }
else if(Speed_switch==4)
      {
       Dir_P=2.2;Dir_D=4.0;Dir_D1=0.7;     //大弯

      }
}

/**************************/
void SpeedMiddle()
{
int y=0;
for(y=59;y>=1;y--)
    { 
       if(ImageData[y][32]==0)  break;  
       if(ImageData[y][39]==0)  break;  /* 0为黑线，，255为白线*/
       if(ImageData[y][46]==0)  break;  
    }
y=y+5;
if(serach_hang_end<54&&Black_flag==0)
{
    if(Speed_control<4&&y<30)//95
               {   
                 
                   if (SpeedNow<70)          SpeedEpt+=25;
                  else if (SpeedNow<80)      SpeedEpt+=15;
                  else if (SpeedNow<85)      SpeedEpt+=5;
                  else if (SpeedNow>100)      SpeedEpt-=10; 
                  else                        SpeedEpt=90;
                  if(SpeedEpt>95)            SpeedEpt=95;
                  Speed_switch=0;
                 } 
     else if(Speed_control<4&&y<50)//85
               {
                   
               
                  if (SpeedNow<75)         SpeedEpt+=15;
                  else if (SpeedNow<80)      SpeedEpt+=5;
                  else if (SpeedNow<90)      SpeedEpt=85;
                  else if (SpeedNow>100)     SpeedEpt-=20;
                  else if (SpeedNow>90)      SpeedEpt-=10;
                  else                       SpeedEpt=80;
                  if(SpeedEpt>90)            SpeedEpt=90;
                  Speed_switch=0; 
                 } 
 /******************************************/
        else if(Speed_control<8&&y<28)          //85
               {    
                 if (SpeedNow<75)          SpeedEpt+=15;
                  else if (SpeedNow<80)      SpeedEpt+=5;
                  else if (SpeedNow<90)      SpeedEpt=85;
                  else if (SpeedNow>100)     SpeedEpt-=20;
                  else if (SpeedNow>90)      SpeedEpt-=10;
                  else                       SpeedEpt=85;
                  if(SpeedEpt>90)            SpeedEpt=90;
                   Speed_switch=1;
                  }
       else if(Speed_control<8&&y<41)//80
             {
                  
                   if (SpeedNow<70)            SpeedEpt+=15;
                  else if (SpeedNow<80)      SpeedEpt+=5;
                  else if (SpeedNow<85)      SpeedEpt=80;
                  else if (SpeedNow>95)      SpeedEpt-=20;
                  else if (SpeedNow>90)      SpeedEpt-=10;
                   else if (SpeedNow>85)      SpeedEpt-=10;
                  else                        SpeedEpt=80;
                  if(SpeedEpt>95)            SpeedEpt=95;
                  Speed_switch=1;
                }
                  
      else if(Speed_control<8&&y<50)//75
             {
                 
                   if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<80)      SpeedEpt=75;
                  else if (SpeedNow>110)      SpeedEpt-=30;
                  else if (SpeedNow>95)      SpeedEpt-=20;
                  else if (SpeedNow>80)      SpeedEpt-=10;
                  else                        SpeedEpt=75;
                  if(SpeedEpt>85)            SpeedEpt=85; 
                 Speed_switch=1;
                }
 /***************************************/
 
      else if(Speed_control<11&&y<12)//75
           {
                 if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<80)      SpeedEpt=75;
                  else if (SpeedNow>90)      SpeedEpt-=30;
                  else if (SpeedNow>80)      SpeedEpt-=20;
                  else                        SpeedEpt=75;
                  if(SpeedEpt>85)            SpeedEpt=85;   
                 Speed_switch=2;

              }
     else if(y>50)//75
           {
                 if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<80)      SpeedEpt=75;
                  else if (SpeedNow>95)      SpeedEpt-=30;
                  else if (SpeedNow>80)      SpeedEpt-=20;
                  else                        SpeedEpt=75;
                  if(SpeedEpt>85)            SpeedEpt=85;  
                 Speed_switch=2;

           }
   else 
          {
                 if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<80)      SpeedEpt=75;
                  else if (SpeedNow>95)      SpeedEpt-=30;
                  else if (SpeedNow>80)      SpeedEpt-=20;
                  else                        SpeedEpt=75;
                  if(SpeedEpt>85)            SpeedEpt=85;      
                 Speed_switch=3;

          }
}
else 
{              if (SpeedNow<70)            SpeedEpt+=5;
                  else if (SpeedNow<75)      SpeedEpt=70;
                  else if (SpeedNow>95)      SpeedEpt-=30;
                  else if (SpeedNow>80)      SpeedEpt-=20;
                  else                        SpeedEpt=70;
                  if(SpeedEpt>85)            SpeedEpt=85;  
                 Speed_switch=4;
}
if(Speed_switch==0)
        {
         Dir_P=1.7;Dir_D=2.0; Dir_D1=0;
        }
else if(Speed_switch==1)
       {
       Dir_P=1.8;Dir_D=2.5; Dir_D1=0.3;
    
       }
else if(Speed_switch==2)
      {
       Dir_P=1.95;Dir_D=2.5;Dir_D1=0.5; 

      }
else  if(Speed_switch==3)
      {
       Dir_P=2.1;Dir_D=2.5;Dir_D1=0.6;     //大弯
       
      }
else if(Speed_switch==4)
      {
       Dir_P=2.2;Dir_D=2.5;Dir_D1=0.7;     //大弯

      }

}
void  SpeedMin()
{
int y=0;
for(y=59;y>=1;y--)
    { 
       if(ImageData[y][32]==0)  break;  
       if(ImageData[y][39]==0)  break;  /* 0为黑线，，255为白线*/
       if(ImageData[y][46]==0)  break;  
    }
y=y+5;
if(serach_hang_end<54&&Black_flag==0)
{
    if(Speed_control<4&&y<30)//85
               {   
                 
                  if (SpeedNow<70)           SpeedEpt+=20;
                  else if (SpeedNow<80)      SpeedEpt+=10;
                  else if (SpeedNow<90)      SpeedEpt=85; 
                  else                        SpeedEpt=85;
                  if(SpeedEpt>90)             SpeedEpt=90;
                  Speed_switch=0;
                 } 
     else if(Speed_control<4&&y<50)//85
               {
                  
                  if (SpeedNow<70)           SpeedEpt+=20;
                  else if (SpeedNow<80)      SpeedEpt+=10;
                  else if (SpeedNow<90)      SpeedEpt=85; 
                  else                        SpeedEpt=85;
                  if(SpeedEpt>90)             SpeedEpt=90;
                  Speed_switch=0; 
                 } 
 /******************************************/
        else if(Speed_control<8&&y<28)          //80
               {    
                   if (SpeedNow<75)          SpeedEpt+=7;
                   else if (SpeedNow<85)      SpeedEpt=80;
                     else if (SpeedNow>85)      SpeedEpt-=15;
                   else                       SpeedEpt=80;
                   if(SpeedEpt>85)            SpeedEpt=85;
                   Speed_switch=1;
                  }
       else if(Speed_control<8&&y<41)//75
             {
                  
                    if (SpeedNow<70)          SpeedEpt+=7;
                   else if (SpeedNow<80)      SpeedEpt=75;
                     else if (SpeedNow>80)      SpeedEpt-=15;
                   else                       SpeedEpt=75;
                   if(SpeedEpt>80)            SpeedEpt=80;
                  Speed_switch=1;
                }
                  
      else if(Speed_control<8&&y<50)//75
             {
                 
                 if (SpeedNow<80)           SpeedEpt=75;
                 else if (SpeedNow>80)      SpeedEpt-=15;
                 Speed_switch=1;
                }
 /***************************************/
 
      else if(Speed_control<11&&y<12)//70
           {
                if (SpeedNow<75)           SpeedEpt=70;  
                   else if (SpeedNow>75)      SpeedEpt-=15;
                 Speed_switch=2;

              }
   else                                           //65
          {
                 if (SpeedNow<70)           SpeedEpt=65; 
                 else if (SpeedNow>70)      SpeedEpt-=15;
                 Speed_switch=3;

          }
}
else 
{             if (SpeedNow<70)           SpeedEpt=65; 
              else if (SpeedNow>70)      SpeedEpt-=15;
                 Speed_switch=4;
}
if(Speed_switch==0)
        {
         Dir_P=1.7;Dir_D=3.4; Dir_D1=0;
        }
else if(Speed_switch==1)
       {
       Dir_P=1.8;Dir_D=3.9; Dir_D1=0;
    
       }
else if(Speed_switch==2)
      {
       Dir_P=1.95;Dir_D=3.9;Dir_D1=0; 

      }
else  if(Speed_switch==3)
      {
       Dir_P=2.0;Dir_D=3.9;Dir_D1=0;     //大弯
       
      }
else if(Speed_switch==4)
      {
       Dir_P=2.1;Dir_D=3.9;Dir_D1=0;     //大弯

      }
}


void Block()
{ 
char stop_hang_left=0,stop_hang_right=0;
char stop_leftflag=0,stop_rightflag=0;
char stop_count=0;
char left_black=0;
char right_black=0;
 

  int lie=0;
  int hang=56;
  for( lie=42;lie>23; lie--)
    {
      for( hang=55;hang>45;hang--)
              if(ImageData[hang][lie]==0)  {stop_hang_left=hang;left_black=1;break;}
      if(left_black==1) break;
    }  
  
   for( lie=36;lie<55;lie++)
    {
      for( hang=55;hang>45;hang--)
               if(ImageData[hang][lie]==0)  {stop_hang_right=hang; right_black=1; break;}
      if(right_black==1) break;
    }  
  if(stop_hang_left-stop_hang_right<3&&stop_hang_left-stop_hang_right>-3&&serach_hang_end<20)
  {if(left_black==1)
        {  
          stop_count=0;
          for( lie=0;lie<78;lie++)
             if(ImageData[stop_hang_left][lie]!=ImageData[stop_hang_left][lie+1])
                                 stop_count++;
            if(stop_count>4)  {stop_leftflag=1;}
        }
   if(right_black==1)
        {  
          stop_count=0;
          for( lie=79;lie>1;lie--)
             if(ImageData[stop_hang_right][lie]!=ImageData[stop_hang_right][lie-1])
                                 stop_count++;
            if(stop_count>4)  {stop_rightflag=1;}
        }
       
  }
if(stop_leftflag==1&&stop_rightflag==1&&CountStop<=0)  
            {StopFlag++; 
             CountStop=80;
            } 
 CountStop--;
 if( CountStop<=0)  { CountStop=0;  ;}
}

