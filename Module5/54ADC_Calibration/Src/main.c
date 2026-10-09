#include "gpio.h"
#include "adc.h"
#include "systick.h"

static volatile uint16_t raw = 0; //Variable global para monitoreo, se borran al final y se declaran como locales limpia al final
static volatile uint32_t mv = 0; //Variable global para monitorreo

int main(void)
{
	gpio_a_init();
	adc_init();
	systick_init();

	uint32_t last_sample_time = get_systick_ms();
	while (1){
		//Non-blocking check: Has 100 ms passed since the last sample?
		if (get_systick_ms() - last_sample_time >= 100){
			last_sample_time = get_systick_ms();
			//Raw value of ADC->DR
			raw = adc_read_single_raw();

			//Scale to milivolts using 3300 mV (3.3V) as reference
			mv = adc_read_single_millivolts(raw, 3300);

		}

		//CPU can do other tasks here freely without hanging in a delay loop
	}
	return 0;
}
