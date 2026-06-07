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
 * @brief      In this case, the GPIO to trigger the NMI interrupt. First use wire to connect PIN_GPIO0 and PIN_GPIO6
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

    /* Set PIN_GPIO6 as output */
    PIN_SetPinAsGPIO(PIN_GPIO6);
    GPIO_SetPinDir(PIN_GPIO6, GPIO_OUTPUT);

    /* Set PIN_GPIO0 as input */
    PIN_SetPinAsGPIO(PIN_GPIO0);
    GPIO_SetPinDir(PIN_GPIO0, GPIO_INPUT);

    /*
    * De-glitch settings, if IO signal state can keep 128 PCLK cycles,
    * then it will will be assumed valid
    */
    PIN_SetDeglitchWindow(DGCLKCTL_PDIV_128);
    PIN_EnableDeglitch(PIN_GPIO0);

    /* Falling edge trigger the NMI */
    SYSTEM_SetGPIONMIInput(PIN_GPIO0, GPIO_LEVEL_LOW);

    /* Enable GPIO Int */
    SYSTEM_EnableNonMaskableInt(NMI_EVENT_GPIO_EVENT);

    while (1)
    {
        printf("GPIO will be set LOW\n");

        Delay_Ms(100);

        GPIO_SetLow(PIN_GPIO6);

        Delay_Ms(1000);

        printf("GPIO will be set High\n");

        Delay_Ms(100);

        GPIO_SetHigh(PIN_GPIO6);
    }
}


void NMI_Handler(void)
{
    printf("NMI_Handler\n");

    /* Clear GPIO Int flag */
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_GPIO_EVENT);

    /* Clear global Int flag */
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_GLOBAL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
