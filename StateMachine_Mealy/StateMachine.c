#include "StateMachine.h"
#include <stddef.h>
#include <stdbool.h>

void StateMachine_Run(State_t const * state){
	if (state != NULL) {
		while (true) {
			State_t const* newState = state->Process();
			
			if (newState != state) {
				state->Exit();
				newState->Enter();
				state = newState;
			}
		}
	}
}
