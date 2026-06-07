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
/* Timer INT period, unit:ms */
#define               TIMEPERIOD                    1000


int32_t               i32VSP;


/*************************************************************************************************************************
 *
 * @brief      This case show how to use timer to trigger ADC.
 *
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

    /* ADC Init, ADC0 is the positive input pin, negative pin is GND*/
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_TIMER1);

    /* Enable ADC */
    ADC_Enable(ADC);

    /* Enable ADC0_IRQn */
    NVIC_EnableIRQ(ADCCH0_IRQn);

    /* Enable SOC interrupt */
    ADC_EnableChannelInt(ADC, ADC_CH0);

    /* Init TIMER1 to count for 1000ms */
    TIMER_Init(TIMER1, TIMEPERIOD);

    /* Enable TIMER1 to generate a signal to trigger ADC SOC to work */
    TIMER_EnableADCSOC(TIMER1);

    /* Enable Timer */
    TIMER_Enable(TIMER1);

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


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
