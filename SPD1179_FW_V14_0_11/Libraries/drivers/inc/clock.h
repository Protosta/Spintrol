/******************************************************************************
 * @file     clock.h
 * @brief    CLOCK module header file.
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


#ifndef CLOCK_H
#define CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  RCO clock frequency
 */
#define __RCO_CLOCK     (32000000U)
#define __ROSC_CLOCK    (32000000U)




/**
 *  @brief  PLL maximum frequency
 */
#define PLL_MAX_FREQ    (100000000U)





/**
 *  @brief Clock Sources
 */
typedef enum
{
    CLOCK_FROM_RCO        = 0x0U,             /*!< Clock from RCO   */
    CLOCK_FROM_ROSC       = 0x1U,             /*!< Clock from ROSC  */
    CLOCK_FROM_XO         = 0x2U,             /*!< Clock from XO    */
    CLOCK_FROM_PLL        = 0x3U,             /*!< Clock from PLL   */
} CLOCK_SourceEnum;




/**
 *  @brief Clock binary dividing ratio
 */
typedef enum
{
    CLOCK_BINDIV_BY_1     = 0x0U,             /*!< Divide by 1    */
    CLOCK_BINDIV_BY_2     = 0x1U,             /*!< Divide by 2    */
    CLOCK_BINDIV_BY_4     = 0x2U,             /*!< Divide by 4    */
    CLOCK_BINDIV_BY_8     = 0x3U,             /*!< Divide by 8    */
    CLOCK_BINDIV_BY_16    = 0x4U,             /*!< Divide by 16   */
    CLOCK_BINDIV_BY_32    = 0x5U,             /*!< Divide by 32   */
    CLOCK_BINDIV_BY_64    = 0x6U,             /*!< Divide by 64   */
    CLOCK_BINDIV_BY_128   = 0x7U,             /*!< Divide by 128  */
} CLOCK_BinaryDivideEnum;




/**
 *  @brief Peripheral Clock Control Module
 */
typedef enum
{
    ADC_MODULE            = 0x0001U,          /*!< ADC    Module Clock Control */
    PGA_MODULE            = 0x0001U,          /*!< PGA    Module Clock Control */
    COMP_MODULE           = 0x0001U,          /*!< COMP   Module Clock Control */
    PWM_MODULE            = 0x0002U,          /*!< PWM    Module Clock Control */
    ECAP_MODULE           = 0x0004U,          /*!< ECAP   Module Clock Control */
    TIMER0_MODULE         = 0x0008U,          /*!< Timer0 Module Clock Control */
    TIMER1_MODULE         = 0x0010U,          /*!< Timer1 Module Clock Control */
    TIMER2_MODULE         = 0x0020U,          /*!< Timer2 Module Clock Control */
    UART0_MODULE          = 0x0040U,          /*!< UART0  Module Clock Control */
    UART1_MODULE          = 0x0080U,          /*!< UART1  Module Clock Control */
    SPI0_MODULE           = 0x0100U,          /*!< SPI0   Module Clock Control */
    SPI1_MODULE           = 0x0200U,          /*!< SPI1   Module Clock Control */
    I2C_MODULE            = 0x0400U,          /*!< I2C    Module Clock Control */
    CAN_MODULE            = 0x0800U,          /*!< CAN    Module Clock Control */
    AHB_MODULE            = 0x1000U,          /*!< AHB    Module Clock Control */
    DG_MODULE             = 0x2000U,          /*!< DG     Module Clock Control */
    WDT0_MODULE           = 0x4000U,          /*!< WDT0   Module Clock Control */
    WDT1_MODULE           = 0x8000U,          /*!< WDT1   Module Clock Control */
    ALL_MODULE            = 0xFFFFU,          /*!< To query all module clock   */
} CLOCK_ModuleEnum;




/**
 *  @brief Pre-defined CPU frequency
 */
