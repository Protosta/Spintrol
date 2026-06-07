/******************************************************************************
 * @file     wdt.h
 * @brief    Watchdog module header file.
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


#ifndef WDT_H
#define WDT_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/******************************************************************************
 * @brief      Start watchdog counter
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_Enable(WDTx)                    ((WDTx)->WDTCTL |= WDTCTL_EN_ENABLE)
#define WDT_Run(WDTx)                       ((WDTx)->WDTCTL |= WDTCTL_EN_ENABLE)




/******************************************************************************
 * @brief      Stop watchdog counter
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_Disable(WDTx)                   ((WDTx)->WDTCTL &= ~WDTCTL_EN_ENABLE)
#define WDT_Stop(WDTx)                      ((WDTx)->WDTCTL &= ~WDTCTL_EN_ENABLE)




/******************************************************************************
 * @brief      Get watchdog run status
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_IsEnable(WDTx)                  (((WDTx)->WDTCTL & WDTCTL_EN_Msk) >> WDTCTL_EN_Pos)
#define WDT_IsRun(WDTx)                     (((WDTx)->WDTCTL & WDTCTL_EN_Msk) >> WDTCTL_EN_Pos)




/******************************************************************************
 * @brief      Enable watchdog running when core halted
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
******************************************************************************/
#define WDT_EnableRunWhenCoreHalt(WDTx)     ((WDTx)->WDTCTL |= WDTCTL_HALTEDRUN_ENABLE)




/******************************************************************************
 * @brief      Disable watchdog running when core halted
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
******************************************************************************/
#define WDT_DisableRunWhenCoreHalt(WDTx)    ((WDTx)->WDTCTL &= ~WDTCTL_HALTEDRUN_ENABLE)




/******************************************************************************
 * @brief      Enable watchdog running when core lockup
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
******************************************************************************/
#define WDT_EnableRunWhenCoreLockup(WDTx)   ((WDTx)->WDTCTL |= WDTCTL_LOCKUPRUN_ENABLE)




/******************************************************************************
 * @brief      Disable watchdog running when core lockup
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
******************************************************************************/
#define WDT_DisableRunWhenCoreLockup(WDTx)  ((WDTx)->WDTCTL &= ~WDTCTL_LOCKUPRUN_ENABLE)




/******************************************************************************
 * @brief      Set watchdog load register value
 *             When the value is written to the register, the WDT count is
 *             immediately restarted from the new value. The minimum valid value is 1.
 *
 * @param[in]  WDTx      :  Select the watchdog module
 * @param[in]  u32LoadVal:  Watchdog load register value
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_SetReloadValue(WDTx,u32LoadVal)   ((WDTx)->WDTLOAD = (u32LoadVal))




/******************************************************************************
 * @brief      Get watchdog load register value
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     The load register value
 *
******************************************************************************/
#define WDT_GetReloadValue(WDTx)            ((WDTx)->WDTLOAD)




/******************************************************************************
 * @brief      Get watchdog current counter value
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     Current counter value
 *
******************************************************************************/
#define WDT_GetCounterValue(WDTx)           ((WDTx)->WDTCNT)




/******************************************************************************
 * @brief      Get watchdog raw event status
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     0 - Event did not occur
 *             1 - Event occurred
 *
 ******************************************************************************/
#define WDT_GetIntRawFlag(WDTx)             ((WDTx)->WDTRAWIF)




/******************************************************************************
 * @brief      Get watchdog interrupt status
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     0 - Interrupt did not occur
 *             1 - Interrupt occurred
 *
 ******************************************************************************/
#define WDT_GetIntFlag(WDTx)                ((WDTx)->WDTIF)




/******************************************************************************
 * @brief      Clear watchdog interrupt flag
 *             A write of any value to the WDTIC register clears the watchdog
 *             interrupt, and reloads the counter from the value in WDTLOAD
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_ClearInt(WDTx)                  ((WDTx)->WDTIC = 0x1)




/******************************************************************************
 * @brief      Feed dog
 *             A write of any value to the WDTIC register clears the watchdog
 *             interrupt, and reloads the counter from the value in WDTLOAD
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_FeedDog(WDTx)                   ((WDTx)->WDTIC = 0x1)




/******************************************************************************
 * @brief      Enable watchdog interrupt and the counter
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_EnableInt(WDTx)                 ((WDTx)->WDTIE = WDTIE_INT_ENABLE)




/******************************************************************************
 * @brief      Disable watchdog interrupt and the counter
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_DisableInt(WDTx)                ((WDTx)->WDTIE = WDTIE_INT_DISABLE)




/******************************************************************************
 * @brief      Enable write access to the protected WDT registers
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_WALLOW(WDTx)                    ((WDTx)->WDTREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected WDT registers
 *
 * @param[in]  WDTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define WDT_WDIS(WDTx)                      ((WDTx)->WDTREGKEY = 0x0)




/**
 *  @brief Watchdog Public Function Declaration
 */
void WDT_Init(WDT_REGS *WDTx, uint32_t u32TimeMs);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* WDT_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
