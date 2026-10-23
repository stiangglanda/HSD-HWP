#ifndef STATE_A_H
#define STATE_A_H

#include "StateMachine.h"

State_t const State_A = {State_A_Enter, State_A_Process, State_A_Exit};

void State_A_Enter(void) {
	// ToDo: What we need to do in entering
}

State_t const* State_A_Process(void) {
	// ToDO: Check, wheter we want to stay or leave
	// return &State_A;
	
	return &State_B;
}

void State_A_Exit(void) {
	// ToDo: What we need to do in leaving
}

#endif