#include "gpio.h"
#include "adc.h"
#include "systick.h"

static volatile uint16_t val_pa0 = 0; //Variable global para monitoreo, se borran al final y se declaran como locales limpia al final
static volatile uint16_t val_pa1 = 0;
int main(void)
{
	adc_init_dual_regular();
	systick_init();

	uint32_t last_sample_time = get_systick_ms();
	while (1){
		//Non-blocking check: Has 100 ms passed since the last sample?
		if (get_systick_ms() - last_sample_time >= 100){
			last_sample_time = get_systick_ms();
				val_pa0 = adc_read_channel();
				val_pa1 = adc_read_channel();
		}

		//CPU can do other tasks here freely without hanging in a delay loop
	}
	return 0;
}
