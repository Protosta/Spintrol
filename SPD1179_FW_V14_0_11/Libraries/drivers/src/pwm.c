/******************************************************************************
 * @file     pwm.c
 * @brief    PWM firmware functions.
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

#include "pwm.h"


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
 * @brief      Initializes PWM complementary pair channel/ PWMxA and PWMxB
 *
 * @param[in]  PWMx         :  Select the PWM module (PWM0~PWM3)
 * @param[in]  u32PWMFreqHz :  PWM output waveform frequency (Hz)
 * @param[in]  u32DeadTimeNs:  Dead time (Ns)
 *
 * @return     none
 *
 ******************************************************************************/
void PWM_InitComplementaryPairChannel(PWM_REGS *PWMx, uint32_t u32PWMFreqHz, uint32_t u32DeadTimeNs)
{
    uint32_t u32DeadTimeClk;
    uint32_t u32PWMPeriod;
    uint32_t u32Multiple;
    uint32_t u32PWMClockDiv;

    /* Enable PWM clock */
    CLOCK_EnableModule(PWM_MODULE);
    
    /*  PWM initial step */
    /*  Step 1: Set PWM frequency and dead time */
    u32PWMPeriod   = ((CLOCK_GetModuleClock(PWM_MODULE)) / u32PWMFreqHz) / 2;
    u32DeadTimeClk = ((u32DeadTimeNs * ((CLOCK_GetModuleClock(PWM_MODULE)) / 100000)) / 10000);

    /* Disable PWM and interrupt */
    PWMx->TBCTL = 0;
    PWM_DisableTripInt(PWMx, TRIP_INT_ALL);
    PWM_DisableTimeEventInt(PWMx);
    
    /*  Step 2: Caculate clock prescale*/
    u32Multiple = u32PWMPeriod / (TBPRD_VAL_Msk >> TBPRD_VAL_Pos);

    /* [0, 8) */
    if (u32Multiple < 8)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_1, TBCTL_TBDIV_(u32Multiple));
    }
    /* [8, 16) */
    else if (u32Multiple < 16)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_2, TBCTL_TBDIV_(u32Multiple >> 1U));
    }
    /* [16, 32) */
    else if (u32Multiple < 32)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_4, TBCTL_TBDIV_(u32Multiple >> 2U));
    }
    /* [32, 64) */
    else if (u32Multiple < 64)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_8, TBCTL_TBDIV_(u32Multiple >> 3U));
    }
    /* [64, 128) */
    else if (u32Multiple < 128)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_16, TBCTL_TBDIV_(u32Multiple >> 4U));
    }
    /* [128, 256) */
    else if (u32Multiple < 256)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_32, TBCTL_TBDIV_(u32Multiple >> 5U));
    }
    /* [256, 512) */
    else if (u32Multiple < 512)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_64, TBCTL_TBDIV_(u32Multiple >> 6U));
    }
    /* [512, 1024) */
    else if (u32Multiple < 1024)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_128, TBCTL_TBDIV_(u32Multiple >> 7U));
    }
       
    u32PWMClockDiv = PWM_GetClockDiv(PWMx);
    u32PWMPeriod = u32PWMPeriod / u32PWMClockDiv;

    /*  Step 3: PWM clock and counter synchronization configure  */
    /*  Step 3.1: Set PWM frequency, counter type(count up-down as center alignment ) */
    PWMx->TBPRD   = u32PWMPeriod;                       /* PWM frequency setting */
    PWMx->TBCTL  |= TBCTL_CNTMODE_COUNT_UP_DOWN;    /* center alignment and PWM counter start to run */

    /*  Step 3.2: PWM module sync setting */
    PWMx->TBCTL  |=  TBCTL_SYNCOSEL_TBCNT_EQU_ZERO  /* Generate sync signal when TBCNT = Zero */
                     | TBCTL_PHSEN_DISABLE
                     | TBCTL_PHSDIR_COUNT_UP_AFTER_SYNC;

    PWMx->TBPHS = 1;

    /*  Step 4: Set PWM output waveform, central alignment and CMPA with duty are propotional  */
    PWMx->AQCTLA |=   AQCTLA_ZRO_DO_NOTHING
                      | AQCTLA_PRD_DO_NOTHING
                      | AQCTLA_CAU_SET_HIGH
                      | AQCTLA_CAD_SET_LOW;

    /*  Step 5: Set duty reload timing, Shadow mode and reload on period point */
    PWMx->CMPCTL |=   CMPCTL_CMPALOCK_UNLOCK
                      | CMPCTL_CMPBLOCK_UNLOCK
                      | CMPCTL_CMPALOAD_LOAD_ON_ZERO
                      | CMPCTL_CMPBLOAD_LOAD_ON_ZERO;


    /* Step 6: Waveform generating with Dead-time */
    PWMx->DBCTL  = DBCTL_CTLWE_ENABLE; /* Set to 0 */
    PWMx->DBCTL |=   DBCTL_FEDSRC_FROM_A
                     | DBCTL_REDSRC_FROM_A
                     | DBCTL_OUTASRC_RISING_EDGE
                     | DBCTL_OUTBSRC_FALLING_EDGE
                     | DBCTL_REDPOL_ACTIVE_HIGH
                     | DBCTL_FEDPOL_ACTIVE_LOW
                     | DBCTL_HALFCYCLE_DISABLE
                     | DBCTL_REDEN_ENABLE
                     | DBCTL_FEDEN_ENABLE
                     | DBCTL_CTLWE_ENABLE;

    PWMx->DBFED = u32DeadTimeClk / u32PWMClockDiv;       /* Dead time delay */
    PWMx->DBRED = u32DeadTimeClk / u32PWMClockDiv;

    /*  Configure PWM stop mode upon lockup/halted signal triggered by debug or other system events */
    PWMx->TBCTL |= TBCTL_DBGRUN_STOP_AFTER_CYCLE;   // Finish current cycle and stop upon lockup/halted signal

    /* 50% duty */
    PWMx->CMPA = (u32PWMPeriod / 2);
    
    /* Clear Int */
    PWM_ClearTripInt(PWMx, TRIP_INT_ALL);
    PWM_ClearTimeEventInt(PWMx);
}




