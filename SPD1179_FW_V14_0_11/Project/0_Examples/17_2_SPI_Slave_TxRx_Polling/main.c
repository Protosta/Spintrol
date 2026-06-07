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

#define                   DEBUG_INFO                        1                         /*debug infomation flag*/
#define                   T_BUFFER_SIZE                     128                       /*data size of recieve and tansmit*/
#define                   DataWidth_8bit                    8                         /*data width size of SPI*/
#define                   SPIBaudrate_1M                    1000000                   /*SPI baudrate*/


uint32_t                  gu32BuffSize                      = T_BUFFER_SIZE;
uint32_t                  gau32TxBuf[T_BUFFER_SIZE];
uint32_t                  gau32RxBuf[T_BUFFER_SIZE];
ErrorStatus               estatus;

static ErrorStatus Check_Receive_Data(void)
{
    int i;
    uint8_t u8Data = 0;

    /*To check the datum sent and recieved are the same*/
    for(i = 0; i < gu32BuffSize; i++)
    {
        if (gau32RxBuf[i] != u8Data)
        {
            #if DEBUG_INFO
            printf("[Error]@%4d: TX(0x%02X) != RX(0x%02X)\n", __LINE__, u8Data, gau32RxBuf[i] );
            #endif
            
            return ERROR;
        }
        else
        {
            #if DEBUG_INFO
            printf("%3d: TX(0x%02X) == RX(0x%02X)\n", i, u8Data, gau32RxBuf[i] );
            #endif
        }

        u8Data++;
    }
    
    return SUCCESS;
}

void SPI_TxRx(void)
{
    int i;
    uint8_t u8Data = 0;

    /* Prepare data to be send */
    for (i = 0; i < (int)(gu32BuffSize); i++)
    {
        gau32TxBuf[i] = u8Data++;
    }

    printf("Slave TxRx data...\n");
    SPI_FullDuplexTransceive(SPI1, gau32TxBuf, gau32RxBuf, gu32BuffSize);
    
    estatus = Check_Receive_Data();
    if (estatus == SUCCESS)
    {
        printf("Success\n");
    }
}


/*************************************************************************************************************************
 *
 * @brief      In this case, slave sent datum received from master back to master.
 *
 *             This demo code couple with another named 'SPI_Master_Polling_TxRx'.
 *             First start the 'SPI_Slave_TxRx_Polling' and then start the 'SPI_Master_Polling_TxRx'
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

    #if (defined(SPD1179) || defined(SPD1177))
    /* Set GPIOs as SPI function */
    PIN_SetChannel(PIN_GPIO12, PIN_GPIO12_SPI1_SCLK);
    PIN_SetChannel(PIN_GPIO13, PIN_GPIO13_SPI1_SFRM);
    PIN_SetChannel(PIN_GPIO14, PIN_GPIO14_SPI1_MOSI);
    PIN_SetChannel(PIN_GPIO15, PIN_GPIO15_SPI1_MISO);

    /* Set Output Strength(for high speed) */
    PIN_SetOutStrength(PIN_GPIO12, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO13, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO14, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO15, PIN_OUT_STRENGTH_20MA);
    #else
    /* Set GPIOs as SPI function */
    PIN_SetChannel(PIN_GPIO36, PIN_GPIO36_SPI1_SCLK);
    PIN_SetChannel(PIN_GPIO37, PIN_GPIO37_SPI1_SFRM);
    PIN_SetChannel(PIN_GPIO38, PIN_GPIO38_SPI1_MOSI);
    PIN_SetChannel(PIN_GPIO39, PIN_GPIO39_SPI1_MISO);

    /* Set Output Strength(for high speed) */
    PIN_SetOutStrength(PIN_GPIO36, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO37, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO38, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO39, PIN_OUT_STRENGTH_20MA);
    #endif

    /*
    * Init SPI Baud Rate, Frame Format
    * 1) Set slave mode
    * 2) Set PHS_POL_00 mode
    * 3) Set frame data 8-bits width
    * 4) Set transfer speed 1Mbps
    */
    SPI_Init(SPI1, SPI_SLAVE, SPI_MODE_PHS_POL_00, DataWidth_8bit, SPIBaudrate_1M);

    /* Enable SPI */
    SPI_Enable(SPI1);

    /* SPI Master Tx/Rx datum */
    SPI_TxRx();

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
