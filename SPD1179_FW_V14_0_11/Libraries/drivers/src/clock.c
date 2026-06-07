/******************************************************************************
 * @file     clock.c
 * @brief    CLOCK firmware functions.
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

#include "clock.h"


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
 * @brief Update clock related information
 *
 * @param[in] u32XOFreq : XO clock frequency
 * Can be any value if XO clock is not used
 *
 * @return none
 *
******************************************************************************/
void CLOCK_UpdateInfo(uint32_t u32XOFreq)
{
    float f32PLLFreq;
    uint32_t u32NFB;
    uint32_t u32NOUT;

    SysInfo.u32SRCCLK[0] = __RCO_CLOCK;
    SysInfo.u32SRCCLK[1] = __ROSC_CLOCK;
    SysInfo.u32SRCCLK[2] = u32XOFreq;

    /* PLL reference clock select */
    if (CLOCK->PLLCTL0 & PLLCTL0_RCLKSELXO_Msk)
    {
        f32PLLFreq = u32XOFreq / 65536.0;
    }
    else 
    {
        f32PLLFreq = __RCO_CLOCK / 65536.0;
    }

    /* PLL input clock dividing ratio */
    if (CLOCK->PLLCTL1 & PLLCTL1_NIN_Msk)
    {
        f32PLLFreq = f32PLLFreq / (READ_FIELD(CLOCK->PLLCTL1, PLLCTL1_NIN_Msk, PLLCTL1_NIN_Pos));
    }

    /* Feedback dividing ratio */
    u32NFB = READ_FIELD(CLOCK->PLLCTL1, PLLCTL1_NFB_Msk, PLLCTL1_NFB_Pos);

    /* VCO to digital clock dividing ratio */
    u32NOUT = READ_FIELD(CLOCK->PLLCTL1, PLLCTL1_NOUT_Msk, PLLCTL1_NOUT_Pos);

    f32PLLFreq = f32PLLFreq * (u32NFB / (u32NOUT + 1));

    SysInfo.u32SRCCLK[3] = (uint32_t)f32PLLFreq;
    SysInfo.u32SYSCLK = SysInfo.u32SRCCLK[CLOCK_GetSystemClockSource()];
}


/******************************************************************************
 * @brief      Configure chip clock system
 *
 * @param[in]  u32CPUFreq:   CPU frequency (HCLK) in Hz
 *                           Pre-defined value in CLOCK_CPUFreqEnum can be used
 *                           for simplicity
 * @param[in]  u32PLLRef  :  PLL reference clock defined by CLOCK_PLLRefSelEnum
 *
 * @return     SUCCESS or ERROR
 *
 *
 * @note       In this function:
 *             - Select PLL as system clock source for CPU and peripherals
 *             - CPU and peripheral clock frequency equal to system clock
 *             - Select RCO as watchdog 0 clock source
 *             - Select ROSC as watchdog 1 clock source
 *
 * @example    (1)  CLOCK_Init(CLOCK_FROM_XTAL6MHZ,CLOCK_CPU_50MHZ);
 *             (2)  CLOCK_Init(CLOCK_FROM_RCO32MHZ,CLOCK_CPU_100MHZ);
 *
 ******************************************************************************/
