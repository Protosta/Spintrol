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


int32_t            i32lresult;
int32_t            i32hresult;


/*************************************************************************************************************************
 *
 * @brief      This test case describes how to detect disconnection status of ADC input PIN, PIN_GPIO0 used as the Input PIN
 *             Test Point in this demo.
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
 *             For disconnection:
 *                (1)Turn off two switch, pull down both Test PIN, so that, the two Test PIN will be zero voltage.
 *                (2)Then, turn on two switch, and measure Input PIN Test PIN voltage value.
 *                (3)Turn off two switch, pull up both Test PIN, so that, the two Test PIN will be 3.3V.
 *                (4)Turn on two switch and measure Input PIN Test PIN voltage value.
 *             If measured value is zero when discharging and 3.3V when charging, it means the Input PIN is disconnecting(floating).
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

    /* Force the ADC positive PIN(ADC test point) tied to low to discharge */
    ADC_ForceSHPositiveInput(ADC, ADC_CH0, ADC_SH_FORCE_GND);

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
    i32lresult = ADC_GetChannelResult(ADC, ADC_CH0);
    printf("The voltage is %d\n", i32lresult);

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

    /* Force the ADC positive PIN tied high to charge */
    ADC_ForceSHPositiveInput(ADC, ADC_CH0, ADC_SH_FORCE_VDD33);

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
    i32hresult = ADC_GetChannelResult(ADC, ADC_CH0);
    printf("The voltage is %d\n", i32hresult);

    /* Check the result */
    if (ABS(i32lresult) < 200 && ABS(i32hresult) > 3200)
    {
        printf("PIN_GPIO0 is disconnected\n");
    }
    else
    {
        printf("PIN_GPIO0 is connected\n");
    }

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
