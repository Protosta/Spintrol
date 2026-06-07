/*******************************************************************************
 * @file     phcomp.h
 * @brief    Phase comparator driver header file.
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


#ifndef PHCOMP_H
#define PHCOMP_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  Phase comparator selection
 */
typedef enum
{
    PHCOMP_U                        = 1U,           /*!< PHCOMP_U           */
    PHCOMP_V                        = 2U,           /*!< PHCOMP_V           */
    PHCOMP_W                        = 4U,           /*!< PHCOMP_W           */
} PHCOMP_ComparatorSelEnum;




/**
 *  @brief  PHCOMP interrupt type definition
 */
typedef enum
{
    PHCOMP_INT_ALL                  = (0x7FU),      /*!< Used for all interrupts                    */
    PHCOMP_INT_GLOBAL               = (1U << 6),    /*!< Global Interrupt Flag
                                                         Only used for query or clear interrupt flag*/
    PHCOMP_INT_PHW_ZERO_CROSS       = (3U << 4),    /*!< W-Phase zero-cross interrupt               */
    PHCOMP_INT_PHW_ZERO_CROSS_HIGH  = (1U << 5),    /*!< W-Phase zero-cross to high interrupt       */
    PHCOMP_INT_PHW_ZERO_CROSS_LOW   = (1U << 4),    /*!< W-Phase zero-cross to low interrupt        */
    PHCOMP_INT_PHV_ZERO_CROSS       = (3U << 2),    /*!< V-Phase zero-cross interrupt               */
    PHCOMP_INT_PHV_ZERO_CROSS_HIGH  = (1U << 3),    /*!< V-Phase zero-cross to high interrupt       */
    PHCOMP_INT_PHV_ZERO_CROSS_LOW   = (1U << 2),    /*!< V-Phase zero-cross to low interrupt        */
    PHCOMP_INT_PHU_ZERO_CROSS       = (3U << 0),    /*!< U-Phase zero-cross interrupt               */
    PHCOMP_INT_PHU_ZERO_CROSS_HIGH  = (1U << 1),    /*!< U-Phase zero-cross to high interrupt       */
    PHCOMP_INT_PHU_ZERO_CROSS_LOW   = (1U << 0)     /*!< U-Phase zero-cross to low interrupt        */
} PHCOMP_IntEnum;




/**
 *  @brief  Phase comparator input channel selection
 */
typedef enum
{
    PHCOMP_FROM_PHU                 = 0U,           /*!< PHU pin            */
    PHCOMP_FROM_PHV                 = 1U,           /*!< PHV pin            */
    PHCOMP_FROM_PHW                 = 2U,           /*!< PHW pin            */
    PHCOMP_FROM_ANA_IN0             = 3U,           /*!< ANA_IN0 pin        */
    PHCOMP_FROM_ANA_IN1             = 4U,           /*!< ANA_IN1 pin        */
    PHCOMP_FROM_ANA_IN2             = 5U,           /*!< ANA_IN2 pin        */
    PHCOMP_FROM_ANA_IN3             = 6U,           /*!< ANA_IN3 pin        */
    PHCOMP_FROM_ANA_IN4             = 7U,           /*!< ANA_IN4 pin        */
} PHCOMP_InputChannelEnum;




/**
 *  @brief  Phase comparator reference selection
 */
typedef enum
{
    PHCOMP_REF_PHC                  = 0U,           /*!< PHC pin            */
    PHCOMP_REF_DAC1                 = 1U,           /*!< DAC1 output        */
    PHCOMP_REF_DAC2                 = 2U,           /*!< DAC2 output        */
    PHCOMP_REF_ANA_IN0              = 3U,           /*!< ANA_IN0 pin        */
    PHCOMP_REF_ANA_IN1              = 4U,           /*!< ANA_IN1 pin        */
    PHCOMP_REF_ANA_IN2              = 5U,           /*!< ANA_IN2 pin        */
    PHCOMP_REF_ANA_IN3              = 6U,           /*!< ANA_IN3 pin        */
    PHCOMP_REF_ANA_IN4              = 7U,           /*!< ANA_IN4 pin        */
} PHCOMP_ReferenceEnum;




/**
 *  @brief  Phase Comparator Hysteresis selection
 */
