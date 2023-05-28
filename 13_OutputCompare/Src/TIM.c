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

void tim3_PB0_output_compare(void)
{
	//enable clock to GPIOB
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//Configure PB0 to alternate function mode
	GPIOB->MODER &=~ GPIO_MODER_MODER0_0;
	GPIOB->MODER |= GPIO_MODER_MODER0_1;

	//Set PB0 to AF2 (TIM3_CH3)
	GPIOB->AFR[0] |= (2U<<GPIO_AFRL_AFRL0_Pos);

	//enable clock access to timer 3 (connected to PB0)
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	//set prescaler value
	TIM3->PSC = 1600 - 1;

	//set ARR value
	TIM3->ARR = 10000 - 1;

	//set output compare toggle mode
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_1;
	TIM3->CCMR2 &=~ TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_3;

	//enable TIM3CH3 in compare mode
	TIM3->CCER |= TIM_CCER_CC3E;

	//clear timer counter
	TIM3->CNT = 0;

	//enable timer
	TIM3->CR1 |= TIM_CR1_CEN;
}

