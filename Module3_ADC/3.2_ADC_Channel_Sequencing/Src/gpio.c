#include "gpio.h"

/*1.How to turn a bit ON (Set bit): register |= (1 << bit_position);
2.How to turn a bit OFF (Clear bit): register &= ~(1 << bit_position);*/

void gpio_a_init_analog(void){
	//1. Enable peripheral clock for GPIOA
	RCC->AHB1ENR |= (1 << 0);

	//2. Configure PA0 and PA1 as Analog mode

	GPIOA->MODER &= ~((3 << 0) | (3 << 2)); //Clear bits for MODER0 and MODER1
	GPIOA->MODER |= ((3 << 0) | (3 << 2)); //Configure MODER0 and MODER1 as Analog mode


}

