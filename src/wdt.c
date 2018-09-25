
/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  wdt.h
*��  ��:  Liut
*��  ��:  V1.00
*��  ��:  2017/06/29
*��  ��:  WDT�����ļ�
*��  ע:  ������HRSDK-GDB-HR8P506 V1.0
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#include "wdt.h"

/***************************************************************
 ��  ����WDT��ʼ����ʼ��
 ����ֵ����
 ����ֵ����
***************************************************************/
void WdtInit(void)
{
    WDT_InitStruType x;

    WDT_RegUnLock();
    x.WDT_Tms = 2000;           //ι������2s
    x.WDT_IE = Enable;
    x.WDT_Rst = Enable;
    x.WDT_Clock = WDT_CLOCK_PCLK;
    WDT_Init(&x);
    WDT_Enable();               //WDT���ڽ�������Enable
    WDT_RegLock();

    NVIC_Init(NVIC_WDT_IRQn, NVIC_Priority_0, Enable);
}

void WDT_IRQHandler(void)
{
   WDT_Clear();                  //ι���򲻸�λ����ι����λ
}
