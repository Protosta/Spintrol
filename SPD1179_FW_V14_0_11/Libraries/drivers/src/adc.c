/******************************************************************************
 * @file     adc.c
 * @brief    ADC firmware functions.
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

#include "adc.h"


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/****************************************************************************//**
 * @brief      Configure the sample & conversion window size (ns) for SOC
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0
 *                               ...
 *                        - \ref ADC_CH15
 *             u32SampleTimeNs:  Sample window time, no less than 125 ns
 *             u32ConvTimeNs  :  Convert window time
 *
 * @return     none
 *
 *******************************************************************************/
void ADC_SetSampleAndConvertTime(ADC_REGS       *ADCx,
                                 ADC_ChannelEnum eCHx,
                                 uint32_t        u32SampleTimeNs,
                                 uint32_t        u32ConvTimeNs
                                )
{
    uint32_t u32ADCModuleClk, u32SampleTimeCnt, u32ConvTimeCnt, u32Temp;

    /* Get ADC Clock Frequency */
    u32ADCModuleClk = CLOCK_GetModuleClock(ADC_MODULE);

    /* Calculate Sample window size - u32ADCModuleClk * u32SampleTimeNs / 10^9 */
    u32Temp = (u32ADCModuleClk / 100000U) * u32SampleTimeNs;
    u32SampleTimeCnt = u32Temp / 10000U;
    if ((u32Temp % 10000U) != 0U)
    {
        u32SampleTimeCnt++;
    }
    
    if (u32SampleTimeCnt == 0U)
    {
        u32SampleTimeCnt = 1U;
    }
    
    /* Calculate Convert window size - u32ADCModuleClk * u32ConvTimeNs / 10^9 */
    u32Temp = (u32ADCModuleClk / 100000U) * u32ConvTimeNs;
    u32ConvTimeCnt = u32Temp / 10000U;
    if ((u32Temp % 10000U) != 0U)
    {
        u32ConvTimeCnt++;
    }
    
    if (u32ConvTimeCnt == 0U)
    {
        u32ConvTimeCnt = 1U;
    }
    
    /* Saturation handling */
    if (u32SampleTimeCnt > 256U)
    {
        u32SampleTimeCnt = 256U;
    }
    if (u32ConvTimeCnt > 32U)
    {
        u32ConvTimeCnt   = 32U;
    }

    ADC_SetChannelSampleTimeCount(ADCx, eCHx, (u32SampleTimeCnt - 1U));
    ADC_SetChannelConvertTimeCount(ADCx, eCHx, (u32ConvTimeCnt - 1U));
}




/******************************************************************************
 * @brief      Configure ADC channel for differential mode
 *
 * @param[in]  eCHx    :  Channel x defined by ADC_ChannelEnum
 *                        Following values are valid:
 *                        - \ref ADC_CH0
 *                               ...
 *                        - \ref ADC_CH15
 * @param[in]  ePosIn  :  Select the ADC positive input
 *                          ADC_SH_PositiveInputEnum
 * @param[in]  eNegIn  :  Select the ADC negative input
 *                          ADC_SH_NegativeInputEnum
 * @param[in]  eTrigSrc:  Select the trigger source
 *                          Please refer to ADC_Channel_SOCTriggerSourceEnum
 *
 * @return     none
 *
 ******************************************************************************/
