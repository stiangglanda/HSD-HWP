StackSize EQU 1024
	
    AREA Startup_Code, CODE, READONLY
    EXPORT Reset_Handler
    IMPORT __main
	EXPORT Startup_GetStackPointer

Startup_GetStackPointer
	MOV R0, SP
	BX LR
	
Reset_Handler
    LDR R0, = __main
    BX R0
    

    AREA Startup_Rom, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD __initial_sp
    DCD Reset_Handler
		
	AREA Startup_Ram, DATA, READWRITE, NOINIT
	EXPORT __initial_sp
	EXPORT Startup_StackGuardTop
	EXPORT Startup_StackGuardBottom
	
Startup_StackGuardTop
	SPACE 4
	
	SPACE StackSize
__initial_sp

	SPACE 4
Startup_StackGuardBottom
	
    END