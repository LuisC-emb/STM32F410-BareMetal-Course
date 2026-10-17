#include "gpio.h"


//Enable the RCC clock for the selected GPIO port
void gpio_clock_enable(GPIO_TypeDef *port) {
	if (port == GPIOA)           RCC->AHB1ENR |= (0x1U << 0);
	else if (port == GPIOB)      RCC->AHB1ENR |= (0x1U << 1);
	else if (port == GPIOC)      RCC->AHB1ENR |= (0x1U << 2);
	else if (port == GPIOH)      RCC->AHB1ENR |= (0x1U << 7);
}


///////////@@Configure a pin as input mode
void gpio_init_input(GPIO_TypeDef *port, uint8_t pin, MY_GPIO_Pupd_t pull_type){
	//1. Enable the clock of port
	gpio_clock_enable(port);

	//2. Configure MODER as 00 (Input mode)
	port->MODER &= ~(0x3U << (pin * 2));
	port->MODER |= (GPIO_MODE_INPUT << (pin * 2));

	//3. Configure PUPDR (None, Pull-up or pull-down)
	port->PUPDR &= ~(0x3U << (pin * 2));
	port->PUPDR |= ((uint32_t)pull_type << (pin*2));
}

///////////@@Configure a pin as output mode
void gpio_init_output (GPIO_TypeDef *port, uint8_t pin, MY_GPIO_Otype_t output_type, MY_GPIO_Pupd_t pull_type){
	//1. Enable the clock of port
	gpio_clock_enable(port);

	//2. Configure MODER as 01 (Output mode)
	port->MODER &= ~(0x3U << (pin * 2));
	port->MODER |= (MY_GPIO_MODE_OUTPUT << (pin * 2));

	//3. Configure OTYPER (Push-Pull / Open-Drain)
	if (output_type == MY_GPIO_OTYPE_OPENDRAIN) {
		port->OTYPER |= (0x1U << pin);
	} else {
		port->OTYPER &= ~(0x1U << pin);
	}

	//4. Configure PUPDR
	port->PUPDR &= ~(0x3U << (pin * 2));
	port->PUPDR |= ((uint32_t)pull_type << (pin * 2));

}
void gpio_a_init_output_pa5(void){
	//1. Check if GPIOA is enabled
	if (RCC->AHB1ENR == (0x1U << 0)){
	}
	else {RCC->AHB1ENR |= (0x1U << 0);
	}

	//1. Output mode to MODER5 = PA5
	GPIOA->MODER &= ~(0x3U << (5 * 2));    	//Clear bits MODER5
	GPIOA->MODER |= (0x1U << (5 * 2));   	//01 for General purpose output mode
}
///////////@@Elements missings (Alternative function, write pin, toggle pin, read pin)
