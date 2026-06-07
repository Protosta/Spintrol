#include "target.h"
#include "iap.h"




BOOL TARGET_IsUartRxFifoEmpty(UART_REGS* pstUart)
{
    BOOL eBool = FALSE;
    uint32_t u32RxNotEmptyFlag = 0U;

    u32RxNotEmptyFlag = UART_GetStatus(pstUart, UART_STS_RX_NOT_EMPTY);

    if (u32RxNotEmptyFlag == 0U)
    {
        eBool = TRUE;
    }

    return eBool;
}




BOOL TARGET_IsUartTxFifoEmpty(void)
{
    BOOL eBool = FALSE;
    uint32_t u32TxEmptyFlag = 0U;

    u32TxEmptyFlag = UART_GetStatus(CONFIG_UART, UART_STS_TX_EMPTY);

    if (u32TxEmptyFlag != 0U)
    {
        eBool = TRUE;
    }

    return eBool;

}




BOOL TARGET_IsLINIdMatch(void)
{
    BOOL eBool = FALSE;
    uint32_t u32IdMatchFlag = 0U;

    u32IdMatchFlag = UART_GetIntRawFlag(CONFIG_LIN, UART_INT_LIN_ID_MATCH);

    if (u32IdMatchFlag != 0U)
    {
        eBool = TRUE;
    }

    return eBool;

}




void TARGET_UartSendDone(UART_REGS* pstUart)
{
	uint32_t i = 0U ;
	for ( i = 0U ; i < 10000U ; i++)
	{
	    if( UART_GetStatus(pstUart, UART_STS_TX_BUSY) == 0U )
		{
			break;
		}
    }
}




void TARGET_RestoreUart()                           
{                                                       
    TARGET_UartSendDone(CONFIG_UART);                                             
    TARGET_RESTORE_UART_PIN();                          
    WRITE_REG(CONFIG_UART->UARTCTL,0x00);               
    WRITE_REG(CONFIG_UART->UARTCTL,0x00);               
    WRITE_REG(CONFIG_UART->UARTBDCNT,0x00000010);       
    CLOCK_DisableModule(CONFIG_UART_CLOCK);             
}




void TARGET_RestoreLin()                           
{                                                       
    TARGET_UartSendDone(CONFIG_LIN);
    TARGET_RESTORE_LIN_PIN();
    WRITE_REG(CONFIG_LIN->UARTCTL, 0);
    WRITE_REG(CONFIG_LIN->UARTCTL, 0);
    WRITE_REG(CONFIG_UART->UARTBDCNT,0x00000010);
    WRITE_REG(CONFIG_LIN->LINCTL, 0);
    WRITE_REG(CONFIG_LIN->LINIDFILT, 0);     
    CLOCK_DisableModule(CONFIG_LIN_CLOCK);
		HV_Reset();         
}




void TARGET_DisableWDT(void)
{
    WDT_WALLOW(WDT0);
    WDT_WALLOW(WDT1);
    WDT_Disable(WDT0);
    WDT_Disable(WDT1);
    WDT_WDIS(WDT0);
    WDT_WDIS(WDT1);
}




void TARGET_RecordErrorInfo(uint8_t u8Bit4Num, uint8_t u8ByteValue)
{
    uint32_t u32tmp = 0U;
    uint32_t u32Mask = 0U;
    uint32_t u32Value = 0U;
	  u8ByteValue &= 0x0FU;
	  u32Mask = (0xFU<<(u8Bit4Num*4U));
    u32Value =  (u8ByteValue<<(u8Bit4Num*4U));
    u32tmp = READ_REG(SYSTEM->NVREG0);
    u32tmp &= ~u32Mask;
    u32tmp |= u32Value;
    WRITE_REG(SYSTEM->NVREG0, u32tmp);
#if 0
    IAP_InitUART();
    printf("EK = 0x%x\n",SYSTEM->NVREG0);
#endif
}




uint32_t BufferToUint32_LE(const uint8_t p_p8Input[])
{

    uint32_t t_u32Temp = 0U ;

    if(NULL!=p_p8Input)
    {

        t_u32Temp = (uint32_t)*(p_p8Input+3);
        t_u32Temp = ( t_u32Temp<<8 ) + *(p_p8Input+2);
        t_u32Temp = ( t_u32Temp<<8 ) + *(p_p8Input+1);
        t_u32Temp = ( t_u32Temp<<8 ) + *(p_p8Input);
    }
    else
    {

        t_u32Temp = 0U;
    }

    return t_u32Temp;
}