typedef enum
{
    CLOCK_CPU_32MHZ       =  32000000U,       /*!< CPU clock frequency = 32MHz  */
    CLOCK_CPU_25MHZ       =  25000000U,       /*!< CPU clock frequency = 25MHz  */
    CLOCK_CPU_50MHZ       =  50000000U,       /*!< CPU clock frequency = 50MHz  */
    CLOCK_CPU_60MHZ       =  60000000U,       /*!< CPU clock frequency = 60MHz  */
    CLOCK_CPU_75MHZ       =  75000000U,       /*!< CPU clock frequency = 75MHz  */
    CLOCK_CPU_100MHZ      = 100000000U,       /*!< CPU clock frequency = 100MHz */
    CLOCK_CPU_MAX         = 100000000U,       /*!< CPU max   frequency = 100MHz */
} CLOCK_CPUFreqEnum;




/**
 *  @brief Pre-defined system clock source
 */
typedef enum
{
    CLOCK_FROM_RCO32MHZ   = (0U),            /*!< PLL reference clock = RCO0(32MHz) */
    CLOCK_FROM_XTAL6MHZ   = (6000000U),      /*!< PLL reference clock = XO(6MHz)    */
    CLOCK_FROM_XTAL8MHZ   = (8000000U),      /*!< PLL reference clock = XO(8MHz)    */
    CLOCK_FROM_XTAL12MHZ  = (12000000U),     /*!< PLL reference clock = XO(12MHz)   */
    CLOCK_FROM_XTAL24MHZ  = (24000000U),     /*!< PLL reference clock = XO(24MHz)   */
    CLOCK_FROM_XTAL32MHZ  = (32000000U)      /*!< PLL reference clock = XO(32MHz)   */
} CLOCK_PLLRefSelEnum;




/******************************************************************************
 * @brief      Is RCO ready
 *
 * @param[in]  None
 *
 * @return     0 - RCO is not ready
 *             1 - RCO is ready
 *
 ******************************************************************************/
#define CLOCK_IsRCOReady()                  ((CLOCK->CLKSTS & CLKSTS_RCORDY_Msk) >> CLKSTS_RCORDY_Pos)




/******************************************************************************
 * @brief      Is ROSC ready
 *
 * @param[in]  None
 *
 * @return     0 - ROSC is not ready
 *             1 - ROSC is ready
 *
 ******************************************************************************/
#define CLOCK_IsROSCReady()                 ((CLOCK->CLKSTS & CLKSTS_ROSCRDY_Msk) >> CLKSTS_ROSCRDY_Pos)




/******************************************************************************
 * @brief      Is XO ready
 *
 * @param[in]  None
 *
 * @return     0 - XO is not ready
 *             1 - XO is ready
 *
 ******************************************************************************/
#define CLOCK_IsXOReady()                   ((CLOCK->CLKSTS & CLKSTS_XORDY_Msk) >> CLKSTS_XORDY_Pos)




/******************************************************************************
 * @brief      Is PLL ready
 *
 * @param[in]  None
 *
 * @return     0 - PLL is not ready
 *             1 - PLL is ready
 *
 ******************************************************************************/
#define CLOCK_IsPLLReady()                  ((CLOCK->CLKSTS & CLKSTS_PLLRDY_Msk) >> CLKSTS_PLLRDY_Pos)




/******************************************************************************
 * @brief      Is VCO fast
 *
 * @param[in]  None
 *
 * @return     0 - VCO is slow
 *             1 - VCO is fast
 *
 ******************************************************************************/
#define CLOCK_IsVCOFrequencyFast()          ((CLOCK->CLKSTS & CLKSTS_VCOFREQ_Msk) >> CLKSTS_VCOFREQ_Pos)




/******************************************************************************
 * @brief      Is VCO frequency valid
 *
 * @param[in]  None
 *
 * @return     0 - VCO frequency is invalid
 *             1 - VCO frequency is valid
 *
 ******************************************************************************/
#define CLOCK_IsVCOFrequencyValid()         ((CLOCK->CLKSTS & CLKSTS_VCOFREQVLD_Msk) >> CLKSTS_VCOFREQVLD_Pos)




/******************************************************************************
 * @brief      Is PLL too fast
 *
 * @param[in]  None
 *
 * @return     0 - PLL is not too fast
 *             1 - PLL is too fast
 *
 ******************************************************************************/
#define CLOCK_IsPLLTooFast()                ((CLOCK->CLKSTS & CLKSTS_PLLFAST_Msk) >> CLKSTS_PLLFAST_Pos)




