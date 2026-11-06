;*******************************************************************************
;* File Name          : startup_stm32f072xb.s
;* Author             : MCD Application Team
;* Description        : STM32F072x8/STM32F072xB devices vector table for MDK-ARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == Reset_Handler
;*                      - Set the vector table entries with the exceptions ISR address
;*                      - Branches to __main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the CortexM0 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;********************************************************************************
;* @attention
;*
;* Copyright (c) 2016 STMicroelectronics.
;* All rights reserved.
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;*******************************************************************************
;* <<< Use Configuration Wizard in Context Menu >>>

; Beim Debuggen startet unser Controller regulaer (FLASH), resettet System und Hardware.
; Danach laden wir das generierte Binary (axf) ins SRAM und setzen SP/PC via (MDK/sram_debug.ini).

; SRAM-Adressen stehen in MDK/sram.sct und reservieren uns unsere Sektionen.

; sram.sct legt STACK in RW_STACK bei 0x20003800 ab. Unsere Größe ist 0x800.
; Damit liegt __initial_sp bei 0x20004000. 
Stack_Size      EQU     0x00000800

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

                PRESERVE8
                THUMB
					
; sram.sct legt die AREA RESET physisch bei 0x20000000 ab.
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     PendSV_Handler                 ; PendSV Handler
                DCD     SysTick_Handler                ; SysTick Handler

                ; External Interrupts
                DCD     WWDG_IRQHandler                ; Window Watchdog
                DCD     PVD_VDDIO2_IRQHandler          ; PVD through EXTI Line detect
                DCD     RTC_IRQHandler                 ; RTC through EXTI Line
                DCD     FLASH_IRQHandler               ; FLASH
                DCD     RCC_CRS_IRQHandler             ; RCC and CRS
                DCD     EXTI0_1_IRQHandler             ; EXTI Line 0 and 1
                DCD     EXTI2_3_IRQHandler             ; EXTI Line 2 and 3
                DCD     EXTI4_15_IRQHandler            ; EXTI Line 4 to 15
                DCD     TSC_IRQHandler                 ; TS
                DCD     DMA1_Channel1_IRQHandler       ; DMA1 Channel 1
                DCD     DMA1_Channel2_3_IRQHandler     ; DMA1 Channel 2 and Channel 3
                DCD     DMA1_Channel4_5_6_7_IRQHandler ; DMA1 Channel 4, Channel 5, Channel 6 and Channel 7
                DCD     ADC1_COMP_IRQHandler           ; ADC1, COMP1 and COMP2 
                DCD     TIM1_BRK_UP_TRG_COM_IRQHandler ; TIM1 Break, Update, Trigger and Commutation
                DCD     TIM1_CC_IRQHandler             ; TIM1 Capture Compare
                DCD     TIM2_IRQHandler                ; TIM2
                DCD     TIM3_IRQHandler                ; TIM3
                DCD     TIM6_DAC_IRQHandler            ; TIM6 and DAC
                DCD     TIM7_IRQHandler                ; TIM7
                DCD     TIM14_IRQHandler               ; TIM14
                DCD     TIM15_IRQHandler               ; TIM15
                DCD     TIM16_IRQHandler               ; TIM16
                DCD     TIM17_IRQHandler               ; TIM17
                DCD     I2C1_IRQHandler                ; I2C1
                DCD     I2C2_IRQHandler                ; I2C2
                DCD     SPI1_IRQHandler                ; SPI1
                DCD     SPI2_IRQHandler                ; SPI2
                DCD     USART1_IRQHandler              ; USART1
                DCD     USART2_IRQHandler              ; USART2
                DCD     USART3_4_IRQHandler            ; USART3 & USART4
                DCD     CEC_CAN_IRQHandler             ; CEC and CAN
                DCD     USB_IRQHandler                 ; USB

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; sram.sct wählt startup_stm32f072xb.o (.text, +FIRST).

