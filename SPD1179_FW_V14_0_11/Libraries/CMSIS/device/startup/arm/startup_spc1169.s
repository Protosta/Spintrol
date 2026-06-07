;/**************************************************************************//**
; * @file     startup_ARMCM4.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM4 Device Series
; * @version  V1.08
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT1_IRQHandler           ;  0 Watchdog 1 IRQHandler
                DCD     MEM_IRQHandler            ;  1 Memory IRQHandler
                DCD     EPWRTZ0_IRQHandler        ;  2 ePower Tripzone 0 IRQHandler
                DCD     EPWRTZ1_IRQHandler        ;  3 ePower Tripzone 1 IRQHandler
                DCD     GPIO_LEVEL_IRQHandler     ;  4 GPIO Level IRQHandler
                DCD     GPIO_EDGE_IRQHandler      ;  5 GPIO Edge IRQHandler
                DCD     UART0_IRQHandler          ;  6 UART0 IRQHandler
                DCD     SPI0_IRQHandler           ;  7 SPI0 IRQHandler
                DCD     UART1_IRQHandler          ;  8 UART1 IRQHandler
                DCD     SPI1_IRQHandler           ;  9 SPI1 IRQHandler
                DCD     CANTRG0_IRQHandler        ; 10 CAN Transfer Group 0 IRQHandler
                DCD     CANTRG1_IRQHandler        ; 11 CAN Transfer Group 1 IRQHandler
                DCD     CANTRG2_IRQHandler        ; 12 CAN Transfer Group 2 IRQHandler
                DCD     CANTRG3_IRQHandler        ; 13 CAN Transfer Group 3 IRQHandler
                DCD     CANTRG4_IRQHandler        ; 14 CAN Transfer Group 4 IRQHandler
                DCD     CANTRG5_IRQHandler        ; 15 CAN Transfer Group 5 IRQHandler
                DCD     CANTRG6_IRQHandler        ; 16 CAN Transfer Group 6 IRQHandler
                DCD     CANTRG7_IRQHandler        ; 17 CAN Transfer Group 7 IRQHandler
                DCD     CANMISC_IRQHandler        ; 18 CAN Miscellaneous IRQHandler
                DCD     I2C_IRQHandler            ; 19 I2C IRQHandler
                DCD     ADCCH0_IRQHandler         ; 20 ADC Channel  0 EOC IRQHandler
                DCD     ADCCH1_IRQHandler         ; 21 ADC Channel  1 EOC IRQHandler
                DCD     ADCCH2_IRQHandler         ; 22 ADC Channel  2 EOC IRQHandler
                DCD     ADCCH3_IRQHandler         ; 23 ADC Channel  3 EOC IRQHandler
                DCD     ADCCH4_IRQHandler         ; 24 ADC Channel  4 EOC IRQHandler
                DCD     ADCCH5_IRQHandler         ; 25 ADC Channel  5 EOC IRQHandler
                DCD     ADCCH6_IRQHandler         ; 26 ADC Channel  6 EOC IRQHandler
                DCD     ADCCH7_IRQHandler         ; 27 ADC Channel  7 EOC IRQHandler
                DCD     ADCCH8_IRQHandler         ; 28 ADC Channel  8 EOC IRQHandler
                DCD     ADCCH9_IRQHandler         ; 29 ADC Channel  9 EOC IRQHandler
                DCD     ADCCH10_IRQHandler        ; 30 ADC Channel 10 EOC IRQHandler
                DCD     ADCCH11_IRQHandler        ; 31 ADC Channel 11 EOC IRQHandler
                DCD     ADCCH12_IRQHandler        ; 32 ADC Channel 12 EOC IRQHandler
                DCD     ADCCH13_IRQHandler        ; 33 ADC Channel 13 EOC IRQHandler
                DCD     ADCCH14_IRQHandler        ; 34 ADC Channel 14 EOC IRQHandler
                DCD     ADCCH15_IRQHandler        ; 35 ADC Channel 15 EOC IRQHandler
                DCD     ADCPPU0_IRQHandler        ; 36 ADC PPU0 IRQHandler
                DCD     ADCPPU1_IRQHandler        ; 37 ADC PPU1 IRQHandler
                DCD     ADCPPU2_IRQHandler        ; 38 ADC PPU2 IRQHandler
                DCD     PHCOMP_IRQHandler         ; 39 PHCOMP IRQHandler
                DCD     PWM0_IRQHandler           ; 40 PWM0 IRQHandler
                DCD     PWM1_IRQHandler           ; 41 PWM1 IRQHandler
                DCD     PWM2_IRQHandler           ; 42 PWM2 IRQHandler
                DCD     PWM3_IRQHandler           ; 43 PWM3 IRQHandler
                DCD     PWM0TZ_IRQHandler         ; 44 PWM0 Trip-Zone IRQHandler
                DCD     PWM1TZ_IRQHandler         ; 45 PWM1 Trip-Zone IRQHandler
                DCD     PWM2TZ_IRQHandler         ; 46 PWM2 Trip-Zone IRQHandler
                DCD     PWM3TZ_IRQHandler         ; 47 PWM3 Trip-Zone IRQHandler
                DCD     ECAP_IRQHandler           ; 48 ECAP IRQHandler
                DCD     DMAC_IRQHandler           ; 49 DMAC IRQHandler
                DCD     TIMER0_IRQHandler         ; 50 Timer0 IRQHandler
                DCD     TIMER1_IRQHandler         ; 51 Timer1 IRQHandler
                DCD     TIMER2_IRQHandler         ; 52 Timer2 IRQHandler
                DCD     CRC_IRQHandler            ; 53 CRC IRQHandler

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                ; Remap vector table
                LDR     R0, =__Vectors
                LDR     R1, =0xE000ED08 ;*VTOR register
                STR     R0,[R1]

                ;* C routines are likely to be called. Setup the stack now
                LDR     SP,=__initial_sp

                LDR     R0, =SystemInit
                BLX     R0

                ;* C routines are likely to be called. Setup the stack now
                LDR     SP,=__initial_sp

                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT1_IRQHandler              [WEAK]
                EXPORT  MEM_IRQHandler               [WEAK]
                EXPORT  EPWRTZ0_IRQHandler           [WEAK]
                EXPORT  EPWRTZ1_IRQHandler           [WEAK]
                EXPORT  GPIO_LEVEL_IRQHandler        [WEAK]
                EXPORT  GPIO_EDGE_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler             [WEAK]
                EXPORT  SPI0_IRQHandler              [WEAK]
                EXPORT  UART1_IRQHandler             [WEAK]
                EXPORT  SPI1_IRQHandler              [WEAK]
                EXPORT  CANTRG0_IRQHandler           [WEAK]
                EXPORT  CANTRG1_IRQHandler           [WEAK]
                EXPORT  CANTRG2_IRQHandler           [WEAK]
                EXPORT  CANTRG3_IRQHandler           [WEAK]
                EXPORT  CANTRG4_IRQHandler           [WEAK]
                EXPORT  CANTRG5_IRQHandler           [WEAK]
                EXPORT  CANTRG6_IRQHandler           [WEAK]
                EXPORT  CANTRG7_IRQHandler           [WEAK]
                EXPORT  CANMISC_IRQHandler           [WEAK]
                EXPORT  I2C_IRQHandler               [WEAK]
                EXPORT  ADCCH0_IRQHandler            [WEAK]
                EXPORT  ADCCH1_IRQHandler            [WEAK]
                EXPORT  ADCCH2_IRQHandler            [WEAK]
                EXPORT  ADCCH3_IRQHandler            [WEAK]
                EXPORT  ADCCH4_IRQHandler            [WEAK]
                EXPORT  ADCCH5_IRQHandler            [WEAK]
                EXPORT  ADCCH6_IRQHandler            [WEAK]
                EXPORT  ADCCH7_IRQHandler            [WEAK]
                EXPORT  ADCCH8_IRQHandler            [WEAK]
                EXPORT  ADCCH9_IRQHandler            [WEAK]
                EXPORT  ADCCH10_IRQHandler           [WEAK]
                EXPORT  ADCCH11_IRQHandler           [WEAK]
                EXPORT  ADCCH12_IRQHandler           [WEAK]
                EXPORT  ADCCH13_IRQHandler           [WEAK]
                EXPORT  ADCCH14_IRQHandler           [WEAK]
                EXPORT  ADCCH15_IRQHandler           [WEAK]
                EXPORT  ADCPPU0_IRQHandler           [WEAK]
                EXPORT  ADCPPU1_IRQHandler           [WEAK]
                EXPORT  ADCPPU2_IRQHandler           [WEAK]
                EXPORT  PHCOMP_IRQHandler            [WEAK]
                EXPORT  PWM0_IRQHandler              [WEAK]
                EXPORT  PWM1_IRQHandler              [WEAK]
                EXPORT  PWM2_IRQHandler              [WEAK]
                EXPORT  PWM3_IRQHandler              [WEAK]
                EXPORT  PWM0TZ_IRQHandler            [WEAK]
                EXPORT  PWM1TZ_IRQHandler            [WEAK]
                EXPORT  PWM2TZ_IRQHandler            [WEAK]
                EXPORT  PWM3TZ_IRQHandler            [WEAK]
                EXPORT  ECAP_IRQHandler              [WEAK]
                EXPORT  DMAC_IRQHandler              [WEAK]
                EXPORT  TIMER0_IRQHandler            [WEAK]
                EXPORT  TIMER1_IRQHandler            [WEAK]
                EXPORT  TIMER2_IRQHandler            [WEAK]
                EXPORT  CRC_IRQHandler               [WEAK]
WDT1_IRQHandler
MEM_IRQHandler
EPWRTZ0_IRQHandler
EPWRTZ1_IRQHandler
GPIO_LEVEL_IRQHandler
GPIO_EDGE_IRQHandler
UART0_IRQHandler
SPI0_IRQHandler
UART1_IRQHandler
SPI1_IRQHandler
CANTRG0_IRQHandler
CANTRG1_IRQHandler
CANTRG2_IRQHandler
CANTRG3_IRQHandler
CANTRG4_IRQHandler
CANTRG5_IRQHandler
CANTRG6_IRQHandler
CANTRG7_IRQHandler
CANMISC_IRQHandler
I2C_IRQHandler
ADCCH0_IRQHandler
ADCCH1_IRQHandler
ADCCH2_IRQHandler
ADCCH3_IRQHandler
ADCCH4_IRQHandler
ADCCH5_IRQHandler
ADCCH6_IRQHandler
ADCCH7_IRQHandler
ADCCH8_IRQHandler
ADCCH9_IRQHandler
ADCCH10_IRQHandler
ADCCH11_IRQHandler
ADCCH12_IRQHandler
ADCCH13_IRQHandler
ADCCH14_IRQHandler
ADCCH15_IRQHandler
ADCPPU0_IRQHandler
ADCPPU1_IRQHandler
ADCPPU2_IRQHandler
PHCOMP_IRQHandler
PWM0_IRQHandler
PWM1_IRQHandler
PWM2_IRQHandler
PWM3_IRQHandler
PWM0TZ_IRQHandler
PWM1TZ_IRQHandler
PWM2TZ_IRQHandler
PWM3TZ_IRQHandler
ECAP_IRQHandler
DMAC_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
CRC_IRQHandler
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