/******************************************************************************
 * @brief      Initializes PWM single channel
 *             Example : Enable PWM0A or PWM3B
 *             Note    : This function only initial PWM control logic but not Pin
 *
 * @param[in]  PWMx        :  Select the PWM module (PWM0~PWM3)
 * @param[in]  ePWM_CH     :  PWM channel selection (PWM_CHA or PWM_CHB)
 * @param[in]  u32PWMFreqHz:  PWM output waveform frequency (Hz)
 *
 * @return     none
 *
 ******************************************************************************/
void PWM_InitSingleChannel(PWM_REGS *PWMx, PWM_ChannelEnum ePWM_CH, uint32_t u32PWMFreqHz)
{
    uint32_t u32PWMPeriod;
    uint32_t u32Multiple;
    uint32_t u32PWMClockDiv;

    /* Enable PWMx clock */
    CLOCK_EnableModule(PWM_MODULE);

    /*  PWM initial step */
    /*  Step 1: Set PWM frequency and dead time */
    u32PWMPeriod  = ((CLOCK_GetModuleClock(PWM_MODULE)) / u32PWMFreqHz) / 2;

    /* Disable PWM and interrupt */
    PWMx->TBCTL = 0;
    PWM_DisableTripInt(PWMx, TRIP_INT_ALL);
    PWM_DisableTimeEventInt(PWMx);

    /*  Step 2: Caculate clock prescale*/
    u32Multiple = u32PWMPeriod / (TBPRD_VAL_Msk >> TBPRD_VAL_Pos);

    /* [0, 8) */
    if (u32Multiple < 8)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_1, TBCTL_TBDIV_(u32Multiple));
    }
    /* [8, 16) */
    else if (u32Multiple < 16)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_2, TBCTL_TBDIV_(u32Multiple >> 1U));
    }
    /* [16, 32) */
    else if (u32Multiple < 32)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_4, TBCTL_TBDIV_(u32Multiple >> 2U));
    }
    /* [32, 64) */
    else if (u32Multiple < 64)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_8, TBCTL_TBDIV_(u32Multiple >> 3U));
    }
    /* [64, 128) */
    else if (u32Multiple < 128)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_16, TBCTL_TBDIV_(u32Multiple >> 4U));
    }
    /* [128, 256) */
    else if (u32Multiple < 256)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_32, TBCTL_TBDIV_(u32Multiple >> 5U));
    }
    /* [256, 512) */
    else if (u32Multiple < 512)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_64, TBCTL_TBDIV_(u32Multiple >> 6U));
    }
    /* [512, 1024) */
    else if (u32Multiple < 1024)
    {
        PWM_SetClockDiv(PWMx, PWM_CLKDIV0_128, TBCTL_TBDIV_(u32Multiple >> 7U));
    }

    u32PWMClockDiv = PWM_GetClockDiv(PWMx);
    u32PWMPeriod = u32PWMPeriod / u32PWMClockDiv;

    /*  Step 3: PWM clock and counter synchronization configure  */
    /*  Step 3.1: Set PWM frequency, counter type(count up-down as center alignment ) */
    PWMx->TBPRD   = u32PWMPeriod;                       /* PWM frequency setting */
    PWMx->TBCTL  |= TBCTL_CNTMODE_COUNT_UP_DOWN;    /* center alignment and PWM counter start to run */

    /*  Step 3.2: PWM module sync setting */
    PWMx->TBCTL  |=  TBCTL_SYNCOSEL_TBCNT_EQU_ZERO  /* Generate sync signal when TBCNT = Zero */
                     | TBCTL_PHSEN_DISABLE
                     | TBCTL_PHSDIR_COUNT_UP_AFTER_SYNC;

    PWMx->TBPHS   = 1;

    /*  Step 4: Set PWM output waveform, central alignment and CMPA with duty are propotional  */
    if(ePWM_CH == PWM_CHA)
    {
        PWMx->AQCTLA  =  AQCTLA_ZRO_DO_NOTHING
                         | AQCTLA_CAU_SET_HIGH
                         | AQCTLA_PRD_DO_NOTHING
                         | AQCTLA_CAD_SET_LOW;

        /* 50% duty */
        PWMx->CMPA = (u32PWMPeriod / 2);
    }
    else
    {
        PWMx->AQCTLB  =  AQCTLA_ZRO_DO_NOTHING
                         | AQCTLA_CBU_SET_HIGH
                         | AQCTLA_PRD_DO_NOTHING
                         | AQCTLA_CBD_SET_LOW;

        /* 50% duty */
        PWMx->CMPB = (u32PWMPeriod / 2);
    }

    /*  Step 5: Set duty reload timing, shadow mode and reload on zero  */
    PWMx->CMPCTL |=  CMPCTL_CMPALOCK_UNLOCK
                     | CMPCTL_CMPBLOCK_UNLOCK
                     | CMPCTL_CMPALOAD_LOAD_ON_ZERO
                     | CMPCTL_CMPBLOAD_LOAD_ON_ZERO;


    /*  Configure PWM stop mode upon lockup/halted signal triggered by debug or other system events */
    PWMx->TBCTL |= (TBCTL_DBGRUN_STOP_AFTER_CYCLE);    // Finish current cycle and stop upon lockup/halted signal
    
    /* Clear Int */
    PWM_ClearTripInt(PWMx, TRIP_INT_ALL);
    PWM_ClearTimeEventInt(PWMx);
}




