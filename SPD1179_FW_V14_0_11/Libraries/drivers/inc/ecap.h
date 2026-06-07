/******************************************************************************
 * @file     ecap.h
 * @brief    eCAP driver header file.
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


#ifndef ECAP_H
#define ECAP_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  ECAP mode definition
 */
typedef enum
{
    ECAP_CAPTURE_MODE               =  0,               /*!< Capture mode                           */
    ECAP_APWM_MODE                  =  1,               /*!< APWM mode                              */
} ECAP_ModeEnum;




/**
 *  @brief  ECAP counter mode on CPU halt definition
 */
typedef enum
{
    ECAP_COUNTER_STOP_IMMEDIATELY   =  0,               /*!< Counter stops immediately              */
    ECAP_COUNTER_STOP_AT_ZERO       =  1,               /*!< Counter stops when it reaches 0        */
    ECAP_COUNTER_KEEP_RUNNING       =  2,               /*!< Counter keeps running                  */
} ECAP_CounterModeOnCPUHaltEnum;




/**
 *  @brief  ECAP SYNCO output options definition
 */
typedef enum
{
    ECAP_SYNCO_DISABLE              =  1,               /*!< SYNC output disable                    */
    ECAP_SYNCO_IS_SYNCI             =  2,               /*!< SYNC output is the same as SYNC input  */
    ECAP_SYNCO_IS_CNT_EQU_PRD       =  3,               /*!< SYNC output when counter=PRD           */
} ECAP_SyncOutEnum;




/**
 *  @brief  ECAP event type definition
 */
typedef enum
{
    ECAP_CEVT0                      =  0,               /*!< Capture event 0                        */
    ECAP_CEVT1                      =  1,               /*!< Capture event 1                        */
    ECAP_CEVT2                      =  2,               /*!< Capture event 2                        */
    ECAP_CEVT3                      =  3,               /*!< Capture event 3                        */
} ECAP_EventEnum;




/**
 *  @brief  ECAP interrupt type definition
 */
typedef enum
{
    ECAP_INT_CEVT0                  = (1U << 0),      /*!< Capture event 0 interrupt                        */
    ECAP_INT_CEVT1                  = (1U << 1),      /*!< Capture event 1 interrupt                        */
    ECAP_INT_CEVT2                  = (1U << 2),      /*!< Capture event 2 interrupt                        */
    ECAP_INT_CEVT3                  = (1U << 3),      /*!< Capture event 3 interrupt                        */
    ECAP_INT_CNT_OVERFLOW           = (1U << 4),      /*!< Counter overflow interrupt                       */
    ECAP_INT_CNT_EQU_PRD            = (1U << 5),      /*!< Counter equal period interrupt (APWM mode only)  */
    ECAP_INT_CNT_EQU_CMP            = (1U << 6),      /*!< Counter equal Compare interrupt (APWM mode only) */
    ECAP_INT_GLOBAL                 = (1U << 7),      /*!< Global interrupt flag                            */
    ECAP_INT_ALL                    = (0xFFU),        /*!< Used for all interrupts                          */
} ECAP_IntEnum;




/******************************************************************************
 * @brief      Set ECAP input source and polarity
 *
 * @param[in]  ECAPx    :  Select the ECAP module
 * @param[in]  ePinName :  Select the GPIO pin for external input
 *                         Please refer to PIN_NameEnum
 * @param[in]  ePinLevel:  Select the GPIO pin level for active external input
 *                         Please refer to GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetInput(ECAPx, ePinName, ePinLevel)                               \
    MODIFY_REG( (ECAPx)->CAPSRCCTL,                                               \
                ( CAPSRCCTL_IOSEL_Msk | CAPSRCCTL_POL_Msk ),                      \
                ( ((ePinName) << CAPSRCCTL_IOSEL_Pos)                             \
                  |((ePinLevel) << CAPSRCCTL_POL_Pos)                              \
                )                                                                 \
              )




/******************************************************************************
 * @brief      Get ECAP input source
 *
 * @param[in]  ECAPx    :  Select the ECAP module
 *
 * @return     Get the GPIO pin for external input
 *             Please refer to PIN_NameEnum
 *
 ******************************************************************************/
#define ECAP_GetInputSource(ECAPx)                                              \
    READ_FIELD( (ECAPx)->CAPSRCCTL, CAPSRCCTL_IOSEL_Msk, CAPSRCCTL_IOSEL_Pos )




