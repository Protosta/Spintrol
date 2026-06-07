/******************************************************************************
 * @file     pwm.h
 * @brief    PWM driver header file.
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
 *
 * @attention
 * THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION REGARDING
 * THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM. SPINTROL S NOT BE
 * LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL DOES NOT GUARANTEE THE
 * CORRECTNESS OF THIS SOFTWARE AND RESERVES THE RIGHT TO MODIFY THE SOFTWARE
 * WITHOUT NOTIFICATION.
 *
 ******************************************************************************/


#ifndef PWM_H
#define PWM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  PWM Module Index for single selection
 */
typedef enum
{
    SEL_PWM0              = 0,            /*!< PWM0            */
    SEL_PWM1              = 1,            /*!< PWM1            */
    SEL_PWM2              = 2,            /*!< PWM2            */
    SEL_PWM3              = 3             /*!< PWM3            */
} PWM_SelEnum;




/**
 *  @brief  PWM Module Index for muitiple selection (Can be ORed)
 */
typedef enum
{
    INC_PWM0              = 0x01UL,       /*!< PWM0            */
    INC_PWM1              = 0x02UL,       /*!< PWM1            */
    INC_PWM2              = 0x04UL,       /*!< PWM2            */
    INC_PWM3              = 0x08UL        /*!< PWM3            */
} PWM_IncEnum;




/**
 *  @brief  PWM channel A or B select type
 */
typedef enum
{
    PWM_CHA               = 0,            /*!< PWM Channel A define     */
    PWM_CHB               = 1             /*!< PWM Channel B define     */
} PWM_ChannelEnum;




/**
 *  @brief  PWM count mode selection
 */
typedef enum
{
    COUNT_DOWN            = 0U,           /*!< Down-count      */
    COUNT_UP              = 1U,           /*!< Up-count        */
    COUNT_UP_DOWN         = 2U,           /*!< Up-down-count   */
    COUNT_STOP            = 3U,           /*!< Stop and freeze */
} PWM_CounterModeEnum;




/**
 *  @brief  PWM clock divider binary part selection
 */
typedef enum
{
    PWM_CLKDIV0_1         = TBCTL_TBPDIV_1,       /*!< /1 (default on reset) */
    PWM_CLKDIV0_2         = TBCTL_TBPDIV_2,       /*!< /2                    */
    PWM_CLKDIV0_4         = TBCTL_TBPDIV_4,       /*!< /4                    */
    PWM_CLKDIV0_8         = TBCTL_TBPDIV_8,       /*!< /8                    */
    PWM_CLKDIV0_16        = TBCTL_TBPDIV_16,      /*!< /16                   */
    PWM_CLKDIV0_32        = TBCTL_TBPDIV_32,      /*!< /32                   */
    PWM_CLKDIV0_64        = TBCTL_TBPDIV_64,      /*!< /64                   */
    PWM_CLKDIV0_128       = TBCTL_TBPDIV_128,     /*!< /128                  */
} PWM_ClockDiv0Enum;




/**
 *  @brief  PWM clock divider linear part selection
 */
typedef enum
{
    PWM_CLKDIV1_1         = TBCTL_TBDIV_1,       /*!< /1 (default on reset) */
    PWM_CLKDIV1_2         = TBCTL_TBDIV_2,       /*!< /2                    */
    PWM_CLKDIV1_3         = TBCTL_TBDIV_3,       /*!< /3                    */
    PWM_CLKDIV1_4         = TBCTL_TBDIV_4,       /*!< /4                    */
    PWM_CLKDIV1_5         = TBCTL_TBDIV_5,       /*!< /5                    */
    PWM_CLKDIV1_6         = TBCTL_TBDIV_6,       /*!< /6                    */
    PWM_CLKDIV1_7         = TBCTL_TBDIV_7,       /*!< /7                    */
    PWM_CLKDIV1_8         = TBCTL_TBDIV_8,       /*!< /8                    */
} PWM_ClockDiv1Enum;




/**
 *  @brief  PWM time-base event selection
 */
typedef enum
{
    SYNCI_EVENT           = TBFLG_SYNCI_EVENT_OCCUR,  /*!< SYNCI event occurred   */
    COUNTER_HIT_MAX       = TBFLG_CNTMAX_REACHED,     /*!< TBCNT = 0xFFFF         */
    COUNTER_HIT_ZRO       = TBFLG_CNTZRO_REACHED,     /*!< TBCNT = 0              */
    COUNTER_HIT_PRD       = TBFLG_CNTPRD_REACHED,     /*!< TBCNT = TBPRD          */
    COUNTER_HIT_CMPA      = TBFLG_CNTCMPA_REACHED,    /*!< TBCNT = CMPA           */
    COUNTER_HIT_CMPB      = TBFLG_CNTCMPB_REACHED,    /*!< TBCNT = CMPB           */
    COUNTER_HIT_CMPC      = TBFLG_CNTCMPC_REACHED,    /*!< TBCNT = CMPC           */
    COUNTER_HIT_CMPD      = TBFLG_CNTCMPD_REACHED,    /*!< TBCNT = CMPD           */
} PWM_TimeBaseEventEnum;




/**
 *  @brief  PWM event-trigger period selection
 */
typedef enum
{
    NO_EVENT              = 0U,           /*!< Disable event counter. No event pulse will be generated */
    ON_1ST_EVENT          = 1U,           /*!< Generate pulse on first event      */
    ON_2ND_EVENT          = 2U,           /*!< Generate pulse on second event     */
    ON_3RD_EVENT          = 3U,           /*!< Generate pulse on third event      */
    ON_4TH_EVENT          = 4U,           /*!< Generate pulse on fourth event     */
    ON_5TH_EVENT          = 5U,           /*!< Generate pulse on fifth event      */
    ON_6TH_EVENT          = 6U,           /*!< Generate pulse on sixth event      */
    ON_7TH_EVENT          = 7U,           /*!< Generate pulse on seventh event    */
    ON_8TH_EVENT          = 8U,           /*!< Generate pulse on eighth event     */
    ON_9TH_EVENT          = 9U,           /*!< Generate pulse on ninth event      */
    ON_10TH_EVENT         = 10U,          /*!< Generate pulse on tenth event      */
    ON_11TH_EVENT         = 11U,          /*!< Generate pulse on eleventh event   */
    ON_12TH_EVENT         = 12U,          /*!< Generate pulse on twelfth event    */
    ON_13TH_EVENT         = 13U,          /*!< Generate pulse on thirteenth event */
    ON_14TH_EVENT         = 14U,          /*!< Generate pulse on fourteenth event */
    ON_15TH_EVENT         = 15U           /*!< Generate pulse on fifteenth event  */
} PWM_EventPeriodEnum;




/**
 *  @brief  PWM edge type
 */
typedef enum
{
    PWM_FALLING_EDGE_DELAY_PATH            = 0,          /*!< PWM negative edge     */
    PWM_RISING_EDGE_DELAY_PATH             = 1           /*!< PWM positive edge     */
} PWM_DeadBandOutputSourceEnum;




/**
 *  @brief  PWM Force output target type
 */
typedef enum
{
    PWM_FRC_ON_CHA              = 1U,       /*!< Force CHA                      */
    PWM_FRC_ON_CHB              = 2U,       /*!< Force CHB                      */
    PWM_FRC_ON_CHA_AND_CHB      = 3U,       /*!< Force CHA and CHB              */
} PWM_ForceTargetEnum;




/**
 *  @brief  PWM SOC and INT event selection
 */
typedef enum
{
    EQU_ZERO                = 0U,         /*!< Event TBCNT=0                                */
    EQU_PERIOD              = 1U,         /*!< Event TBCNT=TBPRD                            */
    EQU_ZERO_PERIOD         = 2U,         /*!< Event TBCNT=0 or TBCNT=TBPRD                 */
    EQU_CMPA_UP_COUNTING    = 3U,         /*!< Event TBCNT=CMPA when TBCNT is counting up   */
    EQU_CMPA_DOWN_COUNTING  = 4U,         /*!< Event TBCNT=CMPA when TBCNT is counting down */
    EQU_CMPB_UP_COUNTING    = 5U,         /*!< Event TBCNT=CMPB when TBCNT is counting up   */
    EQU_CMPB_DOWN_COUNTING  = 6U,         /*!< Event TBCNT=CMPB when TBCNT is counting down */
    EQU_CMPC_UP_COUNTING    = 7U,         /*!< Event TBCNT=CMPC when TBCNT is counting up   */
    EQU_CMPC_DOWN_COUNTING  = 8U,         /*!< Event TBCNT=CMPC when TBCNT is counting down */
    EQU_CMPD_UP_COUNTING    = 9U,         /*!< Event TBCNT=CMPD when TBCNT is counting up   */
    EQU_CMPD_DOWN_COUNTING  = 10U,        /*!< Event TBCNT=CMPD when TBCNT is counting down */
    DCAEVT0_SOC             = 11U,        /*!< Event DCAEVT0.SOC                            */
    DCBEVT0_SOC             = 12U,        /*!< Event DCBEVT0.SOC                            */
} PWM_EventTimingEnum;




/**
 *  @brief  PWM output A and B action after trip event occurs
 */
typedef enum
{
    /* Action on PWM output when digital compare A/B event 1 occur and TBCNT is counting down */
    DCEVT1D_TRIP_AS_TRI_STATE       = TZACTL_DCAEVT1D_TRI_STATE,
    DCEVT1D_TRIP_AS_LOW             = TZACTL_DCAEVT1D_SET_LOW,
    DCEVT1D_TRIP_AS_HIGH            = TZACTL_DCAEVT1D_SET_HIGH,
    DCEVT1D_TRIP_AS_TOGGLE          = TZACTL_DCAEVT1D_TOGGLE,
    DCEVT1D_TRIP_DO_NOTHING         = TZACTL_DCAEVT1D_DO_NOTHING,

    /* Action on PWM output when digital compare A/B event 1 occur and TBCNT is counting up */
    DCEVT1U_TRIP_AS_TRI_STATE       = TZACTL_DCAEVT1U_TRI_STATE,
    DCEVT1U_TRIP_AS_LOW             = TZACTL_DCAEVT1U_SET_LOW,
    DCEVT1U_TRIP_AS_HIGH            = TZACTL_DCAEVT1U_SET_HIGH,
    DCEVT1U_TRIP_AS_TOGGLE          = TZACTL_DCAEVT1U_TOGGLE,
    DCEVT1U_TRIP_DO_NOTHING         = TZACTL_DCAEVT1U_DO_NOTHING,

    /* Action on PWM output when digital compare A/B event 0 occur and TBCNT is counting down */
    DCEVT0D_TRIP_AS_TRI_STATE       = TZACTL_DCAEVT0D_TRI_STATE,
    DCEVT0D_TRIP_AS_LOW             = TZACTL_DCAEVT0D_SET_LOW,
    DCEVT0D_TRIP_AS_HIGH            = TZACTL_DCAEVT0D_SET_HIGH,
    DCEVT0D_TRIP_AS_TOGGLE          = TZACTL_DCAEVT0D_TOGGLE,
    DCEVT0D_TRIP_DO_NOTHING         = TZACTL_DCAEVT0D_DO_NOTHING,

    /* Action on PWM output when digital compare A/B event 0 occur and TBCNT is counting up */
    DCEVT0U_TRIP_AS_TRI_STATE       = TZACTL_DCAEVT0U_TRI_STATE,
    DCEVT0U_TRIP_AS_LOW             = TZACTL_DCAEVT0U_SET_LOW,
    DCEVT0U_TRIP_AS_HIGH            = TZACTL_DCAEVT0U_SET_HIGH,
    DCEVT0U_TRIP_AS_TOGGLE          = TZACTL_DCAEVT0U_TOGGLE,
    DCEVT0U_TRIP_DO_NOTHING         = TZACTL_DCAEVT0U_DO_NOTHING,

    /* Action on PWM output when a trip event occur and TBCNT is counting down */
    TZD_TRIP_AS_TRI_STATE           = TZACTL_TZD_TRI_STATE,
    TZD_TRIP_AS_LOW                 = TZACTL_TZD_SET_LOW,
    TZD_TRIP_AS_HIGH                = TZACTL_TZD_SET_HIGH,
    TZD_TRIP_AS_TOGGLE              = TZACTL_TZD_TOGGLE,
    TZD_TRIP_DO_NOTHING             = TZACTL_TZD_DO_NOTHING,

    /* Action on PWM output when a trip event occur and TBCNT is counting up */
    TZU_TRIP_AS_TRI_STATE           = TZACTL_TZU_TRI_STATE,
    TZU_TRIP_AS_LOW                 = TZACTL_TZU_SET_LOW,
    TZU_TRIP_AS_HIGH                = TZACTL_TZU_SET_HIGH,
    TZU_TRIP_AS_TOGGLE              = TZACTL_TZU_TOGGLE,
    TZU_TRIP_DO_NOTHING             = TZACTL_TZU_DO_NOTHING
} PWM_TripActionEnum;




/**
 *  @brief  PWM Action-Qualifier output when event occurs
 */
typedef enum
{
    /* Action on PWM output when T1 event occur and TBCNT is counting down */
    T1D_DO_NOTHING        = AQCTLA_T1D_DO_NOTHING,
    T1D_SET_LOW           = AQCTLA_T1D_SET_LOW,
    T1D_SET_HIGH          = AQCTLA_T1D_SET_HIGH,
    T1D_TOGGLE            = AQCTLA_T1D_TOGGLE,

    /* Action on PWM output when T1 event occur and TBCNT is counting up */
    T1U_DO_NOTHING        = AQCTLA_T1U_DO_NOTHING,
    T1U_SET_LOW           = AQCTLA_T1U_SET_LOW,
    T1U_SET_HIGH          = AQCTLA_T1U_SET_HIGH,
    T1U_TOGGLE            = AQCTLA_T1U_TOGGLE,

    /* Action on PWM output when T0 event occur and TBCNT is counting down */
    T0D_DO_NOTHING        = AQCTLA_T0D_DO_NOTHING,
    T0D_SET_LOW           = AQCTLA_T0D_SET_LOW,
    T0D_SET_HIGH          = AQCTLA_T0D_SET_HIGH,
    T0D_TOGGLE            = AQCTLA_T0D_TOGGLE,

    /* Action on PWM output when T1 event occur and TBCNT is counting up */
    T0U_DO_NOTHING        = AQCTLA_T0U_DO_NOTHING,
    T0U_SET_LOW           = AQCTLA_T0U_SET_LOW,
    T0U_SET_HIGH          = AQCTLA_T0U_SET_HIGH,
    T0U_TOGGLE            = AQCTLA_T0U_TOGGLE,

    /* Action on PWM output when TBCNT = CMPB and TBCNT is counting down */
    CBD_DO_NOTHING        = AQCTLA_CBD_DO_NOTHING,
    CBD_SET_LOW           = AQCTLA_CBD_SET_LOW,
    CBD_SET_HIGH          = AQCTLA_CBD_SET_HIGH,
    CBD_TOGGLE            = AQCTLA_CBD_TOGGLE,

    /* Action on PWM output when TBCNT = CMPB and TBCNT is counting up */
    CBU_DO_NOTHING        = AQCTLA_CBU_DO_NOTHING,
    CBU_SET_LOW           = AQCTLA_CBU_SET_LOW,
    CBU_SET_HIGH          = AQCTLA_CBU_SET_HIGH,
    CBU_TOGGLE            = AQCTLA_CBU_TOGGLE,

    /* Action on PWM output when TBCNT = CMPA and TBCNT is counting down */
    CAD_DO_NOTHING        = AQCTLA_CAD_DO_NOTHING,
    CAD_SET_LOW           = AQCTLA_CAD_SET_LOW,
    CAD_SET_HIGH          = AQCTLA_CAD_SET_HIGH,
    CAD_TOGGLE            = AQCTLA_CAD_TOGGLE,

    /* Action on PWM output when TBCNT = CMPA and TBCNT is counting up */
    CAU_DO_NOTHING        = AQCTLA_CAU_DO_NOTHING,
    CAU_SET_LOW           = AQCTLA_CAU_SET_LOW,
    CAU_SET_HIGH          = AQCTLA_CAU_SET_HIGH,
    CAU_TOGGLE            = AQCTLA_CAU_TOGGLE,

    /* Action on PWM output when TBCNT = TBPRD */
    PRD_DO_NOTHING        = AQCTLA_PRD_DO_NOTHING,
    PRD_SET_LOW           = AQCTLA_PRD_SET_LOW,
    PRD_SET_HIGH          = AQCTLA_PRD_SET_HIGH,
    PRD_TOGGLE            = AQCTLA_PRD_TOGGLE,

    /* Action on PWM output when TBCNT = Zero */
    ZRO_DO_NOTHING        = AQCTLA_ZRO_DO_NOTHING,
    ZRO_SET_LOW           = AQCTLA_ZRO_SET_LOW,
    ZRO_SET_HIGH          = AQCTLA_ZRO_SET_HIGH,
    ZRO_TOGGLE            = AQCTLA_ZRO_TOGGLE,

    /* PWM Force operation */
    FRC_DO_NOTHING               = 0U,       /*!< Do nothing (action disabled)                              */
    FRC_SET_LOW                  = 1U,       /*!< Clear (force PWM output B to low                          */
    FRC_SET_HIGH                 = 2U,       /*!< Set (force PWM output B to high                           */
    FRC_TOGGLE                   = 3U,       /*!< Toggle (invert current PWM AQ output B status)            */
} PWM_ActionQualifierEnum;




