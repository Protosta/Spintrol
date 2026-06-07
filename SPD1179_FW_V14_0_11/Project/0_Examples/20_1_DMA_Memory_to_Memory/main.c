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
#define              TARGET_ADDRESS            0x1ffffc00


uint32_t            *pu32Src                  = (uint32_t *)SOURCE_ADDRESS;
uint32_t            *pu32Dst                  = (uint32_t *)TARGET_ADDRESS;
uint32_t            i;                                                            /* Print Num */


/*************************************************************************************************************************
 *
 * @brief       This example use DMA channel 0 to transfer data from RAM to RAM.
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

    /* Init source memory */
    pu32Src[0] = 0x22334411;
    pu32Src[1] = 0x55334411;
    pu32Src[2] = 0x88334411;

    /* Source address */
    DMA_SetSourceAddr(DMACH0, SOURCE_ADDRESS);

    /* Destination address */
    DMA_SetDestinationAddr(DMACH0, TARGET_ADDRESS);

    /* Transfer type */
    DMA_SetTransferType(DMACH0, DMA_MEMORY_TO_MEMORY);

    /* Source address increment */
    DMA_SetSourceAddrMode(DMACH0, DMA_ADDRESS_MODE_INCREASE);

    /* Destination address increment */
    DMA_SetDestinationAddrMode(DMACH0, DMA_ADDRESS_MODE_INCREASE);

    /* Set Source Transfer Width */
    DMA_SetSourceTransferWidth(DMACH0, DMA_TRANSFER_IN_WORD);

    /* Set Destination Transfer Width */
    DMA_SetDestinationTransferWidth(DMACH0, DMA_TRANSFER_IN_WORD);

    /* Block transfer num */
    DMA_SetBlockTransferSize(DMACH0, 3);

    /* Enable channel 0 interrupt */
    DMA_EnableChannelInt(DMACH0);

    /* Enable Channel 0 transfer complete interrupt */
    DMA_EnableTransferCompleteInt(DMA_CH0);
    
    /* Enable DMA */
    DMA_Enable();
    
    while (1)
    {
        /* Enable Channel 0 */
        DMA_EnableChannelTransfer(DMA_CH0);

        Delay_Ms(100);
        
        /* Reset the source and destination addr, because source and destination addr is increased after previous loop */
        DMA_Disable();
        DMA_SetSourceAddr(DMACH0, SOURCE_ADDRESS);
        DMA_SetDestinationAddr(DMACH0, TARGET_ADDRESS);
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

        for (i = 0; i < 3; i++)
        {
            printf("Dest[%d] = 0x%08X\n", i, pu32Dst[i]);
        }

        /* Clear DMA_CH0 TRANSFER COMPLETE flag */
        DMA_ClearTransferCompleteInt(DMA_CH0);
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
