#include <stdio.h>
#include <stdint.h>
#include "stm32f746xx.h"
#include "UART.h"
#include "IMU.h"
#include "SYSTICK.h"

#define FOUR_G_SCALE_FACTOR 8192

int16_t x,y,z;
float xg, yg, zg;
extern uint8_t data_rec[6];

int main(void)
{
	/*setup*/
	IMU_init();

	//enable FPU
	SCB->CPACR |= (1U<<20 | 1U<<21 | 1U<<22 | 1U<<23);

	/*run loop*/
	while(1)
	{
		IMU_read_6_values(ACCEL_DATA_X_H);

		x = ((data_rec[0]<<8)|data_rec[1]);
		y = ((data_rec[2]<<8)|data_rec[3]);
		z = ((data_rec[4]<<8)|data_rec[5]);

		xg = (float)x / FOUR_G_SCALE_FACTOR;
		yg = (float)y / FOUR_G_SCALE_FACTOR;
		zg = (float)z / FOUR_G_SCALE_FACTOR;
	}
}

