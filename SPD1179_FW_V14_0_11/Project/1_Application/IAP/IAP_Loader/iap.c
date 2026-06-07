/******************************************************************************
* @file     iap.c
* @brief    This file contains functions related to IAP.
* @version  V14.0.11
* @date     30-March-2026
*
* @note
* Copyright (C) [2014-2024] Spintrol Electronic Technology (Shanghai) Co., Ltd.
* All rights reserved.
*
* @attention
* THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION REGARDING
* THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM. SPINTROL SHALL NOT BE
* LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL DOES NOT GUARANTEE THE
* CORRECTNESS OF THIS SOFTWARE AND RESERVES THE RIGHT TO MODIFY THE SOFTWARE
* WITHOUT NOTIFICATION.
*
******************************************************************************/

#include "target.h"
#include "comprotocol.h"
#include <stdint.h>
#include "iap.h"



static uint16_t IAP_GetCommunicationContent(ST_FFFE_STRU *pFFFEStatStru,uint8_t arr8RawDataRcv[],uint16_t t_u16RcvMaxSize, uint32_t u32Timeout);
static BOOL IAP_StoreEnv(void);
static void IAP_ReportStatus(IAP_Report_enum enumReport , uint8_t u8Report);
static uint32_t IAP_GetCmd(uint8_t* p8Cmd , uint8_t* p8Buf, uint32_t u32BuffMaxLen,uint32_t u32Timeout);
BOOL IAP_ErasePartition(uint32_t u32Addr);
static IAP_Status_enum IAP_HandShake(uint32_t u32Timeout,uint32_t* p32PackTotalNum,uint8_t* p8Error);
static IAP_Status_enum IAP_Communication(uint32_t u32Timeout , uint32_t u32PackTotalNum,uint8_t* p8Error);
static void  IAP_DownloadImage(uint32_t u32Timeout);
static void IAP_RestoreEnv(void);
static IAP_ComTypeEnum IAP_CheckMode(uint32_t* p32Timout);
void IAP_InitUART(void);
static void IAP_InitLIN(void);
static uint32_t g_u32IapEnvBuffer[IAP_ENV_BUFFER_SIZE];
static ST_FFFE_STRU g_IapFFFERcvSt ;
static uint8_t g_a8FFFEBuffer[IAP_FLASHBUFFER_SIZE];
IAP_ComInterfaceDef g_IapComManager;


static uint16_t IAP_GetCommunicationContent(ST_FFFE_STRU *pFFFEStatStru,uint8_t arr8RawDataRcv[],uint16_t t_u16RcvMaxSize, uint32_t u32Timeout)
{
    uint16_t u16RetLen = 0U;
    ErrorStatus eStatus = ERROR;
    uint8_t u8DataBuffer[TARGET_LIN_DATA_WIDTH] = {0};
    uint8_t u8Width = 0U;
    uint8_t i = 0U;
    uint16_t u16UnpackByte = 0U;
    if (pFFFEStatStru != NULL)
    {
        if (g_IapComManager.eComType == IAP_BY_UART)
        {
            u8Width = TARGET_UART_DATA_WIDTH;
        }
        else if (g_IapComManager.eComType == IAP_BY_LIN)
        {
            u8Width = TARGET_LIN_DATA_WIDTH;
        }
        else
        {
            ;
        }

        if (u8Width != 0U)
        {
            do
            {
                eStatus = g_IapComManager.IapReceive(&u8DataBuffer[0], u8Width, u32Timeout);
                if (eStatus == SUCCESS)
                {
                    for (i = 0 ; i < u8Width ; i++)
                    {

                        u16RetLen = FRAME_DataPrtlUnpack(pFFFEStatStru,u8DataBuffer[i], arr8RawDataRcv,t_u16RcvMaxSize);
                        if (u16RetLen > 0U)
                        {
                            break;
                        }
                    }                 

                    if (u16RetLen > 0)
                    {
                        break;
                    }
                }

                u16UnpackByte += u8Width;
                if (u16UnpackByte >= IAP_DATA_STORM_OVWEFLOW_BYTE)
                {
                    /*!< The consecutive invalid packet threshold has been reached  */
                    eStatus = ERROR;
                }
            }
            while(eStatus == SUCCESS);
        }
    }

    return u16RetLen;
}




