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


#define              BAUDRATE              19200             /* LIN Rate */
#define              REFID                 0x01              /* REFID State */
#define              IDMASK                0x01              /* IDMASK State */
uint8_t              u8Id;                                   /* Receive Id */
uint8_t              u8Txd[8];                               /* TX Data */
uint8_t              i;
uint16_t             u16PREDRIID;                            /* PRE-DRIVER mode ID */
ErrorStatus          eErrorState;                            /* Function State */


/*************************************************************************************************************************
 *
 * @brief      In this case, the LIN slave send the data to master.
 *
 *        Key_points:
 *                  (1)First start the slave code to wait the master code to send data.
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
    
    /* Enable and Get Timer module clock */
    CLOCK_EnableModule(TIMER1_MODULE);

    /* Set Timer mode */
    TIMER_SetMode(TIMER1, TIMER_GENERAL_TIMER);

    /* Set reload Timer while Timer reaches 0 */
    TIMER_SetReloadValue(TIMER1, CLOCK_UsToCounter(((80 + 20) * 1000000 / BAUDRATE ), CLOCK_GetModuleClock(TIMER1_MODULE)));
    
    /* Open Global INT for Timer */
    NVIC_EnableIRQ(TIMER1_IRQn);

    /* Enable Timer interrupt */
    TIMER_EnableInt(TIMER1);
    
    /* LIN_Init */
    PIN_SetChannel(PIN_GPIO25, PIN_GPIO25_UART1_TXD);
    PIN_SetChannel(PIN_GPIO26, PIN_GPIO26_UART1_RXD);
    LIN_Init(UART1, LIN_SLAVE, BAUDRATE);
    UART_EnableTx(UART1);
    UART_EnableRx(UART1);

    /* Set the id filter */
    LIN_SetIDFilter(UART1, REFID, IDMASK);

    /* Enable UART1_IRQn trigger INT in MCU side */
    NVIC_EnableIRQ(UART1_IRQn);

    /* Enable the RX time out INT */
    UART_EnableInt(UART1, UART_INT_LIN_ID_MATCH | UART_INT_RX_TIMEOUT | UART_INT_RX_FRAME_ERROR | UART_INT_LIN_BIT_ERROR | UART_INT_AUTOBAUD_LOCK);
    
    while (1)
    {
    }
}


void UART1_IRQHandler(void)
{
    if (UART_GetIntFlag(UART1, UART_INT_LIN_ID_MATCH) != 0)
    {
        /* Get the id */
        u8Id = LIN_GetRxID(UART1);

        u8Id = u8Id & 0x3F;
        
        /* Set the check mode */
        LIN_SetCheckSumMode(UART1, LIN_ENHANCED_CHECKSUM);

        /* Set the respond mode */
        LIN_SetResponse(UART1, LIN_RESPONSE_TX);

        /* Set the respond lenth */
        LIN_SetResponseLen(UART1, LIN_RESPONSE_8_BYTE);
        
        TIMER_SetReloadValue(TIMER1, 
        CLOCK_UsToCounter(((10 * 8 + 20) * 1000000 / (CLOCK_GetModuleClock(UART1_MODULE) / UART_GetBaudCount(UART1))), CLOCK_GetModuleClock(TIMER1_MODULE)));
        TIMER_Enable(TIMER1);
        
        /* Set the respond data */
        for (i = 0; i < LIN_RESPONSE_8_BYTE; i++)
        {
            u8Txd[i] = rand() & 0xff;

        }

        for (i = 0; i < LIN_RESPONSE_8_BYTE; i++)
        {
            UART_WriteByte(UART1, u8Txd[i]);
        }
        
        SET_BITS(UART1->LINCTL, LINCTL_TXCHKSUM_TRANSMIT);

        for (i = 0; i < LIN_RESPONSE_8_BYTE; i++)
        {
            printf("The send data is %x\n", u8Txd[i]);
        }

        /* Clear the start signal flag */
        UART_ClearInt(UART1, UART_INT_LIN_ID_MATCH);
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
    /* GetAutobaudlockFlag */
    if (UART_GetIntFlag(UART1, UART_INT_AUTOBAUD_LOCK) != 0)
    {
        /* The BaudCount must be set once again */
        UART_SetBaudCount(UART1, UART_GetBaudCount(UART1));

        UART_ClearInt(UART1, UART_INT_AUTOBAUD_LOCK);
    }
    UART_ClearInt(UART1, UART_INT_ALL);
}


void TIMER1_IRQHandler()
{
    /* When communication finished, should revert LIN to none response */
    LIN_SetResponse(UART1, LIN_RESPONSE_NONE);

    TIMER_Disable(TIMER1);
    /* Clear the INT */
    TIMER_ClearInt(TIMER1);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
