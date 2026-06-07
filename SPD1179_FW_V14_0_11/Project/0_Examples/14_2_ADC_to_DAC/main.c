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


int32_t                        i32VSP;                                /* Result Value */


/*************************************************************************************************************************
 *
 * @brief      In this case, ADC input variable voltage, and output the ADC voltage to DAC, the DAC output is PIN_GPIO2
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

    /* enable DAC0 */
    COMP_EnableDAC(DAC0);

    /* Set DAC0 as Direct mode(DAC code is immediately update) */
    COMP_SetDACCodeLoadTiming(DAC0, DIRECT_LOAD_MODE);

    /* set DAC0 output to 0V */
    COMP_SetDACValue10Bit(DAC0, 0);

    /* DAC Buffer Init */
    COMP_DACBufferInit(DAC0);

    /* Enable DAC Buffer Output To GPIO */
    COMP_EnableDACBufferOutputToGPIO();

    /* Init ADC and set PIN_GPIO0 as the positive input of the ADC CH0 */
    ADC_EasyInit1(ADC, ADC_CH0, ADC_IN_GPIO0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);

    /* Enable the global INT for the ADC */
    NVIC_EnableIRQ(ADCCH0_IRQn);

    ADC_EnableChannelInt(ADC, ADC_CH0);

    /* Use software to trigger ADC CH0 to work */
    ADC_ForceChannelSOC(ADC, ADC_CH0);

    while (1)
    {

    }
}


void ADCCH0_IRQHandler(void)
{
    /* Result gotten from 'ADC_GetChannelResult()' can be a negative value or a positive value */
    i32VSP = ADC_GetChannelResult(ADC, ADC_CH0);

    printf("ADC data is %d\n", i32VSP);
    printf("ADC Voltage %dmv\n", ValueToVoltage(i32VSP));
    

    i32VSP = (uint32_t)(i32VSP * 1023 * 3.657 / (4095 * 3.3));

    /* Limit value to 0 (0V) ~ 1023 (3.3V) */
    if (i32VSP > 1023)
    {
        i32VSP = 1023;
    }

    if (i32VSP < 0)
    {
        i32VSP = 0;
    }

    printf("DAC input data is %d\n", i32VSP);

    /* Range from 0 (0V) ~ 1023 (3.3V) */
    COMP_SetDACValue10Bit(DAC0, i32VSP);

    /* Clear Channel Int Flag */
    ADC_ClearChannelInt(ADC, ADC_CH0);

    Delay_Ms(500);

    /* Use software to trigger ADC CH0 to work */
    ADC_ForceChannelSOC(ADC, ADC_CH0);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
