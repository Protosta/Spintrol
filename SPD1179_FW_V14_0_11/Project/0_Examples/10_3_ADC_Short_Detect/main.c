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


int32_t             VALUE1, VALUE2, VALUE3;


/*************************************************************************************************************************
 *
 * @brief      This test case describes how to detect short status of ADC input PIN, PIN_GPIO0 used as the Input PIN Test Point
 *             in this demo.
 *
 *                                  Input PIN                Test Point at
 *                                  Test Point                 ADC Input
 *                 -----              -----                    -----                    -----------
 *                |Input|            |     |        /         |test |        /         |    ADC    |
 *                | PIN |------------| PAD |-------��  -------|point|-------��  -------| Controller|
 *                 -----              -----        On/Off      -----       On/Off       -----------
 *                                     / \          / \          / \         / \
 *                                      |            |            |           |
 *                                      |             ------------|------------------------------------The two On/Off switch
 *                                      |                         |                                    are controlled
 *                                       ---------------------------------The two test point will      simultaneously by one
 *                                                           be charged and discharged separately       control bit(SHEN bit)
 *
 *
 *             For Short:
 *                (1)Turn On two switch, Measure Input PIN Test PIN voltage value and save as VALUE1.
 *                (2)Force Input PIN Test Point tie to GND and then measure the voltage value and save as VALUE2.
 *                (3)Force Input PIN Test Point tie to AVDD and then measure the voltage value and save as VALUE3.
 *             If VALUE1 = VALUE2 = VALUE3, it means Input PIN is short.
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

    printf("======= Bgin to try to tied the ADC0 low and then sample the voltage ======\n");

    /*
    * ADC Init, config the PIN_GPIO0 as the positive channel and the negative is GND.
    * Turn On two switch.
    */
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);

    ADC_EnableChannelInt(ADC, ADC_CH0);

    /* Use software to trigger ADC SOC0 to work */
    ADC_ForceChannelSOC(ADC, ADC_CH0);

    /* Wait until ADC conversion finished (Interrupt flag is set) */
    while (ADC_GetChannelIntFlag(ADC, ADC_CH0) == 0)
    {
    }

    /* Get the result */
    VALUE1 = ADC_GetChannelResult(ADC, ADC_CH0);
    printf("The voltage is %d\n", VALUE1);

    /* Turn off the two switch */
    ADC_SetChannelSH(ADC, ADC_CH0, ADC_SH_SEL_NONE);

    /* Set PIN_GPIO0 as GPIO mode */
    PIN_SetChannel(PIN_GPIO0, PIN_GPIO0_GPIO0);

    /*
    * Set the PIN_GPIO0 as pull down model to discharge, keep in mind that the pull up and pull down
    * is not exclusive.
    */
    PIN_DisablePullUp(PIN_GPIO0, PIN_GPIO0_GPIO0);
    PIN_EnablePullDown(PIN_GPIO0, PIN_GPIO0_GPIO0);

    /* Delay for a short time to let the discharge over */
    Delay_Ms(100);

    /*
    * ADC Init, config the PIN_GPIO0 as the positive channel and the negative is GND.
    * Then On two switch.
    */
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);

    ADC_EnableChannelInt(ADC, ADC_CH0);

    /* Use software to trigger ADC SOC0 to work */
    ADC_ForceChannelSOC(ADC, ADC_CH0);

    /* Wait until ADC conversion finished (Interrupt flag is set) */
    while (ADC_GetChannelIntFlag(ADC, ADC_CH0) == 0)
    {
    }

    /* Get the result */
    VALUE2 = ADC_GetChannelResult(ADC, ADC_CH0);
    printf("The voltage is %d\n", VALUE2);

    /* Turn off the two switch */
    ADC_SetChannelSH(ADC, ADC_CH0, ADC_SH_SEL_NONE);

    /*
    * Last 'ADC_EasyInit1()', PIN_GPIO0 was set as analog ADC mode, but pull up and down function
    * is only valid in GPIO mode.
    */
    PIN_SetChannel(PIN_GPIO0, PIN_GPIO0_GPIO0);

    /*
    * Set the PIN_GPIO0 as pull up model to precharge, keep in mind that the pull up and pull down
    * is not exclusive.
    */
    PIN_EnablePullUp(PIN_GPIO0, PIN_GPIO0_GPIO0);
    PIN_DisablePullDown(PIN_GPIO0, PIN_GPIO0_GPIO0);

    /* Delay for a short time to let the precharge over */
    Delay_Ms(100);

    /*
    * ADC Init, config the PIN_GPIO0 as the positive channel and the negative is GND.
    * Then On two switch.
    */
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);

    ADC_EnableChannelInt(ADC, ADC_CH0);

    /* Use software to trigger ADC SOC0 to work */
    ADC_ForceChannelSOC(ADC, ADC_CH0);

    /* Wait until ADC conversion finished (Interrupt flag is set) */
    while (ADC_GetChannelIntFlag(ADC, ADC_CH0) == 0)
    {
    }

    /* Get the ADC SOC result */
    VALUE3 = ADC_GetChannelResult(ADC, ADC_CH0);
    printf("The voltage is %d\n", VALUE3);

    /* Check the result */
    if ((ABS(VALUE1 - VALUE2) < 200) && (ABS(VALUE1 - VALUE3) < 200))
    {
        printf("PIN_GPIO0 is short\n");
    }
    else
    {
        printf("PIN_GPIO0 is not short\n");
    }

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
