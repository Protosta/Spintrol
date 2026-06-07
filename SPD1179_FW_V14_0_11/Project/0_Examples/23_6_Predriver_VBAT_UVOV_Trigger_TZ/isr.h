/******************************************************************************
 * @file     isr.h
 * @brief    Interrupt service routine header file.
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


#ifndef ISR_H
#define ISR_H

#ifdef __cplusplus
extern "C" {
#endif


#if defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif




//---------------------------------------------------------------------------
// Cortex-M4 Processor Exceptions Handlers
//---------------------------------------------------------------------------
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);


//---------------------------------------------------------------------------
// SPC1169 Specific Interrupt Handlers
//---------------------------------------------------------------------------
void WDT1_IRQHandler(void);
void MEM_IRQHandler(void);
void EPWRTZ0_IRQHandler(void);
void EPWRTZ1_IRQHandler(void);
void GPIO_LEVEL_IRQHandler(void);
void GPIO_EDGE_IRQHandler(void);
void UART0_IRQHandler(void);
void SPI0_IRQHandler(void);
void UART1_IRQHandler(void);
void SPI1_IRQHandler(void);
void CANTRG0_IRQHandler(void);
void CANTRG1_IRQHandler(void);
void CANTRG2_IRQHandler(void);
void CANTRG3_IRQHandler(void);
void CANTRG4_IRQHandler(void);
void CANTRG5_IRQHandler(void);
void CANTRG6_IRQHandler(void);
void CANTRG7_IRQHandler(void);
void CANMISC_IRQHandler(void);  
void I2C_IRQHandler(void);
void ADCCH0_IRQHandler(void);
void ADCCH1_IRQHandler(void);
void ADCCH2_IRQHandler(void);
void ADCCH3_IRQHandler(void);
void ADCCH4_IRQHandler(void);
void ADCCH5_IRQHandler(void);
void ADCCH6_IRQHandler(void);
void ADCCH7_IRQHandler(void);
void ADCCH8_IRQHandler(void);
void ADCCH9_IRQHandler(void);
void ADCCH10_IRQHandler(void);
void ADCCH11_IRQHandler(void);
void ADCCH12_IRQHandler(void);
void ADCCH13_IRQHandler(void);
void ADCCH14_IRQHandler(void);
void ADCCH15_IRQHandler(void);
void ADCPPU0_IRQHandler(void);
void ADCPPU1_IRQHandler(void);
void ADCPPU2_IRQHandler(void);
void PHCOMP_IRQHandler(void);
void PWM0_IRQHandler(void);
void PWM1_IRQHandler(void);
void PWM2_IRQHandler(void);
void PWM3_IRQHandler(void);
void PWM0TZ_IRQHandler(void);
void PWM1TZ_IRQHandler(void);
void PWM2TZ_IRQHandler(void);
void PWM3TZ_IRQHandler(void);
void ECAP_IRQHandler(void);
void DMAC_IRQHandler(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void CRC_IRQHandler(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ISR_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