/**
 *  @brief  PWM CMPA/B/C/D and AQCTLA/B reload timing selection
 */
typedef enum
{
    GLOBAL_LOAD_ON_ZERO             = 0UL,      /*!< Load on TBCNT=Zero                            */
    GLOBAL_LOAD_ON_PERIOD           = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    GLOBAL_LOAD_ON_ZERO_PERIOD      = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    GLOBAL_LOAD_ON_SYNC             = 3UL,      /*!< Load on SYNC event                            */
    GLOBAL_LOAD_ON_SYNC_ZERO        = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    GLOBAL_LOAD_ON_SYNC_PERIOD      = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    GLOBAL_LOAD_ON_SYNC_ZERO_PERIOD = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    GLOBAL_LOAD_ON_FORCE            = 7UL,      /*!< Load on software forced strobe pulse          */
    
    TBPRD_LOAD_ON_ZERO              = 0UL,      /*!< Load on TBCNT=Zero                            */
    TBPRD_LOAD_ON_SYNC              = 1UL,      /*!< Load on SYNC event                            */
    TBPRD_LOAD_ON_SYNC_ZERO         = 2UL,      /*!< Load on SYNC event or TBCNT=0                 */
    TBPRD_LOAD_ON_IMMEDIATE         = 3UL,      /*!< Load on immediately                           */
    
    CMPA_LOAD_ON_ZERO               = 0UL,      /*!< Load on TBCNT=Zero                            */
    CMPA_LOAD_ON_PERIOD             = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    CMPA_LOAD_ON_ZERO_PERIOD        = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    CMPA_LOAD_ON_SYNC               = 3UL,      /*!< Load on SYNC event                            */
    CMPA_LOAD_ON_SYNC_ZERO          = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    CMPA_LOAD_ON_SYNC_PERIOD        = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    CMPA_LOAD_ON_SYNC_ZERO_PERIOD   = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    CMPA_LOAD_ON_IMMEDIATE          = 7UL,      /*!< Load on immediately                           */

    CMPB_LOAD_ON_ZERO               = 0UL,      /*!< Load on TBCNT=Zero                            */
    CMPB_LOAD_ON_PERIOD             = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    CMPB_LOAD_ON_ZERO_PERIOD        = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    CMPB_LOAD_ON_SYNC               = 3UL,      /*!< Load on SYNC event                            */
    CMPB_LOAD_ON_SYNC_ZERO          = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    CMPB_LOAD_ON_SYNC_PERIOD        = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    CMPB_LOAD_ON_SYNC_ZERO_PERIOD   = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    CMPB_LOAD_ON_IMMEDIATE          = 7UL,      /*!< Load on immediately                           */

    CMPC_LOAD_ON_ZERO               = 0UL,      /*!< Load on TBCNT=Zero                            */
    CMPC_LOAD_ON_PERIOD             = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    CMPC_LOAD_ON_ZERO_PERIOD        = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    CMPC_LOAD_ON_SYNC               = 3UL,      /*!< Load on SYNC event                            */
    CMPC_LOAD_ON_SYNC_ZERO          = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    CMPC_LOAD_ON_SYNC_PERIOD        = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    CMPC_LOAD_ON_SYNC_ZERO_PERIOD   = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    CMPC_LOAD_ON_IMMEDIATE          = 7UL,      /*!< Load on immediately                           */

    CMPD_LOAD_ON_ZERO               = 0UL,      /*!< Load on TBCNT=Zero                            */
    CMPD_LOAD_ON_PERIOD             = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    CMPD_LOAD_ON_ZERO_PERIOD        = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    CMPD_LOAD_ON_SYNC               = 3UL,      /*!< Load on SYNC event                            */
    CMPD_LOAD_ON_SYNC_ZERO          = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    CMPD_LOAD_ON_SYNC_PERIOD        = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    CMPD_LOAD_ON_SYNC_ZERO_PERIOD   = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    CMPD_LOAD_ON_IMMEDIATE          = 7UL,      /*!< Load on immediately                           */
    
    AQCTLA_LOAD_ON_ZERO             = 0UL,      /*!< Load on TBCNT=Zero                            */
    AQCTLA_LOAD_ON_PERIOD           = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    AQCTLA_LOAD_ON_ZERO_PERIOD      = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    AQCTLA_LOAD_ON_SYNC             = 3UL,      /*!< Load on SYNC event                            */
    AQCTLA_LOAD_ON_SYNC_ZERO        = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    AQCTLA_LOAD_ON_SYNC_PERIOD      = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    AQCTLA_LOAD_ON_SYNC_ZERO_PERIOD = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    AQCTLA_LOAD_ON_IMMEDIATE        = 7UL,      /*!< Load on immediately                           */

    AQCTLB_LOAD_ON_ZERO             = 0UL,      /*!< Load on TBCNT=Zero                            */
    AQCTLB_LOAD_ON_PERIOD           = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    AQCTLB_LOAD_ON_ZERO_PERIOD      = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    AQCTLB_LOAD_ON_SYNC             = 3UL,      /*!< Load on SYNC event                            */
    AQCTLB_LOAD_ON_SYNC_ZERO        = 4UL,      /*!< Load on SYNC event or TBCNT=0                 */
    AQCTLB_LOAD_ON_SYNC_PERIOD      = 5UL,      /*!< Load on SYNC event or TBCNT=TBPRD             */
    AQCTLB_LOAD_ON_SYNC_ZERO_PERIOD = 6UL,      /*!< Load on SYNC event, TBCNT=Zero or TBCNT=TBPRD */
    AQCTLB_LOAD_ON_IMMEDIATE        = 7UL,      /*!< Load on immediately                           */
    
    AQCSFRC_LOAD_ON_ZERO            = 0UL,      /*!< Load on TBCNT=Zero                            */
    AQCSFRC_LOAD_ON_PERIOD          = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    AQCSFRC_LOAD_ON_ZERO_PERIOD     = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    AQCSFRC_LOAD_ON_IMMEDIATE       = 3UL,      /*!< Load on immediately                           */
    
    DBCTL_LOAD_ON_ZERO              = 0UL,      /*!< Load on TBCNT=Zero                            */
    DBCTL_LOAD_ON_PERIOD            = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    DBCTL_LOAD_ON_ZERO_PERIOD       = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    DBCTL_LOAD_ON_IMMEDIATE         = 3UL,      /*!< Load on immediately                           */
    
    DBRED_LOAD_ON_ZERO              = 0UL,      /*!< Load on TBCNT=Zero                            */
    DBRED_LOAD_ON_PERIOD            = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    DBRED_LOAD_ON_ZERO_PERIOD       = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    DBRED_LOAD_ON_IMMEDIATE         = 3UL,      /*!< Load on immediately                           */
    
    DBFED_LOAD_ON_ZERO              = 0UL,      /*!< Load on TBCNT=Zero                            */
    DBFED_LOAD_ON_PERIOD            = 1UL,      /*!< Load on TBCNT=TBPRD                           */
    DBFED_LOAD_ON_ZERO_PERIOD       = 2UL,      /*!< Load on either TBCNT=Zero or TBCNT=TBPRD      */
    DBFED_LOAD_ON_IMMEDIATE         = 3UL,      /*!< Load on immediately                           */
} PWM_LoadTimingEnum;




/**
 *  @brief  PWM T0 and T1 event selection
 */
typedef enum
{
    TxEVENT_DCAEVT0       = 0U,           /*!< DCAEVT0 event */
    TxEVENT_DCAEVT1       = 1U,           /*!< DCAEVT1 event */
    TxEVENT_DCBEVT0       = 2U,           /*!< DCBEVT0 event */
    TxEVENT_DCBEVT1       = 3U,           /*!< DCBEVT1 event */
    TxEVENT_TZ0           = 4U,           /*!< TZ0 event     */
    TxEVENT_TZ1           = 5U,           /*!< TZ1 event     */
    TxEVENT_TZ2           = 6U,           /*!< TZ2 event     */
    TxEVENT_TZ3           = 7U,           /*!< TZ3 event     */
    TxEVENT_TZ4           = 8U,           /*!< TZ4 event     */
    TxEVENT_SYNCI         = 9U,           /*!< SYNCI event   */
} PWM_TxEventEnum;




/**
 *  @brief  PWM trip-zone event selection
 */
typedef enum
{
    TRIP_EVENT_NONE       = 0U,              /*!< Disable all trip-zone events             */
    TRIP_EVENT_TZ0        = (1U << 0),       /*!< TZ0                                      */
    TRIP_EVENT_TZ1        = (1U << 1),       /*!< TZ1                                      */
    TRIP_EVENT_TZ2        = (1U << 2),       /*!< TZ2                                      */
    TRIP_EVENT_TZ3        = (1U << 3),       /*!< TZ3                                      */
    TRIP_EVENT_TZ4        = (1U << 4),       /*!< TZ4                                      */
    TRIP_EVENT_CLKERR     = (1U << 5),       /*!< CLKERR                                   */
    TRIP_EVENT_DCAEVT     = (1U << 6),       /*!< DCAEVT0 for oneshot and DCAEVT1 for CBC  */
    TRIP_EVENT_DCBEVT     = (1U << 7),       /*!< DCBEVT0 for oneshot and DCBEVT1 for CBC  */
    TRIP_EVENT_DEBUG      = (1U << 8)        /*!< DEBUG event                              */
} PWM_TripEventEnum;




/**
 *  @brief  PWM trip-zone interrupt event selection
 */
typedef enum
{
    TRIP_INT_OST        = (1U << 0),   /*!< One-shot trip-zone interrupt event     */
    TRIP_INT_CBC        = (1U << 1),   /*!< CBC trip-zone interrupt event          */
    TRIP_INT_DCAEVT0    = (1U << 2),   /*!< DCAEVT0 trip-zone interrupt event      */
    TRIP_INT_DCAEVT1    = (1U << 3),   /*!< DCAEVT1 trip-zone interrupt event      */
    TRIP_INT_DCBEVT0    = (1U << 4),   /*!< DCBEVT0 trip-zone interrupt event      */
    TRIP_INT_DCBEVT1    = (1U << 5),   /*!< DCBEVT1 trip-zone interrupt event      */
    TRIP_INT_GLOBAL     = (1U << 6),   /*!< GLOBAL interrupt event                 */
    TRIP_INT_ALL        = (0x7FU),     /*!< All interrupt event                    */
} PWM_TripIntEnum;




/**
 *  @brief  PWM Trip-zone output select
 */
typedef enum
{
    TRIP_OUTPUT_DISABLE         = 0UL,        /*!< Disable                             */
    TRIP_OUTPUT_ASYNC           = 1UL,        /*!< Async (Used only for debug purpose) */
    TRIP_OUTPUT_LATCH           = 2UL,        /*!< Latch                               */
    TRIP_OUTPUT_ASYNC_OR_LATCH  = 3UL,        /*!< Async or Latch                      */
} PWM_TripOutputEnum;




/**
 *  @brief  PWM DC trip event selection
 */
typedef enum
{
    DC_TRIP_TZ0           = (1U <<  0),       /*!< TZ0             */
    DC_TRIP_TZ1           = (1U <<  1),       /*!< TZ1             */
    DC_TRIP_TZ2           = (1U <<  2),       /*!< TZ2             */
    DC_TRIP_TZ3           = (1U <<  3),       /*!< TZ3             */
    DC_TRIP_TZ4           = (1U <<  4),       /*!< TZ4             */
    DC_TRIP_EPWRTZ0       = (1U <<  5),       /*!< EPWRTZ0         */
    DC_TRIP_EPWRTZ1       = (1U <<  6),       /*!< EPWRTZ1         */
    DC_TRIP_ADCPPU0TZ     = (1U <<  8),       /*!< ADCPPU0TZ       */
    DC_TRIP_ADCPPU1TZ     = (1U <<  9),       /*!< ADCPPU1TZ       */
    DC_TRIP_ADCPPU2TZ     = (1U << 10),       /*!< ADCPPU2TZ       */
    DC_TRIP_COMP0L        = (1U << 16),       /*!< COMP0L          */
    DC_TRIP_COMP0H        = (1U << 17),       /*!< COMP0H          */
} PWM_DCTripEventEnum;




/**
 *  @brief  PWM Raw DCA/B event selection
 */
typedef enum
{
    DCEVT_DISABLE         = 0,                /*!< Disable, do not generate event   */
    DCH_X_DCL_LOW         = 1,                /*!< DCAH=dont'care,  DCAL=low        */
    DCH_X_DCL_HIGH        = 2,                /*!< DCAH=dont'care,  DCAL=high       */
    DCH_LOW_DCL_X         = 3,                /*!< DCAH=low,        DCAL=dont'care  */
    DCH_HIGH_DCL_X        = 4,                /*!< DCAH=high,       DCAL=dont'care  */
    DCH_HIGH_DCL_LOW      = 5,                /*!< DCAH=high,       DCAL=low        */
    DCH_LOW_DCL_HIGH      = 6,                /*!< DCAH=low,        DCAL=high       */
    DCH_HIGH_DCL_HIGH     = 7,                /*!< DCAH=high,       DCAL=high       */
} PWM_RawDCEventEnum;




/**
 *  @brief  PWM final DCA/B event selection
 */
typedef enum
{
    DCEVT_RAW             = 0,                /*!< From Raw DC event                */
    DCEVT_FILTERED        = 1,                /*!< From Filtered DC event           */
} PWM_DCEventEnum;




/**
 *  @brief  PWM DC filter input select
 */
