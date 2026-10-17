#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f410rb.h"

void systick_init(void);

uint32_t get_systick_ms(void);

#endif /* SYSTICK_H_ */
