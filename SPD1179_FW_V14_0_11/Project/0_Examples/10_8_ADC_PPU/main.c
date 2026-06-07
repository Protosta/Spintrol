/******************************************************************************
 * @file     main.c
 * @brief    Main program body
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
#include <stdio.h>

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif


/*As described below, ADC result convert to voltage can calculate as the follow*/
#define               ValueToVoltage(x)            ((x * 3657) / 4096)


int32_t             i32Result;


void ADC_PPU_Init(ADC_PostProcessUnitEnum ePPU, ADC_ChannelEnum u8DataSel, int32_t i32Ref, ADC_PPU_DataProcessEnum ePol)
{
    /* Enable PPU and Select ADC result */
    ADC->PPUCTL[ePPU] = ADC->PPUCTL[ePPU] | PPUCTL_EN_ENABLE;

    ADC->PPUCTL[ePPU] = ADC->PPUCTL[ePPU] & (~(PPUCTL_DATASEL_Msk | PPUCTL_POL_Msk));

    /* Polarity for comparision */
    ADC->PPUCTL[ePPU] = ADC->PPUCTL[ePPU] | (u8DataSel << PPUCTL_DATASEL_Pos) | (ePol << PPUCTL_POL_Pos);

    /* Set Reference */
    ADC->PPUREF[ePPU] = i32Ref;
}


/*************************************************************************************************************************
 *
 * @brief      In this test case, we use PPU to judge ADC voltage.
 *
 *************************************************************************************************************************/


int main(void)
{
    CLOCK_InitWithRCO(100000000);

    Delay_Init();

    /*
     * Init the UART
     */
    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    printf("Enter the test\n");

    /* ADC Init */
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);

    /* Init ADC PPU */
    ADC_PPU_Init(ADC_PPU0, ADC_CH0, 100, ADCRESULT_MINUS_REFERENCE);

    /* Set PPU0 high threshold is 1500 */
    ADC_SetPPUHighThreshold(ADC, ADC_PPU0, 1500);

    /* Set PPU0 low threshold is 1000 */
    ADC_SetPPULowThreshold(ADC, ADC_PPU0, 1000);

    /* Clear CH0 INT flag */
    ADC_ClearChannelInt(ADC, ADC_CH0);

    /* Clear PPU Unit INT */
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_GLOBAL);
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_CROSS_ZERO);
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_TOO_HIGH);
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_TOO_LOW);

    NVIC_EnableIRQ(ADCPPU0_IRQn);

    /* Enable zero-crossing interrupt of ADC PPU0 */
    ADC_EnablePPUInt(ADC, ADC_PPU0, ADC_PPU_INT_CROSS_ZERO);

    /* Enable too high interrupt of ADC PPU0 */
    ADC_EnablePPUInt(ADC, ADC_PPU0, ADC_PPU_INT_TOO_HIGH);

    /* Enable too low interrupt of ADC PPU0 */
    ADC_EnablePPUInt(ADC, ADC_PPU0, ADC_PPU_INT_TOO_LOW);

    while (1)
    {
        /* Continues to use software to trigger the ADC to work */
        ADC_ForceChannelSOC(ADC, ADC_CH0);

        Delay_Ms(100);
    }
}


void ADCPPU0_IRQHandler(void)
{
    if (ADC_GetPPUIntFlag(ADC, ADC_PPU0, ADC_PPU_INT_CROSS_ZERO) != 0)
    {
        printf("Zero-cross INT had happened\n");
    }

    if (ADC_GetPPUIntFlag(ADC, ADC_PPU0, ADC_PPU_INT_TOO_HIGH) != 0)
    {
        printf("ADC channel voltage too-high INT had happened\n");
    }

    if (ADC_GetPPUIntFlag(ADC, ADC_PPU0, ADC_PPU_INT_TOO_LOW) != 0)
    {
        printf("ADC channel voltage too-low INT had happened\n");
    }

    /* Result gotten from 'ADC_GetChannelResult()' can be a negative value or a positive value */
    i32Result = ADC_GetChannelResult(ADC, ADC_CH0);
    printf("ADC CH0 data is %d\n", i32Result);
    printf("ADC CH0 Voltage %dmv\n", ValueToVoltage(i32Result));

    /* Clear the PPU0 INTs and global INT of PPU0 */
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_CROSS_ZERO);
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_TOO_HIGH);
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_TOO_LOW);
    ADC_ClearPPUInt(ADC, ADC_PPU0, ADC_PPU_INT_GLOBAL);

    ADC_ClearChannelInt(ADC, ADC_CH0);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
