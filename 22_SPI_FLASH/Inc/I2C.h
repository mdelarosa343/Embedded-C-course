/*
 * I2C.h
 *
 *  Created on: Jun 1, 2023
 *      Author: mdelarosa
 */

#ifndef I2C_H_
#define I2C_H_

void I2C1_init(void);
void I2C1_byteRead(char saddr, char maddr, char* data);
void I2C1_burstRead(char saddr, char maddr, unsigned int n, char* data);
void I2C1_byteWrite(char saddr, char maddr, char* data);

#endif /* I2C_H_ */
