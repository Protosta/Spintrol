/******************************************************************************
 * @file     isr.h
 * @brief    Interrupt service routine functions.
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


#include "spc1169.h"




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
// SPC1168 Specific Interrupt Handlers
//---------------------------------------------------------------------------
void EPWRTZ0_IRQHandler(void);
void EPWRTZ1_IRQHandler(void);
void WDT1_IRQHandler(void);
void GPIO_LEVEL_IRQHandler(void);
void GPIO_EDGE_IRQHandler(void);
void UART0_IRQHandler(void);
void SPI0_IRQHandler(void);
void UART1_IRQHandler(void);
void SPI1_IRQHandler(void);
void ADCCH0_IRQHandler(void);
void ADCCH1_IRQHandler(void);
void ADCCH2_IRQHandler(void);
void ADCCH3_IRQHandler(void);
void ADCCH4_IRQHandler(void);
void ADCCH5_IRQHandler(void);
void ADCCH6_IRQHandler(void);
void ADCCH7_IRQHandler(void);
void ADCPPU0_IRQHandler(void);
void ADCPPU1_IRQHandler(void);
void ADCPPU2_IRQHandler(void);
void PWM0_IRQHandler(void);
void PWM1_IRQHandler(void);
void PWM2_IRQHandler(void);
void PWM0TZ_IRQHandler(void);
void PWM1TZ_IRQHandler(void);
void PWM2TZ_IRQHandler(void);
void PHCOMP_IRQHandler(void);
void ECAP_IRQHandler(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void DMAC_IRQHandler(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ISR_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
