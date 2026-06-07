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
#include <stdlib.h>


/* This macro is used to get the PWM period with a specified frequency */
#define                PWM_U                              PWM0
#define                PWM_V                              PWM1
#define                PWM_W                              PWM2
#define                LINK_PWM_U                         SEL_PWM0
#define                PWM_FREQ                           10000                                   /* 10kHz PWM */
#define                PWM_DB_NS                          3000                                    /* 3us */
#define                BAUDRATE                           9600                                    /* LIN Rate */


uint32_t              u32PWMPeriod;                                                              /* PWM Period*/
uint16_t              u16PREDRIID;                                                               /* PRE-DRIVER mode ID */
uint16_t              u16PREDRIDATA                      = 0;                                    /* Data read from PRE-DRIVER */
ErrorStatus           eErrorState;                                                               /* Function State */
uint8_t               u8Id                              = 0x31;                                  /* Send Id */
uint8_t               u8Txd[8];                                                                  /* TX Data */
uint8_t               i;                                                                         /* TX Data */


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


void LIN_Test_Init(UART_REGS *UARTx, LIN_ModeEnum eMode, uint32_t u32BaudRate)
{
    uint32_t u32BaudCnt;

    /* Enable UART Clock */
    CLOCK_EnableModule(UART1_MODULE);

    /* Calculate UART clock divisor */
    u32BaudCnt = CLOCK_GetModuleClock(UART1_MODULE) / u32BaudRate;

    /* Configure the baud count register */
    UART_SetBaudCount(UARTx, u32BaudCnt);


    /* Configure UART control register (UARTCTL) */
    UARTx->UARTCTL = UARTCTL_RXEN_ENABLE             |
                     UARTCTL_TXEN_ENABLE             |
                     UARTCTL_RXDMAEN_DISABLE         |
                     UARTCTL_TXDMAEN_DISABLE         |
                     UARTCTL_LPBK_NORMAL_MODE        |
                     UARTCTL_BUS32_8BIT              |
                     UARTCTL_ABEN_DISABLE            |
                     UARTCTL_ABUP_UPDATE_BY_HW       |
                     UARTCTL_NRZMODE_NRZ_LEVEL       |
                     UARTCTL_DATABIT_8_DATA_BIT      |
                     UARTCTL_PRTYEN_PARITY_ENABLE    |
                     UARTCTL_STOPBIT_1_STOP_BIT;


    /* Configure LIN control register (LINCTL) */
    //  UARTx->LINCTL = LINCTL_LINEN_LIN_MODE         |
    //                  (eMode << LINCTL_MASTER_Pos)  |
    //                  LINCTL_SBRKLEN_13_BIT         |
    //                  LINCTL_SBRKDEL_1_BIT          |
    //                  LINCTL_RESP_RESPONSE_NONE     |
    //                  LINCTL_RESPLEN_X_BYTE         |
    //                  LINCTL_CHKSUM_ENHANCED_MODE;
}


/*************************************************************************************************************************
 *
 * @brief      This case show how to use LIN_TX_Timeout signal to trigger TZ.
 *
 *    Key_points:
 *              (1)Do not use this demo code to do the LIN communication, because in order to show the over-current
 *      phenomenon, we use the LIN_Test_Init to replace LIN_Init, otherwise the TXD can not be set low.
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
        printf("Init PRE-DRIVER mode FAIL\n");
        return 0;
    }
    else
    {
        printf("Init PRE-DRIVER mode SUCCESS[ID:%d]\n", u16PREDRIID);
    }

    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
        return 0;
    }

    /* Power up PRE-DRIVER mode */
    eErrorState = EPWR_WriteRegisterField(HV_REG_PDRVCTL0, PDRVCTL0_EN_Msk, PDRVCTL0_EN_ENABLE);
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

    /*
    Init LIN parameter
    LINCTL_TXSLOPE_19P0US, when Load capacitance 10nF, Pull-up resistor 500 ou
    LINCTL_TXSLOPE_7PUS,  when Load capacitance 1nF, Pull-up resistor 1000 ou
    */
    eErrorState = EPWR_WriteRegisterField(HV_REG_LINCTL, LINCTL_TXSLOPE_Msk | LINCTL_STRENGTH_Msk | LINCTL_TXEN_Msk | LINCTL_EN_Msk, LINCTL_TXSLOPE_19P0US | LINCTL_STRENGTH_47P2MA | LINCTL_TXEN_ENABLE | LINCTL_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegisterField FAIL\n");
        return 0;
    }

    /* Enable LIN_TX_Timeout interrupt */
    eErrorState = EPWR_WriteRegister(HV_REG_TZIE0, TZIE0_LINTXDTIMEOUT_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegister FAIL\n");
        return 0;
    }

    /* Enable TripEvent */
    EPWR_EnableTripEvent(EPWR_TRIP_EVENT_TZ0);

    /* Set the input signal of EPWRTZ0 event as high */
    EPWR_SetTripEventInputActiveHigh(EPWR_TRIP_EVENT_TZ0);

    /* To imitate the LIN_TX_Timeout signal, need to use LIN_Test_Init instead of LIN_Init, otherwise the TXD can not be set low*/
    PIN_SetChannel(PIN_GPIO25, PIN_GPIO25_UART1_TXD);
    PIN_SetChannel(PIN_GPIO26, PIN_GPIO26_UART1_RXD);
    LIN_Test_Init(UART1, LIN_MASTER, BAUDRATE);

    Delay_Ms(1000);
    printf("Generate TZ_Event\n");

    while (1)
    {
        /* Set the TXD low */
        UART1->UARTCTL = UART1->UARTCTL | UARTCTL_SETBRK_SET_BREAK;
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
