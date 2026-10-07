//Here I will to turn on the GPIOA Pin 5 (moder 5)
//Librarys
#include <stdio.h>
#include <stdint.h>

//Macros section
#define RCC_AHB1ENR ((volatile uint32_t*)0x40023830)
#define GPIOA_MODER5 ((volatile uint32_t*)0x40020000)
#define GPIOA_ODR5 ((volatile uint32_t*)0x40020014) //ODR = Output data register

int main(){
*RCC_AHB1ENR |= (1 << 0); //Turn on RCC for GPIOA

*GPIOA_MODER5 &= ~(3 << (5*2)); //set as 00 the pair b_p11 and b_p10
*GPIOA_MODER5 |= (1 << 10); //pg.150 turn on b_p10, pin PA5 enabled as a digital output switch
*GPIOA_ODR5 |= (1 << 5); //Send 3.3V to PA5

//Infinite loop
while (1){
}

return 0;
} 