typedef enum
{
    DCF_FROM_RAW_DCAEVT0  = DCFCTL_SRCSEL_RAWDCAEVT0,       /*!< From Raw DCAEVT0       */
    DCF_FROM_RAW_DCAEVT1  = DCFCTL_SRCSEL_RAWDCAEVT1,       /*!< From Raw DCAEVT1       */
    DCF_FROM_RAW_DCBEVT0  = DCFCTL_SRCSEL_RAWDCBEVT0,       /*!< From Raw DCBEVT0       */
    DCF_FROM_RAW_DCBEVT1  = DCFCTL_SRCSEL_RAWDCBEVT1,       /*!< From Raw DCBEVT1       */
} PWM_DCFilterInputEnum;




/**
 *  @brief  PWM DC filter alignment select
 */
typedef enum
{
    DCF_ALIGN_ON_ZERO         = DCFCTL_PULSESEL_ALIGN_ON_ZERO,
    DCF_ALIGN_ON_PERIOD       = DCFCTL_PULSESEL_ALIGN_ON_PERIOD,
    DCF_ALIGN_ON_ZERO_PERIOD  = DCFCTL_PULSESEL_ALIGN_ON_ZERO_PERIOD
} PWM_DCFilterAlignEnum;




/**
 *  @brief  PWM Sync Output Event selection
 */
typedef enum
{
    SYNCO_SYNCI_AND_FRCSYNC   = TBCTL_SYNCOSEL_SYNCI_AND_FRCSYNC,   /*!< SYNCI or TBCTL.bit.FRCSYNC   */
    SYNCO_TBCNT_EQU_ZERO      = TBCTL_SYNCOSEL_TBCNT_EQU_ZERO,      /*!< TBCNT=0                      */
    SYNCO_TBCNT_EQU_TBPRD     = TBCTL_SYNCOSEL_TBCNT_EQU_TBPRD,     /*!< TBCNT=TBPRD                  */
    SYNCO_TBCNT_EQU_CMPA      = TBCTL_SYNCOSEL_TBCNT_EQU_CMPA,      /*!< TBCNT=CMPA                   */
    SYNCO_TBCNT_EQU_CMPB      = TBCTL_SYNCOSEL_TBCNT_EQU_CMPB,      /*!< TBCNT=CMPB                   */
    SYNCO_TBCNT_EQU_CMPC      = TBCTL_SYNCOSEL_TBCNT_EQU_CMPC,      /*!< TBCNT=CMPC                   */
    SYNCO_TBCNT_EQU_CMPD      = TBCTL_SYNCOSEL_TBCNT_EQU_CMPD,      /*!< TBCNT=CMPD                   */
    SYNCO_DISABLE             = TBCTL_SYNCOSEL_DISABLE              /*!< Disable                      */
} PWM_SyncOutputEventEnum;




/**
 *  @brief  PWM register with shadow feature
 */
typedef enum
{
    SHADOW_TBPRD    = (1U <<  0),      /*!< TBPRD      */
    SHADOW_CMPA     = (1U <<  1),      /*!< CMPA       */
    SHADOW_CMPB     = (1U <<  2),      /*!< CMPB       */
    SHADOW_CMPC     = (1U <<  3),      /*!< CMPC       */
    SHADOW_CMPD     = (1U <<  4),      /*!< CMPD       */
    SHADOW_AQCTLA   = (1U <<  5),      /*!< AQCTLA     */
    SHADOW_AQCTLB   = (1U <<  6),      /*!< AQCTLB     */
    SHADOW_AQCSFRC  = (1U <<  7),      /*!< AQCSFRC    */
    SHADOW_DBCTL    = (1U <<  8),      /*!< DBCTL      */
    SHADOW_DBRED    = (1U <<  9),      /*!< DBRED      */
    SHADOW_DBFED    = (1U << 10),      /*!< DBFED      */
    SHADOW_ALL      = (0x7FFU),        /*!< ALL        */
} PWM_ShadowRegEnum;




/**
 *  @brief  PWM duration clock number
 */
typedef enum
{
    DURATION_4_PWM_CLK      = SYNCOCTL_DURATION_4_PWM_CLK,      /*!< Duration of PWMSYNCO/SOCA/SOCB/SOCC pulse to the pin is 4 PWM clocks      */
    DURATION_8_PWM_CLK      = SYNCOCTL_DURATION_8_PWM_CLK,      /*!< Duration of PWMSYNCO/SOCA/SOCB/SOCC pulse to the pin is 8 PWM clocks      */
    DURATION_16_PWM_CLK     = SYNCOCTL_DURATION_16_PWM_CLK,     /*!< Duration of PWMSYNCO/SOCA/SOCB/SOCC pulse to the pin is 16 PWM clocks     */
    DURATION_32_PWM_CLK     = SYNCOCTL_DURATION_32_PWM_CLK,     /*!< Duration of PWMSYNCO/SOCA/SOCB/SOCC pulse to the pin is 32 PWM clocks     */
} PWM_DurationEnum;




/******************************************************************************
 * @brief      Enable/Disable SYNCO/SOCA/SOCB/SOCC signal output to the pin
 *
 * @param[in] ePWMs: Selected PWM modules defined by PWM_IncEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableSYNCOToGPIO(ePWMs) ( SET_BITS(PWMCFG->SYNCOCTL, (ePWMs) << (SYNCOCTL_SYNCO0EN_Pos) ) )
#define PWM_DisableSYNCOToGPIO(ePWMs) ( CLEAR_BITS(PWMCFG->SYNCOCTL, (ePWMs) << (SYNCOCTL_SYNCO0EN_Pos) ) )
#define PWM_EnableSOCAToGPIO(ePWMs) ( SET_BITS(PWMCFG->SOCAOCTL, (ePWMs) << (SOCAOCTL_SOCA0EN_Pos) ) )
#define PWM_DisableSOCAToGPIO(ePWMs) ( CLEAR_BITS(PWMCFG->SOCAOCTL, (ePWMs) << (SOCAOCTL_SOCA0EN_Pos) ) )
#define PWM_EnableSOCBToGPIO(ePWMs) ( SET_BITS(PWMCFG->SOCBOCTL, (ePWMs) << (SOCBOCTL_SOCB0EN_Pos) ) )
#define PWM_DisableSOCBToGPIO(ePWMs) ( CLEAR_BITS(PWMCFG->SOCBOCTL, (ePWMs) << (SOCBOCTL_SOCB0EN_Pos) ) )
#define PWM_EnableSOCCToGPIO(ePWMs) ( SET_BITS(PWMCFG->SOCCOCTL, (ePWMs) << (SOCCOCTL_SOCC0EN_Pos) ) )
#define PWM_DisableSOCCToGPIO(ePWMs) ( CLEAR_BITS(PWMCFG->SOCCOCTL, (ePWMs) << (SOCCOCTL_SOCC0EN_Pos) ) )




/******************************************************************************
 * @brief      Set pulse duration of PWMSYNCO/SOCA/SOCB/SOCC to the pin
 *
 * @param[in]  eDuration :  Pulse duration defined by PWM_DurationEnum
 *                          Only the following values are valid:
 *                          - \ref DURATION_4_PWM_CLK
 *                          - \ref DURATION_8_PWM_CLK
 *                          - \ref DURATION_16_PWM_CLK
 *                          - \ref DURATION_32_PWM_CLK
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSYNCOToGPIOPulseDuration(eDuration)                              \
    MODIFY_REG(PWMCFG->SYNCOCTL, SYNCOCTL_DURATION_Msk, eDuration)
#define PWM_SetSOCAToGPIOPulseDuration(eDuration)                               \
    MODIFY_REG(PWMCFG->SOCAOCTL, SOCAOCTL_DURATION_Msk, eDuration)
#define PWM_SetSOCBToGPIOPulseDuration(eDuration)                               \
    MODIFY_REG(PWMCFG->SOCBOCTL, SOCBOCTL_DURATION_Msk, eDuration)
#define PWM_SetSOCCToGPIOPulseDuration(eDuration)                               \
    MODIFY_REG(PWMCFG->SOCCOCTL, SOCCOCTL_DURATION_Msk, eDuration)




/******************************************************************************
 * @brief      Enable/Disable global shadow to active load
 *
 * @param[in]  PWMx: Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableGlobalLoad(PWMx)    ((PWMx)->GLDCTL0 |= GLDCTL0_GLDEN_ENABLE)
#define PWM_DisableGlobalLoad(PWMx)   ((PWMx)->GLDCTL0 &= ~GLDCTL0_GLDEN_ENABLE)




/******************************************************************************
 * @brief      Set global shadow to active load timing
 *
 * @param[in]  PWMx:   Select the PWM module
 * @param[in]  eMode:  Global load timing defined by PWM_LoadTimingEnum
 *                     Only the following values are valid:
 *                      - \ref GLOBAL_LOAD_ON_ZERO            
 *                      - \ref GLOBAL_LOAD_ON_PERIOD          
 *                      - \ref GLOBAL_LOAD_ON_ZERO_PERIOD     
 *                      - \ref GLOBAL_LOAD_ON_SYNCI            
 *                      - \ref GLOBAL_LOAD_ON_SYNCI_ZERO       
 *                      - \ref GLOBAL_LOAD_ON_SYNCI_PERIOD     
 *                      - \ref GLOBAL_LOAD_ON_SYNCI_ZERO_PERIOD
 *                      - \ref GLOBAL_LOAD_ON_FORCE           
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetGlobalLoadTiming(PWMx, eMode)                                    \
    WRITE_FIELD((PWMx)->GLDCTL0, GLDCTL0_GLDLOAD_Msk, GLDCTL0_GLDLOAD_Pos, (eMode))




/******************************************************************************
 * @brief      Set continuous global shadow to active load period
 *
 * @param[in]  PWMx:    Select the PWM module
 * @param[in]  ePeriod: Global load period defined by PWM_EventPeriodEnum;
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetContinuousGlobalLoadPeriod(PWMx, ePeriod)                        \
    WRITE_FIELD((PWMx)->GLDCTL0, GLDCTL0_GLDPRD_Msk, GLDCTL0_GLDPRD_Pos, (ePeriod))




/******************************************************************************
 * @brief      Get global shadow to active load strobe event count
 *
 * @param[in]  PWMx:    Select the PWM module
 *
 * @return     Count of global load events that have happened
 *
 ******************************************************************************/
#define PWM_GetGlobalLoadEventCount(PWMx)                                       \
    READ_FIELD((PWMx)->GLDCTL0, GLDCTL0_GLDCNT_Msk, GLDCTL0_GLDCNT_Pos)




/******************************************************************************
 * @brief      Enable one-shot global shadow to active load
 *
 * @param[in]  PWMx:    Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableOneShotGlobalLoadMode(PWMx)                                   \
    SET_BITS((PWMx)->GLDCTL0, GLDCTL0_OSTMODE_Msk)




/******************************************************************************
 * @brief      Enable continuous global shadow to active load
 *
 * @param[in]  PWMx:    Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableContinuousGlobalLoadMode(PWMx)                                \
    CLEAR_BITS((PWMx)->GLDCTL0, GLDCTL0_OSTMODE_Msk)




/******************************************************************************
 * @brief      Start/Get status of one-shot global shadow to active load pending
 *
 * @param[in]  PWMx:    Select the PWM module
 *
 * @return     0 - No one-shot global shadow to active load is pending
 *                 Software forced one-shot load will be ignored until a new
 *                 pending cycle is started
 *             1 - One-shot global shadow to active load is pending
 *                 Software forced strobe pulse will trigger one-shot load and
 *                 clear the flag
 *
 ******************************************************************************/
#define PWM_StartOneShotGlobalLoadPending(PWMx)     ((PWMx)->GLDCTL1 = GLDCTL1_OSTLOAD_PENDING)
#define PWM_IsOneShotGlobalLoadPending(PWMx)        (((PWMx)->GLDCTL1 & GLDCTL1_OSTLOAD_Msk) >> GLDCTL1_OSTLOAD_Pos)




/******************************************************************************
 * @brief      Force one-shot global shadow to active load strobe pulse
 *
 * @param[in]  PWMx:    Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_ForceOneShotGlobalLoad(PWMx)            ((PWMx)->GLDCTL1 = GLDCTL1_FRCLOAD_FORCE)




/******************************************************************************
 * @brief      Select register load by global strobe signal
 *
 * @param[in]  PWMx:    Select the PWM module
 * @param[in]  eReg:    Select the register defined by PWM_ShadowRegEnum
 *                      Multiple registers can be ORed simultaneously
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetRegLoadByGlobalControl(PWMx, eReg)       ((PWMx)->GLDSEL |= (eReg))




/******************************************************************************
 * @brief      Select register load by local strobe signal
 *
 * @param[in]  PWMx:    Select the PWM module
 * @param[in]  eReg:    Select the register defined by PWM_ShadowRegEnum
 *                      Multiple registers can be ORed simultaneously
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetRegLoadByLocalControl(PWMx, eReg)        ((PWMx)->GLDSEL &= ~(eReg))




/******************************************************************************
 * @brief       Get PWMx shadow status
 *
 * @param[in]   PWMx:   Select the PWM module
 * @param[in]   eReg:   Register with shadow feature as defined by PWM_ShadowRegEnum
 *                      Multiple registers can be ORed simultaneously
 *
 * @return      0      - None of the queried requests occurred
 *              not 0  - Corresponding requests for non-zero bit occurred
 *
 ******************************************************************************/
#define PWM_GetShadowStatus(PWMx, eReg)     ((PWMx)->SHADOWSTS & (eReg))




/******************************************************************************
 * @brief      Enable PWMx register link
 *
 * @param[in]  PWMx      :  Select the PWM module
 * @param[in]  ePWMLinked:  Select the target PWM to be linked
 *                          Please refer to PWM_SelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_LinkTBPRD(PWMx,ePWMLinked)      ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_TBPRD_Msk  ) | ((ePWMLinked) << PWMLINK_TBPRD_Pos))
#define PWM_LinkCMPA(PWMx,ePWMLinked)       ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_CMPA_Msk   ) | ((ePWMLinked) << PWMLINK_CMPA_Pos))
#define PWM_LinkCMPB(PWMx,ePWMLinked)       ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_CMPB_Msk   ) | ((ePWMLinked) << PWMLINK_CMPB_Pos))
#define PWM_LinkCMPC(PWMx,ePWMLinked)       ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_CMPC_Msk   ) | ((ePWMLinked) << PWMLINK_CMPC_Pos))
#define PWM_LinkCMPD(PWMx,ePWMLinked)       ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_CMPD_Msk   ) | ((ePWMLinked) << PWMLINK_CMPD_Pos))
#define PWM_LinkDBRED(PWMx,ePWMLinked)      ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_DBRED_Msk  ) | ((ePWMLinked) << PWMLINK_DBRED_Pos))
#define PWM_LinkDBFED(PWMx,ePWMLinked)      ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_DBFED_Msk  ) | ((ePWMLinked) << PWMLINK_DBFED_Pos))
#define PWM_LinkGLDCTL1(PWMx,ePWMLinked)    ((PWMx)->PWMLINK = ((PWMx)->PWMLINK & ~PWMLINK_GLDCTL1_Msk) | ((ePWMLinked) << PWMLINK_GLDCTL1_Pos))




/******************************************************************************
 * @brief      Disable PWMx register link
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_UnlinkTBPRD(PWMx)               ((PWMx)->PWMLINK |= PWMLINK_TBPRD_Msk)
#define PWM_UnlinkCMPA(PWMx)                ((PWMx)->PWMLINK |= PWMLINK_CMPA_Msk)
#define PWM_UnlinkCMPB(PWMx)                ((PWMx)->PWMLINK |= PWMLINK_CMPB_Msk)
#define PWM_UnlinkCMPC(PWMx)                ((PWMx)->PWMLINK |= PWMLINK_CMPC_Msk)
#define PWM_UnlinkCMPD(PWMx)                ((PWMx)->PWMLINK |= PWMLINK_CMPD_Msk)
#define PWM_UnlinkDBRED(PWMx)               ((PWMx)->PWMLINK |= PWMLINK_DBRED_Msk)
#define PWM_UnlinkDBFED(PWMx)               ((PWMx)->PWMLINK |= PWMLINK_DBFED_Msk)
#define PWM_UnlinkGLDCTL1(PWMx)             ((PWMx)->PWMLINK |= PWMLINK_GLDCTL1_Msk)




/******************************************************************************
 * @brief      Set/Get PWMx Time-Base clock divider
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eDiv0:  PWMx clock divider binary part
 *                     Please refer to PWM_ClockDiv0Enum
 * @param[in]  eDiv1:  PWMx clock divider linearly part
 *                     Please refer to PWM_ClockDiv1Enum
 *
 * @return     None
 * @return     Actual PWM Time-Base clock divider value
 *
 * @note       PWM Time-Base clock divider = 2^TBPDIV * (TBDIV+1)
 *
 * @example    PWM_SetClockDiv(PWM0, PWM_CLKDIV0_2 , PWM_CLKDIV1_1);
 *             PWM_SetClockDiv(PWM1, PWM_CLKDIV0_32, PWM_CLKDIV1_3);
 *
 ******************************************************************************/
