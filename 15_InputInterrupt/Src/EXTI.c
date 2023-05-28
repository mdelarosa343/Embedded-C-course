#include "stm32f746xx.h"

//user button is PC13

void pc13_exti_init(void)
{
	//disable global interrupts
	__disable_irq();

	//enable clock access to GPIOC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

	//set PC13 as input
	GPIOC->MODER &=~ GPIO_MODER_MODER13_0 | GPIO_MODER_MODER13_1;

	//enable clock access to syscfg module
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	//select port C for exti13
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;

	//unmask exti13
	EXTI->IMR |= EXTI_IMR_IM13;

	//select falling edge trigger
	EXTI->FTSR |= EXTI_FTSR_TR13;

	//enable exti13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//enable global interrupts again
	__enable_irq();
}