/******************************************************************************
 * @brief      Get ECAP input source polarity
 *
 * @param[in]  ECAPx    :  Select the ECAP module
 *
 * @return     Get the GPIO pin level for active external input
 *             Please refer to GPIO_LevelEnum
 *
 ******************************************************************************/
#define ECAP_GetInputSourcePolarity(ECAPx)                                      \
    READ_FIELD( (ECAPx)->CAPSRCCTL, CAPSRCCTL_POL_Msk, CAPSRCCTL_POL_Pos )




/******************************************************************************
 * @brief      Set capture synchronization input source and polarity
 *
 * @param[in]  ECAPx    :  Select the ECAP module
 * @param[in]  ePinName :  Select the GPIO pin for external input
 *                         Please refer to PIN_NameEnum
 * @param[in]  ePinLevel:  Select the GPIO pin level for active external input
 *                         Please refer to GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetSyncInput(ECAPx, ePinName, ePinLevel)                           \
    MODIFY_REG( (ECAPx)->CAPSYNCICTL,                                             \
                (   CAPSYNCICTL_IOSEL_Msk                                                   \
                    | CAPSYNCICTL_POL_Msk                                                       \
                ),                                                                          \
                (   ((ePinName) << CAPSYNCICTL_IOSEL_Pos)                                   \
                    | ((ePinLevel) << CAPSYNCICTL_POL_Pos)                                    \
                )                                                                           \
              )




/******************************************************************************
 * @brief      Get capture synchronization input source
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Get the GPIO number for external input
 *             Please refer to PIN_NameEnum
 *
 ******************************************************************************/
#define ECAP_GetSyncInputSource(ECAPx)                                          \
    READ_FIELD( (ECAPx)->CAPSYNCICTL, CAPSYNCICTL_IOSEL_Msk, CAPSYNCICTL_IOSEL_Pos )




/******************************************************************************
 * @brief      Get capture synchronization input polarity
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Get the GPIO pin level for active external input
 *             Please refer to GPIO_LevelEnum
 *
 ******************************************************************************/
#define ECAP_GetSyncInputPolarity(ECAPx)                                        \
    READ_FIELD( (ECAPx)->CAPSYNCICTL, CAPSYNCICTL_POL_Msk, CAPSYNCICTL_POL_Pos )




/******************************************************************************
 * @brief      Set Counter Value
 *
 * @param[in]  ECAPx    :  Select the ECAP module
 * @param[in]  u32CntVal:  Counter value
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetCounterValue(ECAPx,u32CntVal)   ((ECAPx)->CAPTSCNT = (u32CntVal))




/******************************************************************************
 * @brief      Get ECAP counter value
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current counter value
 *
 ******************************************************************************/
#define ECAP_GetCounterValue(ECAPx)         ((ECAPx)->CAPTSCNT)




/******************************************************************************
 * @brief      Set ECAP synchronization reload value
 *             ECAP counter will equal CAPCNTPHS after synchronization event
 *
 * @param[in]  ECAPx :  Select the ECAP module
 * @param[in]  u32Val:  ECAP counter reload value
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetSyncReloadValue(ECAPx,u32Val)   ((ECAPx)->CAPCNTPHS = (u32Val))




/******************************************************************************
 * @brief      Get ECAP synchronization reload value
 *             ECAP counter will equal CAPCNTPHS after synchronization event
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     ECAP counter reload value
 *
 ******************************************************************************/
#define ECAP_GetSyncReloadValue(ECAPx)      ((ECAPx)->CAPCNTPHS)




/******************************************************************************
 * @brief      Get CAP0 value
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current CAP0 value
 *
 ******************************************************************************/
#define ECAP_GetCAP0(ECAPx)                 ((ECAPx)->CAP0)




/******************************************************************************
 * @brief      Get CAP1 value
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current CAP1 value
 *
 ******************************************************************************/
#define ECAP_GetCAP1(ECAPx)                 ((ECAPx)->CAP1)




/******************************************************************************
 * @brief      Get CAP2 value
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current CAP2 value
 *
 ******************************************************************************/
#define ECAP_GetCAP2(ECAPx)                 ((ECAPx)->CAP2)




/******************************************************************************
 * @brief      Get CAP3 value
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current CAP3 value
 *
 ******************************************************************************/
