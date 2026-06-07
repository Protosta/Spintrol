/******************************************************************************
 * @file     ecap.c
 * @brief    ECAP firmware functions.
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

#include "ecap.h"


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
 * @brief      Set capture synchronization source input
 *
 * @param[in]  ECAPx   : Select the ECAP module
 * @param[in]  ePinName: Select the chip pin, should be PIN_NameEnum
 * @param[in]  eLvl    : Select the GPIO pin level to generate Sync event
 *                       Please refer to LEVEL or GPIO_LevelEnum
 *
 * @return     none
 *
 ******************************************************************************/
void ECAP_InitSyncIO(ECAP_REGS* ECAPx, PIN_NameEnum ePinName, LEVEL eLvl)
{
    /* Set pin input */
    PIN_DisableDeglitch(ePinName);

    /* Select Sync event source pin and polarity */
    ECAPx->CAPSYNCICTL = ( (ePinName) << CAPSYNCICTL_IOSEL_Pos ) | ( (eLvl) << CAPSYNCICTL_POL_Pos );
}




/******************************************************************************
 * @brief      Set ECAP input source
 *
 * @param[in]  ECAPx   : Select the ECAP module
 * @param[in]  ePinName: Select the chip pin, should be PIN_NameEnum
 * @param[in]  eLvl    : Select the GPIO pin level to generate Sync event
 *                       Please refer to LEVEL or GPIO_LevelEnum
 *
 * @return     none
 *
 ******************************************************************************/
void ECAP_InitCaptureIO(ECAP_REGS* ECAPx, PIN_NameEnum ePinName, LEVEL eLvl)
{
    /* Set pin input */
    PIN_DisableDeglitch(ePinName);

    /* Select ECAP event source pin */
    ECAPx->CAPSRCCTL = ( (ePinName) << CAPSRCCTL_IOSEL_Pos ) | ( (eLvl) << CAPSRCCTL_POL_Pos );
}




/******************************************************************************
 * @brief      Initializes the ECAP module operating in capture mode
 *
 * @param[in]  ECAPx   :  Select the ECAP module
 * @param[in]  ePinName:  Select the GPIO pin as capture input
 *
 * @return     none
 *
 ******************************************************************************/
void ECAP_CaptureModeInit(ECAP_REGS *ECAPx, PIN_NameEnum ePinName)
{
    /* Open ECAP clock */
    CLOCK_EnableModule(ECAP_MODULE);
    
    /* Configure IO Pin for capture */
    ECAP_SetInput(ECAPx, ePinName, GPIO_LEVEL_HIGH);

    ECAPx->CAPCTL =   CAPCTL_APWMMODE_CAPTURE_MODE        /* Configure ECAP as Capture mode             */
                      | CAPCTL_CAPLDEN_ENABLE               /* Enable Cap Register loading on a capture event */
                      | CAPCTL_STOPWRAP_ON_CAPTURE_EVENT3   /* Stop/Wrap after Capture Event 3            */
                      | CAPCTL_ONESHOT_DISABLE              /* Operate in Continous mode                  */
                      | CAPCTL_CAP0POL_TRIG_ON_RISING_EDGE  /* Event 0 occurs on pulse rising edge        */
                      | CAPCTL_CAP1POL_TRIG_ON_FALLING_EDGE /* Event 1 occurs on pulse falling edge       */
                      | CAPCTL_CAP2POL_TRIG_ON_RISING_EDGE  /* Event 2 occurs on pulse rising edge        */
                      | CAPCTL_CAP3POL_TRIG_ON_FALLING_EDGE /* Event 3 occurs on pulse falling edge       */
                      | CAPCTL_CNTRST0_ENABLE               /* Reset capture counter when Event 0 occurs  */
                      | CAPCTL_CNTRST1_ENABLE               /* Reset capture counter when Event 1 occurs  */
                      | CAPCTL_CNTRST2_ENABLE               /* Reset capture counter when Event 2 occurs  */
                      | CAPCTL_CNTRST3_ENABLE               /* Reset capture counter when Event 3 occurs  */
                      | CAPCTL_TSCNTRUN_STOP_COUNTER;       /* Disable ECAP counter                       */
                      
    /* Disable interrupt */
    ECAP_DisableInt(ECAPx, ECAP_INT_ALL);

    /* Disable Capture event interrupt */
    ECAPx->CAPIE = 0U;
    
    /* Clear Int */
    ECAP_ClearInt(ECAPx, ECAP_INT_ALL);
}




/******************************************************************************
 * @brief      Initializes the ECAP module operating in APWM mode
 *
 * @param[in]  ECAPx     :  Select the ECAP module
 * @param[in]  u32PwmFreq:  Define the frequency of PWM
 *                          This function will calculate period automaticlly
 * @param[in]  u32PwmDuty:  Define the duty of PWM
 *                          PWM duty = u32PwmDuty/10000  (00.00% ~ 100.00%)
 * @param[in]  ePinLevel :  Select the GPIO pin level for active output
 *                          Please refer to GPIO_LevelEnum
 *
 * @return     none
 *
 ******************************************************************************/
void ECAP_APWMModeInit(ECAP_REGS *ECAPx,
                       uint32_t u32PwmFreq, uint32_t u32PwmDuty,
                       LEVEL ePinLevel)
{
    /* Open ECAP clock */
    CLOCK_EnableModule(ECAP_MODULE);
    
    /* Disable ECAP and interrupt */
    ECAP_StopCounter(ECAPx);
    ECAP_DisableInt(ECAPx, ECAP_INT_ALL);
    
    /* Config ECAP operating mode */
    ECAPx->CAPCTL |= CAPCTL_APWMMODE_APWM_MODE;

    /* Calculate Period Value based on system clock and ECAP clock */
    ECAP_SetPRD(ECAPx, CLOCK_GetModuleClock(ECAP_MODULE) / u32PwmFreq);

    /* Set polarity */
    ECAP_SetAPWMOutputPolarity(ECAPx, ePinLevel);
    
    /* Set duty */
    ECAP_APWMSetDuty(ECAPx, u32PwmDuty);
    
    /* Clear Int */
    ECAP_ClearInt(ECAPx, ECAP_INT_ALL);
}




/******************************************************************************
 * @brief      Set the duty of PWM waveform
 *
 * @param[in]  u32PwmDuty:  Define the duty of PWM
 *                          PWM duty = u32PwmDuty/10000  (00.00% ~ 100.00%)
 *
 * @return     none
 *
 ******************************************************************************/
void ECAP_APWMSetDuty(ECAP_REGS *ECAPx, uint32_t u32PwmDuty)
{
    if (GPIO_LEVEL_LOW == ECAP_GetAPWMOutputPolarity(ECAPx))
    {
        u32PwmDuty = 10000 - u32PwmDuty;
    }

    if (u32PwmDuty == 10000)
    {
        ECAPx->CAP1 = ECAPx->CAP0;
    }
    else if (ECAPx->CAP0 >= (0xFFFFFFFFUL / u32PwmDuty))
    {
        ECAPx->CAP1 = (ECAPx->CAP0 / 10000) * u32PwmDuty;
    }
    else
    {
        ECAPx->CAP1 = (ECAPx->CAP0 * u32PwmDuty) / 10000;
    }
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
