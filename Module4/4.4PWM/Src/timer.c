#include "timer.h"

void tim5_pwm_init(void){
	//1. Habilitar reloj para TIM5 en el RCC
	RCC->APB1ENR |= (1 << 3);

	//2. Configuration TIM5 base time (1kHz)
	TIM5->PSC = 15; // with PSC = 15. Make 1 tick each 1us. Fcnt = 1 MHz
	TIM5->ARR = 999; //fcycle = 1 kHz with ARR = 999. T = 1ms.

	//3. PWM mode 1 + Preload enabled. (CCMR define the ch as output)
	TIM5->CCMR1 &= ~(7 << 4);
	TIM5->CCMR1 |= (6 << 4) | (1 << 3);

	//4. Enable output pin for channel 1. (CCER open the output drain)
	TIM5->CCER |= (1 << 0);

	//5. Duty cycle inicial (250 = 25%)
	TIM5->CCR1 = 250;

	//5. Start the timer.
	TIM5->CR1 |= (1 << 0);
}

void tim5_set_duty_cycle(uint32_t duty){
	TIM5->CCR1 = duty;
}
