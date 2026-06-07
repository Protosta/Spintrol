/******************************************************************************
 * @file     can.c
 * @brief    CAN firmware functions.
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


#include "can.h"


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/******************************************************************************
 * @brief      Reset CAN module
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     none
 *
 ******************************************************************************/
ErrorStatus CAN_Reset( CAN_REGS *CANx )
{
    volatile uint32_t u32Timeout = 0xffffffffU;
    ErrorStatus  eStatus = ERROR;
    
    /* Disable module run */
    CAN_Disable(CANx) ;

    /* Wait transfer operation stop */
    for (u32Timeout = 0xffffffffU; u32Timeout > 0U; u32Timeout--)
    {
        if (CAN_GetOperationMode(CANx) == CAN_OPERATE_STOP)
        {
            break;
        }
    }

    /* Reset module to default state */
    SET_BITS(CANx->CANCTL, CANCTL_RST_Msk ) ;

    if (u32Timeout != 0U)
    {
        eStatus = SUCCESS;  
    }
    
    return eStatus ;
}




/******************************************************************************
 * @brief      Init message RAM
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     none
 *
 ******************************************************************************/
void CAN_InitMessageRAM( CAN_REGS *CANx )
{
    int       i ;
    uint32_t *pu32Addr = (uint32_t *)(long)&CANx->CANMBOX[0] ;

    /* Init all contents of message RAM with 0 */
    for ( i = 0 ; i < CAN_MBOX_NUM * ( CAN_MBOX_SIZE >> 2 ) ; ++i )
    {
        pu32Addr[i] = 0x0 ;
    }

    /* Init only mailbox control position of message RAM with 0 */
    // for ( i = ( CAN_MBOX_SIZE >> 2 ) - 1 ; i < CAN_MBOX_NUM * ( CAN_MBOX_SIZE >> 2 ) ; i += CAN_MBOX_SIZE )
    // {
    //     pu32Addr[i] = 0x0 ;
    // }
}




/******************************************************************************
 * @brief      Encode message data length
 *
 * @param[in]  u8Len : Message data length
 *
 * @return     Message data length code, type is uint8_t
 *
 * @note       assert ( ( u8Len >= 0 ) && ( u8Len <= 64 ) )
 *
 ******************************************************************************/
uint8_t CAN_EncodeDataLength( uint8_t u8Len )
{
    if      ( u8Len <=  8 ) return u8Len ;
    else if ( u8Len <= 12 ) return  9 ;
    else if ( u8Len <= 16 ) return 10 ;
    else if ( u8Len <= 20 ) return 11 ;
    else if ( u8Len <= 24 ) return 12 ;
    else if ( u8Len <= 32 ) return 13 ;
    else if ( u8Len <= 48 ) return 14 ;
    else                    return 15 ;
}




/******************************************************************************
 * @brief      Decode message data length
 *
 * @param[in]  u8LenCode : Message data length code
 *
 * @return     Message data length, type is uint8_t
 *
 * @note       assert ( ( u8Len >= 0 ) && ( u8Len <= 15 ) )
 *
 ******************************************************************************/
uint8_t CAN_DecodeDataLength( uint8_t u8LenCode )
{
    switch ( u8LenCode )
    {
        case  9 : return 12 ;
        case 10 : return 16 ;
        case 11 : return 20 ;
        case 12 : return 24 ;
        case 13 : return 32 ;
        case 14 : return 48 ;
        case 15 : return 64 ;
        default : return u8LenCode ;
    }
}




/******************************************************************************
 * @brief      Set message data bytes
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  pu8Data: message data bytes
 * @param[in]  u8Size : message data bytes size, valid range is 0 to 64
 *
 * @return     none
 *
 * @note       mailbox write access only support 32bits size.
 *
 ******************************************************************************/