static BOOL IAP_StoreEnv(void)
{
    EnumReturn enumRet = EnumReturnFalse;

    /* step1: if need software init */
    enumRet = FRAME_DataPrtlInit(&g_IapFFFERcvSt , g_a8FFFEBuffer,IAP_FLASHBUFFER_SIZE);
    if (EnumReturnTrue != enumRet)
    {
        TARGET_RecordErrorInfo(IAP_FLOW_4BIT_2_NUM,0x01);
       return FALSE;
    }

    /* step2: save wdt0&1 setting */
		g_u32IapEnvBuffer[0] = WDT0->WDTCTL;
    g_u32IapEnvBuffer[1] = WDT1->WDTCTL;
    TARGET_DisableWDT();

    return TRUE;
}




static void IAP_ReportStatus(IAP_Report_enum enumReport , uint8_t u8Report)
{
    uint8_t u8DataBuffer[2] = {0};

    if (g_IapComManager.IapSend != NULL)
    {
        u8DataBuffer[0] = enumReport;
        u8DataBuffer[1] = u8Report;

        g_IapComManager.IapSend( u8DataBuffer,2U,IAP_SEND_TIMEOUT_MS);  
    }
}




static uint32_t IAP_GetCmd(uint8_t* p8Cmd , uint8_t* p8Buf, uint32_t u32BuffMaxLen,uint32_t u32Timeout)
{
    uint32_t u32RetLen = 0U;
    uint32_t u32TmpLen = 0U;
    uint16_t u16PackLen = 0U;
    uint8_t u8Cmd;
    uint8_t a8UnpackBuffer[IAP_FLASHBUFFER_SIZE];
    uint16_t u16UnpackLen = 0U;
    uint16_t u16Crc1 = 0U ;
    uint32_t u32Crc2 = 0U;

    u16UnpackLen = IAP_GetCommunicationContent(&g_IapFFFERcvSt, a8UnpackBuffer, IAP_FLASHBUFFER_SIZE, u32Timeout);

    if (u16UnpackLen > 0)
    {
        u16PackLen = BufferToUint16_LE(&a8UnpackBuffer[0]);

        if (u16PackLen == (u16UnpackLen-IAP_PACK_CMD_OFFSET))
        {
            u8Cmd = a8UnpackBuffer[2];

            u16Crc1 = BufferToUint16_LE(&a8UnpackBuffer[u16UnpackLen-IAP_PACK_CRC_LEN]);

            TARGET_CalculateCRC16((uint32_t)&a8UnpackBuffer[2],u16UnpackLen-IAP_PACK_CRC_LEN-IAP_PACK_CMD_OFFSET,&u32Crc2);      

            if (u16Crc1 ==  u32Crc2)
            {
                *p8Cmd = u8Cmd;
                u32TmpLen = u16UnpackLen-IAP_PACK_DATA_ALL_OFFSET-IAP_PACK_CRC_LEN;
                if (u32TmpLen <= u32BuffMaxLen)
                {
                    TARGET_MemCpy(p8Buf,&a8UnpackBuffer[IAP_PACK_DATA_ALL_OFFSET],u32TmpLen);
                    u32RetLen = u32TmpLen;
                }
                else
                {
                    IAP_ReportStatus(REPORT_NACK,IAP_ERROR_MAX_LEN);
                }
            }
            else
            {
                IAP_ReportStatus(REPORT_NACK,IAP_ERROR_DATA_CRC);    
            }
        }
        else
        {
            IAP_ReportStatus(REPORT_NACK,IAP_ERROR_ERROR_LEN);   
        }
    }
    
    return u32RetLen;
}




