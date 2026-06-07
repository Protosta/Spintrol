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
#define                PWM_FREQ                              20000                                             /* 20kHz PWM */
#define                PWM_DB_NS                             1000                                              /* 1000ns */


uint32_t               u32PWMPeriod;


/*************************************************************************************************************************
 *
 * @brief      In this case, 20kHz waveform with 25% duty will be output through PWM1 A/B channel respectively, so the high
 *             level is 2.5e4ns=25us in one period(50us). but 1us delay will add to the rising edge of channel A and another
 *             1us to the fall edge of channel B with the sub-module dead band is working. As a result, the high level is
 *             (25-1=24)us (low level is 50-24=26us) in one period of channel A, and the channel B is the same as channel A,
 *             but a phase offset between channel A and B. There give a sketch map.
 *
 *                                                                |<---------- one period ---------> |
 *                                                          ->|1us|<-                                |
 *                                                            |                                      |
 *                                                            |    ---------                         |
 *                                                            |   |         |                        |
 *                                                            |   |         |                        |
 *                            PWM1A              -----------------           -----------------------------
 *                            PWM1B              -------------            ->|1us|<------------------------
 *                                                            |                 |                |
 *                                                            |                 |                |   |
 *                                                             -----------------               ->|1us|<-
 *                                                            |                                  |
 *                                                            |                                  |
 *                                                            |<----------- one period --------->|
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

    /*
    * 1. Init PWM1 and output 20kHz waveform on channel A
    *
    * 2. Add 1ns dead band at falling and rising edge
    *
    * 3. Channel B output the channel A waveform which added DB
    */
    PWM_InitComplementaryPairChannel(PWM1, PWM_FREQ, PWM_DB_NS);

    /* Set PWM0A output 75% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM1);
    PWM_SetCMPA(PWM1, u32PWMPeriod / 4);

    /* Select PIN_GPIO12/PIN_GPIO13 as the channel A/B output of PWM1 respectively */
    PIN_SetChannel(PIN_GPIO12, PIN_GPIO12_PWM1A);
    PIN_SetChannel(PIN_GPIO13, PIN_GPIO13_PWM1B);

    /* Start PWM1 */
    PWM_RunCounter(PWM1);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
