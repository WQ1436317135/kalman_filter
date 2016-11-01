/*=======================================================
 描述: 按下矩阵键盘对应显示键值
             written by 果汁 
	     transplant by 默语
	     2016.10.13
  1 2  3 15
  4 5  6 14
  7 8  9 13
 10 0 11 12
=========================================================*/
#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"
#include "keyboard16.h"
		  	
int key=16;
//int flag;
/*****************初始化*******************/
void key16_init(void)
{
  gpio_init(MY_PT(0),GPO,0);
  gpio_init(MY_PT(1),GPO,0);
  gpio_init(MY_PT(2),GPO,0);
  gpio_init(MY_PT(3),GPO,0);
        
  gpio_init(MY_PT(4),GPO,0);
  gpio_init(MY_PT(5),GPO,0);
  gpio_init(MY_PT(6),GPO,0);
  gpio_init(MY_PT(7),GPO,0);
}
/*************矩阵键盘扫描******************/
unsigned int key16_scan(void)
{      
	unsigned char temp;
	key=16;
	///1
	PBAND_OUT=0xfe;
	temp=PBAND_IN;
	temp=temp%0xf0;
	if(temp!=0xf0)
	{
		delay(20);
		temp=PBAND_IN;            
		temp=temp&0xf0;//0xf0 == 240
		if(temp!=0xf0)
		{
			temp=PBAND_IN;
			switch(temp)
			{
			case 0xee :
				key=12;
	//			flag=2;
				break;
			case 0xde:
				key=13;
	//			flag=8;
				break;
			case 0xbe:
				key=14;
	//			flag=2;
				break;
			case 0x7e:
				key=15;
	//			flag=2;
				break;
			}
			while(temp!=0xf0)		   
			{
				temp=PBAND_IN;
				temp=temp&0xf0;
			}
		}
        }
	////2
	PBAND_OUT=0xfd;
	temp=PBAND_IN;
	temp=temp%0xf0;	
	if(temp!=0xf0)
	{
		delay(20);
		temp=PBAND_IN;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=PBAND_IN;
			switch(temp)
			{
			case 0xed:
				key=11;
	//			flag=2;
				break;
			case 0xdd:
				key=9;
	//			flag=1;
				break;
			case 0xbd:
				key=6;
	//			flag=1;
				break;
			case 0x7d:
				key=3;
	//			flag=1;
				break;
			}
			while(temp!=0xf0)
			{
				temp=PBAND_IN;
				temp=temp&0xf0;
			}
		}
	}
	///3
	PBAND_OUT=0xfb;
	temp=PBAND_IN;
	temp=temp%0xf0;
	if(temp!=0xf0)
	{
		delay(20);
		temp=PBAND_IN;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=PBAND_IN;
			switch(temp)
			{
			case 0xeb:
				key=0;
		//		flag=2;
				break;
			case 0xdb:
				key=8;
		//		flag=1;
				break;
			case 0xbb:
				key=5;
		//		flag=1;
				break;
			case 0x7b:
				key=2;
		//		flag=1;
				break;
			}
			while(temp!=0xf0)
			{
				temp=PBAND_IN;
				temp=temp&0xf0;				
			} 
		}
	}
	///4
	PBAND_OUT=0xf7;
	temp=PBAND_IN;
	temp=temp%0xf0;
	if(temp!=0xf0)
	{
		delay(20);
		temp=PBAND_IN;
		temp=temp&0xf0;
		if(temp!=0xf0)
		{
			temp=PBAND_IN;
			switch(temp)
			{
			case 0xe7:
				key=10;
		//		flag=1;
				break;
			case 0xd7:
				key=7;
		//		flag=1;
				break;
			case 0xb7:
				key=4;
		//		flag=1;
				break;
			case 0x77:
				key=1;
		//		flag=1;
				break;
			}
			while(temp!=0xf0)
			{
				temp=PBAND_IN;
				temp=temp&0xf0;
			}
		}
	}  
	return key;
}
/**********************一个模板***************************/
/*
       switch(key_num)
      {
      case 0:break;
      case 1:break;
      case 2:break;
      case 3:break;
      case 4:break;
      case 5:break;
      case 6:break;
      case 7:break;
      case 8:break;
      case 9:break;
      case 10:break;
      case 11:break;
      case 12:break;
      case 13:break;
      case 14:break;
      case 15:break;
      case 16:break;
      default:break;       
      }
*/