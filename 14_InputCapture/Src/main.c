#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"
#include "ADC.h"
#include "SYSTICK.h"
#include "TIM.h"

int timestamp = 0;
//Must have jumper wire between D33 and D26 on Nucleo board (PB0 and PB6)
int main(void)
{
	//setup⠀

	//Initialize UART TX/RX so that we can transmit ADC values over serial
	uart3_tx_rx_init();

	//enable LED toggling timer
	tim3_PB0_output_compare();

	//enable input capture timer
	tim4_PB6_input_capture();

	//run loop
	while(1)
	{
		//Wait until edge captured
		while(!(TIM4->SR & TIM_SR_CC1IF)){}

		//Read Value of counter
		timestamp = TIM4->CCR1;
		printf("Timestamp: %d \n\r", (int)timestamp);
	}
}
