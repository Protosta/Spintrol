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
#include<math.h>



#define               PWM_FREQ                20000                              /* 20kHz PWM */
#define               PWM_DB_NS               1000                               /* 1000ns */
#define               PWM_BlankWIN_Size       100                                /* 100 TBCNT CLK */
#define               PWM_Blank_Offset        50                                 /* 50 TBCNT CLK */
#define               COMP_FilterWIN          300                                /* 300ns */
#define               SampleRgisterNVol       1500                               /* Sampler register negative voltage : 1500mV */
#define               VolOffsetmV             500                                /* COMP monitor voltage range offset 500mV*/


uint32_t u32PWMPeriod;


void PWMx_Set_TZ_Event(PWM_REGS *PWMx)
{
    /* Affected by results monitored from COMP0 */
    PWM_EnableDCAHTripEvent(PWMx, DC_TRIP_COMP0H);
    PWM_EnableDCAHTripEvent(PWMx, DC_TRIP_COMP0L);

    /*DCAEVT0 event comes from DCAL=don't care, DCAH=high*/
    PWM_SetRawDCAEVT0(PWMx, DCH_HIGH_DCL_X);

    /* Set the filter, Filter trigger conditions is TBCNT=0*/
    PWM_SetDCFilter(PWMx, DCF_FROM_RAW_DCAEVT0, DCF_ALIGN_ON_ZERO);

    /* Enable PWM DC filter blank function */
    PWM_EnableDCFilterBlank(PWMx);

    /* Set blank window size as 100 TBCLK and offset as 50 TBCLK */
    PWM_SetDCFilterBlankWindow(PWMx, PWM_BlankWIN_Size, PWM_Blank_Offset);

    /* USe the filtered to deal the data from DCAEVT0 */
    PWM_SetDCAEVT0(PWMx, DCEVT_FILTERED);
    
    /* Set the DCAEVT0 as OneShot mode */
    PWM_SetOneShotTripEvent(PWMx, TRIP_EVENT_DCAEVT, TRIP_OUTPUT_LATCH);

    /* Set output to tri-state upon OST trip event */
    PWM_SetCHAOutputWhenTrip(PWMx, TZU_TRIP_AS_LOW |
                             TZD_TRIP_AS_LOW |
                             DCEVT0U_TRIP_DO_NOTHING |
                             DCEVT0D_TRIP_DO_NOTHING |
                             DCEVT1U_TRIP_DO_NOTHING |
                             DCEVT1D_TRIP_DO_NOTHING);

    PWM_SetCHBOutputWhenTrip(PWMx, TZU_TRIP_AS_LOW |
                             TZD_TRIP_AS_LOW |
                             DCEVT0U_TRIP_DO_NOTHING |
                             DCEVT0D_TRIP_DO_NOTHING |
                             DCEVT1U_TRIP_DO_NOTHING |
                             DCEVT1D_TRIP_DO_NOTHING);

    PWM_EnableTripInt(PWMx, TRIP_INT_OST);
}


/*************************************************************************************************************************
 *
 * @brief      In this case, The aim is to protect the waveform from over/below current, but current is hard to
 *             test, so we test the current sampling register instead.
 *
 *             Key point:
 *                       When selecting the GAIN value of PGA, In order to prevent the output tube from being saturated,
 *                      it is necessary to ensure that the output range is between 0.3V and AVDD - 0.3V
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
    /*
    * set the GPIO as ADC.
    */
    PIN_SetChannel(PIN_GPIO0, PIN_GPIO0_ANA_IN0);

    /*
    * Set PGA in  single-ended mode.
    *
    */
    PGA_InitSPGA(SPGA_FROM_ANA_IN0, SPGA_GAIN_1X);

    /* Enable PGA */
    PGA_EnableSPGA();

    /*
     * 1. Initialize comparator with 300ns deglitch filtering window.
     * 2. Set DAC voltage, COMP_HI's negative port is 2000mV, COMP_LO's positive port is 1000mV
     */
    COMP_Init(COMP_H, COMP_FROM_SPGA_OUT, SampleRgisterNVol + VolOffsetmV, COMP_FilterWIN);
    COMP_Init(COMP_L, COMP_FROM_SPGA_OUT, SampleRgisterNVol - VolOffsetmV, COMP_FilterWIN);

    /* Enable comparator */
    COMP_Enable(COMP_H);
    COMP_Enable(COMP_L);

    /* Select the channel A/B output of PWM1 respectively */
    PIN_SetChannel(PIN_GPIO12, PIN_GPIO12_PWM1A);
    PIN_SetChannel(PIN_GPIO13, PIN_GPIO13_PWM1B);

    PWM_InitComplementaryPairChannel(PWM1, PWM_FREQ, PWM_DB_NS);

    /* Set PWM1A output 25% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM1);
    PWM_SetCMPA(PWM1, (u32PWMPeriod * 3) / 4);

    /* Start counting */
    PWM_RunCounter(PWM1);

    NVIC_EnableIRQ(PWM1TZ_IRQn);
    
    /* Set the DC sub-module for PWM1 */
    PWMx_Set_TZ_Event(PWM1);

    while (1)
    {
        Delay_Ms(1000);

        /* Restore the output of wave in oneshot mode*/
        PWM_ClearTripInt(PWM1, TRIP_INT_OST);
    }
}

void PWM1TZ_IRQHandler(void)
{
    if (PWM_GetOneShotTripEventFlag(PWM1, TRIP_EVENT_DCAEVT))
    {
        printf("one-shot trip event occurred\n");
        
        PWM_ClearOneShotTripEventFlag(PWM1, TRIP_EVENT_DCAEVT);
    }
    PWM_ClearTripInt(PWM1, TRIP_INT_GLOBAL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
