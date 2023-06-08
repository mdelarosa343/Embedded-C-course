/*
 * UART.h
 *
 *  Created on: May 22, 2023
 *      Author: mdela
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
#include "stm32f746xx.h"
void uart3_tx_init(void);
void uart3_tx_rx_init(void);
char uart3_read(void);
void uart3_rx_interrupt_init(void);
void DMA1_stream3_init(uint32_t src, uint32_t dst, uint32_t len);

#endif /* UART_H_ */
