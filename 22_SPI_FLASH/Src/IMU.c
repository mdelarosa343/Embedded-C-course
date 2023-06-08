#include <stdint.h>
#include "IMU.h"
#include "SYSTICK.h"

char data;

uint8_t data_rec[6];


void IMU_read_address(uint8_t reg)
{
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
}

void IMU_write(uint8_t reg, char value)
{
	I2C1_byteWrite(DEVICE_ADDR, reg, &value);
}

void IMU_read_6_values(uint8_t reg)
{
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
	data_rec[0] = data;
	reg+=1;
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
	data_rec[1] = data;
	reg+=1;
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
	data_rec[2] = data;
	reg+=1;
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
	data_rec[3] = data;
	reg+=1;
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
	data_rec[4] = data;
	reg+=1;
	I2C1_byteRead(DEVICE_ADDR, reg, &data);
	data_rec[5] = data;
}

void IMU_init(void)
{
	//Enable I2C module
	I2C1_init();

	//Read DEVID, should return 0xEA
	IMU_read_address(DEVID_R);

	//Select User Bank 0
	IMU_write(USER_BANK_SELECT, (0U << 4));

	//reset IMU
	IMU_write(POWER_MGMT_1_R, (1U << 7));

	//delay for reset
	SysTickDelaymicrosecond(100);

	//wake up IMU
	IMU_write(POWER_MGMT_1_R, (1U));

	//Select User Bank 2
	IMU_write(USER_BANK_SELECT, (2U << 4));

	//wait for bank select
	SysTickDelaymicrosecond(200);

	//Set scale range to +-4g
	IMU_write(ACCEL_CONFIG_R, (0b01 << 1));

	//Set ODR to 375 Hz
	IMU_write(ACCEL_SMPLRT_DIV_1, 0x00);
	IMU_write(ACCEL_SMPLRT_DIV_2, 0x02);

	//Select User Bank 0
	IMU_write(USER_BANK_SELECT, (0U << 4));
}
