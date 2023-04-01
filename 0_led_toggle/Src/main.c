

#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOB_OFFSET		(0x0400U)
#define GPIOB_BASE			(AHB1PERIPH_BASE + GPIOB_OFFSET)

#define RCC_OFFSET 			(0x3800U)
#define RCC_BASE 			(AHB1PERIPH_BASE + RCC_OFFSET)

#define RCC_AHB1EN_R_OFFSET	(0x30U)
#define RCC_AHB1EN_R		*(volatile unsigned int*)(RCC_BASE + RCC_AHB1EN_R_OFFSET)

#define MODE_R_OFFSET 		(0x00U)
#define GPIOB_MODE_R		*(volatile unsigned int*)(GPIOB_BASE + MODE_R_OFFSET)

#define OD_R_OFFSET 		(0x14U)
#define GPIOB_OD_R			*(volatile unsigned int*)(GPIOB_BASE + OD_R_OFFSET)



// this bit for RCC enable for GPIOB
#define RCC_GPIOBEN 		(1U<<1)

// green led is PB0
#define G_LED_PIN			(1U<<0)

// blue led is PB7
#define B_LED_PIN			(1U<<7)

// red led is PB14
#define R_LED_PIN			(1U<<14)



int main(void)
{
	/*setup*/

	/*Enable clock to GPIOB*/
	RCC_AHB1EN_R |= RCC_GPIOBEN;

	/*Set pin 0 as output pin*/
	GPIOB_MODE_R |= (1U<<0);
	GPIOB_MODE_R &=~ (1U<<1);

	/*Set pin 7 as output pin*/
	GPIOB_MODE_R |= (1U<<14);
	GPIOB_MODE_R &=~ (1U<<15);

	/*Set pin 14 as output pin*/
	GPIOB_MODE_R |= (1U<<28);
	GPIOB_MODE_R &=~ (1U<<29);

	/*run loop*/
	for(;;){

		/*toggle pin output data on led pins*/
		GPIOB_OD_R ^= (G_LED_PIN | B_LED_PIN | R_LED_PIN);

		/* primitive delay before toggling again*/
		for(int i = 0; i < 100000; i++);
	};
}
