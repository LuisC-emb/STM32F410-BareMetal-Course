#ifndef TIM_H_
#define TIM_H_

#include "stm32f410rb.h"

void tim5_pwm_init(void);
void tim5_set_duty_cycle (uint32_t duty);

#endif //**TIM_H_**
