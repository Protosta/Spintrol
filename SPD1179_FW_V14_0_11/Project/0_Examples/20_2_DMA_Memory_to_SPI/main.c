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


#define              SOURCE_ADDRESS            0x1ffffa00


uint32_t            *pu32Src                  = (uint32_t *)SOURCE_ADDRESS;
uint32_t            au32Result[4];                                               /* Result data */
uint32_t            i;                                                           /* Print Num */


void DMA_SPI_Init(SPI_REGS *SPIx)
{
    /* Unlock Key Protect */
    SPI_WALLOW(SPIx);

    /* Stop SPI */
    SPI_Disable(SPIx);

    /* SPI_Init */
    SPI_Init(SPIx, SPI_MASTER, SPI_MODE_PHS_POL_00, 32, 1000000);

    /* Enable SPI loop */
    SPI_EnableLoopback(SPIx);

    /* Enable the Tx DMA */
    SPI_SetTxDMA(SPIx, ENABLE);
    SPI_SetRxDMA(SPIx, DISABLE);
}


void DMA_Int_Init(DMA_ChannelEnum DMA_CHx)
{
    /* Enable the DMA interrupt */
    DMA_EnableTransferCompleteInt(DMA_CHx);
    DMA_EnableTransferErrorInt(DMA_CHx);

    /* Clear all interrupt flag */
    DMA_ClearTransferCompleteInt(DMA_CHx);
    DMA_ClearTransferErrorInt(DMA_CHx);

    /* Disable the DMA transfer */
    DMA_DisableChannelTransfer(DMA_CHx);
}


/*************************************************************************************************************************
 *
 * @brief       This example use DMA channel 0 to transfer the data from RAM to SPI.
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

    /* Enable global INT for DMA */
    NVIC_EnableIRQ(DMAC_IRQn);

    /* Stop DMA */
    DMA_Disable();

    /* Wait until DMA is disable */
    while (DMA_IsEnable() == 1)
    {}

    /* DMA relevant SPI parameter set */
    DMA_SPI_Init(SPI0);

    /* Run SPI */
    SPI_Enable(SPI0);

    /* DMA enable interrupt */
    DMA_Int_Init(DMA_CH0);

    /* Transfer type */
    DMA_SetTransferType(DMACH0, DMA_MEMORY_TO_PERIPHERAL);

    /* Set source transfer parameters */
    DMA_SetSourceTransferWidth(DMACH0, DMA_TRANSFER_IN_WORD);
    DMA_SetSourceBurstLen(DMACH0, DMA_BURST_LENGTH_4_WORDS);

    /* Set destination transfer parameters */
    DMA_SetDestinationTransferWidth(DMACH0, DMA_TRANSFER_IN_WORD);
    DMA_SetDestinationBurstLen(DMACH0, DMA_BURST_LENGTH_4_WORDS);

    /* Block transfer num */
    DMA_SetBlockTransferSize(DMACH0, 4);

    /* Init source memory */
    pu32Src = (uint32_t *)SOURCE_ADDRESS;
    pu32Src[0] = 0x82131415;
    pu32Src[1] = 0x86171819;
    pu32Src[2] = 0x80212223;
    pu32Src[3] = 0x84252627;

    for (i = 0; i < 4; i++)
    {
        printf("The Send word is %x\n", *((uint32_t *)pu32Src + i));
    }

    /* Source address */
    DMA_SetSourceAddr(DMACH0, SOURCE_ADDRESS);
    /* Source address increment */
    DMA_SetSourceAddrMode(DMACH0, DMA_ADDRESS_MODE_INCREASE);
    DMA_SetSourceHandShake(DMACH0, DMA_HANDSHAKE_BY_SOFTWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH) ;

    /* Destination address */
    DMA_SetDestinationAddr(DMACH0, (uint32_t)(&SPI0->SPIDATA));
    /* Destination address increment */
    DMA_SetDestinationAddrMode(DMACH0, DMA_ADDRESS_NO_CHANGE);
    DMA_SetDestinationHandShake(DMACH0, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH) ;
    /* Destination peripheral */
    DMA_SetDestinationPeripheral(DMACH0, DMA_DPER_SPI0_TX);

    /* DMA disable suspend */
    DMA_DisableSuspend(DMACH0);

    /* Enable channel 0 interrupt */
    DMA_EnableChannelInt(DMACH0);
    
    /* Enable DMA */
    DMA_Enable();
    
    while (1)
    {
        /* Enable Channel 0 transfer*/
        DMA_EnableChannelTransfer(DMA_CH0);

        /* Wait until all data is received */
        while ((SPI_GetRxFIFOLevel(SPI0) != 4))
        {
        }

        for (i = 0; i < 4; i = i + 1)
        {
            au32Result[i] = SPI_ReceiveData(SPI0);

            printf("%d:Rx 0x%08X\n", i, au32Result[i]);
        }

        Delay_Ms(100);

        /* Reset the source addr, because source addr is increased after previous loop */
        DMA_Disable();
        DMA_SetSourceAddr(DMACH0, SOURCE_ADDRESS);
        DMA_Enable();
    }
}


void DMAC_IRQHandler(void)
{
    /* Get TRANSFER ERROR flag */
    if (DMA_GetGlobalIntFlag(DMA_INT_TRANSFER_ERROR) != 0)
    {
        printf("DMA Channel Error!\n");
    }

    /* Get TRANSFER COMPLETE flag */
    if (DMA_GetGlobalIntFlag(DMA_INT_TRANSFER_COMPLETE) != 0)
    {
        printf("Channel transfer complete!\n");
    }

    /* Get DMA_CH0 TRANSFER COMPLETE flag */
    if (DMA_GetTransferCompleteIntFlag(DMA_CH0) != 0)
    {
        printf("Channel 0 transfer complete!\n");
        /* Clear DMA_CH0 TRANSFER COMPLETE flag */
        DMA_ClearTransferCompleteInt(DMA_CH0);
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
