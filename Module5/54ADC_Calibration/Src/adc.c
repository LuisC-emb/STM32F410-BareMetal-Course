#include "adc.h"


/*1.How to turn a bit ON (Set bit): register |= (1 << bit_position);
2.How to turn a bit OFF (Clear bit): register &= ~(1 << bit_position);*/

void adc_init (void){

	//1. Enable peripheral clock for ADC1 (1 on bit 8)
	RCC->APB2ENR |= (1 << 8);

	//2. Set clock prescaler ADC_CCR (common control register)
	ADC_C->CCR &= ~(3 << 16); //PCLK2 (16MHz) divided by 2 = 8MHz

	//3.Configure ADC resolution, alignment & Mode
	ADC->CR1 &= ~(3 << 24); //Resolution 12 bits (minimum 15 ADCCLK cylcles)with 00 on bit 25:24
	ADC->CR2 &= ~(1 << 11); //Right alignment, 0 on bit 11
	ADC->CR2 &= ~(1 << 1); //Single conversion mode (1 conversion and stops)
	ADC->SQR1 &= ~(15 << 20); //Channel sequence Lenght, 1 conversion with 0000 on 23:20
	ADC->SQR3 &= ~(31 << 0); //Assign channel 0 to sequence 1

	//4. Configure Sampling time (ADC_SMPR2)
	ADC->SMPR2 &= ~(7 << 0); //Sample time set on 3 cycle on PA0 because bit 0 is for SMP0

	//5. Enable the ADC peripheral
	ADC->CR2 |= (1 << 0); //ADC converter ON
}

uint16_t adc_read_single_raw (void){
	//1. Trigger and poll stauts:
	ADC->CR2 |= (1 << 30); //Start conversion of regular channels

	//2. Poll EOC (end of conversion) flag until set
	while (!(ADC->SR & (1 << 1))){
		//wait here until conversion completes. E0C = 1
	}
	return (uint16_t)(ADC->DR);
}

uint32_t adc_read_single_millivolts (uint16_t raw_value, uint32_t vdd_mv){
	//Preven reading beyond 12-bit maximum
	if (raw_value > 4095U) {
	        raw_value = 4095U;
	    }
	// Cast raw_value to uint32_t to avoid integer overflow during multiplication!
	// Max calculation: 4095 * 3300 = 13,513,500 (Fits comfortably inside uint32_t)
	return ((uint32_t)raw_value * vdd_mv) / 4095;
}
