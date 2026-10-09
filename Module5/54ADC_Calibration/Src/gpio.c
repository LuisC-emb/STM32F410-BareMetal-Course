#include "gpio.h"

/*1.How to turn a bit ON (Set bit): register |= (1 << bit_position);
2.How to turn a bit OFF (Clear bit): register &= ~(1 << bit_position);*/

void gpio_a_init(void){
	//1. Enable peripheral clock for GPIOA
	RCC->AHB1ENR |= (1 << 0);

	//2. Configure PA0 as Analog mode

	GPIOA->MODER &= ~(3 << 0); //Clear bits for MODER0
	GPIOA->MODER |= (3 << 0); //Configure MODER0 as Analog mode
}