static IAP_Status_enum IAP_HandShake(uint32_t u32Timeout,uint32_t* p32PackTotalNum,uint8_t* p8Error)
{
    uint8_t u8Error = 0U;
    IAP_Status_enum enumStatus = IAP_STATUS_WAIT_FIRST_HANDSHAKE;
    uint8_t u8Cmd = 0U;
    uint32_t u32RetLen = 0U;
    BOOL eContinue = FALSE;
    uint8_t a8Buf[IAP_CMD_BUFFER_SIZE];
    uint32_t u32PackTotalNum1 = 0U;
    uint32_t u32PackTotalNum2 = 0U;

    do
    {
        u32RetLen = IAP_GetCmd(&u8Cmd,a8Buf,IAP_CMD_BUFFER_SIZE,u32Timeout);

        if (u32RetLen != 0)
        {
            eContinue = TRUE;
            switch(enumStatus)
            {
                case IAP_STATUS_WAIT_FIRST_HANDSHAKE:
                {
                    if(IAP_CMD_FIRST_HANDSHAKE == u8Cmd )
                    {
                        /*  get u32PackTotalNum1 */
                        u32PackTotalNum1 = BufferToUint16_LE(&a8Buf[IAP_PACKNUM_OFFSET_FROM_DATA_ALL]);
                        IAP_ReportStatus(REPORT_ACK_HANDSHAKE,IAP_CMD_FIRST_HANDSHAKE);
                        enumStatus = IAP_STATUS_WAIT_SECOND_HANDSHAKE;
                    }
                    else
                    {
                        u8Error = IAP_ERROR_CMD_3;
                        eContinue = FALSE;   /* break do while*/
                    }
                    break;
                }
                case IAP_STATUS_WAIT_SECOND_HANDSHAKE:
                {
                    if(IAP_CMD_SECOND_HANDSHAKE == u8Cmd )
                    {
                        /*  get  u32PackTotalNum2*/
                        u32PackTotalNum2 = BufferToUint16_LE(&a8Buf[IAP_PACKNUM_OFFSET_FROM_DATA_ALL]);

                        if (u32PackTotalNum1 == u32PackTotalNum2)
                        {
                            *p32PackTotalNum = u32PackTotalNum1;
                            enumStatus = IAP_STATUS_HANDSHAKE_SUCCESS;
                            IAP_ReportStatus(REPORT_ACK_HANDSHAKE,IAP_CMD_SECOND_HANDSHAKE);
                        }
                        else
                        {
                            u8Error = IAP_ERROR_HANDSHAKE_PACKNUM;
                        }
                    }
                    else
                    {
                        u8Error = IAP_ERROR_SECOND_HANDSHAKE_CMD;
                    }
                    eContinue = FALSE;   /* break do while*/
                    break;
                }
                default:
                {
                    u8Error = IAP_ERROR_HANDSHAKE_STATUS;
                    eContinue = FALSE;   /* break do while*/
                }
            }
        }
        else
        {
            /* timeout */
            if(IAP_STATUS_WAIT_FIRST_HANDSHAKE == enumStatus)
            {
                u8Error = IAP_ERROR_FIRST_HANDSHAKE_TIMEOUT;
            }
            else if (IAP_STATUS_WAIT_SECOND_HANDSHAKE == enumStatus)
            {
                u8Error = IAP_ERROR_SECOND_HANDSHAKE_TIMEOUT;
            }
            eContinue = FALSE;  /* break do while*/
        }
    } while (eContinue == TRUE);

    *p8Error = u8Error;
    return enumStatus;
}