/******************************************************************************
 * @brief      Is PLL too slow
 *
 * @param[in]  None
 *
 * @return     0 - PLL is not too slow
 *             1 - PLL is too slow
 *
 ******************************************************************************/
#define CLOCK_IsPLLTooSlow()                ((CLOCK->CLKSTS & CLKSTS_PLLSLOW_Msk) >> CLKSTS_PLLSLOW_Pos)




/******************************************************************************
 * @brief      Is clock detection error
 *
 * @param[in]  None
 *
 * @return     0 - No clock detection error
 *             1 - Clock detection error occurred
 *
 ******************************************************************************/
#define CLOCK_IsDetectionError()            ((CLOCK->CLKSTS & CLKSTS_CLKDETERR_Msk) >> CLKSTS_CLKDETERR_Pos)




/******************************************************************************
 * @brief      Enable/Disable RCO
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_EnableRCO()                   (CLOCK->RCOCTL |= RCOCTL_EN_ENABLE)
#define CLOCK_DisableRCO()                  (CLOCK->RCOCTL &= ~RCOCTL_EN_Msk)




/******************************************************************************
 * @brief      Is RCO enabled
 *
 * @param[in]  None
 *
 * @return     0 - RCO is disabled
 *             1 - RCO is enabled
 *
 ******************************************************************************/
#define CLOCK_IsEnableRCO()                 ((CLOCK->RCOCTL & RCOCTL_EN_Msk) >> RCOCTL_EN_Pos)




/******************************************************************************
 * @brief      Enable/Disable XO
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_EnableXO()                    (CLOCK->XOCTL |= XOCTL_EN_ENABLE)
#define CLOCK_DisableXO()                   (CLOCK->XOCTL &= ~XOCTL_EN_Msk)




/******************************************************************************
 * @brief      Is XO enabled
 *
 * @param[in]  None
 *
 * @return     0 - XO is disabled
 *             1 - XO is enabled
 *
 ******************************************************************************/
#define CLOCK_IsEnableXO()                  ((CLOCK->XOCTL & XOCTL_EN_Msk) >> XOCTL_EN_Pos)




/******************************************************************************
 * @brief      Enable/Disable XO bypass mode
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_EnableXOBypass()              (CLOCK->XOCTL |= XOCTL_BYPASS_BYPASS)
#define CLOCK_DisableXOBypass()             (CLOCK->XOCTL &= ~XOCTL_BYPASS_Msk)




/******************************************************************************
 * @brief      Select input pin for XO in bypass mode
 *
 * @param[in]  PIN_GPIO3 or PIN_GPIO4
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetPinForXOBypass(ePin)                                           \
    (CLOCK->XOCTL = (CLOCK->XOCTL & ~XOCTL_FEEDPIN_Msk)                         \
                  | (((ePin) - PIN_GPIO3) << XOCTL_FEEDPIN_Pos))




/******************************************************************************
 * @brief      Enable/Disable PLL
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_EnablePLL()                   (CLOCK->PLLCTL0 |= PLLCTL0_EN_ENABLE)
#define CLOCK_DisablePLL()                  (CLOCK->PLLCTL0 &= ~PLLCTL0_EN_Msk)




/******************************************************************************
 * @brief      Is PLL enabled
 *
 * @param[in]  None
 *
 * @return     0 - PLL is disabled
 *             1 - PLL is enabled
 *
 ******************************************************************************/
#define CLOCK_IsEnablePLL()                 ((CLOCK->PLLCTL0 & PLLCTL0_EN_Msk) >> PLLCTL0_EN_Pos)




/******************************************************************************
 * @brief      Enable/Disable PLL Trim
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_EnablePLLTrim()               (CLOCK->PLLCTL0 |= PLLCTL0_FCALEN_ENABLE)
#define CLOCK_DisablePLLTrim()              (CLOCK->PLLCTL0 &= ~PLLCTL0_FCALEN_Msk)




/******************************************************************************
 * @brief      Open/Close PLL Trim Window
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_OpenPLLTrimWindow()           (CLOCK->PLLCTL0 |= PLLCTL0_FCALWIN_ENABLE)
#define CLOCK_ClosePLLTrimWindow()          (CLOCK->PLLCTL0 &= ~PLLCTL0_FCALWIN_Msk)




/******************************************************************************
 * @brief      Set PLL input dividing ratio
 *
 * @param[in]  u8Div: Input dividing ratio
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetPLLInputDiv(u8Div)         WRITE_FIELD(CLOCK->PLLCTL1, PLLCTL1_NIN_Msk, PLLCTL1_NIN_Pos, u8Div)




/******************************************************************************
 * @brief      Get PLL input dividing ratio
 *
 * @param[in]  None
 *
 * @return     PLL input dividing ratio
 *
 ******************************************************************************/
