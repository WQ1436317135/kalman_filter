#include "Signal.h"
#include "include.h"
int Middle=39,Middle_last=39; 
int first_scanning=0;
int Signal_Driection_error=0;
int R_old=79,L_old=0;
int centre_signal[60]={39};
int  halfwidth_signal[60]={39};
extern char Cross_flag;
extern char Cross_center;
extern unsigned char ImageData[60][80];
void scanning_track(unsigned char *ImageData_ina,int hang)  
{ 
     int i=0,k=0;
     int  _halfwidth=0;
     int virtual_R=79, virtual_L=0;
     int R=79,L=0;
     uint8 ImageData[80];
     int  getright_flag=1, getleft_flag=1;
      for(i=0;i<10;i++)   /* 1为黑线，，0为白线*/
        for(k=0;k<8;k++)        
     ImageData[i*8+k]=(ImageData_ina[hang*10+i]>>(7-k) )&0x01;
     if(first_scanning==0)              //第一次起跑扫描，设置初始值
       {
         first_scanning=1;
         for(i=0;i<60;i++)  //依次给60行赋中心值
          { 
            centre_signal[i]=39;           //每一行的中心都是39
            halfwidth_signal[i]=39;        //每一行的赛道半宽都是39
          }
       }
      else
       {
         Middle_last=centre_signal[hang];    //将上次中心值给Middle_last
         _halfwidth=halfwidth_signal[hang];  //将上次赛道半宽值给_halfwidth
       }
      // halfwidth[hang]=20;
         for(i=0;i<80;i++)                  //判断右边界是否丢线
           {
             if(ImageData[Middle_last+i]==0) //扫到白色 （255为白）    
               {
                 virtual_R=Middle_last+i;    //虚拟右边界（此时即真实右边界）
                 getright_flag=1;            //右边界未丢线标志位
               }
             else                           //为0，扫到黑边
               {
                virtual_R=virtual_R+1;
                 break; 
               }
               
             if(Middle_last+i==79)        //右边丢线
               {
                 getright_flag=0;           //右边丢线标志位
                 virtual_R=79;              //右边逻辑边界值（非真实）
                  break;
               }
           }
    if(virtual_R>=79)        //右边丢线
          {
           getright_flag=0;           //右边丢线标志位
            virtual_R=79;              //右边逻辑边界值（非真实）   
             }
        for(i=0;i<80;i++)                  //判断左边界是否丢线
           {
             
             if(ImageData[Middle_last-i]==0) //扫到白线（255为白）   
              {
                 virtual_L=Middle_last-i;    //虚拟左边界（此时即真实左边界）
                 getleft_flag=1;             //扫描到左边界标志位
               }
              else
              {
                virtual_L=virtual_L-1;
                 break;
              }
             if(Middle_last-i==0)         //左边丢线
               {
                  getleft_flag=0;           //左边丢线标志位
                  virtual_L=0;              //左边逻辑边界值（非真实）
                  break;
                }
               
            }
         
  if(virtual_L<=0)         //左边丢线
               {
                  getleft_flag=0;           //左边丢线标志位
                  virtual_L=0;              //左边逻辑边界值（非真实）
                  
                }       
 //各种丢线情况// 
     if(getleft_flag==1&&getright_flag==1)   //都没丢线
              {
                 L=virtual_L;
                 R=virtual_R;
                halfwidth_signal[hang]=(virtual_R-virtual_L)/2;
               }
      else if(getleft_flag==0&&getright_flag==1)      //左边丢线时   
             { 
                R=virtual_R;
                L=virtual_R - _halfwidth*2;                 //左边边界真实值=右边边界-上次赛道宽           
              }
      else if(getleft_flag==1&&getright_flag==0)    //右边丢线时 
              {
                L=virtual_L;
                R=virtual_L+_halfwidth*2;                  //右边边界真实值=右边边界-上次赛道宽
              }
    else if(getleft_flag==0&&getright_flag==0) 
           {
                L=L_old;
                R=R_old;                  //右边边界真实值=右边边界-上次赛道宽
             }
Middle=(int)((R + L)/2); 
if(Middle>=79)  Middle=79;
if(Middle<=0)  Middle=0;
centre_signal[hang]=Middle;
Signal_Driection_error=centre_signal[hang]-39;
//Display4(Signal_Driection_error,84,2);
 }