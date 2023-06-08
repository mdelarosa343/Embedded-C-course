#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"
#include "SYSTICK.h"
#include "SPI.h"
#include "FLASH.h"



int main(void)
{
	/*setup*/
	uart3_tx_rx_init();
	SPI1_gpio_init();
	SPI1_config();

	//target address (24 bit max)
	uint32_t addr = 0x000FAF;

	//value to write to address
	uint8_t value = 0x69;

	uint8_t result;

	//This line is a dummy transmit to "catch" errant clock behavior on first transmission
	uint8_t txtest = FLASH_busy();
	if(txtest)
	{
		printf("First clock still bad");
	}

	/*run loop*/
	while(1)
	{
		//write 0xAF to adrr, wait 0.1 sec, and then read addr
		FLASH_WRITE(addr, value);
		printf("Write complete \n\r");
		result = FLASH_READ(addr);
		printf("Read complete -------- value: %d \n\r", result);
	}
}

