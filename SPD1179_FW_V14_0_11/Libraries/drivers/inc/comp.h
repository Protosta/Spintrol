/******************************************************************************
 * @file     comp.h
 * @brief    Comparator driver header file.
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


#ifndef __COMP_H
#define __COMP_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  Comparator selection
 */
typedef enum
{
    COMP_L               = 1U,              /*!< COMPL   */
    COMP_H               = 2U,              /*!< COMPH   */
} COMP_ComparatorSelEnum;




/**
 *  @brief  Comparator input channel selection
 */
typedef enum
{
    COMP_FROM_DPGAN_OUT   = 0U,             /*!< Negative output of differential PGA  */
    COMP_FROM_DPGAP_OUT   = 1U,             /*!< Positive output of differential PGA  */
    COMP_FROM_SPGA_OUT    = 2U,             /*!< Output of single-ended PGA           */
    COMP_FROM_ANA_IN0     = 3U,             /*!< ANA_IN0 input from GPIO0             */
    COMP_FROM_ANA_IN1     = 4U,             /*!< ANA_IN1 input from GPIO1             */
    COMP_FROM_ANA_IN2     = 5U,             /*!< ANA_IN2 input from GPIO2             */
    COMP_FROM_ANA_IN3     = 6U,             /*!< ANA_IN3 input from GPIO3             */
    COMP_FROM_ANA_IN4     = 7U,             /*!< ANA_IN4 input from GPIO4             */
} COMP_InputChannelEnum;




/**
 *  @brief  Comparator output selection
 */
typedef enum
{
    COMP_OUTPUT_ORIGINAL                        = 0,    /*!< Original output                                                    */
    COMP_OUTPUT_SYNC                            = 1,    /*!< Synchronous output with PWM clock                                  */
    COMP_OUTPUT_FILTERED                        = 2,    /*!< Digital filter output                                              */
    COMP_OUTPUT_LATCHED                         = 3,    /*!< Latched digital filter output                                      */
    COMP_OUTPUT_ORIGINAL_OR_LATCHED             = 4,    /*!< Original output or Latched digital filter output                   */
    COMP_OUTPUT_SYNC_OR_LATCHED                 = 5,    /*!< Synchronous output with PWM clock or Latched digital filter output */
    COMP_OUTPUT_FILTERED_OR_LATCHED             = 6,    /*!< Digital filter output or the latched one                           */
    COMP_OUTPUT_ORIGINAL_OR_FILTERED_OR_LATCHED = 7,    /*!< Original output or Synchronous output with PWM clock or Latched digital filter output */
} COMP_OutputSelEnum;




/**
 *  @brief  Comparator hysteresis selection
 */
typedef enum
{
    COMP_HYST_0_MV        = 0,                /*!< Hysteresis 0  mV */
    COMP_HYST_12_MV       = 1,                /*!< Hysteresis 12 mV */
    COMP_HYST_24_MV       = 2,                /*!< Hysteresis 24 mV */
    COMP_HYST_36_MV       = 3,                /*!< Hysteresis 36 mV */
} COMP_HystSelEnum;




/**
 *  @brief  DAC selection
 */
typedef enum
{
    DAC0                  = 0,                /*!< DAC0     */
    DAC1                  = 1,                /*!< DAC1     */
    DAC2                  = 2,                /*!< DAC2     */
} COMP_DACSelEnum;




/**
 *  @brief  DAC load timing selection
 */
typedef enum
{
    SHADOW_LOAD_MODE      = 0,                /*!< Shadow load mode   */
    DIRECT_LOAD_MODE      = 1,                /*!< Direct load mode   */
} COMP_DACLoadTimingEnum;




/******************************************************************************
 * @brief      Enable comparator
 *
 * @param[in]  eComp:  Comparator selection defined by COMP_ComparatorSelEnum
 *                     COMP_L is for under-voltage protection
 *                     COMP_H is for over-voltage protection
 *
 *                     COMPL = 1 when input value < Reference value
 *                     COMPH = 1 when input value > Reference value
 *
 * @return     None
 *
 * @example    COMP_Enable(COMP_L);
 *
 ******************************************************************************/
#define COMP_Enable(eCOMP)                  (COMP->COMPCTL |= (eCOMP))