#define PWM_SetClockDiv(PWMx, eDiv0, eDiv1)                                     \
    MODIFY_REG((PWMx)->TBCTL, TBCTL_TBPDIV_Msk|TBCTL_TBDIV_Msk, (eDiv0) | (eDiv1))

__STATIC_INLINE uint32_t PWM_GetClockDiv(PWM_REGS *PWMx)
{
    uint32_t u32TBDIV;
    uint32_t u32TBPDIV;
    
    u32TBPDIV = READ_FIELD((PWMx)->TBCTL, TBCTL_TBPDIV_Msk, 
                                                TBCTL_TBPDIV_Pos);
    u32TBPDIV = 0x1U << u32TBPDIV;
    
    u32TBDIV  = READ_FIELD((PWMx)->TBCTL, TBCTL_TBDIV_Msk, 
                                                TBCTL_TBDIV_Pos) + 1;
    
    return u32TBDIV * u32TBPDIV;
}




/******************************************************************************
 * @brief      Set/Get current PWM counter value
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 * @return     PWM current counter value (16 bit)
 *
 ******************************************************************************/
#define PWM_SetCounterValue(PWMx, u16Val)   ((PWMx)->TBCNT = (u16Val))
#define PWM_GetCounterValue(PWMx)           ((PWMx)->TBCNT)



/******************************************************************************
 * @brief      Get PWM period value
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     PWM period shadow value (16 bit)
 *
 ******************************************************************************/
#define PWM_GetPRD(PWMx)                    ((PWMx)->TBPRDA)
#define PWM_GetShadowPRD(PWMx)              ((PWMx)->TBPRD)

#define PWM_GetPeriod(PWMx)                 ((PWMx)->TBPRDA)
#define PWM_GetShadowPeriod(PWMx)           ((PWMx)->TBPRD)




/******************************************************************************
 * @brief      Set PWM period value
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  u16Val:  PWM reload counter (16 bit)
 *
 * @return     None
 *
 * @detail     PWM carrier frequency will be divided by period value
 *             If PWM is up counting or down counting,
 *                PWM frequency = PWM clock/Period
 *             if PWM is up counting and down counting,
 *                PWM frequency = PWM clock/Period/2
 *             Thus user may design PWM frequency by Period and PWM clock frequency
 *
 ******************************************************************************/
#define PWM_SetPRD(PWMx,u16Val)             ((PWMx)->TBPRD = (u16Val))

#define PWM_SetPeriod(PWMx,u16Val)          ((PWMx)->TBPRD = (u16Val))




/******************************************************************************
 * @brief      Set TBPRD load timing
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  TBPRD value load timing defined by PWM_LoadTimingEnum
 *                     Only the following values are valid:
 *                      - \ref TBPRD_LOAD_ON_ZERO              
 *                      - \ref TBPRD_LOAD_ON_SYNCI              
 *                      - \ref TBPRD_LOAD_ON_SYNCI_ZERO         
 *                      - \ref TBPRD_LOAD_ON_IMMEDIATE         
 *
 * @return     None
 *
 * @example    PWM_SetPRDLoadTiming(PWM0, TBPRD_LOAD_ON_ZERO);
 *
 ******************************************************************************/
#define PWM_SetPRDLoadTiming(PWMx,eMode)                                        \
    WRITE_FIELD((PWMx)->TBCTL, TBCTL_TBPRDLOAD_Msk, TBCTL_TBPRDLOAD_Pos, (eMode))




/******************************************************************************
 * @brief      Lock, unlock period active value
 *             Active value in TBPRD will not change
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_LockPRD(PWMx)               ((PWMx)->TBCTL |= TBCTL_TBPRDLOCK_LOCK)
#define PWM_UnlockPRD(PWMx)             ((PWMx)->TBCTL &= ~TBCTL_TBPRDLOCK_LOCK)




/******************************************************************************
 * @brief      Set PWM synchronization reload value
 *             PWM counter will equal TBPHS after synchronization event
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  u16Val:  PWM reload value
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSyncReloadValue(PWMx,u16Val)           ((PWMx)->TBPHS = (u16Val))




/******************************************************************************
 * @brief      Enable/Disable PWM synchronization
 *             PWM counter will equal TBPHS upon synchronization event
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableSync(PWMx)              ((PWMx)->TBCTL |= TBCTL_PHSEN_ENABLE)
#define PWM_DisableSync(PWMx)             ((PWMx)->TBCTL &= ~TBCTL_PHSEN_ENABLE)




/******************************************************************************
 * @brief      Force PWM synchronization
 *             PWM counter will equal TBPHS upon synchronization event
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_ForceSingleSync(PWMx)         ((PWMx)->TBCTL |= TBCTL_FRCSYNC_FORCE)




/******************************************************************************
 * @brief      Select PWMSYNCO signal
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  eSYNCO:  Select the PWM SYNCO event
 *                      Please refer to PWM_SyncOutputEventEnum
 *
 * @return     None
 *
 * @example    PWM_SetSyncOutEvent(PWM0, SYNCO_TBCNT_EQU_ZERO);
 *
 ******************************************************************************/
#define PWM_SetSyncOutEvent(PWMx,eSYNCO)    ((PWMx)->TBCTL = ((PWMx)->TBCTL & ~TBCTL_SYNCOSEL_Msk) | (eSYNCO))




/******************************************************************************
 * @brief      Select PWM counter direction after synchronization
 *             (Only valid in up-down-count mode)
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eDir:  Select the counter direction
 *                    Valid option is COUNT_UP(1) or COUNT_DOWN(0)
 *
 * @return     None
 *
 * @example    PWM_SetCounterDirAfterSync(PWM0, COUNT_UP);
 *             PWM_SetCounterDirAfterSync(PWM0, COUNT_DOWN);
 *
 ******************************************************************************/
#define PWM_SetCounterDirAfterSync(PWMx,eDir)   ((PWMx)->TBCTL = ((PWMx)->TBCTL & ~TBCTL_PHSDIR_Msk) | ((eDir) << TBCTL_PHSDIR_Pos))




/******************************************************************************
 * @brief      PWM counter will not increase when in MCU debug mode
 *             Note: Please remember to configure CBC trip when debug
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_StopCounterInDebug(PWMx)        ((PWMx)->TBCTL = ((PWMx)->TBCTL & ~TBCTL_DBGRUN_Msk) | TBCTL_DBGRUN_STOP_AFTER_CYCLE)




/******************************************************************************
 * @brief      Set/Get PWM counter counting mode (4 modes include stop)
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  Specifies the clock counting mode
 *                     Please refer to PWM_CounterModeEnum
 *                      - \ref COUNT_DOWN
 *                      - \ref COUNT_UP
 *                      - \ref COUNT_UP_DOWN
 *                      - \ref COUNT_STOP
 *
 * @return     None
 * @return     Specifies the clock counting mode
 *                 Please refer to PWM_CounterModeEnum
 *                  - \ref COUNT_DOWN
 *                  - \ref COUNT_UP
 *                  - \ref COUNT_UP_DOWN
 *                  - \ref COUNT_STOP
 *
 * @example    PWM_SetCounterMode(PWM0, COUNT_UP_DOWN);
 *             PWM_SetCounterMode(PWM1, COUNT_STOP);
 *             PWM_GetCounterMode(PWM0);
 *             PWM_GetCounterMode(PWM1);
 *
 ******************************************************************************/
#define PWM_SetCounterMode(PWMx,eMode)      ((PWMx)->TBCTL = ((PWMx)->TBCTL & ~TBCTL_CNTMODE_Msk) | ((eMode) << TBCTL_CNTMODE_Pos))
#define PWM_GetCounterMode(PWMx)            READ_FIELD((PWMx)->TBCTL, TBCTL_CNTMODE_Msk, TBCTL_CNTMODE_Pos)




/******************************************************************************
 * @brief      Run/Stop/Get status of PWM counter
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define PWM_RunCounter(PWMx)                ((PWMx)->TBCTL |= TBCTL_CNTRUN_COUNT_RUN)
#define PWM_StopCounter(PWMx)               ((PWMx)->TBCTL &= ~TBCTL_CNTRUN_COUNT_RUN)
#define PWM_IsCounterRun(PWMx)              (((PWMx)->TBCTL & TBCTL_CNTRUN_Msk) >> TBCTL_CNTRUN_Pos)




/******************************************************************************
 * @brief      Get the counting direction of PWM counter
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     0 - PWM counter is counting down
 *             1 - PWM counter is counting up
 *
 ******************************************************************************/
#define PWM_GetCountingDirection(PWMx)      (((PWMx)->TBFLG & TBFLG_CNTDIR_Msk) >> TBFLG_CNTDIR_Pos)




/******************************************************************************
 * @brief      Check if PWM counter is counting up
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     0 - PWM counter is counting down
 *             1 - PWM counter is counting up
 *
 ******************************************************************************/
#define PWM_IsCountingUp(PWMx)              (((PWMx)->TBFLG & TBFLG_CNTDIR_Msk) >> TBFLG_CNTDIR_Pos)




/******************************************************************************
 * @brief      Check if PWM counter is counting down
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     0 - PWM counter is counting up
 *             1 - PWM counter is counting down
 *
 ******************************************************************************/
#define PWM_IsCountingDown(PWMx)            (1U - (((PWMx)->TBFLG & TBFLG_CNTDIR_Msk) >> TBFLG_CNTDIR_Pos))




/******************************************************************************
 * @brief      Get time-base event flag
 *
 * @param[in]  PWMx:   Select the PWM module
 * @param[in]  eEvt:   Select the time-base event from PWM_TimeBaseEventEnum
 *                     Multiple events can be ORed simultaneously
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for non-zero bit occurred
 *
 ******************************************************************************/
#define PWM_GetTimeBaseEventFlag(PWMx, eEvt)    ((PWMx)->TBFLG & (eEvt))




/******************************************************************************
 * @brief      Clear time-base event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the time-base event from PWM_TimeBaseEventEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_ClearTimeBaseEventFlag(PWMx, eEvt)  ((PWMx)->TBFLGCLR = (eEvt))




/******************************************************************************
 * @brief      Set PWMx CMPx value
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  u16Val:  PWM comparator x value(16 bit)
 *                      It should be a value from 0 to TBPRD
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetCMPA(PWMx,u16Val)            ((PWMx)->CMPA = (u16Val))
#define PWM_SetCMPB(PWMx,u16Val)            ((PWMx)->CMPB = (u16Val))
#define PWM_SetCMPC(PWMx,u16Val)            ((PWMx)->CMPC = (u16Val))
#define PWM_SetCMPD(PWMx,u16Val)            ((PWMx)->CMPD = (u16Val))




/******************************************************************************
 * @brief      Get PWMx CMPx shadow value
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     CMPx shadow value (16 bit)
 *
 ******************************************************************************/
#define PWM_GetShadowCMPA(PWMx)             ((PWMx)->CMPA)
#define PWM_GetShadowCMPB(PWMx)             ((PWMx)->CMPB)
#define PWM_GetShadowCMPC(PWMx)             ((PWMx)->CMPC)
#define PWM_GetShadowCMPD(PWMx)             ((PWMx)->CMPD)




/******************************************************************************
 * @brief      Get PWMx CMPx value
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     CMPx active value (16 bit)
 *
 ******************************************************************************/
#define PWM_GetCMPA(PWMx)                   ((PWMx)->CMPAA)
#define PWM_GetCMPB(PWMx)                   ((PWMx)->CMPBA)
#define PWM_GetCMPC(PWMx)                   ((PWMx)->CMPCA)
#define PWM_GetCMPD(PWMx)                   ((PWMx)->CMPDA)




