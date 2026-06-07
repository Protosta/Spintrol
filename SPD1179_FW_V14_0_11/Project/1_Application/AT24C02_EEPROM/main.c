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

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif

#include<stdio.h>
#include<stdlib.h>
#include "at24c02.h"

#define         AT24C02_START_ADDR   0x00

uint8_t         au8WriteByteBuf[1] = {0xAB};
uint8_t         au8ReadByteBuf[1] =  {0x00};

uint8_t         au8WritePageBuf[8];
uint8_t         au8ReadPageBuf[8];

uint8_t         au8WriteBuf[256];
uint8_t         au8ReadBuf[256];

ErrorStatus     AT24C02_Byte_Test(void);
ErrorStatus     AT24C02_PageByte_Test(void);
ErrorStatus     AT24C02_MultiByte_Test(void);


/*************************************************************************************************************************
 *
 * @brief      In this case, the IIC controller is used as master and sent data to the AT24C02 
 *             and read these data back to compara, if there is a item not equal with each other, the test FAIL.
 *
 *************************************************************************************************************************/

int main()
{
    CLOCK_InitWithRCO(100000000);

    Delay_Init();

    /*
    * Init the UART
    *
    * 1.Set the GPIO34/35 as UART FUNC
    *
    * 2.Enable the UART CLK
    *
    * 3.Set the rest para
    */
    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);
    
    /* AT24C02 Init */
    AT24C02_Init();

    /* Read and write a byte data to AT24C02 */
    AT24C02_Byte_Test();

    Delay_Ms(10);

    /* Read and write a page byte data to AT24C02 */
    AT24C02_PageByte_Test();
    Delay_Ms(10);

    /* Read and write multiple bytes data to AT24C02 */
    AT24C02_MultiByte_Test();

    while(1)
    {

    }
}




ErrorStatus AT24C02_Byte_Test(void)
{
    ErrorStatus eStatus;
    EEPROM_INFO("Write a byte data: ");
    
    printf("0x%02X \n", au8WriteByteBuf[0]);
    
    /* Send one byte of data to 24C02 */   
    eStatus = AT24C02_WriteByte(EEPROM_PAGE_SIZE, au8WriteByteBuf[0]);
    if(eStatus == ERROR)
    {
        EEPROM_DEBUG("[Write Data ERROR]\n");
        return ERROR;
    }
    else
    {
        EEPROM_DEBUG("[Write Data SUCCESS]\n");
    }
    
    EEPROM_INFO("Read a byte data: ");
   
    /* Read one byte of data from AT24C02 */
    AT24C02_ReadByte(EEPROM_PAGE_SIZE, au8ReadByteBuf);
  
    printf("0x%02X \n", au8ReadByteBuf[0]);
    
    /*  To check the data sent and recieved are the same */
    if(au8ReadByteBuf[0] != au8WriteByteBuf[0])
    {
        EEPROM_INFO("ERROR: AT24C02 inconsistent data was written and read");
        return ERROR;
    }
    else
    {
        EEPROM_INFO("AT24C02 read and write a byte test successful\n");
        return SUCCESS;
    }
}




ErrorStatus AT24C02_PageByte_Test(void)
{
    uint16_t i;
    ErrorStatus eStatus;
    
    EEPROM_INFO("Write a page byte data: ");
    
    for(i = 0; i < 8; i++)
    {
        au8WritePageBuf[i] = i+5;
        
        au8ReadPageBuf[i] = 0x00;
        
        printf("0x%02X ", au8WritePageBuf[i]);
    }
    
    printf("\n\r");
    
    eStatus = AT24C02_WritePage(au8WritePageBuf, AT24C02_START_ADDR, EEPROM_PAGE_SIZE);
    if(eStatus == ERROR)
    {
        EEPROM_DEBUG("[Write Data Error]\n");
        return ERROR;
    }
    else
    {
        EEPROM_DEBUG("[Write Data Success]\n");
    }
    
    EEPROM_INFO("Read a page byte data: ");
    
    AT24C02_Read(au8ReadPageBuf, AT24C02_START_ADDR, EEPROM_PAGE_SIZE);
    
    for (i = 0; i < 8; i++)
    {   
        if(au8ReadPageBuf[i] != au8WritePageBuf[i])
        {
            printf("0x%02X ", au8ReadPageBuf[i]);
                
            EEPROM_INFO("ERROR: AT24C02 inconsistent data was written and read\n");
                
            return ERROR;
        }
        else
        {
            printf("0x%02X ", au8ReadPageBuf[i]);
        }
    }

    printf("\n\r");
    
    EEPROM_INFO("AT24C02 read and write a page byte test successful\n");
        
    return SUCCESS;
}



ErrorStatus AT24C02_MultiByte_Test(void)
{
    uint16_t i;
    ErrorStatus eStatus;

    EEPROM_INFO("Write data:");
    
    /* Initialize au8WriteBuf and au8ReadBuf*/
    for ( i = 0; i < 256; i++ ) 
    {   
        au8WriteBuf[i] = i;
        au8ReadBuf[i] = 0xFF; 
    
        printf("0x%02X ", au8WriteBuf[i]);
    
        if(i % 16 == 15)    
        {
            printf("\n\r");
        }    
    }
    
    /* Write 256 bytes of data sequentially to AT24C02 */
    eStatus = AT24C02_Write(au8WriteBuf, AT24C02_START_ADDR, 256);
    if(eStatus == ERROR)
    {
        EEPROM_DEBUG("[Write Data Error]\n");
        return ERROR;
    }
    else
    {
        EEPROM_DEBUG("[Write Data Success]\n");
    }

    EEPROM_INFO("Read data:");
    
    /* Read 256 bytes of data sequentially from AT24C02 */
    AT24C02_Read(au8ReadBuf, AT24C02_START_ADDR, 256); 

    for (i = 0; i < 256; i++)
    {
        if(au8ReadBuf[i] != au8WriteBuf[i])
        {
            printf("0x%02X ", au8ReadBuf[i]);
            EEPROM_INFO("ERROR: AT24C02 inconsistent data was written and read");

            return ERROR;
        }

        printf("0x%02X ", au8ReadBuf[i]);
    
        if(i % 16 == 15)
        {
            printf("\n\r");
        }
    }
    
    EEPROM_INFO("AT24C02 read and write all test successful\n");

    return SUCCESS;
}