/******************************************************************************
 * @brief      Disable comparator
 *
 * @param[in]  eComp:  Comparator selection defined by COMP_ComparatorSelEnum
 *                     COMP_L is for under-voltage protection
 *                     COMP_H is for over-voltage protection
 *
 *                     COMPL = 1 when input value < Reference value
 *                     COMPH = 1 when input value > Reference value
 *
 * @return     None
 *
 * @example    COMP_Disable(COMP_L);
 *
 ******************************************************************************/
#define COMP_Disable(eCOMP)                 (COMP->COMPCTL &= ~(eCOMP))




/******************************************************************************
 * @brief      Select input channel
 *
 * @param[in]  eComp:  Comparator selection defined by COMP_ComparatorSelEnum
 *                     It is a dummy parameter here so as to be compatiable with
 *                     SDK functions for other products
 * @param[in]  eCH  :  Channel selection defined by COMP_InputChannelEnum
 *
 * @return     None
 *
 * @example    COMP_SelectChannel(COMP_L, COMP_FROM_ANA_IN0);
 *
 ******************************************************************************/
#define COMP_SelectChannel(eCOMP, eCH)                                          \
    (COMP->COMPCTL = (COMP->COMPCTL & ~COMPCTL_INSEL_Msk) | ((eCH) << COMPCTL_INSEL_Pos))




/******************************************************************************
 * @brief      Set comparator hysteresis
 *
 * @param[in]  eComp   :  Comparator selection defined by COMP_ComparatorSelEnum
 *                        It is a dummy parameter here so as to be compatiable with
 *                        SDK functions for other products
 * @param[in]  eHystSel:  Select the hysteresis
 *                        Please refer to COMP_HystSelEnum
 *
 * @return     None
 *
 * @example    COMP_SetHysteresis(COMP_L, COMP_HYST_12_MV);
 *
 ******************************************************************************/
#define COMP_SetHysteresis(eCOMP, eHystSel)                                     \
    (COMP->COMPCTL = (COMP->COMPCTL & ~COMPCTL_HYSTSEL_Msk) | ((eHystSel) << COMPCTL_HYSTSEL_Pos))




