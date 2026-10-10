#include <stdint.h>

#define STACK_GUARD 0xDEADDEAD

extern uint32_t Startup_StackGuardTop;
extern uint32_t Startup_StackGuardBottom;
static int32_t Main_StackStatus;

uint32_t const * Startup_GetStackPointer(void);

// Determines the status of the stack.
// returns
// -1 if a stack overflow has been detected. 
// -2 if a stack underflow has been detected. 
// A non-negative value representing the number of unused bytes on the stack. 
// If more than INT32_MAX bytes are unused, INT32_MAX is returned. 
int32_t Main_GetStackStatus(void) {
  if (Startup_StackGuardTop != STACK_GUARD) {
    return -1;
  }
  if (Startup_StackGuardBottom != STACK_GUARD) {
    return -2;
  }

  uint32_t const * const start = &Startup_StackGuardTop + 1;
  uint32_t const * i = start;
  while (i < &Startup_StackGuardBottom && *i == 0) {
    i++;
  }

  uintptr_t unused = (uintptr_t)i - (uintptr_t)start;
  if (unused > INT32_MAX) {
    return INT32_MAX;
  }
  return (int32_t)unused;
}

int main(void) {
    Startup_StackGuardBottom = STACK_GUARD;
    Startup_StackGuardTop = STACK_GUARD;
	
		uint32_t const * stackPointer;
		stackPointer = Startup_GetStackPointer();
    Main_StackStatus = Main_GetStackStatus();

    while(1) {
			Main_StackStatus = Main_GetStackStatus();
    }
}