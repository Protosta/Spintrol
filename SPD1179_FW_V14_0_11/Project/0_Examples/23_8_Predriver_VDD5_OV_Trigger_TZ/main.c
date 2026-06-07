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
#include "spd1179.h"
#include <stdio.h>


/* This macro is used to get the PWM period with a specified frequency */
#define                PWM_U                              PWM0
#define                PWM_V                              PWM1
#define                PWM_W                              PWM2
#define                LINK_PWM_U                         SEL_PWM0
#define                PWM_FREQ                           10000                                   /* 10kHz PWM */
#define                PWM_DB_NS                          3000                                    /* 3us */


uint32_t              u32PWMPeriod;                                                              /* PWM Period*/
uint16_t              u16PREDRIID;                                                               /* PRE-DRIVER mode ID */
uint16_t              u16PREDRIDATA                      = 0;                                    /* Data read from PRE-DRIVER */
ErrorStatus           eErrorState;                                                               /* Function State */


void PWMx_Set_TZ_Event(PWM_REGS *PWMx)
{
    /* Affected by results monitored from all three phases */
    PWM_EnableDCAHTripEvent(PWMx, DC_TRIP_EPWRTZ0);

    /*DCAEVT0 event comes from DCAL=don't care, DCAH=high*/
    PWM_SetRawDCAEVT0(PWMx, DCH_HIGH_DCL_X);

    /* Set the DCAEVT0 as OneShot mode */
    PWM_SetOneShotTripEvent(PWMx, TRIP_EVENT_DCAEVT, TRIP_OUTPUT_LATCH);

    /* Set output to tri-state upon DCAEVT0 trip event */
    PWM_SetCHAOutputWhenTrip(PWMx, TZU_TRIP_AS_LOW |
                             TZD_TRIP_AS_LOW |
                             DCEVT0U_TRIP_AS_LOW |
                             DCEVT0D_TRIP_AS_LOW |
                             DCEVT1U_TRIP_AS_LOW |
                             DCEVT1D_TRIP_AS_LOW);

    PWM_SetCHBOutputWhenTrip(PWMx, TZU_TRIP_AS_LOW |
                             TZD_TRIP_AS_LOW |
                             DCEVT0U_TRIP_AS_LOW |
                             DCEVT0D_TRIP_AS_LOW |
                             DCEVT1U_TRIP_AS_LOW |
                             DCEVT1D_TRIP_AS_LOW);
}


/*************************************************************************************************************************
 *
 * @brief      This case show how to use VDD5 over-voltage signal to trigger TZ.
 *
 *
 *************************************************************************************************************************/


int main(void)
{
    uint32_t u32Timeout;
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

    /* HV reset */
    eErrorState = HV_Reset();
    if (eErrorState == ERROR)
    {
        printf("HV_Reset FAIL\n");
        return 0;
    }
    else
    {
        printf("HV_Reset SUCCESS\n");
    }

    /* HV init */
    eErrorState = HV_Init(&u16PREDRIID);
    if (eErrorState == ERROR)
    {
        printf("Init HV mode FAIL\n");
        return 0;
    }
    else
    {
        printf("Init HV mode SUCCESS[ID:%d]\n", u16PREDRIID);
    }

    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
        return 0;
    }

    /* Power up PRE-DRIVER mode */
    eErrorState = EPWR_WriteRegisterField(HV_REG_PDRVCTL0, PDRVCTL0_EN_Msk,  PDRVCTL0_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("Power up PRE-DRIVER FAIL\n");
        return 0;
    }

    /* Wait for PRE-DRIVER mode become enable */
    for(u32Timeout = 0xFFFFFFFF; u32Timeout > 0x00000000; u32Timeout--)
    {
        if ((u16PREDRIDATA & PMUSTS_CPRDY_READY) != 0)
        {
            break;
        }

        Delay_Ms(10);

        eErrorState = EPWR_ReadRegister(HV_REG_PMUSTS, &u16PREDRIDATA);
        if (eErrorState == ERROR)
        {
            printf("Read Register FAIL[%02x]\n", u16PREDRIDATA);
            return 0;
        }
    }
    if (u32Timeout == 0)
    {
        printf("Enable PRE-DRIVER error\n");
        return 0;
    }

    /* Set the VDD5 over-voltage threshold */
    eErrorState = EPWR_WriteRegisterField(HV_REG_EVTTHCTL0, EVTTHCTL0_VDD5OV_Msk, EVTTHCTL0_VDD5OV_5P68V );
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegisterField FAIL\n");
        return 0;
    }

    /* Enable VDD5 over-voltage interrupt */
    eErrorState = EPWR_WriteRegister(HV_REG_TZIE0, TZIE0_VDD5OV_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegister FAIL\n");
        return 0;
    }

    /* Enable TripEvent */
    EPWR_EnableTripEvent(EPWR_TRIP_EVENT_TZ0);

    /* Set the input signal of EPWRTZ0 event as high */
    EPWR_SetTripEventInputActiveHigh(EPWR_TRIP_EVENT_TZ0);

    /*
    * Init PWM0/PWM1/PWM2 and output 20kHz waveform on both channel A and channel B.
    */
    PWM_InitComplementaryPairChannel(PWM_U, PWM_FREQ, PWM_DB_NS);
    PWM_InitComplementaryPairChannel(PWM_V, PWM_FREQ, PWM_DB_NS);
    PWM_InitComplementaryPairChannel(PWM_W, PWM_FREQ, PWM_DB_NS);

    PWMx_Set_TZ_Event(PWM_U);

    PWMx_Set_TZ_Event(PWM_V);

    PWMx_Set_TZ_Event(PWM_W);


    /* PWM0 set CMPA and loading the same value to PWM1/2 synchronously */
    PWM_LinkCMPA(PWM_V, LINK_PWM_U);
    PWM_LinkCMPA(PWM_W, LINK_PWM_U);

    /* Set the duty as 75% */
    u32PWMPeriod = PWM_GetShadowPRD(PWM_U);
    PWM_SetCMPA(PWM_U, u32PWMPeriod / 4);

    /* Start counting */
    PWM_RunCounter(PWM_U);
    PWM_RunCounter(PWM_V);
    PWM_RunCounter(PWM_W);

    while (1)
    {
        Delay_Ms(2000);

        /* Restore the output of three phase wave */
        PWM_ClearTripInt(PWM0, TRIP_INT_OST);
        PWM_ClearTripInt(PWM1, TRIP_INT_OST);
        PWM_ClearTripInt(PWM2, TRIP_INT_OST);
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
