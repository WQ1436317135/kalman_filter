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
      for(i=0;i<10;i++)   /* 1Ϊ���ߣ���0Ϊ����*/
        for(k=0;k<8;k++)        
     ImageData[i*8+k]=(ImageData_ina[hang*10+i]>>(7-k) )&0x01;
     if(first_scanning==0)              //��һ������ɨ�裬���ó�ʼֵ
       {
         first_scanning=1;
         for(i=0;i<60;i++)  //���θ�60�и�����ֵ
          { 
            centre_signal[i]=39;           //ÿһ�е����Ķ���39
            halfwidth_signal[i]=39;        //ÿһ�е����������39
          }
       }
      else
       {
         Middle_last=centre_signal[hang];    //���ϴ�����ֵ��Middle_last
         _halfwidth=halfwidth_signal[hang];  //���ϴ��������ֵ��_halfwidth
       }
      // halfwidth[hang]=20;
         for(i=0;i<80;i++)                  //�ж��ұ߽��Ƿ���
           {
             if(ImageData[Middle_last+i]==0) //ɨ����ɫ ��255Ϊ�ף�    
               {
                 virtual_R=Middle_last+i;    //�����ұ߽磨��ʱ����ʵ�ұ߽磩
                 getright_flag=1;            //�ұ߽�δ���߱�־λ
               }
             else                           //Ϊ0��ɨ���ڱ�
               {
                virtual_R=virtual_R+1;
                 break; 
               }
               
             if(Middle_last+i==79)        //�ұ߶���
               {
                 getright_flag=0;           //�ұ߶��߱�־λ
                 virtual_R=79;              //�ұ��߼��߽�ֵ������ʵ��
                  break;
               }
           }
    if(virtual_R>=79)        //�ұ߶���
          {
           getright_flag=0;           //�ұ߶��߱�־λ
            virtual_R=79;              //�ұ��߼��߽�ֵ������ʵ��   
             }
        for(i=0;i<80;i++)                  //�ж���߽��Ƿ���
           {
             
             if(ImageData[Middle_last-i]==0) //ɨ�����ߣ�255Ϊ�ף�   
              {
                 virtual_L=Middle_last-i;    //������߽磨��ʱ����ʵ��߽磩
                 getleft_flag=1;             //ɨ�赽��߽��־λ
               }
              else
              {
                virtual_L=virtual_L-1;
                 break;
              }
             if(Middle_last-i==0)         //��߶���
               {
                  getleft_flag=0;           //��߶��߱�־λ
                  virtual_L=0;              //����߼��߽�ֵ������ʵ��
                  break;
                }
               
            }
         
  if(virtual_L<=0)         //��߶���
               {
                  getleft_flag=0;           //��߶��߱�־λ
                  virtual_L=0;              //����߼��߽�ֵ������ʵ��
                  
                }       
 //���ֶ������// 
     if(getleft_flag==1&&getright_flag==1)   //��û����
              {
                 L=virtual_L;
                 R=virtual_R;
                halfwidth_signal[hang]=(virtual_R-virtual_L)/2;
               }
      else if(getleft_flag==0&&getright_flag==1)      //��߶���ʱ   
             { 
                R=virtual_R;
                L=virtual_R - _halfwidth*2;                 //��߽߱���ʵֵ=�ұ߽߱�-�ϴ�������           
              }
      else if(getleft_flag==1&&getright_flag==0)    //�ұ߶���ʱ 
              {
                L=virtual_L;
                R=virtual_L+_halfwidth*2;                  //�ұ߽߱���ʵֵ=�ұ߽߱�-�ϴ�������
              }
    else if(getleft_flag==0&&getright_flag==0) 
           {
                L=L_old;
                R=R_old;                  //�ұ߽߱���ʵֵ=�ұ߽߱�-�ϴ�������
             }
Middle=(int)((R + L)/2); 
if(Middle>=79)  Middle=79;
if(Middle<=0)  Middle=0;
centre_signal[hang]=Middle;
Signal_Driection_error=centre_signal[hang]-39;
//Display4(Signal_Driection_error,84,2);
 }