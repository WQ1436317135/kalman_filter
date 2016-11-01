/*=======================================================
 描述: 按下矩阵键盘对应显示键值
             written by 果汁
	     transplant by 郑默语
	     2016.10.13
  1 2  3 15
  4 5  6 14
  7 8  9 13
 10 0 11 12
=========================================================*/
#ifndef __KEYBORD16_H__
#define __KEYBORD16_H__
/* 
可以更改B端口为其他端口,但若想更改0-7:   i.改下面的0为1或2或3   ii.还需到C文件里去改  
*/
#define PBAND_IN     PTB_B0_IN   //B0-B7
#define PBAND_OUT    PTB_B0_OUT
#define MY_PT(x)     PTB##x  

#define delay(n) DELAY_MS(n)

extern void key16_init(void);//注意占用   

extern unsigned int key16_scan(void);

#endif //__KEYBORD16_H__