/******************************************************************************
 * @brief      Configure TZ0 source from GPIO
 *             The selected pin will be automatically configured as GPIO input
 *
 * @param[in]  ePinName :  Select the pin
 *                         Please refer to PIN_NameEnum
 *             ePinLevel:  Select the GPIO pin level to trigger trip event
 *                         Please refer to GPIO_LevelEnum
 * @return     none
 *
 ******************************************************************************/
void PWM_SetTZ0FromGPIO(PIN_NameEnum ePinName, uint8_t ePinLevel)
{
    /* Set Pin as GPIO input */
    PIN_SetPinAsGPIO(ePinName);
    GPIO_SetPinDir(ePinName, GPIO_INPUT);

    PWMCFG->TZ0SRCCTL = (ePinName << TZ0SRCCTL_IOSEL_Pos) | (ePinLevel << TZ0SRCCTL_POL_Pos);
}




/******************************************************************************
 * @brief      Configure TZ1 source from GPIO
 *             The selected pin will be automatically configured as GPIO input
 *
 * @param[in]  ePinName :  Select the pin
 *                         Please refer to PIN_NameEnum
 *             ePinLevel:  Select the GPIO pin level to trigger trip event
 *                         Please refer to GPIO_LevelEnum
 * @return     none
 *
 ******************************************************************************/
void PWM_SetTZ1FromGPIO(PIN_NameEnum ePinName, uint8_t ePinLevel)
{
    /* Set Pin as GPIO input */
    PIN_SetPinAsGPIO(ePinName);
    GPIO_SetPinDir(ePinName, GPIO_INPUT);

    PWMCFG->TZ1SRCCTL = (ePinName << TZ1SRCCTL_IOSEL_Pos) | (ePinLevel << TZ1SRCCTL_POL_Pos);
}




/******************************************************************************
 * @brief      Configure TZ2 source from GPIO
 *             The selected pin will be automatically configured as GPIO input
 *
 * @param[in]  ePinName :  Select the pin
 *                         Please refer to PIN_NameEnum
 *             ePinLevel:  Select the GPIO pin level to trigger trip event
 *                         Please refer to GPIO_LevelEnum
 * @return     none
 *
 ******************************************************************************/
