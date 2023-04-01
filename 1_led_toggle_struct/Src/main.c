
#define PERIPH_BASE 		(0x40000000UL)
#define AHB1PERIPH_OFFSET 	(0x00020000UL)
#define AHB1PERIPH_BASE 	(PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOB_OFFSET		(0x0400U)
#define GPIOB_BASE			(AHB1PERIPH_BASE + GPIOB_OFFSET)

#define RCC_OFFSET 			(0x3800U)
#define RCC_BASE 			(AHB1PERIPH_BASE + RCC_OFFSET)


#define __IO volatile

typedef struct
{
	__IO unsigned int MODER;
	__IO unsigned int dummy[4];
	__IO unsigned int ODR;
} GPIO_TypeDef;

typedef struct
{
	__IO unsigned int dummy[12];
	__IO unsigned int AHB1EN;
} RCC_TypeDef;

//define pointers to structs for clean syntax of register access
#define GPIOB 			((GPIO_TypeDef*) GPIOB_BASE)
#define RCC 			((RCC_TypeDef*) RCC_BASE)


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
	RCC->AHB1EN |= RCC_GPIOBEN;

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
	for(;;){

		/*toggle pin output data on led pins*/
		GPIOB->ODR ^= (G_LED_PIN | B_LED_PIN | R_LED_PIN);

		/* primitive delay before toggling again*/
		for(int i = 0; i < 100000; i++);
	};
}
