/*
 * FLASH.h
 *
 *  Created on: Jun 7, 2023
 *      Author: mdelarosa
 */

#ifndef FLASH_H_
#define FLASH_H_

#define READ_SR_1		0x05
#define READ_DATA		0x03
#define WRITE_ENABLE	0x06
#define PAGE_PROGRAM	0x02

uint8_t FLASH_READ(uint32_t address);
void FLASH_WRITE(uint32_t address, uint8_t value);

#endif /* FLASH_H_ */
