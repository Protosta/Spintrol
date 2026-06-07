/******************************************************************************
 * @file     phcomp.c
 * @brief    PHCOMP firmware functions.
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

#include "phcomp.h"


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
 * @brief      Set PHCOMP filter window size and threshold
 *
 * @param[in]  u8WinSize  : Filter window size (1 ~ 32)
 * @param[in]  u8Threshold: Filter threshold value (1 ~ 32)
 *
 * @return     none
 *
 *******************************************************************************/
void PHCOMP_SetFilterWindow(uint8_t u8WinSize, uint8_t u8Threshold)
{
    /* Invalid Window size */
    if ((u8WinSize == 0) || (u8WinSize > 32))
    {
        return;
    }

    /* Invalid Window Threshold */
    if ((u8Threshold == 0) || (u8Threshold > 32))
    {
        return;
    }

    /* Configure Filter Window */
    MODIFY_REG(PHCOMP->PHCOMPFILTER, PHCOMPFILTER_FLTWIN_Msk | PHCOMPFILTER_FLTTH_Msk, 
    ((u8WinSize   - 1) << PHCOMPFILTER_FLTWIN_Pos) | ((u8Threshold - 1) << PHCOMPFILTER_FLTTH_Pos));
}




/******************************************************************************
 * @brief      Set Trip-zone filter window size and threshold (nero second)
 *
 * @param[in]  u32SizeTimeNS     : Window Size (Time in ns)
 * @param[in]  u32ThresholdTimeNS: Threshold (Time in ns)
 *
 * @return     none
 *
 *******************************************************************************/
void PHCOMP_SetFilterWindowTimeNs(uint32_t u32SizeTimeNS, uint32_t u32ThresholdTimeNS)
{
    uint32_t u32TimeCnt1, u32TimeCnt2;
    uint32_t u32FilterDiv;
    
    /* Use the max Filter Window Size(32U) to caculate minimum Filter Div */
    u32FilterDiv = SysInfo.u32SYSCLK / 100000U * (u32SizeTimeNS) / (32U * 10000U);
    
    /* If minimum Filter Div if too small, increase the Filter Div to legal range, at this time, Filter Window Size is decreased */
    if (u32FilterDiv == 0U)
    {
        /* Use the minimum Filter Div to recaculate Filter Window Size, at this time, 0U <= Filter Window Size < 32U*/
        u32FilterDiv++;
        u32TimeCnt1 = (SysInfo.u32SYSCLK / 100000U * (u32SizeTimeNS) /u32FilterDiv / 10000U);
    }
    /* else if minimum Filter Div if too big, decrease the Filter Div to legal range, at this time, Filter Window Size is increased,
    force Filter Window Size to legal range*/
    else if (u32FilterDiv >= 1024U)
    {
        u32FilterDiv = 1024U;
        
        u32TimeCnt1 = 32U;
    }
    else
    {
        /* Use the minimum Filter Div to recaculate Filter Window Size */
        u32TimeCnt1 = (SysInfo.u32SYSCLK / 100000U * (u32SizeTimeNS) /u32FilterDiv / 10000U);
        
        /* If minimum Filter Div can not set Filter Window Size <= 32U, use the (u32FilterDiv + 1) to recaculate Filter Window Size, 
        at this time, Filter Window Size is decreased */
        if (u32TimeCnt1 > 32U)
        {
            /* Use the minimum Filter Div to recaculate Filter Window Size, at this time, 0U <= Filter Window Size < 32U*/
            u32FilterDiv++;
            u32TimeCnt1 = (SysInfo.u32SYSCLK / 100000U * (u32SizeTimeNS) /u32FilterDiv / 10000U);
        }
    }
    
    /* If Filter Window Size is decreased to 0, set to 1 */
    if (u32TimeCnt1 == 0U)
    {
        u32TimeCnt1 = 1U;
    }
    
    /* Caculate Filter Threshold */
    u32TimeCnt2 = SysInfo.u32SYSCLK / 100000U * (u32ThresholdTimeNS) / u32FilterDiv / 10000U;
    
    /* Threshold value must be bigger than WindowSize/2 */
    if ((u32TimeCnt2 * 2) < u32TimeCnt1)
    {
        u32TimeCnt2 = u32TimeCnt1 / 2 + 1;
    }

    if (u32TimeCnt2 == 0)
    {
        u32TimeCnt2 = 1;
    }
    else if (u32TimeCnt2 > 32)
    {
        u32TimeCnt2 = 32;
    }
    
    /* Set Filter Div */
    PHCOMP_SetFilterClockDiv(u32FilterDiv);

    PHCOMP_SetFilterWindow(u32TimeCnt1, u32TimeCnt2);
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
