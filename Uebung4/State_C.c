#ifndef STATE_C_H
#define STATE_C_H

#include "StateMachine.h"

State_t const State_C = {State_C_Enter, State_C_Process, State_C_Exit};

void State_C_Enter(void) {
	// ToDo: What we need to do in entering
}

State_t const* State_C_Process(void) {
	// ToDO: Check, wheter we want to stay or leave
	// return &State_A;
	
	return &State_A;
}

void State_C_Exit(void) {
	// ToDo: What we need to do in leaving
}

#endif