#include <stdint.h>

extern uint32_t Startup_StackGuardTop;
extern uint32_t Startup_StackGuardBottom;

uint32_t const * Startup_GetStackPointer(void);

int main(void) {
    Startup_StackGuardBottom = 0xDEADBEEF;
    Startup_StackGuardTop = 0xDEADDEAD;
	
		uint32_t const * Stackpointer;
    while(1) {
			Stackpointer = Startup_GetStackPointer();
    }
}