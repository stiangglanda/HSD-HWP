#include "StateMachine.h"
#include "LED.h"
#include "Gpio.h"
#include "EventQueue.h"
#include "Button.h"

/* Zustand B: 1 Euro Guthaben. */
State_t const State_B = {State_B_Enter, State_B_Process, State_B_Exit};

void State_B_Enter(void)
{
	
}

struct State_s const *State_B_Process(void)
{
    Event_t event;
    if (EventQueue_Get(&event) != EVENTQUEUE_SUCCESS) {
        return &State_B;
    }

    if (event.X == USER0_PRESSED) {
        /* Zustand B UND zweite Münze erzeugen bei MEALY die Ausgabe. */
        LED_On(GPIO_ID_LED3);
		
		/* Ticket ist bezahlt und unser Guthaben wieder 0 Euro. */
        return &State_A; 
    }
	
	/* Anderes Ereignis bewirkt kein Ticket. */
    LED_Off(GPIO_ID_LED3); 
    return &State_B;
}

void State_B_Exit(void)
{
    /* Ausgang gehört zum gerade erfolgten Übergang. */
}
