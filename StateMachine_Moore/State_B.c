#include "StateMachine.h"
#include "LED.h"
#include "Gpio.h"
#include "EventQueue.h"
#include "Button.h"

/* Zustand B: 1 Euro Guthaben, Ausgang 0. */
State_t const State_B = {State_B_Enter, State_B_Process, State_B_Exit};

void State_B_Enter(void)
{
	/* Auch in State B erfolgt keine Ausgabe. Wäre nicht notwendig. */
    LED_Off(GPIO_ID_LED3);
}

struct State_s const *State_B_Process(void)
{
    Event_t event;
    if (EventQueue_Get(&event) == EVENTQUEUE_SUCCESS) {
        if (event.X == USER0_PRESSED) {
            /* Zweite Münze wählt den Ausgabezustand (State C). */
            return &State_C;
        }
    }
    return &State_B;
}

void State_B_Exit(void)
{
	
}