static IAP_Status_enum IAP_Communication(uint32_t u32Timeout , uint32_t u32PackTotalNum,uint8_t* p8Error)
{

    uint8_t u8Error = 0U;
    IAP_Status_enum enumStatus = IAP_STATUS_HANDSHAKE_SUCCESS;
    uint8_t u8Cmd;
    uint32_t u32RetLen = 0;
    #ifdef __CC_ARM
        __align(4) uint8_t a8Buf[IAP_CMD_BUFFER_SIZE];
    #elif defined(__ICCARM__)
        uint8_t __attribute__((aligned(4))) a8Buf[IAP_CMD_BUFFER_SIZE];
    #endif
    uint32_t u32Buflen = 0 ;
    uint16_t u16TmpSN = 0;
    uint16_t u16LastSN = 0 ;
    BOOL eFirstSN = TRUE;
    BOOL eRightSN = FALSE;
    BOOL eContinue = FALSE;
    uint32_t u32WriteAddr = 0U;

    do
    {
        u32RetLen = IAP_GetCmd(&u8Cmd,a8Buf,IAP_CMD_BUFFER_SIZE,u32Timeout);

        if (0 != u32RetLen)
        {
            u32Buflen = u32RetLen;
            eContinue = TRUE;
            if ( IAP_IS_AVAILD_CMD(u8Cmd))
            {
                /* get sn from  a8Buf u8TmpSN == a8Buf[3~4] */
                u16TmpSN = BufferToUint16_LE(&a8Buf[IAP_PACKSN_OFFSET_FROM_DATA_ALL]);
                if (TRUE == eFirstSN )
                {
                    if (u16TmpSN == IAP_FIRST_SN)
                    {
                        eFirstSN = FALSE;
                        u16LastSN = u16TmpSN;
                        eRightSN = TRUE;
                        enumStatus = IAP_STATUS_TRANSFER_DATA;
                    }
                    else
                    {
                        /* first sn is not 0 error */
                        u8Error = IAP_ERROR_PACK_SN_1;
                        eContinue = FALSE;  /* break */
                        eRightSN = FALSE;
                    }
                }
                else
                {
                    if(u16TmpSN == u16LastSN + 1)
                    {
                        u16LastSN = u16TmpSN;
                        eRightSN = TRUE;
                    }
                    else
                    {
                        /* sn is not has continuity */
                        u8Error = IAP_ERROR_PACK_SN_2;
                        eContinue = FALSE;  /* break */
                        eRightSN = FALSE;
                    }
                }

                if( (TRUE == eRightSN) && (u16TmpSN <= u32PackTotalNum))
                {
                    if (u8Cmd == IAP_CMD_WRITE_DATA)
                    {

                        /* get write_addr from a8Buf */
                        u32WriteAddr = BufferToUint32_LE(&a8Buf[IAP_WRITECMD_ADDR_OFFSET_FROM_DATA_ALL]);

                        if (TARGET_ASSERT_STARTADDR_IN_MAIN_C_FLASH(u32WriteAddr,(u32Buflen-IAP_WRITECMD_DATA_OFFSET_FROM_DATA_ALL)))
                        {
                            /*!< get data_len from a8Buf | check write_addr and data_len right | get data[] from  a8Buf | write date to flash*/
                            /*!< check wrong set u8Error ,continue FALSE */
 
                            if ( ((u32Buflen-IAP_WRITECMD_DATA_OFFSET_FROM_DATA_ALL)%8U) == 0U)
                            {
                                if (FLASH_OP_SUCCESS == pHWLIB->FLASHC_Program((uint32_t*)&a8Buf[IAP_WRITECMD_DATA_OFFSET_FROM_DATA_ALL], u32WriteAddr,
                                                                (u32Buflen-IAP_WRITECMD_DATA_OFFSET_FROM_DATA_ALL)/4U))
                                {
                                    IAP_ReportStatus(REPORT_ACK,(uint8_t)u16TmpSN);
                                }
                                else
                                {
                                    TARGET_RecordErrorInfo(IAP_BOOT_FLASH_4BIT_NUM, RECORD_FLASH_WRITE_ERROR_1);
                                    u8Error = IAP_ERROR_WRITE_FLASH;
                                    eContinue = FALSE;  /* break */
                                }
                            }
                            else
                            {
                                    u8Error = IAP_ERROR_WRITE_AGLIN;
                                    eContinue = FALSE;  /* break */                                
                            }
                        }
                        else
                        {
                            u8Error = IAP_ERROR_ADDR_VAILD;
                            eContinue = FALSE;  /* break */
                        }
                    }
                    else if (u8Cmd == IAP_CMD_ERASE_DATA)
                    {

                        /* get write_addr from a8Buf */
                        u32WriteAddr = BufferToUint32_LE(&a8Buf[IAP_WRITECMD_ADDR_OFFSET_FROM_DATA_ALL]);
                        if (TARGET_ASSERT_STARTADDR_IN_MAIN_C_FLASH(u32WriteAddr,1))
                        {

                            /*!< get data_len from a8Buf | check write_addr and data_len right | get data[] from  a8Buf | write date to flash*/
                            /*!< check wrong set u8Error ,continue FALSE */
                            if (FLASH_OP_SUCCESS == pHWLIB->FLASHC_EraseSector(u32WriteAddr))
                            {
                                IAP_ReportStatus(REPORT_ACK,(uint8_t)u16TmpSN);
                            }
                            else
                            {
                                TARGET_RecordErrorInfo(IAP_BOOT_FLASH_4BIT_NUM, RECORD_FLASH_ERASESECTOR_ERROR_1);
                                u8Error = IAP_ERROR_ERASE_FLASH;
                                eContinue = FALSE;  /* break */
                            }
                        }
                        else
                        {
                            u8Error = IAP_ERROR_ADDR_VAILD;
                            eContinue = FALSE;  /* break */
                        }
                    }
                    else
                    {
                        u8Error = IAP_ERROR_CMD_2;
                        eContinue = FALSE;  /* break */
                    }

                    if (u32PackTotalNum == u16TmpSN)
                    {
                        eContinue = FALSE;  /* break */
                        if (u8Error == 0U)
                        {
                            enumStatus = IAP_STATUS_TRANSFER_COMPLETE;
                        }
                    }
                }
                else
                {
                    u8Error = IAP_ERROR_PACK_SN_3;
                    eContinue = FALSE;  /* break */
                }
            }
            else
            {
                u8Error = IAP_ERROR_CMD_1;
                eContinue = FALSE;  /* break */
            }

        }
        else
        {
            /* timeout */
            u8Error = IAP_ERROR_WRITE_DATA_TIMEOUT;
            eContinue = FALSE;  /* break */
        }
    } while (eContinue == TRUE);

    *p8Error = u8Error;
    return enumStatus;
}