#define ECAP_GetCAP3(ECAPx)                 ((ECAPx)->CAP3)




/******************************************************************************
 * @brief      Get active PRD value for APWM mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current active PRD value
 *
 ******************************************************************************/
#define ECAP_GetPRD(ECAPx)                  ((ECAPx)->CAP0)




/******************************************************************************
 * @brief      Set active PRD value for APWM mode
 *
 * @param[in]  ECAPx :  Select the ECAP module
 * @param[in]  u32Val:  Active PRD value to be set
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetPRD(ECAPx, u32Val)          ((ECAPx)->CAP0 = (u32Val))




/******************************************************************************
 * @brief      Get active CMP value for APWM mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current active CMP value
 *
 ******************************************************************************/
#define ECAP_GetCMP(ECAPx)                  ((ECAPx)->CAP1)




/******************************************************************************
 * @brief      Set active CMP value for APWM mode
 *
 * @param[in]  ECAPx :  Select the ECAP module
 * @param[in]  u32Val:  Active CMP value to be set
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetCMP(ECAPx, u32Val)          ((ECAPx)->CAP1 = (u32Val))




/******************************************************************************
 * @brief      Get shadow PRD value for APWM mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current active PRD value
 *
 ******************************************************************************/
#define ECAP_GetShadowPRD(ECAPx)            ((ECAPx)->CAP2)




/******************************************************************************
 * @brief      Set shadow PRD value for APWM mode
 *
 * @param[in]  ECAPx :  Select the ECAP module
 * @param[in]  u32Val:  Shadow PRD value to be set
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetShadowPRD(ECAPx, u32Val)    ((ECAPx)->CAP2 = (u32Val))




/******************************************************************************
 * @brief      Get shadow CMP value for APWM mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     Current active CMP value
 *
 ******************************************************************************/
#define ECAP_GetShadowCMP(ECAPx)            ((ECAPx)->CAP3)




/******************************************************************************
 * @brief      Set shadow CMP value for APWM mode
 *
 * @param[in]  ECAPx :  Select the ECAP module
 * @param[in]  u32Val:  Shadow CMP value to be set
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetShadowCMP(ECAPx, u32Val)    ((ECAPx)->CAP3 = (u32Val))




/******************************************************************************
 * @brief      Set ECAP Run Mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 * @param[in]  eMode:  Run mode
 *                     Please refer to ECAP_ModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
/* #define ECAP_SetRunMode(ECAPx, eMode)                                           \
 WRITE_FIELD((ECAPx)->CAPCTL, CAPCTL_APWMMODE_Msk, CAPCTL_APWMMODE_Pos, (eMode)) */

#define ECAP_SetMode(ECAPx, eMode)                                              \
    WRITE_FIELD((ECAPx)->CAPCTL, CAPCTL_APWMMODE_Msk, CAPCTL_APWMMODE_Pos, (eMode))




