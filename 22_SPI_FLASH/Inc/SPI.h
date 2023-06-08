/*
 * SPI.h
 *
 *  Created on: Jun 6, 2023
 *      Author: mdelarosa
 */

#ifndef SPI_H_
#define SPI_H_

void SPI1_gpio_init(void);
void SPI1_config(void);
void SPI1_transmit(uint8_t* data, uint32_t size);
void SPI1_receive(uint8_t* data, uint32_t size);
void cs_enable(void);
void cs_disable(void);

#endif /* SPI_H_ */
