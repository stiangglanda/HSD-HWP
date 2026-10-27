#include "StateMachine.h"
#include "Gpio.h"
#include "EventQueue.h"

static void Enter(void) { 
	Gpio_Set(GPIO_ID_LED4, false);
}
static void Exit(void) {
	Gpio_Set(GPIO_ID_LED4, true);
}

static State_t const * Process(void) {
    Event_t event;
    if (EventQueue_Get(&event) == 0 && event.EventType == 1 && event.X == 0) {
        return &State_A; // User0 gedrückt
    }
    return &State_B;
}

State_t const State_B = { Enter, Process, Exit };