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


#define              BAUDRATE              19200             /* LIN Rate */


uint8_t              u8Id                  = 0x31;           /* Send Id */
uint16_t             u16PREDRIID;                            /* PRE-DRIVER mode ID */
uint16_t             u16PREDRIDATA;                          /* Data read from PRE-DRIVER */
ErrorStatus          eErrorState;                            /* Function State */
uint8_t              i;                                      /* Print Num */
volatile uint8_t     u8Rxd[9];                               /* RX Data */
volatile uint8_t     state                 = 0;


/*************************************************************************************************************************
 *
 * @brief      In this case, the LIN master receive the data from slave.
 *
 *        Key_points:
 *                  (1)First start the slave code to wait the master code to send data.
 *                  (2)Reset the baud rate before each communication with slave
 *                  (3)Select the Master pull-up resistor based on the load capacitance,
 *                  observation point is between LIN and GND, when Load capacitance 10nF,
 *                  Pull-up resistor 500 ou; when Load capacitance 8nF, Pull-up resistor
 *                  660 ou; when Load capacitance 1nF, Pull-up resistor 1000 ou
 *
 *                                    observation point
 *
 *                                  *    *
 *                                 *    *
 *              *************     *    *      LIN     *************
 *              *           ***************************           *
 *              *  Master   *        *                *   Slave   *
 *              *           ***************************           *
 *              *************                 GND     *************
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

    /*
    Init LIN parameter
    when Baud rate 9600, LINCTL_TXSLOPE_19P0US
    when Baud rate 19200, LINCTL_TXSLOPE_7PUS
    */
    eErrorState = EPWR_WriteRegisterField(HV_REG_LINCTL, LINCTL_TXSLOPE_Msk | LINCTL_STRENGTH_Msk | LINCTL_TXEN_Msk | LINCTL_EN_Msk, LINCTL_TXSLOPE_7PUS | LINCTL_STRENGTH_47P2MA | LINCTL_TXEN_ENABLE | LINCTL_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("LINCTL_WriteRegisterField FAIL\n");
        return 0;
    }
    
    /* LIN_Init */
    PIN_SetChannel(PIN_GPIO25, PIN_GPIO25_UART1_TXD);
    PIN_SetChannel(PIN_GPIO26, PIN_GPIO26_UART1_RXD);
    LIN_Init(UART1, LIN_MASTER, BAUDRATE);
    UART_EnableTx(UART1);
    UART_EnableRx(UART1);

    UART_SetRxFIFOThreshold(UART1, LIN_RESPONSE_8_BYTE);

    /* Enable UART1_IRQn trigger INT in MCU side */
    NVIC_EnableIRQ(UART1_IRQn);

    /* Enable the RX time out INT */
    UART_EnableInt(UART1, UART_INT_RX_REQ | UART_INT_RX_TIMEOUT | UART_INT_RX_FRAME_ERROR | UART_INT_LIN_BIT_ERROR);

    while (1)
    {
        /* Init the state */
        state = 0;

        /* Set the respond mode */
        LIN_SetResponse(UART1, LIN_RESPONSE_RX);

        /* Set the respond lenth */
        LIN_SetResponseLen(UART1, LIN_RESPONSE_8_BYTE);

        /* Set the check mode */
        if (u8Id == 0x3C || u8Id == 0x3D)
        {
            LIN_SetCheckSumMode(UART1, LIN_CLASSIC_CHECKSUM);
        }
        else
        {
            LIN_SetCheckSumMode(UART1, LIN_ENHANCED_CHECKSUM);
        }

        /* Set the id, then the communication is start*/
        LIN_SetTxID(UART1, u8Id);
        UART_SetBreak(UART1);
        
        /* Wait until leave RX_REQ */
        while (state == 0)
        {
        }
        
        for (i = 0; i < LIN_RESPONSE_8_BYTE + 1; i++)
        {
            printf("u8Rxd[%d] is %x\n", i, u8Rxd[i]);
        }
        
        /* Wait slave */
        Delay_Ms(100);
    }
}


void UART1_IRQHandler(void)
{
    if (UART_GetIntFlag(UART1, UART_INT_RX_REQ) != 0)
    {
        for (i = 0; i < LIN_RESPONSE_8_BYTE + 1; i++)
        {
            u8Rxd[i] = UART_ReadByte(UART1);
        }
        
        state = 1;
        
        /* Clear the start signal flag */
        UART_ClearInt(UART1, UART_INT_RX_REQ);
    }
    /* GetRxTimeoutIntFlag */
    else if (UART_GetIntFlag(UART1, UART_INT_RX_TIMEOUT) != 0)
    {
        printf("LIN Rx Time out\n");
        UART_ClearInt(UART1, UART_INT_RX_TIMEOUT);
    }
    /* GetRxStopbitErrorIntFlag */
    else if (UART_GetIntFlag(UART1, UART_INT_RX_FRAME_ERROR) != 0)
    {
        printf("LIN Rx Stop bit error\n");
        UART_ClearInt(UART1, UART_INT_RX_FRAME_ERROR);
    }
    /* GetTxBitErrorIntFlag */
    else if (UART_GetIntFlag(UART1, UART_INT_LIN_BIT_ERROR) != 0)
    {
        printf("LIN Tx bit error\n");
        UART_ClearInt(UART1, UART_INT_LIN_BIT_ERROR);
    }
    UART_ClearInt(UART1, UART_INT_ALL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
