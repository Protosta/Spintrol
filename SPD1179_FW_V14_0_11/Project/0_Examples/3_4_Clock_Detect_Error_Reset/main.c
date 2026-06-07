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


ErrorStatus Status;


/*************************************************************************************************************************
 *
 * @brief      In this case, we suppose the PLL clock is 100MHz, but set the PLL clock at 75MHz. Then use the RCO0 to detect
 *              if PLL clock is around 100MHz, if clock error happened, reset the system.
 *
 *              Key_points:
 *                        (1)the UART TXD PIN must be pull up, otherwise the printf will be abnormal
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

    /* Observe the clock error reset flag */
    if (SYSTEM_GetResetEventFlag(RESET_EVENT_CLK_DETECT_ERROR) != 0)
    {
        printf("the PLL CLKDETERR happened\n");
        /* Clear the PLL clock error reset flag */
        SYSTEM_ClearResetEventFlag(RESET_EVENT_CLK_DETECT_ERROR);
    }

    /* Configure PLL clock */
    Status = CLOCK_ConfigurePLL(0, __RCO_CLOCK, CLOCK_CPU_75MHZ);
    if (Status == SUCCESS)
    {
        printf("the PLL initial success\n");
    }
    else
    {
        printf("the PLL initial failed\n");
    }

    /* Initialize the clock detection */
    Status = CLOCK_DetectionInit(CLOCK_FROM_RCO, CLOCK_CPU_32MHZ, CLOCK_FROM_PLL, 100000000, 1);
    if (Status == SUCCESS)
    {
        printf("the PLL detect set success\n");
    }
    else
    {
        printf("the PLL detect set failed\n");
    }

    Delay_Ms(1000);

    /* Enable clock error reset MCU */
    SYSTEM_EnableResetEvent(RESET_EVENT_CLK_DETECT_ERROR);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
