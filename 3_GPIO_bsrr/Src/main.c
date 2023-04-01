#include "stm32f746xx.h"


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
	RCC->AHB1ENR |= RCC_GPIOBEN;

	/*Set pin 0 as output pin*/
	GPIOB->MODER |= (1U<<0);
	GPIOB->MODER &=~ (1U<<1);

	/*Set pin 7 as output pin*/
	GPIOB->MODER |= (1U<<14);
	GPIOB->MODER &=~ (1U<<15);

	/*Set pin 14 as output pin*/
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &=~ (1U<<29);

	/*run loop*/
	while(1){

		/*set bits for LED pins*/
		GPIOB->BSRR = (G_LED_PIN | B_LED_PIN | R_LED_PIN);

		/* delay before resetting bits*/
		for(int i = 0; i < 100000; i++);

		/*reset bits for LED pins*/
		GPIOB->BSRR = (G_LED_PIN<<16 | B_LED_PIN<<16 | R_LED_PIN<<16);

		/* delay again*/
		for(int i = 0; i < 100000; i++);
	};
}
