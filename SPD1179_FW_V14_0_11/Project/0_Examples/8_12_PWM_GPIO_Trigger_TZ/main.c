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
#define              PWM_FREQ                            20000                               /* 20kHz PWM */


uint32_t             u32PWMPeriod;


/*************************************************************************************************************************
 *
 * @brief      In this case, 40kHz waveform with 50% duty will be output through PWM1 B channel, bringing out by PWM up-down
 *             counting mode. we can measure this waveform with PIN_GPIO13 connected to a oscilloscope.
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

    /* Select PIN_GPIO13 as the channel B output of PWM1 */
    PIN_SetChannel(PIN_GPIO13, PIN_GPIO13_PWM1B);

    /* Init PWM1 and output 20kHz waveform on channel B */
    PWM_InitSingleChannel(PWM1, PWM_CHB, PWM_FREQ);

    /* Configure PWM counter as up counting mode */
    PWM_SetCounterMode(PWM1, COUNT_DOWN);

    /*
    * The PWM counting mode is set to be up-down by default, as a result, we need
    * to re-config the AQCTLA register, which is used for controlling the PWM output
    * action when ZRO/CAU/PRD/CAD (for more information, please read the PWM application
    * note) event had happened.
    *
    * Key Point: the PWM freq will be double because of the ZRO/CAU/PRD/CAD event.
    */
    PWM_ActionQualifierCHB(PWM1, AQCTLB_ZRO_SET_HIGH
                           | AQCTLB_CAU_DO_NOTHING
                           | AQCTLB_PRD_DO_NOTHING
                           | AQCTLB_CAD_SET_LOW);

    /* Set PWM1B output 50% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM1);
    PWM_SetCMPA(PWM1, u32PWMPeriod / 2);

    /* Start PWM1 */
    PWM_RunCounter(PWM1);
    
    /*
    * Trigger TZ0 event when PIN_GPIO6 is low
    */
    PWM_SetTZ0FromGPIO(PIN_GPIO6, GPIO_LEVEL_LOW);

    /*
    * De-glitch settings, if IO signal state can keep 128 PCLK cycles,
    * then it will will be assumed valid
    */
    PIN_SetDeglitchWindow(DGCLKCTL_PDIV_128);
    PIN_EnableDeglitch(PIN_GPIO6);

    /* Trigger TZ1 event when PIN_GPIO8 is low */
    PWM_SetTZ1FromGPIO(PIN_GPIO8, GPIO_LEVEL_LOW);

    /* Trigger TZ2 event when PIN_GPIO9 is low */
    PWM_SetTZ2FromGPIO(PIN_GPIO9, GPIO_LEVEL_LOW);

    /*
    * Set TZ0 as one-shot trip event. The one-shot mode means once the
    * corresponding event has happened, the PWM waveform will stop, and
    * will not start until the flag is cleared.
    *
    * The key point there is 'TZEVT_ASYNC_ONLY_FOR_DEBUG' can not be
    * set in practical engineering, it can only be used in DEBUG mode.
    */
    PWM_SetOneShotTripEvent(PWM1, TRIP_EVENT_TZ0, TRIP_OUTPUT_ASYNC_OR_LATCH);

    /*
    * Set TZ1 and TZ2 as CBC trip event. The symbol 'CBC' means once the
    * corresponding event has happened, the PWM waveform will stop, but
    * start again at the next PWM CLK period with do nothing manually.
    *
    * The key point there is the same as 'PWM_SetOneShotTripEvent()'
    */
    PWM_SetCBCTripEvent(PWM1, TRIP_EVENT_TZ1 | TRIP_EVENT_TZ2, TRIP_OUTPUT_ASYNC_OR_LATCH);

    /*
    * Set PWM1 output as tristate upon one-shot and CBC trip event,
    * need to explicitly specify actions for all 6 trip scenarios
    */
    PWM_SetCHAOutputWhenTrip(PWM1, TZU_TRIP_AS_TRI_STATE |
                             TZD_TRIP_AS_TRI_STATE |
                             DCEVT0U_TRIP_DO_NOTHING |
                             DCEVT0D_TRIP_DO_NOTHING |
                             DCEVT1U_TRIP_DO_NOTHING |
                             DCEVT1D_TRIP_DO_NOTHING);

    PWM_SetCHBOutputWhenTrip(PWM1, TZU_TRIP_AS_TRI_STATE |
                             TZD_TRIP_AS_TRI_STATE |
                             DCEVT0U_TRIP_DO_NOTHING |
                             DCEVT0D_TRIP_DO_NOTHING |
                             DCEVT1U_TRIP_DO_NOTHING |
                             DCEVT1D_TRIP_DO_NOTHING);

    NVIC_EnableIRQ(PWM1TZ_IRQn);

    PWM_EnableTripInt(PWM1, TRIP_INT_OST);
    PWM_EnableTripInt(PWM1, TRIP_INT_CBC);

    while (1)
    {
        Delay_Ms(500);
        
        /* Restore the output of wave in oneshot mode*/
        PWM_ClearTripInt(PWM1, TRIP_INT_OST);
    }
}

void PWM1TZ_IRQHandler(void)
{
    if (PWM_GetOneShotTripEventFlag(PWM1, TRIP_EVENT_TZ0))
    {
        printf("TZ0 one-shot trip event occurred\n");
        
        PWM_ClearOneShotTripEventFlag(PWM1, TRIP_EVENT_TZ0);
    }

    if (PWM_GetCBCTripEventFlag(PWM1, TRIP_EVENT_TZ1))
    {
        printf("TZ1 cycle-by-cycle trip event occurred\n");
        
        PWM_ClearCBCTripEventFlag(PWM1, TRIP_EVENT_TZ1);
    }
    
    if (PWM_GetCBCTripEventFlag(PWM1, TRIP_EVENT_TZ2))
    {
        printf("TZ2 cycle-by-cycle trip event occurred\n");
        
        PWM_ClearCBCTripEventFlag(PWM1, TRIP_EVENT_TZ2);
    }
    
    PWM_ClearTripInt(PWM1, TRIP_INT_CBC);

    PWM_ClearTripInt(PWM1, TRIP_INT_GLOBAL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
