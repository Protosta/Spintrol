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


#define PWM_FREQ                                             10000                                         /* 10000Hz PWM */


/*************************************************************************************************************************
 *
 * @brief      In this case, In this case, PIN_GPIO19 used as PWM output and ECAP output.
 *
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

    CLOCK_EnableModule(ECAP_MODULE);

    /* Config ECAP operating mode */
    ECAP_SetMode(ECAP, ECAP_APWM_MODE);

    /* Calculate Period Value based on system clock and ECAP clock */
    ECAP_SetPRD(ECAP, CLOCK_GetModuleClock(ECAP_MODULE) / PWM_FREQ);

    printf("ECAP->CAP0 is %x", ECAP->CAP0);

    /* Set polarity */
    ECAP_SetAPWMOutputPolarity(ECAP, GPIO_LEVEL_HIGH);

    /* Set duty */
    ECAP_APWMSetDuty(ECAP, 5000);

    /* Set Output */
    PIN_SetChannel(PIN_GPIO1, PIN_GPIO1_ECAP_APWMO);

    /* Run Counter */
    ECAP_RunCounter(ECAP);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