typedef enum
{
    PHCOMP_HYST_0_MV                = 0UL,          /*!< Hysteresis 0  mV   */
    PHCOMP_HYST_12_MV               = 1UL,          /*!< Hysteresis 12 mV   */
    PHCOMP_HYST_24_MV               = 2UL,          /*!< Hysteresis 24 mV   */
    PHCOMP_HYST_36_MV               = 3UL,          /*!< Hysteresis 36 mV   */
} PHCOMP_HystSelEnum;




/**
 *  @brief  PHCOMP operation mode Definition
 */
typedef enum
{
    PHCOMP_BEMF                     = 0x0U,         /*!< Phase comparator mode for back EMF sensing  */
    PHCOMP_NORMAL                   = 0x1U,         /*!< Normal voltage comparator                   */
} PHCOMP_ModeEnum;




/******************************************************************************
 * @brief      Enable Phase Comparator
 *
 * @param[in]  ePHCOMP: Phase comparator selection defined by PHCOMP_ComparatorSelEnum
 *
 * @return     None
 *
 * @example    PHCOMP_Enable(PHCOMP_U|PHCOMP_V|PHCOMP_W);
 *
 ******************************************************************************/
#define PHCOMP_Enable(ePHCOMP)              (PHCOMP->PHCOMPCTL                  \
            |= ((((ePHCOMP)&PHCOMP_U) << 0U)                                    \
            |   (((ePHCOMP)&PHCOMP_V) << 3U)                                    \
            |   (((ePHCOMP)&PHCOMP_W) << 6U)))



/******************************************************************************
 * @brief      Disable Phase Comparator
 *
 * @param[in]  ePHCOMP: Phase comparator selection defined by PHCOMP_ComparatorSelEnum
 *
 * @return     None
 *
 * @example    PHCOMP_Disable(PHCOMP_U|PHCOMP_V|PHCOMP_W);
 *
 ******************************************************************************/
#define PHCOMP_Disable(ePHCOMP)             (PHCOMP->PHCOMPCTL                  \
            &= ~((((ePHCOMP)&PHCOMP_U) << 0U)                                   \
             |   (((ePHCOMP)&PHCOMP_V) << 3U)                                   \
             |   (((ePHCOMP)&PHCOMP_W) << 6U)))




/******************************************************************************
 * @brief      Get Phase Comparator status
 *
 * @param[in]  ePHCOMP: Phase comparator selection defined by PHCOMP_ComparatorSelEnum
 *
 * @return     0 - The phase is not Enable
 *             others - The phase is Enable

 * @example    PHCOMP_IsEnable(PHCOMP_U)
 *
 ******************************************************************************/
__STATIC_INLINE uint32_t PHCOMP_IsEnable(PHCOMP_ComparatorSelEnum ePHCOMP)
{
    uint32_t u32flag = 0x0U;

    if (((ePHCOMP) & PHCOMP_U) != 0x0U)
    {
        u32flag |= (PHCOMP->PHCOMPCTL & PHCOMPCTL_PHUEN_Msk);
    }
    if (((ePHCOMP) & PHCOMP_V) != 0x0U)
    {
        u32flag |= (PHCOMP->PHCOMPCTL & PHCOMPCTL_PHVEN_Msk);
    }
    if (((ePHCOMP) & PHCOMP_W) != 0x0U)
    {
        u32flag |= (PHCOMP->PHCOMPCTL & PHCOMPCTL_PHWEN_Msk);
    }
    return u32flag;
}




/******************************************************************************
 * @brief      Select input channel
 *
 * @param[in]  ePHCOMP: Phase comparator selection defined by PHCOMP_ComparatorSelEnum
 * @param[in]  eCH:     Channel selection defined by PHCOMP_InputChannelEnum
 *
 * @return     None
 *
 * @example    PHCOMP_SelectChannel(PHCOMP_U, PHCOMP_FROM_ANA_IN0);
 *
 ******************************************************************************/
