#include <stdint.h>

extern uint32_t Startup_StackGuardTop;
extern uint32_t Startup_StackGuardBottom;

int main(void) {
    Startup_StackGuardBottom = 0xDEADBEEF;
    Startup_StackGuardTop = 0xDEADDEAD;
    while(1) {

    }
}