static void IAP_DownloadImage(uint32_t u32Timeout)
{
    // int retTmp = -1;
    uint8_t u8ReportError = 0;
    IAP_Status_enum enumStatus = IAP_STATUS_WAIT_FIRST_HANDSHAKE;
    uint32_t u32PackTotalNum = 0xFFFF ;
    
    /* step1: handShake */
    enumStatus = IAP_HandShake(u32Timeout*IAP_CMD_TIME_OUT_MILLISECOND, &u32PackTotalNum, &u8ReportError);

    if (IAP_STATUS_HANDSHAKE_SUCCESS == enumStatus)
    {
				/* step2: transfer data */
				enumStatus = IAP_Communication(IAP_DOWNLOAD_EACHSN_TIMEOUT_MS, u32PackTotalNum, &u8ReportError);

				if (IAP_STATUS_TRANSFER_COMPLETE == enumStatus)
				{
								;
				}
				else
				{
						TARGET_RecordErrorInfo(IAP_FLOW_4BIT_2_NUM,0x06);
						IAP_ReportStatus(REPORT_NACK,u8ReportError);
				}
    }
    else if (IAP_STATUS_WAIT_FIRST_HANDSHAKE != enumStatus)
    {
        TARGET_RecordErrorInfo(IAP_FLOW_4BIT_2_NUM,0x07);
        IAP_ReportStatus(REPORT_NACK,u8ReportError);
    }
    else
    {
        /*!< enumStatus is IAP_STATUS_WAIT_FIRST_HANDSHAKE, do not send anything */
        ;
        //TARGET_RecordErrorInfo(IAP_FLOW_4BIT_2_NUM,0x08);
        //IAP_ReportStatus(REPORT_NACK,u8ReportError);
    }
}




