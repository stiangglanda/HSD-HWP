#include <stm32f072xb.h>
#include "Timer.h"
#include "Gpio.h"
#include "StateMachine.h"
#include "Key.h"

//static void MyCallback(int id) {
//	static bool ledState = true;
//	(void)id;
//	Gpio_Set(GPIO_ID_LED4, ledState);
//	ledState = !ledState;
//}

int main() {
	__enable_irq();

	Key_Initialize();

	// Timer_Callback_t myCallbackVar = *MyCallback;
	// Gpio_Initialize(GPIO_ID_LED4, GPIO_MODE_OUTPUT, false);

	// Timer_Initialize(TIMER_ID_TIM6);
	// Timer_Enable(TIMER_ID_TIM6, myCallbackVar, 1000/6/2, TIME_UNIT_MS, true);
	
	State_t const* state = &State_A;
	state->Enter();
	
	StateMachine_Run(state);
}