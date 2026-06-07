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
#include "spd1179.h"
#include <stdio.h>


uint16_t                         u16PREDRIID;                  /* PRE-DRIVER mode ID */
ErrorStatus                      eErrorState;                  /* Function State */


/*************************************************************************************************************************
 *
 * @brief      In this case, use the MON pin to detect the rising edge. First connect the MON pin to GND, then connect the
 *            pin to VBAT.
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

    /* HV reset */
    eErrorState = HV_Reset();
    if (eErrorState == ERROR)
    {
        printf("HV_Reset FAIL\n");
        return 0;
    }
    else
    {
        printf("HV_Reset SUCCESS\n");
    }

    /* HV init */
    eErrorState = HV_Init(&u16PREDRIID);
    if (eErrorState == ERROR)
    {
        printf("Init HV mode FAIL\n");
        return 0;
    }
    else
    {
        printf("Init HV mode SUCCESS[ID:%d]\n", u16PREDRIID);
    }

    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
        return 0;
    }

    /* MON module enable */
    eErrorState = EPWR_WriteRegisterField(HV_REG_MONCTL, MONCTL_PULLMODE_Msk | MONCTL_EN_Msk, MONCTL_PULLMODE_PULL_ADAPTIVE | MONCTL_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("MONCTL_WriteRegisterField FAIL\n");
        return 0;
    }

    /* Set the GPIO as input */
    PIN_SetChannel(PIN_GPIO27, PIN_GPIO27_GPIO27);
    GPIO_SetPinDir(PIN_GPIO27, GPIO_INPUT);

    /* Set the filter window */
    PIN_SetDeglitchWindow(DGCLKCTL_PDIV_128);
    PIN_EnableDeglitch(PIN_GPIO27);

    /* Enable GPIO edge trigger INT in MCU side */
    NVIC_EnableIRQ(GPIO_EDGE_IRQn);

    /* GPIO INT configuration: rising edge will trigger INT */
    GPIO_SetEdgeIntMode(PIN_GPIO27, GPIO_EDGE_RISING);

    while (1)
    {

    }
}


void GPIO_EDGE_IRQHandler()
{
    int iResult = -1;

    /* Checking if Edge had detected */
    iResult = GPIO_GetRisingEdgeIntRawFlag(PIN_GPIO27);
    if (iResult == 1)
    {
        printf("Rising edge had detected\n");
    }
    else
    {
        printf("No rising edge, test failed\n");
    }

    /* Clear GPIO INT */
    GPIO_ClearRisingEdgeInt(PIN_GPIO27);
    GPIO_ClearGlobalEdgeInt();
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
