#include "StateMachine.h"

void StateMachine_Run(Size_t const * state) {
	while(1) {
		State_t const* newState = state->Process();
		
		if(newState!= state) {
			state->Exit();
			newState->Enter();
			state = newState;
		}
	}
}