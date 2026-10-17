#include "gpio.h"

void gpio_pa0_init_pwm(void){
	//1. Habilitar reloj para GPIOA en el RCC
	 RCC->AHB1ENR |= (1 << 0);

	//2. Modo funcion alternativa en PA0 (10 en bits 1:0)
	 GPIOA->MODER &= ~(3 << 0); //Clear bits 1:0
	 GPIOA->MODER |= (2 << 0); //Write 10 in bits 1:0

	//3. Seleccionar AF2 (TIM5_Ch1) en AFRL (alternate function low register) para PA0 (0010 en bits 3:0)
	 GPIOA->AFRL &= ~(15 << 0); //Clear bits 3:0
	 GPIOA->AFRL |= (2 << 0); //Write 0010 bits 3:0

}
