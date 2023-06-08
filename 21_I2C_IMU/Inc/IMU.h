/*
 * IMU.h
 *
 *  Created on: Jun 1, 2023
 *      Author: mdelarosa
 */

#ifndef IMU_H_
#define IMU_H_

#include "I2C.h"

#define DEVID_R 				0x00
#define DEVICE_ADDR 			0b1101000
#define ACCEL_CONFIG_R 			0x14
#define POWER_MGMT_1_R 			0x06
#define POWER_MGMT_2_R 			0x07
#define ACCEL_DATA_X_H		 	0x2D
#define ACCEL_DATA_X_L		 	0x2E
#define ACCEL_DATA_Y_H		 	0x2F
#define ACCEL_DATA_Y_L		 	0x30
#define ACCEL_DATA_Z_H		 	0x31
#define ACCEL_DATA_Z_L		 	0x32
#define ACCEL_SMPLRT_DIV_1		0x10
#define ACCEL_SMPLRT_DIV_2		0x11
#define USER_BANK_SELECT		0x7F

void IMU_init(void);
void IMU_read_address(uint8_t reg);
void IMU_write(uint8_t reg, char value);
void IMU_read_6_values(uint8_t reg);


#endif /* IMU_H_ */