/******************************************************************************
 * @brief      Set counter behavior upon CPU halt
 *             (due to debug or other reason)
 *
 * @param[in]  ECAPx:  Select the ECAP module
 * @param[in]  eMode:  Counter mode when CPU is halted
 *                     Please refer to ECAP_CounterModeOnCPUHaltEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetCounterModeOnCPUHalt(ECAPx, eMode)                              \
    WRITE_FIELD((ECAPx)->CAPCTL, CAPCTL_DBGRUN_Msk, CAPCTL_DBGRUN_Pos, (eMode))




/******************************************************************************
 * @brief      APWM output is active high
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define  ECAP_SetAPWMOutputActiveHigh(ECAPx)       ((ECAPx)->CAPCTL |= CAPCTL_APWMPOL_ACTIVE_HIGH)





/******************************************************************************
 * @brief      APWM output is active low
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetAPWMOutputActiveLow(ECAPx)        ((ECAPx)->CAPCTL &= ~CAPCTL_APWMPOL_Msk)




/******************************************************************************
 * @brief      Set APWM output polarity
 *
 * @param[in]  ECAPx    :  Select the ECAP module
 * @param[in]  ePinLevel:  Select the GPIO pin level for active output
 *                         Please refer to GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetAPWMOutputPolarity(ECAPx,ePinLevel)   WRITE_FIELD( (ECAPx)->CAPCTL, CAPCTL_APWMPOL_Msk, CAPCTL_APWMPOL_Pos, (ePinLevel) )




/******************************************************************************
 * @brief      Get APWM output polarity
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_GetAPWMOutputPolarity(ECAPx)   READ_FIELD( (ECAPx)->CAPCTL, CAPCTL_APWMPOL_Msk, CAPCTL_APWMPOL_Pos )




/******************************************************************************
 * @brief      Software force counter synchronizing
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_ForceSync(ECAPx)               ((ECAPx)->CAPCTL |= CAPCTL_FRCSYNC_FORCE)




/******************************************************************************
 * @brief      Set ECAP SYNC output
 *
 * @param[in]  ECAPx   :  Select the ECAP module
 * @param[in]  eSyncOut:  SYNC output options
 *                        Please refer to ECAP_SyncOutEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetSyncOut(ECAPx, eSyncOut)    ((ECAPx)->CAPCTL = ((ECAPx)->CAPCTL & ~CAPCTL_SYNCOSEL_Msk) | ((eSyncOut) << CAPCTL_SYNCOSEL_Pos))




/******************************************************************************
 * @brief      Enable phase synchronization
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_EnableSync(ECAPx)              ((ECAPx)->CAPCTL |= CAPCTL_PHSEN_ENABLE)




/******************************************************************************
 * @brief      Disable phase synchronization
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_DisableSync(ECAPx)             ((ECAPx)->CAPCTL &= ~CAPCTL_PHSEN_Msk)




/******************************************************************************
 * @brief      ECAP Run Counter
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_RunCounter(ECAPx)              ((ECAPx)->CAPCTL |= CAPCTL_TSCNTRUN_START_COUNTER)




/******************************************************************************
 * @brief      ECAP Stop Counter
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_StopCounter(ECAPx)             ((ECAPx)->CAPCTL &= ~CAPCTL_TSCNTRUN_Msk)




/******************************************************************************
 * @brief      One-shot Re-Arming
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_OneshotReArm(ECAPx)            ((ECAPx)->CAPCTL |= CAPCTL_REARM_FORCE)





/******************************************************************************
 * @brief      Set stop/wrap event
 *
 * @param[in]  ECAPx :  Select the ECAP module
 * @param[in]  eEvent:  ECAP event at which capture event counter stops or wraps
 *                      Please refer to ECAP_EventEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetStopWrapEvent(ECAPx, eEvent)    ((ECAPx)->CAPCTL = ((ECAPx)->CAPCTL & ~CAPCTL_STOPWRAP_Msk) | ((eEvent) << CAPCTL_STOPWRAP_Pos))





/******************************************************************************
 * @brief      Operate in one-shot mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_EnableOneshotMode(ECAPx)       ((ECAPx)->CAPCTL |= CAPCTL_ONESHOT_ENABLE)




/******************************************************************************
 * @brief      Operate in continuous mode
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_DisableOneshotMode(ECAPx)      ((ECAPx)->CAPCTL &= ~CAPCTL_ONESHOT_Msk)




/******************************************************************************
 * @brief      Set event filter prescale
 *
 * @param[in]  ECAPx:  Select the ECAP module
 * @param[in]  u8Div:  Event filter prescale (1 ~ 256)
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetEventDiv(ECAPx,u8Div)       ((ECAPx)->CAPCTL = ((ECAPx)->CAPCTL & ~CAPCTL_EVTDIV_Msk) | CAPCTL_EVTDIV_(u8Div - 1))




/******************************************************************************
 * @brief      Reset event divider counter
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_ResetEventDivider(ECAPx)       SET_BITS((ECAPx)->CAPCTL, CAPCTL_EVTDIVRST_Msk)




/******************************************************************************
 * @brief      Enable load captured counter value into CAPx registers
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_EnableLoadCapture(ECAPx)       ((ECAPx)->CAPCTL |= CAPCTL_CAPLDEN_ENABLE)




/******************************************************************************
 * @brief      Disable load captured counter value into CAPx registers
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_DisableLoadCapture(ECAPx)       ((ECAPx)->CAPCTL &= ~CAPCTL_CAPLDEN_Msk)




/******************************************************************************
 * @brief      Enable counter reset on capture event
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eCapEvt:  Select the capture event
 *                       Please refer to ECAP_EventEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_EnableEventResetCounter(ECAPx,eCapEvt)   ((ECAPx)->CAPCTL |= (CAPCTL_CNTRST0_ENABLE << ((eCapEvt) << 1)))




/******************************************************************************
 * @brief      Disable counter reset on capture event
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eCapEvt:  Select the capture event
 *                       Please refer to ECAP_EventEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_DisableEventResetCounter(ECAPx,eCapEvt)  ((ECAPx)->CAPCTL &= ~(CAPCTL_CNTRST0_ENABLE << ((eCapEvt) << 1)))




/******************************************************************************
 * @brief      Capture event triggered edge
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eCapEvt:  Select the capture event
 *                       Please refer to ECAP_EventEnum
 * @param[in]  eEdge:  Select the capture edge
 *                       Please refer to GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_SetEventTriggeredEdge(ECAPx,eCapEvt,eEdge)                        \
    MODIFY_REG((ECAPx)->CAPCTL, (1 << ((eCapEvt) << 1)), ((eEdge) << ((eCapEvt) << 1)))




/******************************************************************************
 * @brief      Get event event raw flag
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eIntEvt:  Select the interrupt event, ORed of ECAP_IntEnum
 *                       Please refer to ECAP_IntEnum
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for non-zero bit occurred
 *
 ******************************************************************************/