ErrorStatus CLOCK_Init(CLOCK_PLLRefSelEnum u32PLLRef, uint32_t u32CPUFreq)
{
    ErrorStatus Status = SUCCESS;
    volatile uint32_t u32TimeOut;
    __IO uint32_t  *p = (__IO uint32_t *)0x40000208;

    /* Relax Flash XIP access timing */
    FLASHC_RelaxXIPTiming();

    /* Configure PLL clock */
    if (u32PLLRef == 0U)
    {
        /* Enable RCO */
        CLOCK_EnableRCO();

        /* Wait RCO ready */
        for (u32TimeOut = 10000U; u32TimeOut > 0U; u32TimeOut--)
        {
            if (CLOCK_IsRCOReady() == 1U)
            {
                break;
            }
        }
        
        if ((CLOCK_IsRCOReady() == 0U) || (CLOCK_IsROSCReady() == 0U))
        {
            /* RCO and ROSC are needed by watchdog 0 and watchdog 1 */
            Status = ERROR;
        }
        else
        {
            /* Select RCO as reference */
            Status = CLOCK_ConfigurePLL(0U, 32000000, u32CPUFreq);
        }
    }
    else
    {
        PIN_SetChannel(PIN_GPIO3, PIN_GPIO3_XIN);
        PIN_SetChannel(PIN_GPIO4, PIN_GPIO4_XOUT);
        
        *p = (*p & (~0x18000000)) | (0x3 << 27);
        
        /* Enable XO */
        CLOCK_EnableXO();

        /* Delay more than 50us */
        u32TimeOut = 550;

        while (u32TimeOut)
        {
            u32TimeOut--;
        }
        
        *p = (*p & (~0x18000000)) | (0x2 << 27);

        *p = (*p & (~0x18000000)) | (0x3 << 27);

        /* Wait XO ready */
        for (u32TimeOut = 4000000U; u32TimeOut > 0U; u32TimeOut--)
        {
            if (CLOCK_IsXOReady())
            {
                break;
            }
        }

        if ((u32TimeOut == 0U) || (u32CPUFreq > PLL_MAX_FREQ))
        {
            /* Wait reference clock timeout or invalid PLL clock frequency */
            Status = ERROR;
        }
        else
        {
            SysInfo.u32SRCCLK[2] = u32PLLRef;
            
            /* Select XO as reference */
            Status = CLOCK_ConfigurePLL(1U, u32PLLRef, u32CPUFreq);

        }
    }

    if (Status == SUCCESS)
    {
        /* Select system clock as PLL clock divided by 1 */
        CLOCK->SYSCLKCTL = SYSCLKCTL_SRC_PLL;

        /* Set watchdog 0 clock as RCO clock divided by 1 */
        CLOCK->WDT0CLKCTL = WDT0CLKCTL_SRC_RCO;

        /* Set watchdog 1 clock as ROSC clock divided by 1 */
        CLOCK->WDT1CLKCTL = WDT1CLKCTL_SRC_ROSC;


        /* Update system information */
        SysInfo.u32SRCCLK[0]= __RCO_CLOCK;
        SysInfo.u32SRCCLK[1]= __ROSC_CLOCK;
        SysInfo.u32SYSCLK   = u32CPUFreq;

        /* Update FLASH timing due to the new frequency */
        pHWLIB->FLASHC_SetTiming(u32CPUFreq);

        /* Clear CLK interrupt */
        SYSTEM_ClearNonMaskableInt(NMI_EVENT_PLL_UNLOCK | NMI_EVENT_CLK_DETECT_ERROR);
        
        /* Check PLL status */
        if (CLOCK_IsPLLTooSlow())
        {
            return ERROR;
        }
        if (CLOCK_IsPLLTooFast())
        {
            return ERROR;
        }
    }

    return Status;
}




/******************************************************************************
 * @brief      Configure chip clock system with XO as reference
 *
 * @param[in]  u32XOFreq  :  PLL reference clock
 * @param[in]  u32CPUFreq:   CPU frequency (HCLK) in Hz
 *
 * @return     SUCCESS or ERROR
 *
 *
 * @note       In this function:
 *             - Select XO as system clock source for u32XOFreq is equal to 
 *             u32CPUFreq case
 *             - Select PLL as system clock source for other cases
 *             - CPU and peripheral clock frequency equal to system clock
 *             - Select RCO as watchdog 0 clock source
 *             - Select ROSC as watchdog 1 clock source
 *
 * @example    (1)  CLOCK_InitWithXO(16000000U,50000000U);
 *             (2)  CLOCK_InitWithXO(32000000U,100000000U);
 *
 ******************************************************************************/
