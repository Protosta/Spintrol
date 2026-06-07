/******************************************************************************
 * @file     timer.h
 * @brief    TIMER module header file.
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


#ifndef TIMER_H
#define TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  TIMER operation mode definition
 */
typedef enum
{
    TIMER_GENERAL_TIMER   = 0,                /*!< General timer mode               */
    TIMER_GATED_TIMER     = 1,                /*!< Gated (by GPIO input) timer mode */
    TIMER_EVENT_COUNTER   = 2,                /*!< GPIO event counter mode          */
    TIMER_EVENT_CAPTURE   = 3,                /*!< GPIO event capture mode          */
} TIMER_ModeEnum;




/******************************************************************************
 * @brief      Set Timer Re-Load value
 *
 * @param[in]  TIMERx        :  Select the timer module
 * @param[in]  u32ReloadValue:  Reload value
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_SetReloadValue(TIMERx,u32ReloadValue)     ((TIMERx)->TMRLOAD = (u32ReloadValue))




/******************************************************************************
 * @brief      Get Timer Re-Load value
 *
 * @param[in]  TIMERx        :  Select the timer module
 *
 * @return     u32ReloadValue:  Reload value
 *
 ******************************************************************************/
#define TIMER_GetReloadValue(TIMERx)                    ((TIMERx)->TMRLOAD)




/******************************************************************************
 * @brief      Set Timer Counter value
 *
 * @param[in]  TIMERx         :  Select the timer module
 * @param[in]  u32CounterValue:  Counter value
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_SetCounterValue(TIMERx,u32CounterValue)   ((TIMERx)->TMRCNT = (u32CounterValue))




/******************************************************************************
 * @brief      Get Timer Counter value
 *
 * @param[in]  TIMERx         :  Select the timer module
 *
 * @return     Current counter value for general timer mode, gated timer mode
 *             and event counter mode
 *             Counter value when event happened for event capture mode
 *
 ******************************************************************************/
#define TIMER_GetCounterValue(TIMERx)       ((TIMERx)->TMRCNT)




/******************************************************************************
 * @brief      Set the timer external input
 *
 * @param[in]  TIMERx   :  Select the timer module
 * @param[in]  ePinName  :  Select the GPIO number for external input
 *                         Please refer to PIN_NameEnum
 * @param[in]  ePinLevel:  Select the GPIO pin level for active external input
 *                         Please refer to GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_SetExternalInput(TIMERx, ePinName, ePinLevel)  MODIFY_REG( (TIMERx)->TMRCTL,                           \
        ( TMRCTL_EXTSEL_Msk | TMRCTL_EXTPOL_Msk ),  \
        ( ((ePinName) << TMRCTL_EXTSEL_Pos) | ((ePinLevel) << TMRCTL_EXTPOL_Pos) )  \
                                                                       )




/******************************************************************************
 * @brief      Enable Hold counter value upon TMRCTL.EN from 1 to 0
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_EnableCounterHold(TIMERx)     ((TIMERx)->TMRCTL |= TMRCTL_HOLD_ENABLE)




/******************************************************************************
 * @brief      Reset counter value to Zero upon TMRCTL.EN from 1 to 0
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_DisableCounterHold(TIMERx)    ((TIMERx)->TMRCTL &= ~TMRCTL_HOLD_Msk)




/******************************************************************************
 * @brief      Enabel ADCSOC generation whenever TMRCNT counts down to 0
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_EnableADCSOC(TIMERx)          ((TIMERx)->TMRCTL |= TMRCTL_ADCSOCEN_ENABLE)




/******************************************************************************
 * @brief      Do not generate ADCSOC
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_DisableADCSOC(TIMERx)         ((TIMERx)->TMRCTL &= ~TMRCTL_ADCSOCEN_Msk)




/******************************************************************************
 * @brief      Enable generate PWMSYNC signal whenever TMRCNT counts down to 0
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_EnablePWMSync(TIMERx)         ((TIMERx)->TMRCTL |= TMRCTL_PWMSYNCEN_ENABLE)




/******************************************************************************
 * @brief      Do not generate PWMSYNC signal
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_DisablePWMSync(TIMERx)        ((TIMERx)->TMRCTL &= ~TMRCTL_PWMSYNCEN_Msk)



/******************************************************************************
 * @brief      Set the timer operation mode
 *
 * @param[in]  TIMERx:  Select the timer module
 * @param[in]  eMode :  Timer operation mode
 *                      Please refer to TIMER_ModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_SetMode(TIMERx, eMode)        ((TIMERx)->TMRCTL = (((TIMERx)->TMRCTL & (~TMRCTL_MODE_Msk)) | ((eMode) << TMRCTL_MODE_Pos)))




/******************************************************************************
 * @brief      Enable Timer
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_Enable(TIMERx)                ((TIMERx)->TMRCTL |= TMRCTL_EN_ENABLE)
#define TIMER_Run(TIMERx)                   ((TIMERx)->TMRCTL |= TMRCTL_EN_ENABLE)




/******************************************************************************
 * @brief      Disable Timer
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_Disable(TIMERx)               ((TIMERx)->TMRCTL &= ~TMRCTL_EN_Msk)
#define TIMER_Stop(TIMERx)                  ((TIMERx)->TMRCTL &= ~TMRCTL_EN_Msk)




/******************************************************************************
 * @brief      Get Timer run status
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_IsEnable(TIMERx)              (((TIMERx)->TMRCTL & TMRCTL_EN_Msk ) >> TMRCTL_EN_Pos)
#define TIMER_IsRun(TIMERx)                 (((TIMERx)->TMRCTL & TMRCTL_EN_Msk ) >> TMRCTL_EN_Pos)




/******************************************************************************
 * @brief      Enable Timer interrupt
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_EnableInt(TIMERx)             ((TIMERx)->TMRIE |= TMRIE_INT_ENABLE)




/******************************************************************************
 * @brief      Disable Timer interrupt
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_DisableInt(TIMERx)            ((TIMERx)->TMRIE &= ~TMRIE_INT_Msk)




/******************************************************************************
 * @brief      Clear Timer interrupt
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_ClearInt(TIMERx)              ((TIMERx)->TMRIC = TMRIC_INT_CLEAR)




/******************************************************************************
 * @brief      Get Timer event raw flag
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     0 - Timer event did not occur
 *             1 - Timer event occurred
 *
 ******************************************************************************/
#define TIMER_GetIntRawFlag(TIMERx)         ((TIMERx)->TMRRAWIF)




/******************************************************************************
 * @brief      Get Timer interrupt flag
 *
 * @param[in]  TIMERx:  Select the timer module
 *
 * @return     0 - Timer interrupt did not occur
 *             1 - Timer interrupt occurred
 *
 ******************************************************************************/
#define TIMER_GetIntFlag(TIMERx)            ((TIMERx)->TMRIF)




/******************************************************************************
 * @brief      Enable write access to the protected TIMER registers
 *
 * @param[in]  TIMERx:  Select the TIMER module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_WALLOW(TIMERx)                 ((TIMERx)->TMRREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected TIMER registers
 *
 * @param[in]  TIMERx:  Select the TIMER module
 *
 * @return     None
 *
 ******************************************************************************/
#define TIMER_WDIS(TIMERx)                   ((TIMERx)->TMRREGKEY = 0x0)




/**
 *  @brief  TIMER Public Function Declaration
 */
void TIMER_Init(TIMER_REGS *TIMERx, uint32_t u32TimerPeriodMs);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* TIMER_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