/******************************************************************************
 * @brief      Set CMPA/CMPB/CMPC/CMPD load timing
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  PWM Comparator value load timing defined by PWM_LoadTimingEnum
 *                     Only the following values are valid:
 *                      - \ref CMPA_LOAD_ON_ZERO             
 *                      - \ref CMPA_LOAD_ON_PERIOD           
 *                      - \ref CMPA_LOAD_ON_ZERO_PERIOD      
 *                      - \ref CMPA_LOAD_ON_SYNCI             
 *                      - \ref CMPA_LOAD_ON_SYNCI_ZERO        
 *                      - \ref CMPA_LOAD_ON_SYNCI_PERIOD      
 *                      - \ref CMPA_LOAD_ON_SYNCI_ZERO_PERIOD 
 *                      - \ref CMPA_LOAD_ON_IMMEDIATE        
 *                      - \ref CMPB_LOAD_ON_ZERO             
 *                      - \ref CMPB_LOAD_ON_PERIOD           
 *                      - \ref CMPB_LOAD_ON_ZERO_PERIOD      
 *                      - \ref CMPB_LOAD_ON_SYNCI             
 *                      - \ref CMPB_LOAD_ON_SYNCI_ZERO        
 *                      - \ref CMPB_LOAD_ON_SYNCI_PERIOD      
 *                      - \ref CMPB_LOAD_ON_SYNCI_ZERO_PERIOD 
 *                      - \ref CMPB_LOAD_ON_IMMEDIATE        
 *                      - \ref CMPC_LOAD_ON_ZERO             
 *                      - \ref CMPC_LOAD_ON_PERIOD           
 *                      - \ref CMPC_LOAD_ON_ZERO_PERIOD      
 *                      - \ref CMPC_LOAD_ON_SYNCI             
 *                      - \ref CMPC_LOAD_ON_SYNCI_ZERO        
 *                      - \ref CMPC_LOAD_ON_SYNCI_PERIOD      
 *                      - \ref CMPC_LOAD_ON_SYNCI_ZERO_PERIOD 
 *                      - \ref CMPC_LOAD_ON_IMMEDIATE        
 *                      - \ref CMPD_LOAD_ON_ZERO             
 *                      - \ref CMPD_LOAD_ON_PERIOD           
 *                      - \ref CMPD_LOAD_ON_ZERO_PERIOD      
 *                      - \ref CMPD_LOAD_ON_SYNCI             
 *                      - \ref CMPD_LOAD_ON_SYNCI_ZERO        
 *                      - \ref CMPD_LOAD_ON_SYNCI_PERIOD      
 *                      - \ref CMPD_LOAD_ON_SYNCI_ZERO_PERIOD 
 *                      - \ref CMPD_LOAD_ON_IMMEDIATE   
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetCMPALoadTiming(PWMx,eMode)   ((PWMx)->CMPCTL = ((PWMx)->CMPCTL & ~CMPCTL_CMPALOAD_Msk) | ((eMode) << CMPCTL_CMPALOAD_Pos))
#define PWM_SetCMPBLoadTiming(PWMx,eMode)   ((PWMx)->CMPCTL = ((PWMx)->CMPCTL & ~CMPCTL_CMPBLOAD_Msk) | ((eMode) << CMPCTL_CMPBLOAD_Pos))
#define PWM_SetCMPCLoadTiming(PWMx,eMode)   ((PWMx)->CMPCTL = ((PWMx)->CMPCTL & ~CMPCTL_CMPCLOAD_Msk) | ((eMode) << CMPCTL_CMPCLOAD_Pos))
#define PWM_SetCMPDLoadTiming(PWMx,eMode)   ((PWMx)->CMPCTL = ((PWMx)->CMPCTL & ~CMPCTL_CMPDLOAD_Msk) | ((eMode) << CMPCTL_CMPDLOAD_Pos))




/******************************************************************************
 * @brief      Lock CMPA/CMPB/CMPC/CMPD active value
 *             Active value in CMPx will not change
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_LockCMPA(PWMx)                  ((PWMx)->CMPCTL |= CMPCTL_CMPALOCK_LOCK)
#define PWM_LockCMPB(PWMx)                  ((PWMx)->CMPCTL |= CMPCTL_CMPBLOCK_LOCK)
#define PWM_LockCMPC(PWMx)                  ((PWMx)->CMPCTL |= CMPCTL_CMPCLOCK_LOCK)
#define PWM_LockCMPD(PWMx)                  ((PWMx)->CMPCTL |= CMPCTL_CMPDLOCK_LOCK)




/******************************************************************************
 * @brief      UnLock CMPA/CMPB/CMPC/CMPD active value
 *             Active value in CMPx will be updated when loading event occurred
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_UnlockCMPA(PWMx)                ((PWMx)->CMPCTL &= ~CMPCTL_CMPALOCK_LOCK)
#define PWM_UnlockCMPB(PWMx)                ((PWMx)->CMPCTL &= ~CMPCTL_CMPBLOCK_LOCK)
#define PWM_UnlockCMPC(PWMx)                ((PWMx)->CMPCTL &= ~CMPCTL_CMPCLOCK_LOCK)
#define PWM_UnlockCMPD(PWMx)                ((PWMx)->CMPCTL &= ~CMPCTL_CMPDLOCK_LOCK)




/******************************************************************************
 * @brief      Set AQCTLA/B load timing
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  AQCTLA/B load timing defined by PWM_LoadTimingEnum
 *                     Only the following values are valid:
 *                      - \ref AQCTLA_LOAD_ON_ZERO              
 *                      - \ref AQCTLA_LOAD_ON_PERIOD            
 *                      - \ref AQCTLA_LOAD_ON_ZERO_PERIOD       
 *                      - \ref AQCTLA_LOAD_ON_SYNCI              
 *                      - \ref AQCTLA_LOAD_ON_SYNCI_ZERO         
 *                      - \ref AQCTLA_LOAD_ON_SYNCI_PERIOD       
 *                      - \ref AQCTLA_LOAD_ON_SYNCI_ZERO_PERIOD  
 *                      - \ref AQCTLA_LOAD_ON_IMMEDIATE         
 *                      - \ref AQCTLB_LOAD_ON_ZERO              
 *                      - \ref AQCTLB_LOAD_ON_PERIOD            
 *                      - \ref AQCTLB_LOAD_ON_ZERO_PERIOD       
 *                      - \ref AQCTLB_LOAD_ON_SYNCI              
 *                      - \ref AQCTLB_LOAD_ON_SYNCI_ZERO         
 *                      - \ref AQCTLB_LOAD_ON_SYNCI_PERIOD       
 *                      - \ref AQCTLB_LOAD_ON_SYNCI_ZERO_PERIOD  
 *                      - \ref AQCTLB_LOAD_ON_IMMEDIATE         
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetAQCTLALoadTiming(PWMx,eMode) ((PWMx)->AQCTL = ((PWMx)->AQCTL & ~AQCTL_AQCTLALOAD_Msk) | ((eMode) << AQCTL_AQCTLALOAD_Pos))
#define PWM_SetAQCTLBLoadTiming(PWMx,eMode) ((PWMx)->AQCTL = ((PWMx)->AQCTL & ~AQCTL_AQCTLBLOAD_Msk) | ((eMode) << AQCTL_AQCTLBLOAD_Pos))




/******************************************************************************
 * @brief      Lock AQCTLA/B active value
 *             Active value in AQCTLA/B will not change
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_LockAQCTLA(PWMx)                ((PWMx)->AQCTL |= AQCTL_AQCTLALOCK_LOCK)
#define PWM_LockAQCTLB(PWMx)                ((PWMx)->AQCTL |= AQCTL_AQCTLBLOCK_LOCK)




/******************************************************************************
 * @brief      UnLock AQCTLA/B active value
 *             Active value in CMPx will be updated when loading event occurred
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_UnlockAQCTLA(PWMx)              ((PWMx)->AQCTL &= ~AQCTL_AQCTLALOCK_LOCK)
#define PWM_UnlockAQCTLB(PWMx)              ((PWMx)->AQCTL &= ~AQCTL_AQCTLBLOCK_LOCK)




/******************************************************************************
 * @brief      Set PWMxA/B output waveform
 *
 * @param[in]  PWMx      :  Select the PWM module
 * @param[in]  eActionSel:  Specifies the action after events
 *                          Please refer to PWM_ActionQualifierEnum
 *
 * @return     None
 *
 * @example    PWM_ActionQualifierCHA(PWM0, CAU_SET_HIGH|CAD_SET_LOW|
 *                                          CBD_DO_NOTHING|CBU_DO_NOTHING|
 *                                          PRD_DO_NOTHING|ZRO_SET_LOW);
 *             Wrong configuration!!
 *             PWM_ActionQualifierCHA(PWM1, CAU_SET_HIGH|CAU_SET_LOW|  --> Can NOT configure 2 actions for same event
 *                                          CBD_DO_NOTHING|CBU_DO_NOTHING|
 *                                          PRD_DO_NOTHING|ZRO_SET_LOW);
 *
 ******************************************************************************/
#define PWM_ActionQualifierCHA(PWMx,eActionSel) ((PWMx)->AQCTLA = (eActionSel))
#define PWM_ActionQualifierCHB(PWMx,eActionSel) ((PWMx)->AQCTLB = (eActionSel))




/******************************************************************************
 * @brief      Get PWMxA/B action qualifier shadow value
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     AQCTLA/AQCTLB shadow value
 *
 ******************************************************************************/
#define PWM_GetShadowAQCTLA(PWMx)           ((PWMx)->AQCTLA)
#define PWM_GetShadowAQCTLB(PWMx)           ((PWMx)->AQCTLB)




/******************************************************************************
 * @brief      Get PWMxA/B action qualifier active value
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     AQCTLA/AQCTLB shadow value
 *
 ******************************************************************************/
#define PWM_GetAQCTLA(PWMx)                 ((PWMx)->AQCTLAA)
#define PWM_GetAQCTLB(PWMx)                 ((PWMx)->AQCTLBA)




/******************************************************************************
 * @brief      Set T0/T1 event
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Specifies the event as defined by PWM_TxEventEnum
 *
 * @return     None
 *
 * @example    PWM_SetT0Event(PWM0, TxEVENT_DCAEVT0);
 *             PWM_SetT1Event(PWM0, TxEVENT_TZ0);
 *
 ******************************************************************************/
#define PWM_SetT0Event(PWMx,eEvt)           ((PWMx)->AQCTL = ((PWMx)->AQCTL & ~AQCTL_T0SEL_Msk) | ((eEvt) << AQCTL_T0SEL_Pos))
#define PWM_SetT1Event(PWMx,eEvt)           ((PWMx)->AQCTL = ((PWMx)->AQCTL & ~AQCTL_T1SEL_Msk) | ((eEvt) << AQCTL_T1SEL_Pos))




/******************************************************************************
 * @brief      Set/Get channel A software one-shot force output action
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eAction:  Software one-shot force action defined by PWM_ActionQualifierEnum
 *                       Only the following values are valid:
 *                        - \ref FRC_DO_NOTHING
 *                        - \ref FRC_SET_LOW
 *                        - \ref FRC_SET_HIGH
 *                        - \ref FRC_TOGGLE
 *
 * @return     None
 * @return     Software one-shot force action defined by PWM_ActionQualifierEnum
 *             Only the following values are valid:
 *              - \ref FRC_DO_NOTHING
 *              - \ref FRC_SET_LOW
 *              - \ref FRC_SET_HIGH
 *              - \ref FRC_TOGGLE
 *
 * @example    PWM_SetCHAOneShotForceOutputAction(PWM0, FRC_DO_NOTHING);
 *             PWM_GetCHAOneShotForceOutputAction(PWM0);
 *
 ******************************************************************************/
#define PWM_SetCHAOneShotForceOutputAction(PWMx,eAction)                        \
    ((PWMx)->AQSFRC = ((PWMx)->AQSFRC & ~AQSFRC_ACTSFA_Msk)                     \
                      | ((eAction) << AQSFRC_ACTSFA_Pos)                        \
    )

#define PWM_GetCHAOneShotForceOutputAction(PWMx)                                \
    (((PWMx)->AQSFRC & AQSFRC_ACTSFA_Msk) >> AQSFRC_ACTSFA_Pos)




/******************************************************************************
 * @brief      Set/Get channel B software one-shot force output action
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eAction:  Software one-shot force action defined by PWM_ActionQualifierEnum
 *                       Only the following values are valid:
 *                        - \ref FRC_DO_NOTHING
 *                        - \ref FRC_SET_LOW
 *                        - \ref FRC_SET_HIGH
 *                        - \ref FRC_TOGGLE
 *
 * @return     None
 * @return     Software one-shot force action defined by PWM_ActionQualifierEnum
 *             Only the following values are valid:
 *              - \ref FRC_DO_NOTHING
 *              - \ref FRC_SET_LOW
 *              - \ref FRC_SET_HIGH
 *              - \ref FRC_TOGGLE
 *
 * @example    PWM_SetCHBOneShotForceOutputAction(PWM0, FRC_DO_NOTHING);
 *             PWM_GetCHBOneShotForceOutputAction(PWM0);
 *
 ******************************************************************************/
#define PWM_SetCHBOneShotForceOutputAction(PWMx,eAction)                        \
    ((PWMx)->AQSFRC = ((PWMx)->AQSFRC & ~AQSFRC_ACTSFB_Msk)                     \
                      | ((eAction) << AQSFRC_ACTSFB_Pos)                        \
    )

#define PWM_GetCHBOneShotForceOutputAction(PWMx)                                \
    (((PWMx)->AQSFRC & AQSFRC_ACTSFB_Msk) >> AQSFRC_ACTSFB_Pos)




/******************************************************************************
 * @brief      Force software one-shot output action on which output channel
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eTar :  Software force target defined by PWM_ForceTargetEnum
 *                     Only the following values are valid:
 *                      - \ref PWM_FRC_ON_CHA
 *                      - \ref PWM_FRC_ON_CHB
 *                      - \ref PWM_FRC_ON_CHA_AND_CHB
 *
 * @return     None
 *
 * @example    PWM_ForceOneShotOutput(PWM0, PWM_FRC_ON_CHA);
 *             PWM_ForceOneShotOutput(PWM0, PWM_FRC_ON_CHA_AND_CHB);
 *
 ******************************************************************************/
#define PWM_ForceOneShotOutput(PWMx,eTar)                                       \
    ((PWMx)->AQSFRC |= ((eTar) << AQSFRC_OTSFRC_Pos))




/******************************************************************************
 * @brief      Set AQCSFRC load timing
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  AQCSFRC load timing defined by PWM_LoadTimingEnum
 *                     Only the following values are valid:
 *                      - \ref AQCSFRC_LOAD_ON_ZERO            
 *                      - \ref AQCSFRC_LOAD_ON_PERIOD          
 *                      - \ref AQCSFRC_LOAD_ON_ZERO_PERIOD     
 *                      - \ref AQCSFRC_LOAD_ON_IMMEDIATE       
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetAQCSFRCLoadTiming(PWMx,eMode)                                    \
    ((PWMx)->AQSFRC = ((PWMx)->AQSFRC & ~AQSFRC_CSFLOAD_Msk) | ((eMode) << AQSFRC_CSFLOAD_Pos))




/******************************************************************************
 * @brief      Set channel A software continuous force output action
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eAction:  Software continuous force action defined by PWM_ActionQualifierEnum
 *                       Only the following values are valid:
 *                        - \ref FRC_DO_NOTHING
 *                        - \ref FRC_SET_LOW
 *                        - \ref FRC_SET_HIGH
 *
 * @return     None
 *
 * @example    PWM_SetCHAContinuousForceOutputAction(PWM0, FRC_DO_NOTHING);
 *
 ******************************************************************************/
#define PWM_SetCHAContinuousForceOutputAction(PWMx,eAction)                      \
    ((PWMx)->AQCSFRC = ((PWMx)->AQCSFRC & ~AQCSFRC_CSFA_Msk)                    \
                       | ((eAction) << AQCSFRC_CSFA_Pos)                        \
    )




/******************************************************************************
 * @brief      Set channel B software continuous force output action
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eAction:  Software continuous force action defined by PWM_ActionQualifierEnum
 *                       Only the following values are valid:
 *                        - \ref FRC_DO_NOTHING
 *                        - \ref FRC_SET_LOW
 *                        - \ref FRC_SET_HIGH
 *
 * @return     None
 *
 * @example    PWM_SetCHBContinuousForceOutputAction(PWM0, FRC_DO_NOTHING);
 *
 ******************************************************************************/
#define PWM_SetCHBContinuousForceOutputAction(PWMx,eAction)                      \
    ((PWMx)->AQCSFRC = ((PWMx)->AQCSFRC & ~AQCSFRC_CSFB_Msk)                    \
                       | ((eAction) << AQCSFRC_CSFB_Pos)                        \
    )




/******************************************************************************
 * @brief      Get channel A software continuous force output action
 *
 * @param[in]  PWMx: Select the PWM module
 *
 * @return     Software continuous force action defined by PWM_ActionQualifierEnum
 *             Only the following values are valid:
 *              - \ref FRC_DO_NOTHING
 *              - \ref FRC_SET_LOW
 *              - \ref FRC_SET_HIGH
 *
 * @example    // Get value from active register
 *             PWM_GetCHAContinuousForceOutputAction(PWM0);
 *             // Get value from shadow register
 *             PWM_GetShadowCHAContinuousForceOutputAction(PWM0);
 *
 ******************************************************************************/
#define PWM_GetCHAContinuousForceOutputAction(PWMx)                              \
    (((PWMx)->AQCSFRCA & AQCSFRCA_CSFA_Msk) >> AQCSFRCA_CSFA_Pos)

#define PWM_GetShadowCHAContinuousForceOutputAction(PWMx)                        \
    (((PWMx)->AQCSFRC & AQCSFRC_CSFA_Msk) >> AQCSFRC_CSFA_Pos)




/******************************************************************************
 * @brief      Get channel B software continuous force output action
 *
 * @param[in]  PWMx: Select the PWM module
 *
 * @return     Software continuous force action defined by PWM_ActionQualifierEnum
 *             Only the following values are valid:
 *              - \ref FRC_DO_NOTHING
 *              - \ref FRC_SET_LOW
 *              - \ref FRC_SET_HIGH
 *
 * @example    PWM_GetCHBContinuousForceOutputAction(PWM0);
 *
 ******************************************************************************/
