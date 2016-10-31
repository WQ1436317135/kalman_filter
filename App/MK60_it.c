/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外初学论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_it.c
 * @brief      山外K60 平台中断复位函数
 * @author     山外科技
 * @version    v5.0
 * @date       2013-06-26
 */

#include "include.h"
/**************************/
int16 wheel=0; 
/*****************************/
   
/*****速度方向**********/
void PIT0_IRQHandler()
{
  

   //duoji_Pd();
   speed_Control(); 
   PIT_Flag_Clear(PIT0);       //清中断标志位
}

void FTM2_INPUT_IRQHandler(void)    //第一路测速
{
    uint8 s = FTM2_STATUS;          //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    uint8 CHn;

    FTM2_STATUS = 0x00;             //清中断标志位

    CHn = 0;
    if( s & (1 << CHn) )
    {
        wheel++;               //速度脉冲累加
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
}
void PORTA_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;
    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;                                   //清中断标志位

    n = 29;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 28;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif

}
/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}






