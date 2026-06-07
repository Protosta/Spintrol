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


uint8_t                      u8Ram_Test_Flag;


/*************************************************************************************************************************
 *
 * @brief      In this case, print system boot times, RAM test result and ECC test result.
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

    printf("BOOTCNT is %d\n", SYSTEM_GetBootCount());

    /* Get RAM built-in self test flag */
    u8Ram_Test_Flag = (SYSTEM->BOOTINFO & BOOTINFO_RAMBISTERR_Msk) >> BOOTINFO_RAMBISTERR_Pos;

    if (u8Ram_Test_Flag == 0)
    {
        printf("RAM test passed\n");
    }
    else
    {
        printf("RAM test failed\n");
    }

    /* Judge if ROM error happened */
    if (SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_ROM_MULTI_BIT_ERROR) != 0)
    {
        printf("ROMtest failed\n");
        printf("ROMERRADDR is %x\n", SYSTEM->ROMERRADDR);
        return 0;
    }
    /* Judge if Flash error happened */
    if (SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_FLASH_MULTI_BIT_ERROR) != 0)
    {
        printf("FLASH test failed\n");
        printf("FLASHERRADDR is %x\n", SYSTEM->FLASHERRADDR);
        return 0;
    }
    /* Judge if IRAM error happened */
    if (SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_RAM0_MULTI_BIT_ERROR) != 0)
    {
        printf("RAM0 test failed\n");
        printf("RAM0ERRADDR is %x\n", SYSTEM->RAM0ERRADDR);
        return 0;
    }
    /* Judge if DRAM error happened */
    if (SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_RAM1_MULTI_BIT_ERROR) != 0)
    {
        printf("RAM1 test failed\n");
        printf("RAM1ERRADDR is %x\n", SYSTEM->RAM1ERRADDR);
        return 0;
    }

    printf("ECC test passed\n");

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
