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
#include <stdlib.h>


#define                DatumCount                  4
#define                WORD_TEST


uint16_t               i;
uint32_t               u32RXData;                                      /* Receive word */
uint32_t               u32TXData;                                      /* Send word */
uint8_t                u8RXData;                                       /* Receive byte */
uint8_t                u8TXData;                                       /* Send byte */


uint32_t UART_RX_Word(void)
{
    volatile uint32_t i = 0;
    uint32_t u32Data = 0;
    uint32_t u32Bit;

    for (i = 0; i < 4; i++)
    {
        /* Wait until data is available in RBR or the FIFO */
        while (!UART_GetStatus(UART1, UART_STS_RX_NOT_EMPTY))
        {
        }

        /* In receive process, the MSB come first and the LSB comes the last */
        u32Bit = ((3 - i) * 8);
        u32Data |= UART_ReadByte(UART1) << u32Bit;
    }

    return u32Data;
}


void UART_TX_Word(uint32_t u32Data)
{
    volatile uint32_t i = 0;
    uint32_t u32Mask;
    uint32_t u32Bit;

    for (i = 0; i < 4; i++)
    {
        /*
        * Write the datum to UART Transmit Holding Register, which will be sent out,
        * the MSB sent out first.
        */
        u32Mask = 0xFF000000 >> (i * 8);
        u32Bit = (3 - i) * 8;
        UART_WriteByte(UART1, (u32Data & (u32Mask)) >> (u32Bit));

        /* Wait for the TX FIFO empty */
        while (!UART_GetStatus(UART1, UART_STS_TX_EMPTY));
    }
}


uint8_t UART_RX_Byte(void)
{
    uint8_t u8Data = 0;

    /* Wait until data is available in RBR or the FIFO */
    while (!UART_GetStatus(UART1, UART_STS_RX_NOT_EMPTY));

    /* In receive process, the MSB come first and the LSB comes the last */
    u8Data = UART_ReadByte(UART1);

    return u8Data;
}


void UART_TX_Byte(uint8_t u8Data)
{
    /* Write the datum to UART Transmit Holding Register */
    UART_WriteByte(UART1, u8Data);

    /* Wait for the TX FIFO empty */
    while (!UART_GetStatus(UART1, UART_STS_TX_EMPTY));
}


/*************************************************************************************************************************
 *
 * @brief      In this case, UART using polling model to transmit datum, and the other UART end communicating with this
 *             UART end will sent these datum back, The TX UART end in this demo will receive the back datum and do a
 *             double check.
 *
 *
 *            This demo is a couple with another named 'UART_RX_and_SentBack'.
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
    * Init the UART1
    *
    * 1.Set the GPIO25/26 as UART FUNC
    *
    * 2.Enable the UART CLK
    *
    * 3.Set the rest para
    */
    PIN_SetChannel(PIN_GPIO6, PIN_GPIO6_UART1_TXD);
    PIN_SetChannel(PIN_GPIO7, PIN_GPIO7_UART1_RXD);
    UART_Init(UART1, 38400);
    UART_EnableTx(UART1);
    UART_EnableRx(UART1);

    printf("Enter the test\n");

#ifdef WORD_TEST
    /* Generate the world datum to be sent and sent them out */
    for (i = 0; i < DatumCount; i++)
    {
        u32TXData = rand() & 0xFFFFFFFF;
        UART_TX_Word(u32TXData);
        u32RXData = UART_RX_Word();
        printf("The u32TXData is %x\n", u32TXData);
        if (u32TXData != u32RXData)
        {
            printf("The test is Error\n");
            return 0;
        }
    }
    printf("The test is pass\n");
#else
    /* Generate the byte datum to be sent and sent them out */
    for (i = 0; i < DatumCount; i++)
    {
        u8TXData = rand() & 0xFF;
        UART_TX_Byte(u8TXData);
        u8RXData = UART_RX_Byte();

        printf("The u8TXData is %x\n", u8TXData);

        if (u8TXData != u8RXData)
        {
            printf("The test is Error\n");
            return 0;
        }
    }
    printf("The test is pass\n");
#endif

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