/******************************************************************************
 * @brief      Set output type
 *
 * @param[in]  eCOMP     : Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  eOutputSel: Output selection defined by COMP_OutputSelEnum
 *
 * @return     None
 *
 * @example    COMP_SetOutputType(COMP_L, COMP_OUTPUT_FILTERED)
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetOutputType(COMP_ComparatorSelEnum eCOMP, COMP_OutputSelEnum eOutputSel)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL = (COMP->COMPLCTL & ~(COMPLCTL_SEL4PWM_Msk | COMPLCTL_SEL4GPIO_Msk)) |
                             (eOutputSel << COMPLCTL_SEL4PWM_Pos) |
                             (eOutputSel << COMPLCTL_SEL4GPIO_Pos);
            break;

        case COMP_H:
            COMP->COMPHCTL = (COMP->COMPHCTL & ~(COMPHCTL_SEL4PWM_Msk | COMPHCTL_SEL4GPIO_Msk)) |
                             (eOutputSel << COMPHCTL_SEL4PWM_Pos) |
                             (eOutputSel << COMPHCTL_SEL4GPIO_Pos);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set output type for PWM
 *
 * @param[in]  eCOMP     : Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  eOutputSel: Output selection defined by COMP_OutputSelEnum
 *
 * @return     None
 *
 * @example    COMP_SetOutputTypeForPWM(COMP_L, COMP_OUTPUT_FILTERED)
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetOutputTypeForPWM(COMP_ComparatorSelEnum eCOMP, COMP_OutputSelEnum eOutputSel)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL = (COMP->COMPLCTL & ~COMPLCTL_SEL4PWM_Msk) | (eOutputSel << COMPLCTL_SEL4PWM_Pos);
            break;

        case COMP_H:
            COMP->COMPHCTL = (COMP->COMPHCTL & ~COMPHCTL_SEL4PWM_Msk) | (eOutputSel << COMPHCTL_SEL4PWM_Pos);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set output type for GPIO
 *
 * @param[in]  eCOMP     : Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  eOutputSel: Output selection defined by COMP_OutputSelEnum
 *
 * @return     None
 *
 * @example    COMP_SetOutputTypeForGPIO(COMP_L, COMP_OUTPUT_FILTERED)
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetOutputTypeForGPIO(COMP_ComparatorSelEnum eCOMP, COMP_OutputSelEnum eOutputSel)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL = (COMP->COMPLCTL & ~COMPLCTL_SEL4GPIO_Msk) | (eOutputSel << COMPLCTL_SEL4GPIO_Pos);
            break;

        case COMP_H:
            COMP->COMPHCTL = (COMP->COMPHCTL & ~COMPHCTL_SEL4GPIO_Msk) | (eOutputSel << COMPHCTL_SEL4GPIO_Pos);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Reset comparator filter
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_ResetFilter(COMP_ComparatorSelEnum eCOMP)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL |= COMPLCTL_FLTRST_RESET;
            break;

        case COMP_H:
            COMP->COMPHCTL |= COMPHCTL_FLTRST_RESET;
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set comparator output active polarity for GPIO and PWM
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  eLevel: Force polarity defined by LEVEL
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetOutputPolarity(COMP_ComparatorSelEnum eCOMP, LEVEL eLevel)
{
    switch (eCOMP)
    {
        case COMP_L:
            MODIFY_REG(COMP->COMPLCTL,                                                \
                       COMPLCTL_POL4GPIO_Msk | COMPLCTL_POL4PWM_Msk,                    \
                       (eLevel << COMPLCTL_POL4GPIO_Pos) | (eLevel << COMPLCTL_POL4PWM_Pos));
            break;

        case COMP_H:
            MODIFY_REG(COMP->COMPHCTL,                                                \
                       COMPHCTL_POL4GPIO_Msk | COMPHCTL_POL4PWM_Msk,                    \
                       (eLevel << COMPHCTL_POL4GPIO_Pos) | (eLevel << COMPHCTL_POL4PWM_Pos));
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set comparator output active polarity for PWM
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  eLevel: Force polarity defined by LEVEL
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetOutputPolarityForPWM(COMP_ComparatorSelEnum eCOMP, LEVEL eLevel)
{
    switch (eCOMP)
    {
        case COMP_L:
            MODIFY_REG(COMP->COMPLCTL, COMPLCTL_POL4PWM_Msk, (eLevel << COMPLCTL_POL4PWM_Pos));
            break;

        case COMP_H:
            MODIFY_REG(COMP->COMPHCTL, COMPHCTL_POL4PWM_Msk, (eLevel << COMPHCTL_POL4PWM_Pos));
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set comparator output active polarity for GPIO
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  eLevel: Force polarity defined by LEVEL
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetOutputPolarityForGPIO(COMP_ComparatorSelEnum eCOMP, LEVEL eLevel)
{
    switch (eCOMP)
    {
        case COMP_L:
            MODIFY_REG(COMP->COMPLCTL, COMPLCTL_POL4GPIO_Msk, (eLevel << COMPLCTL_POL4GPIO_Pos));
            break;

        case COMP_H:
            MODIFY_REG(COMP->COMPHCTL, COMPHCTL_POL4GPIO_Msk, (eLevel << COMPHCTL_POL4GPIO_Pos));
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Enable filter output flag cleared by PWMSYNC
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_EnablePWMSyncClearFilterOutputFlag(COMP_ComparatorSelEnum eCOMP)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL |= COMPLCTL_SYNCCLREN_ENABLE;
            break;

        case COMP_H:
            COMP->COMPHCTL |= COMPHCTL_SYNCCLREN_ENABLE;
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Disable filter output flag cleared by PWMSYNC
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_DisablePWMSyncClearFilterOutputFlag(COMP_ComparatorSelEnum eCOMP)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL &= ~COMPLCTL_SYNCCLREN_ENABLE;
            break;

        case COMP_H:
            COMP->COMPHCTL &= ~COMPHCTL_SYNCCLREN_ENABLE;
            break;

        default:
            break;
    }
}



/******************************************************************************
 * @brief      Set Filter Window Size and Threshold
 *
 * @param[in]  eCOMP      : Select the comparator
 * @param[in]  u8Size     : Filter window size (1 ~ 32)
 * @param[in]  u8Threshold: Filter threshold value (1 ~ 32)
 *
 * @return     None
 *
 * @note       u8Threshold must bigger than u8Size/2
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetFilterWindow(COMP_ComparatorSelEnum eCOMP, uint8_t u8Size, uint8_t u8Threshold)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL = (COMP->COMPLCTL & ~(COMPLCTL_FLTWIN_Msk | COMPLCTL_FLTTH_Msk)) |
                             (((u8Size - 1) << COMPLCTL_FLTWIN_Pos) & COMPLCTL_FLTWIN_Msk) |
                             (((u8Threshold - 1) << COMPLCTL_FLTTH_Pos) & COMPLCTL_FLTTH_Msk);
            break;

        case COMP_H:
            COMP->COMPHCTL = (COMP->COMPHCTL & ~(COMPHCTL_FLTWIN_Msk | COMPHCTL_FLTTH_Msk)) |
                             (((u8Size - 1) << COMPHCTL_FLTWIN_Pos) & COMPHCTL_FLTWIN_Msk) |
                             (((u8Threshold - 1) << COMPHCTL_FLTTH_Pos) & COMPHCTL_FLTTH_Msk);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set filter clock divider
 *
 * @param[in]  eCOMP    : Select the comparator
 *                        Please refer to COMP_ComparatorSelEnum
 * @param[in]  u16ClkDiv: Filter clock divider
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetFilterClockDiv(COMP_ComparatorSelEnum eCOMP, uint16_t u16ClkDiv)
{
    switch (eCOMP)
    {
        case COMP_L:
            COMP->COMPLCTL = (COMP->COMPLCTL & ~COMPLCTL_FLTDIV_Msk) | (((u16ClkDiv - 1) << COMPLCTL_FLTDIV_Pos) & COMPLCTL_FLTDIV_Msk);
            break;

        case COMP_H:
            COMP->COMPHCTL = (COMP->COMPHCTL & ~COMPHCTL_FLTDIV_Msk) | (((u16ClkDiv - 1) << COMPHCTL_FLTDIV_Pos) & COMPHCTL_FLTDIV_Msk);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Select the synchronous output from PWM for DAC code load
 *
 *
 * @param[in]  eCOMP    :  Comparator selection defined by COMP_ComparatorSelEnum
 * @param[in]  ePWMIndex:  PWM module index
 *                         Please refer to PWM_SelEnum
 *
 * @return     None
 *
 * @example    COMP_SetSyncEvent(COMP_L, SEL_PWM0);
 *
 ******************************************************************************/