#define PHCOMP_SelectChannel(ePHCOMP, eCH)                                      \
    {                                                                           \
        if ( (ePHCOMP) == PHCOMP_U )                                            \
        {                                                                       \
            PHCOMP->PHCOMPCTL &= ~(PHCOMPCTL_PHUSEL_Msk);                       \
            PHCOMP->PHCOMPCTL |= (eCH << PHCOMPCTL_PHUSEL_Pos);                 \
        }                                                                       \
        else if ( (ePHCOMP) == PHCOMP_V )                                       \
        {                                                                       \
            PHCOMP->PHCOMPCTL &= ~(PHCOMPCTL_PHVSEL_Msk);                       \
            PHCOMP->PHCOMPCTL |= (eCH << PHCOMPCTL_PHVSEL_Pos);                 \
        }                                                                       \
        else if ( (ePHCOMP) == PHCOMP_W )                                       \
        {                                                                       \
            PHCOMP->PHCOMPCTL &= ~(PHCOMPCTL_PHWSEL_Msk);                       \
            PHCOMP->PHCOMPCTL |= (eCH << PHCOMPCTL_PHWSEL_Pos);                 \
        }                                                                       \
    }




/******************************************************************************
 * @brief      Select referece
 *
 * @param[in]  eRef:    Reference selection defined by PHCOMP_ReferenceEnum
 *
 * @return     None
 *
 * @example    PHCOMP_SelectReference(PHCOMP_REF_PHC);
 *
 ******************************************************************************/
#define PHCOMP_SelectReference(eRef)                                            \
    (PHCOMP->PHCOMPCTL = (PHCOMP->PHCOMPCTL & ~PHCOMPCTL_PHREFSEL_Msk) | ((eRef) << PHCOMPCTL_PHREFSEL_Pos))




/******************************************************************************
 * @brief      Select referece
 *
 * @param[in]  eHyst:   Hysterisis selection defined by PHCOMP_HystSelEnum
 *
 * @return     None
 *
 * @example    PHCOMP_SetHysteresis(eHyst);
 *
 ******************************************************************************/
#define PHCOMP_SetHysteresis(eHyst)                                             \
    (PHCOMP->PHCOMPCTL = (PHCOMP->PHCOMPCTL & ~PHCOMPCTL_HYSTSEL_Msk) | ((eHyst) << PHCOMPCTL_HYSTSEL_Pos))





/******************************************************************************
 * @brief      Set comparator mode
 *
 * @param[in]  eMode:  comparator mode defined by PHCOMP_ModeEnum
 *                     Following values are valid:
 *                       - \ref PHCOMP_BEMF
 *                       - \ref PHCOMP_NORMAL
 *
 * @return     None
 *
 ******************************************************************************/
#define PHCOMP_SetMode(eMode)                                                   \
    WRITE_FIELD(PHCOMP->PHCOMPCTL, PHCOMPCTL_MODE_Msk, PHCOMPCTL_MODE_Pos, (eMode))




/******************************************************************************
 * @brief      Get phase comparator output status
 *
 * @param[in]  ePHCOMP: Phase comparator selection defined by PHCOMP_ComparatorSelEnum
 *
 * @return     0 - Phase realtime filtered output status is Low
 *             others - Phase realtime filtered output status is High
 *
 * @example    PHCOMP_GetOutputStatus(PHCOMP_U|PHCOMP_V|PHCOMP_W)
 *
 ******************************************************************************/
#define PHCOMP_GetFilterOutputStatus(ePHCOMP)       (PHCOMP->PHCOMPSTS & (ePHCOMP))
#define PHCOMP_GetOriginalOutputStatus(ePHCOMP)     (PHCOMP->PHCOMPSTS & ((ePHCOMP) << 3U))




/******************************************************************************
 * @brief      Enable interrupt
 *
 * @param[in]  ePHCOMPInt: Phase comparator selection defined by PHCOMP_IntEnum
 *
 * @return     None
 *
 * @example    PHCOMP_EnableInt(PHCOMP_INT_ALL)
 *
 ******************************************************************************/
#define PHCOMP_EnableInt(ePHCOMPInt)           (PHCOMP->PHCOMPIE |= ((ePHCOMPInt)))




/******************************************************************************
 * @brief      Disable interrupt
 *
 * @param[in]  ePHCOMPInt: Phase comparator selection defined by PHCOMP_IntEnum
 *
 * @return     None
 *
 * @example    PHCOMP_DisableInt(PHCOMP_INT_PHU_ZERO_CROSS_HIGH)
 *
 ******************************************************************************/
#define PHCOMP_DisableInt(ePHCOMPInt)          (PHCOMP->PHCOMPIE &= ~((ePHCOMPInt)))




