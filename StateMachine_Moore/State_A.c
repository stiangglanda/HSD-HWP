#include "StateMachine.h"
#include "LED.h"
#include "Gpio.h"
#include "EventQueue.h"
#include "Button.h"

/* Zustand A: 0 Euro Guthaben, Ausgang 0. */
State_t const State_A = {State_A_Enter, State_A_Process, State_A_Exit};

void State_A_Enter(void)
{
	/* Ausgang ist diesem Zustand zugeordnet. Wäre nicht notwendig. */
    LED_Off(GPIO_ID_LED3); 
}

struct State_s const *State_A_Process(void)
{
    Event_t event;
    if (EventQueue_Get(&event) == EVENTQUEUE_SUCCESS) {
        if (event.X == USER0_PRESSED) {
			/* Erste Münze setzt uns in den Zustand 1 Euro Guthaben (State B). */
            return &State_B; 
        }
    }
    return &State_A;
}

void State_A_Exit(void)
{
	
}
