#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"
#include "ADC.h"


uint32_t sensor_value;

int main(void)
{
	/*setup*/
	//Initialize UART TX/RX so that we can transmit ADC values over serial
	uart3_tx_rx_init();

	//Initialize ADC
	pa3_adc_init();


	/*run loop*/
	while(1)
	{
		start_conversion();
		sensor_value = adc_read();
		printf("Sensor Value : %d \n\r", (int)sensor_value);
	}
}
