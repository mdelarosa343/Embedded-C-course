#include "stm32f746xx.h"


// this bit for RCC enable for GPIOB
#define RCC_GPIOBEN 		(1U<<1)

// this bit for RCC enable for GPIOC
#define RCC_GPIOCEN 		(1U<<2)

// green led is PB0
#define G_LED_PIN			(1U<<0)

// blue led is PB7
#define B_LED_PIN			(1U<<7)

// red led is PB14
#define R_LED_PIN			(1U<<14)

//user button is PC13
#define BTN_Pin			(1U<<13)



int main(void)
{
	/*setup*/

	/*Enable clock to GPIOB and GPIOC*/
	RCC->AHB1ENR |= RCC_GPIOBEN | RCC_GPIOCEN;

	/*Set PB0 as output pin*/
	GPIOB->MODER |= (1U<<0);
	GPIOB->MODER &=~ (1U<<1);

	/*Set PB7 as output pin*/
	GPIOB->MODER |= (1U<<14);
	GPIOB->MODER &=~ (1U<<15);

	/*Set PB14 as output pin*/
	GPIOB->MODER |= (1U<<28);
	GPIOB->MODER &=~ (1U<<29);

	/*Set PC13 as input pin*/
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	/*run loop*/
	while(1){
		// if button pressed, turn on LED
		if(GPIOC->IDR & BTN_Pin){
			/*set bits for LED pins*/
			GPIOB->BSRR = (G_LED_PIN | B_LED_PIN | R_LED_PIN);
		}
		else{
			/*reset bits for LED pins*/
			GPIOB->BSRR = (G_LED_PIN<<16 | B_LED_PIN<<16 | R_LED_PIN<<16);
		}

	};
}
