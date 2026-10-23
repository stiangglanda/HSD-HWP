#ifndef STATE_B_H
#define STATE_B_H

#include "StateMachine.h"

State_t const State_B = {State_B_Enter, State_B_Process, State_B_Exit};

void State_B_Enter(void) {
	// ToDo: What we need to do in entering
}

State_t const* State_B_Process(void) {
	// ToDO: Check, wheter we want to stay or leave
	// return &State_A;
	
	return &State_B;
}

void State_B_Exit(void) {
	// ToDo: What we need to do in leaving
}

#endif