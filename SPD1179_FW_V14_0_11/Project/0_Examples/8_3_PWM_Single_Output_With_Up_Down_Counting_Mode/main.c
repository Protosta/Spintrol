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


/* This macro is used to get the PWM period with a specified frequency */
#define                PWM_Frequency                        20000                          /* 20kHz PWM */


uint32_t               u32PWMPeriod;


/*************************************************************************************************************************
 *
 * @brief      In this case, 20kHz waveform with 50% duty will be output through PWM1 A channel, bringing out by PWM up-down
 *             counting mode. We can measure this waveform with PIN_GPIO12.
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

    /* Init PWM1 and output 20kHz waveform on channel A */
    PWM_InitSingleChannel(PWM1, PWM_CHA, PWM_Frequency);

    /* Set PWM1A output 50% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM1);
    PWM_SetCMPA(PWM1, u32PWMPeriod / 2);

    /* Select PIN_GPIO12 as the channel A output of PWM1 */
    PIN_SetChannel(PIN_GPIO12, PIN_GPIO12_PWM1A);

    /* Start PWM1 */
    PWM_RunCounter(PWM1);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