#define COMP_SetSyncEvent(eCOMP, ePWMIndex)                                     \
    (COMP->COMPCTL = (COMP->COMPCTL & ~COMPCTL_SYNCSEL_Msk) | ((ePWMIndex) << COMPCTL_SYNCSEL_Pos))




/******************************************************************************
 * @brief      Clear the filtered COMP output flag
 *
 * @param[in]  eCOMP: Comparator selection defined by COMP_ComparatorSelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_ClearFilterOutputFlag(eCOMP)   (COMP->COMPFLGCLR = (eCOMP))




/******************************************************************************
 * @brief      Get the filtered output flag
 *
 * @param[in]  eCOMP:  Select the comparator from COMP_ComparatorSelEnum
 *                     Multiple comparators can be ORed simultaneously
 *
 * @return     0     - None of the queried comparators filtered output is high
 *             not 0 - Corresponding comparators filtered output for non-zero bit is high
 *
 * @example    COMP_GetFilterOutputFlag(COMP_L)
 *             COMP_GetFilterOutputFlag(COMP_L | COMP_H)
 *
 ******************************************************************************/
#define COMP_GetFilterOutputFlag(eCOMP)     (COMP->COMPFLG & (eCOMP))




/******************************************************************************
 * @brief      Get the raw filter output
 *
 * @param[in]  eCOMP:  Select the comparator from COMP_ComparatorSelEnum
 *                     Multiple comparators can be ORed simultaneously
 *
 * @return     0     - None of the queried comparators raw filtered output is high
 *             not 0 - Corresponding comparators raw filtered output for non-zero bit is high
 *
 * @example    COMP_GetRawFilterOutput(COMP_L)
 *             COMP_GetRawFilterOutput(COMP_L | COMP_H)
 *
 ******************************************************************************/
#define COMP_GetRawFilterOutput(eCOMP)      (COMP->COMPFLTOUT & (eCOMP))