uint16_t BufferToUint16_LE(const uint8_t p_p8Input[])
{

    uint16_t t_u16Temp = 0U ;

    if(NULL!=p_p8Input)
    {

        t_u16Temp = (uint16_t)*(p_p8Input+1);
        t_u16Temp = (uint16_t)( t_u16Temp<<8 ) + *(p_p8Input);
    }
    else
    {

        t_u16Temp = 0U;
    }

    return t_u16Temp;
}




FlashOperationStatus TARGET_FlashRead(uint32_t u32FlashAddr,uint32_t u32SizeOfWords,uint8_t* p8Buffer)
{
	
	TARGET_MemCpy((void*)p8Buffer,(void*)u32FlashAddr,u32SizeOfWords*4U);
	return FLASH_OP_SUCCESS;
}



void TARGET_CalculateCRC16(uint32_t u32Startaddr,uint32_t u32Size,uint32_t* p32Crc)
{
    CRC_Init(CRC, CRC_MODE_16_CCITT);
    *p32Crc = CRC_CalculateWithInitValueIsZero(CRC, (uint8_t*)u32Startaddr, u32Size);
}           





BOOL TARGET_GetJumpFunAddr(uint32_t u32StartAddr , uint32_t *p32Entry)
{
	BOOL eBool = FALSE;
	if (p32Entry != NULL)
	{
        *p32Entry =  *(__IO uint32_t *)(u32StartAddr + 4);
        
        if (TARGET_ASSERT_STARTADDR_IN_MAIN_C_FLASH(*p32Entry,1))
        {
            eBool = TRUE;
        }
	}
	return eBool;
}





ErrorStatus TARGET_UartReceive(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout)
{
    BOOL eBoolTmp = FALSE;
    uint32_t i = 0U;
    uint32_t j = 0U;

    for(i = 0U; i < u32Count; i++)
    {
        /* Wait until data is available in RBR or the FIFO */
        for(j = u32timeout; j > 0; j--)
        {
            eBoolTmp = TARGET_IsUartRxFifoEmpty(CONFIG_UART);
            if (eBoolTmp == TRUE) 
            {
                continue;
            }
            else
            {
                break;
            }
        }

        /* Timeout */
        if(j == 0)
        {
            return ERROR;
        }

        /* Read one byte data from UART peripheral */
        au8Buf[i] = UART_ReadByte(CONFIG_UART);
    }

    return SUCCESS;
}




ErrorStatus TARGET_UartSend(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout)
{
    BOOL eBoolTmp = FALSE;
    volatile uint32_t i = 0U;
    volatile uint32_t j = 0U;

    for(i = 0U; i < u32Count; i++)
    {
        /* Send byte data */
        UART_WriteByte(CONFIG_UART,au8Buf[i]);
        /* Wait until data is available in RBR or the FIFO */
        for(j = u32timeout; j > 0; j--)
        {
            eBoolTmp = TARGET_IsUartTxFifoEmpty();
            if (eBoolTmp == TRUE) 
            {
                break;
            }
            else
            {
                continue;
            }
        }
        /* Timeout */
        if(j == 0)
        {
            return ERROR;
        }
    }


    return SUCCESS;
}




