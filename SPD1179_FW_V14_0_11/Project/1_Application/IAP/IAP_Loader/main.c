/******************************************************************************
 * @file     main.c
 * @brief    Main body
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
#include "iap.h"
#include "stdio.h"




/*********************************************************************************************************************
 *
 * @brief      In this case, use UART or LIN to update IAP_App in MCU
 *
 *                                                                    
 *                                                          __ __ __ __ __ __ __ __ __ __ __ __ __
 *                                                         |                                      |
 *                                                         |                                      |
 *             _____         ______ _____                  |            _________________         |
 *            |     |       |            |-RX------------- |--------TX-|                 |        |
 *            | PC  |       |            |                 |           |       MCU       |        |
 *            |     |<----->| USB-TO-UART|-TX------------- |--------RX-|                 |        |
 *            |     |       |            |                 |           |                 |        |
 *            |     |       |            |                 |           |                 |        |
 *            |_____|       |____________|-------------GND-|-----------|_________________|        |
 *                                                         |                                      |
 *                                                         |__ __ __ __ __ __ __ __ __ __ __ __ __|
 *
 *                                                                      
 *                                                          __ __ __ __ __ __ __ __ __ __ __ __ __
 *                                                         |                                      |
 *                                                         |                                      |
 *             _____         ______ _____                  |            _________ _______         |
 *            |     |       |            |-------------LIN-|--------x--|     |       |   |        |
 *            | PC  |       |            |                 |        |  | LIN | MCU   |   |        |
 *            |     |<----->| USB-TO-LIN |                 |220pF  --- | PHY |       |   |        |
 *            |     |       |            |                 |       --- |     |       |   |        |
 *            |     |       |            |                 |        |  |_____|_______|   |        |
 *            |_____|       |____________|-------------GND-|--------x--|_________________|        |
 *                                                         |                                      |
 *                                                         |__ __ __ __ __ __ __ __ __ __ __ __ __|
 *
 * @KeyPoint   :   1. RX connect to TX, TX connect to RX
 *
 * @KeyPoint   :   1. On master side, the tool equipped with a 1k built-in pull-up resistor, so do not need to add any
 *                 pull-up resistor
 *                 2. On slave side, the MCU equipped with a 30k built-in pull-up resistor, so do not need to add any
 *                 pull-up resistor in circuit
 *                 3. On slave side, there need to be a 220pF capacitance between LIN and GND
 *
 * @TestMethod :   1. Use ISP to download IAP_Loader first
 *                 2. In IAP tool click download button to download IAP_App
 *                 3. Reboot MCU because IAP_Loader is already timeout(handshake window is ms level)
 * 
 * @TestResult :   IAP_App run success
 *
 **********************************************************************************************************************/
int32_t main(void)
{
    /* Clock Init */
    CLOCK_InitWithRCO(IAP_CORE_CLK);

    /* Delay Init */
    Delay_Init();

    /*
     * Init the UART
     */
    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);
    
    IAP_Entry();

    while (1)
    {
    }
}

/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