static void IAP_RestoreEnv(void)
{
    /* 1. restore uart clk pin and bps */
        /* Wait UART Tx Idle */
    /* Wait UART Tx Idle */
	
    #if IAP_INTERFACE == 0
		TARGET_RestoreUart();
    #endif

    #if IAP_INTERFACE == 1
		TARGET_RestoreLin();
    #endif
	
    /* 3. restore wdt status */
    WDT_WALLOW(WDT0);
    WDT_WALLOW(WDT1);
        /* Resume WDT Reg */
    WRITE_REG((WDT0)->WDTCTL,g_u32IapEnvBuffer[0]);
    WRITE_REG((WDT1)->WDTCTL,g_u32IapEnvBuffer[1]);
    WDT_WDIS(WDT0);
    WDT_WDIS(WDT1);
}




static IAP_ComTypeEnum IAP_CheckMode(uint32_t* p32Timout)
{
    IAP_ComTypeEnum eRet = IAP_BY_NONE;
    uint64_t u64WaitTime = 0U;
    BOOL eBool = FALSE;

    /*!< step1:Check if need try UART IAP */
    eBool = TARGET_IsEnableUARTIAP();

    if (eBool == TRUE)
    {
        /*!< step1.1: Uart Init */        
        IAP_InitUART();

        /*!< step1.2: Get uart waittime */
        u64WaitTime = MODECHECK_UART_TIME_WAIT_MS;

        *p32Timout = (uint32_t)u64WaitTime;
        eRet = IAP_BY_UART;

    }
		/*!< step2.1:Check if need try LIN IAP */
    else
    {
        /*!< step1:Check if need try UART IAP */
        eBool = TARGET_IsEnableLINIAP();

        if (eBool == TRUE)
        {

            /*!< step2.2: LIN Init */  
            IAP_InitLIN();

            /*!< step2.3: Get wait time from User config */
            u64WaitTime = MODECHECK_LIN_TIME_WAIT_MS;

            *p32Timout = (uint32_t)u64WaitTime;

            eRet = IAP_BY_LIN;
        }
    }

    return eRet;
}




void IAP_InitUART(void)
{
    uint32_t u32BpsTmp = 0U;
    /*!< step1.1: Init UART driver */
    CLOCK_EnableModule(CONFIG_UART_CLOCK);
    /*!< Set Pin MUX to UART0 TXD RXD */
    TARGET_SET_UART_PIN();
    /*!< UART setting - 8-bit character, 1 stop bit, no parity. & Enable auto-baud */
    //UART_Init(CONFIG_UART, CONFIG_UART_BPS);
    u32BpsTmp = CONFIG_IAP_UART_BPS;

    UART_Init(CONFIG_UART, u32BpsTmp);
    UART_EnableTx(CONFIG_UART);
    UART_EnableRx(CONFIG_UART);
}




