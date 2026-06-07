/****************************************************************************
 * @brief    Device vector table for EWARM toolchain
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
 *
 * @attention
 * THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION REGARDING 
 * THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM. SPINTROL SHALL NOT BE
 * LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL DOES NOT GUARANTEE THE 
 * CORRECTNESS OF THIS SOFTWARE AND RESERVES THE RIGHT TO MODIFY THE SOFTWARE 
 * WITHOUT NOTIFICATION.
 *
 ******************************************************************************/
;
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)               ;-16 Top of Stack
        DCD     Reset_Handler             ;-15 Reset Handler
        
        DCD     NMI_Handler               ;-14 NMI Handler
        DCD     HardFault_Handler         ;-13 Hard Fault Handler
        DCD     MemManage_Handler         ;-12 MPU Fault Handler
        DCD     BusFault_Handler          ;-11 Bus Fault Handler
        DCD     UsageFault_Handler        ;-10 Usage Fault Handler
        DCD     0                         ;- 9 Reserved
        DCD     0                         ;- 8 Reserved
        DCD     0                         ;- 7 Reserved
        DCD     0                         ;- 6 Reserved
        DCD     SVC_Handler               ;- 5 SVCall Handler
        DCD     DebugMon_Handler          ;- 4 Debug Monitor Handler
        DCD     0                         ;- 3 Reserved
        DCD     PendSV_Handler            ;- 2 PendSV Handler
        DCD     SysTick_Handler           ;- 1 SysTick Handler

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


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        
        ; Remap vector table
        LDR     R0, =__vector_table
        LDR     R1, =0xE000ED08 ;*VTOR register
        STR     R0,[R1]
        
        ;* C routines are likely to be called. Setup the stack now
        LDR     SP,=sfe(CSTACK)
        
        LDR     R0, =SystemInit
        BLX     R0
        
        ;* Reset stack pointer before zipping off to user application
        LDR     SP,=sfe(CSTACK)
        
        LDR     R0, =__iar_program_start
        BX      R0


        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler
        
        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B  BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B  SysTick_Handler

        PUBWEAK WDT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
WDT1_IRQHandler
        B WDT1_IRQHandler
        
        PUBWEAK MEM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
MEM_IRQHandler
        B MEM_IRQHandler
        
        PUBWEAK EPWRTZ0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EPWRTZ0_IRQHandler
        B EPWRTZ0_IRQHandler
        
        PUBWEAK EPWRTZ1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
EPWRTZ1_IRQHandler
        B EPWRTZ1_IRQHandler
        
        PUBWEAK GPIO_LEVEL_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
GPIO_LEVEL_IRQHandler
        B GPIO_LEVEL_IRQHandler
        
        PUBWEAK GPIO_EDGE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
GPIO_EDGE_IRQHandler
        B GPIO_EDGE_IRQHandler
        
        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
UART1_IRQHandler
        B UART1_IRQHandler
        
        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
SPI1_IRQHandler
        B SPI1_IRQHandler
              
        PUBWEAK CANTRG0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG0_IRQHandler
        B CANTRG0_IRQHandler

        PUBWEAK CANTRG1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG1_IRQHandler
        B CANTRG1_IRQHandler

        PUBWEAK CANTRG2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG2_IRQHandler
        B CANTRG2_IRQHandler

        PUBWEAK CANTRG3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG3_IRQHandler
        B CANTRG3_IRQHandler

        PUBWEAK CANTRG4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG4_IRQHandler
        B CANTRG4_IRQHandler

        PUBWEAK CANTRG5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG5_IRQHandler
        B CANTRG5_IRQHandler

        PUBWEAK CANTRG6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG6_IRQHandler
        B CANTRG6_IRQHandler

        PUBWEAK CANTRG7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANTRG7_IRQHandler
        B CANTRG7_IRQHandler

        PUBWEAK CANMISC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CANMISC_IRQHandler
        B CANMISC_IRQHandler

        PUBWEAK I2C_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
I2C_IRQHandler
        B I2C_IRQHandler

        PUBWEAK ADCCH0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH0_IRQHandler
        B ADCCH0_IRQHandler
         
        PUBWEAK ADCCH1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH1_IRQHandler
        B ADCCH1_IRQHandler

        PUBWEAK ADCCH2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH2_IRQHandler
        B ADCCH2_IRQHandler

        PUBWEAK ADCCH3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH3_IRQHandler
        B ADCCH3_IRQHandler

        PUBWEAK ADCCH4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH4_IRQHandler
        B ADCCH4_IRQHandler
        
        PUBWEAK ADCCH5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH5_IRQHandler
        B ADCCH5_IRQHandler
        
        PUBWEAK ADCCH6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH6_IRQHandler
        B ADCCH6_IRQHandler
        
        PUBWEAK ADCCH7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH7_IRQHandler
        B ADCCH7_IRQHandler
             
        PUBWEAK ADCCH8_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH8_IRQHandler
        B ADCCH8_IRQHandler
         
        PUBWEAK ADCCH9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH9_IRQHandler
        B ADCCH9_IRQHandler

        PUBWEAK ADCCH10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH10_IRQHandler
        B ADCCH10_IRQHandler

        PUBWEAK ADCCH11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH11_IRQHandler
        B ADCCH11_IRQHandler

        PUBWEAK ADCCH12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH12_IRQHandler
        B ADCCH12_IRQHandler
        
        PUBWEAK ADCCH13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH13_IRQHandler
        B ADCCH13_IRQHandler
        
        PUBWEAK ADCCH14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH14_IRQHandler
        B ADCCH14_IRQHandler
        
        PUBWEAK ADCCH15_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCCH15_IRQHandler
        B ADCCH15_IRQHandler

        PUBWEAK ADCPPU0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCPPU0_IRQHandler
        B ADCPPU0_IRQHandler
        
        PUBWEAK ADCPPU1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCPPU1_IRQHandler
        B ADCPPU1_IRQHandler
        
        PUBWEAK ADCPPU2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ADCPPU2_IRQHandler
        B ADCPPU2_IRQHandler
              
        PUBWEAK PHCOMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PHCOMP_IRQHandler
        B PHCOMP_IRQHandler

        PUBWEAK PWM0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM0_IRQHandler
        B PWM0_IRQHandler
        
        PUBWEAK PWM1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM1_IRQHandler
        B PWM1_IRQHandler
        
        PUBWEAK PWM2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM2_IRQHandler
        B PWM2_IRQHandler

        PUBWEAK PWM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM3_IRQHandler
        B PWM3_IRQHandler

        PUBWEAK PWM0TZ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM0TZ_IRQHandler
        B PWM0TZ_IRQHandler
       
        PUBWEAK PWM1TZ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM1TZ_IRQHandler
        B PWM1TZ_IRQHandler

        PUBWEAK PWM2TZ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM2TZ_IRQHandler
        B PWM2TZ_IRQHandler
        
        PUBWEAK PWM3TZ_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
PWM3TZ_IRQHandler
        B PWM3TZ_IRQHandler
            
        PUBWEAK ECAP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
ECAP_IRQHandler
        B ECAP_IRQHandler

        PUBWEAK DMAC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
DMAC_IRQHandler
        B DMAC_IRQHandler

        PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
TIMER0_IRQHandler
        B TIMER0_IRQHandler
        
        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
TIMER1_IRQHandler
        B TIMER1_IRQHandler
        
        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
TIMER2_IRQHandler
        B TIMER2_IRQHandler
        
        PUBWEAK CRC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1) 
CRC_IRQHandler
        B CRC_IRQHandler
        


        END

/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
