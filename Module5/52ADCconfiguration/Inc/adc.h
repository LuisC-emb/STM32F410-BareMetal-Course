#ifndef ADC_H_
#define ADC_H_

#include "stm32f410rb.h"

void adc_init (void);
uint16_t adc_read_single (void);

#endif /* ADC_H_ */