static void IAP_InitLIN(void)
{
    uint32_t u32BpsTmp =0U;
    uint16_t             u16PREDRIID;                            /* PRE-DRIVER mode ID */
    ErrorStatus          eErrorState;                            /* Function State */

    u32BpsTmp = CONFIG_IAP_LIN_BPS;
    
    /* HV init */
    eErrorState = HV_Init(&u16PREDRIID);
    if (eErrorState == ERROR)
    {
        return;
    }


    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        return;
    }

    /*
    Init LIN parameter
    when Baud rate 9600, LINCTL_TXSLOPE_19P0US
    when Baud rate 19200, LINCTL_TXSLOPE_7PUS
    */
    eErrorState = EPWR_WriteRegisterField(HV_REG_LINCTL, LINCTL_TXSLOPE_Msk | LINCTL_STRENGTH_Msk | LINCTL_TXEN_Msk | LINCTL_EN_Msk, LINCTL_TXSLOPE_7PUS | LINCTL_STRENGTH_47P2MA | LINCTL_TXEN_ENABLE | LINCTL_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        return;
    }
    
    /* LIN configuration */
    TARGET_SET_LIN_PIN();
    LIN_Init(CONFIG_LIN, LIN_SLAVE, u32BpsTmp);
    UART_EnableTx(CONFIG_LIN);
    UART_EnableRx(CONFIG_LIN);
		
		/* Set the check mode */
		LIN_SetCheckSumMode(CONFIG_LIN, LIN_ENHANCED_CHECKSUM);
		
		/* Set the respond lenth */
		LIN_SetResponseLen(CONFIG_LIN, LIN_RESPONSE_8_BYTE);
    
    LIN_SetIDFilter(CONFIG_LIN, CONFIG_LIN_RECEIVE_ID, CONFIG_LIN_IDMASK);
    
    LIN_SetRxFIFOMode(CONFIG_LIN, LIN_SAVE_CORRECT_DATA);
}




int32_t IAP_Entry(void)
{
    int ret = -1;
    IAP_ComTypeEnum eComType = IAP_BY_NONE;
    uint32_t u32Timeout = 0 ;
		uint32_t u32EntryAddr;
    /* step1: iap soft ware init , restore env */
    if (FALSE == IAP_StoreEnv())
    {
        /* restore env to be continue*/
        TARGET_RecordErrorInfo(IAP_FLOW_4BIT_1_NUM,0x07);
        IAP_RestoreEnv();
        return ret;
    }
    
    /*!< step2: Check if IAP autobaud and handshark by lin or uart */
    eComType = IAP_CheckMode(&u32Timeout);
	
    if (eComType == IAP_BY_UART)
    {
        /*!< In this case , has autobaud and receive handshark in MODECHECK , 
            do not need autobaud in IAP download */
        /*!< Set communicaiton drv interface is UART , used by IAP_DownloadImage */
        g_IapComManager.IapReceive = TARGET_UartReceive;
        g_IapComManager.IapSend    = TARGET_UartSend;
        g_IapComManager.eComType   = IAP_BY_UART;
        IAP_DownloadImage(u32Timeout);
    }
    /*!< step3: Check if MODECHECK has LIN IAP handshark */
    else if (eComType == IAP_BY_LIN)
    {
        /*!< In this case , has autobaud and receive handshark in MODECHECK , 
            do not need autobaud in IAP download */
        /*!< Set communicaiton drv interface is LIN , used by IAP_DownloadImage */
        g_IapComManager.IapReceive = TARGET_LinReceive;
        g_IapComManager.IapSend    = TARGET_LinSend;
        g_IapComManager.eComType   = IAP_BY_LIN;
        IAP_DownloadImage(u32Timeout);
    }
    else
    {
        /*!< Do not need download */
        TARGET_RecordErrorInfo(IAP_FLOW_4BIT_1_NUM,0x0A);
    }

    /* step4: restore env to be continue*/
    IAP_RestoreEnv();
		
		if (TRUE == TARGET_GetJumpFunAddr(TATGET_ENTRY_LOCATION_ADDR , &u32EntryAddr))
		{
				/* Jump to the address */
				((PTRJUMP)((uintptr_t)u32EntryAddr))();
		}
    return 1;
}

/******************* Copyright (C) 2024 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