void ADC_Init(ADC_REGS                    *ADCx,
              ADC_ChannelEnum             eCHx,
              ADC_SH_PositiveInputEnum    ePosIn,
              ADC_SH_NegativeInputEnum    eNegIn,
              ADC_Channel_SOCTriggerSourceEnum   eTrigSrc
             )
{
    /* Enable ADC Module Clock */
    CLOCK_EnableModule(ADC_MODULE);
    
    /* Disable ADC and interrupt */
    ADC_Disable(ADCx) ;
    ADC_DisableChannelInt(ADCx, eCHx);

    /* Set input channel */
    ADC_SetChannelSHPositiveInput(ADCx, eCHx, ePosIn);
    ADC_SetChannelSHNegativeInput(ADCx, eCHx, eNegIn);

    /* Select trigger source */
    ADC_SetChannelSOCTriggerSource(ADCx, eCHx, eTrigSrc);

    /* Set sample and convert time */
    ADC_SetSampleAndConvertTime(
        ADCx,
        eCHx,
        ADC_DEFAULT_SAMPLE_TIME_NS,
        ADC_DEFAULT_CONVERSION_TIME_NS
    );

    /* Set channel gain and offset */
    ADC_SetChannelGain(ADCx, eCHx, ADCx->SHGAIN[0]);
    ADC_SetChannelOffset(ADCx, eCHx, ADCx->SHOFFSET[0]);
    
    /* Set CH[x] Sampling Holder mode */
    ADC_SetChannelSH(ADCx, eCHx, ADC_SH_SEL_0);
    
    /* Clear SOC interrupt */
    ADC_ClearChannelInt(ADCx, eCHx);


    /* Configure I/O Pin */
    switch (ePosIn)
    {
        case ADC_SH0_P_ANA_IN0:
            PIN_SetPinAsAnalog(PIN_GPIO0);
            break;
        case ADC_SH0_P_ANA_IN2:
            PIN_SetPinAsAnalog(PIN_GPIO2);
            break;
        case ADC_SH0_P_ANA_IN4:
            PIN_SetPinAsAnalog(PIN_GPIO4);
            break;
        case ADC_SH0_P_ANA_IN9_PHU:
            PIN_SetPinAsAnalog(PIN_GPIO36);
            break;
        case ADC_SH0_P_ANA_IN10_PHV:
            PIN_SetPinAsAnalog(PIN_GPIO37);
            break;
        case ADC_SH0_P_ANA_IN11_PHW:
            PIN_SetPinAsAnalog(PIN_GPIO38);
            break;
        case ADC_SH0_P_ANA_IN13_VBATM_DIV:
            PIN_SetPinAsAnalog(PIN_GPIO40);
            break;
        default:
            break;
    }

    switch (eNegIn)
    {
        case ADC_SH0_N_ANA_IN1:
            PIN_SetPinAsAnalog(PIN_GPIO1);
            break;
        case ADC_SH0_N_ANA_IN3:
            PIN_SetPinAsAnalog(PIN_GPIO3);
            break;
        case ADC_SH0_N_ANA_IN5:
            PIN_SetPinAsAnalog(PIN_GPIO28);
            break;
        case ADC_SH0_N_ANA_IN6:
            PIN_SetPinAsAnalog(PIN_GPIO29);
            break;
        case ADC_SH0_N_ANA_IN7:
            PIN_SetPinAsAnalog(PIN_GPIO30);
            break;
        case ADC_SH0_N_ANA_IN8:
            PIN_SetPinAsAnalog(PIN_GPIO31);
            break;
        case ADC_SH0_N_ANA_IN12_PHC:
            PIN_SetPinAsAnalog(PIN_GPIO39);
            break;
        default:
            break;
    }
}




