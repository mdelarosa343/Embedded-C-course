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

static void dma_callback(void);

int main(void)
{
	/*setup*/

	char message[31] = "Hello from Stm32 DMA transfer\n\r";
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

	uart3_tx_init();
	DMA1_stream3_init((uint32_t) message, (uint32_t) &(USART3->TDR), (uint32_t) 31);


	/*run loop*/
	while(1)
	{

	};
}

static void dma_callback(void)
{
	GPIOB->ODR ^= R_LED_PIN | G_LED_PIN | B_LED_PIN;
}

void DMA1_Stream3_IRQHandler(void)
{
	//check for transfer complete interrupt
	if(DMA1->LISR & DMA_LISR_TCIF3)
	{
		//clear the flag
		DMA1->LISR |= DMA_LIFCR_CTCIF3;
		//Do the thing
		dma_callback();
	}
}