ErrorStatus CLOCK_InitWithXO(uint32_t u32XOFreq, uint32_t u32CPUFreq)
{
    ErrorStatus Status = SUCCESS;
    volatile uint32_t  u32TimeOut;
    __IO uint32_t  *p = (__IO uint32_t *)0x40000208;

    /* Relax Flash XIP access timing */
    FLASHC_RelaxXIPTiming();
    
    PIN_SetChannel(PIN_GPIO3, PIN_GPIO3_XIN);
    PIN_SetChannel(PIN_GPIO4, PIN_GPIO4_XOUT);
    
    *p = (*p & (~0x18000000)) | (0x3 << 27);
    
    /* Enable XO */
    CLOCK_EnableXO();

    /* Delay more than 50us */
    u32TimeOut = 550;

    while (u32TimeOut)
    {
        u32TimeOut--;
    }
    
    *p = (*p & (~0x18000000)) | (0x2 << 27);

    *p = (*p & (~0x18000000)) | (0x3 << 27);

    /* Wait XO ready */
    for (u32TimeOut = 4000000U; u32TimeOut > 0U; u32TimeOut--)
    {
        if (CLOCK_IsXOReady())
        {
            break;
        }
    }

    if ((u32TimeOut == 0U) || (u32CPUFreq > PLL_MAX_FREQ))
    {
        /* Wait reference clock timeout or invalid PLL clock frequency */
        Status = ERROR;
    }
    else
    {
        if (u32CPUFreq != u32XOFreq)
        {
            /* Configure PLL clock */
            Status = CLOCK_ConfigurePLL(1U, u32XOFreq, u32CPUFreq);
        }
    }

    if (Status == SUCCESS)
    {
        if (u32CPUFreq == u32XOFreq)
        {
            /* Select system clock as XO clock divided by 1 */
            CLOCK->SYSCLKCTL = SYSCLKCTL_SRC_XO;
        }
        else
        {
            /* Select system clock as PLL clock divided by 1 */
            CLOCK->SYSCLKCTL = SYSCLKCTL_SRC_PLL;
        }

        /* Set watchdog 0 clock as RCO clock divided by 1 */
        CLOCK->WDT0CLKCTL = WDT0CLKCTL_SRC_RCO;

        /* Set watchdog 1 clock as ROSC clock divided by 1 */
        CLOCK->WDT1CLKCTL = WDT1CLKCTL_SRC_ROSC;

        /* Update system information */
        SysInfo.u32SRCCLK[0] = __RCO_CLOCK;
        SysInfo.u32SRCCLK[1] = __ROSC_CLOCK;
        SysInfo.u32SRCCLK[2] = u32XOFreq;
        SysInfo.u32SYSCLK    = u32CPUFreq;

        /* Update FLASH timing due to the new frequency */
        pHWLIB->FLASHC_SetTiming(u32CPUFreq);
        
        /* Clear CLK interrupt */
        SYSTEM_ClearNonMaskableInt(NMI_EVENT_PLL_UNLOCK | NMI_EVENT_CLK_DETECT_ERROR);
        
        /* Check PLL status */
        if (CLOCK_IsPLLTooSlow())
        {
            return ERROR;
        }
        if (CLOCK_IsPLLTooFast())
        {
            return ERROR;
        }
    }

    return Status;
}




/******************************************************************************
 * @brief      Configure chip clock system with RCO as reference
 *
 * @param[in]  u32CPUFreq:   CPU frequency (HCLK) in Hz
 *
 * @return     SUCCESS or ERROR
 *
 * @note       In this function:
 *             - Select RCO as system clock source for 32MHz case
 *             - Select PLL as system clock source for other cases
 *             - CPU and peripheral clock frequency equal to system clock
 *             - Select RCO as watchdog 0 clock source
 *             - Select ROSC as watchdog 1 clock source
 *
 * @example    (1)  CLOCK_InitWithRCO(32000000U);
 *             (2)  CLOCK_InitWithRCO(100000000U);
 *
 ******************************************************************************/