#define PWM_GetCHBContinuousForceOutputAction(PWMx)                              \
    (((PWMx)->AQCSFRCA & AQCSFRCA_CSFB_Msk) >> AQCSFRCA_CSFB_Pos)

#define PWM_GetShadowCHBContinuousForceOutputAction(PWMx)                        \
    (((PWMx)->AQCSFRC & AQCSFRC_CSFB_Msk) >> AQCSFRC_CSFB_Pos)




/******************************************************************************
 * @brief      Set DBCTL/DBRED/DBFED load timing
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  DBCTL/DBRED/DBFED load timing defined by PWM_LoadTimingEnum
 *                     Only the following values are valid:
 *                      - \ref DBCTL_LOAD_ON_ZERO              
 *                      - \ref DBCTL_LOAD_ON_PERIOD            
 *                      - \ref DBCTL_LOAD_ON_ZERO_PERIOD       
 *                      - \ref DBCTL_LOAD_ON_IMMEDIATE        
 *                      - \ref DBRED_LOAD_ON_ZERO              
 *                      - \ref DBRED_LOAD_ON_PERIOD            
 *                      - \ref DBRED_LOAD_ON_ZERO_PERIOD       
 *                      - \ref DBRED_LOAD_ON_IMMEDIATE   
 *                      - \ref DBFED_LOAD_ON_ZERO              
 *                      - \ref DBFED_LOAD_ON_PERIOD            
 *                      - \ref DBFED_LOAD_ON_ZERO_PERIOD       
 *                      - \ref DBFED_LOAD_ON_IMMEDIATE    
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBCTLLoadTiming(PWMx,eMode)  ((PWMx)->DBCTL = ((PWMx)->DBCTL & ~DBCTL_DBCTLLOAD_Msk) | ((eMode) << DBCTL_DBCTLLOAD_Pos))
#define PWM_SetDBREDLoadTiming(PWMx,eMode)  ((PWMx)->DBCTL = ((PWMx)->DBCTL & ~DBCTL_DBREDLOAD_Msk) | ((eMode) << DBCTL_DBREDLOAD_Pos))
#define PWM_SetDBFEDLoadTiming(PWMx,eMode)  ((PWMx)->DBCTL = ((PWMx)->DBCTL & ~DBCTL_DBFEDLOAD_Msk) | ((eMode) << DBCTL_DBFEDLOAD_Pos))




/******************************************************************************
 * @brief      Lock DBCTL/DBRED/DBFED active value
 *             Active value in DBCTL[9:0]/DBRED/DBFED will not change
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_LockDBCTL(PWMx)                 ((PWMx)->DBCTL |= DBCTL_DBCTLLOCK_LOCK)
#define PWM_LockDBRED(PWMx)                 ((PWMx)->DBCTL |= DBCTL_DBREDLOCK_LOCK)
#define PWM_LockDBFED(PWMx)                 ((PWMx)->DBCTL |= DBCTL_DBFEDLOCK_LOCK)




/******************************************************************************
 * @brief      UnLock DBCTL/DBRED/DBFED active value
 *             Active value in DBCTL[9:0]/DBRED/DBFED will be updated when loading event occurred
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_UnlockDBCTL(PWMx)               ((PWMx)->DBCTL &= ~DBCTL_DBCTLLOCK_LOCK)
#define PWM_UnlockDBRED(PWMx)               ((PWMx)->DBCTL &= ~DBCTL_DBREDLOCK_LOCK)
#define PWM_UnlockDBFED(PWMx)               ((PWMx)->DBCTL &= ~DBCTL_DBFEDLOCK_LOCK)




/******************************************************************************
 * @brief      Enable/Disable Dead Band half cycle
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDBHalfCycle(PWMx)                                             \
    SET_BITS((PWMx)->DBCTL,DBCTL_CTLWE_ENABLE|DBCTL_HALFCYCLE_Msk)

#define PWM_DisableDBHalfCycle(PWMx)                                            \
    ((PWMx)->DBCTL = DBCTL_CTLWE_ENABLE | ((PWMx)->DBCTL & ~DBCTL_HALFCYCLE_Msk))




/******************************************************************************
 * @brief      Enable/Disable Dead Band delay one all edge, then output
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDBDualEdgeDelayMode(PWMx)                                         \
    SET_BITS((PWMx)->DBCTL,DBCTL_CTLWE_ENABLE|DBCTL_DUALEDGE_Msk)

#define PWM_DisableDBDualEdgeDelayMode(PWMx)                                        \
    ((PWMx)->DBCTL = DBCTL_CTLWE_ENABLE | ((PWMx)->DBCTL & ~DBCTL_DUALEDGE_Msk))




/******************************************************************************
 * @brief      Set Dead Band output A channel source
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eEdge:  Edge defined by PWM_DeadBandOutputSourceEnum
 *                     Only the following values are valid:
 *                      - \ref PWM_FALLING_EDGE_DELAY_PATH
 *                      - \ref PWM_RISING_EDGE_DELAT_PATH
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBOutputASource(PWMx,eEdge)                                      \
    ((PWMx)->DBCTL =                                                            \
            DBCTL_CTLWE_ENABLE | ( ((PWMx)->DBCTL & ~DBCTL_OUTASRC_Msk)         \
                                   |((eEdge) << DBCTL_OUTASRC_Pos))             \
    )




/******************************************************************************
 * @brief      Set Dead Band output B channel source
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eEdge:  Edge defined by PWM_DeadBandOutputSourceEnum
 *                     Only the following values are valid:
 *                      - \ref PWM_FALLING_EDGE_DELAY_PATH
 *                      - \ref PWM_RISING_EDGE_DELAT_PATH
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBOutputBSource(PWMx,eEdge)                                       \
    ((PWMx)->DBCTL =                                                             \
            DBCTL_CTLWE_ENABLE | ( ((PWMx)->DBCTL & ~DBCTL_OUTBSRC_Msk)          \
                                   |((eEdge) << DBCTL_OUTBSRC_Pos))              \
    )




/******************************************************************************
 * @brief      Set Dead Band falling edge output polarity
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eEdge:  eLvl defined by LEVEL
 *                     Only the following values are valid:
 *                      - \ref LOW
 *                      - \ref HIGH
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBFallingEdgeOutputPolarity(PWMx,eLvl)                           \
    ((PWMx)->DBCTL =                                                            \
            DBCTL_CTLWE_ENABLE | ( ((PWMx)->DBCTL & ~DBCTL_FEDPOL_Msk)         \
                                   |((eLvl) << DBCTL_FEDPOL_Pos))               \
    )




/******************************************************************************
 * @brief      Set Dead Band rising edge output polarity
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eEdge:  eLvl defined by LEVEL
 *                     Only the following values are valid:
 *                      - \ref LOW
 *                      - \ref HIGH
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBRisingEdgeOutputPolarity(PWMx,eLvl)                             \
    ((PWMx)->DBCTL =                                                             \
            DBCTL_CTLWE_ENABLE | ( ((PWMx)->DBCTL & ~DBCTL_REDPOL_Msk)          \
                                   |((eLvl) << DBCTL_REDPOL_Pos))                \
    )




/******************************************************************************
 * @brief      Set Dead Band falling edge delay input source
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eChn :  eChn defined by PWM_ChannelEnum
 *                     Only the following values are valid:
 *                      - \ref PWM_CHA
 *                      - \ref PWM_CHB
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBFallingEdgeInputSource(PWMx,eChn)                               \
    ((PWMx)->DBCTL =                                                             \
            DBCTL_CTLWE_ENABLE | ( ((PWMx)->DBCTL & ~DBCTL_FEDSRC_Msk)          \
                                   |((eChn) << DBCTL_FEDSRC_Pos))                \
    )




/******************************************************************************
 * @brief      Set Dead Band rising edge delay input source
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eChn :  eChn defined by PWM_ChannelEnum
 *                     Only the following values are valid:
 *                      - \ref PWM_CHA
 *                      - \ref PWM_CHB
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBRisingEdgeInputSource(PWMx,eChn)                               \
    ((PWMx)->DBCTL =                                                            \
            DBCTL_CTLWE_ENABLE | (((PWMx)->DBCTL & ~DBCTL_REDSRC_Msk)          \
                                  |((eChn) << DBCTL_REDSRC_Pos))                \
    )




/******************************************************************************
 * @brief      Enable/Disable Dead Band falling edge delay
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDBFallingEdgeDelay(PWMx)                                      \
    SET_BITS((PWMx)->DBCTL, DBCTL_CTLWE_ENABLE|DBCTL_FEDEN_Msk )

#define PWM_DisableDBFallingEdgeDelay(PWMx)                                     \
    ((PWMx)->DBCTL = DBCTL_CTLWE_ENABLE | ((PWMx)->DBCTL & ~DBCTL_FEDEN_Msk))




/******************************************************************************
 * @brief      Enable/Disable Dead Band rising edge delay
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDBRisingEdgeDelay(PWMx)                                      \
    SET_BITS((PWMx)->DBCTL, DBCTL_CTLWE_ENABLE|DBCTL_REDEN_Msk )

#define PWM_DisableDBRisingEdgeDelay(PWMx)                                     \
    ((PWMx)->DBCTL = DBCTL_CTLWE_ENABLE | ((PWMx)->DBCTL & ~DBCTL_REDEN_Msk))




/******************************************************************************
 * @brief      Set PWM dead band rising edge delay
 *
 * @param[in]  PWMx    : Select the PWM module
 * @param[in]  u32Delay: Rising edge delay, unit is based on PWM counter clock and Half clock enable
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBRED(PWMx,u16Delay)                 ((PWMx)->DBRED = (u16Delay))
#define PWM_SetDeadBandRisingDelay(PWMx,u16Delay)   ((PWMx)->DBRED = (u16Delay))




/******************************************************************************
 * @brief      Get PWM dead band effective rising edge delay
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     Active rising edge delay (16 bit), unit is PWM counter clock and Half clock enable
 *
 ******************************************************************************/
#define PWM_GetDBRED(PWMx)                  ((PWMx)->DBREDA)
#define PWM_GetDeadBandRisingDelay(PWMx)    ((PWMx)->DBREDA)




/******************************************************************************
 * @brief      Set PWM dead band falling edge delay
 *
 * @param[in]  PWMx    :  Select the PWM module
 * @param[in]  u32Delay:  Falling edge delay,  unit is based on PWM counter clock and Half clock enable
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetDBFED(PWMx,u16Delay)                 ((PWMx)->DBFED = (u16Delay))
#define PWM_SetDeadBandFallingDelay(PWMx,u16Delay)  ((PWMx)->DBFED = (u16Delay))




/******************************************************************************
 * @brief      Get PWM dead band effective falling edge delay
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     Active falling edge delay (16 bit), unit is PWM counter clock and Half clock enable
 *
 ******************************************************************************/
#define PWM_GetDBFED(PWMx)                  ((PWMx)->DBFEDA)
#define PWM_GetDeadBandFallingDelay(PWMx)   ((PWMx)->DBFEDA)




/******************************************************************************
 * @brief      Get PWM dead band shadow rising edge delay
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     Active rising edge delay (16 bit), unit is PWM counter clock
 *
 ******************************************************************************/
#define PWM_GetShadowDBRED(PWMx)            ((PWMx)->DBRED)




/******************************************************************************
 * @brief      Get PWM dead band shadow falling edge delay
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     Active falling edge delay (16 bit), unit is PWM counter clock
 *
 ******************************************************************************/
#define PWM_GetShadowDBFED(PWMx)            ((PWMx)->DBFED)




/******************************************************************************
 * @brief      Enable Debug mode as an CBC trip event
 *             PWM output will be triped to configured state when in Debug mode
 *
 *             Please remember  PWM_SetCHAOutputWhenTrip() and
 *             PWM_SetCHBOutputWhenTrip() to set the PWM output when trip
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableTripWhenDebug(PWMx)       ((PWMx)->TZSEL |= (TZSEL_CBCWE_ENABLE | TZSEL_DBGCBC_ENABLE))




/******************************************************************************
 * @brief      One-shot trip event select
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the one-shot trip events as defined by PWM_TripEventEnum
 *                    Multiple events can be ORed simultaneously
 * @param[in]  eType: Select the one-shot trip signal type as defined by PWM_TripOutputEnum
 *
 * @return     None
 *
 * @example    PWM_SetOneShotTripEvent(PWM0, TRIP_EVENT_TZ0, TRIP_OUTPUT_LATCH);
 *             PWM_SetOneShotTripEvent(PWM0, TRIP_EVENT_TZ0 | TRIP_EVENT_TZ1, TRIP_OUTPUT_LATCH);
 *
 ******************************************************************************/
#define PWM_SetOneShotTripEvent(PWMx,eEvt,eOutType)                            \
    ((PWMx)->TZSEL = ((eEvt) << TZSEL_TZ0OST_Pos) | ((eOutType) << TZSEL_OSTOUT_Pos) | TZSEL_OSTWE_ENABLE)




/******************************************************************************
 * @brief      CBC trip event select
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the CBC trip events as defined by PWM_TripEventEnum
 *                    Multiple events can be ORed simultaneously
 * @param[in]  eType: Select the CBC trip signal type as defined by PWM_TripOutputEnum
 * @return     None
 *
 * @example    PWM_SetCBCTripEvent(PWM0, TRIP_EVENT_TZ0, TRIP_OUTPUT_LATCH);
 *             PWM_SetCBCTripEvent(PWM0, TRIP_EVENT_TZ0 | TRIP_EVENT_TZ1, TRIP_OUTPUT_LATCH);
 *
 ******************************************************************************/
#define PWM_SetCBCTripEvent(PWMx,eEvt,eOutType)                                \
    ((PWMx)->TZSEL = ((eEvt) << TZSEL_TZ0CBC_Pos) | ((eOutType) << TZSEL_CBCOUT_Pos) | TZSEL_CBCWE_ENABLE)




/******************************************************************************
 * @brief      Get one-shot trip event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the one-shot trip events as defined by PWM_TripEventEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for non-zero bit occurred
 *
 * @example    PWM_GetOneShotTripEventFlag(PWM0, TRIP_EVENT_TZ0);
 *             PWM_GetOneShotTripEventFlag(PWM0, TRIP_EVENT_TZ0 | TRIP_EVENT_TZ1);
 *
 ******************************************************************************/
#define PWM_GetOneShotTripEventFlag(PWMx, eEvt)   ((PWMx)->TZFLG & (eEvt))




/******************************************************************************
 * @brief      Get CBC trip event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the CBC trip events as defined by PWM_TripEventEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for non-zero bit occurred
 *
 * @example    PWM_GetOneShotTripEventFlag(PWM0, TRIP_EVENT_TZ0);
 *             PWM_GetOneShotTripEventFlag(PWM0, TRIP_EVENT_TZ0 | TRIP_EVENT_TZ1);
 *
 ******************************************************************************/
#define PWM_GetCBCTripEventFlag(PWMx, eEvt)     (((PWMx)->TZFLG >> TZFLG_TZ0CBC_Pos) & (eEvt))




/******************************************************************************
 * @brief      Clear one-shot trip event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the one-shot trip events as defined by PWM_TripEventEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 * @example    PWM_ClearOneShotTripEventFlag(PWM0, TRIP_EVENT_TZ0);
 *             PWM_ClearOneShotTripEventFlag(PWM0, TRIP_EVENT_TZ0 | TRIP_EVENT_TZ1);
 *
 ******************************************************************************/
#define PWM_ClearOneShotTripEventFlag(PWMx, eEvt)   ((PWMx)->TZFLGCLR = (eEvt))




