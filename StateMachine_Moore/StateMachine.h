#ifndef STATEMACHINE_H
#define STATEMACHINE_H

typedef void (*StateTransitionFunction_t)(void);
typedef struct State_s const * (*StateFunction_t)(void);

typedef struct State_s {
	StateTransitionFunction_t Enter;
	StateFunction_t Process;
	StateTransitionFunction_t Exit;
} State_t;

extern State_t const State_A;
extern State_t const State_B;
extern State_t const State_C;

void State_A_Enter(void);
struct State_s const * State_A_Process(void);
void State_A_Exit(void);

void State_B_Enter(void);
struct State_s const * State_B_Process(void);
void State_B_Exit(void);

void State_C_Enter(void);
struct State_s const *State_C_Process(void);
void State_C_Exit(void);

void StateMachine_Run(State_t const * state);

#endif
