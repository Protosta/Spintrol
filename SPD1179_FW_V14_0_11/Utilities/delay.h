/******************************************************************************
 * @file     delay.h
 * @brief    Time-Delay module header file.
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


#ifndef DELAY_H
#define DELAY_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  Default delay method
             - DELAY_BY_HW_TIMER0 :  Delay by timer0
             - DELAY_BY_HW_TIMER1 :  Delay by timer1
             - DELAY_BY_HW_TIMER2 :  Delay by timer2
             - DELAY_BY_SW_FLASH  :  Delay by software, code running in Flash
             - DELAY_BY_SW_SRAM   :  Delay by software, code running in SRAM
 */
#if   defined(DELAY_BY_HW_TIMER0)
#define DELAY_TIMER             (TIMER0)
#elif defined(DELAY_BY_HW_TIMER1)
#define DELAY_TIMER             (TIMER1)
#elif defined(DELAY_BY_HW_TIMER2)
#define DELAY_TIMER             (TIMER2)
#elif !defined(DELAY_BY_SW_SRAM)
#define DELAY_BY_SW_FLASH
#endif




/**
 *  @brief  Delay Public Function Declaration
 */
void Delay_Init(void);
void Delay_Ms(uint32_t u32DelayMs);
void Delay_Us(uint32_t u32DelayUs);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* DELAY_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