void CAN_SetMessageData( CAN_REGS *CANx, uint8_t u8MBoxId, uint8_t *pu8Data, uint8_t u8Size )
{
    int      i ;
    uint8_t  u8DataLen ;
    uint32_t u32Data ;
    uint8_t  u8WSize ;

    u8DataLen = CAN_DecodeDataLength( CAN_EncodeDataLength( u8Size ) ) ;
    u8WSize   = ( u8Size >> 2 ) << 2 ;

    for ( i = 0 ; i < u8WSize ; i += 4 )
    {
        u32Data  = pu8Data[i+0]       ;
        u32Data += pu8Data[i+1] <<  8 ;
        u32Data += pu8Data[i+2] << 16 ;
        u32Data += pu8Data[i+3] << 24 ;

        CAN_SetMessageDataByWord(CANx, u8MBoxId, i>>2, u32Data ) ;
    }
    if ( i < u8Size )
    {
        u32Data  =                    pu8Data[i++]                 ;
        u32Data += ( ( i < u8Size ) ? pu8Data[i++] : 0xCCU ) <<  8 ;
        u32Data += ( ( i < u8Size ) ? pu8Data[i++] : 0xCCU ) << 16 ;
        u32Data += (                                 0xCCU ) << 24 ;

        CAN_SetMessageDataByWord(CANx, u8MBoxId, i>>2, u32Data ) ;

        i += 4 ;
    }
    while ( i < u8DataLen )
    {
        CAN_SetMessageDataByWord(CANx, u8MBoxId, i>>2, 0xCCCCCCCCU ) ;
        i += 4 ;
    }
}




/******************************************************************************
 * @brief      Get message data bytes
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  pu8Data: message data bytes
 * @param[in]  u8Size : message data bytes size, valid range is 0 to 64
 *
 * @return     none
 *
 ******************************************************************************/
void CAN_GetMessageData( CAN_REGS *CANx, uint8_t u8MBoxId, uint8_t *pu8Data, uint8_t u8Size )
{
    int      i ;
    uint8_t *pu8MbData = (uint8_t *)(long)( & CANx->CANMBOX[u8MBoxId].CANMBOXFDW[0] ) ;

    for ( i = 0 ; i < u8Size ; i ++ )
    {
        pu8Data[i] = pu8MbData[i] ;
    }
}




/******************************************************************************
 * @brief      Set message
 *
 * @param[in]  CANx : Select the CAN module
 * @param[in]  pMsg : Message pointer, which type is CAN_MessageTypeDef
 *
 * @return     Error status, which type is ErrorStatus
 *
 * @note       For different mailbox usage:
 *             - transmit frame need set:
 *               id,ide,rtr,fdf,brs,esi,dlc,data
 *               txreq==1,new==1,dir==1
 *             - receive frame need set:
 *               id,ide,rtr,
 *               id_msk,ide_msk,rtr_msk
 *               txreq==0,new==0,dir==0
 *             - transmit remote frame and receive data frame need set:
 *               id,ide,rtr==0,fdf,brs,esi,dlc
 *               id_msk,ide_msk==1,rtr_msk==1 (receive data frame only)
 *               txreq==1,new==0,dir==0,rmten==1
 *             - receive remote frame and transmit data frame need set:
 *               id,ide,rtr==0,fdf,brs,esi,dlc
 *               id_msk,ide_msk==1 (transmit data frame only)
 *               txreq==0,new==1,dir==1,rmten==1
 *
 * @note       This function will always enable ide_msk,rtr_msk
 *
 ******************************************************************************/
