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


int32_t             i32VSP;


/*************************************************************************************************************************
 *
 * @brief      In this case, we use two PIN_GPIO0 as the input of the ADC, then getting result from the register.
 *             Code            Real Voltage in ADC view
 *            -4096            -3.65 V
 *                0            0 V
 *             4095            3.65 V
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

    /*ADC Init*/
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);
    
    ADC_EnableChannelInt(ADC, ADC_CH0);

    /* Set Average Times */
    ADC_SetChannelResultAverageCount(ADC, ADC_CH0, ADC_AVERAGE_COUNT_32);

    while (1)
    {
        /* Use software to trigger ADC SOC0 start to work */
        ADC_ForceChannelSOC(ADC, ADC_CH0);

        /* Wait until ADC conversion finished (Interrupt flag was set) */
        while (ADC_GetChannelIntFlag(ADC, ADC_CH0) == 0);


        /* Get result */
        i32VSP = ADC_GetChannelResult(ADC, ADC_CH0);

        /* Clear ADC SOC0 INT flag */
        ADC_ClearChannelInt(ADC, ADC_CH0);

        printf("ADC Single End Result = %d\n", i32VSP);
        printf("ADC Single End Voltage %dmv\n", ValueToVoltage(i32VSP));

        Delay_Ms(500);
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
