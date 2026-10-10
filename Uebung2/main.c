#include <stdint.h>

#define STACK_GUARD 0xDEADDEAD

extern uint32_t Startup_StackGuardTop;
extern uint32_t Startup_StackGuardBottom;
static int32_t Main_StackStatus;
static uint32_t Main_Result;

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

// Returns the n-th triangular number. 
// n: The triangular number to return.
// returns: 0 if n 0 is zero, n + Main_TriangularNumber(n 1) otherwise.
static uint32_t Main_TriangularNumber(uint32_t n) {
  if (n == 0) {
    return 0;
  }
  return n + Main_TriangularNumber(n - 1);
}

int main(void) {
    Startup_StackGuardBottom = STACK_GUARD;
    Startup_StackGuardTop = STACK_GUARD;
	
		for (uint32_t n = 0; n <= 9; n++) {
      Main_Result = Main_TriangularNumber(n);
      Main_StackStatus = Main_GetStackStatus();
    }

    while(1) {
    }
}