ErrorStatus TARGET_LinSend(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout)
{
    uint8_t u8TmpArr[TARGET_LIN_DATA_WIDTH];
    uint32_t i = 0U;
    uint32_t j = 0U;
    BOOL eBoolTmp = FALSE;
        
    LIN_SetIDFilter(CONFIG_LIN, CONFIG_LIN_SEND_ID, CONFIG_LIN_IDMASK);

    for (i = 0U ; i < u32Count ; i+=TARGET_LIN_DATA_WIDTH)
    {
        if ((i + TARGET_LIN_DATA_WIDTH) > u32Count)
        {

            TARGET_MemSet(&u8TmpArr[0], 0 ,TARGET_LIN_DATA_WIDTH);
            TARGET_MemCpy(u8TmpArr, &au8Buf[i], u32Count - i );


            for(j = u32timeout; j > 0; j--)
            {
                eBoolTmp = TARGET_IsLINIdMatch();
                if (eBoolTmp == TRUE ) 
                {

                    /* Clear id match flag */
                    UART_ClearInt(CONFIG_LIN, UART_INT_LIN_ID_MATCH);  

                    /* Set the respond mode */
                    LIN_SetResponse(CONFIG_LIN, LIN_RESPONSE_TX);

                    for (j = 0; j < TARGET_LIN_DATA_WIDTH; j++)
                    {
                        UART_WriteByte(CONFIG_LIN, u8TmpArr[j]);
												while(UART_GetTxFIFOLevel(CONFIG_LIN) != 0)
												{}
                    }

                    /* Send frame */
                    SET_BITS(CONFIG_LIN->LINCTL, LINCTL_TXCHKSUM_TRANSMIT);
                    break;
                }
                else
                {
                    continue;
                }
            }
            /* Timeout */
            if(j == 0)
            {
                return ERROR;
            }
            break;
        }
        else
        {
            for(j = u32timeout; j > 0; j--)
            {
                eBoolTmp = TARGET_IsLINIdMatch();
                if (eBoolTmp == TRUE) 
                {
                    /* Clear id match flag */
                    UART_ClearInt(CONFIG_LIN, UART_INT_LIN_ID_MATCH);  

                    /* Set the respond mode */
                    LIN_SetResponse(CONFIG_LIN, LIN_RESPONSE_TX);

                    for (j = 0; j < TARGET_LIN_DATA_WIDTH; j++)
                    {
                        UART_WriteByte(CONFIG_LIN, au8Buf[(i + j)]);

                    }

                    /* Send frame */
                    SET_BITS(CONFIG_LIN->LINCTL, LINCTL_TXCHKSUM_TRANSMIT);
										
										while(UART_GetTxFIFOLevel(CONFIG_LIN) != 0)
										{}
                    break;
                }
                else
                {
                    continue;
                }
            }
            /* Timeout */
            if(j == 0)
            {
                return ERROR;
            }
        }

    }
    
    return SUCCESS;
}




ErrorStatus TARGET_LinReceive(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout)
{
    BOOL eBoolTmp = FALSE;
    uint32_t i = 0U;
    uint32_t j = 0U;
    uint32_t z = 0U;
        
    LIN_SetIDFilter(CONFIG_LIN, CONFIG_LIN_RECEIVE_ID, CONFIG_LIN_IDMASK);

    for(i = 0U; i < u32Count; i += TARGET_LIN_DATA_WIDTH)
    {
        /* Wait until data is available in RBR or the FIFO */
        for(j = u32timeout; j > 0; j--)
        {
            eBoolTmp = TARGET_IsLINIdMatch();

            if (eBoolTmp == TRUE) 
            {
                break;
            }
            else
            {
                continue;
            }
        }

        /* Timeout */
        if(j == 0)
        {
            return ERROR;
        }

        /* Clear id match flag */
        UART_ClearInt(CONFIG_LIN, UART_INT_LIN_ID_MATCH); 
      
        /* Set the respond mode */
        LIN_SetResponse(CONFIG_LIN, LIN_RESPONSE_RX);

        
        for(j = u32timeout; j > 0; j--)
        {
            if ( UART_GetIntRawFlag(CONFIG_LIN, UART_INT_RX_REQ) != 0x0) 
            {
                break;
            }
            else
            {
                ;
            }
        }

        /* Timeout */
        if(j == 0)
        {
            return ERROR;
        }        

        for (z = 0; z < TARGET_LIN_DATA_WIDTH; z++)
        {
            au8Buf[i+z] = UART_ReadByte(CONFIG_LIN);
        }
    }

    return SUCCESS;
}




BOOL TARGET_IsEnableUARTIAP(void)
{
    BOOL eRet = FALSE;

    #if IAP_INTERFACE == 0
        eRet = TRUE;
    #endif

    return eRet ;
}




BOOL TARGET_IsEnableLINIAP(void)
{
    BOOL eRet = FALSE;
    #if IAP_INTERFACE == 1
        eRet = TRUE;
    #endif

    return eRet ;
}