ErrorStatus CLOCK_InitWithRCO(uint32_t u32CPUFreq)
{
    ErrorStatus Status = SUCCESS;
    volatile uint32_t    u32TimeOut;

    /* Relax Flash XIP access timing */
    FLASHC_RelaxXIPTiming();

    /* Enable RCO */
    CLOCK_EnableRCO();

    /* Wait RCO ready */
    for (u32TimeOut = 10000U; u32TimeOut > 0U; u32TimeOut--)
    {
        if (CLOCK_IsRCOReady() == 1U)
        {
            break;
        }
    }

    if ((CLOCK_IsRCOReady() == 0U) || (CLOCK_IsROSCReady() == 0U))
    {
        /* RCO and ROSC are needed by watchdog 0 and watchdog 1 */
        Status = ERROR;
    }
    else
    {
        if (u32CPUFreq != 32000000U)
        {
            /* Configure PLL clock */
            Status = CLOCK_ConfigurePLL(0U, 32000000, u32CPUFreq);
        }
    }

    if (Status == SUCCESS)
    {
        if (u32CPUFreq == 32000000U)
        {
            /* Select system clock as PLL clock divided by 1 */
            CLOCK->SYSCLKCTL = SYSCLKCTL_SRC_RCO;
        }
        else
        {
            /* Select system clock as PLL clock divided by 1 */
            CLOCK->SYSCLKCTL = SYSCLKCTL_SRC_PLL;
        }

        /* Set watchdog 0 clock as RCO clock divided by 1 */
        CLOCK->WDT0CLKCTL = WDT0CLKCTL_SRC_RCO;

        /* Set watchdog 1 clock as ROSC clock divided by 1 */
        CLOCK->WDT1CLKCTL = WDT1CLKCTL_SRC_ROSC;

        /* Update system information */
        SysInfo.u32SRCCLK[0]= __RCO_CLOCK;
        SysInfo.u32SRCCLK[1]= __ROSC_CLOCK;
        SysInfo.u32SYSCLK   = u32CPUFreq;

        /* Update FLASH timing due to the new frequency */
        pHWLIB->FLASHC_SetTiming(u32CPUFreq);
        
        /* Clear CLK interrupt */
        SYSTEM_ClearNonMaskableInt(NMI_EVENT_PLL_UNLOCK | NMI_EVENT_CLK_DETECT_ERROR);
        
        /* Check PLL status */
        if (CLOCK_IsPLLTooSlow())
        {
            return ERROR;
        }
        if (CLOCK_IsPLLTooFast())
        {
            return ERROR;
        }
    }

    return Status;
}




