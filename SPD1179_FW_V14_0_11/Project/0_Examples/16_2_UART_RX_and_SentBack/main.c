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


#define              WORD_TEST


uint32_t             u32RXData;                                     /* Receive word */
uint8_t              u8RXData;                                      /* Receive byte */


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
 * @brief      In this case, UART using polling model receive the datum come from transmitting end, and sent these datum
 *             back.
 *
 *
 *************************************************************************************************************************/


int main(void)
{
    CLOCK_InitWithRCO(100000000);

    Delay_Init();

    /*
     * Init the UART0
     */
    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    /*
     * Init the UART1
     */
    PIN_SetChannel(PIN_GPIO6, PIN_GPIO6_UART1_TXD);
    PIN_SetChannel(PIN_GPIO7, PIN_GPIO7_UART1_RXD);
    UART_Init(UART1, 38400);
    UART_EnableTx(UART1);
    UART_EnableRx(UART1);

    printf("Enter the test\n");

#ifdef WORD_TEST
    /* Receive the byte data comes from the transmitting end, and sent it back */
    while (1)
    {
        u32RXData = UART_RX_Word();
        UART_TX_Word(u32RXData);
        printf("u32RXData is %x\n", u32RXData);
    }
#else
    /* Receive the byte data comes from the transmitting end, and sent it back */
    while (1)
    {
        u8RXData = UART_RX_Byte();
        UART_TX_Byte(u8RXData);
        printf("u8RXData is %x\n", u8RXData);
    }
#endif
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
