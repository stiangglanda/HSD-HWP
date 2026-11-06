#include "StateMachine.h"
#include "LED.h"
#include "Gpio.h"

int main(void)
{
	/* Anfangsausgang einmalig auf 0 setzen. */
    LED_Off(GPIO_ID_LED3);

    /* Runner ruft Enter nicht für den Startzustand auf! */
    State_A.Enter();
    StateMachine_Run(&State_A);

    return 0;
}
