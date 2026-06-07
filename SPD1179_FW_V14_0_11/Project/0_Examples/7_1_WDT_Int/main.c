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


//#define CURRENT_WDT_TEST_0


/*************************************************************************************************************************
 *
 * @brief      In this case, the WDT can trigger a INT to MCU.
 *
 *        Key_points:
 *                  (1)the UART TXD PIN must be pull up, otherwise the printf will be abnormal
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

#ifdef CURRENT_WDT_TEST_0
    /* Init WDT0 and set count time to 1000ms */
    WDT_Init(WDT0, 1000);

    /* Enable the counter and the interrupt */
    WDT_EnableInt(WDT0);

    WDT_Enable(WDT0);
#else
    /* Init WDT0 and set count time to 1000ms */
    WDT_Init(WDT1, 1000);

    /* Enable the NVIC INT of WDT1 */
    NVIC_EnableIRQ(WDT1_IRQn);

    /* Enable the counter and the interrupt */
    WDT_EnableInt(WDT1);

    WDT_Enable(WDT1);
#endif
    while (1)
    {

    }
}


#ifdef CURRENT_WDT_TEST_0
/* In our solution, WDT0 INT connected to SYS NMI */
void NMI_Handler()
{
    /* Clear INT, So that SYS would restart */
    WDT_ClearInt(WDT0);

    /* Disable the INT */
    WDT_DisableInt(WDT0);

    printf("WDT0 INT test OK\n");
}
#else
void WDT1_IRQHandler()
{
    /* Clear INT, So that SYS would restart */
    WDT_ClearInt(WDT1);

    /* Disable the INT */
    WDT_DisableInt(WDT1);

    printf("WDT1 INT test OK\n");
}
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
