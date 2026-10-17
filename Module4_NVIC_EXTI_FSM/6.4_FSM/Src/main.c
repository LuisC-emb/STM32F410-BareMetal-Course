#include "stm32f410rb.h"
#include "gpio.h"
#include "exti.h"

//1. Declare the extern volatile flag managed by exti.c ISR
extern volatile uint8_t button_pressed_flag;

//2. Define our application states using an enum
typedef enum {
	STATE_IDLE = 0,
	STATE_TOGGLE_LED,
	STATE_WAIT_RELEASE
} SystemState_t;

int main(void){
	//3.. Initialize Hardware Drivers Once
	gpio_a_init_output_pa5(); //Initialize onboard LED on PA5
	exti0_pa0_init(); //Button interrupt

	 //Set initial state
	volatile SystemState_t current_state = STATE_IDLE;


	while (1){
		//4. Background application FSM Loop
		switch (current_state){
			case STATE_IDLE:
				//CPU waits here efficiently. When the user presses the button, the hardware runs the ISR, which sets button_pressed_flag = 1.
				if (button_pressed_flag == 1){
					button_pressed_flag = 0; //Clear software flag
					current_state = STATE_TOGGLE_LED;
				}
				break;

			case STATE_TOGGLE_LED:
				//Do your application task here (e.g., toggle LED or change mode)
				GPIOA->ODR ^= (0x1U << 5);

				//Move to the next state or back to idle
				current_state = STATE_IDLE;
				break;
			case STATE_WAIT_RELEASE:

				if ((GPIOA->IDR & (0x1U << 0)) == 0){
					current_state = STATE_IDLE;
				}
				break;
			default:
				//Safety catch for unexpected states
				current_state = STATE_IDLE;
				break;
			}

		}


	return 0;
	}