/******************************************************************************
 * @brief      Configure PLL clock
 *
 * @param[in]  u8RefClkFromXO:  Reference clock selection
 *                               - \ref 1 -> clock source(reference) is from external crystal clock
 *                               - \ref 0 -> clock source(reference) is from internal RCO(32MHz)
 * @param[in]  u32RefClkHz   :  Reference clock frequency (Hz)
 * @param[in]  u32PLLClk     :  PLL output clock frequency (Hz)
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus CLOCK_ConfigurePLL(uint8_t u8RefClkFromXO, uint32_t u32RefClkHz, uint32_t u32PLLClk)
{
    volatile uint32_t  u32TimeOut;
    uint32_t       u32NOUT;
    uint32_t       u32NIN;
    uint32_t       u32NFB;
    uint32_t       u32VCOBand;
    uint64_t       u64NFB;
    ErrorStatus Status = SUCCESS;

    if (u32PLLClk > PLL_MAX_FREQ)
    {
        /* Invalid PLL clock frequency */
        Status = ERROR;
    }
    else
    {
        /* NIN number */
        if (u32RefClkHz <= 8000000U)
        {
            u32NIN = 1U;
        }
        else if (u32RefClkHz <= 16000000U)
        {
            u32NIN = 2U;
        }
        else if (u32RefClkHz <= 24000000U)
        {
            u32NIN = 3U;
        }
        else if (u32RefClkHz <= 32000000U)
        {
            u32NIN = 4U;
        }
        else if (u32RefClkHz <= 40000000U)
        {
            u32NIN = 5U;
        }
        else if (u32RefClkHz <= 48000000U)
        {
            u32NIN = 6U;
        }
        else if (u32RefClkHz <= 56000000U)
        {
            u32NIN = 7U;
        }
        else
        {
            Status = ERROR;
        }


        if (Status == SUCCESS)
        {
            /* NOUT number (VCO range is [400 : 600] MHz) */
            if (u32PLLClk > 75000000U)
            {
                u32NOUT = 6U;      /* (75 : 100] MHz */
            }
            else if (u32PLLClk > 50000000U)
            {
                u32NOUT = 8U;      /* (50 : 75] MHz    */
            }
            else if (u32PLLClk > 37500000U)
            {
                u32NOUT = 12U;     /* (37.5 : 50] MHz  */
            }
            else if (u32PLLClk >= 25000000U)
            {
                u32NOUT = 16U;     /* [25 : 37.5] MHz  */
            }
            else
            {
                Status = ERROR;
            }
        }


        if (Status == SUCCESS)
        {
            /* NFB Number */
            u32NFB = u32PLLClk * u32NOUT;
            u64NFB = ((uint64_t)u32NIN) << 16;
            u64NFB = u64NFB * ((uint64_t)u32NFB);
            u64NFB = u64NFB / ((uint64_t)u32RefClkHz);
            u32NFB = (uint32_t)u64NFB;

            /* Set NIN, NOUT and NFB */
            CLOCK->PLLCTL1 = ((u32NOUT - 1U) << PLLCTL1_NOUT_Pos) | (u32NIN << PLLCTL1_NIN_Pos) | (u32NFB << PLLCTL1_NFB_Pos);

            /* Set ICP, Reference clock, and enable PLL */
            u32VCOBand = (CLOCK->PLLCTL0 & PLLCTL0_VCOBAND_Msk) >> PLLCTL0_VCOBAND_Pos;

            CLOCK->PLLCTL0 = (u32VCOBand << PLLCTL0_VCOBAND_Pos) |
                             (((96U * u32NFB / (11U - u32VCOBand) / 100U) >> 16) << PLLCTL0_ICP_Pos) |
                             (u8RefClkFromXO << PLLCTL0_RCLKSELXO_Pos) |
                             PLLCTL0_EN_ENABLE;

            /* Wait PLL clock ready */
            for (u32TimeOut = 100000U; u32TimeOut > 0U; u32TimeOut--)
            {
                if (CLOCK_IsPLLReady() == 1U)
                {
                    break;
                }
            }

            /* PLL can't be ready */
            if (CLOCK_IsPLLReady() == 0U)
            {
                Status = ERROR;
            }
        }
    }
    
    /* Clear PLL unlock and detect error flag */
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_PLL_UNLOCK | NMI_EVENT_CLK_DETECT_ERROR);

    SysInfo.u32SRCCLK[3] = u32PLLClk;

    return Status;
}




