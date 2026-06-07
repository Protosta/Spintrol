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

    /* Set PIN_GPIO6 as GPIO FUNC */
    PIN_SetPinAsGPIO(PIN_GPIO6);

    /* Set PIN_GPIO6 direction */
    GPIO_SetPinDir(PIN_GPIO6, GPIO_OUTPUT);

    /* Set the GPIO as low level */
    GPIO_SetLow(PIN_GPIO6);

    /* Toggle the GPIO level */
    GPIO_SetHigh(PIN_GPIO6);

    Delay_Ms(1);
    
    /* Checking if these configure work */
    if (GPIO_GetLevel(PIN_GPIO6) != GPIO_LEVEL_LOW)
    {
        printf("GPIO toggle PASS\n");
    }
    else
    {
        printf("GPIO toggle FAIL\n");
    }

    while (1)
    {
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
