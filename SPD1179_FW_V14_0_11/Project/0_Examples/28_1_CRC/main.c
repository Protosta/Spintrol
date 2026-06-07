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




char                sCRCTestStr[100]         = "CRC calculate access done!";
uint8_t             au8CRCTestStr[100]         = {0xA0, 0xA1, 0xA2, 0xA3, 
0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE};
uint32_t            u32Result;


/**************************************************************************
 *
 * @brief      "CRC calculate access done!" is calculated by mcu firstly, 
 *             then compare the mcu result with online result, if equal, 
 *             test pass.
 *
 * @note       There is no need to use interrupts to get CRC results, because 
 *             CRC results are obtained immediately. If you must use interrupts, 
 *             note that interrupts may triggered twice, once after feed word 
 *             stream and once after feed byte stream.             
 *
 **************************************************************************/


int main(void)
{
    uint32_t u32Result;

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
    
    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  CRC-32/IEEE802P3      0x04C11DB7    0xFFFFFFFF    true     true     0xFFFFFFFF
     */
    CRC_Init(CRC, CRC_MODE_32_IEEE802P3); 
    
    /*
     * When Init Value is not all 0, need to feed special stream(FrameHead)
     * to generate Init Value.
     * for CRC8, stream format is 0xXX000000(low 3 bytes are always 0x00)
     * for CRC16, stream format is 0xXXXX0000(low 2 bytes are always 0x00)
     * for CRC32, stream format is 0xXXXXXXXX
     *
     * At first use, FrameHead must be caculated, step is:
     * 1, Use online CRC web to get target result, for 0xA1 0xA2 0xA3 0xA4 
     * 0xA5 0xA6 0xA7, RC-32/IEEE802P3 result is 0xB2B66EFA;
     *
     * 2, Change FrameHead from 0x00000000 to 0xFFFFFFFF, each time judge 
     * if CRC result is equal to RC-32/IEEE802P3 online result(0xB2B66EFA);
     *
     * 3, When CRC result is equal to online result(0xB2B66EFA), caculation
     * finished and current FrameHead(0x9226f562) is what we need
     */
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[1], 7, 
    0x9226f562);
    if (u32Result != 0xB2B66EFA)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[2], 6, 
    0x9226f562);
    if (u32Result != 0x7FC4C8FD)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[3], 5, 
    0x9226f562);
    if (u32Result != 0x5CF02EA6)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[0], 5, 
    0x9226f562);
    if (u32Result != 0xCDBF173E)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[1], 8, 
    0x9226f562);
    if (u32Result != 0x57D5693B)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[2], 7, 
    0x9226f562);
    if (u32Result != 0xC97C8E3E)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[3], 6, 
    0x9226f562);
    if (u32Result != 0x35E632A4)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[0], 3, 
    0x9226f562);
    if (u32Result != 0xA9FDCB1E)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[1], 4, 
    0x9226f562);
    if (u32Result != 0x5AFEA0A9)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[2], 4, 
    0x9226f562);
    if (u32Result != 0x71CFC321)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, &au8CRCTestStr[3], 4, 
    0x9226f562);
    if (u32Result != 0x4C2ED23A)
    {
        return 0;
    }
    
    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  CRC-16/CCITT          0x1021        0x0000        true     true     0x0000
     */
    CRC_Init(CRC, CRC_MODE_16_CCITT);
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[0], 4);
    if (u32Result != 0xFCE8)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[1], 7);
    if (u32Result != 0xC9F6)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[2], 6);
    if (u32Result != 0xB3BD)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[3], 5);
    if (u32Result != 0x3B29)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[0], 5);
    if (u32Result != 0x8894)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[1], 8);
    if (u32Result != 0xBB32)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[2], 7);
    if (u32Result != 0x479F)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[3], 6);
    if (u32Result != 0x95BA)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[0], 3);
    if (u32Result != 0x3FE8)
    {
        return 0;
    }

    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[1], 4);
    if (u32Result != 0x6250)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[2], 4);
    if (u32Result != 0x41C0)
    {
        return 0;
    }
    
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, &au8CRCTestStr[3], 4);
    if (u32Result != 0xFA3D)
    {
        return 0;
    }

    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  CRC-8/AUTOSAR_2F      0x2F          0xFF          false    false    0xFF 
     */
    CRC_Init(CRC, CRC_MODE_8_AUTOSAR_2F);
    
    /*
     * When Init Value is not all 0, need to feed special stream(FrameHead)
     * to generate Init Value.
     * for CRC8, stream format is 0xXX000000(low 3 bytes are always 0x00)
     * for CRC16, stream format is 0xXXXX0000(low 2 bytes are always 0x00)
     * for CRC32, stream format is 0xXXXXXXXX
     *
     * At first use, FrameHead must be caculated, step is:
     * 1, Use online CRC web to get target result, for "CRC calculate access done!", 
     * CRC-8/AUTOSAR_2F result is 0xC9;
     *
     * 2, Change FrameHead from 0x00000000 to 0xFF000000, each time judge 
     * if CRC result is equal to CRC-8/AUTOSAR_2F online result(0xC9);
     *
     * 3, When CRC result is equal to online result(0xC9), caculation
     * finished and current FrameHead(0x7d000000) is what we need
     */
    u32Result = CRC_CalculateWithInitValueIsNotZero(CRC, (uint8_t *)sCRCTestStr, 
    strlen(sCRCTestStr), 0x7d000000);
    if (u32Result != 0xC9)
    {
        return 0;
    }
    
    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  CRC-16/T10-DIF        0x8BB7        0x0000        false    false    0x0000
     */
    CRC_Init(CRC, CRC_MODE_16_T10_DIF);
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, (uint8_t *)sCRCTestStr, 
    strlen(sCRCTestStr));
    if (u32Result != 0x69A9)
    {
        return 0;
    }  

    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  CRC-16/DNP            0x3D65        0x0000        true     true     0xFFFF
     */
    CRC_Init(CRC, CRC_MODE_16_DNP);
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, (uint8_t *)sCRCTestStr, 
    strlen(sCRCTestStr));
    if (u32Result != 0x8111)
    {
        return 0;
    }

    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  CRC-16/IBM            0x8005        0x0000        true     true     0x0000
     */
    CRC_Init(CRC, CRC_MODE_16_IBM);
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, (uint8_t *)sCRCTestStr, 
    strlen(sCRCTestStr));
    if (u32Result != 0x73F8)
    {
        return 0;
    }
    
    /*
     *  Algorithm             Poly          Init Value    RefIn    RefOut   XorOut 
     *  Custom                0x8005        0x0000        false    false    0xFFFF
     */
    CRC_SetMode(CRC, CRC_MODE_16_IBM);
    CRC_ReverseData(CRC, CRC_DATA_NOT_REVERSE);
    CRC_XorOutputData(CRC, CRC_OUTPUTDATA_XOR_ALL_1);
    u32Result = CRC_CalculateWithInitValueIsZero(CRC, (uint8_t *)sCRCTestStr, 
    strlen(sCRCTestStr));
    if (u32Result != 0x7A3D)
    {
        return 0;
    }

    printf("Test Pass\n");
 
    while(1)
    {

    }
}




/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