/******************************************************************************
 * @brief      Configure PLL clock with reference from RCO
 *
 * @param[in]  u32PLLClk:  PLL clock output frequency (Hz)
 *                         It should be <= 100MHz
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus CLOCK_ConfigurePLLWithRCO(uint32_t u32PLLClk)
{
    volatile uint32_t    u32TimeOut;
    uint32_t    u32NOUT;
    uint32_t    u32NFB;
    uint32_t    u32VCOBand;
    ErrorStatus Status = SUCCESS;

    /* Enable RCO */
    CLOCK_EnableRCO();

    /* Wait RCO ready */
    for (u32TimeOut = 10000U; u32TimeOut > 0U; u32TimeOut--)
    {
        if (CLOCK_IsRCOReady() == 1U)
        {
            break;
        }
    }

    if ((CLOCK_IsRCOReady() == 0U) || (u32PLLClk > PLL_MAX_FREQ))
    {
        /* RCO not ready or invalid PLL clock frequency */
        Status = ERROR;
    }
    else
    {
        /* NOUT number (VCO range is [400 : 600] MHz) */
        if (u32PLLClk > 75000000U)
        {
            u32NOUT = 6U;      /* (75 : 100] MHz */
        }
        else if (u32PLLClk > 50000000U)
        {
            u32NOUT = 8U;      /* (50 : 75] MHz    */
        }
        else if (u32PLLClk > 37500000U)
        {
            u32NOUT = 12U;     /* (37.5 : 50] MHz  */
        }
        else if (u32PLLClk >= 25000000U)
        {
            u32NOUT = 16U;     /* [25 : 37.5] MHz  */
        }
        else
        {
            Status = ERROR;
        }


        if (Status == SUCCESS)
        {
            /* NFB Number */
            u32NFB = u32PLLClk * u32NOUT / 25U * 128U / 625U;

            /* Set NIN, NOUT and NFB */
            CLOCK->PLLCTL1 = ((u32NOUT - 1U) << PLLCTL1_NOUT_Pos) | (4U << PLLCTL1_NIN_Pos) | (u32NFB << PLLCTL1_NFB_Pos);

            /* Set ICP, Reference clock, and enable PLL */
            u32VCOBand = (CLOCK->PLLCTL0 & PLLCTL0_VCOBAND_Msk) >> PLLCTL0_VCOBAND_Pos;

            CLOCK->PLLCTL0 = (u32VCOBand << PLLCTL0_VCOBAND_Pos) |
                             (((96U * u32NFB / (11U - u32VCOBand) / 100U) >> 16) << PLLCTL0_ICP_Pos) |
                             PLLCTL0_RCLKSELXO_RCO | PLLCTL0_EN_ENABLE;

            /* Wait PLL clock ready */
            for (u32TimeOut = 100000U; u32TimeOut > 0U; u32TimeOut--)
            {
                if (CLOCK_IsPLLReady() == 1U)
                {
                    break;
                }
            }

            /* PLL can't be ready */
            if (CLOCK_IsPLLReady() == 0U)
            {
                Status = ERROR;
            }
        }
    }

    SysInfo.u32SRCCLK[3] = u32PLLClk;

    return Status;
}




/******************************************************************************
 * @brief      Set the clock dividing ratio of the selected peripheral module
 *
 * @param[in]  eModule:  The peripheral module defined by CLOCK_ModuleEnum
 * @param[in]  u32Div :  Clock dividing ratio value
 *
 * @return     none
 *
 * @example    CLOCK_SetModuleDiv(PWM_MODULE, 2);
 *             CLOCK_SetModuleDiv(ADC_MODULE, 4);
 *
 ******************************************************************************/
ErrorStatus CLOCK_SetModuleDiv(CLOCK_ModuleEnum eModule, uint32_t u32Div)
{
    ErrorStatus status = SUCCESS;

    if (u32Div < 1 || u32Div > 256)
    {
        status = ERROR;
    }
    else
    {
        switch(eModule)
        {
            case WDT0_MODULE:
                CLOCK->WDT0CLKCTL = (CLOCK->WDT0CLKCTL & (~WDT0CLKCTL_DIV_Msk))
                                    | ((u32Div - 1) & WDT0CLKCTL_DIV_Msk);
                break;
            case WDT1_MODULE:
                CLOCK->WDT1CLKCTL = (CLOCK->WDT1CLKCTL & (~WDT1CLKCTL_DIV_Msk))
                                    | ((u32Div - 1) & WDT1CLKCTL_DIV_Msk);
                break;
            case DG_MODULE:
                CLOCK->DGCLKCTL = u32Div - 1;
                break;
            default:
                CLOCK->SYSCLKCTL = (CLOCK->SYSCLKCTL & (~SYSCLKCTL_DIV_Msk))
                                    | ((u32Div - 1) & SYSCLKCTL_DIV_Msk);
                SysInfo.u32SYSCLK = SysInfo.u32SRCCLK[CLOCK_GetSystemClockSource()] / u32Div;
                break;
        }
    }

    return status;
}



/******************************************************************************
 * @brief      Get the clock frequency (Hz) of the selected peripheral module
 *
 * @param[in]  eModule:  The peripheral module defined by CLOCK_ModuleEnum
 *
 * @return     Clock frequency in Hz
 *
 * @note       This function can only excute correctly after CLOCK_Init()
 *
 ******************************************************************************/
