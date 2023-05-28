#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"
#include "ADC.h"
#include "SYSTICK.h"
#include "TIM.h"

// green led is PB0
#define G_LED_PIN			(1U<<0)

// blue led is PB7
#define B_LED_PIN			(1U<<7)

// red led is PB14
#define R_LED_PIN			(1U<<14)

//user button is PC13
#define BTN_Pin			(1U<<13)



int main(void)
{
	/*setup*/

	//Initialize UART TX/RX so that we can transmit ADC values over serial
	uart3_tx_rx_init();

	//Initialize timer
	tim2_1Hz_init();

	/*Enable clock to GPIOB and GPIOC*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

	/*Set PB0 as output pin*/
	GPIOB->MODER |= GPIO_MODER_MODER0_0;
	GPIOB->MODER &=~ GPIO_MODER_MODER0_1;

	/*Set PB7 as output pin*/
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
	GPIOB->MODER &=~ GPIO_MODER_MODER7_1;

	/*Set PB14 as output pin*/
	GPIOB->MODER |= GPIO_MODER_MODER14_0;
	GPIOB->MODER &=~ GPIO_MODER_MODER14_1;

	/*Set PC13 as input pin*/
	GPIOC->MODER &=~ GPIO_MODER_MODER13_0;
	GPIOC->MODER &=~ GPIO_MODER_MODER13_1;

	/*run loop*/
	while(1)
	{
		//wait for UIF flag
		while(!(TIM2->SR & TIM_SR_UIF)){}

		//clear UIF flag
		TIM2->SR &=~ TIM_SR_UIF;

		//toggle LED's
		GPIOB->ODR ^= R_LED_PIN | G_LED_PIN | B_LED_PIN;

		printf("A second has passed!! \n\r");
	}
}
