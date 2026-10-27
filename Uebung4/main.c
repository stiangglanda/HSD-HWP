#include <stm32f072xb.h>
#include "Timer.h"
#include "Gpio.h"
#include "StateMachine.h"
#include "Key.h"
#include "EventQueue.h"

int main() {
	__enable_irq();

	Gpio_Initialize(GPIO_ID_LED3, GPIO_MODE_OUTPUT, true);
	Gpio_Initialize(GPIO_ID_LED4, GPIO_MODE_OUTPUT, true);

  EventQueue_Initialize();
  Key_Initialize();

  StateMachine_Run(&State_A);
}