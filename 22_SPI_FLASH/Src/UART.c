#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"

#define SYS_FREQ 		16000000
#define APB1_CLK		SYS_FREQ
#define UART_BAUDRATE	115200


static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
void uart3_tx_init(void);
void uart3_write(int ch);

int __io_putchar(int ch)
{
	uart3_write(ch);
	return ch;
}

void DMA1_stream3_init(uint32_t src, uint32_t dst, uint32_t len)
{
	//Enable clock access to DMA1
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;

	//Disable DMA1 stream 3
	DMA1_Stream3->CR &=~ DMA_SxCR_EN;

	//wait until stream 3 is disabled
	while(DMA1_Stream3->CR & DMA_SxCR_EN){}

	//clear all interrupt flags for stream 3
	DMA1->LIFCR |= DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3;

	//set the destination buffer
	DMA1_Stream3->PAR = dst;

	//set the source buffer
	DMA1_Stream3->M0AR = src;

	//set length
	DMA1_Stream3->NDTR = len;

	//select stream 3 CH4
	DMA1_Stream3->CR |= 4U << DMA_SxCR_CHSEL_Pos;

	//Enable memory increment
	DMA1_Stream3->CR |= DMA_SxCR_MINC;

	//configure transfer direction (Memory to Peripheral)
	DMA1_Stream3->CR |= 0b01 << DMA_SxCR_DIR_Pos;

	//Enable DMA transfer complete interrupt
	DMA1_Stream3->CR |= DMA_SxCR_TCIE;

	//Enable direct mode and disable FIFO
	DMA1_Stream3->FCR = 0;

	//Enable DMA1 stream 3 again
	DMA1_Stream3->CR |= DMA_SxCR_EN;

	//Enable UART3 transmitter DMA
	USART3->CR3 |= USART_CR3_DMAT;

	//DMA interrupt enable in NVIC
	NVIC_EnableIRQ(DMA1_Stream3_IRQn);
}



void uart3_tx_rx_init(void)
{
	/******************Configure USART GPIO Pins******************/

	/*Enable GPIOD clock (Pins for USART are on GPIOD)*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/*Set PD8 to alternate function mode*/
	GPIOD->MODER &=~ GPIO_MODER_MODER8_0;
	GPIOD->MODER |= GPIO_MODER_MODER8_1;
	/*Set PD8 alternate function mode to UART_TX*/
	GPIOD->AFR[1] |= (GPIO_AFRH_AFRH0_0 | GPIO_AFRH_AFRH0_1 | GPIO_AFRH_AFRH0_2) ;
	GPIOD->AFR[1] &=~ GPIO_AFRH_AFRH0_3;

	/*Set PD9 to alternate function mode*/
	GPIOD->MODER &=~ GPIO_MODER_MODER9_0;
	GPIOD->MODER |= GPIO_MODER_MODER9_1;
	/*Set PD9 alternate function mode to UART_TX*/
	GPIOD->AFR[1] |= (GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH1_1 | GPIO_AFRH_AFRH1_2) ;
	GPIOD->AFR[1] &=~ GPIO_AFRH_AFRH1_3;


	/******************Configure USART module******************/

	/*Enable USART2 clock*/
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	/*Configure Baudrate*/
	uart_set_baudrate(USART3, APB1_CLK, UART_BAUDRATE);

	/*Enable Transmit and Receive and set UART defaults*/
	USART3->CR1 = (USART_CR1_TE | USART_CR1_RE);

	/*Enable UART Module*/
	USART3->CR1 |= USART_CR1_UE;
}

void uart3_rx_interrupt_init(void)
{
	/******************Configure USART GPIO Pins******************/

	/*Enable GPIOD clock (Pin for USART is on GPIOD)*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	/*Set PD9 to alternate function mode*/
	GPIOD->MODER &=~ GPIO_MODER_MODER9_0;
	GPIOD->MODER |= GPIO_MODER_MODER9_1;
	/*Set PD9 alternate function mode to UART_RX*/
	GPIOD->AFR[1] |= (GPIO_AFRH_AFRH1_0 | GPIO_AFRH_AFRH1_1 | GPIO_AFRH_AFRH1_2) ;
	GPIOD->AFR[1] &=~ GPIO_AFRH_AFRH1_3;


	/******************Configure USART module******************/

	/*Enable USART3 clock*/
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	/*Configure Baudrate*/
	uart_set_baudrate(USART3, APB1_CLK, UART_BAUDRATE);

	/*Enable Transmit and Receive and set UART defaults*/
	USART3->CR1 = (USART_CR1_TE | USART_CR1_RE);

	//Enable RXNE interrupt
	USART3->CR1 |= USART_CR1_RXNEIE;

	//Enable RXNE interrupt in NVIC
	NVIC_EnableIRQ(USART3_IRQn);

	/*Enable UART Module*/
	USART3->CR1 |= USART_CR1_UE;
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

	/*Enable USART3 clock*/
	RCC->APB1ENR |= RCC_APB1ENR_USART3EN;

	/*Configure Baudrate*/
	uart_set_baudrate(USART3, APB1_CLK, UART_BAUDRATE);

	/*Configure transfer direction to Transmit and set UART defaults*/
	USART3->CR1 = USART_CR1_TE;

	/*Enable UART Module*/
	USART3->CR1 |= USART_CR1_UE;
}

char uart3_read(void)
{
	/*Make sure RX data register is not empty*/
	while(!(USART3->ISR & USART_ISR_RXNE)){}

	/*Read RX data register*/
	return USART3->RDR;
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