uint32_t CLOCK_GetModuleClock(CLOCK_ModuleEnum eModule)
{
    uint32_t u32Div, u32Clk;

    uint8_t u8Src;

    u32Div = CLOCK_GetModuleDiv(eModule);

    if (eModule == WDT0_MODULE)
    {
        u8Src = CLOCK_GetWDT0ClockSource();
    }
    else if (eModule == WDT1_MODULE)
    {
        u8Src = CLOCK_GetWDT1ClockSource();
    }
    else
    {
        u8Src = CLOCK_GetSystemClockSource();
    }
    u32Clk = SysInfo.u32SRCCLK[u8Src] / u32Div;

    return u32Clk;
}




/******************************************************************************
 * @brief      Initialize the clock detection
 *
 * @param[in]  eRefClk      : Reference clock defined by CLOCK_SourceEnum
 *             u32RefFreq   : Reference clock frequency in Hz
 *             eDetClk      : Detected clock defined by CLOCK_SourceEnum
 *             u32DetFreq   : Detected clock frequency in Hz
 *             u32TolPercent: Frequency error tolerance in percent (<= 50%)
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus CLOCK_DetectionInit(CLOCK_SourceEnum eRefClk, uint32_t u32RefFreq, CLOCK_SourceEnum eDetClk, uint32_t u32DetFreq, uint32_t u32TolPercent)
{
    uint32_t    u32Cnt;
    uint32_t    u32CntMax;
    ErrorStatus Status;

    /* Check input parameters */
    if ((((eRefClk == CLOCK_FROM_RCO) || (eDetClk == CLOCK_FROM_RCO)) && (CLOCK_IsRCOReady() == 0)) ||
            (((eRefClk == CLOCK_FROM_ROSC) || (eDetClk == CLOCK_FROM_ROSC)) && (CLOCK_IsROSCReady() == 0)) ||
            (((eRefClk == CLOCK_FROM_XO) || (eDetClk == CLOCK_FROM_XO)) && (CLOCK_IsXOReady() == 0)) ||
            (((eRefClk == CLOCK_FROM_PLL) || (eDetClk == CLOCK_FROM_PLL)) && (CLOCK_IsPLLReady() == 0)) ||
            (u32RefFreq > 100000000UL) || (u32DetFreq > 100000000UL) || (u32TolPercent > 50UL) ||
            (eRefClk > CLOCK_FROM_PLL) || (eDetClk > CLOCK_FROM_PLL) || (eRefClk == eDetClk))
    {
        Status = ERROR;
    }
    else
    {
        /* Detection Counter value */
        u32Cnt    = ((uint64_t)u32DetFreq << 16) / u32RefFreq;
        u32CntMax = u32Cnt * (100 + u32TolPercent) / 100;

        Status = SUCCESS;

        if (u32CntMax <= 511UL)
        {
            u32Cnt = u32Cnt << 7;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_128 << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 1023UL)
        {
            u32Cnt = u32Cnt << 6;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_64  << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 2047UL)
        {
            u32Cnt = u32Cnt << 5;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_32  << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 4095UL)
        {
            u32Cnt = u32Cnt << 4;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_16  << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 8191UL)
        {
            u32Cnt = u32Cnt << 3;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_8   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 16383UL)
        {
            u32Cnt = u32Cnt << 2;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_4   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 32767UL)
        {
            u32Cnt = u32Cnt << 1;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_2   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 65535UL)
        {
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 131070UL)
        {
            u32Cnt = u32Cnt >> 1;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_2   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 262140UL)
        {
            u32Cnt = u32Cnt >> 2;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_4   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 524280UL)
        {
            u32Cnt = u32Cnt >> 3;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_8   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 1048560UL)
        {
            u32Cnt = u32Cnt >> 4;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_16  << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 2097120UL)
        {
            u32Cnt = u32Cnt >> 5;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_32  << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 4194240UL)
        {
            u32Cnt = u32Cnt >> 6;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_64  << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 8388480UL)
        {
            u32Cnt = u32Cnt >> 7;
            CLOCK->CLKDETCTL = (eRefClk             << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_128 << CLKDETCTL_DCLKDIV_Pos);
        }
        else
        {
            Status = ERROR;
        }

        /* Detection Counter threshold */
        CLOCK->CLKDETCTH  = u32Cnt * (100 - u32TolPercent) / 100;
        u32CntMax         = u32Cnt * (100 + u32TolPercent) / 100;
        CLOCK->CLKDETCTH |= u32CntMax << 16;

        /* Enable clock detection */
        CLOCK->CLKDETCTL |= CLKDETCTL_EN_ENABLE;
    }

    return Status;
}