/******************************************************************************
 * @brief      This function is only for single-ended use, that is
 *              - The signal ternimal selected by u8PinSel
 *              - The other terminal is internal GND
 *              - Default sampling time is ADC_DEFAULT_SAMPLE_TIME_NS(default 400ns)
 *                 and conversion time is ADC_DEFAULT_CONVERSION_TIME_NS(default 150ns)
 *              - This function will auto-set selected pin as analog pin
 *                 If user select pin outside the range of ADC pin, it will not effect.
 *
 * @param[in]  eCHx    :  Channel x defined by ADC_ChannelEnum
 *                        Following values are valid:
 *                        - \ref ADC_CH0
 *                               ...
 *                        - \ref ADC_CH15
 * @param[in]  u8PinSel:  Select the ADC input pin
 *                        It can be GPIO pin number or Pin defined in adc.h
 *
 *                        PIN_NameEnum  (Only support ADC pin GPIO0~GPIO4, GPIO28~GPIO31, GPIO36~GPIO40)
 *
 *                        If user want to use internal signal like VDD12,
 *                        please use this type ADC_InputSelectEnum

 * @param[in]  eTrigSrc:  Select the trigger source
 *                        Please refer to ADC_Channel_SOCTriggerSourceEnum

 * @return     none
 *
 * @example    - Initial CH1 to get ADC2(GPIO2) signal with software trigger
 *                 ADC_EasyInit1(ADC, ADC_CH1, PIN_GPIO2, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                 or
 *                 ADC_EasyInit1(ADC, ADC_CH1, ADC_IN_GPIO2, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *
 *             - Initial CH2 to get internal VDD12 signal with PWM trigger
 *                 ADC_EasyInit1(ADC, ADC_CH2, ADC_IN_VDD12, ADC_SOC_TRIGGER_FROM_PWM0SOCA);
 *
 *             - Initial CH3 to get GPIO4(ANA_IN4) signal with software trigger
 *                 <1> ADC_EasyInit1(ADC, ADC_CH3, PIN_GPIO4, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                 <2> Software trigger
 *                     ADC_SetChannelSOCTriggerSource(ADC, ADC_CH3, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                 <3> Get value when data ready
 *                     ADC_GetChannelResult(ADC, ADC_CH3); --> Take longer cpu cycle but accuracy (Recommend)
 *
 *                     ADC_GetChannelRawResult(ADC, ADC_CH3);   --> Raw data, user should determine polarity.
 *
 ******************************************************************************/
ErrorStatus ADC_EasyInit1(ADC_REGS                    *ADCx,
                          ADC_ChannelEnum             eCHx,
                          uint8_t                     u8PinSel,
                          ADC_Channel_SOCTriggerSourceEnum   eTrigSrc
                         )
{
    ErrorStatus Status;

    /* Enable ADC Module Clock */
    CLOCK_EnableModule(ADC_MODULE);
    
    /* Disable ADC and interrupt */
    ADC_Disable(ADCx) ;
    ADC_DisableChannelInt(ADCx, eCHx);

    /* Select input pin and configure SOC */
    Status = ADC_SelectPinSingleEnd(ADCx, eCHx, u8PinSel, eTrigSrc);

    /* Set sample and convert time */
    ADC_SetSampleAndConvertTime(
        ADCx,
        eCHx,
        ADC_DEFAULT_SAMPLE_TIME_NS,
        ADC_DEFAULT_CONVERSION_TIME_NS
    );

    /* Set channel gain and offset */
    ADC_SetChannelGain(ADCx, eCHx, ADCx->SHGAIN[0]);
    ADC_SetChannelOffset(ADCx, eCHx, ADCx->SHOFFSET[0]);
    
    /* Clear interrupt */
    ADC_ClearChannelInt(ADCx, eCHx);

    /* Only GPIO0~GPIO4, GPIO28~GPIO31, GPIO36~GPIO40 can be configured as Analog Pin */
    PIN_SetPinAsAnalog((PIN_NameEnum)u8PinSel);

    return Status;
}




