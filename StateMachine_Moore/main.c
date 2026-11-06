#include "StateMachine.h"

int main(void)
{
    /* Enter setzt den Startzustand auf 0 Euro. */
    State_A.Enter();
    StateMachine_Run(&State_A);

    return 0;
}
