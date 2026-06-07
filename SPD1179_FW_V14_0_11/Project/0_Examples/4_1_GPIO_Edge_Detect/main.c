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


/*************************************************************************************************************************
 *
 * @brief      In this case, PIN_GPIO6 ouput a rising edge, PIN_GPIO7 connected with PIN_GPIO6 will detect this rising edge,
 *             corresponding information will be print when rising edge happened.
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

    /* Set PIN_GPIO6/PIN_GPIO7 as GPIO FUNC */
    PIN_SetChannel(PIN_GPIO6, PIN_GPIO6_GPIO6);
    PIN_SetChannel(PIN_GPIO7, PIN_GPIO7_GPIO7);

    /* Set PIN_GPIO6/PIN_GPIO7 direction */
    GPIO_SetPinDir(PIN_GPIO6, GPIO_OUTPUT);
    GPIO_SetPinDir(PIN_GPIO7, GPIO_INPUT);

    /*
    * De-glitch settings, if IO signal state can keep 128 PCLK cycles,
    * then it will will be assumed valid
    */
    PIN_SetDeglitchWindow(DGCLKCTL_PDIV_128);
    PIN_EnableDeglitch(PIN_GPIO7);

    /* Enable GPIO edge trigger INT in MCU side */
    NVIC_EnableIRQ(GPIO_EDGE_IRQn);

    /* GPIO INT configuration: rising edge will trigger INT */
    GPIO_SetEdgeIntMode(PIN_GPIO7, GPIO_EDGE_RISING);

    /* Generate a rising edge */
    GPIO_SetLow(PIN_GPIO6);
    Delay_Ms(100);
    GPIO_SetHigh(PIN_GPIO6);

    while (1)
    {
    }
}


void GPIO_EDGE_IRQHandler()
{
    /* Checking if Edge had detected */
    if (GPIO_GetRisingEdgeIntRawFlag(PIN_GPIO7) == 1)
    {
        printf("Rising edge had detected\n");
    }
    else
    {
        printf("No rising edge, test failed\n");
    }

    /* Clear GPIO INT */
    GPIO_ClearRisingEdgeInt(PIN_GPIO7);
    GPIO_ClearGlobalEdgeInt();
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
