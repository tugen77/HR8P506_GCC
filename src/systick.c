/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  systick.c
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ϵͳ�δ�ģ�����
*��  ע:  ������HRSDK-GDB-8P506
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "systick.h"

__IO uint32_t TimingDelay;

/*********************************************************
������: void User_SysTickInit(void)
��  ��: ϵͳ�δ��ʼ����100us
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void User_SysTickInit(void)
{
    SYSTICK_InitStruType x;

    x.SysTick_Value = SystemCoreClock / 10000;  //100us
    x.SysTick_ClkSource = SysTick_ClkS_Cpu;
    x.SysTick_ITEnable = Enable;                //�ж�ʹ��
    SysTick_Init(&x);

    SysTick_Disable();                          //ʹ��ʱ�ſ���
}

/*********************************************************
������: void Delay_100us(__IO uint32_t nTime)
��  ��: ϵͳ�δ�100us��ʱ
����ֵ: ��ʱ100us����
���ֵ: ��
����ֵ: �� 
**********************************************************/
void Delay_100us(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    SysTick_Enable();
    while(TimingDelay != 0);
    SysTick_Disable();
}

/*********************************************************
������: void TimingDelay_Decrement(void)
��  ��: ϵͳ�δ��жϵ���
����ֵ: ��
���ֵ: ��
����ֵ: �� 
**********************************************************/
void TimingDelay_Decrement(void)
{
    if(TimingDelay != 0)
        TimingDelay --;
}

void SysTick_IRQHandler(void)
{
    TimingDelay_Decrement();
}
