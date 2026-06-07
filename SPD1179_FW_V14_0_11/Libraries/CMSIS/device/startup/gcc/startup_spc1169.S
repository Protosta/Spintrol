/****************************************************************************
 * @brief    Device vector table for GCC toolchain
 * @version  VXX.XX.XX
 * @date     XX-XXX-XXXX
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

    
  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

    .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  ldr     r0, =0xE000ED08
  ldr     r1, =g_pfnVectors
  str     r1, [r0]

  ldr   sp, =_estack       /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system initialization function.*/
  bl  SystemInit   

/* Call the application's entry point.*/
  bl  main
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None     
 * @retval None       
*/
    .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b  Infinite_Loop
  .size  Default_Handler, .-Default_Handler

   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors
    
g_pfnVectors:
    .word  _estack             
    .word   Reset_Handler               
    .word   NMI_Handler                 
    .word   HardFault_Handler           
    .word   MemManage_Handler           
    .word   BusFault_Handler            
    .word   UsageFault_Handler          
    .word   0                           
    .word   0                           
    .word   0                           
    .word   0                           
    .word   SVC_Handler                 
    .word   DebugMon_Handler            
    .word   0                           
    .word   PendSV_Handler              
    .word   SysTick_Handler             

                                        
    .word   WDT1_IRQHandler          
    .word   MEM_IRQHandler           
    .word   EPWRTZ0_IRQHandler       
    .word   EPWRTZ1_IRQHandler       
    .word   GPIO_LEVEL_IRQHandler    
    .word   GPIO_EDGE_IRQHandler     
    .word   UART0_IRQHandler         
    .word   SPI0_IRQHandler          
    .word   UART1_IRQHandler         
    .word   SPI1_IRQHandler          
    .word   CANTRG0_IRQHandler       
    .word   CANTRG1_IRQHandler       
    .word   CANTRG2_IRQHandler       
    .word   CANTRG3_IRQHandler       
    .word   CANTRG4_IRQHandler       
    .word   CANTRG5_IRQHandler       
    .word   CANTRG6_IRQHandler       
    .word   CANTRG7_IRQHandler       
    .word   CANMISC_IRQHandler       
    .word   I2C_IRQHandler           
    .word   ADCCH0_IRQHandler        
    .word   ADCCH1_IRQHandler        
    .word   ADCCH2_IRQHandler        
    .word   ADCCH3_IRQHandler        
    .word   ADCCH4_IRQHandler        
    .word   ADCCH5_IRQHandler        
    .word   ADCCH6_IRQHandler        
    .word   ADCCH7_IRQHandler        
    .word   ADCCH8_IRQHandler        
    .word   ADCCH9_IRQHandler        
    .word   ADCCH10_IRQHandler       
    .word   ADCCH11_IRQHandler       
    .word   ADCCH12_IRQHandler       
    .word   ADCCH13_IRQHandler       
    .word   ADCCH14_IRQHandler       
    .word   ADCCH15_IRQHandler       
    .word   ADCPPU0_IRQHandler       
    .word   ADCPPU1_IRQHandler       
    .word   ADCPPU2_IRQHandler       
    .word   PHCOMP_IRQHandler        
    .word   PWM0_IRQHandler          
    .word   PWM1_IRQHandler          
    .word   PWM2_IRQHandler          
    .word   PWM3_IRQHandler          
    .word   PWM0TZ_IRQHandler        
    .word   PWM1TZ_IRQHandler        
    .word   PWM2TZ_IRQHandler        
    .word   PWM3TZ_IRQHandler        
    .word   ECAP_IRQHandler          
    .word   DMAC_IRQHandler          
    .word   TIMER0_IRQHandler        
    .word   TIMER1_IRQHandler        
    .word   TIMER2_IRQHandler        
    .word   CRC_IRQHandler           



    .weak NMI_Handler
    .thumb_set NMI_Handler, Default_Handler

    .weak HardFault_Handler
    .thumb_set HardFault_Handler, Default_Handler
    
    .weak MemManage_Handler
    .thumb_set MemManage_Handler,Default_Handler
    
    .weak BusFault_Handler
    .thumb_set BusFault_Handler,Default_Handler
    
    .weak UsageFault_Handler
    .thumb_set UsageFault_Handler,Default_Handler
    
    .weak SVC_Handler
    .thumb_set SVC_Handler, Default_Handler
    
    .weak DebugMon_Handler
    .thumb_set DebugMon_Handler,Default_Handler
    
    .weak PendSV_Handler
    .thumb_set PendSV_Handler, Default_Handler

    .weak SysTick_Handler
    .thumb_set SysTick_Handler, Default_Handler

    .weak WDT1_IRQHandler
    .thumb_set WDT1_IRQHandler, Default_Handler

    .weak MEM_IRQHandler
    .thumb_set MEM_IRQHandler, Default_Handler

    .weak EPWRTZ0_IRQHandler
    .thumb_set EPWRTZ0_IRQHandler, Default_Handler

    .weak EPWRTZ1_IRQHandler
    .thumb_set EPWRTZ1_IRQHandler, Default_Handler

    .weak GPIO_LEVEL_IRQHandler
    .thumb_set GPIO_LEVEL_IRQHandler, Default_Handler

    .weak GPIO_EDGE_IRQHandler
    .thumb_set GPIO_EDGE_IRQHandler, Default_Handler

    .weak UART0_IRQHandler
    .thumb_set UART0_IRQHandler, Default_Handler

    .weak SPI0_IRQHandler
    .thumb_set SPI0_IRQHandler, Default_Handler

    .weak UART1_IRQHandler
    .thumb_set UART1_IRQHandler, Default_Handler

    .weak SPI1_IRQHandler
    .thumb_set SPI1_IRQHandler, Default_Handler

    .weak CANTRG0_IRQHandler
    .thumb_set CANTRG0_IRQHandler, Default_Handler

    .weak CANTRG1_IRQHandler
    .thumb_set CANTRG1_IRQHandler, Default_Handler
    
    .weak CANTRG2_IRQHandler
    .thumb_set CANTRG2_IRQHandler, Default_Handler

    .weak CANTRG3_IRQHandler
    .thumb_set CANTRG3_IRQHandler, Default_Handler

    .weak CANTRG4_IRQHandler
    .thumb_set CANTRG4_IRQHandler, Default_Handler

    .weak CANTRG5_IRQHandler
    .thumb_set CANTRG5_IRQHandler, Default_Handler

    .weak CANTRG6_IRQHandler
    .thumb_set CANTRG6_IRQHandler, Default_Handler

    .weak CANTRG7_IRQHandler
    .thumb_set CANTRG7_IRQHandler, Default_Handler

    .weak CANMISC_IRQHandler
    .thumb_set CANMISC_IRQHandler, Default_Handler

    .weak I2C_IRQHandler
    .thumb_set I2C_IRQHandler, Default_Handler

    .weak ADCCH0_IRQHandler
    .thumb_set ADCCH0_IRQHandler, Default_Handler

    .weak ADCCH1_IRQHandler
    .thumb_set ADCCH1_IRQHandler, Default_Handler

    .weak ADCCH2_IRQHandler
    .thumb_set ADCCH2_IRQHandler, Default_Handler

    .weak ADCCH3_IRQHandler
    .thumb_set ADCCH3_IRQHandler, Default_Handler

    .weak ADCCH4_IRQHandler
    .thumb_set ADCCH4_IRQHandler, Default_Handler

    .weak ADCCH5_IRQHandler
    .thumb_set ADCCH5_IRQHandler, Default_Handler

    .weak ADCCH6_IRQHandler
    .thumb_set ADCCH6_IRQHandler, Default_Handler

    .weak ADCCH7_IRQHandler
    .thumb_set ADCCH7_IRQHandler, Default_Handler

    .weak ADCCH8_IRQHandler
    .thumb_set ADCCH8_IRQHandler, Default_Handler

    .weak ADCCH9_IRQHandler
    .thumb_set ADCCH9_IRQHandler, Default_Handler

    .weak ADCCH10_IRQHandler
    .thumb_set ADCCH10_IRQHandler, Default_Handler

    .weak ADCCH11_IRQHandler
    .thumb_set ADCCH11_IRQHandler, Default_Handler

    .weak ADCCH12_IRQHandler
    .thumb_set ADCCH12_IRQHandler, Default_Handler

    .weak ADCCH13_IRQHandler
    .thumb_set ADCCH13_IRQHandler, Default_Handler

    .weak ADCCH14_IRQHandler
    .thumb_set ADCCH14_IRQHandler, Default_Handler

    .weak ADCCH15_IRQHandler
    .thumb_set ADCCH15_IRQHandler, Default_Handler

    .weak ADCPPU0_IRQHandler
    .thumb_set ADCPPU0_IRQHandler, Default_Handler

    .weak ADCPPU1_IRQHandler
    .thumb_set ADCPPU1_IRQHandler, Default_Handler

    .weak ADCPPU2_IRQHandler
    .thumb_set ADCPPU2_IRQHandler, Default_Handler

    .weak PHCOMP_IRQHandler
    .thumb_set PHCOMP_IRQHandler, Default_Handler

    .weak PWM0_IRQHandler
    .thumb_set PWM0_IRQHandler, Default_Handler

    .weak PWM1_IRQHandler
    .thumb_set PWM1_IRQHandler, Default_Handler

    .weak PWM2_IRQHandler
    .thumb_set PWM2_IRQHandler, Default_Handler

    .weak PWM3_IRQHandler
    .thumb_set PWM3_IRQHandler, Default_Handler

    .weak PWM0TZ_IRQHandler
    .thumb_set PWM0TZ_IRQHandler, Default_Handler

    .weak PWM1TZ_IRQHandler
    .thumb_set PWM1TZ_IRQHandler, Default_Handler

    .weak PWM2TZ_IRQHandler
    .thumb_set PWM2TZ_IRQHandler, Default_Handler

    .weak PWM3TZ_IRQHandler
    .thumb_set PWM3TZ_IRQHandler, Default_Handler

    .weak ECAP_IRQHandler
    .thumb_set ECAP_IRQHandler, Default_Handler

    .weak DMAC_IRQHandler
    .thumb_set DMAC_IRQHandler, Default_Handler

    .weak TIMER0_IRQHandler
    .thumb_set TIMER0_IRQHandler, Default_Handler

    .weak TIMER1_IRQHandler
    .thumb_set TIMER1_IRQHandler, Default_Handler

    .weak TIMER2_IRQHandler
    .thumb_set TIMER2_IRQHandler, Default_Handler
 
    .weak CRC_IRQHandler
    .thumb_set CRC_IRQHandler, Default_Handler