/******************************************************************************
 * @brief      Clear CBC trip event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the CBC trip events as defined by PWM_TripEventEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 * @example    PWM_ClearCBCTripEventFlag(PWM0, TRIP_EVENT_TZ0);
 *             PWM_ClearCBCTripEventFlag(PWM0, TRIP_EVENT_TZ0 | TRIP_EVENT_TZ1);
 *
 ******************************************************************************/
#define PWM_ClearCBCTripEventFlag(PWMx, eEvt)       ((PWMx)->TZFLGCLR = ((eEvt) << TZFLGCLR_TZ0CBC_Pos))




/******************************************************************************
 * @brief      Set PWMxA/B output pin state after trip event happen
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eAction:  Specifies the action after trip
 *                       Please refer to PWM_TripActionEnum
 *
 * @return     None
 *
 * @note       Actions for six scenarios should be explicitly specified
 *
 * @example    PWM_SetCHAOutputWhenTrip(PWM0, TZU_TRIP_AS_LOW |
 *                                            TZD_TRIP_AS_LOW |
 *                                            DCEVT0U_TRIP_DO_NOTHING |
 *                                            DCEVT0D_TRIP_DO_NOTHING |
 *                                            DCEVT1U_TRIP_DO_NOTHING |
 *                                            DCEVT1D_TRIP_DO_NOTHING);
 *                                            TZD_TRIP_AS_LOW | TZU_TRIP_DO_NOTHING);
 *             Wrong configuration!!
 *             PWM_SetCHAOutputWhenTrip(PWM0, TZU_TRIP_AS_LOW | TZU_TRIP_AS_HIGH  <-- CANNOT configure 2 actions for the same event
 *                                            TZD_TRIP_AS_LOW |
 *                                            DCEVT0U_TRIP_DO_NOTHING |
 *                                            DCEVT0D_TRIP_DO_NOTHING |
 *                                            DCEVT1U_TRIP_DO_NOTHING |
 *                                            DCEVT1D_TRIP_DO_NOTHING);
 *                                            TZD_TRIP_AS_LOW | TZU_TRIP_DO_NOTHING);
 *
 ******************************************************************************/
#define PWM_SetCHAOutputWhenTrip(PWMx,eAction)  ((PWMx)->TZACTL = (eAction))
#define PWM_SetCHBOutputWhenTrip(PWMx,eAction)  ((PWMx)->TZBCTL = (eAction))




/******************************************************************************
 * @brief      Enable/Disable trip-zone interrupt event
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the trip-zone interrupt event as defined in PWM_TripIntEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 * @example    PWM_EnableTripInt(PWM0, TRIP_INT_OST);
 *             PWM_EnableTripInt(PWM0, TRIP_INT_DCAEVT0 | TRIP_INT_DCAEVT1);
 *             PWM_DisableTripInt(PWM0, TRIP_INT_OST);
 *             PWM_DisableTripInt(PWM0, TRIP_INT_DCAEVT0 | TRIP_INT_DCAEVT1);
 *
 ******************************************************************************/
#define PWM_EnableTripInt(PWMx, eEvt)        ((PWMx)->TZIE |= (eEvt))
#define PWM_DisableTripInt(PWMx, eEvt)       ((PWMx)->TZIE &= ~(eEvt))




/******************************************************************************
 * @brief      Get trip-zone event raw flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the trip-zone interrupt event as defined in PWM_TripIntEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     0      - None of the queried interrupts occurred
 *             not 0  - Corresponding interrupts for non-zero bit occurred
 *
 * @example    PWM_GetTripIntRawFlag(PWM0, TRIP_INT_OST);
 *             PWM_GetTripIntRawFlag(PWM0, TRIP_INT_DCAEVT0 | TRIP_INT_DCAEVT1);
 *
 ******************************************************************************/
#define PWM_GetTripIntRawFlag(PWMx, eEvt)   (((PWMx)->TZIF >> TZIF_OSTRAW_Pos) & (eEvt))




/******************************************************************************
 * @brief      Get trip-zone interrupt flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the trip-zone interrupt event as defined in PWM_TripIntEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     0     - None of the queried interrupts occurred
 *             not 0 - Corresponding interrupts for non-zero bit occurred
 *
 * @example    PWM_GetTripIntRawFlag(PWM0, TRIP_INT_OST);
 *             PWM_GetTripIntRawFlag(PWM0, TRIP_INT_DCAEVT0 | TRIP_INT_DCAEVT1);
 *
 ******************************************************************************/
#define PWM_GetTripIntFlag(PWMx, eEvt)      ((PWMx)->TZIF & (eEvt))




/******************************************************************************
 * @brief      Clear trip-zone interrupt flag
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the trip-zone interrupt event as defined in PWM_TripIntEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 * @example    PWM_ClearTripInt(PWM0, TRIP_INT_OST);
 *             PWM_ClearTripInt(PWM0, TRIP_INT_DCAEVT0 | TRIP_INT_DCAEVT1);
 *
 ******************************************************************************/
#define PWM_ClearTripInt(PWMx, eEvt)        ((PWMx)->TZIC = (eEvt))




/******************************************************************************
 * @brief      Hardware clear cycle by cycle trip interrupt flag
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  eMode:  CBC trip status clear mode
 *                     Please refer to TZIC_CBCCLRMODE_xxxx
 *
 * @return     None
 *
 * @example    PWM_ClearCBCTripIntByHardware(PWM0, TZIC_CBCCLRMODE_CLEAR_ON_ZERO);
 *
 ******************************************************************************/
#define PWM_ClearCBCTripIntByHardware(PWMx,eMode) ((PWMx)->TZIC = (eMode) | TZIC_CBCCLRMODEWE_ENABLE)




/******************************************************************************
 * @brief      Force trip-zone interrupt
 *
 * @param[in]  PWMx:  Select the PWM module
 * @param[in]  eEvt:  Select the trip-zone interrupt event as defined in PWM_TripIntEnum
 *                    Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 * @example    PWM_ForceTripInt(PWM0, TRIP_INT_OST);
 *             PWM_ForceTripInt(PWM0, TRIP_INT_DCAEVT0 | TRIP_INT_DCAEVT1);
 *
 ******************************************************************************/
#define PWM_ForceTripInt(PWMx, eEvt)        ((PWMx)->TZFRC = (eEvt) | ((eEvt) << 8))




/******************************************************************************
 * @brief      Enable DCAH/DCAL/DCBH/DCBL trip events
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  eEvent:  Select the DC trip events
 *                      Please refer to PWM_DCTripEventEnum
 *
 * @return     None
 *
 * @example    PWM_EnableDCAHTripEvent(PWM0, DC_TRIP_COMP0L);
 *             PWM_EnableDCAHTripEvent(PWM0, DC_TRIP_COMP0H | DC_TRIP_TZ0);
 *
 ******************************************************************************/
#define PWM_EnableDCAHTripEvent(PWMx,eEvent)  ((PWMx)->DCAHTRIPSEL |= (eEvent))
#define PWM_EnableDCALTripEvent(PWMx,eEvent)  ((PWMx)->DCALTRIPSEL |= (eEvent))
#define PWM_EnableDCBHTripEvent(PWMx,eEvent)  ((PWMx)->DCBHTRIPSEL |= (eEvent))
#define PWM_EnableDCBLTripEvent(PWMx,eEvent)  ((PWMx)->DCBLTRIPSEL |= (eEvent))




/******************************************************************************
 * @brief      Disable DCAH/DCAL/DCBH/DCBL trip events
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  eEvent:  Select the DC trip events
 *                      Please refer to PWM_DCTripEventEnum
 *
 * @return     None
 *
 * @example    PWM_DisableDCAHTripEvent(PWM0, DC_TRIP_COMP0L);
 *             PWM_DisableDCAHTripEvent(PWM0, DC_TRIP_COMP0H | DC_TRIP_TZ0);
 *
 ******************************************************************************/
#define PWM_DisableDCAHTripEvent(PWMx,eEvent) ((PWMx)->DCAHTRIPSEL &= ~(eEvent))
#define PWM_DisableDCALTripEvent(PWMx,eEvent) ((PWMx)->DCALTRIPSEL &= ~(eEvent))
#define PWM_DisableDCBHTripEvent(PWMx,eEvent) ((PWMx)->DCBHTRIPSEL &= ~(eEvent))
#define PWM_DisableDCBLTripEvent(PWMx,eEvent) ((PWMx)->DCBLTRIPSEL &= ~(eEvent))




/******************************************************************************
 * @brief      Set raw DCAEVT0/DCAEVT1/DCBEVT0/DCBEVT1 event
 *
 * @param[in]  PWMx    :  Select the PWM module
 * @param[in]  eEvent  :  Select the Raw DC event
 *                        Please refer to PWM_RawDCEventEnum
 *
 * @return     None
 *
 * @example    PWM_SetRawDCAEVT0(PWM0, DCH_X_DCL_HIGH);
 *
 ******************************************************************************/
#define PWM_SetRawDCAEVT0(PWMx,eEvent)                                         \
    ((PWMx)->TZDCSEL = ((PWMx)->TZDCSEL & ~TZDCSEL_RAWDCAEVT0_Msk) | ((eEvent) << TZDCSEL_RAWDCAEVT0_Pos))

#define PWM_SetRawDCAEVT1(PWMx,eEvent)                                         \
    ((PWMx)->TZDCSEL = ((PWMx)->TZDCSEL & ~TZDCSEL_RAWDCAEVT1_Msk) | ((eEvent) << TZDCSEL_RAWDCAEVT1_Pos))

#define PWM_SetRawDCBEVT0(PWMx,eEvent)                                         \
    ((PWMx)->TZDCSEL = ((PWMx)->TZDCSEL & ~TZDCSEL_RAWDCBEVT0_Msk) | ((eEvent) << TZDCSEL_RAWDCBEVT0_Pos))

#define PWM_SetRawDCBEVT1(PWMx,eEvent)                                         \
    ((PWMx)->TZDCSEL = ((PWMx)->TZDCSEL & ~TZDCSEL_RAWDCBEVT1_Msk) | ((eEvent) << TZDCSEL_RAWDCBEVT1_Pos))




/******************************************************************************
 * @brief      Set final DCAEVT0/DCAEVT1/DCBEVT0/DCBEVT1 event
 *
 * @param[in]  PWMx    :  Select the PWM module
 * @param[in]  eEvent  :  Select the final DC event
 *                        Please refer to PWM_DCEventEnum
 *
 * @return     None
 *
 * @example    PWM_SetDCAEVT0(PWM0, DCEVT_FILTERED);
 *             PWM_SetDCBEVT0(PWM0, DCEVT_RAW);
 *
 ******************************************************************************/
#define PWM_SetDCAEVT0(PWMx,eEvent)                                            \
    ((PWMx)->DCACTL = ((PWMx)->DCACTL & ~DCACTL_EVT0SRCSEL_Msk) | ((eEvent) << DCACTL_EVT0SRCSEL_Pos))

#define PWM_SetDCAEVT1(PWMx,eEvent)                                            \
    ((PWMx)->DCACTL = ((PWMx)->DCACTL & ~DCACTL_EVT1SRCSEL_Msk) | ((eEvent) << DCACTL_EVT1SRCSEL_Pos))

#define PWM_SetDCBEVT0(PWMx,eEvent)                                            \
    ((PWMx)->DCBCTL = ((PWMx)->DCBCTL & ~DCBCTL_EVT0SRCSEL_Msk) | ((eEvent) << DCBCTL_EVT0SRCSEL_Pos))

#define PWM_SetDCBEVT1(PWMx,eEvent)                                            \
    ((PWMx)->DCBCTL = ((PWMx)->DCBCTL & ~DCBCTL_EVT1SRCSEL_Msk) | ((eEvent) << DCBCTL_EVT1SRCSEL_Pos))




/******************************************************************************
 * @brief      Enable/Disable DCAEVT0 trigger SYNC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDCAEVT0TriggerSync(PWMx)  ((PWMx)->DCACTL |= DCACTL_EVT0SYNCE_ENABLE)
#define PWM_DisableDCAEVT0TriggerSync(PWMx) ((PWMx)->DCACTL &= ~DCACTL_EVT0SYNCE_ENABLE)




/******************************************************************************
 * @brief      Enable/Disable DCBEVT0 trigger SYNC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDCBEVT0TriggerSync(PWMx)  ((PWMx)->DCBCTL |= DCBCTL_EVT0SYNCE_ENABLE)
#define PWM_DisableDCBEVT0TriggerSync(PWMx) ((PWMx)->DCBCTL &= ~DCBCTL_EVT0SYNCE_ENABLE)




/******************************************************************************
 * @brief      Enable/Disable DCAEVT0 trigger SOC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDCAEVT0TriggerSOC(PWMx)   ((PWMx)->DCACTL |= DCACTL_EVT0SOCE_ENABLE)
#define PWM_DisableDCAEVT0TriggerSOC(PWMx)  ((PWMx)->DCACTL &= ~DCACTL_EVT0SOCE_ENABLE)




/******************************************************************************
 * @brief      Enable/Disable DCBEVT0 trigger SOC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDCBEVT0TriggerSOC(PWMx)   ((PWMx)->DCBCTL |= DCBCTL_EVT0SOCE_ENABLE)
#define PWM_DisableDCBEVT0TriggerSOC(PWMx)  ((PWMx)->DCBCTL &= ~DCBCTL_EVT0SOCE_ENABLE)




/******************************************************************************
 * @brief      Set DC filter
 *
 * @param[in]  PWMx  :  Select the PWM module
 * @param[in]  eEvent:  Select the input event of the filter
 *                      Please refer to PWM_DCFilterInputEnum
 * @param[in]  eAlign:  Select the blank window alignment
 *                      Please refer to PWM_DCFilterAlignEnum
 *
 * @return     None
 *
 * @example    PWM_SetDCFilter(PWM0, DCF_FROM_RAW_DCAEVT0, DCF_ALIGN_ON_ZERO);
 *
 ******************************************************************************/
#define PWM_SetDCFilter(PWMx, eEvent, eAlign)                                  \
    ((PWMx)->DCFCTL = ((PWMx)->DCFCTL & ~(DCFCTL_SRCSEL_Msk | DCFCTL_PULSESEL_Msk)) | (eEvent) | (eAlign))




/******************************************************************************
 * @brief      Enable/Disable DC filter blanking window from other PWM module
 *
 * @param[in]  PWMx :  Select the PWM module
 * @param[in]  ePWMs:  Select other PWM module
 *                     Please refer to PWM_IncEnum
 *
 * @return     None
 *
 * @example    PWM_EnableDCFilterFromOtherPWM(PWM0, INC_PWM1);
 *             PWM_EnableDCFilterFromOtherPWM(PWM0, INC_PWM1 | INC_PWM2);
 *             PWM_DisableDCFilterFromOtherPWM(PWM0, INC_PWM1);
 *             PWM_DisableDCFilterFromOtherPWM(PWM0, INC_PWM1 | INC_PWM2);
 *
 ******************************************************************************/
#define PWM_EnableDCFilterFromOtherPWM(PWMx,ePWMs)  ((PWMx)->DCFCTL |= ((ePWMs) << DCFCTL_WIN0EN_Pos))
#define PWM_DisableDCFilterFromOtherPWM(PWMx,ePWMs) ((PWMx)->DCFCTL &= ~((ePWMs) << DCFCTL_WIN0EN_Pos))




