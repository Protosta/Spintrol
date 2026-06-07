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
 * @brief      In this case, if VDD33 over-voltage or VDD33 under-voltage event happened, reset the system.
 *
 *              Key_points:
 *                        (1)the UART TXD PIN must be pull up, otherwise the printf will be abnormal
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

    /* Observe the VDD33OV reset flag */
    if (SYSTEM_GetResetEventFlag(RESET_EVENT_VDD33OV) != 0)
    {
        printf("VDD33 over-voltage reset happened\n");

        /* Clear the VDD33OV reset flag */
        SYSTEM_ClearResetEventFlag(RESET_EVENT_VDD33OV);
    }

    /* Observe the VDD33UV reset flag */
    else if (SYSTEM_GetResetEventFlag(RESET_EVENT_VDD33UV) != 0)
    {
        printf("VDD33 under-voltage reset happened\n");

        /* Clear the VDD33UV reset flag */
        SYSTEM_ClearResetEventFlag(RESET_EVENT_VDD33UV);
    }

    /* Assert value must be equal to de-assert value */
    /* Set the BOD of VDD33UV */
    POWER_SetVDD33UVThreshold(BOD_VDD33UV_3dot03_V, BOD_VDD33UV_3dot03_V);

    /* Set the BOD of VDD33OV */
    POWER_SetVDD33OVThreshold(BOD_VDD33OV_3dot66_V, BOD_VDD33OV_3dot66_V);

    /* Enable VDD33 over-voltage and VDD33 under-voltage reset MCU */
    SYSTEM_EnableResetEvent(RESET_EVENT_VDD33UV | RESET_EVENT_VDD33OV);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
