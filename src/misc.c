#include "main.h"

static unsigned char		fac_us;
static unsigned short		fac_ms;

void qudelay(unsigned int d)
{
	unsigned long		__count;
	
	__count = 12 + (d - 1) * 18;
	
	__asm__ __volatile__ (
		"					mov			r0, %0			\n\t"		
		"loopu: 											\n\t"
		"					sub		r0, r0, #1	\n\t"
		"					bcs			loopu						"
		: "=r" (__count)
		: "0" (__count)						
	);	
}

void qmdelay(unsigned int d)
{
	unsigned long		__count;
	
//	__count = 18000 + (d - 1) * 18000;
	__count = d * 13000;
	
	__asm__ __volatile__ (
		"					mov			r0, %0			\n\t"		
		"loopm: 											\n\t"
		"					sub		r0, r0, #1	\n\t"
		"					bcs			loopm						"
		: "=r" (__count)
		: "0" (__count)						
	);
}


void SysTick_Delay_Init(unsigned char SYSCLK)
{
	SysTick->CTRL = 0xFFFFFFFB;
	
	fac_us = SYSCLK / 8;
	fac_ms = (unsigned short)fac_us * 1000;
}

void delay_ms(unsigned short ms)  
{  
	unsigned long			temp;
	
	SysTick->LOAD = (unsigned long)ms * fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	
	do {
		temp = SysTick->CTRL;	
	} while((temp & 0x01) && (!(temp & (1 << 16))));
	
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
}  

void delay_us(unsigned short us)  
{  
	unsigned long			temp;
	
	SysTick->LOAD = (unsigned long)us * fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	
	do {
		temp = SysTick->CTRL;	
	} while((temp & 0x01) && (!(temp & (1 << 16))));
	
	SysTick->CTRL = 0x00;
	SysTick->VAL = 0x00;
} 

