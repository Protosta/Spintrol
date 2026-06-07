/******************************************************************************
 * @file     at24c02.c
 * @brief    at24c02 firmware functions.
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

#include "at24c02.h"


/******************************************************************************
 * @brief      Initializes I2C interface for AT24C02
 *
 * @param[in]  none
 *
 * @return     ERROR or SUCCESS
 *
 ******************************************************************************/
ErrorStatus AT24C02_Init(void)
{
    /* Config GPIOx as I2C function */
    PIN_SetChannel(GPIOx_SCL_PIN, I2C_SCL_FUNC);
    PIN_SetChannel(GPIOx_SDA_PIN, I2C_SDA_FUNC);

    /*
    * Set Output Strength as 20mA, in case of many more
    * slaves are linking to the master.
    */
    PIN_SetOutStrength(GPIOx_SCL_PIN, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(GPIOx_SDA_PIN, PIN_OUT_STRENGTH_20MA);

    /* Disable All Interrupt */
    I2C_DisableInt(I2C, I2C_INT_ALL);

    /* Clear All Interrupt */
    I2C_ClearInt(I2C, I2C_INT_ALL);

    /* Init I2C as Master */
    I2C_MasterInit(I2C);
    
    I2C_InitFastSpeed(I2C, EEPROM_SPEED, I2C_MASTER);

    /* Enable I2C */
    I2C_Enable(I2C);

    return SUCCESS;
}




/******************************************************************************
 * @brief      Send EEPROM device address and EEPROM memory address to AT24C02
 *
 * @param[in]  I2Cx            :  Select the I2C module
 * @param[in]  eAddrMode       :  Address mode
 *                                Please refer to I2C_AddrModeEnum
 *                                 - \ref I2C_ADDR_7BIT
 *                                 - \ref I2C_ADDR_10BIT
 * @param[in]  u16TargetDevAddr:  EEPROM device address
 * @param[in]  u8MemAddr       :  EEPROM memory address
 *
 * @return     none
 *
 ******************************************************************************/
static void AT24C02_WriteAddr(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode, 
                           uint16_t u16TargetDevAddr, uint8_t u8MemAddr)
{
    /* Set I2C Module Address Mode */
    I2C_SetAddressMode(I2Cx, eAddrMode);

    /* Set EEPROM Device Address*/
    I2C_SetTargetAddress(I2Cx, u16TargetDevAddr);

    /* Write EEPROM Memory Address to TxFIFO */
    I2C_WriteByte(I2Cx, u8MemAddr);
}




/******************************************************************************
 * @brief      Write a Byte data to AT24C02
 *
 * @param[in]  u8Addr:  EEPROM memory address to be written to
 * @param[in]  u8Data:  Byte data to be written to
 *
 * @return     ERROR or SUCCESS
 *
 ******************************************************************************/


ErrorStatus AT24C02_WriteByte(uint8_t u8Addr, uint8_t u8Data)
{
    uint32_t u32Timeout;
    uint8_t u8ResponseAddrFlag;
    uint8_t u8ResponseDataFlag;

    /* Send EEPROM device address and EEPROM memory address to AT24C02 */
    AT24C02_WriteAddr(I2C, I2C_ADDR_7BIT, EEPROM_DEVICE_ADDR, u8Addr);

    u32Timeout = EEPROM_TIMEOUT;

    /* Wait Until TxFIFO Not Full */
    while(!I2C_GetStatus(I2C, I2C_STS_TX_NOT_FULL)) 
    {
        if((u32Timeout--) == 0U)
        {
            EEPROM_DEBUG("[AT24C02_WriteByte FAIL] TxFIFO is always full\n");
            return ERROR;
        }
    }
    
    /* Write a Byte Data to TxFIFO */
    I2C_WriteByte(I2C, u8Data);


    /* Wait for the AT24C02 to complete the write operation */
    Delay_Ms(10);

    u8ResponseAddrFlag = I2C_GetTxAbortSource(I2C, I2C_MST_TX_ABORT_BY_TX_A7B_NAK);
    u8ResponseDataFlag = I2C_GetTxAbortSource(I2C, I2C_MST_TX_ABORT_BY_TX_DATA_NAK);


    if((u8ResponseAddrFlag == 1U) || (u8ResponseDataFlag == 1U))
    {
        EEPROM_DEBUG("[AT24C02_WriteByte FAIL] AT24C02 not response \n");
        return ERROR;
    }


    return SUCCESS;
}




/******************************************************************************
 * @brief      Read a byte data from AT24C02
 *
 * @param[in]  u8Addr :  EEPROM memory address to be read
 * @param[in]  pu8Data:  A pointer to byte data to be read
 *
 * @return     ERROR or SUCCESS
 *                  
 *
 ******************************************************************************/
ErrorStatus AT24C02_ReadByte(uint8_t u8Addr, uint8_t* pu8Data)
{
    uint32_t u32Timeout;
    
    /* Send EEPROM device address and EEPROM memory address to AT24C02 */
    AT24C02_WriteAddr(I2C, I2C_ADDR_7BIT, EEPROM_DEVICE_ADDR, u8Addr);

    /* Write TxFIFO, Send Read Comamnd */
    I2C_MasterReadCmd(I2C);
	
	u32Timeout = EEPROM_TIMEOUT;

    /* Wait Until RxFIFO Not Empty */
    while (!I2C_GetStatus(I2C, I2C_STS_RX_NOT_EMPTY)) 
    {              
        if((u32Timeout--) == 0U)
        {
            EEPROM_DEBUG("[AT24C02_ReadByte FAIL] RxFIFO is always empty\n");
            return ERROR;
        }
    }

    /* Read a byte from the device */
    *pu8Data = I2C_ReadByte(I2C);

    return SUCCESS;
}




/******************************************************************************
 * @brief      Write a page data to AT24C02
 *
 * @param[in]  pu8Data    :  Pointer to the array data to be written
 * @param[in]  u8Addr     :  EEPROM memory address to be written (within a page)
 * @param[in]  u8Size     :  Number of bytes to be written (within a page)
 * 
 * @return     ERROR or SUCCESS
 *
 ******************************************************************************/
ErrorStatus AT24C02_WritePage(uint8_t* pu8Data, uint8_t u8Addr, uint8_t u8Size)
{
    uint8_t i;
    uint32_t u32Timeout;
    uint8_t u8ResponseAddrFlag;
    uint8_t u8ResponseDataFlag;
    
    if((u8Size > 8U) || (((u8Addr & 0x7U) + u8Size) > 8U))
    {
        EEPROM_DEBUG("[AT24C02_WritePage FAIL] More than a page data\n");
        return ERROR;
    }

    AT24C02_WriteAddr(I2C, I2C_ADDR_7BIT, EEPROM_DEVICE_ADDR, u8Addr);

    for(i = 0; i < u8Size; i++)
    {
		u32Timeout = EEPROM_TIMEOUT;
        /* Wait Until TxFIFO Not Full */
        while(!I2C_GetStatus(I2C, I2C_STS_TX_NOT_FULL)) 
        {
            if((u32Timeout--) == 0U)
            {
                EEPROM_DEBUG("[AT24C02_WritePage FAIL] TxFIFO is always full\n");
                return ERROR;
            }
        }

        /* Send the current byte */
        I2C_WriteByte(I2C, pu8Data[i]);
    }

    /* Wait for the AT24C02 to complete the write operation */
    Delay_Ms(10);
    
    /* Query whether the AT24C02 is responding */
    u8ResponseAddrFlag = I2C_GetTxAbortSource(I2C, I2C_MST_TX_ABORT_BY_TX_A7B_NAK);
    u8ResponseDataFlag = I2C_GetTxAbortSource(I2C, I2C_MST_TX_ABORT_BY_TX_DATA_NAK);


    if((u8ResponseAddrFlag == 1U) || (u8ResponseDataFlag == 1U))
    {
        EEPROM_DEBUG("[AT24C02_WritePage FAIL] AT24C02 not response \n");
        return ERROR;
    }


    return SUCCESS;
}




/******************************************************************************
 * @brief      Write data to AT24C02
 *
 * @param[in]  pu8Data    :  Pointer to the array data to be written
 * @param[in]  u8Addr     :  EEPROM memory address to be written
 * @param[in]  u16Size    :  Number of bytes to be written
 *
 * @return     ERROR or SUCCESS
 *                  
 *
 ******************************************************************************/
ErrorStatus AT24C02_Write(uint8_t* pu8Data, uint8_t u8Addr, uint16_t u16Size)
{
    ErrorStatus eStatus = SUCCESS;
    uint8_t  u8AddrOffset; 
    uint8_t  u8BegPgNum;
    uint8_t  u8EndPgNum;
    uint8_t  u8AddrCur;
    uint8_t* pu8Buf;
    uint8_t  u8Count;
    uint8_t  i;
    
    u8AddrCur = u8Addr;
    pu8Buf = pu8Data;
    
    if(((u8Addr + u16Size) > 256U) || (u16Size > 256U))
    {
        EEPROM_DEBUG("[AT24C02_Write FAIL] Function argument error");
        return ERROR;
    }

    /* Get page number of start address and end address */
    u8BegPgNum = u8Addr / EEPROM_PAGE_SIZE;
    u8EndPgNum = (u8Addr + u16Size - 1) / EEPROM_PAGE_SIZE;
    
    /* Both start address and end address are within the same page */
    if(u8BegPgNum == u8EndPgNum)
    {
        return ( AT24C02_WritePage(pu8Data, u8Addr, u16Size) );
    }
    /* Start address and end address are not in the same page */
    else
    {
        /* For first page */
        u8AddrOffset = u8Addr % EEPROM_PAGE_SIZE;
        u8Count = EEPROM_PAGE_SIZE - u8AddrOffset;
        
        eStatus = AT24C02_WritePage(pu8Buf, u8Addr, u8Count);
        if(eStatus == ERROR)
        {
            EEPROM_DEBUG("[AT24C02_WritePage FAIL]");
            return ERROR;
        }
        
        pu8Buf += u8Count;
        u8AddrCur += u8Count;
        
        for(i = u8BegPgNum + 1; i <= u8EndPgNum; i++)
        {
            /* For last page */
            if(i == u8EndPgNum)
            {
                u8Count = (u16Size - u8Count) % EEPROM_PAGE_SIZE;
                
                /* If u8Count is 0, the last page has a page data to be writen*/
                if(u8Count == 0U)
                {
                    u8Count = EEPROM_PAGE_SIZE;
                }
                
                return( AT24C02_WritePage(pu8Buf, u8AddrCur, u8Count) );
            }
            else
            {
                eStatus = AT24C02_WritePage(pu8Buf, u8AddrCur, EEPROM_PAGE_SIZE);
                if(eStatus == ERROR)
                {
                    EEPROM_DEBUG("[AT24C02_WritePage FAIL]");
                    return ERROR;
                }
                
                pu8Buf += EEPROM_PAGE_SIZE;
                u8AddrCur += EEPROM_PAGE_SIZE;
            }
        }
    }

    return SUCCESS;
}




/******************************************************************************
 * @brief      Read data from AT24C02
 *             Random read and sequential read are supported
 *
 * @param[in]  pu8Data    :  Pointer to the array that hold data read from AT24C02
 * @param[in]  u8Addr     :  EEPROM memory address to be read
 * @param[in]  u16Size    :  Number of bytes to be read
 *
 * @return     ERROR or SUCCESS
 *
 *
 ******************************************************************************/
ErrorStatus AT24C02_Read(uint8_t* pu8Data, uint8_t u8Addr, uint16_t u16Size)
{
    uint16_t i;
    uint32_t u32Timeout;

    if(((u8Addr + u16Size) > 256U) || (u16Size > 256U))
    {
        EEPROM_DEBUG("[AT24C02_Read FAIL] Function argument error");
        return ERROR;
    }


    AT24C02_WriteAddr(I2C, I2C_ADDR_7BIT, EEPROM_DEVICE_ADDR, u8Addr);

    /* While there is data to be read */
    for(i = 0; i < u16Size; i++)  
    {                 
        /* Write TxFIFO, Send Read Comamnd */
        I2C_MasterReadCmd(I2C);
		
		u32Timeout = EEPROM_TIMEOUT;

        /* Wait Until RxFIFO Not Empty */
        while (!I2C_GetStatus(I2C, I2C_STS_RX_NOT_EMPTY)) 
        {           
            if((u32Timeout--) == 0U)
            {
                EEPROM_DEBUG("[AT24C02_Read FAIL] RxFIFO is always empty\n");
                return ERROR;
            }
        }

        /* Read a byte from the device */
        pu8Data[i] = I2C_ReadByte(I2C);
    }
    
    return SUCCESS;
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
