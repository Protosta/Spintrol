/******************************************************************************
 * @file     wdt.c
 * @brief    Watchog firmware functions.
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

#include "wdt.h"


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/******************************************************************************
 * @brief      Initialize the Watchdog Timer
 *
 * @param[in]  WDTx     :  Select the watchdog module
 * @param[in]  u32TimeMs:  Watchdog timeout in ms
 *
 * @return     none
 *
 ******************************************************************************/
void WDT_Init(WDT_REGS *WDTx, uint32_t u32TimeMs)
{
    uint32_t u32WdtClk;

    /* Enable write access to all other registers */
    WDT_WALLOW(WDTx);
    
    /* Disable WDT and interrupt */
    WDT_Disable(WDTx);
    WDT_DisableInt(WDTx);

    /* Enable and Get Watchdog module clock */
    if (WDTx == WDT0)
    {
        u32WdtClk = CLOCK_GetModuleClock(WDT0_MODULE);
    }
    else
    {
        u32WdtClk = CLOCK_GetModuleClock(WDT1_MODULE);
    }

    /* Watchdog load register value */
    WDT_SetReloadValue(WDTx, u32WdtClk / 1000 * u32TimeMs);

    /* Allow watchdog to run during CPU halted mode */
    WDT_EnableRunWhenCoreHalt(WDTx);

    /* Allow watchdog to run during CPU lockup mode */
    WDT_EnableRunWhenCoreLockup(WDTx);
    
    /* Clear Int */
    WDT_ClearInt(WDTx);
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
