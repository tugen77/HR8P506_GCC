/*********************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*�ļ���:  systick.h
*��  ��:  Liut
*��  ��:  V1.01
*��  ��:  2017/06/29
*��  ��:  ϵͳ�δ�ģ�����ͷ�ļ�
*��  ע:  ������HRSDK-GDB-8P506
          ���������ѧϰ����ʾʹ�ã����û�ֱ�����ô����������ķ��ջ������е��κη������Ρ�
**********************************************************/
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

//#include "lib_config.h"
//#include "system_hr8p506.h"

void User_SysTickInit(void);
void Delay_100us(__IO uint32_t nTime);
void TimingDelay_Decrement(void);

#endif