/******************************************************************************
 * @brief      This function is for differential mode, that is
 *             - Default sampling time is ADC_DEFAULT_SAMPLE_TIME_NS(default 400ns)
 *                 and conversion time is ADC_DEFAULT_CONVERSION_TIME_NS(default 150ns)
 *             - This function will auto-set selected pin as analog pin
 *                 If user select pin outside the range of ADC pin, it will not effect.
 *
 * @param[in]  eCHx    :  Channel x defined by ADC_ChannelEnum
 *                        Following values are valid:
 *                        - \ref ADC_CH0
 *                               ...
 *                        - \ref ADC_CH15
 * @param[in]  u8PinSel_1:  Select the first terminal ADC pin
 *                          It can be GPIO pin or Pin defined in adc.h
 *
 *                          PIN_NameEnum  (Only support ADC pin GPIO0~GPIO4, GPIO28~GPIO31, GPIO36~GPIO40)
 *
 *                          If user want to use internal signal like VDD12,
 *                          please use this type ADC_InputSelectEnum
 *
 * @param[in]  u8PinSel_2:  Select the second terminal ADC pin
 * @param[in]  eTrigSrc  :  Select the trigger source
 *                          Please refer to ADC_Channel_SOCTriggerSourceEnum
 *
 * @return     none
 *
 * @details    Be sure to select pin as described as figure in technical reference manual
 *             SPC1169 do not support dedicated pins to differential mode
 *             Example :
 *                Wrong  --> ADC_EasyInit2(ADC, ADC_CH5, ADC_IN_GPIO2, ADC_IN_GPIO4, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                Correct -> ADC_EasyInit2(ADC, ADC_CH5, ADC_IN_GPIO2, ADC_IN_GPIO3, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *
 * @example    Initial CH3 to get differential signal between GPIO2(ADC2) and GPIO3(ADC3) signal
 *             with software trigger
 *                 <1> ADC_EasyInit2(ADC, ADC_CH3, PIN_GPIO2, PIN_GPIO3, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                 <2> Software trigger
 *                     ADC_SetChannelSOCTriggerSource(ADC, ADC_CH3, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                 <3> Get value when data ready
 *                     ADC_GetChannelResult(ADC, ADC_CH3); --> Take longer cpu cycle but accuracy (Recommend)
 *
 * @note       ADC_EasyInit2(ADC, ADC_CH3, PIN_GPIO2, PIN_GPIO3, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *             and
 *             ADC_EasyInit2(ADC, ADC_CH3, PIN_GPIO3, PIN_GPIO2, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *             are the same, the polarity of GPIO2(ANA_IN2) and GPIO3(ANA_IN3) is determined in
 *             ADC hardware channel structure, please read the TRM for details.
 *
 ******************************************************************************/
ErrorStatus ADC_EasyInit2(ADC_REGS                    *ADCx,
                          ADC_ChannelEnum             eCHx,
                          uint8_t                     u8PinSel_1,
                          uint8_t                     u8PinSel_2,
                          ADC_Channel_SOCTriggerSourceEnum   eTrigSrc
                         )
{
    ErrorStatus Status;

    /* Enable ADC Module Clock */
    CLOCK_EnableModule(ADC_MODULE);
    
    /* Disable ADC and interrupt */
    ADC_Disable(ADCx) ;
    ADC_DisableChannelInt(ADCx, eCHx);

    /* Select input pin and configure SOC */
    Status = ADC_SelectPinDifferetial(
                 ADCx,
                 eCHx,
                 (ADC_InputSelectEnum)u8PinSel_1,
                 (ADC_InputSelectEnum)u8PinSel_2, eTrigSrc
             );

    /* Set sample and convert time */
    ADC_SetSampleAndConvertTime(
        ADCx,
        eCHx,
        ADC_DEFAULT_SAMPLE_TIME_NS,
        ADC_DEFAULT_CONVERSION_TIME_NS
    );

    /* Set channel gain and offset */
    ADC_SetChannelGain(ADCx, eCHx, ADCx->SHGAIN[0]);
    ADC_SetChannelOffset(ADCx, eCHx, ADCx->SHOFFSET[0]);
    
    /* Clear interrupt */
    ADC_ClearChannelInt(ADCx, eCHx);

    /* Only GPIO0~GPIO4, GPIO28~GPIO31, GPIO36~GPIO40 can be configured as Analog Pin */
    PIN_SetPinAsAnalog((PIN_NameEnum)u8PinSel_1);
    PIN_SetPinAsAnalog((PIN_NameEnum)u8PinSel_2);
    return Status;
}