#define ECAP_GetIntRawFlag(ECAPx, eIntEvt)  ((ECAPx)->CAPRAWIF & (eIntEvt))




/******************************************************************************
 * @brief      Get event interrupt flag
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eIntEvt:  Select the interrupt event, ORed of ECAP_IntEnum
 *                       Please refer to ECAP_IntEnum
 *
 * @return     0     - None of the queried interrupts occurred
 *             not 0 - Corresponding interrupts for non-zero bit occurred
 *
 ******************************************************************************/
#define ECAP_GetIntFlag(ECAPx, eIntEvt)     ((ECAPx)->CAPIF & (eIntEvt))




/******************************************************************************
 * @brief      Enable event interrupt
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eIntEvt:  Select the interrupt event, ORed of ECAP_IntEnum
 *                       Please refer to ECAP_IntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_EnableInt(ECAPx,eIntEvt)       ((ECAPx)->CAPIE |= (eIntEvt))




/******************************************************************************
 * @brief      Disable event interrupt
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eIntEvt:  Select the interrupt event, ORed of ECAP_IntEnum
 *                       Please refer to ECAP_IntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_DisableInt(ECAPx,eIntEvt)      ((ECAPx)->CAPIE &= ~(eIntEvt))




/******************************************************************************
 * @brief      Clear event interrupt
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eIntEvt:  Select the interrupt event, ORed of ECAP_IntEnum
 *                       Please refer to ECAP_IntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_ClearInt(ECAPx,eIntEvt)        ((ECAPx)->CAPIC = (eIntEvt))




/******************************************************************************
 * @brief      Force event interrupt
 *
 * @param[in]  ECAPx  :  Select the ECAP module
 * @param[in]  eIntEvt:  Select the interrupt event, ORed of ECAP_IntEnum
 *                       Please refer to ECAP_IntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_ForceInt(ECAPx,eIntEvt)        ((ECAPx)->CAPIFRC = (eIntEvt) | ((eIntEvt) << 8))




/******************************************************************************
 * @brief      Enable write access to the protected CLOCK registers
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_WALLOW(ECAPx)                  ((ECAPx)->CAPREGKEY = 0x1ACCE551UL)




/******************************************************************************
 * @brief      Disable write access to the protected CLOCK registers
 *
 * @param[in]  ECAPx:  Select the ECAP module
 *
 * @return     None
 *
 ******************************************************************************/
#define ECAP_WDIS(ECAPx)                    ((ECAPx)->CAPREGKEY = 0x0UL)




/**
 *  @brief ECAP Public Function Declaration
 */
void ECAP_InitSyncIO(ECAP_REGS *ECAPx, PIN_NameEnum ePinName, LEVEL eLvl);
void ECAP_InitCaptureIO(ECAP_REGS *ECAPx, PIN_NameEnum ePinName, LEVEL eLvl);
void ECAP_CaptureModeInit(ECAP_REGS *ECAPx, PIN_NameEnum ePinName);

void ECAP_APWMModeInit(ECAP_REGS *ECAPx, uint32_t u32PwmFreq, uint32_t u32PwmDuty, LEVEL ePinLevel);
void ECAP_APWMSetDuty(ECAP_REGS *ECAPx, uint32_t u32PwmDuty);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ECAP_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
