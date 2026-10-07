//SysTick Code
#include <stdint.h>
#include <stdio.h>

//Systick registers
#define STK_CTRL ((volatile uint32_t*)0xE000E010)
#define STK_LOAD ((volatile uint32_t*)0xE000E014)
#define STK_VAL ((volatile uint32_t*)0xE000E018)

//GPIO register for PA5 (LD2)
#define RCC_AHB1ENR ((volatile uint32_t*) 0x40023830)  //pg 119. EnableRegister for GPIOA.
#define GPIOA_MODER5 ((volatile uint32_t*) 0x40020000) //pg 150. ModerRegister. b_p11&10
#define GPIOA_BSRR ((volatile uint32_t*)0x40020018)    //pg 153. Bit set/reset register

void systick_init(void){
	*STK_LOAD = 15999;                 //1. Load 15999 for 1ms tick at 16MHz
	*STK_VAL = 0;                      //2. Clear current counter value
	*STK_CTRL |= (1 << 0) | (1 << 2);  //3. Enable systick + select processor clock
}

void delay_ms(uint32_t ms) {
	for (uint32_t i = 0; i < ms; i++){
		//Wait until countflag (bit 16) turns 1
		//Reading STK_CTRL automatically clears COUNTFLAG back to 0
		while (((*STK_CTRL) & (1 << 16)) == 0); //each 1 ms I'll leave this while
	}
}

//REMEMBER *macro |= (1 << b_p); Turn on.   *macro &= ~(1 << b_p); Turn off
int main(void){
	*RCC_AHB1ENR |= (1 << 0);       //GPIOA clock enable
	*GPIOA_MODER5 &= ~(3 << (5*2)); //turn off bits 11:10.
	*GPIOA_MODER5 |= (1 << (5*2));  //turn on bit 10. MODER5 become output.

	systick_init (); //Initialize Systick

	while(1){
		*GPIOA_BSRR = (1 << 5);   //PA5 HIGH
		delay_ms(3000);           //Wait 1 second (1000 ms)

		*GPIOA_BSRR = (1 << (16+5));   //PA5 LOW
		delay_ms(3000);           //Wait 1 second (1000 ms)
	}

	return 0;
}