/******************************************************************************
 * @brief      Get ADC Input Pin Code
 *             Encode logic for ADC Input pin: Sampler(4-bit) + Channel (4-bit)
 *             Sampler - \ref 8  SH Positive    - \ref 9  SH Negative
 *
 * @param[in]  u8PinSel :  Select the ADC input pin
 *                         It can be GPIO pin or Pin defined in adc.h
 *                         PIN_NameEnum (Only support ADC pin GPIO0~GPIO4, GPIO28~GPIO31, GPIO36~GPIO40)
 *
 *                         If user want to use internal signal like VDD12,
 *                         please use this type ADC_InputSelectEnum
 *
 * @return     ADC Input Pin Code
 *
 ******************************************************************************/
static uint8_t ADC_GetInputPinCode(uint8_t u8PinSel)
{
    uint8_t u8PinCode = 0U;

    /* Set Pin code */
    switch (u8PinSel)
    {
        case PIN_GPIO0:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN0);
            break;

        case PIN_GPIO1:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN1);
            break;

        case PIN_GPIO2:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN2);
            break;

        case PIN_GPIO3:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN3);
            break;

        case PIN_GPIO4:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN4);
            break;
        
        case PIN_GPIO28:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN5);
            break;
        
        case PIN_GPIO29:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN6);
            break;
        
        case PIN_GPIO30:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN7);
            break;
        
        case PIN_GPIO31:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN8);
            break;

        case PIN_GPIO36:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN9_PHU);
            break;
        
        case PIN_GPIO37:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN10_PHV);
            break;
        
        case PIN_GPIO38:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN11_PHW);
            break;
        
        case PIN_GPIO39:
            u8PinCode = (0x90U | ADC_SH0_N_ANA_IN12_PHC);
            break;
        
        case PIN_GPIO40:
            u8PinCode = (0x80U | ADC_SH0_P_ANA_IN13_VBATM_DIV);
            break;
        
        default:    /* Other ADC Input Pin */
            u8PinCode = u8PinSel;
            break;
    }

    return u8PinCode;
}




/******************************************************************************
 * @brief      Configure ADC channel for single-ended
 *             The other terminal is default as internal GND
 *
 * @param[in]  eCHx    :  Select the channel to be used
 * @param[in]  u8PinSel:  Select the ADC input pin
 *                        It can be GPIO pin or Pin defined in adc.h
 *                        PIN_NameEnum  (Only support ADC pin GPIO0~GPIO4, GPIO28~GPIO31, GPIO36~GPIO40)
 *
 *                        If user want to use internal signal like VDD12,
 *                        please use this type ADC_InputSelectEnum

 * @param[in]  eTrigSrc:  Select the trigger source
 *                        Please refer to ADC_Channel_SOCTriggerSourceEnum
 *
 * @return     none
 *
 ******************************************************************************/
ErrorStatus ADC_SelectPinSingleEnd(ADC_REGS                    *ADCx,
                                   ADC_ChannelEnum             eCHx,
                                   uint8_t                     u8PinSel,
                                   ADC_Channel_SOCTriggerSourceEnum   eTrigSrc
                                  )
{
    ErrorStatus Status = SUCCESS;

    /* Pin code */
    uint8_t  u8PinCode = 0U;

    /* Positive channel selection */
    uint32_t u32CHPSel = 0U;

    /* Negative channel selection */
    uint32_t u32CHNSel = 0U;


    /* Get ADC Input Pin code */
    u8PinCode = ADC_GetInputPinCode(u8PinSel);

    /* Configure S/H and Channel Selection */
    switch ((u8PinCode & 0xF0U) >> 4)
    {
        case 8:   /* SH Positive */
            u32CHPSel = u8PinCode & 0x0FU;
            u32CHNSel = 0;  /* GND */
            break;

        case 9:   /* SH Negative */
            u32CHPSel = 0;  /* GND */
            u32CHNSel = u8PinCode & 0x0FU;
            break;

        default:
            Status = ERROR;
            break;
    }

    /* Configure SOC */
    if (Status == SUCCESS)
    {
        /* Set input channel */
        ADC_SetChannelSHPositiveInput(ADCx, eCHx, u32CHPSel);
        ADC_SetChannelSHNegativeInput(ADCx, eCHx, u32CHNSel);

        /* Select trigger source */
        ADC_SetChannelSOCTriggerSource(ADCx, eCHx, eTrigSrc);

        /* Select S/H */
        ADC_SetChannelSH(ADCx, eCHx, ADC_SH_SEL_0);
    }

    return Status;
}




