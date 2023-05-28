#include <stdint.h>
#include "stm32f746xx.h"

#define SYS_FREQ 		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart3_tx_init(void);
void uart3_write(int ch);

int main(void)
{
	/*setup*/
	uart3_tx_init();


	/*run loop*/
	while(1)
	{
		uart3_write('Y');
	};
}


void uart3_tx_init(void)
{
	/******************Configure USART GPIO Pin******************/

	/*Enable GPIOD clock (Pin for USART3_TX is PD8)*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/*Set pin D8 to alternate function mode*/
	GPIOD->MODER &=~ GPIO_MODER_MODER8_0;
	GPIOD->MODER |= GPIO_MODER_MODER8_1;

	/*Set PD8 alternate function mode to UART_TX*/
	GPIOD->AFR[1] |= (GPIO_AFRH_AFRH0_0 | GPIO_AFRH_AFRH0_1 | GPIO_AFRH_AFRH0_2) ; 	/*((1U<<8) | (1U<<9) | (1U<<10))*/
	GPIOD->AFR[1] &=~ GPIO_AFRH_AFRH0_3; 	/*(1U<<11)*/


	/******************Configure USART module******************/

	/*Enable USART2 clock*/
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	/*Configure Baudrate*/
	uart_set_baudrate(USART3, APB1_CLK, UART_BAUDRATE);

	/*Configure transfer direction to Transmit and set UART defaults*/
	USART3->CR1 = USART_CR1_TE;

	/*Enable UART Module*/
	USART3->CR1 |= USART_CR1_UE;
}

void uart3_write(int ch)
{
	/*Make sure TX data register is empty*/
	while(!(USART3->ISR & USART_ISR_TXE)){}

	/*Write to TX data register*/
	USART3->TDR = (ch & 0xFF);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