#define CLOCK_GetPLLInputDiv()              ((CLOCK->PLLCTL1 & PLLCTL1_NIN_Msk) >> PLLCTL1_NIN_Pos)




/******************************************************************************
 * @brief      Set PLL output dividing ratio
 *
 * @param[in]  u8Div: Output dividing ratio
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetPLLOutputDiv(u8Div)        WRITE_FIELD(CLOCK->PLLCTL1, PLLCTL1_NOUT_Msk, PLLCTL1_NOUT_Pos, (u8Div) - 1)




/******************************************************************************
 * @brief      Get PLL output dividing ratio
 *
 * @param[in]  None
 *
 * @return     PLL output dividing ratio
 *
 ******************************************************************************/
#define CLOCK_GetPLLOutputDiv()             (((CLOCK->PLLCTL1 & PLLCTL1_NOUT_Msk) >> PLLCTL1_NOUT_Pos) + 1)




/******************************************************************************
 * @brief      Set PLL feedback dividing ratio
 *
 * @param[in]  u32Div: Feedback dividing ratio scaled up by 65536
 *                     The actual dividing ratio will be u32Div/65536
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetPLLFeedbackDiv(u32Div)     WRITE_FIELD(CLOCK->PLLCTL1, PLLCTL1_NFB_Msk, PLLCTL1_NFB_Pos, u32Div)




/******************************************************************************
 * @brief      Get PLL feedback dividing ratio
 *
 * @param[in]  None
 *
 * @return     PLL feedback dividing ratio scaled up by 65536
 *
 ******************************************************************************/
#define CLOCK_GetPLLFeedbackDiv()           ((CLOCK->PLLCTL1 & PLLCTL1_NFB_Msk) >> PLLCTL1_NFB_Pos)




/******************************************************************************
 * @brief      Set Reference clock
 *
 * @param[in]  eRefClk: Reference clock defined by CLOCK_SourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetReferenceClock(eRefClk)    WRITE_FIELD(CLOCK->CLKDETCTL, CLKDETCTL_RCLKSEL_Msk, CLKDETCTL_RCLKSEL_Pos, eRefClk)




/******************************************************************************
 * @brief      Set Reference clock dividing ratio
 *
 * @param[in]  eRefDiv: Reference clock dividing ratio by CLOCK_BinaryDivideEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetReferenceClockDiv(eRefDiv)   WRITE_FIELD(CLOCK->CLKDETCTL, CLKDETCTL_RCLKDIV_Msk, CLKDETCTL_RCLKDIV_Pos, eRefDiv)




/******************************************************************************
 * @brief      Set Detect clock
 *
 * @param[in]  eDetClk: Detected clock defined by CLOCK_SourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetDetectClock(eDetClk)       WRITE_FIELD(CLOCK->CLKDETCTL, CLKDETCTL_DCLKSEL_Msk, CLKDETCTL_DCLKSEL_Pos, eDetClk)




/******************************************************************************
 * @brief      Set Detect clock dividing ratio
 *
 * @param[in]  eDetDiv: Detect clock dividing ratio by CLOCK_BinaryDivideEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetDetectClockDiv(eDetDiv)    WRITE_FIELD(CLOCK->CLKDETCTL, CLKDETCTL_DCLKDIV_Msk, CLKDETCTL_DCLKDIV_Pos, eDetDiv)




/******************************************************************************
 * @brief      Enable/Disable clock detection
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_EnableDetection()             (CLOCK->CLKDETCTL |= CLKDETCTL_EN_ENABLE)
#define CLOCK_DisableDetection()            (CLOCK->CLKDETCTL &= ~CLKDETCTL_EN_Msk)




/******************************************************************************
 * @brief      Set clock detection threshold
 *
 * @param[in]  u16Min:  Minimum counter value
 *             u16Max:  Maximum counter value
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetDetectionThreshold(u16Min, u16Max)     (CLOCK->CLKDETCTH = ((u16Min) & 0xFFFF) | ((u16Max) << 16))




/******************************************************************************
 * @brief      Get clock detection counter value
 *
 * @param[in]  None
 *
 * @return     16-bit counter value
 *
 ******************************************************************************/
