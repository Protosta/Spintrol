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
#include <stdlib.h>
#include <string.h>
#include "math.h"

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif


#include "SEGGER_RTT.h"


volatile int _Cnt;


/*************************************************************************************************************************
 *
 * @brief      This demo shows the communication with JLinkRTTViewer.exe
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
    
    printf("RTT Test...\n\n");


    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);


    SEGGER_RTT_WriteString(0, "SEGGER Real-Time-Terminal Sample\r\n\r\n");
    SEGGER_RTT_WriteString(0, "###### Testing SEGGER_printf() ######\r\n");

    SEGGER_RTT_printf(0, "printf Test: %%c,         'S' : %c.\r\n", 'S');
    SEGGER_RTT_printf(0, "printf Test: %%5c,        'E' : %5c.\r\n", 'P');
    SEGGER_RTT_printf(0, "printf Test: %%-5c,       'G' : %-5c.\r\n", 'I');
    SEGGER_RTT_printf(0, "printf Test: %%5.3c,      'G' : %-5c.\r\n", 'N');
    SEGGER_RTT_printf(0, "printf Test: %%.3c,       'E' : %-5c.\r\n", 'T');
    SEGGER_RTT_printf(0, "printf Test: %%c,         'R' : %c.\r\n", 'R');

    SEGGER_RTT_printf(0, "printf Test: %%s,      \"RTT\" : %s.\r\n", "RTT");
    SEGGER_RTT_printf(0, "printf Test: %%s, \"RTT\\r\\nRocks.\" : %s.\r\n", "RTT\r\nRocks.");

    SEGGER_RTT_printf(0, "printf Test: %%u,       12345 : %u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%+u,      12345 : %+u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%.3u,     12345 : %.3u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%.6u,     12345 : %.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%6.3u,    12345 : %6.3u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%8.6u,    12345 : %8.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%08u,     12345 : %08u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%08.6u,   12345 : %08.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%0u,      12345 : %0u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-.6u,    12345 : %-.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3u,   12345 : %-6.3u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6u,   12345 : %-8.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08u,    12345 : %-08u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6u,  12345 : %-08.6u.\r\n", 12345);
    SEGGER_RTT_printf(0, "printf Test: %%-0u,     12345 : %-0u.\r\n", 12345);

    SEGGER_RTT_printf(0, "printf Test: %%u,      -12345 : %u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%+u,     -12345 : %+u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.3u,    -12345 : %.3u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.6u,    -12345 : %.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%6.3u,   -12345 : %6.3u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%8.6u,   -12345 : %8.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08u,    -12345 : %08u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08.6u,  -12345 : %08.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%0u,     -12345 : %0u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-.6u,   -12345 : %-.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3u,  -12345 : %-6.3u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6u,  -12345 : %-8.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08u,   -12345 : %-08u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6u, -12345 : %-08.6u.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-0u,    -12345 : %-0u.\r\n", -12345);

    SEGGER_RTT_printf(0, "printf Test: %%d,      -12345 : %d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%+d,     -12345 : %+d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.3d,    -12345 : %.3d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%.6d,    -12345 : %.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%6.3d,   -12345 : %6.3d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%8.6d,   -12345 : %8.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08d,    -12345 : %08d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%08.6d,  -12345 : %08.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%0d,     -12345 : %0d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-.6d,   -12345 : %-.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3d,  -12345 : %-6.3d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6d,  -12345 : %-8.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08d,   -12345 : %-08d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6d, -12345 : %-08.6d.\r\n", -12345);
    SEGGER_RTT_printf(0, "printf Test: %%-0d,    -12345 : %-0d.\r\n", -12345);

    SEGGER_RTT_printf(0, "printf Test: %%x,      0x1234ABC : %x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%+x,     0x1234ABC : %+x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%.3x,    0x1234ABC : %.3x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%.6x,    0x1234ABC : %.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%6.3x,   0x1234ABC : %6.3x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%8.6x,   0x1234ABC : %8.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%08x,    0x1234ABC : %08x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%08.6x,  0x1234ABC : %08.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%0x,     0x1234ABC : %0x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-.6x,   0x1234ABC : %-.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-6.3x,  0x1234ABC : %-6.3x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-8.6x,  0x1234ABC : %-8.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-08x,   0x1234ABC : %-08x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-08.6x, 0x1234ABC : %-08.6x.\r\n", 0x1234ABC);
    SEGGER_RTT_printf(0, "printf Test: %%-0x,    0x1234ABC : %-0x.\r\n", 0x1234ABC);

    SEGGER_RTT_printf(0, "printf Test: %%p,      &_Cnt      : %p.\r\n", &_Cnt);

    SEGGER_RTT_WriteString(0, "###### SEGGER_printf() Tests done. ######\r\n");

    printf("End...\n");
  
    do 
    {
        _Cnt++;
        SEGGER_RTT_printf(0, "printf Test: %%p,      &_Cnt      : %p.\r\n", _Cnt);
    } while (1);
}




/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
