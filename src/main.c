#include "main.h"
#include "systick.h"
#include "uart.h"
#include "misc.h"
#include "wdt.h"
#include "keys.h"
#include "leds.h"


void Delay(unsigned long x)
{
	unsigned int y;
	while(x--)
		for(y = 100; y > 0; y--);
}

int main(void)
{
	unsigned char			dd;


	User_SysTickInit();
	
	ledsInit();
	Uart0Init(9600);  
	keysInit();
	WdtInit();

	dd = 0;
	while(1)
	{
		WDT_Clear();                        //喂狗不复位，不喂狗复位

		if(dd)
		{
			dd = 0;
			ledsAct(LED_RED, ACT_ON);
			ledsAct(LED_GREEN, ACT_OFF);
		} else {
			dd = 1;
			ledsAct(LED_GREEN, ACT_ON);
			ledsAct(LED_RED, ACT_OFF);
		}
		Delay_100us(10000);
	}
}


