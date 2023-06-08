#include "stm32f746xx.h"


void I2C1_init(void)
{
	//Enable Clock access for GPIOB
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	/*Note: PB8 ---- SCL
	 * 		PB9 ---- SDA
	 */

	//set PB8 and PB9 to alternate function mode
	GPIOB->MODER |= (0b10 << GPIO_MODER_MODER8_Pos | 0b10 << GPIO_MODER_MODER9_Pos);

	//set PB8 and PB9 to alternate function 4
	GPIOB->AFR[1] |= (4u << GPIO_AFRH_AFRH0_Pos | 4u << GPIO_AFRH_AFRH1_Pos);

	//set PB8 and PB9 output types to open drain
	GPIOB->OTYPER |= (GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);

	//Enable pull-up for PB8 and PB9
	GPIOB->PUPDR |= (0b01 << GPIO_PUPDR_PUPDR8_Pos | 0b01 << GPIO_PUPDR_PUPDR9_Pos);

	//Enable Clock access to I2C1
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

	//Do a Reset
	I2C1->CR1 &=~ I2C_CR1_PE;

	//Peripheral Clock Frequency = 16MHz?

	//Set SCL to standard mode (100KHz)
	I2C1->TIMINGR |= 3U << I2C_TIMINGR_PRESC_Pos;
	I2C1->TIMINGR |= 0x13 << I2C_TIMINGR_SCLL_Pos;
	I2C1->TIMINGR |= 0xF << I2C_TIMINGR_SCLH_Pos;
	I2C1->TIMINGR |= 0x2 << I2C_TIMINGR_SDADEL_Pos;
	I2C1->TIMINGR |= 0x4 << I2C_TIMINGR_SCLDEL_Pos;

	//Enable I2C1 module
	I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1_byteRead(char saddr, char maddr, char* data)
{
	//wait until bus not busy
	while(I2C1->ISR & I2C_ISR_BUSY){}

	//Clear stop flag
	I2C1->ICR |= I2C_ICR_STOPCF;

	/*Send memory address to slave*/
	//Set NBYTES to 1
	I2C1->CR2 &=~ (0xFF << I2C_CR2_NBYTES_Pos);
	I2C1->CR2 |= 1U << I2C_CR2_NBYTES_Pos;

	//set slave address
	I2C1->CR2 |= ((saddr << I2C_CR2_SADD_Pos) << 1);

	//set write mode
	I2C1->CR2 &=~ I2C_CR2_RD_WRN;

	//generate start
	I2C1->CR2 |= I2C_CR2_START;

	//wait for TXIS flag to be set (transmitter empty)
	while(!(I2C1->ISR & I2C_ISR_TXIS)){}

	//Write memory address to TXDR
	I2C1->TXDR = maddr;

	//wait for transmit complete
	while(!(I2C1->ISR & I2C_ISR_TC)){}

	/*read from slave*/

	//set read mode
	I2C1->CR2 |= I2C_CR2_RD_WRN;

	//generate restart
	I2C1->CR2 |= I2C_CR2_START;

	//wait for RXNE flag to be set
	while(!(I2C1->ISR & I2C_ISR_RXNE)){}

	//read data from receive register
	*data++ = I2C1->RXDR;

	//wait for transmit complete
	while(!(I2C1->ISR & I2C_ISR_TC)){}

	//generate stop
	I2C1->CR2 |= I2C_CR2_STOP;
}

void I2C1_burstRead(char saddr, char maddr, unsigned int n, char* data)
{
	//wait until bus not busy
	while(I2C1->ISR & I2C_ISR_BUSY){}

	//Clear stop flag
	I2C1->ICR |= I2C_ICR_STOPCF;

	/*Send memory address to slave*/
	//Set NBYTES to 1
	I2C1->CR2 &=~ (0xFF << I2C_CR2_NBYTES_Pos);
	I2C1->CR2 |= 1U << I2C_CR2_NBYTES_Pos;

	//set slave address
	I2C1->CR2 |= ((saddr << I2C_CR2_SADD_Pos) << 1);

	//set write mode
	I2C1->CR2 &=~ I2C_CR2_RD_WRN;

	//generate start
	I2C1->CR2 |= I2C_CR2_START;

	//wait for TXIS flag to be set (transmitter empty)
	while(!(I2C1->ISR & I2C_ISR_TXIS)){}

	//Write memory address to TXDR
	I2C1->TXDR = maddr;

	//wait for transmit complete
	while(!(I2C1->ISR & I2C_ISR_TC)){}


	/*read from slave*/
	//Set NBYTES to n
	I2C1->CR2 &=~ (0xFF << I2C_CR2_NBYTES_Pos);
	I2C1->CR2 |= n << I2C_CR2_NBYTES_Pos;

	//set read mode
	I2C1->CR2 |= I2C_CR2_RD_WRN;

	//generate restart
	I2C1->CR2 |= I2C_CR2_START;

	//loop until NBYTES received (essentially transmit complete)
	while(!(I2C1->ISR & I2C_ISR_TC))
	{
		//what
		for(int i = 0; i < 300; i++){}

		//wait for RXNE flag to be set
		while(!(I2C1->ISR & I2C_ISR_RXNE)){}

		//read data from receive register and increment pointer
		*data++ = I2C1->RXDR;
	}

	//generate stop
	I2C1->CR2 |= I2C_CR2_STOP;
}

void I2C1_byteWrite(char saddr, char maddr, char* data)
{
	//wait until bus not busy
	while(I2C1->ISR & I2C_ISR_BUSY){}

	//Clear stop flag
	I2C1->ICR |= I2C_ICR_STOPCF;

	/*Send memory address to slave*/
	//Set NBYTES to 2
	I2C1->CR2 &=~ (0xFF << I2C_CR2_NBYTES_Pos);
	I2C1->CR2 |= (2 << I2C_CR2_NBYTES_Pos);

	//set slave address
	I2C1->CR2 |= ((saddr << I2C_CR2_SADD_Pos) << 1);

	//set write mode
	I2C1->CR2 &=~ I2C_CR2_RD_WRN;

	//generate start
	I2C1->CR2 |= I2C_CR2_START;

	//wait for TXIS flag to be set (transmitter empty)
	while(!(I2C1->ISR & I2C_ISR_TXIS)){}

	//Write memory address to TXDR
	I2C1->TXDR = maddr;

	/*write to slave*/
	//wait for TXIS flag to be set (transmitter empty)
	while(!(I2C1->ISR & I2C_ISR_TXIS)){}

	//Write data to TXDR
	I2C1->TXDR = *data;

	//wait until NBYTES transmitted (essentially transmit complete)
	while(!(I2C1->ISR & I2C_ISR_TC)){}

	//generate stop
	I2C1->CR2 |= I2C_CR2_STOP;
}