ErrorStatus CAN_SetMessage( CAN_REGS *CANx, CAN_MessageTypeDef *pMsg )
{
    uint32_t u32MBControlInfo = 0;
    FunctionalState eMsgTxReq ;

    /* Try disable mailbox */
    if ( ERROR == CAN_AbortMessageTransferRequest( CANx, pMsg->u8MBoxId ) )
    {
        return ERROR ;
    }

    /* Set IDE,FDF */
    CAN_SetMessageFrameFormat( CANx, pMsg->u8MBoxId, pMsg->eFormat ) ;

    /* Set RTR */
    CAN_SetMessageFrameType( CANx, pMsg->u8MBoxId, pMsg->eType ) ;

    /* Set ID,ID_msk */
    switch ( pMsg->eFormat )
    {
        case CAN_FORMAT_STD      :
        case CAN_FORMAT_FD_STD   :
        {
            CAN_SetMessageStandardIdentifier    (CANx, pMsg->u8MBoxId, pMsg->u32Id ) ;
            CAN_SetMessageStandardIdentifierMask(CANx, pMsg->u8MBoxId, pMsg->u32IdMask ) ;
            break ;
        }
        case CAN_FORMAT_EXT      :
        case CAN_FORMAT_FD_EXT   :
        {
            CAN_SetMessageExtendedIdentifier    (CANx, pMsg->u8MBoxId, pMsg->u32Id ) ;
            CAN_SetMessageExtendedIdentifierMask(CANx, pMsg->u8MBoxId, pMsg->u32IdMask ) ;
            break ;
        }
        default: break ;
    }

    /* Set IDE_msk */
    if ( pMsg->eMaskIdeEn )
    {
        CAN_EnableMessageExtendedIdentifierMask(CANx, pMsg->u8MBoxId ) ;
    }
    else
    {
        CAN_DisableMessageExtendedIdentifierMask(CANx, pMsg->u8MBoxId ) ;
    }

    /* Set RTR_msk */
    if ( pMsg->eMaskRtrEn )
    {
        CAN_EnableMessageFrameTypeMask (CANx, pMsg->u8MBoxId ) ;
    }
    else
    {
        CAN_DisableMessageFrameTypeMask(CANx, pMsg->u8MBoxId ) ;
    }

    /* Set BRS */
    if ( pMsg->eBrs )
    {
        CAN_EnableMessageBitRateSwitch( CANx, pMsg->u8MBoxId ) ;
    }
    else
    {
        CAN_DisableMessageBitRateSwitch( CANx, pMsg->u8MBoxId ) ;
    }

    /* Set ESI */
    if ( pMsg->eEsiCtlEn )
    {
        if ( pMsg->eEsi )
        {
            CAN_ForceSendRecessiveErrorStateIndicator( CANx, pMsg->u8MBoxId ) ;
        }
        else
        {
            CAN_ForceSendDominantErrorStateIndicator( CANx, pMsg->u8MBoxId ) ;
        }
    }
    else
    {
        CAN_DisableForceSendErrorStateIndicator( CANx, pMsg->u8MBoxId ) ;
    }

    /* Set message data length */
    CAN_SetMessageDataLength(CANx, pMsg->u8MBoxId, pMsg->u8DataLen ) ;

    /* Set message data information */
    if ( ( pMsg->eDataDir == CAN_MSG_DATA_TX )
      && ( pMsg->eType    == CAN_FRAME_DATA  )
      && ( pMsg->u8DataLen>  0               )
    /* Except when data buffer point to mailbox its self */
      && ( (uint32_t *)(pMsg->pu8Data) != (uint32_t *)(long)( & CANx->CANMBOX[pMsg->u8MBoxId].CANMBOXFDW[0] ) )
    )
    {
        /* Set message data */
        CAN_SetMessageData( CANx, pMsg->u8MBoxId, pMsg->pu8Data, pMsg->u8DataLen ) ;
    }

    /* Clear message timestamp */
    CAN_ClearMessageTimestamp(CANx, pMsg->u8MBoxId ) ;

    /* Set message control information */
    eMsgTxReq = (FunctionalState)(
           (  pMsg->eDataDir && !pMsg->eRmtRspEn ) /* transmit frame only */
        || ( !pMsg->eDataDir &&  pMsg->eRmtRspEn ) /* transmit remote frame and receive data frame */
    ) ;

    if (pMsg->eDataDir)
    {
        u32MBControlInfo |= CAN_MBOX_ENABLE_MSG_DATA_TX;
    }

    if (pMsg->eRmtRspEn)
    {
        u32MBControlInfo |= CAN_MBOX_ENABLE_RESPONSE_REMOTE;
    }

    if (pMsg->eDataDir)
    {
        u32MBControlInfo |= CAN_MBOX_SET_MSG_NEW;
    }
    
    if (eMsgTxReq)
    {
        u32MBControlInfo |= CAN_MBOX_REQUEST_TX;
    }

    if (pMsg->eIntEn)
    {
        u32MBControlInfo |= CAN_MBOX_ENABLE_INT;
    }
    
    if (pMsg->eEobEn)
    {
        u32MBControlInfo |= CAN_MBOX_ENABLE_EOB;
    }

    if (pMsg->eOverwriteEn)
    {
        u32MBControlInfo |= CAN_MBOX_ENABLE_OVERWRITE_EOB;
    }

    /* Set message control information */
    CAN_SetMailboxControlInfo( CANx, pMsg->u8MBoxId, u32MBControlInfo) ;

    return SUCCESS;
}




/******************************************************************************
 * @brief      Get message
 *
 * @param[in]  CANx : Select the CAN module
 * @param[in]  pMsg : Message pointer, which type is CAN_MessageTypeDef
 *
 * @return     none
 *
 ******************************************************************************/
