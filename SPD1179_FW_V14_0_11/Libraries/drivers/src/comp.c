/******************************************************************************
 * @file     comp.c
 * @brief    Comparator firmware functions.
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

#include "comp.h"


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
 * @brief      Configure Comparator
 *
 * @param[in]  eCOMP            :  Select the comparator
 *                                 Please refer to COMP_ComparatorSelEnum
 * @param[in]  eCH              :  Select the comparator input channel
 *                                 Please refer to COMP_InputChannelEnum
 * @param[in]  i32DACVoltageMV  :  DAC voltage range from 0(0 voltage) ~ 3300 (3300 mV = 3.3 V)
 * @param[in]  u32FilterWindowNs:  Filter sample window (nero second)
 *                                   If Filter Clock =10MHZ, its range from 0~31*(1/10MHz)= 3100 ns= 3.1 us
 *
 * @return     none
 *
 * @note       (1) All COMP_x_LO share same DAC_LO(DAC1)
 *             (2) All COMP_x_HI share same DAC_HI(DAC0)
 *             (3) This function do NOT saturate DAC value and deglitch(filter) value, please note it!
 *
 ******************************************************************************/
void COMP_Init(COMP_ComparatorSelEnum eCOMP, COMP_InputChannelEnum eCH, int32_t i32DACVoltageMV, uint32_t u32FilterWindowNs)
{
    /* Enable Comparator clock */
    CLOCK_EnableModule(COMP_MODULE);

    /* Disable comparator */
    COMP_Disable(eCOMP);

    /* Set Input channe1 */
    COMP_SelectChannel(eCOMP, eCH);

    /* Set comparator output = Filtered */
    COMP_SetOutputType(eCOMP, COMP_OUTPUT_FILTERED);

    /* Set Filter window - Threshld value = 0.6 * Window Size */
    COMP_SetFilterWindowTimeNs(eCOMP, u32FilterWindowNs, u32FilterWindowNs * 3 / 5);

    /* Enable DAC for comparison */
    COMP_EnableDAC(DAC0);
    COMP_EnableDAC(DAC1);

    /* Set DAC value */
    switch (eCOMP)
    {
        case COMP_H:
            COMP_SetDACVoltage(DAC0, i32DACVoltageMV);
            break;

        case COMP_L:
            COMP_SetDACVoltage(DAC1, i32DACVoltageMV);
            break;
    }

    /* Clear latched filter status */
    COMP_ClearFilterOutputFlag(COMP_L | COMP_H);
}




/******************************************************************************
 * @brief      Set Filter Window Size and Threshold (nero second)
 *
 * @param[in]  eCOMP             : Select the comparator
 * @param[in]  u32SizeTimeNS     : Window Size (Time in ns)
 * @param[in]  u32ThresholdTimeNS: Threshold (Time in ns)
 *
 * @return     none
 *
 ******************************************************************************/
void COMP_SetFilterWindowTimeNs(COMP_ComparatorSelEnum eCOMP, uint32_t u32SizeTimeNS, uint32_t u32ThresholdTimeNS)
{
    uint32_t u32TimeCnt1, u32TimeCnt2;
    uint32_t u32FilterDiv;
    
    /* Use the max Filter Window Size(32U) to caculate minimum Filter Div */
    u32FilterDiv = CLOCK_GetModuleClock(COMP_MODULE) / 100000U * (u32SizeTimeNS) / (32U * 10000U);
    
    /* If minimum Filter Div if too small, increase the Filter Div to legal range, at this time, Filter Window Size is decreased */
    if (u32FilterDiv == 0U)
    {
        /* Use the minimum Filter Div to recaculate Filter Window Size, at this time, 0U <= Filter Window Size < 32U*/
        u32FilterDiv++;
        u32TimeCnt1 = (CLOCK_GetModuleClock(COMP_MODULE) / 100000U * (u32SizeTimeNS) /u32FilterDiv / 10000U);
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
        u32TimeCnt1 = (CLOCK_GetModuleClock(COMP_MODULE) / 100000U * (u32SizeTimeNS) /u32FilterDiv / 10000U);
        
        /* If minimum Filter Div can not set Filter Window Size <= 32U, use the (u32FilterDiv + 1) to recaculate Filter Window Size, 
        at this time, Filter Window Size is decreased */
        if (u32TimeCnt1 > 32U)
        {
            /* Use the minimum Filter Div to recaculate Filter Window Size, at this time, 0U <= Filter Window Size < 32U*/
            u32FilterDiv++;
            u32TimeCnt1 = (CLOCK_GetModuleClock(COMP_MODULE) / 100000U * (u32SizeTimeNS) /u32FilterDiv / 10000U);
        }
    }
    
    /* If Filter Window Size is decreased to 0, set to 1 */
    if (u32TimeCnt1 == 0U)
    {
        u32TimeCnt1 = 1U;
    }
    
    /* Caculate Filter Threshold */
    u32TimeCnt2 = CLOCK_GetModuleClock(COMP_MODULE) / 100000U * (u32ThresholdTimeNS) / u32FilterDiv / 10000U;
    
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
    COMP_SetFilterClockDiv(eCOMP, u32FilterDiv);

    COMP_SetFilterWindow(eCOMP, u32TimeCnt1, u32TimeCnt2);
}




/******************************************************************************
 * @brief      Init DAC Buffer
 *
 * @param[in]  eDACSel : Select the DAC module
 *                       Please refer to COMP_DACSelEnum
 *                       - \ref DAC0
 *                       - \ref DAC1
 *
 * @return     none
 *
 ******************************************************************************/
void COMP_DACBufferInit(COMP_DACSelEnum eDACSel)
{
    /* Select DAC Buffer Input */
    COMP_SetDACBufferInput(eDACSel);

    /* Enable DAC Buffer */
    COMP_EnableDACBuffer();

    /* Enable output to GPIO */
//  COMP_EnableDACBufferOutputToGPIO();
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