Reset_Handler   PROC
                EXPORT  Reset_Handler                 [WEAK]
                IMPORT  __main
                IMPORT  ram_system_init

                ; [V2] Dieses kleine Beispiel verwendet keine Interrupts.
                ; Maskierbare Interrupts bleiben deshalb gesperrt.
                CPSID   I
                ; CONTROL=0 wählt MSP im bereits zurückgesetzten Thread-Kontext.
                MOVS    R0, #0
                MSR     CONTROL, R0
                ISB
                LDR     R0, =__initial_sp
                MSR     MSP, R0

                LDR     R0, =ram_system_init
                BLX     R0

                ; Beim Wechsel in __main initialisiert die C-Runtime unsere Regionen ZI/.bss.
                ; RW-Initialwerte lädt die Debug-INI direkt ins SRAM.
                LDR     R0, =__main
                BX      R0
                ENDP

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
					
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
					
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
					
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
					
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WWDG_IRQHandler                [WEAK]
                EXPORT  PVD_VDDIO2_IRQHandler          [WEAK]
                EXPORT  RTC_IRQHandler                 [WEAK]
                EXPORT  FLASH_IRQHandler               [WEAK]
                EXPORT  RCC_CRS_IRQHandler             [WEAK]
                EXPORT  EXTI0_1_IRQHandler             [WEAK]
                EXPORT  EXTI2_3_IRQHandler             [WEAK]
                EXPORT  EXTI4_15_IRQHandler            [WEAK]
                EXPORT  TSC_IRQHandler                 [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler       [WEAK]
                EXPORT  DMA1_Channel2_3_IRQHandler     [WEAK]
                EXPORT  DMA1_Channel4_5_6_7_IRQHandler [WEAK]
                EXPORT  ADC1_COMP_IRQHandler           [WEAK]
                EXPORT  TIM1_BRK_UP_TRG_COM_IRQHandler [WEAK]
                EXPORT  TIM1_CC_IRQHandler             [WEAK]
                EXPORT  TIM2_IRQHandler                [WEAK]
                EXPORT  TIM3_IRQHandler                [WEAK]
                EXPORT  TIM6_DAC_IRQHandler            [WEAK]
                EXPORT  TIM7_IRQHandler                [WEAK]
                EXPORT  TIM14_IRQHandler               [WEAK]
                EXPORT  TIM15_IRQHandler               [WEAK]
                EXPORT  TIM16_IRQHandler               [WEAK]
                EXPORT  TIM17_IRQHandler               [WEAK]
                EXPORT  I2C1_IRQHandler                [WEAK]
                EXPORT  I2C2_IRQHandler                [WEAK]
                EXPORT  SPI1_IRQHandler                [WEAK]
                EXPORT  SPI2_IRQHandler                [WEAK]
                EXPORT  USART1_IRQHandler              [WEAK]
                EXPORT  USART2_IRQHandler              [WEAK]
                EXPORT  USART3_4_IRQHandler            [WEAK]
                EXPORT  CEC_CAN_IRQHandler             [WEAK]
                EXPORT  USB_IRQHandler                 [WEAK]


WWDG_IRQHandler
PVD_VDDIO2_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_CRS_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
TSC_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_3_IRQHandler
DMA1_Channel4_5_6_7_IRQHandler
ADC1_COMP_IRQHandler
TIM1_BRK_UP_TRG_COM_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM6_DAC_IRQHandler
TIM7_IRQHandler
TIM14_IRQHandler
TIM15_IRQHandler
TIM16_IRQHandler
TIM17_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_4_IRQHandler
CEC_CAN_IRQHandler
USB_IRQHandler

                B       .

                ENDP

                ALIGN


; __user_setup_stackheap meldet der C-Library einen leeren Heap.
; Der MSP ist bereits gesetzt. R0=Heap-Anfang=0, R2=Heap-Ende=0.
__user_setup_stackheap PROC
                EXPORT  __user_setup_stackheap
                MOVS    R0, #0
                MOVS    R2, #0
                BX      LR
                ENDP

; Die normale C-Library hat einen Exit-Pfad nach main(). Dieser 
; Ersatz vermeidet dort einen Semihosting-Aufruf an den Debugger.
                IMPORT  __use_no_semihosting
_sys_exit       PROC
                EXPORT  _sys_exit
                B       .
                ENDP

                ALIGN
                END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
