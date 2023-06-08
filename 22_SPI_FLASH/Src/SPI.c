#include <stdint.h>
#include "stm32f746xx.h"
#include "SPI.h"

void SPI1_gpio_init(void)
{
	//Enable clock access to GPIO of pins (PA5, PA6, PA7, PD15)
	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN);

	//Configure GPIO pins
	/*Note: PA5  ---- SCK
	 * 		PA6  ---- MISO
	 * 		PA7  ---- MOSI
	 * 		PD15 ---- CS
	 */

	//set PA 5,6, and 7 to alternate function mode
	GPIOA->MODER |= (0b10 << GPIO_MODER_MODER5_Pos | 0b10 << GPIO_MODER_MODER6_Pos | 0b10 << GPIO_MODER_MODER7_Pos);

	//set PD15 as output pin
	GPIOD->MODER |= (0b01 << GPIO_MODER_MODER15_Pos) ;

	//set PA 5,6, and 7 to alternate function 5
	GPIOA->AFR[0] |= (5u << GPIO_AFRL_AFRL5_Pos | 5u << GPIO_AFRL_AFRL6_Pos | 5u << GPIO_AFRL_AFRL7_Pos);
}

void SPI1_config(void)
{
	//Enable clock access to SPI module
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	//Set SPI Baudrate to 4MHz (16MHz/4)
	SPI1->CR1 |= (4u << SPI_CR1_BR_Pos);

	//Configure CPOL and CPHA (mode 0)
	SPI1->CR1 &=~ (SPI_CR1_CPOL | SPI_CR1_CPOL);

	//Enable Full Duplex
	SPI1->CR1 &=~ SPI_CR1_RXONLY;

	//Set MSB first
	SPI1->CR1 &=~ SPI_CR1_LSBFIRST;

	//Set to Master mode
	SPI1->CR1 |= SPI_CR1_MSTR;

	//Disable CRC
	SPI1->CR1 &=~ SPI_CR1_CRCEN;

	//Set mode to Software Slave Management (SSM) and set NSS pin high
	SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI);

	//configure transfer size to 8 bits
	SPI1->CR2 |= (0b0111 << SPI_CR2_DS_Pos);

	//configure reception threshold to 8 bits
	SPI1->CR2 |= SPI_CR2_FRXTH;

	//Enable SPI module
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI1_transmit(uint8_t* data, uint32_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		//Wait for TXE to be set (transmit buffer empty)
		while(!(SPI1->SR & SPI_SR_TXE)){}

		//Write data to the data register
		*(__IO uint8_t *)&SPI1->DR = data[i];
	}

	//Wait until TXE is set
	while(!(SPI1->SR & SPI_SR_TXE)){}
	//Wait for SPI not busy
	while(SPI1->SR & SPI_SR_BSY){}
}

void SPI1_receive(uint8_t* data, uint32_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		//send dummy data
		*(__IO uint8_t *)&SPI1->DR = 0;

		//Wait for RXNE flag
		while(!(SPI1->SR & SPI_SR_RXNE)){}

		//read data from data register and increment data pointer
		*data++ = (SPI1->DR);
	}

	//Wait until TXE is set
	while(!(SPI1->SR & SPI_SR_TXE)){}
	//Wait for SPI not busy
	while(SPI1->SR & SPI_SR_BSY){}
}

void cs_enable(void)
{
	//Set PD15 low
	GPIOD->BSRR = (1u << GPIO_BSRR_BR15_Pos);
}

void cs_disable(void)
{
	//Set PD15 high
	GPIOD->BSRR = (1u << GPIO_BSRR_BS15_Pos);
}
