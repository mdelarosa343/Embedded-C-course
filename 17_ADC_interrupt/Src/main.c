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
	pa3_adc_interrupt_init();
	start_conversion();

	/*run loop*/
	while(1)
	{

	}
}

static void adc_callback(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor Value : %d \n\r", (int)sensor_value);
}

void ADC_IRQHandler(void)
{
	//check if EOC flag is raised
	if((ADC1->SR & ADC_SR_EOC)!= 0)
	{
		//clear EOC flag
		ADC1->SR &=~ ADC_SR_EOC;

		//Do the thing
		adc_callback();

	}
}
