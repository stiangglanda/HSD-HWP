#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef void (*StateTransitionFunction_t)(void);
typedef struct State_s const * (*StateFunction_t)(void);

typedef struct State_s {
    StateTransitionFunction_t Enter;
    StateFunction_t Process;
    StateTransitionFunction_t Exit;
} State_t;

void StateMachine_Run(State_t const * state);

extern State_t const State_A;
extern State_t const State_B;

#endif