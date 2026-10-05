;******************************************************************************
		AREA Startup_Ram, DATA, READWRITE, NOINIT
;******************************************************************************

Stack_Size      EQU     64

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

;******************************************************************************
        AREA    Startup_Code, CODE, READONLY
;******************************************************************************
        THUMB
        EXPORT  Reset_Handler

Reset_Handler   PROC            
				MOVS	R0, #1
				MOVS	R1, #2
				MOVS	R2, #3
Loop
				PUSH 	{ R0-R2 }
				POP		{ R2 }
				POP		{ R1 }
				POP		{ R0 }
				B       Loop
                ENDP

;******************************************************************************
        AREA    Startup_Rom, DATA, READONLY
;******************************************************************************
        EXPORT  __Vectors

__Vectors       DCD     __initial_sp        ; initial SP
                DCD     Reset_Handler       ; Reset-Vektor

;******************************************************************************
        END
;******************************************************************************