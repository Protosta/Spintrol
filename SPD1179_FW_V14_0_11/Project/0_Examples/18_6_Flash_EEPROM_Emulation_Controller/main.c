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

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "eeprom_lib.h"

#define EEPROM_ENTRY_SIZE                       256

uint32_t WriteBuf[EEPROM_ENTRY_SIZE];
uint32_t ReadBuf[EEPROM_ENTRY_SIZE];
uint32_t status = 0;

/*************************************************************************************************************************
 *
 * @brief      In this case, we use the Flash to emulate the EEPROM
 *
 *              Key_points:
 *                        (1)Need to erase chip to make sure the EEPROM is clean at the first time.
 *
 *************************************************************************************************************************/


int main(void)
{
    uint32_t i;
    
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

    pHWLIB->FLASHC_Init();

    /* Init WriteBuf data */
    for(i = 0; i < 256; i++)
    {
        WriteBuf[i] = rand();
    }

    /* Init eeprom struct */
    status = EEPROM_Init();
    if (status != EEPROM_STATUS_OK)
    {
        if (status == EEPROM_STATUS_INVALID_HEADER)
        {
            status = EEPROM_Format();
            if (status != EEPROM_STATUS_OK)
            {
                printf("Erases EEPROM pages and Select a page FAIL!\n");
                return 1;
            }
            else
            {
                printf("Erases EEPROM pages and Select a page as VALID SUCCESS\n");
            }
        }
        else
        {
            printf("status %x\n", status);
            
            /* Add operation here, for example MEEPROM_Format */
            status = EEPROM_Format();
            if (status != EEPROM_STATUS_OK)
            {
                printf("Erases EEPROM pages and Select a page FAIL!\n");
                return 1;
            }
            else
            {
                printf("Erases EEPROM pages and Select a page as VALID SUCCESS\n");
            }
        }
    }
    
    /* Write eeprom data */
    for (i = 0; i < 256; i++)
    {
        status = EEPROM_WriteWord(i, WriteBuf[i]);
        if(status != EEPROM_STATUS_OK)
        {
            printf("Write eeprom data FAIL!\n");
            return 1;
        }
    }


    /* Read eeprom data */
    for (i = 0; i < 256; i++)
    {
        status = EEPROM_ReadWord(i, &ReadBuf[i]);
        if(status != EEPROM_STATUS_OK)
        {
            printf("Read eeprom data FAIL!\n");
            return 1;
        }
    }

    /* Check the read back data */
    for(i = 0; i < 256; i++)
    {
        if(ReadBuf[i] != WriteBuf[i])
        {
            printf("Test FAIL!\n");
            printf("Data[%d] : %d - %d\n",i,ReadBuf[i], WriteBuf[i]);
            break;
        }
    }

    printf("Test SUCCESS!\n");

    while(1)
    {
        
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