/******************************************************************************
 * @brief      Initialize the clock detection with RCO as the reference
 *
 * @param[in]  eDetClk      : Select the detected clock
 *                            Please refer to CLOCK_SourceEnum
 *             u32DetFreq   : Detected clock frequency in Hz
 *             u32TolPercent: Frequency error tolerance in percent (<= 50%)
 *
 * @return     SUCCESS or ERROR
 *
 * @note       In this function:
 *             - RCO is always selected as the reference clock
 *
 ******************************************************************************/
ErrorStatus CLOCK_DetectionInitWithRCO(CLOCK_SourceEnum eDetClk, uint32_t u32DetFreq, uint32_t u32TolPercent)
{
    uint32_t    u32Cnt;
    uint32_t    u32CntMax;
    volatile uint32_t    u32TimeOut;
    ErrorStatus Status;


    /* Detection Counter value */
    u32Cnt    = (u32DetFreq << 5) / 15625;
    u32CntMax = u32Cnt * (100 + u32TolPercent) / 100;

    /* Enable RCO and wait it is ready */
    CLOCK_EnableRCO();
    for (u32TimeOut = 10000; u32TimeOut > 0; u32TimeOut--)
    {
        if (CLOCK_IsRCOReady())
        {
            break;
        }
    }

    /* Check clock ready status and input parameters */
    if ((u32TolPercent > 50UL) || (u32DetFreq > 100000000UL) || (CLOCK_IsRCOReady() == 0) ||
            ((eDetClk == CLOCK_FROM_ROSC) && (CLOCK_IsROSCReady() == 0)) ||
            ((eDetClk == CLOCK_FROM_XO  ) && (CLOCK_IsXOReady()   == 0)) ||
            ((eDetClk == CLOCK_FROM_PLL ) && (CLOCK_IsPLLReady()  == 0)))
    {
        Status = ERROR;
    }
    else
    {
        Status = SUCCESS;

        if (u32CntMax <= 511)
        {
            u32Cnt = u32Cnt << 7;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO      << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_128 << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 1023)
        {
            u32Cnt = u32Cnt << 6;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_64  << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 2047)
        {
            u32Cnt = u32Cnt << 5;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_32  << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 4095)
        {
            u32Cnt = u32Cnt << 4;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_16  << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 8191)
        {
            u32Cnt = u32Cnt << 3;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_8   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 16383)
        {
            u32Cnt = u32Cnt << 2;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_4   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 32767)
        {
            u32Cnt = u32Cnt << 1;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_2   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 65535)
        {
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 131070)
        {
            u32Cnt = u32Cnt >> 1;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_2   << CLKDETCTL_DCLKDIV_Pos);
        }
        else if (u32CntMax <= 262140)
        {
            u32Cnt = u32Cnt >> 2;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_4   << CLKDETCTL_DCLKDIV_Pos);
        }
        else
        {
            u32Cnt = u32Cnt >> 3;
            CLOCK->CLKDETCTL = (CLOCK_FROM_RCO     << CLKDETCTL_RCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_1   << CLKDETCTL_RCLKDIV_Pos) |
                               (eDetClk             << CLKDETCTL_DCLKSEL_Pos) |
                               (CLOCK_BINDIV_BY_8   << CLKDETCTL_DCLKDIV_Pos);
        }

        /* Detection Counter threshold */
        CLOCK->CLKDETCTH  = u32Cnt * (100 - u32TolPercent) / 100;
        u32CntMax         = u32Cnt * (100 + u32TolPercent) / 100;
        CLOCK->CLKDETCTH |= u32CntMax << 16;

        /* Enable clock detection */
        CLOCK->CLKDETCTL |= CLKDETCTL_EN_ENABLE;
    }

    return Status;
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
