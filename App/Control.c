#include "Control.h"
#include "include.h"
/**************内部变量的声明*****************/
//图像处理相关的变量
char  R[60]={79}, L[60]={0};      //处理之后得到左右黑线，，，，必须是有符号的数可能小于0
char  center[60]={39};
char  L_loseLine[60]={1}, R_loseLine[60]={1};   //丢线的标志，，1为丢线
char width=0,width_last1=0,width_last2=0;
char  serach_hang_start=59;
char  serach_hang_end=4;
char   L_Correct=0,R_Correct=0;
char   Black_flag=0;
char   podao_flag=0;
extern unsigned char Stop_start;
unsigned char *pointer;
/*************外部变量的声明**************/
extern unsigned char ImageData[60][80];    //行解压之后的图像
signed char _width[OV7725_EAGLE_H] =
  {//实际测量

 7,   7,   8,   8,   8,   8,   8,   10,   10,   11,
   12,   12,   13,   13,   14,   14,   14,   16,   16,   17,
     17,   18,   18,   19,   19,   20,   21,   21,   22,   22,
       22,   22,   23,   23,   25,   25,   26,   26,   27,   27,
         28,   28,   29,   29,   30,   30,   31,   31,   32,   32,
           33,   34,   34,   34,   35,   35,   36,   36,   37,   37

  };
/************内部函数的声明**************/
void get_black_line();                 //最开始从两边往中间搜找黑线
/**************************************/
void frist_black_line()
{char L_lie=0,R_lie=0;
for( L_lie=0;L_lie<75;L_lie++)     /**从左到右，，，由黑到白为左边的边界，，，**/
    if(ImageData[serach_hang_start][L_lie]==0&&ImageData[serach_hang_start][L_lie+1]!=0)
                   { break;}
if(L_lie>=75){L[serach_hang_start]=0;L_loseLine[ serach_hang_start]=1;}
else         {L[serach_hang_start]=L_lie;L_loseLine[ serach_hang_start]=0;}
/***********************************/
for(R_lie=79;R_lie>=4;R_lie--)
    if(ImageData[serach_hang_start][R_lie]==0&&ImageData[serach_hang_start][R_lie-1]!=0)
        {break;}
if( R_lie<=4) {R[serach_hang_start]=79;R_loseLine[ serach_hang_start]=1;}
else           {R[serach_hang_start]=R_lie;R_loseLine[ serach_hang_start]=0;}
/*************************/
if(R_loseLine[ serach_hang_start]==0&&L_loseLine[ serach_hang_start]==0)
{if(R[serach_hang_start]-L[serach_hang_start]<0)
  {if(L[serach_hang_start]>=39) L[serach_hang_start]=0;
  if(R[serach_hang_start]<39)    R[serach_hang_start]=79;
  }
}
center[59]=(R[serach_hang_start]+L[serach_hang_start])/2;
}
/************外部函数的声明*************/
void get_black_line()
{
frist_black_line();
char L_lie=0,R_lie=0;
char L_Start=0,R_Start=79;
char L_end_low=0, L_end_up=79,R_end_low=0,R_end_up=79;
char Black_Count=0; //跳出找线循环
char Black_FlagCount=0;
serach_hang_end=4;
 width=0;
 width_last1=0;
 width_last2=0;
 Black_flag=0;
  podao_flag=0;
   L_Correct=0;
   R_Correct=0;
/*****************************************/
for(int hang=58;hang>=4;hang--)
{

  L_Start=L[hang+1];
  L_end_up=L_Start+5;
  if(L_end_up>R[hang+1])   L_end_up=R[hang+1];
  L_end_low=L_Start-3;
  if(L_end_low<0)   L_end_low=0; /* 0为黑线，，1为白线*/
/*****************************************/
  pointer=& ImageData[hang][ L_end_up];
  for(L_lie= L_end_up;L_lie>=L_end_low;L_lie--)
       {
        if(*pointer==0)  {break;}
         pointer--;
        }
  if (L_lie<L_end_low)         {L[hang]=L[hang+1];L_loseLine[hang]=1;}
  else                         { L[hang]=L_lie+1;L_loseLine[hang]=0;}

/**********************************************/
R_Start=R[hang+1];
R_end_low=R_Start-5;
if(R_end_low<L[hang+1])  R_end_low=L[hang+1];
R_end_up=R_Start+3;
if(R_end_up>79)  R_end_up=79;
/********************************/
pointer=&ImageData[hang][R_end_low];
for(R_lie=R_end_low;R_lie<=R_end_up;R_lie++)
      {
      if(*pointer==0)  break;
      pointer++;
      }
if(R_lie>R_end_up)         { R_loseLine[hang]=1;R[hang]=R[hang+1];}//没找到
else                        { R_loseLine[hang]=0;  R[hang]=R_lie-1; }
/************************************/
if(R_loseLine[hang]==0&&L_loseLine[hang]==0)
                  {   center[hang]=(R[hang]+L[hang])/2.0;
                       Black_FlagCount++;
                       width=R[hang]-L[hang];
                       L_Correct++;
                       R_Correct++;
                  }
else if(R_loseLine[hang]==1&&L_loseLine[hang]==0)
                     {
                       center[hang]=L[hang]+ _width[hang];
                       Black_FlagCount=0;
                        L_Correct++;

                      }
else if(R_loseLine[hang]==0&&L_loseLine[hang]==1)
                    {
                     center[hang]=R[hang]-_width[hang];
                      Black_FlagCount=0;
                       R_Correct++;
                    }
else if(R_loseLine[hang]==1&&L_loseLine[hang]==1)
                   {
                    // center[hang]=center[hang+1];
                     center[hang]=39;
                     Black_FlagCount=0;
                   }

/**************************************/
if(width_last2-width>9&&Black_FlagCount>9&&hang>25)
             {
             if((R[hang+2]-R[hang])-(L[hang]-L[hang+2])>5)
                            Black_flag=-1;//障碍在右边
             else if((L[hang]-L[hang+2])-(R[hang+2]-R[hang])>5)
                            Black_flag=1;//左边
            }

width_last2=width_last1;
width_last1=width ;
/*********************************


/**********跳出的条件需要改变**************************/
if(ImageData[hang][center[hang]]==0)    Black_Count++;
else                                    Black_Count=0;
if( Black_Count>2)           {serach_hang_end=hang;break;}
if(R[hang]<5||L[hang]>74||(R[hang]-L[hang]<5))
                              {serach_hang_end=hang;break;}
}
if(serach_hang_end>10&&Black_FlagCount>18)
      {
      podao_flag=1;
    }

}
/****************************************/
int Cross_count=0;
char Cross_flag=0;
char Cross_center=39;
void Cross(int hang)
{
  char L_lie=0,R_lie=79;
  int n=0;
 Cross_flag=0;
 for(n=0;n<80;n++)
         {
           if(ImageData[hang][n]==0)  break;  /* 0为黑线，，255为白线*/
         }
if(n>=80)  Cross_flag=1;
if(Cross_flag==1)
{
   Stop_start=1;
  char Lie=0,y;
  for(Lie=0;Lie<=79;Lie++)
  {
   for(y=60;y>=10;y--)
                {if(ImageData[y][Lie]==0)  break;}
   if(y<=10)        {L_lie=Lie;break;}
   }

  for(Lie=79;Lie>=0;Lie--)
  {
   for(y=60;y>=10;y--)
                {if(ImageData[y][Lie]==0)  break;}
   if(y<=10)        {R_lie=Lie;break;}
   }
}
Cross_center=(L_lie+R_lie)/2;
}
/**************************/
