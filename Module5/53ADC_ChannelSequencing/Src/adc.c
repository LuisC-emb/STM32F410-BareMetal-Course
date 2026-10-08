#include "adc.h"
#include "gpio.h"


/*1.How to turn a bit ON (Set bit): register |= (1 << bit_position);
2.How to turn a bit OFF (Clear bit): register &= ~(1 << bit_position);*/

void adc_init_dual_regular (void){
	gpio_a_init_analog();

	//1. Enable peripheral clock for ADC1 (1 on bit 8)
	RCC->APB2ENR |= (1 << 8);

	//2. Set clock prescaler ADC_CCR (common control register)
	ADC_C->CCR &= ~(3 << 16);                 //PCLK2 (16MHz) divided by 2 = 8MHz

	//3. Configure ADC resolution and alignment
	ADC->CR1 &= ~(3 << 24);                   //Resolution 12 bits. Total ADCCLK cycles are defined by this and SMPR2
	ADC->CR2 &= ~(1 << 11);                   //Right alignment, 0 on bit 11
	ADC->CR2 |= (1 << 10);                    // EOCS = 1

	//4.Configure scan mode and discontinuous mode
	ADC->CR1 |= (1 << 8);                     //SCAN = 1
	ADC->CR1 |= (1 << 11);                    //DISCEN = 1 (1 channel per trigger)
	ADC->CR1 &= ~(7 << 13);                  // DISCNUM = 000 (1 channel per trigger event)

	//5. Configure sequence lenght. L = 1 (2 conversion total)
	ADC->SQR1 &= ~(15 << 20);                 //Clear L register
	ADC->SQR1 |= (1 << 20);                   //L = 1 -> 2 channels in sequence

	//6. Assign channels to slots
	ADC->SQR3 &= ~(1023 << 0);                //Clear SQ1 and SQ2
	ADC->SQR3 |= (0 << 0);                    //SQ1 = Channel 0 (PA0)
	ADC->SQR3 |= (1 << 5);                    //SQ2 = Channel 1 (PA1)

	//7. Configure Sampling time for PA0 and PA1
	ADC->SMPR2 &= ~(7 << 0);                  //Sample time set on 3 cycle on PA0
	ADC->SMPR2 &= ~(7 << 3);                  //Sample time set on 3 cycle on PA1

	//8. Enable the ADC peripheral
	ADC->CR2 |= (1 << 0);                      //ADC converter ON -> ADON = 1

	//NOTE: The order of the steps 2-7 doesn't matter when ADON = 0 (step 8)
}

uint16_t adc_read_channel (void){
	//1. Trigger and poll stauts:
	ADC->CR2 |= (1 << 30); //Start conversion of regular channels

	//2. Poll EOC (end of conversion) flag until set
	while (!(ADC->SR & (1 << 1))){

	}
	return (uint16_t)(ADC->DR);
}