/******************************************************************************
 * @brief      Enable/Disable DC filter blanking window
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDCFilterBlank(PWMx)       ((PWMx)->DCFCTL |= DCFCTL_BLANKEN_ENABLE)
#define PWM_DisableDCFilterBlank(PWMx)      ((PWMx)->DCFCTL &= ~DCFCTL_BLANKEN_ENABLE)




/******************************************************************************
 * @brief      Enable/Disable DC filter blanking window inversion
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableDCFilterBlankInvert(PWMx)   ((PWMx)->DCFCTL |= DCFCTL_BLANKINV_ENABLE)
#define PWM_DisableDCFilterBlankInvert(PWMx)  ((PWMx)->DCFCTL &= ~DCFCTL_BLANKINV_ENABLE)




/******************************************************************************
 * @brief      Set DC Filter window size and offset
 *
 * @param[in]  PWMx     :  Select the PWM module
 * @param[in]  u16Size  :  Size of the blank window (16 bit)
 *                         Unit: counter clock
 * @param[in]  u16Offset:  Offset of the blank window (16 bit)
 *                         Unit: counter clock
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void PWM_SetDCFilterBlankWindow(PWM_REGS *PWMx, uint16_t u16Size, uint16_t u16Offset)
{
    PWMx->DCFWINDOW = u16Size;
    PWMx->DCFOFFSET = u16Offset;
}




/******************************************************************************
 * @brief      Enable/Disable SOCA signal generation to trigger ADC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableSOCA(PWMx)                ((PWMx)->ETCTL |= ETCTL_SOCAEN_ENABLE)
#define PWM_DisableSOCA(PWMx)               ((PWMx)->ETCTL &= ~ETCTL_SOCAEN_ENABLE)




/******************************************************************************
 * @brief      Set the timing to generate PWM SOC(SOCA) ADC trigger pulse
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eTiming:  Specifies the event timing
 *                       Please refer to PWM_EventTimingEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSOCATiming(PWMx,eTiming)                                        \
    ((PWMx)->ETCTL = ((PWMx)->ETCTL & ~ETCTL_SOCASEL_Msk) | ((eTiming) << ETCTL_SOCASEL_Pos))




/******************************************************************************
 * @brief      Set the period to generate PWMA SOC(SOCA) ADC trigger pulse
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  ePeriod:  Specifies the period
 *                       Please refer to PWM_EventPeriodEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSOCAPeriod(PWMx,ePeriod)                                        \
    ((PWMx)->ETPS = ((PWMx)->ETPS & ~ETPS_SOCAPRD_Msk) | ((ePeriod) << ETPS_SOCAPRD_Pos))




/******************************************************************************
 * @brief      Enable/Disable SOCB signal generation to trigger ADC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableSOCB(PWMx)                ((PWMx)->ETCTL |= ETCTL_SOCBEN_ENABLE)
#define PWM_DisableSOCB(PWMx)               ((PWMx)->ETCTL &= ~ETCTL_SOCBEN_ENABLE)




/******************************************************************************
 * @brief      Set the timing to generate PWM SOC(SOCB) ADC trigger pulse
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eTiming:  Specifies the event timing
 *                       Please refer to PWM_EventTimingEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSOCBTiming(PWMx,eTiming)                                        \
    ((PWMx)->ETCTL = ((PWMx)->ETCTL & ~ETCTL_SOCBSEL_Msk) | ((eTiming) << ETCTL_SOCBSEL_Pos))




/******************************************************************************
 * @brief      Set the period to generate PWM SOC(SOCB) ADC trigger pulse
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  ePeriod:  Specifies the period
 *                       Please refer to PWM_EventPeriodEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSOCBPeriod(PWMx,ePeriod)                                        \
    ((PWMx)->ETPS = ((PWMx)->ETPS & ~ETPS_SOCBPRD_Msk) | ((ePeriod) << ETPS_SOCBPRD_Pos))




/******************************************************************************
 * @brief      Enable/Disable SOCC signal generation to trigger ADC
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableSOCC(PWMx)                ((PWMx)->ETCTL |= ETCTL_SOCCEN_ENABLE)
#define PWM_DisableSOCC(PWMx)               ((PWMx)->ETCTL &= ~ETCTL_SOCCEN_ENABLE)




/******************************************************************************
 * @brief      Set the timing to generate PWM SOC(SOCC) ADC trigger pulse
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eTiming:  Specifies the event timing
 *                       Please refer to PWM_EventTimingEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSOCCTiming(PWMx,eTiming)                                        \
    ((PWMx)->ETCTL = ((PWMx)->ETCTL & ~ETCTL_SOCCSEL_Msk) | ((eTiming) << ETCTL_SOCCSEL_Pos))




/******************************************************************************
 * @brief      Set the period to generate PWM SOC(SOCC) ADC trigger pulse
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  ePeriod:  Specifies the period
 *                       Please refer to PWM_EventPeriodEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_SetSOCCPeriod(PWMx,ePeriod)                                        \
    ((PWMx)->ETPS = ((PWMx)->ETPS & ~ETPS_SOCCPRD_Msk) | ((ePeriod) << ETPS_SOCCPRD_Pos))




/******************************************************************************
 * @brief      Enable/Disable time event interrupt
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_EnableTimeEventInt(PWMx)       ((PWMx)->ETCTL |= ETCTL_INTEN_ENABLE)
#define PWM_DisableTimeEventInt(PWMx)      ((PWMx)->ETCTL &= ~ETCTL_INTEN_ENABLE)




/******************************************************************************
 * @brief      Set the timing to generate PWM time event
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  eTiming:  Specifies the event timing
 *                       Please refer to PWM_EventTimingEnum
 *
 * @return     None
 *
 * @details    This function is to configure the timing to trigger time event
 *
 ******************************************************************************/
#define PWM_SetTimeEventIntTiming(PWMx,eTiming)                                 \
    WRITE_FIELD((PWMx)->ETCTL, ETCTL_INTSEL_Msk, ETCTL_INTSEL_Pos, (eTiming))




/******************************************************************************
 * @brief      Set/Get the period to generate PWM time event interrupt
 *
 * @param[in]  PWMx   :  Select the PWM module
 * @param[in]  ePeriod:  Specifies the period
 *                       Please refer to PWM_EventPeriodEnum
 *
 * @return     None
 * @return     PWM time event interrupt period
 *
 ******************************************************************************/
#define PWM_SetTimeEventIntPeriod(PWMx,ePeriod)                                 \
    WRITE_FIELD((PWMx)->ETPS, ETPS_INTPRD_Msk, ETPS_INTPRD_Pos, (ePeriod))

#define PWM_GetTimeEventIntPeriod(PWMx)                                         \
    READ_FIELD((PWMx)->ETPS, ETPS_INTPRD_Msk, ETPS_INTPRD_Pos)




/******************************************************************************
 * @brief      Get the PWM SOC ADC trigger event count
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     PWM SOC event count
 *
 ******************************************************************************/
#define PWM_GetSOCACount(PWMx)  (((PWMx)->ETPS & ETPS_SOCACNT_Msk) >> ETPS_SOCACNT_Pos)
#define PWM_GetSOCBCount(PWMx)  (((PWMx)->ETPS & ETPS_SOCBCNT_Msk) >> ETPS_SOCBCNT_Pos)
#define PWM_GetSOCCCount(PWMx)  (((PWMx)->ETPS & ETPS_SOCCCNT_Msk) >> ETPS_SOCCCNT_Pos)




/******************************************************************************
 * @brief      Get the PWM time event interrupt count
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     PWM time event interrupt count
 *
 ******************************************************************************/
#define PWM_GetTimeEventIntCount(PWMx)      (((PWMx)->ETPS & ETPS_INTCNT_Msk) >> ETPS_INTCNT_Pos)




/******************************************************************************
 * @brief      Clear time event interrupt flag
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_ClearTimeEventInt(PWMx)         ((PWMx)->ETCLR = ETCLR_INT_CLEAR)




/******************************************************************************
 * @brief      Clear SOCx event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_ClearSOCAEvent(PWMx)            ((PWMx)->ETCLR = ETCLR_SOCA_CLEAR)
#define PWM_ClearSOCBEvent(PWMx)            ((PWMx)->ETCLR = ETCLR_SOCB_CLEAR)
#define PWM_ClearSOCCEvent(PWMx)            ((PWMx)->ETCLR = ETCLR_SOCC_CLEAR)




/******************************************************************************
 * @brief      Get time event interrupt flag
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     0 - PWM interrupt did not occur
 *             not 0 - PWM interrupt occurred
 *
 ******************************************************************************/
#define PWM_GetTimeEventIntFlag(PWMx)       (((PWMx)->ETFLG & ETFLG_INT_Msk))




/******************************************************************************
 * @brief      Get SOCx event flag
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     0 - SOC event did not occur
 *             not 0 - An SOC event occurred
 *
 ******************************************************************************/
#define PWM_GetSOCAEventFlag(PWMx)          (((PWMx)->ETFLG & ETFLG_SOCA_Msk))
#define PWM_GetSOCBEventFlag(PWMx)          (((PWMx)->ETFLG & ETFLG_SOCB_Msk))
#define PWM_GetSOCCEventFlag(PWMx)          (((PWMx)->ETFLG & ETFLG_SOCC_Msk))




/******************************************************************************
 * @brief      Software force SOCx
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 * @note       It results in single trigger on time-event interrupt,
 *             which increase the event counter by 1 in ETPS register
 *
 ******************************************************************************/
#define PWM_ForceTimeEventInt(PWMx)         ((PWMx)->ETFRC = ETFRC_INT_FORCE | (ETFRC_INT_FORCE << 8))




/******************************************************************************
 * @brief      Software force SOCx
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 * @note       It results in single trigger on SOCx event,
 *             which increase the event counter by 1 in ETPS register
 *
 ******************************************************************************/
#define PWM_ForceSOCA(PWMx)                 ((PWMx)->ETFRC = ETFRC_SOCA_FORCE | (ETFRC_SOCA_FORCE << 8))
#define PWM_ForceSOCB(PWMx)                 ((PWMx)->ETFRC = ETFRC_SOCB_FORCE | (ETFRC_SOCB_FORCE << 8))
#define PWM_ForceSOCC(PWMx)                 ((PWMx)->ETFRC = ETFRC_SOCC_FORCE | (ETFRC_SOCC_FORCE << 8))




/******************************************************************************
 * @brief      Software force clock synchronization for PWM modules
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_ForceClockSync()                (PWMCFG->FRCSYNC = FRCSYNC_PWMCLK_FORCE)




/******************************************************************************
 * @brief      Software force PWM synchronization
 *
 * @param[in]  ePWMs:  Select the PWM module to be synchronized
 *                     Please refer to PWM_IncEnum
 *
 * @return     None
 *
 * @example    PWM_ForceSync(INC_PWM0);  // For PWM0 Sync
 *             PWM_ForceSync(INC_PWM0 | INC_PWM1);  // For PWM0 and PWM1 Sync
 *
 ******************************************************************************/
#define PWM_ForceSync(ePWMs)                (PWMCFG->FRCSYNC = (ePWMs))




/******************************************************************************
 * @brief      Enable/Disable PWM synchronization by GPIO
 *
 * @param[in]  ePWMs:  Select the PWM module to be synchronized
 *                     Please refer to PWM_IncEnum
 *
 * @return     None
 *
 * @example    PWM_EnableSyncFromGPIO(INC_PWM0);  // Enable PWM0 Sync by GPIO
 *             PWM_EnableSyncFromGPIO(INC_PWM0 | INC_PWM1);  // Enable PWM0 and PWM1 Sync by GPIO
 *             PWM_DisableSyncFromGPIO(INC_PWM0);  // Disable PWM0 Sync by GPIO
 *             PWM_DisableSyncFromGPIO(INC_PWM0 | INC_PWM1);  // Disable PWM0 and PWM1 Sync by GPIO
 *
 ******************************************************************************/
#define PWM_EnableSyncFromGPIO(ePWMs)       (PWMCFG->GPIOSYNCIEN |= (ePWMs))
#define PWM_DisableSyncFromGPIO(ePWMs)      (PWMCFG->GPIOSYNCIEN &= ~(ePWMs))




/******************************************************************************
 * @brief      Enable PWM synchronization by Timer
 *
 * @param[in]  ePWMs:  Select the PWM module to be synchronized
 *                     Please refer to PWM_IncEnum
 *
 * @return     None
 *
 * @example    PWM_EnableSyncFromTIMER0(INC_PWM0);  // Enable PWM0 Sync by Timer0
 *             PWM_EnableSyncFromTIMER0(INC_PWM0 | INC_PWM1);  // Enable PWM0 and PWM1 Sync by Timer0
 *
 ******************************************************************************/
#define PWM_EnableSyncFromTIMER0(ePWMs)     (PWMCFG->TMR0SYNCIEN |= (ePWMs))
#define PWM_EnableSyncFromTIMER1(ePWMs)     (PWMCFG->TMR1SYNCIEN |= (ePWMs))
#define PWM_EnableSyncFromTIMER2(ePWMs)     (PWMCFG->TMR2SYNCIEN |= (ePWMs))




/******************************************************************************
 * @brief      Disable PWM synchronization by Timer
 *
 * @param[in]  ePWMs:  Select the PWM module to be un-synchronized
 *                     Please refer to PWM_IncEnum
 *
 * @return     None
 *
 * @example    PWM_DisableSyncFromTIMER0(INC_PWM0);  // Disable PWM0 Sync by Timer0
 *             PWM_DisableSyncFromTIMER0(INC_PWM0 | INC_PWM1);  // Disable PWM0 and PWM1 Sync by Timer0
 *
 ******************************************************************************/
#define PWM_DisableSyncFromTIMER0(ePWMs)    (PWMCFG->TMR0SYNCIEN &= ~(ePWMs))
#define PWM_DisableSyncFromTIMER1(ePWMs)    (PWMCFG->TMR1SYNCIEN &= ~(ePWMs))
#define PWM_DisableSyncFromTIMER2(ePWMs)    (PWMCFG->TMR2SYNCIEN &= ~(ePWMs))




/******************************************************************************
 * @brief      Enable/Disable write access to the protected PWM registers
 *
 * @param[in]  PWMx:  Select the PWM module
 *
 * @return     None
 *
 ******************************************************************************/
#define PWM_WALLOW(PWMx)                ((PWMx)->PWMREGKEY = 0x1ACCE551)
#define PWM_WDIS(PWMx)                  ((PWMx)->PWMREGKEY = 0x0)




/******************************************************************************
 * @brief      Enable/Disable write access to the protected PWMCFG registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PWMCFG_WALLOW()                 (PWMCFG->PWMCFGREGKEY = 0x1ACCE551)
#define PWMCFG_WDIS()                   (PWMCFG->PWMCFGREGKEY = 0x0)




/**
 *  @brief  PWM Public Function Declaration
 */
void PWM_InitComplementaryPairChannel(PWM_REGS *PWMx, uint32_t u32PWMFreqHz, uint32_t u32DeadTimeNs);
void PWM_InitSingleChannel(PWM_REGS *PWMx, PWM_ChannelEnum ePWM_CH, uint32_t u32PWMFreqHz);

void PWM_SetTZ0FromGPIO(PIN_NameEnum ePin, uint8_t ePinLevel);
void PWM_SetTZ1FromGPIO(PIN_NameEnum ePin, uint8_t ePinLevel);
void PWM_SetTZ2FromGPIO(PIN_NameEnum ePin, uint8_t ePinLevel);
void PWM_SetTZ3FromGPIO(PIN_NameEnum ePin, uint8_t ePinLevel);
void PWM_SetTZ4FromGPIO(PIN_NameEnum ePin, uint8_t ePinLevel);

void PWM_SetSyncFromGPIO(PIN_NameEnum ePin, uint8_t ePinLevel);

uint32_t PWM_CalculateSyncReloadValue(uint32_t u32TBPRD, PWM_CounterModeEnum eCntMode, uint8_t ePHSDIR, uint32_t u32SyncVal, uint32_t u32TBClkDiv);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* PWM_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
