#include "StateMachine.h"

void StateMachine_Run(State_t const * state) {
    state->Enter();
    while (1) {
        State_t const * next = state->Process();
        if (next != state) {
            state->Exit();
            next->Enter();
            state = next;
        }
    }
}