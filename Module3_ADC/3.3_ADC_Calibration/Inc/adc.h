#ifndef ADC_H_
#define ADC_H_

#include "stm32f410rb.h"

void adc_init (void);
uint16_t adc_read_single_raw (void);
uint32_t adc_read_single_millivolts (uint16_t raw_value, uint32_t vdd_mv);

#endif /* ADC_H_ */
