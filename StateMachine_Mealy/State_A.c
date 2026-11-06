#include "StateMachine.h"
#include "LED.h"
#include "Gpio.h"
#include "EventQueue.h"
#include "Button.h"

/* Zustand A: 0 Euro Guthaben. */
State_t const State_A = {State_A_Enter, State_A_Process, State_A_Exit};

void State_A_Enter(void)
{
    /* Der Ausgang wird bei Mealy in Process bestimmt. */
}

struct State_s const *State_A_Process(void)
{
	/* In Zustand A entsteht kein Ticket, wir setzen aktiv LED3 = Off. */
	LED_Off(GPIO_ID_LED3); 

    Event_t event;
    if (EventQueue_Get(&event) != EVENTQUEUE_SUCCESS) {
		/* Ohne Ereignis wird nichts verändert. */
        return &State_A; 
    }

    if (event.X == USER0_PRESSED) {
		/* Unsere erste Münze setzt das Guthaben auf 1 Euro. */
        return &State_B; 
    }
    return &State_A;
}

void State_A_Exit(void)
{
	
}