/******************************************************************************
 * @brief      Configure ADC channel for differential mode
 *
 * @param[in]  eCHx      :  Select the channel to be used
 * @param[in]  u8PinSel_1:  Select the first terminal ADC pin
 *                          It can be ADC_InputSelectEnum or PIN_NameEnum
 * @param[in]  u8PinSel_2:  Select the second terminal ADC pin
 *                          It can be ADC_InputSelectEnum or PIN_NameEnum
 * @param[in]  eTrigSrc  :  Select the trigger source
 *                          Please refer to ADC_Channel_SOCTriggerSourceEnum
 *
 * @return     none
 *
 * @details    Be sure to select pin as described as figure in technical reference manual
 *             SPC1169 do not support dedicated pins to differential mode
 *             Example:
 *                Wrong   --> ADC_SelectPinDifferetial(ADC, ADC_CH5, ADC_IN_GPIO2, ADC_IN_GPIO4, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *                Correct --> ADC_SelectPinDifferetial(ADC, ADC_CH5, ADC_IN_GPIO2, ADC_IN_GPIO3, ADC_SOC_TRIGGER_FROM_SOFTWARE);
 *
 ******************************************************************************/
ErrorStatus ADC_SelectPinDifferetial(ADC_REGS                    *ADCx,
                                     ADC_ChannelEnum             eCHx,
                                     uint8_t                     u8PinSel_1,
                                     uint8_t                     u8PinSel_2,
                                     ADC_Channel_SOCTriggerSourceEnum   eTrigSrc
                                    )
{
    ErrorStatus Status = SUCCESS;

    /* Pin code */
    uint8_t  u8PinCode1 = 0U;
    uint8_t  u8PinCode2 = 0U;

    /* Positive channel selection */
    uint32_t u32CHPSel = 0U;

    /* Negative channel selection */
    uint32_t u32CHNSel = 0U;


    /* Get ADC Input Pin code */
    u8PinCode1 = ADC_GetInputPinCode(u8PinSel_1);
    u8PinCode2 = ADC_GetInputPinCode(u8PinSel_2);

    if ((u8PinCode1 & 0xF0U) ==  (u8PinCode2 & 0xF0U))
    {
        Status = ERROR;
    }
    else
    {
        /* Configure S/H and Channel Selection */
        switch ((u8PinCode1 & 0xF0U) >> 4)
        {
            case 8:   /* SH Positive */
                u32CHPSel = u8PinCode1 & 0x0FU;
                u32CHNSel = u8PinCode2 & 0x0FU;
                break;

            case 9:   /* SH Negative */
                u32CHPSel = u8PinCode2 & 0x0FU;
                u32CHNSel = u8PinCode1 & 0x0FU;
                break;

            default:
                Status = ERROR;
                break;
        }
    }
    
    /* Configure SOC */
    if (Status == SUCCESS)
    {
        /* Set input channel */
        ADC_SetChannelSHPositiveInput(ADCx, eCHx, u32CHPSel);
        ADC_SetChannelSHNegativeInput(ADCx, eCHx, u32CHNSel);

        /* Select trigger source */
        ADC_SetChannelSOCTriggerSource(ADCx, eCHx, eTrigSrc);

        /* Select S/H */
        ADC_SetChannelSH(ADCx, eCHx, ADC_SH_SEL_0);
    }

    return Status;
}




/******************************************************************************
 * @brief      Enable ADCx module
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
void ADC_Enable(ADC_REGS *ADCx)
{
    volatile uint32_t u32Timeout = 0U;

    SET_BITS( (ADCx)->ADCCTL, ADCCTL_REFEN_Msk | ADCCTL_EN_Msk);

    for (u32Timeout = 0U; u32Timeout < 5000U; u32Timeout++)
    { ; }
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