void PWM_SetTZ2FromGPIO(PIN_NameEnum ePinName, uint8_t ePinLevel)
{
    /* Set Pin as GPIO input */
    PIN_SetPinAsGPIO(ePinName);
    GPIO_SetPinDir(ePinName, GPIO_INPUT);

    PWMCFG->TZ2SRCCTL = (ePinName << TZ2SRCCTL_IOSEL_Pos) | (ePinLevel << TZ2SRCCTL_POL_Pos);
}




/******************************************************************************
 * @brief      Configure TZ3 source from GPIO
 *             The selected pin will be automatically configured as GPIO input
 *
 * @param[in]  ePinName :  Select the pin
 *                         Please refer to PIN_NameEnum
 *             ePinLevel:  Select the GPIO pin level to trigger trip event
 *                         Please refer to GPIO_LevelEnum
 * @return     none
 *
 ******************************************************************************/
void PWM_SetTZ3FromGPIO(PIN_NameEnum ePinName, uint8_t ePinLevel)
{
    /* Set Pin as GPIO input */
    PIN_SetPinAsGPIO(ePinName);
    GPIO_SetPinDir(ePinName, GPIO_INPUT);

    PWMCFG->TZ3SRCCTL = (ePinName << TZ3SRCCTL_IOSEL_Pos) | (ePinLevel << TZ3SRCCTL_POL_Pos);
}




/******************************************************************************
 * @brief      Configure TZ4 source from GPIO
 *             The selected pin will be automatically configured as GPIO input
 *
 * @param[in]  ePinName :  Select the pin
 *                         Please refer to PIN_NameEnum
 *             ePinLevel:  Select the GPIO pin level to trigger trip event
 *                         Please refer to GPIO_LevelEnum
 * @return     none
 *
 ******************************************************************************/
void PWM_SetTZ4FromGPIO(PIN_NameEnum ePinName, uint8_t ePinLevel)
{
    /* Set Pin as GPIO input */
    PIN_SetPinAsGPIO(ePinName);
    GPIO_SetPinDir(ePinName, GPIO_INPUT);

    PWMCFG->TZ4SRCCTL = (ePinName << TZ4SRCCTL_IOSEL_Pos) | (ePinLevel << TZ4SRCCTL_POL_Pos);
}



/******************************************************************************
 * @brief      Configure PWM synchronization signal from GPIO
 *
 * @param[in]  ePinName :  Select the pin
 *                         Please refer to PIN_NameEnum
 *             ePinLevel:  Select the GPIO pin level to generate Sync event
 *                         Please refer to GPIO_LevelEnum
 * @return     none
 *
 ******************************************************************************/
void PWM_SetSyncFromGPIO(PIN_NameEnum ePinName, uint8_t ePinLevel)
{
    /* Set Pin as GPIO input */
    PIN_SetPinAsGPIO(ePinName);
    GPIO_SetPinDir(ePinName, GPIO_INPUT);

    PWMCFG->GPIOSYNCICTL = (ePinName << GPIOSYNCICTL_IOSEL_Pos) | (ePinLevel << GPIOSYNCICTL_POL_Pos);
}




/******************************************************************************
 * @brief      Calculate the counter phase value
 *
 * @param[in]  u32TBPRD   :  PWM counter period
 * @param[in]  eCntMode   :  Counter mode
 * @param[in]  ePHSDIR    :  Phase direction
 *                           Valid value is COUNT_UP (1) or COUNT_DOWN (0)
 * @param[in]  u32SyncVal :  Counter phase value
 * @param[in]  u32TBClkDiv:  TBCLK divider
 *
 * @return     Time-base Phase register value
 *
 ******************************************************************************/
uint32_t PWM_CalculateSyncReloadValue(uint32_t u32TBPRD, PWM_CounterModeEnum eCntMode, uint8_t ePHSDIR, uint32_t u32SyncVal, uint32_t u32TBClkDiv)
{
    uint32_t u32PHSVal = 0;


    if(u32TBClkDiv > 1)
    {
        u32PHSVal = u32SyncVal;
    }
    else
    {
        if(eCntMode == COUNT_UP)
        {
            u32PHSVal = (u32SyncVal + 1) % u32TBPRD;
        }
        else if(eCntMode == COUNT_DOWN)
        {
            u32PHSVal = (u32SyncVal + u32TBPRD - 1) % u32TBPRD;
        }
        else if(eCntMode == COUNT_UP_DOWN)
        {
            if(ePHSDIR == COUNT_UP)
            {
                u32PHSVal = (u32SyncVal == u32TBPRD) ? (u32TBPRD - 1) : (u32SyncVal + 1);
            }
            else if(ePHSDIR == COUNT_DOWN)
            {
                u32PHSVal = (u32SyncVal == 0) ? (1) : (u32SyncVal - 1);
            }
        }
    }

    return u32PHSVal;
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