#define CLOCK_GetDetectionCounterValue()    (CLOCK->CLKDETCNT)




/******************************************************************************
 * @brief      Set system clock source
 *
 * @param[in]  eSrc:  The clock source defined by CLOCK_SourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetSystemClockSource(eSrc)    (CLOCK->SYSCLKCTL = (eSrc) << SYSCLKCTL_SRC_Pos)




/******************************************************************************
 * @brief      Set system clock source
 *
 * @param[in]  None
 *
 * @return     eSrc:  The clock source defined by CLOCK_SourceEnum
 *
 ******************************************************************************/
#define CLOCK_GetSystemClockSource()    ( (CLOCK->SYSCLKCTL & SYSCLKCTL_SRC_Msk) >> SYSCLKCTL_SRC_Pos)




/******************************************************************************
 * @brief      Set watchdog 0 clock source
 *
 * @param[in]  eSrc:  The clock source defined by CLOCK_SourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetWDT0ClockSource(eSrc)      WRITE_FIELD(CLOCK->WDT0CLKCTL, WDT0CLKCTL_SRC_Msk, WDT0CLKCTL_SRC_Pos, eSrc)



/******************************************************************************
 * @brief      Set watchdog 1 clock source
 *
 * @param[in]  eSrc:  The clock source defined by CLOCK_SourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_SetWDT1ClockSource(eSrc)      WRITE_FIELD(CLOCK->WDT1CLKCTL, WDT1CLKCTL_SRC_Msk, WDT1CLKCTL_SRC_Pos, eSrc)




/******************************************************************************
 * @brief      Get watchdog 0 clock source
 *
 * @param[in]  None
 *
 * @return     The clock source
 *
 ******************************************************************************/
#define CLOCK_GetWDT0ClockSource()      ((CLOCK->WDT0CLKCTL & WDT0CLKCTL_SRC_Msk) >> WDT0CLKCTL_SRC_Pos)




/******************************************************************************
 * @brief      Get watchdog 1 clock source
 *
 * @param[in]  None
 *
 * @return     The clock source
 *
 ******************************************************************************/
#define CLOCK_GetWDT1ClockSource()      ((CLOCK->WDT1CLKCTL & WDT1CLKCTL_SRC_Msk) >> WDT1CLKCTL_SRC_Pos)




/******************************************************************************
 * @brief      Enable/Disable the clock of the selected peripheral module
 *
 * @param[in]  eModule:  The peripheral module defined by CLOCK_ModuleEnum
 *
 * @return     None
 *
 * @example    CLOCK_EnableModule(ADC_MODULE);
 *
 ******************************************************************************/
#define CLOCK_EnableModule(eModule)     (CLOCK->PERICLKEN |= (eModule))
#define CLOCK_DisableModule(eModule)    (CLOCK->PERICLKEN &= ~(eModule))




/******************************************************************************
 * @brief      Query module clock enable status
 *
 * @param[in]  eModule:  The peripheral module defined by CLOCK_ModuleEnum
 *
 * @return     0:       None of the queried clocks is enabled
 *             Not 0:   Corresponding clocks for non-zero bit is enabled
 *
 * @example    CLOCK_IsEnableModule(ADC_MODULE | PWM_MODULE);
 *
 ******************************************************************************/
#define CLOCK_IsEnableModule(eModule)   ((CLOCK->PERICLKEN | 0xF000U) & (eModule))




/******************************************************************************
 * @brief      Get the clock dividing ratio of the selected peripheral module
 *
 * @param[in]  eModule:  The peripheral module defined by CLOCK_ModuleEnum
 *
 * @return     For normal module Clock dividing ratio value range from (DIV+1)
 *             For DG module Clock dividing ratio value range from
 *             (DIV+1)*2^PDIV
 *
 ******************************************************************************/
