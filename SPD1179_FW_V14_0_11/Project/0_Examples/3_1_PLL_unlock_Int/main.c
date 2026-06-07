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


ErrorStatus                    Status;


/*************************************************************************************************************************
 *
 * @brief      In this case, test the PLL clock unlock.
 *
 *************************************************************************************************************************/


int main(void)
{
    CLOCK_InitWithRCO(CLOCK_CPU_32MHZ);

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

    /* Configure PLL clock */
    Status = CLOCK_ConfigurePLL(0, __RCO_CLOCK, 100000000);
    if (Status == SUCCESS)
    {
        printf("the PLL initial success\n");
    }
    else
    {
        printf("the PLL initial failed\n");
    }

    /* Enable PLL clock unlock Int */
    SYSTEM_EnableNonMaskableInt(NMI_EVENT_PLL_UNLOCK);

    /* Suddenly change the NIN to create PLL clock unlock event  */
    CLOCK->PLLCTL1 = (CLOCK->PLLCTL1 & (~PLLCTL1_NIN_Msk)) | PLLCTL1_NIN_1;

    while (1)
    {

    }
}


void NMI_Handler(void)
{
    printf("NMI_Handler\n");

    /* Get PLL UNLOCK flag */
    if (SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_PLL_UNLOCK) != 0)
    {
        printf("PLLUNLOCK interrupt\n");
    }

    Delay_Ms(500);

    /* Clear PLL UNLOCK Int */
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_PLL_UNLOCK);

    /* Clear NMI Int */
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_GLOBAL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