/******************************************************************************
 * @brief      Enable DAC
 *
 * @param[in]  eDACSel:  Select the DAC
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_EnableDAC(COMP_DACSelEnum eDACSel)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL |= DAC0CTL_EN_ENABLE;
            break;

        case DAC1:
            COMP->DAC1CTL |= DAC1CTL_EN_ENABLE;
            break;

        case DAC2:
            COMP->DAC2CTL |= DAC2CTL_EN_ENABLE;
            break;
    }
}




/******************************************************************************
 * @brief      Disable DAC
 *
 * @param[in]  eDACSel:  Select the DAC
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_DisableDAC(COMP_DACSelEnum eDACSel)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL &= ~DAC0CTL_EN_ENABLE;
            break;

        case DAC1:
            COMP->DAC1CTL &= ~DAC1CTL_EN_ENABLE;
            break;

        case DAC2:
            COMP->DAC2CTL &= ~DAC2CTL_EN_ENABLE;
            break;
    }
}




/******************************************************************************
 * @brief      Set DAC value
 *
 * @param[in]  eDACSel:  Select the DAC
 * @param[in]  u32Code:  Range from 0 (0V) ~ 1023 (3.3V)
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACValue10Bit(COMP_DACSelEnum eDACSel, uint32_t u32Code)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CODE = u32Code;
            break;

        case DAC1:
            COMP->DAC1CODE = u32Code;
            break;

        case DAC2:
            COMP->DAC2CODE = u32Code;
            break;
    }
}

__STATIC_INLINE uint32_t COMP_GetDACValue10Bit(COMP_DACSelEnum eDACSel)
{
    switch (eDACSel)
    {
        case DAC0:
            return COMP->DAC0CODE;

        case DAC1:
            return COMP->DAC1CODE;

        case DAC2:
            return COMP->DAC2CODE;

        default:
            return 0;
    }
}




/******************************************************************************
 * @brief      Set DAC value in milli voltage
 *
 * @param[in]  eDACSel   :  Select the DAC
 * @param[in]  i32ValueMV:  Range from 0(0 voltage) ~ 3300 (3300 mV = 3.3 V)
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACVoltage(COMP_DACSelEnum eDACSel, int32_t i32ValueMV)
{
    int32_t i32Val;
    i32Val = (i32ValueMV * 1024) / 3300;

    if (i32Val > 1023)
    {
        i32Val = 1023;
    }
    if (i32Val < 0)
    {
        i32Val = 0;
    }

    COMP_SetDACValue10Bit(eDACSel, i32Val);
}




/******************************************************************************
 * @brief      Select the PWM synchronous output signal for DAC
 *
 * @param[in]  eDACSel  :  Select the DAC
 *                         Please refer to COMP_DACSelEnum
 * @param[in]  ePWMIndex:  PWM module index
 *                         Please refer to PWM_SelEnum
 *
 * @return     None
 *
 * @example    COMP_SetDACSyncEvent(DAC0, SEL_PWM0);
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACSyncEvent(COMP_DACSelEnum eDACSel, uint8_t ePWMIndex)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL = (COMP->DAC0CTL & ~DAC0CTL_SYNCSEL_Msk) | ((ePWMIndex) << DAC0CTL_SYNCSEL_Pos);
            break;

        case DAC1:
            COMP->DAC1CTL = (COMP->DAC1CTL & ~DAC1CTL_SYNCSEL_Msk) | ((ePWMIndex) << DAC1CTL_SYNCSEL_Pos);
            break;

        case DAC2:
            COMP->DAC2CTL = (COMP->DAC2CTL & ~DAC2CTL_SYNCSEL_Msk) | ((ePWMIndex) << DAC2CTL_SYNCSEL_Pos);
            break;
    }
}




/******************************************************************************
 * @brief      Set DAC Code Load Mode
 *
 * @param[in]  eDACSel  :  Select the DAC
 * @param[in]  eLoadMode:  DAC code load mode defined by COMP_DACLoadTimingEnum
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACCodeLoadTiming(COMP_DACSelEnum eDACSel, uint8_t eLoadMode)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL = (COMP->DAC0CTL & ~DAC0CTL_CODELOAD_Msk) | (eLoadMode << DAC0CTL_CODELOAD_Pos);
            break;

        case DAC1:
            COMP->DAC1CTL = (COMP->DAC1CTL & ~DAC1CTL_CODELOAD_Msk) | (eLoadMode << DAC1CTL_CODELOAD_Pos);
            break;

        case DAC2:
            COMP->DAC2CTL = (COMP->DAC2CTL & ~DAC2CTL_CODELOAD_Msk) | (eLoadMode << DAC2CTL_CODELOAD_Pos);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Enable DAC Ramp
 *
 * @param[in]  eDACSel  :  Select the DAC
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_EnableDACRamp(COMP_DACSelEnum eDACSel)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL |= DAC0CTL_RAMPEN_ENABLE;
            break;

        case DAC1:
            COMP->DAC1CTL |= DAC1CTL_RAMPEN_ENABLE;
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Disable DAC Ramp
 *
 * @param[in]  eDACSel  :  Select the DAC
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_DisableDACRamp(COMP_DACSelEnum eDACSel)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL &= ~DAC0CTL_RAMPEN_ENABLE;
            break;

        case DAC1:
            COMP->DAC1CTL &= ~DAC1CTL_RAMPEN_ENABLE;
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set DAC Ramp Load Mode
 *
 * @param[in]  eDACSel  :  Select the DAC
 * @param[in]  eLoadMode:  DAC ramp load mode defined by COMP_DACLoadTimingEnum
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACRampLoadTiming(COMP_DACSelEnum eDACSel, uint8_t eLoadMode)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->DAC0CTL = (COMP->DAC0CTL & ~DAC0CTL_RAMPLOAD_Msk) | (eLoadMode << DAC0CTL_RAMPLOAD_Pos);
            break;

        case DAC1:
            COMP->DAC1CTL = (COMP->DAC1CTL & ~DAC1CTL_RAMPLOAD_Msk) | (eLoadMode << DAC1CTL_RAMPLOAD_Pos);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Set DAC Ramp Reload Value
 *
 * @param[in]  eDACSel:  Select the DAC
 * @param[in]  u16Load:  DAC ramp reload value
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACRampReloadValue(COMP_DACSelEnum eDACSel, uint16_t u16Load)
{
    switch (eDACSel)
    {
        case DAC0:
            (COMP->RAMP0MAX = (u16Load));
            break;

        case DAC1:
            (COMP->RAMP1MAX = (u16Load));
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Get DAC Ramp Reload Value
 *
 * @param[in]  eDACSel:  Select the DAC
 *
 * @return     16-bit ramp reload value
 *
 ******************************************************************************/
