#include "State_C.h"
#include "LED.h"
#include "Gpio.h"
#include "EventQueue.h"
#include "Button.h"

/* Zustand C: Ticket bezahlt, Restguthaben 0 Euro, Ausgang 1. */
State_t const State_C = {State_C_Enter, State_C_Process, State_C_Exit};

void State_C_Enter(void)
{
    /* Bei Moore wird nun bei Transition in State C das Ticket ausgegeben. */
    LED_On(GPIO_ID_LED3);
}

struct State_s const *State_C_Process(void)
{
    Event_t event;
    if (EventQueue_Get(&event) == EVENTQUEUE_SUCCESS) {
		if (event.X == USER0_PRESSED) {
			/* Neue Münze zählt für das nächste Ticket. */
			return &State_B; 
		}
    }
	
	/* Wir verlassen den Ausgabezustand. */
    return &State_A; 
}

void State_C_Exit(void)
{
	/* Ticketausgabe wird beendet und wir kehren in State A oder B zurück. */
    LED_Off(GPIO_ID_LED3);
}
