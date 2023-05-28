#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"

int main(void)
{
	/*setup*/
	uart3_tx_init();


	/*run loop*/
	while(1)
	{
		printf("Hello from STM32F4.....\n\r");
	};
}