__STATIC_INLINE uint16_t COMP_GetDACRampReloadValue(COMP_DACSelEnum eDACSel)
{
    uint16_t u16Load;

    switch (eDACSel)
    {
        case DAC0:
            u16Load = (COMP->RAMP0MAXA);
            break;

        case DAC1:
            u16Load = (COMP->RAMP1MAXA);
            break;

        default:
            break;
    }
    return u16Load;
}




/******************************************************************************
 * @brief      Set DAC Ramp Delay
 *
 * @param[in]  eDACSel  :  Select the DAC
 * @param[in]  u16Delay :  DAC ramp delay
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACRampDelay(COMP_DACSelEnum eDACSel, uint16_t u16Delay)
{
    switch (eDACSel)
    {
        case DAC0:
            (COMP->RAMP0DLY = (u16Delay));
            break;

        case DAC1:
            (COMP->RAMP1DLY = (u16Delay));
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Get DAC Ramp Delay
 *
 * @param[in]  eDACSel:  Select the DAC
 *
 * @return     16-bit ramp delay
 *
 ******************************************************************************/
__STATIC_INLINE uint16_t COMP_GetDACRampDelay(COMP_DACSelEnum eDACSel)
{
    uint16_t u16Delay;

    switch (eDACSel)
    {
        case DAC0:
            u16Delay = (COMP->RAMP0DLYA);
            break;

        case DAC1:
            u16Delay = (COMP->RAMP1DLYA);
            break;

        default:
            break;
    }
    return u16Delay;
}




