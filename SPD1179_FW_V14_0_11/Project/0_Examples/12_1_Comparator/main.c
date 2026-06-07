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
 * @brief      In this case, if the value of DPGAP_OUT is bigger than the reference voltage, the print will be 
 *             "DPGAP_OUT is higher than 2500mV", 
 *             otherwise, "DPGAP_OUT is lower than 1900mV\n".
 * @note       When do the test, DPGAN_IN should be connected to GND, DPGAP_IN should be connected to voltage source.
 *             DPGAP_OUT = DVDD33/2+DPGAP_IN*G/2
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

    /*
    * set the DPGA, G == 2
    */
    PGA_InitDPGA(DPGA_GAIN_2X);

    /* Enable PGA */
    PGA_EnableDPGA();

    /* DPGAP_OUT = DVDD33/2+DPGAP_IN*G/2 */
    /* Set DPGAP as input to comparator, set Too High threshold is 2500mV, filter window is 200ns */
    COMP_Init(COMP_H, COMP_FROM_DPGAP_OUT, 2500, 200);
    
    /* Set DPGAP as input to comparator, set Too Low threshold is 1900mV, filter window is 200ns */
    COMP_Init(COMP_L, COMP_FROM_DPGAP_OUT, 1900, 200);

    /* Enable comparator */
    COMP_Enable(COMP_H);
    COMP_Enable(COMP_L);

    while (1)
    {
        /* Get the comparator status */
        if (COMP_GetFilterOutputFlag(COMP_H) != 0)
        {
            printf("DPGAP_OUT is higher than 2500mV\n");
        }
        else if (COMP_GetFilterOutputFlag(COMP_L) != 0)
        {
            printf("DPGAP_OUT is lower than 1900mV\n");
        }

        /* Clear latched filter status */
        COMP_ClearFilterOutputFlag(COMP_L | COMP_H);

        Delay_Ms(500);
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
