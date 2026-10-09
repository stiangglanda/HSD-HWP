StackSize EQU 64
	
    AREA Startup_Code, CODE, READONLY
    EXPORT Reset_Handler
    IMPORT __main

Reset_Handler
	B
    

    AREA Startup_Rom, DATA, READONLY
    EXPORT __Vectors

__Vectors
    DCD __initial_sp
    DCD Reset_Handler
		
	AREA Startup_Ram, DATA, READWRITE, NOINIT
		
	SPACE StackSize
__initial_sp
	
    END