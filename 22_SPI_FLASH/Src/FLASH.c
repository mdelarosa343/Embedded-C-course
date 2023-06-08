#include <stdint.h>
#include "stm32f746xx.h"
#include "FLASH.h"
#include "SPI.h"


uint8_t FLASH_busy(void)
{
	uint8_t receive;

	//Create command sequence (READ_SR_1 code)
	uint8_t command = READ_SR_1;

	//enable cs
	cs_enable();

	//send command
	SPI1_transmit(&command, 1);

	//receive data into receive pointer
	SPI1_receive(&receive, 1);

	//disable cs
	cs_disable();

	//return BUSY bit of SR_1
	return (receive & 1u);
}

uint8_t FLASH_READ(uint32_t address)
{
	uint8_t receive;

	//Create command sequence (read_data command, then 24 bit address)
	uint8_t command[4] =
	{
		(uint8_t)READ_DATA,
		(uint8_t)((address & 0x00FF0000)>>16),
		(uint8_t)((address & 0x0000FF00)>>8),
		(uint8_t)(address & 0x000000FF)
	};
	//enable cs
	cs_enable();

	//send read command
	SPI1_transmit(command, 4);

	//receive data into receive pointer
	SPI1_receive(&receive, 1);

	//disable cs
	cs_disable();

	//wait for Flash not busy
	while(FLASH_busy()){}

	//return result
	return receive;
}

void FLASH_WRITE(uint32_t address, uint8_t value)
{
	//send write enable command before writing
	uint8_t W_E = WRITE_ENABLE;
	//enable cs
	cs_enable();
	//send read command
	SPI1_transmit(&W_E, 1);
	//disable cs
	cs_disable();

	//wait for Flash not busy
	while(FLASH_busy()){}

	//Create write command sequence (PAGE_PROGRAM command, then 24 bit address, then 8 bit write value)
	uint8_t command[5] =
	{
		(uint8_t)PAGE_PROGRAM,
		(uint8_t)((address & 0x00FF0000)>>16),
		(uint8_t)((address & 0x0000FF00)>>8),
		(uint8_t)(address & 0x000000FF),
		value
	};
	//enable cs
	cs_enable();

	//send write command
	SPI1_transmit(command, 5);

	//disable cs
	cs_disable();

	//wait for Flash not busy
	while(FLASH_busy()){}
}
