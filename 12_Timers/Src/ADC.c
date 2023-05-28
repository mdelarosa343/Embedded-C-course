#include "stm32f746xx.h"
#include <stdint.h>

void pa3_adc_init(void)
{
	/*Setup ADC Pin (PA3)*/
	//Enable Clock access to GPIOA
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//Set PA3 to analog input
	GPIOA->MODER |= (GPIO_MODER_MODER3_0 | GPIO_MODER_MODER3_1);


	/*Setup ADC Module*/
	//Enable Clock to ADC Module
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	//start conversion sequence at Channel 1
	ADC1->SQR3 = (3U<<ADC_SQR3_SQ1_Pos);
	//conversion sequence length of 1
	ADC1->SQR1 = (0U<<ADC_SQR1_L_Pos);
	//enable ADC Module
	ADC1->CR2 |= ADC_CR2_ADON;
}

void start_conversion(void)
{
	//Enable continuous conversion
	ADC1->CR2 |= ADC_CR2_CONT;
	//Start adc conversion
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void)
{
	//Wait for conversion to complete
	while(!(ADC1->SR & ADC_SR_EOC)){}

	//read converted result
	return ADC1->DR;
}
