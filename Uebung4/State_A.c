#include "StateMachine.h"
#include "Gpio.h"
#include "EventQueue.h"

static void Enter(void) { Gpio_Set(GPIO_ID_LED3, false); }
static void Exit(void)  { Gpio_Set(GPIO_ID_LED3, true); }

static State_t const * Process(void) {
    Event_t event;
    if (EventQueue_Get(&event) == 0 && event.EventType == 1 && event.X == 1) {
        return &State_B; // User1 gedrückt
    }
    return &State_A;
}

State_t const State_A = { Enter, Process, Exit };