#include "stm32f746xx.h"
#include "core_cm7.h"

#define SYSTICK_LOAD_VAL 		16000 //CPU cycles per millisecond

void SysTickDelayMs(int delay)
{
	//Configure Systick

	//Reload timer with number of clocks per millisecond
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	//clear systick current value register
	SysTick->VAL = 0;

	// enable systick and select clock source as CPU clock
	SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk);

	for(int i=0; i<delay; i++)
	{
		//wait for count flag to be set before looping again
		while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0){}
	}
	SysTick->CTRL = 0;
}

void SysTick_1hz_interrupt(void)
{
	//Reload timer with number of clocks per second
	SysTick->LOAD = 16000000 - 1;

	//clear systick current value register
	SysTick->VAL = 0;

	// enable systick and select clock source as CPU clock AND enable interrupt mode
	SysTick->CTRL = (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk);
}

