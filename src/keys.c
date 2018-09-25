#include "main.h"

#include "uart.h"

void keysInit(void)
{
	GPIO_InitSettingType	GPIO_InitStructure;
	KINT_InitSettingType	KINT_InitStructure;
	
	GPIO_InitStructure.Signal = GPIO_Pin_Signal_Digital;
	GPIO_InitStructure.Dir = GPIO_Direction_Input;
	GPIO_InitStructure.Func = GPIO_Reuse_Func0;
	GPIO_InitStructure.ODE = GPIO_ODE_Output_Disable;
	GPIO_InitStructure.DS = GPIO_DS_Output_Normal;
	GPIO_InitStructure.PUE = GPIO_PUE_Input_Enable;
	GPIO_InitStructure.PDE = GPIO_PDE_Input_Disable;

	GPIO_Init(GPIO_Pin_B13, &GPIO_InitStructure); // KL2
	
	KINT_InitStructure.IE_Set = KINT_IE_Set_Enable;
	KINT_InitStructure.Trigger_Style = KINT_Trigger_Trailing_Edge;
	KINT_Init(GPIO_Pin_B13, &KINT_InitStructure);                     //初始化按键中断PB9  
}



void KINT_IRQHandler(void)
{
	if(KINT_GetITFlag(GPIO_Pin_B13) != RESET)
	{
		KINT_ClearITFlag(GPIO_Pin_B13);      // 清除按键中断标志位
		Uart0PutChar(0x5A);
	}
}


