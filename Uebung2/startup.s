StackSize EQU 64
	
    AREA Startup_Code, CODE, READONLY
    EXPORT Reset_Handler
    IMPORT __main

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
		
	SPACE StackSize
__initial_sp
	
    END