/******************************************************************************
 * @brief      Set DAC Ramp Decrement
 *
 * @param[in]  eDACSel:  Select the DAC
 * @param[in]  u16Dec :  DAC ramp decrement
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACRampDecrement(COMP_DACSelEnum eDACSel, uint16_t u16Dec)
{
    switch (eDACSel)
    {
        case DAC0:
            COMP->RAMP0DEC = u16Dec;
            break;

        case DAC1:
            COMP->RAMP1DEC = u16Dec;
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief      Get DAC Ramp Decrement
 *
 * @param[in]  eDACSel:  Select the DAC
 *
 * @return     16-bit ramp decrement
 *
 ******************************************************************************/
__STATIC_INLINE uint16_t COMP_GetDACRampDecrement(COMP_DACSelEnum eDACSel)
{
    uint16_t u16Decrement;

    switch (eDACSel)
    {
        case DAC0:
            u16Decrement = (COMP->RAMP0DECA);
            break;

        case DAC1:
            u16Decrement = (COMP->RAMP1DECA);
            break;

        default:
            break;
    }
    return u16Decrement;
}




/******************************************************************************
 * @brief      Get DAC Ramp Counter Value
 *
 * @param[in]  eDACSel:  Select the DAC
 *
 * @return     16-bit ramp counter value
 *
 ******************************************************************************/
__STATIC_INLINE uint16_t COMP_GetDACRampCounterValue(COMP_DACSelEnum eDACSel)
{
    uint16_t u16Cnt;

    switch (eDACSel)
    {
        case DAC0:
            u16Cnt = (COMP->RAMP0CNT);
            break;

        case DAC1:
            u16Cnt = (COMP->RAMP1CNT);
            break;

        default:
            break;
    }
    return u16Cnt;
}
#define COMP_GetDAC0RampCounterValue()      (COMP->RAMP0CNT)
#define COMP_GetDAC1RampCounterValue()      (COMP->RAMP1CNT)




/******************************************************************************
 * @brief      Set DAC Buffer input
 *
 * @param[in]  eDACSel:  Select the DAC module
 *                       Please refer to COMP_DACSelEnum,
 *                       only DAC0 and DAC1 is legal.
 *                       - \ref DAC0
 *                       - \ref DAC1
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void COMP_SetDACBufferInput(COMP_DACSelEnum eDACSel)
{
switch (eDACSel)
    {
        case DAC0:
            
        case DAC1:
            WRITE_FIELD(COMP->DACBUFCTL, DACBUFCTL_INSEL_Msk, DACBUFCTL_INSEL_Pos, (eDACSel));
            break;

        default:
            break;
    }
}



/******************************************************************************
 * @brief      Get DAC Buffer input
 *
 * @param[in]  None
 *
 * @return     DAC0 or DAC1
 *
 ******************************************************************************/
#define COMP_GetDACBufferInput()            READ_FIELD(COMP->DACBUFCTL, DACBUFCTL_INSEL_Msk, DACBUFCTL_INSEL_Pos)




/******************************************************************************
 * @brief      Enable DAC Buffer output to GPIO
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_EnableDACBufferOutputToGPIO()    SET_BITS(COMP->DACBUFCTL, DACBUFCTL_OE_Msk)




/******************************************************************************
 * @brief      Disable DAC Buffer output to GPIO
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_DisableDACBufferOutputToGPIO()   CLEAR_BITS(COMP->DACBUFCTL, DACBUFCTL_OE_Msk)




/******************************************************************************
 * @brief      Enable DAC Buffer
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_EnableDACBuffer()              (COMP->DACBUFCTL |= DACBUFCTL_EN_ENABLE)




/******************************************************************************
 * @brief      Disable DAC Buffer
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_DisableDACBuffer()             (COMP->DACBUFCTL &= ~DACBUFCTL_EN_ENABLE)




/******************************************************************************
 * @brief      Enable write access to the protected COMP registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_WALLOW()                       (COMP->COMPREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected COMP registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define COMP_WDIS()                         (COMP->COMPREGKEY = 0x0)




/**
 *  @brief  Comparator Public Function Declaration
 */
void COMP_Init(COMP_ComparatorSelEnum eCOMP, COMP_InputChannelEnum eCH, int32_t i32DACVoltageMV, uint32_t u32DeglicthTimeNs);

void COMP_SetFilterWindowTimeNs(COMP_ComparatorSelEnum eCOMP, uint32_t u32SizeTimeNS, uint32_t u32ThresholdTimeNS);

void COMP_DACBufferInit(COMP_DACSelEnum eDACSel);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* __COMP_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
