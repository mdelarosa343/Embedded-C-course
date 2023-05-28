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

void tim4_PB6_input_capture(void)
{
	//enable clock to GPIOB
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	//Configure PB6 to alternate function mode
	GPIOB->MODER &=~ GPIO_MODER_MODER6_0;
	GPIOB->MODER |= GPIO_MODER_MODER6_1;

	//Set PB6 to AF2 (TIM4_CH1)
	GPIOB->AFR[0] |= (2U<<GPIO_AFRL_AFRL6_Pos);

	//enable clock access to timer 4 (connected to PB6)
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	//set prescaler value
	TIM4->PSC = 16000 - 1;

	//set CH1 to input mode
	TIM4->CCMR2 |= TIM_CCMR1_CC1S_0;
	TIM4->CCMR2 &=~ TIM_CCMR1_CC1S_1;

	//set CH1 to capture at rising edge and enable capture mode
	TIM4->CCER &=~  TIM_CCER_CC1NP | TIM_CCER_CC1P;
	TIM4->CCER |=  TIM_CCER_CC1E;

	//enable timer 4
	TIM4->CR1 |= TIM_CR1_CEN;
}

