#include "systick.h"

volatile uint32_t ms_ticks = 0;

void systick_init(void){
	STK->LOAD = 15999;                 //1. Load 15999 for 1ms tick at 16MHz
	STK->VAL = 0;                      //2. Clear current counter value
	STK->CTRL |= (1 << 0)              //Bit 0: ENABLE systick counter
			  | (1 << 1)               //Bit 1: TICKINT (Enable SysTick Interrupt
			  | (1 << 2);              //Bit 2: CLKSOURCE (Processor Clock 16MHz)
}

void SysTick_Handler(void){
	ms_ticks++; //Increments our 1 ms timebase counter
}

uint32_t get_systick_ms(void) {
	return ms_ticks; //Non-blocking! Returns instantly in a few clocks cycle
}
