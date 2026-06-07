/******************************************************************************
 * @file     system.c
 * @brief    SYSTEM firmware functions.
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

#include "system.h"


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
 * @brief      Set system monitor interval
 *
 * @param[in]  u32IntervalUs:  Interval in us
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus SYSTEM_SetMonitorInterval(uint32_t u32IntervalUs)
{
    ErrorStatus status;
    uint32_t    u32Cnt;

    /* Calculate system monitor interval in HCLK cycles */
    u32Cnt = SysInfo.u32SYSCLK / 1000 * u32IntervalUs / 1000;
    if (u32Cnt > 0)
    {
        u32Cnt = (u32Cnt - 1) >> 3;
    }


    if (u32Cnt > 0xFFFF)
    {
        /* Invalid HCLK cycles */
        status = ERROR;
    }
    else
    {
        /* Set system monitor interval */
        SYSTEM->SYSMONCTL = (SYSTEM->SYSMONCTL & ~SYSMONCTL_MONPRD_Msk)
                          | SYSMONCTL_MONPRD_(u32Cnt);

        status = SUCCESS;
    }

    return status;
}




/******************************************************************************
 * @brief      Set system monitor threshold
 *
 * @param[in]  eItem    :  Select the system monitor item
 *                         Please refer to SYSTEM_MonitorItemEnum
 * @param[in]  u32MinVal:  Minimum allowed voltage in mV or temperature in C
 * @param[in]  u32MaxVal:  Maximum allowed voltage in mV or temperature in C
 *
 * @return     SUCCESS or ERROR
 *
 * @note       Error will be detected if the voltage is > u32MaxmV or < u32MinmV
 *
 ******************************************************************************/
ErrorStatus SYSTEM_SetMonitorThreshold(SYSTEM_MonitorItemEnum eItem, uint32_t u32MinVal, uint32_t u32MaxVal)
{
    ErrorStatus status;
    uint32_t    u32MinCode;
    uint32_t    u32MaxCode;

    /* 
     * TPMUOFFSET
     * TPMUGAIN
     * TLINOFFSET
     * TLINGAIN
     * TMCUOFFSET
     * TMCUGAIN   
     */
    int32_t     ai32Temp[6];
    
    /* Read trim data */
    pHWLIB->FLASHC_Read((uint32_t *)ai32Temp, 0x11001168, 6);

    /* Calculate monitor codes according to input values */
    if ((eItem == MONITOR_HV_VBAT) || (eItem == MONITOR_HV_VMON))
    {
        u32MinCode = ((u32MinVal << 12) / 13) / 3657;
        u32MaxCode = ((u32MaxVal << 12) / 13) / 3657;
    }
    else if (eItem == MONITOR_HV_VCP)
    {
        u32MinCode = ((u32MinVal << 12) / 15) / 3657;
        u32MaxCode = ((u32MaxVal << 12) / 15) / 3657;
    }
    else if (eItem == MONITOR_HV_VDD5)
    {
        u32MinCode = ((u32MinVal << 12) / 5) / 3657;
        u32MaxCode = ((u32MaxVal << 12) / 5) / 3657;
    }
    else if (eItem == MONITOR_HV_PMU_TEMPERATURE)
    {
        if (ai32Temp[0] != 0xffffffff)
        {
            u32MinCode = ((int32_t)u32MaxVal * 65536 - ai32Temp[0]) / ai32Temp[1];
            u32MaxCode = ((int32_t)u32MinVal * 65536 - ai32Temp[0]) / ai32Temp[1]; 
        }
        else
        {
            u32MinCode = (13125 - u32MaxVal * 33) >> 4;
            u32MaxCode = (13125 - u32MinVal * 33) >> 4;
        }
    }
    else if (eItem == MONITOR_HV_LIN_TEMPERATURE)
    {
        if (ai32Temp[2] != 0xffffffff)
        {
            u32MinCode = ((int32_t)u32MaxVal * 65536 - ai32Temp[2]) / ai32Temp[3];
            u32MaxCode = ((int32_t)u32MinVal * 65536 - ai32Temp[2]) / ai32Temp[3];
        }
        else
        {
            u32MinCode = (26549 - u32MaxVal * 69) >> 5;
            u32MaxCode = (26549 - u32MinVal * 69) >> 5;
        }
    }
    else if (eItem == MONITOR_MCU_TEMPERATURE)
    {
        if (ai32Temp[4] != 0xffffffff)
        {
            u32MinCode = ((int32_t)u32MinVal * 65536 - ai32Temp[4]) / ai32Temp[5];
            u32MaxCode = ((int32_t)u32MaxVal * 65536 - ai32Temp[4]) / ai32Temp[5];
        }
        else
        {
            u32MinCode = (305657 + u32MinVal * 1081) >> 12;
            u32MaxCode = (305657 + u32MaxVal * 1081) >> 12;
        }
    }
    else
    {
        u32MinCode = (u32MinVal << 12) / 3657;
        u32MaxCode = (u32MaxVal << 12) / 3657;
    }


    if ((u32MinCode > 0xFFF) || (u32MaxCode > 0xFFF))
    {
        /* Invalid monitor code */
        status = ERROR;
    }
    else
    {
        status = SUCCESS;
        switch (eItem)
        {
            case MONITOR_ADCREF:
                SYSTEM->VADCREFTH = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_VDD12:
                SYSTEM->VDD12TH   = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_VDD33:
                SYSTEM->VDD33TH   = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_MCU_TEMPERATURE:
                SYSTEM->TMCUTH    = u32MinCode | (u32MaxCode << 16);
                break;
            
            case MONITOR_HV_LIN_TEMPERATURE:
                SYSTEM->TLINTH    = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_HV_PMU_TEMPERATURE:
                SYSTEM->TPMUTH    = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_HV_VBG:
                SYSTEM->VBGTH     = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_HV_VDD5:
                SYSTEM->VDD5TH    = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_HV_VMON:
                SYSTEM->VMONTH    = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_HV_VCP:
                SYSTEM->VCPTH     = u32MinCode | (u32MaxCode << 16);
                break;

            case MONITOR_HV_VBAT:
                SYSTEM->VBATTH    = u32MinCode | (u32MaxCode << 16);
                break;

            default:
                status = ERROR;
                break;
        }
    }

    return status;
}




