#include "stm32f746xx.h"

void tim2_1Hz_init(void)
{
	//enable clock access to timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//set prescaler value
	TIM2->PSC = 1600 - 1;

	//set ARR value
	TIM2->ARR = 10000 - 1;

	//clear timer counter
	TIM2->CNT = 0;

	//enable timer
	TIM2->CR1 |= TIM_CR1_CEN;
}

void tim2_1Hz_interrupt_init(void)
{
	//enable clock access to timer 2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	//set prescaler value
	TIM2->PSC = 1600 - 1;

	//set ARR value
	TIM2->ARR = 10000 - 1;

	//clear timer counter
	TIM2->CNT = 0;

	//enable timer
	TIM2->CR1 |= TIM_CR1_CEN;

	//Enable TIM2 interrupt
	TIM2->DIER |= TIM_DIER_UIE;

	//Enable TIM2 interrupt in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);

}

