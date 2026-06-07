/******************************************************************************
 * @file     system_soc.c
 * @brief    CMSIS Device System Source File for SPCxxxx Device Series
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

#include "spc1169.h"




/**
 *  @brief  Define clocks
 */
#define __SYSTEM_CLOCK            (32000000UL)  /* 32MHz */




///**
// *  @brief  System Core Clock Variable
// */
//uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /* System Core Clock Frequency      */




/**
 *  @brief  System Information Data Variable
 */
SysInfoStruct SysInfo = {
    {__RCO_CLOCK,                /* u32SRCCLK[0] RCO clock frequency */
    __ROSC_CLOCK,               /* u32SRCCLK[1] ROSC clock frequency*/
    CLOCK_FROM_XTAL32MHZ,       /* u32SRCCLK[2] XO clock frequency*/
    0},                          /* u32SRCCLK[3] PLL clock frequency*/
    __RCO_CLOCK,                /* u32SYSCLK */
    0,                          /* i32SHOffset */
    0,                          /* i32SHGain */
};



///******************************************************************************
// * @brief      Updates the SystemCoreClock with current core Clock
// *             retrieved from cpu registers.
// *
// * @param[in]  none
// *
// * @return     none
// *
// ******************************************************************************/
//void SystemCoreClockUpdate (void)
//{
//
//  SystemCoreClock = __SYSTEM_CLOCK;
//
//}




/******************************************************************************
 * @brief      Initialize the system
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void SystemInit (void)
{
    uint32_t u32Temp;
    #if (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2) |                 /* set CP10 Full Access */
                   (3UL << 11*2)  );               /* set CP11 Full Access */
    #endif

    #ifdef UNALIGNED_SUPPORT_DISABLE
      SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    #endif
    
    /* 
     * Clear VDD33UV, VDD33OV, VDD12UV, VDD12OV error flag 
     * when VDD33UV, VDD33OV, VDD12UV, VDD12OV is disabled
     */
    u32Temp = (~READ_REG(SYSTEM->NMIE));
    u32Temp &= READ_REG(SYSTEM->NMRAWIF);
    u32Temp &= (0xF);
    SYSTEM_ClearNonMaskableInt(u32Temp);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