/******************************************************************************
 * @brief      Clear interrupt
 *
 * @param[in]  ePHCOMPInt: Phase comparator selection defined by PHCOMP_IntEnum
 *
 * @return     None
 *
 * @example    PHCOMP_ClearInt(PHCOMP_INT_PHU_ZERO_CROSS|PHCOMP_INT_PHV_ZERO_CROSS|PHCOMP_INT_PHW_ZERO_CROSS)
 *
 ******************************************************************************/
#define PHCOMP_ClearInt(ePHCOMPInt)            (PHCOMP->PHCOMPIC = (ePHCOMPInt))




/******************************************************************************
 * @brief      Get event raw flag
 *
 * @param[in]  ePHCOMPInt: Phase comparator selection defined by PHCOMP_IntEnum
 *
 * @return     0 - Indicates no output zero-cross event occurred
 *             others - Indicates zero-cross event occurred
 *
 * @example    PHCOMP_GetIntRawFlag(PHCOMP_INT_PHU_ZERO_CROSS|PHCOMP_INT_PHV_ZERO_CROSS|PHCOMP_INT_PHW_ZERO_CROSS)
 *
 ******************************************************************************/
#define PHCOMP_GetIntRawFlag(ePHCOMPInt)        (PHCOMP->PHCOMPRAWIF & (ePHCOMPInt))




/******************************************************************************
 * @brief      Get interrupt flag
 *
 * @param[in]  ePHCOMPInt: Phase comparator selection defined by PHCOMP_IntEnum
 *
 * @return     0 - Indicates no interrupt occurred
 *             others - Indicates interrupt occurred
 *
 * @example    PHCOMP_GetIntFlag(PHCOMP_INT_PHU_ZERO_CROSS|PHCOMP_INT_PHV_ZERO_CROSS|PHCOMP_INT_PHW_ZERO_CROSS)
 *
 ******************************************************************************/
#define PHCOMP_GetIntFlag(ePHCOMPInt)         (PHCOMP->PHCOMPIF & (ePHCOMPInt))




/******************************************************************************
 * @brief      Reset finite state machine for BEMF phase comparator mode
 *
 * @param[in]  ePHCOMP: Phase comparator selection defined by PHCOMP_ComparatorSelEnum
 *
 * @return     None
 *
 * @example    PHCOMP_ResetFSM(PHCOMP_U|PHCOMP_V|PHCOMP_W)
 *
 ******************************************************************************/
#define PHCOMP_ResetFSM(ePHCOMP)            (PHCOMP->PHCOMPRST = (ePHCOMP))



/******************************************************************************
 * @brief      Set blank window size and offset
 *
 * @param[in]  u16Size  :  Size of the blank window (16 bit)
 *                         Unit: counter clock
 * @param[in]  u16Offset:  Offset of the blank window (16 bit)
 *                         Unit: counter clock
 *
 * @return     None
 *
 ******************************************************************************/
#define PHCOMP_SetBlankWindow(u16Size, u16Offset)   (PHCOMP->PHCOMPBLANK = ((u16Size) << PHCOMPBLANK_WINSIZE_Pos) | (u16Offset))




/******************************************************************************
 * @brief      Set PHCOMP filter clock dividing ratio
 *
 * @param[in]  u16ClkDiv:  Dividing ratio (1~1024)
 *
 * @return     None
 *
 ******************************************************************************/
#define PHCOMP_SetFilterClockDiv(u16ClkDiv)         (PHCOMP->PHCOMPFILTER = (PHCOMP->PHCOMPFILTER & ~PHCOMPFILTER_FLTDIV_Msk) | ((u16ClkDiv - 1) << PHCOMPFILTER_FLTDIV_Pos))




/******************************************************************************
 * @brief      Enable write access to protected Phase Comparison Register
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PHCOMP_WALLOW()            (PHCOMP->PHCOMPREGKEY = 0x1ACCE551U)
#define PHCOMP_WDIS()              (PHCOMP->PHCOMPREGKEY = 0x0U)



/**
 *  @brief  PHCOMP Public Function Declaration
 */
void PHCOMP_SetFilterWindow(uint8_t u8WinSize, uint8_t u8Threshold);
void PHCOMP_SetFilterWindowTimeNs(uint32_t u32SizeTimeNS, uint32_t u32ThresholdTimeNS);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* PHCOMP_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