void CAN_GetMessage( CAN_REGS *CANx, CAN_MessageTypeDef *pMsg )
{
    /* Get mailbox control information */
    pMsg->eDataDir      = (CAN_DataDirectionEnum)CAN_GetMessageDataDirection( CANx, pMsg->u8MBoxId ) ;
    pMsg->eRmtRspEn     = CAN_IsEnableMailboxResponseRemoteFrame( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;
    pMsg->eIntEn        = CAN_IsEnableMailboxTransferInterrupt( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;
    pMsg->eEobEn        = CAN_IsEnableMailboxEndOfBlock( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;
    pMsg->eOverwriteEn  = CAN_IsEnableMailboxOverwrite( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;

    /* Get IDE,FDF */
    pMsg->eFormat = (CAN_FrameFormatEnum)CAN_GetMessageFrameFormat( CANx, pMsg->u8MBoxId ) ;

    /* Get RTR */
    pMsg->eType   = (CAN_FrameTypeEnum)CAN_GetMessageFrameType( CANx, pMsg->u8MBoxId ) ;

    /* Get ID */
    switch ( pMsg->eFormat )
    {
        case CAN_FORMAT_STD      :
        case CAN_FORMAT_FD_STD   :
        {
            pMsg->u32Id     = CAN_GetMessageStandardIdentifier    (CANx, pMsg->u8MBoxId ) ;
            pMsg->u32IdMask = CAN_GetMessageStandardIdentifierMask(CANx, pMsg->u8MBoxId ) ;
            break ;
        }
        case CAN_FORMAT_EXT      :
        case CAN_FORMAT_FD_EXT   :
        {
            pMsg->u32Id     = CAN_GetMessageExtendedIdentifier    (CANx, pMsg->u8MBoxId ) ;
            pMsg->u32IdMask = CAN_GetMessageExtendedIdentifierMask(CANx, pMsg->u8MBoxId ) ;
            break ;
        }
        default: break ;
    }

    /* Get BRS */
    pMsg->eBrs      = CAN_IsEnableMessageBitRateSwitch( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;

    /* Get ESI,ESI_ctl */
    pMsg->eEsi      = CAN_GetMessageErrorStateIndicator ( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;
    pMsg->eEsiCtlEn = CAN_IsForceSendErrorStateIndicator( CANx, pMsg->u8MBoxId ) ? ENABLE : DISABLE ;

    /* Get message data length */
    pMsg->u8DataLen = CAN_GetMessageDataLength(CANx, pMsg->u8MBoxId ) ;
    switch ( pMsg->eFormat )
    {
        case CAN_FORMAT_STD      :
        case CAN_FORMAT_EXT      :
        {
            if ( pMsg->u8DataLen > 8 )
            {
                pMsg->u8DataLen = 8 ;
            }
            break ;
        }
        case CAN_FORMAT_FD_STD   :
        case CAN_FORMAT_FD_EXT   :
        default: break ;
    }

    /* Get message data information */
    if ( ( pMsg->eType    == CAN_FRAME_DATA  )
      && ( pMsg->u8DataLen>  0               )
    /* Except when data buffer point to mailbox its self */
      && ( (uint32_t *)(pMsg->pu8Data) != (uint32_t *)(long)( & CANx->CANMBOX[pMsg->u8MBoxId].CANMBOXFDW[0] ) )
    )
    {
        CAN_GetMessageData( CANx, pMsg->u8MBoxId, pMsg->pu8Data, pMsg->u8DataLen ) ;
    }

    /* Get message timestamp */
    pMsg->u32Timestamp = CAN_GetMessageTimestamp(CANx, pMsg->u8MBoxId ) ;
}




/******************************************************************************
 * @brief      Abort message transfer request
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     SUCCESS  - Abort transfer request success
 *             ERROR    - Abort transfer request failed
 *
 ******************************************************************************/
ErrorStatus CAN_AbortMessageTransferRequest( CAN_REGS *CANx, uint8_t u8MBoxId )
{
    /* Disable mailbox */
    CAN_DisableMailbox( CANx, u8MBoxId ) ;

    /* If mailbox write on locked mailbox, return error */
    if ( CAN_IsEnableMailbox( CANx, u8MBoxId ) )
    {
        return ERROR ;
    }
    else
    {
        return SUCCESS ;
    }
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
