/*
 * ADC.h
 *
 *  Created on: May 22, 2023
 *      Author: mdela
 */

#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void pa3_adc_init(void);
void start_conversion(void);
uint32_t adc_read(void);
void pa3_adc_interrupt_init(void);

#endif /* ADC_H_ */
