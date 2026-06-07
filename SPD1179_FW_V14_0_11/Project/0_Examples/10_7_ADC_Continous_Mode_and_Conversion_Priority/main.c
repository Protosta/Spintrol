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
#define               SAMPLETIMENS                 400
#define               CONVTIMENS                   400
//#define                SOC0_first_PRIORITY


int32_t               i32VSP;


/*************************************************************************************************************************
 *
 * @brief      This case show the convert priority of ADC.
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
    ADC_EasyInit1(ADC, ADC_CH1, PIN_GPIO1, ADC_SOC_TRIGGER_FROM_SOFTWARE);
    ADC_EasyInit1(ADC, ADC_CH2, PIN_GPIO2, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);

#ifdef SOC0_first_PRIORITY
    /* now the SOC0 are high priority, SOC1-SOC15 is in round mode , if the value is ADCSOCPRICTL_PRIORITY_CUTOFF_AT_SOC3,
    SOC0-SOC2 are high priority, SOC3-SOC15 is in round mode...*/
    ADC_SetSOCPriority(ADC, ADCSOCPRICTL_PRIORITY_CUTOFF_AT_SOC1);
#endif

    ADC_SetSampleAndConvertTime(ADC, ADC_CH0, SAMPLETIMENS, CONVTIMENS);
    ADC_SetSampleAndConvertTime(ADC, ADC_CH1, SAMPLETIMENS, CONVTIMENS);
    ADC_SetSampleAndConvertTime(ADC, ADC_CH2, SAMPLETIMENS, CONVTIMENS);

    /* Enable SOC1/2 can be triggered by signal come from ADC EOC(end of convert) INT */
    ADC_EnableChannelIntTriggerSOC(ADC, ADC_CH0);
    ADC_EnableChannelIntTriggerSOC(ADC, ADC_CH2);

    /* Set the trigger source of SOC1/2 as the EOC of SOC0 */
    ADC_SetChannelIntTriggerSOC(ADC, ADC_CH0, ADC_CH1);
    ADC_SetChannelIntTriggerSOC(ADC, ADC_CH2, ADC_CH1);

    /* Enable G-INT for SOC0/1/2 */
    NVIC_EnableIRQ(ADCCH0_IRQn);
    NVIC_EnableIRQ(ADCCH1_IRQn);
    NVIC_EnableIRQ(ADCCH2_IRQn);

    /* Enable SOC interrupt */
    ADC_EnableChannelInt(ADC, ADC_CH0);
    ADC_EnableChannelInt(ADC, ADC_CH1);
    ADC_EnableChannelInt(ADC, ADC_CH2);
    
    /* Enable ADC PPU     */
    ADC_EnablePPU(ADC, ADC_PPU0);
    ADC_EnablePPU(ADC, ADC_PPU1);

    /* Select CH result as post-processing data */
    ADC_SetPPUInput(ADC, ADC_PPU0, ADC_CH0, ADC_CH0, ADCRESULT_MINUS_REFERENCE);
    ADC_SetPPUInput(ADC, ADC_PPU1, ADC_CH2, ADC_CH2, ADCRESULT_MINUS_REFERENCE);

    /* Use software to trigger SOC1 to work */
    ADC_ForceChannelSOC(ADC, ADC_CH1);

    Delay_Ms(100);
    printf("PPU[%d] delay is %d\n", ADC_PPU0, ADC_GetPPUTriggerDelay(ADC, ADC_PPU0));
    printf("PPU[%d] delay is %d\n", ADC_PPU1, ADC_GetPPUTriggerDelay(ADC, ADC_PPU1));
    while (1)
    {

    }
}


void ADCCH0_IRQHandler(void)
{
    /* Result gotten from 'ADC_GetResult()' can be a negative value or a positive value */
    i32VSP = ADC_GetChannelResult(ADC, ADC_CH0);

    printf("ADC CH0 data is %d\n", i32VSP);
    printf("ADC CH0 Voltage %dmv\n", ValueToVoltage(i32VSP));

    /* Clear SOC INT */
    ADC_ClearChannelInt(ADC, ADC_CH0);
}


void ADCCH1_IRQHandler(void)
{
    /* Result gotten from 'ADC_GetResult()' can be a negative value or a positive value */
    i32VSP = ADC_GetChannelResult(ADC, ADC_CH1);
    /* Don't do any time consumption operation in this operation(like printf). otherwise, although the ADC sampling operation is right,
    the print sequence may seems wrong*/

    /* Clear SOC INT */
    ADC_ClearChannelInt(ADC, ADC_CH1);
}


void ADCCH2_IRQHandler(void)
{
    /* Result gotten from 'ADC_GetResult()' can be a negative value or a positive value */
    i32VSP = ADC_GetChannelResult(ADC, ADC_CH2);

    printf("ADC CH2 data is %d\n", i32VSP);
    printf("ADC CH2 Voltage %dmv\n", ValueToVoltage(i32VSP));

    /* Clear soc1 INT */
    ADC_ClearChannelInt(ADC, ADC_CH2);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
