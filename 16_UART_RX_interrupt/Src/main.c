#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"

char key;

// green led is PB0
#define G_LED_PIN			(1U<<0)

// blue led is PB7
#define B_LED_PIN			(1U<<7)

// red led is PB14
#define R_LED_PIN			(1U<<14)

//user button is PC13
#define BTN_Pin			(1U<<13)

static void uart_callback(void);

int main(void)
{
	/*setup*/

	/*Enable clock to GPIOB*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	/*Set PB0 as output pin*/
	GPIOB->MODER |= GPIO_MODER_MODER0_0;
	GPIOB->MODER &=~ GPIO_MODER_MODER0_1;

	/*Set PB7 as output pin*/
	GPIOB->MODER |= GPIO_MODER_MODER7_0;
	GPIOB->MODER &=~ GPIO_MODER_MODER7_1;

	/*Set PB14 as output pin*/
	GPIOB->MODER |= GPIO_MODER_MODER14_0;
	GPIOB->MODER &=~ GPIO_MODER_MODER14_1;

	/*Initialize UART RX*/
	uart3_rx_interrupt_init();


	/*run loop*/
	while(1)
	{

	};
}

static void uart_callback(void)
{
	key = USART3->RDR;
	if(key == '1')
	{
		GPIOB->BSRR = R_LED_PIN | G_LED_PIN | B_LED_PIN;
	}
	else
	{
		GPIOB->BSRR = R_LED_PIN<<16 | G_LED_PIN<<16 | B_LED_PIN<<16;
	}
}

void USART3_IRQHandler(void)
{
	//check if RXNE is set
	if(USART3->ISR & USART_ISR_RXNE)
	{
		//Do the thing
		uart_callback();
	}
}