__STATIC_INLINE uint32_t CLOCK_GetModuleDiv(CLOCK_ModuleEnum eModule)
{
    uint32_t u32Div;
    uint32_t u32PDiv;

    if (eModule == DG_MODULE)
    {
        u32Div = READ_FIELD(CLOCK->DGCLKCTL, DGCLKCTL_DIV_Msk, DGCLKCTL_DIV_Pos);
        u32PDiv = READ_FIELD(CLOCK->DGCLKCTL, DGCLKCTL_PDIV_Msk, DGCLKCTL_PDIV_Pos);
        return ((u32Div + 1) * (1 << u32PDiv));
    }
    else if (eModule == WDT0_MODULE)
    {
        return ((CLOCK->WDT0CLKCTL & WDT0CLKCTL_DIV_Msk) + 1);
    }
    else if (eModule == WDT1_MODULE)
    {
        return ((CLOCK->WDT1CLKCTL & WDT1CLKCTL_DIV_Msk) + 1);
    }
    else
    {
        return ((CLOCK->SYSCLKCTL & SYSCLKCTL_DIV_Msk) + 1);
    }
}




/******************************************************************************
 * @brief      Get clock ready status
 *
 * @param[in]  eModule:  The peripheral module defined by CLOCK_ModuleEnum
 *
 * @return     None
 *
 * @example    0:       None of the queried clocks is ready
 *             Not 0:   Corresponding clocks for non-zero bit is ready
 *
 ******************************************************************************/
#define CLOCK_IsModuleReady(eModule)    (CLOCK->PERICLKSTS & (eModule))




/******************************************************************************
 * @brief      Calculate the counter value according to clock frequency and
 *             desired time in us, ns or ms
 *
 * @param[in]  u32Ns/u32Us/u32Ms:  Nero second / Micro second / Milli second
 * @param[in]  u32ClkHz         :  Clock frequency(Hz)
 *
 * @return     Clock cycle count
 *
 * @example    If there is a module with 1MHz working frequency and there is a
 *             counter inside sourced as same as this module.
 *             If we want this counter in 5 us, the following code can help to design
 *             Module.Counter = CLOCK_NsToCounter(5,1000000)
 *
 ******************************************************************************/
#define CLOCK_NsToCounter(u32Ns,u32ClkHz)   (((u32Ns)*((u32ClkHz)/100000))/10000)
#define CLOCK_UsToCounter(u32Us,u32ClkHz)   (((u32Us)*((u32ClkHz)/1000))/1000)
#define CLOCK_MsToCounter(u32Ms,u32ClkHz)   ((u32Ms)*((u32ClkHz)/1000))




/******************************************************************************
 * @brief      Enable write access to the protected CLOCK registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_WALLOW()                      (CLOCK->CLKREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected CLOCK registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define CLOCK_WDIS()                        (CLOCK->CLKREGKEY = 0x0)




/**
 *  @brief  CLOCK Public Function Declaration
 */
ErrorStatus CLOCK_Init(CLOCK_PLLRefSelEnum u32PLLRef, uint32_t u32CPUFreq);
ErrorStatus CLOCK_InitWithRCO(uint32_t u32CPUFreq);
ErrorStatus CLOCK_InitWithXO(uint32_t u32XOFreq, uint32_t u32CPUFreq);
ErrorStatus CLOCK_ConfigurePLL(uint8_t u8RefClkFromXO, uint32_t u32RefClkHz, uint32_t u32PLLClk);
ErrorStatus CLOCK_ConfigurePLLWithRCO(uint32_t u32PLLClk);

ErrorStatus CLOCK_SetModuleDiv(CLOCK_ModuleEnum eModule, uint32_t u32Div);

uint32_t CLOCK_GetModuleClock(CLOCK_ModuleEnum eModule);

ErrorStatus CLOCK_DetectionInit(CLOCK_SourceEnum eRefClk, uint32_t u32RefFreq, CLOCK_SourceEnum eDetClk, uint32_t u32DetFreq, uint32_t u32TolPercent);
ErrorStatus CLOCK_DetectionInitWithRCO(CLOCK_SourceEnum eDetClk, uint32_t u32DetFreq, uint32_t u32TolPercent);

void CLOCK_UpdateInfo(uint32_t u32XOFreq);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* CLOCK_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