/******************************************************************************
 * @brief      Set system monitor sample and convert time
 *
 * @param[in]  u32TimeNs:  Sample/Convert time in ns
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus SYSTEM_SetMonitorSampleAndConvertTime(uint32_t u32TimeNs)
{
    ErrorStatus status;
    uint32_t    u32Cnt;

    /* Calculate system monitor interval in HCLK cycles */
    u32Cnt = (SysInfo.u32SYSCLK / 100U) * u32TimeNs / 40000000U;

    if (u32Cnt > 31U)
    {
        /* Invalid HCLK cycles */
        status = ERROR;
    }
    else
    {
        /* Set system monitor interval */
        SYSTEM->SYSMONCTL = (SYSTEM->SYSMONCTL & ~SYSMONCTL_SCWIN_Msk)
                          | SYSMONCTL_SCWIN_(u32Cnt);
        status = SUCCESS;
    }

    return status;
}




#if (defined(SPC1169))
/******************************************************************************
 * @brief      Set GPIO to wake up from stop state
 *
 * @param[in]  ePinName :  Pin to be sensed for wakeup as defined by PIN_NameEnum
 *             ePinLevel:  Pin level to trigger wake up as defined by LEVEL
 *
 * @return     Success or ERROR
 *
 ******************************************************************************/
ErrorStatus SYSTEM_SetStopWakeUpByGPIO(PIN_NameEnum ePinName, LEVEL ePinLevel)
{
    ErrorStatus status;

    if ((ePinName > PIN_GPIO_LAST) || (ePinLevel > HIGH))
    {
        /* Invalid GPIO number or GPIO pin level */
        status = ERROR;
    }
    else
    {
        /* Config pin as GPIO input */
        PIN_SetPinAsGPIO((PIN_NameEnum)ePinName);
        GPIO_SetPinDir((PIN_NameEnum)ePinName, GPIO_INPUT);

        /* Set GPIO number and active level */
        SYSTEM->GPIOWKUPCTL = (ePinLevel << GPIOWKUPCTL_STOPWKUPPOL_Pos) |
                              (ePinName  << GPIOWKUPCTL_STOPWKUPIO_Pos) |
                              GPIOWKUPCTL_STOPWKUPWE_ENABLE;

        status = SUCCESS;
    }

    return status;
}




/******************************************************************************
 * @brief      Set GPIO to wake up from sleep state
 *
 * @param[in]  ePinName :  Pin to be sensed for wake up as define by PIN_NameEnum
 *                         Valid options can only be either PIN_GPIO4 or PIN_GPIO28
 *             ePinLevel:  Pin level to trigger wake up as defined by LEVEL
 *
 * @return     Success or ERROR
 *
 ******************************************************************************/
ErrorStatus SYSTEM_SetSleepWakeUpByGPIO(PIN_NameEnum ePinName, LEVEL ePinLevel)
{
    ErrorStatus status;

    if (((ePinName != PIN_GPIO4) && (ePinName != PIN_GPIO28)) || (ePinLevel > HIGH))
    {
        /* Invalid GPIO number or GPIO pin level */
        status = ERROR;
    }
    else
    {
        /* Config pin as GPIO input */
        PIN_SetPinAsGPIO((PIN_NameEnum)ePinName);
        GPIO_SetPinDir((PIN_NameEnum)ePinName, GPIO_INPUT);

        /* Set GPIO number and active level */
        if (ePinName == PIN_GPIO4)
        {
            SYSTEM->GPIOWKUPCTL = (ePinLevel << GPIOWKUPCTL_SLEEPWKUPPOL_Pos)
                                | (1U << GPIOWKUPCTL_SLEEPWKUPIO_Pos)
                                | GPIOWKUPCTL_SLEEPWKUPWE_ENABLE;
        }
        else
        {
            SYSTEM->GPIOWKUPCTL = (ePinLevel << GPIOWKUPCTL_SLEEPWKUPPOL_Pos)
                                | GPIOWKUPCTL_SLEEPWKUPWE_ENABLE;
        }
        status = SUCCESS;
    }

    return status;
}
#endif


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif

              
/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
