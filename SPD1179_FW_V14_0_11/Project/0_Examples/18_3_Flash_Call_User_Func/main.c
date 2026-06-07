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
#include <stdlib.h>
#include <string.h>
#include "func.h"




uint32_t    SPINTestFlag, *argv_1;
PHBs        * MotorStatus, * argvPHB;
int         * argv;
int         val = 10;


/*************************************************************************************************************************
 *
 * @brief      In this demo, A example how to access the function in the different flash partition of the main processing
 *             thread is gaven. This project is the demo code of main processing thread, the user function interface demo
 *             can be found in folder named "Flash_User_FuncWrap". You can load the code in "Flash_User_FuncWrap" first into
 *             flash, then load this project code, if every thing is done, this main thread use the function pointer to find
 *             the user function interface address and execute it.
 *
 *                                      ------------------
 *                                     |                  |
 *                                     |                  |
 *                                     |------------------|
 *                                     |  User function   |<------
 *                                     |     Interface    |       |
 *                                     |------------------|       |
 *                                     |                  |       |
 *                                     |                  |       |
 *                                     |                  |       |
 *                                     |                  |       |
 *                                     |                  |       |
 *                                     |                  |       |
 *                                     |                  |       |
 *                                     |------------------|       |
 *                                     |    Main thread   |-------    At a moment, the main thread call the function in the
 *                                     |                  |           space dose not belong to the main thread.
 *                                      ------------------
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
    
    pHWLIB->FLASHC_Init();
    
    printf("Start test...\n");

    printf("Init global value %d...\n", ThirdFuncLib->pTestFunc());

    argv = &val;
    SPINTestFlag = ThirdFuncLib->pUserFunc(1, 2, 3, argv, 4);
    printf("Spintrol test result : %d \n",SPINTestFlag);
    
    argv = &val;
    SPINTestFlag = ThirdFuncLib->pUserFunc(1, 2, 3, argv, 4);
    printf("Spintrol test result : %d \n",SPINTestFlag);

    argv_1 = (uint32_t *)&val;
    argvPHB = malloc(sizeof(struct PHB));
    memset(argvPHB, 0x0, sizeof(struct PHB));

    MotorStatus = ThirdFuncLib->pGetMotorStatus(argv_1, argvPHB, argv, &argv_1, 3);
    printf("Motor test result : %d , %d\n",MotorStatus->phase,MotorStatus->voltage);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
