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


uint8_t              u8Id                  = 0x31;           /* Send Id */
uint8_t              u8Txd[8];                               /* TX Data */
uint16_t             u16PREDRIID;                            /* PRE-DRIVER mode ID */
uint16_t             u16PREDRIDATA;                          /* Data read from PRE-DRIVER */
ErrorStatus          eErrorState;                            /* Function State */


/* LIN test init function */
void LIN_Test_Init(UART_REGS *UARTx, LIN_ModeEnum eMode, uint32_t u32BaudRate)
{
    UART_InitSpeed(UARTx, u32BaudRate);

    /* Configure UART control register (UARTCTL) */
    UARTx->UARTCTL = UARTCTL_RXEN_ENABLE             |
                     UARTCTL_TXEN_ENABLE             |
                     UARTCTL_RXDMAEN_DISABLE         |
                     UARTCTL_TXDMAEN_DISABLE         |
                     UARTCTL_LPBK_NORMAL_MODE        |
                     UARTCTL_BUS32_8BIT              |
                     UARTCTL_ABEN_ENABLE             |
                     UARTCTL_ABUP_UPDATE_BY_HW       |
                     UARTCTL_NRZMODE_NRZ_LEVEL       |
                     UARTCTL_DATABIT_8_DATA_BIT      |
                     UARTCTL_PRTYEN_PARITY_ENABLE    |
                     UARTCTL_STOPBIT_1_STOP_BIT;


    /* Configure LIN control register (LINCTL) */
//    UARTx->LINCTL = LINCTL_LINEN_LIN_MODE         |
//                    (eMode << LINCTL_MASTER_Pos)  |
//                    LINCTL_SBRKLEN_13_BIT         |
//                    LINCTL_SBRKDEL_1_BIT          |
//                    LINCTL_RESP_RESPONSE_NONE     |
//                    LINCTL_RESPLEN_X_BYTE         |
//                    LINCTL_CHKSUM_ENHANCED_MODE   |
//                    LINCTL_ATOTH_AUTO_THRESHOLD   |
//                    LINCTL_ATXCHKSUM_AUTO_TX;
}


/*************************************************************************************************************************
 *
 * @brief      In this case, show the LIN TX_Timeout event, the demo code set the TX pin at Low(over 12ms), so the LIN TX
 *        TIMEOUT will happen
 *
 *        Key_points:
 *                  (1)Do not use this demo code to do the LIN communication, because in order to show the over-current
 *        phenomenon, we use the LIN_Test_Init to replace LIN_Init, otherwise the TXD can not be set low.
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
        printf("EPWR_WriteRegisterField FAIL\n");
        return 0;
    }

    /* Enable LIN TX_Timeout shutdown */
    eErrorState = EPWR_WriteRegisterField(HV_REG_LINTXPDEVTEN, LINTXPDEVTEN_LINTXDTIMEOUT_Msk, LINTXPDEVTEN_LINTXDTIMEOUT_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegisterField FAIL\n");
        return 0;
    }

    /* Enable LIN TX_Timeout interrupt */
    eErrorState = EPWR_WriteRegister(HV_REG_TZIE0, TZIE0_LINTXDTIMEOUT_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegister FAIL\n");
        return 0;
    }
    
    /* To imitate TX_Timeout signal, need to use LIN_Test_Init instead of LIN_Init, otherwise the TXD can not be set low*/
    PIN_SetChannel(PIN_GPIO25, PIN_GPIO25_UART1_TXD);
    PIN_SetChannel(PIN_GPIO26, PIN_GPIO26_UART1_RXD);
    LIN_Test_Init(UART1, LIN_MASTER, BAUDRATE);

    /* Enable EPWRTZ0 trigger INT in MCU side */
    NVIC_EnableIRQ(EPWRTZ0_IRQn);

    EPWR_EnableTripEvent(EPWR_TRIP_EVENT_TZ0);

    /* Set the input signal of EPWRTZ0 event as high */
    EPWR_SetTripEventInputActiveHigh(EPWR_TRIP_EVENT_TZ0);

    /* Set the TXD low */
    while (1)
    {
        UART1->UARTCTL = UART1->UARTCTL | UARTCTL_SETBRK_SET_BREAK;
    }
}


void EPWRTZ0_IRQHandler(void)
{
    /* Read the interrupt flag */
    eErrorState = EPWR_ReadRegister(HV_REG_TZIF0, &u16PREDRIDATA);
    if (eErrorState == ERROR)
    {
        printf("EPWR_ReadRegister FAIL\n");
        return;
    }
    if ((u16PREDRIDATA & TZIF0_LINTXTIMEOUT_OCCUR) != 0)
    {
        printf("LINTXTIMEOUT happened\n");
    }

    /* Clear TX_Timeout flag */
    eErrorState = EPWR_WriteRegister(HV_REG_TZIC0, TZIC0_LINTXDTIMEOUT_CLEAR);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegister FAIL\n");
        return;
    }

    /* Clear the total flag */
    EPWR_ClearTripEventFlag(EPWR_TRIP_EVENT_TZ0);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
