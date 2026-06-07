/******************************************************************************
 * @file     can.h
 * @brief    CAN driver header file.
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
 *
 * @attention
 * THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION REGARDING
 * THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM. SPINTROL SH0LL NOT BE
 * LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL DOES NOT GUARANTEE THE
 * CORRECTNESS OF THIS SOFTWARE AND RESERVES THE RIGHT TO MODIFY THE SOFTWARE
 * WITHOUT NOTIFICATION.
 *
 ******************************************************************************/


#ifndef CAN_H
#define CAN_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  CAN mailbox number
 */
#define  CAN_MBOX_NUM           64


/**
 *  @brief  CAN mailbox size
 */
#define  CAN_MBOX_SIZE          (20 << 2)




/**
 *  @brief  CAN module operation mode enumeration
 */
typedef enum
{
    CAN_OPERATE_STOP            = 0, /*!< Moduel is stopped                 */
    CAN_OPERATE_INTEGRATION     = 1, /*!< Module is in integration staus    */
    CAN_OPERATE_IDLE            = 2, /*!< Module is idle                    */
    CAN_OPERATE_TX_BUSY         = 3, /*!< Module is busy transmitting frame */
    CAN_OPERATE_RX_BUSY         = 4, /*!< Module is busy reception frame    */
    CAN_OPERATE_RESTRICTED      = 5, /*!< Module is in restricted mode      */
    CAN_OPERATE_BUS_OFF         = 6  /*!< Module is bus off                 */
} CAN_OperationEnum ;




/**
 *  @brief  CAN module status enumeration
 */
typedef enum
{
    CAN_STS_ERROR_PASSIVE       = (1 << 15U), /*!< Moduel is error passive state.   */
    CAN_STS_ERROR_WARN          = (1 << 16U)  /*!< Module is error warning state.   */
} CAN_StatusEnum ;




/**
 *  @brief  CAN last error code enumeration
 */
typedef enum
{
    CAN_LAST_ERROR_NONE             = 0, /*!< No error occured                            */
    CAN_LAST_ERROR_STUFF            = 1, /*!< Bit stuff error occured                     */
    CAN_LAST_ERROR_FORM             = 2, /*!< Form error occured                          */
    CAN_LAST_ERROR_ACK              = 3, /*!< Ack error occured                           */
    CAN_LAST_ERROR_BIT1             = 4, /*!< Bit error occured on recessive bit          */
    CAN_LAST_ERROR_BIT0             = 5, /*!< Bit error occured on dominant bit           */
    CAN_LAST_ERROR_CRC              = 6, /*!< Crc error occured                           */
    CAN_LAST_ERROR_NONE_AFTER_READ  = 7  /*!< No error occured after last read error code */
} CAN_ErrorCodeEnum ;




/**
 *  @brief  CAN misc interrupt enumeration
 */
typedef enum
{
    CAN_MISC_INT_TRANSFER_ERROR      = 1U <<  0,          /*!< Message transfer error interrupt       */
    CAN_MISC_INT_WARN                = 1U <<  1,          /*!< Error warning interrupt                */
    CAN_MISC_INT_PASSIVE             = 1U <<  2,          /*!< Error passive status entry interrupt   */
    CAN_MISC_INT_BUS_OFF             = 1U <<  3,          /*!< Bus off status entry interrupt         */
    CAN_MISC_INT_FILTER_OK           = 1U <<  4,          /*!< Receive massage ID filter OK interrupt */
    CAN_MISC_INT_PROTOCOL_EXCEPTION  = 1U <<  5,          /*!< Protocol exception event interrupt     */
    CAN_MISC_INT_MRAM_SBE            = 1U <<  6,          /*!< Memory single bit error interrupt      */
    CAN_MISC_INT_MRAM_MBE            = 1U <<  7,          /*!< Memory multi bit error interrupt       */
    CAN_MISC_INT_TIMESTAMP_OVERFLOW  = 1U <<  8,          /*!< Timestamp counter overflow interrupt   */
    CAN_MISC_INT_MESSAGE_LOST        = 1U <<  9,          /*!< Message lost interrupt                 */
    CAN_MISC_INT_GLOBAL              = (int)(1U << 31),   /*!< Global interrupt                       */
    CAN_MISC_INT_ALL                 = (int)(0x800003FFU) /*!< Used for all interrupts                */
} CAN_MiscIntEnum ;




/**
 *  @brief  CAN transfer interrupt enumeration
 */
typedef enum
{
    CAN_TRAN_GRP0_INT = 1U <<  0 , /*!< Message transfer done for mailbox  0 to  7 */
    CAN_TRAN_GRP1_INT = 1U <<  1 , /*!< Message transfer done for mailbox  8 to 15 */
    CAN_TRAN_GRP2_INT = 1U <<  2 , /*!< Message transfer done for mailbox 16 to 23 */
    CAN_TRAN_GRP3_INT = 1U <<  3 , /*!< Message transfer done for mailbox 24 to 31 */
    CAN_TRAN_GRP4_INT = 1U <<  4 , /*!< Message transfer done for mailbox 32 to 39 */
    CAN_TRAN_GRP5_INT = 1U <<  5 , /*!< Message transfer done for mailbox 40 to 47 */
    CAN_TRAN_GRP6_INT = 1U <<  6 , /*!< Message transfer done for mailbox 48 to 55 */
    CAN_TRAN_GRP7_INT = 1U <<  7   /*!< Message transfer done for mailbox 56 to 63 */
} CAN_TranGrpIntEnum ;



/**
 *  @brief  CAN TXD pin test mode enumeration
 */
typedef enum
{
    CAN_TX_MODE_NORMALL         = 0, /*!< TXD is normal mode                        */
    CAN_TX_MODE_SAMPLE_POINT    = 1, /*!< Sample point can be monitored at TXD pin  */
    CAN_TX_MODE_LOW             = 2, /*!< TXD pin drives a dominant value           */
    CAN_TX_MODE_HIGH            = 3  /*!< TXD pin drives a recessive value          */
} CAN_TXModeEnum ;




/**
 *  @brief  CAN message format enumeration
 */
typedef enum
{
    CAN_FORMAT_STD      = 0, /*!< Standard frame format     */
    CAN_FORMAT_EXT      = 1, /*!< Extended frame format     */
    CAN_FORMAT_FD_STD   = 2, /*!< FD Standard frame format  */
    CAN_FORMAT_FD_EXT   = 3  /*!< FD Extended frame format  */
} CAN_FrameFormatEnum ;




/**
 *  @brief  CAN frame type enumeration
 */
typedef enum
{
    CAN_FRAME_DATA      = 0, /*!< Data frame    */
    CAN_FRAME_REMOTE    = 1  /*!< Remote frame  */
} CAN_FrameTypeEnum ;




/**
 *  @brief  CAN message data direction enumeration
 */
typedef enum
{
    CAN_MSG_DATA_RX     = 0, /*!< Reception message data    */
    CAN_MSG_DATA_TX     = 1  /*!< Transmission message data */
} CAN_DataDirectionEnum ;




/**
 *  @brief  CAN mailbox control enumeration
 */
typedef enum
{
    /* Below enumeration is used for write mailbox control information */
    CAN_MBOX_ENABLE                     = (int)(1U << 31),  /*!< Enable mailbox                         */
    CAN_MBOX_ENABLE_MSG_DATA_TX         = 1 << 30,          /*!< Message data transfer direction on bus */
    CAN_MBOX_ENABLE_RESPONSE_REMOTE     = 1 << 29,          /*!< Enable auto response remote frame      */
    CAN_MBOX_SET_MSG_NEW                = 1 << 28,          /*!< New message                            */
    CAN_MBOX_REQUEST_TX                 = 1 << 26,          /*!< Transmission request                   */
    CAN_MBOX_ENABLE_INT                 = 1 << 24,          /*!< Enbale mailbox transfer interupt       */
    CAN_MBOX_ENABLE_EOB                 = 1 << 23,          /*!< Enable end of block                    */
    CAN_MBOX_ENABLE_OVERWRITE_EOB       = 1 << 22,          /*!< Enable overwrite end of block mailbox  */
    /* Below enumeration is used for read mailbox control information */
    CAN_MBOX_IS_ENABLE                  = (int)(1U << 31),  /*!< Enable mailbox                         */
    CAN_MBOX_IS_ENABLE_MSG_DATA_TX      = 1 << 30,          /*!< Message data transfer direction on bus */
    CAN_MBOX_IS_ENABLE_RESPONSE_REMOTE  = 1 << 29,          /*!< Enable auto response remote frame      */
    CAN_MBOX_IS_MSG_NEW                 = 1 << 28,          /*!< New message                            */
    CAN_MBOX_IS_MSG_LOST                = 1 << 27,          /*!< Receive message lost flag              */
    CAN_MBOX_IS_REQUEST_TX              = 1 << 26,          /*!< Transmission request                   */
    CAN_MBOX_IS_INT_OCCURED             = 1 << 25,          /*!< Interrupt pending flag                 */
    CAN_MBOX_IS_ENABLE_INT              = 1 << 24,          /*!< Enbale mailbox transfer interupt       */
    CAN_MBOX_IS_ENABLE_EOB              = 1 << 23,          /*!< Enable end of block                    */
    CAN_MBOX_IS_ENABLE_OVERWRITE_EOB    = 1 << 22,          /*!< Enable overwrite end of block mailbox  */
    CAN_MBOX_IS_LOCK_WRITE              = 1 << 21,          /*!< Mailbox locked flag                    */
    CAN_MBOX_ALL_CONTROL_FIELD          = (int)(0xFFE00000U)/*!< Mailbox all control field mask         */
} CAN_MailboxControlEnum ;




/**
 *  @brief  CAN mailbox type definition
 */
typedef struct
{
    /* Message definition */
    CAN_FrameFormatEnum         eFormat         ; /*!< Frame format: STD,EXT,FD_STD,FD_EXT              */
    CAN_FrameTypeEnum           eType           ; /*!< Frame type  : data frame or remote frame         */
    uint32_t                    u32Id           ; /*!< Message identifier                               */
    uint32_t                    u32IdMask       ; /*!< Message identifier mask                          */
    FunctionalState             eMaskRtrEn      ; /*!< Enable mask RTR bit                              */
    FunctionalState             eMaskIdeEn      ; /*!< Enable mask IDE bit                              */
    uint8_t                     u8DataLen       ; /*!< Message data length                              */
    uint8_t                     *pu8Data        ; /*!< Message data buffer pointer                      */
    uint32_t                    u32Timestamp    ; /*!< Message data timestamp based on nominal bit time */
    FunctionalState             eBrs            ; /*!< Bit Rate Switch enable bit                       */
    FunctionalState             eEsi            ; /*!< Error State Indicator bit                        */
    FunctionalState             eEsiCtlEn       ; /*!< ESI control bit when send mesage :
                                                       0: send ESI with node error state;
                                                       1: send ESI with eEsi value.                     */
    /* Mailbox control definition */
    uint8_t                     u8MBoxId        ; /*!< Mailbox ID                                       */
    CAN_DataDirectionEnum       eDataDir        ; /*!< Transmission or reception message data           */
    FunctionalState             eRmtRspEn       ; /*!< Enable response remote frame                     */
    FunctionalState             eIntEn          ; /*!< Enable transfer done interrupt                   */
    FunctionalState             eEobEn          ; /*!< Current mailbox is End Of Block, valid for reception data          */
    FunctionalState             eOverwriteEn    ; /*!< Enable message overwrite, valid for reception data and EOB enabled */
} CAN_MessageTypeDef ;




/******************************************************************************
 * @brief      Enable message RAM parity check
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableParityCheck(CANx)                                             \
    SET_BITS((CANx)->CANCTL, CANCTL_PRTYCHK_Msk)
/******************************************************************************
 * @brief      Disable message RAM parity check
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableParityCheck(CANx)                                            \
    CLEAR_BITS((CANx)->CANCTL, CANCTL_PRTYCHK_Msk)
/******************************************************************************
 * @brief      Is enable message RAM parity check
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - Message RAM parity check is disabled
 *             not 0 - Message RAM parity check is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableParityCheck(CANx)                                           \
    READ_BITS((CANx)->CANCTL, CANCTL_PRTYCHK_Msk)
/******************************************************************************
 * @brief      Get message RAM parity check error address
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Parity check error address, which type is uint32_t
 *
 ******************************************************************************/
#define CAN_GetMemoryErrorAddress(CANx)                                         \
    READ_REG( (CANx)->CANMEMERRADDR )




/******************************************************************************
 * @brief      Enable CAN Non-SIO mode (based on BOSCH specification)
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableNonIsoMode(CANx)                                              \
    SET_BITS( (CANx)->CANCTL, CANCTL_NONISO_Msk )
/******************************************************************************
 * @brief      Disable CAN Non-SIO mode (based on BOSCH specification)
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableNonIsoMode(CANx)                                             \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_NONISO_Msk )
/******************************************************************************
 * @brief      Is enable CAN Non-SIO mode (based on BOSCH specification)
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN Non-SIO mode is disabled
 *             not 0 - CAN Non-SIO mode is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableNonIsoMode(CANx)                                            \
    READ_BITS( (CANx)->CANCTL, CANCTL_NONISO_Msk )




/******************************************************************************
 * @brief      Enable Flexible Data rate CAN format
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableFDFormat(CANx)                                                \
    SET_BITS( (CANx)->CANCTL, CANCTL_FDEN_Msk )
/******************************************************************************
 * @brief      Disable Flexible Data rate CAN format
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableFDFormat(CANx)                                               \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_FDEN_Msk )
/******************************************************************************
 * @brief      Is enable Flexible Data rate CAN format
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - Flexible Data rate CAN format is disabled
 *             not 0 - Flexible Data rate CAN format is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableFDFormat(CANx)                                              \
    READ_BITS( (CANx)->CANCTL, CANCTL_FDEN_Msk )




/******************************************************************************
 * @brief      Enable CAN test mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableTestMode(CANx)                                                \
    SET_BITS( (CANx)->CANCTL, CANCTL_TSTMODE_Msk )
/******************************************************************************
 * @brief      Disable CAN test mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableTestMode(CANx)                                               \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_TSTMODE_Msk )
/******************************************************************************
 * @brief      Is enable CAN test mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN test mode is disabled
 *             not 0 - CAN test mode is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableTestMode(CANx)                                              \
    READ_BITS( (CANx)->CANCTL, CANCTL_TSTMODE_Msk )
/******************************************************************************
 * @brief      Enable CAN loopback mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableLoopback(CANx)                                                \
    SET_BITS( (CANx)->CANTEST, CANTEST_LOOP_Msk )
/******************************************************************************
 * @brief      Disable CAN Loopback Mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableLoopback(CANx)                                               \
    CLEAR_BITS( (CANx)->CANTEST, CANTEST_LOOP_Msk )
/******************************************************************************
 * @brief      Is enable CAN loopback mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN loopback mode is disabled
 *             not 0 - CAN loopback mode is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableLoopback(CANx)                                              \
    READ_BITS( (CANx)->CANTEST, CANTEST_LOOP_Msk )
/******************************************************************************
 * @brief      Enable CAN external loopback mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableExternalLoopback(CANx)                                        \
    SET_BITS( (CANx)->CANTEST, CANTEST_ELOOP_Msk )
/******************************************************************************
 * @brief      Disable CAN external loopback mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableExternalLoopback(CANx)                                       \
    CLEAR_BITS( (CANx)->CANTEST, CANTEST_ELOOP_Msk )
/******************************************************************************
 * @brief      Is enable CAN external loopback mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN external loopback mode is disabled
 *             not 0 - CAN external loopback mode is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableExternalLoopback(CANx)                                      \
    READ_BITS( (CANx)->CANTEST, CANTEST_ELOOP_Msk )
/******************************************************************************
 * @brief      Set TXD pin test mode
 *
 * @param[in]  CANx  : Select the CAN module
 *             eMode : TXD Pin Mode, which type is CAN_TXModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_SetTxPinTestMode(CANx, eMode)                                       \
    WRITE_FIELD( (CANx)->CANTEST, CANTEST_TXMODE_Msk, CANTEST_TXMODE_Pos, (eMode) )
/******************************************************************************
 * @brief      Get TXD pin test mode
 *
 * @param[in]  CANx :  Select the CAN module
 *
 * @return     TXD Pin Mode, which type is CAN_TXModeEnum
 *
 ******************************************************************************/
#define CAN_GetTxPinTestMode(CANx)                                              \
    READ_FIELD( (CANx)->CANTEST, CANTEST_TXMODE_Msk, CANTEST_TXMODE_Pos )
/******************************************************************************
 * @brief      Get TXD pin level
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - TXD pin is dominant bit
 *             not 0 - TXD pin is recessive bit
 *
 ******************************************************************************/
#define CAN_GetTxPinLevel(CANx)                                                 \
    READ_BITS( (CANx)->CANTEST, CANTEST_TXD_Msk )
/******************************************************************************
 * @brief      Get RXD pin level
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - RXD pin is dominant bit
 *             not 0 - RXD pin is recessive bit
 *
 ******************************************************************************/
#define CAN_GetRxPinLevel(CANx)                                                 \
    READ_BITS( (CANx)->CANTEST, CANTEST_RXD_Msk )




/******************************************************************************
 * @brief      Enable CAN monitor mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMonitorMode(CANx)                                             \
    SET_BITS( (CANx)->CANCTL, CANCTL_MONMODE_Msk )
/******************************************************************************
 * @brief      Disable CAN monitor mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMonitorMode(CANx)                                            \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_MONMODE_Msk )
/******************************************************************************
 * @brief      Is enable CAN monitor mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN monitor mode is disabled
 *             not 0 - CAN monitor mode is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMonitorMode(CANx)                                           \
    READ_BITS( (CANx)->CANCTL, CANCTL_MONMODE_Msk )




/******************************************************************************
 * @brief      Enable restricted mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableRestrictedMode(CANx)                                          \
    SET_BITS( (CANx)->CANCTL, CANCTL_RESMODE_Msk )
/******************************************************************************
 * @brief      DIsable restricted mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableRestrictedMode(CANx)                                         \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_RESMODE_Msk )
/******************************************************************************
 * @brief      Is enable restricted mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN restricted mode is disabled
 *             not 0 - CAN restricted mode is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableRestrictedMode(CANx)                                        \
    READ_BITS( (CANx)->CANCTL, CANCTL_RESMODE_Msk )




/******************************************************************************
 * @brief      Enable edge filter function during integration state
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableEdgeFilter(CANx)                                              \
    SET_BITS( (CANx)->CANCTL, CANCTL_EDGEFLT_Msk )
/******************************************************************************
 * @brief      Disable edge filter function during integration state
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableEdgeFilter(CANx)                                             \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_EDGEFLT_Msk )
/******************************************************************************
 * @brief      Is enable edge filter function during integration state
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN edge filter function is disabled
 *             not 0 - CAN edge filter function is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableEdgeFilter(CANx)                                            \
    READ_BITS( (CANx)->CANCTL, CANCTL_EDGEFLT_Msk )




/******************************************************************************
 * @brief      Enable transmission pause 2 nominal bit function
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableTransmissionPause(CANx)                                       \
    SET_BITS( (CANx)->CANCTL, CANCTL_TXPAUSE_Msk )
/******************************************************************************
 * @brief      Disable transmission pause 2 nominal bit function
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableTransmissionPause(CANx)                                      \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_TXPAUSE_Msk )
/******************************************************************************
 * @brief      Is enable transmission pause 2 nominal bit function
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN transmission pause 2 nominal bit function is disabled
 *             not 0 - CAN transmission pause 2 nominal bit function is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableTransmissionPause(CANx)                                     \
    READ_BITS( (CANx)->CANCTL, CANCTL_TXPAUSE_Msk )




/******************************************************************************
 * @brief      Enable protocol exception
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableProtocolException(CANx)                                       \
    SET_BITS( (CANx)->CANCTL, CANCTL_PXEN_Msk )
/******************************************************************************
 * @brief      Disable protocol exception
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableProtocolException(CANx)                                      \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_PXEN_Msk )
/******************************************************************************
 * @brief      Is enable protocol exception
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN protocol exception is disabled
 *             not 0 - CAN protocol exception is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableProtocolException(CANx)                                     \
    READ_BITS( (CANx)->CANCTL, CANCTL_PXEN_Msk )




/******************************************************************************
 * @brief      Enable swap TXD/RXD pin
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnablePinSwap(CANx)                                                 \
    SET_BITS( (CANx)->CANCTL, CANCTL_IOSWAP_Msk )
/******************************************************************************
 * @brief      Disable swap TXD/RXD pin
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisablePinSwap(CANx)                                                \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_IOSWAP_Msk )
/******************************************************************************
 * @brief      Is enable swap TXD/RXD pin
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - Swap TXD/RXD pin is disabled
 *             not 0 - Swap TXD/RXD pin is enabled
 *
 ******************************************************************************/
#define CAN_IsEnablePinSwap(CANx)                                               \
    READ_BITS( (CANx)->CANCTL, CANCTL_IOSWAP_Msk )




/******************************************************************************
 * @brief      Enable auto retransmission after transmission failed
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableAutoRetransmission(CANx)                                      \
    SET_BITS( (CANx)->CANCTL, CANCTL_RETX_Msk )
/******************************************************************************
 * @brief      Disable auto retransmission after transmission failed
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableAutoRetransmission(CANx)                                     \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_RETX_Msk )
/******************************************************************************
 * @brief      Is enable auto retransmission after transmission failed
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN auto retransmission is disabled
 *             not 0 - CAN auto retransmission is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableAutoRetransmission(CANx)                                    \
    READ_BITS( (CANx)->CANCTL, CANCTL_RETX_Msk )




/******************************************************************************
 * @brief      Enable auto bus on after bus off occured
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableAutoBusOn(CANx)                                               \
    SET_BITS( (CANx)->CANCTL, CANCTL_AUTOON_Msk )
/******************************************************************************
 * @brief      Disable auto bus on after bus off occured
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableAutoBusOn(CANx)                                              \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_AUTOON_Msk )
/******************************************************************************
 * @brief      Is enable auto bus on after bus off occured
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN auto bus on is disabled
 *             not 0 - CAN auto bus on is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableAutoBusOn(CANx)                                             \
    READ_BITS( (CANx)->CANCTL, CANCTL_AUTOON_Msk )
/******************************************************************************
 * @brief      Manually enable bus off recovery sequence after bus off occured
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 * @note       This bit is self clear bit
 *
 ******************************************************************************/
#define CAN_EnableBusOffRecovery(CANx)                                          \
    SET_BITS( (CANx)->CANCTL, CANCTL_RECOVEN_Msk )
/******************************************************************************
 * @brief      Set bus off recovery delay
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u16Val : Bus off recovery delay based on nominal bit time
 *
 * @return     None
 *
 * @note       assert ( ( u16Val >= 0 ) && ( u16Val <= 65535 ) )
 *
 ******************************************************************************/
#define CAN_SetBusOffRecoveryDelay(CANx, u16Val)                                \
    WRITE_FIELD( (CANx)->CANBRDLY, CANBRDLY_DLY_Msk, CANBRDLY_DLY_Pos, u16Val )
/******************************************************************************
 * @brief      Get bus off recovery delay
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Bus off recovery delay based on nominal bit time, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetBusOffRecoveryDelay(CANx)                                        \
    READ_FIELD( (CANx)->CANBRDLY, CANBRDLY_DLY_Msk, CANBRDLY_DLY_Pos )




/******************************************************************************
 * @brief      Is CAN module software reset
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 * @note       This bit will be cleared after module reset acknowledged
 *
 ******************************************************************************/
#define CAN_IsReset(CANx)                                                       \
    READ_BITS( (CANx)->CANCTL, CANCTL_RST_Msk )





/******************************************************************************
 * @brief      Enabled CAN module run
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_Enable(CANx)                                                        \
    SET_BITS( (CANx)->CANCTL, CANCTL_RUN_Msk )
/******************************************************************************
 * @brief      Disable CAN module run
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_Disable(CANx)                                                       \
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_RUN_Msk )
/******************************************************************************
 * @brief      Is enable CAN module run
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN is disabled
 *             not 0 - CAN is enabled
 *
 ******************************************************************************/
#define CAN_IsEnable(CANx)                                                      \
    READ_BITS( (CANx)->CANCTL, CANCTL_RUN_Msk )




/******************************************************************************
 * @brief      Set nominal bit rate prescaler
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u16Val : Nominal bit rate prescaler
 *
 * @return     None
 *
 * @note       assert ( ( u16Val >= 1 ) && ( u16Val <= 256 ) )
 *             Must set data bit rate prescaler with same value
 *
 ******************************************************************************/
#define CAN_SetNominalBitRatePrescaler(CANx, u16Val)                            \
    WRITE_FIELD( (CANx)->CANNBTQ, CANNBTQ_NBRP_Msk, CANNBTQ_NBRP_Pos, (u16Val) - 1 )
/******************************************************************************
 * @brief      Get nominal bit rate prescaler
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Nominal bit rate prescaler, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetNominalBitRatePrescaler(CANx)                                   \
    ( 1 + READ_FIELD( (CANx)->CANNBTQ, CANNBTQ_NBRP_Msk, CANNBTQ_NBRP_Pos ) )




/******************************************************************************
 * @brief      Set nominal bit phase buffer segment1
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u16Val : Time quatum number for nominal bit phase buffer segment1
 *
 * @return     None
 *
 * @note       assert ( ( u16Val >= 2 ) && ( u16Val <= 256 ) )
 *
 ******************************************************************************/
#define CAN_SetNominalBitPhaseBufferSegment1(CANx, u16Val)                      \
    WRITE_FIELD( (CANx)->CANNBTQ, CANNBTQ_NSEG1_Msk, CANNBTQ_NSEG1_Pos, (u16Val) - 1 )
/******************************************************************************
 * @brief      Get nominal bit phase buffer segment1
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Time quatum number for nominal bit phase buffer segment1, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetNominalBitPhaseBufferSegment1(CANx)                              \
    ( 1 + READ_FIELD( (CANx)->CANNBTQ, CANNBTQ_NSEG1_Msk, CANNBTQ_NSEG1_Pos ) )




/******************************************************************************
 * @brief      Set nominal bit phase buffer segment2
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8Val  : Time quatum number for nominal bit phase buffer segment2
 *
 * @return     None
 *
 * @note       assert ( ( u8Val >= 2 ) && ( u8Val <= 128 ) )
 *
 ******************************************************************************/
#define CAN_SetNominalBitPhaseBufferSegment2(CANx, u8Val)                       \
    WRITE_FIELD( (CANx)->CANNBTQ, CANNBTQ_NSEG2_Msk, CANNBTQ_NSEG2_Pos, (u8Val) - 1 )
/******************************************************************************
 * @brief      Get nominal bit phase buffer segment2
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Time quatum number for nominal bit phase buffer segment2, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetNominalBitPhaseBufferSegment2(CANx)                              \
    ( 1 + READ_FIELD( (CANx)->CANNBTQ, CANNBTQ_NSEG2_Msk, CANNBTQ_NSEG2_Pos ) )




/******************************************************************************
 * @brief      Set nominal bit resync jump width
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8Val  : Time quatum number for nominal bit resync jump width
 *
 * @return     None
 *
 * @note       assert ( ( u8Val >= 1 ) && ( u8Val <= 128 ) )
 *
 ******************************************************************************/
#define CAN_SetNominalBitResyncJumpWidth(CANx, u8Val)                           \
    WRITE_FIELD( (CANx)->CANNBTQ, CANNBTQ_NSJW_Msk, CANNBTQ_NSJW_Pos, (u8Val) - 1 )
/******************************************************************************
 * @brief      Get Nominal Bit Resync Jump Width
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Time quatum number for nominal bit resync jump width, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetNominalBitResyncJumpWidth(CANx)                                  \
    ( 1 + READ_FIELD( (CANx)->CANNBTQ, CANNBTQ_NSJW_Msk, CANNBTQ_NSJW_Pos ) )




/******************************************************************************
 * @brief      Set data bit rate prescaler
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u16Val : Data bit rate prescaler
 *
 * @return     None
 *
 * @note       assert ( ( u16Val >= 1 ) && ( u16Val <= 256 ) )
 *             Must set nominal bit rate prescaler with same value
 *
 ******************************************************************************/
#define CAN_SetDataBitRatePrescaler(CANx, u16Val)                               \
    WRITE_FIELD( (CANx)->CANDBTQ, CANDBTQ_DBRP_Msk, CANDBTQ_DBRP_Pos, (u16Val) - 1 )
/******************************************************************************
 * @brief      Get data bit rate prescaler
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Data bit rate prescaler, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetDataBitRatePrescaler(CANx)                                       \
    ( 1 + READ_FIELD( (CANx)->CANDBTQ, CANDBTQ_DBRP_Msk, CANDBTQ_DBRP_Pos ) )




/******************************************************************************
 * @brief      Set data bit phase buffer segment1
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u8Val : Time quatum number for data bit phase buffer segment1
 *
 * @return     None
 *
 * @note       assert ( ( u8Val >= 1 ) && ( u8Val <= 32 ) )
 *
 ******************************************************************************/
#define CAN_SetDataBitPhaseBufferSegment1(CANx, u8Val)                          \
    WRITE_FIELD( (CANx)->CANDBTQ, CANDBTQ_DSEG1_Msk, CANDBTQ_DSEG1_Pos, (u8Val) - 1 )
/******************************************************************************
 * @brief      Get data bit phase buffer segment1
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Time quatum number for data bit phase buffer segment1, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetDataBitPhaseBufferSegment1(CANx)                                 \
    ( 1 + READ_FIELD( (CANx)->CANDBTQ, CANDBTQ_DSEG1_Msk, CANDBTQ_DSEG1_Pos ) )




/******************************************************************************
 * @brief      Set data bit phase buffer segment2
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u8Val : Time quatum number for data bit phase buffer segment2
 *
 * @return     None
 *
 * @note       assert ( ( u8Val >= 2 ) && ( u8Val <= 16 ) )
 *
 ******************************************************************************/
#define CAN_SetDataBitPhaseBufferSegment2(CANx, u8Val)                          \
    WRITE_FIELD( (CANx)->CANDBTQ, CANDBTQ_DSEG2_Msk, CANDBTQ_DSEG2_Pos, (u8Val) - 1 )
/******************************************************************************
 * @brief      Get data bit phase buffer segment2
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Time quatum number for data bit phase buffer segment2, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetDataBitPhaseBufferSegment2(CANx)                                 \
    ( 1 + READ_FIELD( (CANx)->CANDBTQ, CANDBTQ_DSEG2_Msk, CANDBTQ_DSEG2_Pos ) )




/******************************************************************************
 * @brief      Set data bit resync jump width
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u8Val : Time quatum number for data bit resync jump width
 *
 * @return     None
 *
 * @note       assert ( ( u8Val >= 1 ) && ( u8Val <= 16 ) )
 *
 ******************************************************************************/
#define CAN_SetDataBitResyncJumpWidth(CANx, u8Val)                              \
    WRITE_FIELD( (CANx)->CANDBTQ, CANDBTQ_DSJW_Msk, CANDBTQ_DSJW_Pos, (u8Val) - 1 )
/******************************************************************************
 * @brief      Get data bit resync jump width
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Time quatum number for data bit resync jump width, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetDataBitResyncJumpWidth(CANx)                                     \
    ( 1 + READ_FIELD( (CANx)->CANDBTQ, CANDBTQ_DSJW_Msk, CANDBTQ_DSJW_Pos ) )




/******************************************************************************
 * @brief      Enable transmitter delay compensation
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableTransmitterDelayCompensation(CANx)                            \
    SET_BITS( (CANx)->CANDBTQ, CANDBTQ_TDC_Msk )
/******************************************************************************
 * @brief      Disable transmitter delay compensation
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableTransmitterDelayCompensation(CANx)                           \
    CLEAR_BITS( (CANx)->CANDBTQ, CANDBTQ_TDC_Msk )
/******************************************************************************
 * @brief      Is enable transmitter delay compensation
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - Transmitter delay compensation is disabled
 *             not 0 - Transmitter delay compensation is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableTransmitterDelayCompensation(CANx)                          \
    READ_BITS( (CANx)->CANDBTQ, CANDBTQ_TDC_Msk )
/******************************************************************************
 * @brief      Set transmitter delay offset
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u16Val : Transmitter delay offset value
 *
 * @return     None
 *
 * @note       assert ( ( u16Val >= 0 ) && ( u16Val <= 1023 ) )
 *
 ******************************************************************************/
#define CAN_SetTransmitterDelayOffset(CANx, u16Val)                             \
    WRITE_FIELD( (CANx)->CANTDC, CANTDC_TDCO_Msk, CANTDC_TDCO_Pos, (u16Val) )
/******************************************************************************
 * @brief      Get transmitter delay offset
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Transmitter delay offset value, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetTransmitterDelayOffset(CANx)                                     \
    READ_FIELD( (CANx)->CANTDC, CANTDC_TDCO_Msk, CANTDC_TDCO_Pos )
/******************************************************************************
 * @brief      Set transmitter delay window
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u16Val : Transmitter delay window value
 *
 * @return     None
 *
 * @note       assert ( ( u16Val >= 0 ) && ( u16Val <= 1023 ) )
 *
 ******************************************************************************/
#define CAN_SetTransmitterDelayWindow(CANx, u16Val)                             \
    WRITE_FIELD( (CANx)->CANTDC, CANTDC_TDCW_Msk, CANTDC_TDCW_Pos, (u16Val) )
/******************************************************************************
 * @brief      Get Transmitter Delay Window
 *
 * @param[in]  CANx :  Select the CAN module
 *
 * @return     Transmitter delay window value, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetTransmitterDelayWindow(CANx)                                     \
    READ_FIELD( (CANx)->CANTDC, CANTDC_TDCW_Msk, CANTDC_TDCW_Pos )
/******************************************************************************
 * @brief      Get transmitter delay
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Transmitter delay value, which type is uint16_t
 *
 ******************************************************************************/
#define CAN_GetTransmitterDelay(CANx)                                           \
    READ_FIELD( (CANx)->CANTDC, CANTDC_TDCV_Msk, CANTDC_TDCV_Pos )




/******************************************************************************
 * @brief      Get CAN status
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u32Query: Status, which can be Ored by CAN_StatusEnum
 *
 * @return     0     - None of the queried statuses occurred
 *             Not 0 - Corresponding statuses for non-zero bit occurred
 *
 ******************************************************************************/
#define CAN_GetStatus(CANx, u32Query)                                           \
    ( READ_REG( CANx->CANSTS ) & u32Query )




/******************************************************************************
 * @brief      Get CAN operation mode
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     CAN operation mode, which type is CAN_OperationEnum
 *
 ******************************************************************************/
#define CAN_GetOperationMode(CANx)                                              \
    READ_FIELD( (CANx)->CANSTS, CANSTS_OPMODE_Msk, CANSTS_OPMODE_Pos )
/******************************************************************************
 * @brief      Is CAN in bus off state
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - CAN is not bus off state
 *             Not 0 - CAN is bus off state
 *
 ******************************************************************************/
#define CAN_IsBusOff(CANx)                                                      \
    ( ( CAN_GetOperationMode(CANx) == CAN_OPERATE_BUS_OFF ) ? 1 : 0 )




/******************************************************************************
 * @brief      Get receiver error count
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Receiver error count value, which type is uint8_t
 *
 * @note       During bus off state, this value show bus off recovery procedure
 *
 ******************************************************************************/
#define CAN_GetReceiverErrorCount(CANx)                                         \
    READ_FIELD( (CANx)->CANSTS, CANSTS_REC_Msk, CANSTS_REC_Pos )
/******************************************************************************
 * @brief      Get transmitter error count
 *
 * @param[in]  CANx :  Select the CAN module
 *
 * @return     Transmitter error count value, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetTransmitterErrorCount(CANx)                                      \
    READ_FIELD( (CANx)->CANSTS, CANSTS_TEC_Msk, CANSTS_TEC_Pos )




/******************************************************************************
 * @brief      Has wrote on locked mailbox
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - Write on locked mailbox did not occur
 *             not 0 - Write on locked mailbox occurred
 *
 * @note       This field is read cleared, so need be accessed by uint8_t type
 *
 ******************************************************************************/
#define CAN_IsWriteOnLockedMailbox(CANx)                                        \
    ( ( (uint8_t *)( (uint32_t)(long)( &(CANx)->CANLEC ) ) ) [2] )
/******************************************************************************
 * @brief      Get data phase last error code
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Data phase last error code, which type is CAN_ErrorCodeEnum
 *
 * @note       This field is read cleared, so need be accessed by uint8_t type
 *
 ******************************************************************************/
#define CAN_GetDataPhaseLastErrorCode(CANx)                                     \
    ( ( (uint8_t *)( (uint32_t)(long)( &(CANx)->CANLEC ) ) ) [1] )
/******************************************************************************
 * @brief      Get nominal phase last error code
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Nominal phase last error code, which type is CAN_ErrorCodeEnum
 *
 * @note       This field is read cleared, so need be accessed by uint8_t type
 *
 ******************************************************************************/
#define CAN_GetLastErrorCode(CANx)                                              \
    ( ( (uint8_t *)( (uint32_t)(long)( &(CANx)->CANLEC ) ) ) [0] )




/******************************************************************************
 * @brief      Enable misc interrupt
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u32Int: Select interrupts, which can be Ored by CAN_MiscIntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMiscInt(CANx, u32Int)                                         \
    SET_BITS( (CANx)->CANMIE, (uint32_t)(u32Int) )
/******************************************************************************
 * @brief      Disable misc interrupt
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u32Int: Select interrupts, which can be Ored by CAN_MiscIntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMiscInt(CANx, u32Int)                                        \
    CLEAR_BITS( (CANx)->CANMIE, (uint32_t)(u32Int) )
/******************************************************************************
 * @brief      Is enable misc interrupt
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u32Query: Select interrupts, which can be Ored by CAN_MiscIntEnum
 *
 * @return     0     - None of the queried interrupts is enabled
 *             Not 0 - Corresponding interrupts for non-zero bit is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMiscInt(CANx, u32Query)                                     \
    READ_BITS( (CANx)->CANMIE, (uint32_t)(u32Query) )
/******************************************************************************
 * @brief      Get misc event raw flag
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u32Query: Select interrupts, which can be Ored by CAN_MiscIntEnum
 *
 * @return     0     - None of the queried events occurred
 *             Not 0 - Corresponding events for non-zero bit occurred
 *
 ******************************************************************************/
#define CAN_GetMiscIntRawFlag(CANx, u32Query)                                   \
    READ_BITS( (CANx)->CANMRAWIF, (uint32_t)(u32Query) )
/******************************************************************************
 * @brief      Get misc interrupt flag
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u32Query: Select interrupts, which can be Ored by CAN_MiscIntEnum
 *
 * @return     0     - None of the queried interrupts occurred
 *             Not 0 - Corresponding interrupts for non-zero bit occurred
 *
 ******************************************************************************/
#define CAN_GetMiscIntFlag(CANx, u32Query)                                      \
    READ_BITS( (CANx)->CANMIF, (uint32_t)(u32Query) )
/******************************************************************************
 * @brief      Clear misc interrupt
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u32Int: Select interrupts, which can be Ored by CAN_MiscIntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ClearMiscInt(CANx, u32Int)                                          \
    WRITE_REG( (CANx)->CANMIC, (uint32_t)(u32Int) )




/******************************************************************************
 * @brief      Get transfer group interrupt flag
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u32Query: Select interrupts, which can be Ored by CAN_TranGrpIntEnum
 *
 * @return     0     - None of the queried interrupts occurred
 *             Not 0 - Corresponding interrupts for non-zero bit occurred
 *
 ******************************************************************************/
#define CAN_GetTransferGroupIntFlag(CANx, u32Query)                             \
    READ_BITS( (CANx)->CANTGIF, (u32Query) )
/******************************************************************************
 * @brief      Clear transfer group interrupt flag
 *
 * @param[in]  CANx  : Select the CAN module
 * @param[in]  u32Int: Select interrupts, which can be Ored by CAN_TranGrpIntEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ClearTransferGroupInt(CANx, u32Int)                                 \
    WRITE_REG( (CANx)->CANTGIC, (u32Int) )




/******************************************************************************
 * @brief      Set Receiver Error Counter load value
 *
 * @param[in]  CANx : Select the CAN module
 * @param[in]  u8Val: REC load value, which will be used when receive valid frame and REC bigger than 127
 *
 * @note       assert ( ( u8Data >= 119 ) && ( u8Data <= 127 ) )
 *
 ******************************************************************************/
#define CAN_SetReceiverErrorCounterLoadValue(CANx, u8Val)                       \
    WRITE_FIELD( (CANx)->CANECCTL, CANECCTL_RECLD_Msk, CANECCTL_RECLD_Pos, u8Val )
/******************************************************************************
 * @brief      Get Receiver Error Counter load value
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     REC load value, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetReceiverErrorCounterLoadValue(CANx)                              \
    READ_FIELD( (CANx)->CANECCTL, CANECCTL_RECLD_Msk, CANECCTL_RECLD_Pos )




/******************************************************************************
 * @brief      Set error warn value
 *
 * @param[in]  CANx : Select the CAN module
 * @param[in]  u8Val: Error warn value. When TEC or REC bigger than this value, will trigger warning
 *
 * @return     None
 *
 * @note       assert ( ( u8Data >= 80 ) && ( u8Data <= 127 ) )
 *
 ******************************************************************************/
#define CAN_SetErrorWarnValue(CANx, u8Val)                                      \
    WRITE_FIELD( (CANx)->CANECCTL, CANECCTL_ERRWARN_Msk, CANECCTL_ERRWARN_Pos, u8Val )
/******************************************************************************
 * @brief      Get error warn value
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Error warn value, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetErrorWarnValue(CANx)                                             \
    READ_FIELD( (CANx)->CANECCTL, CANECCTL_ERRWARN_Msk, CANECCTL_ERRWARN_Pos )




/******************************************************************************
 * @brief      Get mailbox 0 to 31 transmit request flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes have transmit request
 *             Not 0 - Corresponding mailboxes for non-zero bit have transmit request
 *
 ******************************************************************************/
#define CAN_GetMailbox0To31TxRequestFlag(CANx, u32Msk)                          \
    READ_BITS( (CANx)->CANTXREQ[0], (u32Msk) )
/******************************************************************************
 * @brief      Get mailbox 31 to 63 transmit request flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes have transmit request
 *             Not 0 - Corresponding mailboxes for non-zero bit have transmit request
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_GetMailbox32To63TxRequestFlag(CANx, u32Msk)                         \
    READ_BITS( (CANx)->CANTXREQ[1], (u32Msk) )




/******************************************************************************
 * @brief      Get mailbox 0 to 31 new message flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes have new message
 *             Not 0 - Corresponding mailboxes for non-zero bit have new message
 *
 ******************************************************************************/
#define CAN_GetMailbox0To31NewMessageFlag(CANx, u32Msk)                         \
    READ_BITS( (CANx)->CANMSGNEW[0], (u32Msk) )
/******************************************************************************
 * @brief      Get mailbox 32 to 63 new message flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes have new message
 *             Not 0 - Corresponding mailboxes for non-zero bit have new message
 *
 ******************************************************************************/
#define CAN_GetMailbox32To63NewMessageFlag(CANx, u32Msk)                        \
    READ_BITS( (CANx)->CANMSGNEW[1], (u32Msk) )




/******************************************************************************
 * @brief      Get mailbox 0 to 31 transfer done interrupt flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes transferred done
 *             Not 0 - Corresponding mailboxes for non-zero bit transferred done
 *
 ******************************************************************************/
#define CAN_GetMailbox0To31TransferDoneIntFlag(CANx, u32Msk)                    \
    READ_BITS( (CANx)->CANMSGIF[0], (u32Msk) )
/******************************************************************************
 * @brief      Get mailbox 32 to 63 transfer done interrupt flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes transferred done
 *             Not 0 - Corresponding mailboxes for non-zero bit transferred done
 *
 ******************************************************************************/
#define CAN_GetMailbox32To63TransferDoneIntFlag(CANx, u32Msk)                   \
    READ_BITS( (CANx)->CANMSGIF[1], (u32Msk) )




/******************************************************************************
 * @brief      Get mailbox 0 to 31 enabled flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes is enabled
 *             Not 0 - Corresponding mailboxes for non-zero bit is enabled
 *
 ******************************************************************************/
#define CAN_GetMailbox0To31EnabledFlag(CANx, u32Msk)                            \
    READ_BITS( (CANx)->CANMBEN[0], (u32Msk) )
/******************************************************************************
 * @brief      Get mailbox 32 to 63 enabled flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u32Msk : Mailbox select mask, each bit represent one mailbox
 *
 * @return     0     - None of the queried mailboxes is enabled
 *             Not 0 - Corresponding mailboxes for non-zero bit is enabled
 *
 ******************************************************************************/
#define CAN_GetMailbox32To63EnabledFlag(CANx, u32Msk)                           \
    READ_BITS( (CANx)->CANMBEN[1], (u32Msk) )




/******************************************************************************
 * @brief      Enable timestamp
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableTimestamp(CANx)                                               \
    SET_BITS( (CANx)->CANTSCTL, CANTSCTL_TSEN_Msk )
/******************************************************************************
 * @brief      Disable timestamp
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableTimestamp(CANx)                                              \
    CLEAR_BITS( (CANx)->CANTSCTL, CANTSCTL_TSEN_Msk )
/******************************************************************************
 * @brief      Is enable timestamp
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     0     - Timestamp is disabled
 *             not 0 - Timestamp is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableTimestamp(CANx)                                             \
    READ_BITS( (CANx)->CANTSCTL, CANTSCTL_TSEN_Msk )
/******************************************************************************
 * @brief      Reset timestamp
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ResetTimestamp(CANx)                                                \
    WRITE_REG( (CANx)->CANTSCNT, 0 )
/******************************************************************************
 * @brief      Get timestamp count value
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     Current timestamp count value, which type is uint32_t and count based on sample point
 *
 ******************************************************************************/
#define CAN_GetTimestamp(CANx)                                                  \
    READ_REG( (CANx)->CANTSCNT )




/******************************************************************************
 * @brief      Enable write access to the protected CANx register
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_WALLOW(CANx)                                                        \
    WRITE_REG( (CANx)->CANREGKEY, 0x1ACCE551U )
/******************************************************************************
 * @brief      Disable write access to the protected CANx register
 *
 * @param[in]  CANx : Select the CAN module
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_WDIS(CANx)                                                          \
    WRITE_REG( (CANx)->CANREGKEY, 0x0U )








/******************************************************************************
 * @brief      Set mailbox control information
 *
 * @param[in]  CANx     : Select the CAN module
 * @param[in]  u8MBoxId   : Mailbox index
 * @param[in]  u32Sel   : Ored by CAN_MailboxControlEnum
 *
 * @return     None
 *
 * @note       Validation write value after write control configuration
 *             e.g.
 *             CAN_SetMailboxControlInfo( CANx, u8MBoxId, u32Sel )
 *             if ( CAN_IsWriteOnLockedMailbox(CANx) )
 *             {
 *                 // current mailbox is busy transfering message, can't be written
 *                 // and will ignore current write access.
 *             }
 *
 ******************************************************************************/
#define CAN_SetMailboxControlInfo( CANx, u8MBoxId, u32Sel )                       \
    WRITE_REG( (CANx)->CANMBOX[(u8MBoxId)].CANMBOXMCTL,                           \
        ( (CANx)->CANMBOX[(u8MBoxId)].CANMBOXMCTL & ~CAN_MBOX_ALL_CONTROL_FIELD ) | (u32Sel) \
    )
/******************************************************************************
 * @brief      Get mailbox control information
 *
 * @param[in]  CANx     : Select the CAN module
 * @param[in]  u8MBoxId   : Mailbox index
 * @param[in]  u32Query : Ored by CAN_MailboxControlEnum
 *
 * @return     0     - None of the queried statuses occurred
 *             Not 0 - Corresponding statuses for non-zero bit occurred
 *
 ******************************************************************************/
#define CAN_GetMailboxControlInfo( CANx, u8MBoxId, u32Query )                     \
    READ_BITS( (CANx)->CANMBOX[(u8MBoxId)].CANMBOXMCTL, (u32Query) )




/******************************************************************************
 * @brief      Set message data length
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  u8Len  : Message data length
 *
 * @return     None
 *
 * @note       assert ( ( u8Len >= 0 ) && ( u8Len <= 64 ) )
 *
 ******************************************************************************/
#define CAN_SetMessageDataLength( CANx, u8MBoxId, u8Len )                         \
    WRITE_FIELD( (CANx)->CANMBOX[(u8MBoxId)].CANMBOXMCTL,                         \
        CANMBOXMCTL_DLC_Msk,                                                    \
        CANMBOXMCTL_DLC_Pos,                                                    \
        CAN_EncodeDataLength( (u8Len) )                                         \
    )
/******************************************************************************
 * @brief      Get message data length
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message data length, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetMessageDataLength( CANx, u8MBoxId )                                \
    CAN_DecodeDataLength(                                                       \
        READ_FIELD( (CANx)->CANMBOX[(u8MBoxId)].CANMBOXMCTL                       \
            , CANMBOXMCTL_DLC_Msk                                               \
            , CANMBOXMCTL_DLC_Pos                                               \
        )                                                                       \
    )




/******************************************************************************
 * @brief      Force send Error State Indicator bit with dominant value
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ForceSendDominantErrorStateIndicator(CANx, u8MBoxId)                  \
    WRITE_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL,                             \
        ( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL & ~CANMBOXMCTL_ESI_Msk ) | CANMBOXMCTL_ESICTL_Msk \
    )
/******************************************************************************
 * @brief      Force send Error State Indicator bit with recessive value
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ForceSendRecessiveErrorStateIndicator(CANx, u8MBoxId)                 \
    WRITE_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL,                             \
        (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL | CANMBOXMCTL_ESI_Msk | CANMBOXMCTL_ESICTL_Msk \
    )
/******************************************************************************
 * @brief      Disable force send Error State Indicator bit
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 * @note       Send ESI with dominant bit when node is error active state;
 *             Send ESI with recessive bit when node is error passive state.
 *
 ******************************************************************************/
#define CAN_DisableForceSendErrorStateIndicator(CANx, u8MBoxId)                   \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_ESI_Msk | CANMBOXMCTL_ESICTL_Msk )
/******************************************************************************
 * @brief      Is force send Error State Indicator bit
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Force send ESI is disabled
 *             not 0 - Force send ESI is enabled
 *
 ******************************************************************************/
#define CAN_IsForceSendErrorStateIndicator(CANx, u8MBoxId)                        \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_ESICTL_Msk )
/******************************************************************************
 * @brief      Is recessive Error State Indicator bit
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 * @return     0     - ESI is dominant bit
 *             not 0 - ESI is recessive bit
 *
 ******************************************************************************/
#define CAN_GetMessageErrorStateIndicator(CANx, u8MBoxId)                         \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_ESI_Msk )




/******************************************************************************
 * @brief      Enable Bit Rate Switch
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMessageBitRateSwitch(CANx, u8MBoxId )                           \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_BRS_Msk )
/******************************************************************************
 * @brief      Disable Bit Rate Switch
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMessageBitRateSwitch(CANx, u8MBoxId )                          \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_BRS_Msk )
/******************************************************************************
 * @brief      Is enable Bit Rate Switch
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - BRS is disabled
 *             not 0 - BRS is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMessageBitRateSwitch(CANx, u8MBoxId )                         \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_BRS_Msk )




/******************************************************************************
 * @brief      Enable Flexible Data rate Format
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMessageFlexibleDataRate(CANx, u8MBoxId )                        \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_FDF_Msk )
/******************************************************************************
 * @brief      Disable Flexible Data rate Format
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMessageFlexibleDataRate(CANx, u8MBoxId )                       \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_FDF_Msk )
/******************************************************************************
 * @brief      Is enable Flexible Data rate Format
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - FDF is disabled
 *             not 0 - FDF is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMessageFlexibleDataRate(CANx, u8MBoxId )                      \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_FDF_Msk )




/******************************************************************************
 * @brief      Is mailbox locked
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox is not locked
 *             not 0 - Mailbox is locked
 *
 ******************************************************************************/
#define CAN_IsMailboxLocked(CANx, u8MBoxId )                                      \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_LOCK_Msk )




/******************************************************************************
 * @brief      Enable mailbox overwrite
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMailboxOverwrite(CANx, u8MBoxId )                               \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_OVWR_Msk )
/******************************************************************************
 * @brief      Disable mailbox overwrite
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMailboxOverwrite(CANx, u8MBoxId )                              \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_OVWR_Msk )
/******************************************************************************
 * @brief      Is enable mailbox overwrite
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox overwrite is disabled
 *             not 0 - Mailbox overwrite is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMailboxOverwrite(CANx, u8MBoxId )                             \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_OVWR_Msk )




/******************************************************************************
 * @brief      Enable mailbox end of block
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMailboxEndOfBlock(CANx, u8MBoxId )                              \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_EOB_Msk )
/******************************************************************************
 * @brief      Disable mailbox end of block
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMailboxEndOfBlock(CANx, u8MBoxId )                             \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_EOB_Msk )
/******************************************************************************
 * @brief      Is enable mailbox end of block
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - EOB is disabled
 *             not 0 - EOB is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMailboxEndOfBlock(CANx, u8MBoxId )                            \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_EOB_Msk )




/******************************************************************************
 * @brief      Enable mailbox transfer done interrupt
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMailboxTransferInterrupt(CANx, u8MBoxId )                       \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_IE_Msk )
/******************************************************************************
 * @brief      Disable mailbox transfer done interrupt
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMailboxTransferInterrupt(CANx, u8MBoxId )                      \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_IE_Msk )
/******************************************************************************
 * @brief      Is enable mailbox transfer done interrupt
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox transfer done interrupt is disabled
 *             not 0 - Mailbox transfer done interrupt is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMailboxTransferInterrupt(CANx, u8MBoxId )                     \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_IE_Msk )




/******************************************************************************
 * @brief      Is mailbox transfer done interrupt occured
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox transfer done interrupt did not occur
 *             not 0 - Mailbox transfer done interrupt occurred
 *
 ******************************************************************************/
#define CAN_IsMailboxTransferInterruptOccured(CANx, u8MBoxId )                    \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_IF_Msk )
/******************************************************************************
 * @brief      Clear mailbox transfer done interrupt flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ClearMailboxTransferInterrupt(CANx, u8MBoxId )                        \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_IF_Msk )




/******************************************************************************
 * @brief      Enable mailbox transmit request
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMailboxTransmitRequest(CANx, u8MBoxId )                         \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_TXREQ_Msk )
/******************************************************************************
 * @brief      Disable mailbox transmit request
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMailboxTransmitRequest(CANx, u8MBoxId )                        \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_TXREQ_Msk )
/******************************************************************************
 * @brief      Is enable mailbox transmit request
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox transfer done interrupt is disabled
 *             not 0 - Mailbox transfer done interrupt is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMailboxTransmitRequest(CANx, u8MBoxId )                       \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_TXREQ_Msk )




/******************************************************************************
 * @brief      Is message lost
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Message is not lost
 *             not 0 - Message is lost
 *
 ******************************************************************************/
#define CAN_IsMessageLost(CANx, u8MBoxId )                                        \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_LOST_Msk )
/******************************************************************************
 * @brief      Clear message lost flag
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ClearMessageLost(CANx, u8MBoxId )                                     \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_LOST_Msk )




/******************************************************************************
 * @brief      Enable message new
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMessageNew(CANx, u8MBoxId )                                     \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_NEW_Msk )
/******************************************************************************
 * @brief      Disable message new
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMessageNew(CANx, u8MBoxId )                                    \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_NEW_Msk )
/******************************************************************************
 * @brief      Is message new
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Message is not new
 *             not 0 - Message is new
 *
 ******************************************************************************/
#define CAN_IsMessageNew(CANx, u8MBoxId )                                         \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_NEW_Msk )




/******************************************************************************
 * @brief      Enable mailbox response remote frame
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMailboxResponseRemoteFrame(CANx, u8MBoxId )                     \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_RMTEN_Msk )
/******************************************************************************
 * @brief      Disable mailbox response remote frame
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMailboxResponseRemoteFrame(CANx, u8MBoxId )                    \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_RMTEN_Msk )
/******************************************************************************
 * @brief      Is enable mailbox response remote frame
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox response remote frame is disabled
 *             not 0 - Mailbox response remote frame is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMailboxResponseRemoteFrame(CANx, u8MBoxId )                   \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_RMTEN_Msk )




/******************************************************************************
 * @brief      Set message data transfer direction
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  eDir   : Message data transfer direction, which type is CAN_DataDirectionEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_SetMessageDataDirection(CANx, u8MBoxId, eDir )                        \
    WRITE_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_DIR_Msk, CANMBOXMCTL_DIR_Pos, (eDir) )
/******************************************************************************
 * @brief      Get message data transfer direction
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message data transfer direction, which type is CAN_DataDirectionEnum
 *
 ******************************************************************************/
#define CAN_GetMessageDataDirection(CANx, u8MBoxId )                              \
    READ_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_DIR_Msk, CANMBOXMCTL_DIR_Pos )




/******************************************************************************
 * @brief      Enable mailbox
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMailbox(CANx, u8MBoxId )                                        \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_EN_Msk )
/******************************************************************************
 * @brief      Disable mailbox
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMailbox(CANx, u8MBoxId )                                       \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_EN_Msk )
/******************************************************************************
 * @brief      Is enable mailbox
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - Mailbox response remote frame is disabled
 *             not 0 - Mailbox response remote frame is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMailbox(CANx, u8MBoxId )                                      \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXMCTL, CANMBOXMCTL_EN_Msk )




/**** **************************************************************************
 * @brief      Clear message timestamp
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_ClearMessageTimestamp(CANx, u8MBoxId )                                \
    WRITE_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXMTS, 0x0U )
/******************************************************************************
 * @brief      Get message timestamp
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message timestamp based on CAN bit, which size is uint32_t
 *
 ******************************************************************************/
#define CAN_GetMessageTimestamp(CANx, u8MBoxId )                                  \
    READ_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXMTS )




/******************************************************************************
 * @brief      Set message identifier
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  u32Id  : Message frame identifier
 *
 * @return     None
 *
 * @note       For standard frame format, need left shift 18-bit for raw identifier
 *
 ******************************************************************************/
#define CAN_SetMessageStandardIdentifier(CANx, u8MBoxId, u32Id )                  \
    WRITE_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_ID_Msk, CANMBOXFID_ID_Pos, ( (u32Id) << 18 ) )

#define CAN_SetMessageExtendedIdentifier(CANx, u8MBoxId, u32Id )                  \
    WRITE_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_ID_Msk, CANMBOXFID_ID_Pos, (u32Id) )

/******************************************************************************
 * @brief      Get message identifier
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message frame identifier, which size is uint32_t
 *
 * @note       For standard frame format, u32Id need right shift 18-bit
 *
 ******************************************************************************/
#define CAN_GetMessageStandardIdentifier(CANx, u8MBoxId )                         \
    ( READ_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID >> 18 ) & 0x7FFU )

#define CAN_GetMessageExtendedIdentifier(CANx, u8MBoxId )                         \
    READ_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_ID_Msk, CANMBOXFID_ID_Pos )




/******************************************************************************
 * @brief      Set message identifier mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  u32Msk : Message frame identifier mask
 *
 * @return     None
 *
 * @note       For standard frame format, need left shift 18-bit for raw identifier
 *
 ******************************************************************************/
#define CAN_SetMessageStandardIdentifierMask(CANx, u8MBoxId, u32Msk )             \
    WRITE_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_ID_Msk, CANMBOXFMSK_ID_Pos, ( (u32Msk) << 18 ) )

#define CAN_SetMessageExtendedIdentifierMask(CANx, u8MBoxId, u32Msk )             \
    WRITE_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_ID_Msk, CANMBOXFMSK_ID_Pos, (u32Msk) )

/******************************************************************************
 * @brief      Get message identifier mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message frame identifier mask, which size is uint32_t
 *
 * @note       For standard frame format, u32Msk need right shift 18-bit
 *
 ******************************************************************************/
#define CAN_GetMessageStandardIdentifierMask(CANx, u8MBoxId )                     \
    ( READ_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK >> 18 ) & 0x7FFU )

#define CAN_GetMessageExtendedIdentifierMask(CANx, u8MBoxId )                     \
    READ_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_ID_Msk, CANMBOXFMSK_ID_Pos )




/******************************************************************************
 * @brief      Enable message Extended Identifier
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMessageExtendedIdentifier(CANx, u8MBoxId )                      \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_IDE_Msk )
/******************************************************************************
 * @brief      Disable message Extended Identifier
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMessageExtendedIdentifier(CANx, u8MBoxId )                     \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_IDE_Msk )
/******************************************************************************
 * @brief      Is enable message Extended Identifier
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - IDE is disabled
 *             not 0 - IDE is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMessageExtendedIdentifier(CANx, u8MBoxId )                    \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_IDE_Msk )
/******************************************************************************
 * @brief      Enable message Extended Identifier mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMessageExtendedIdentifierMask(CANx, u8MBoxId )                  \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_IDE_Msk )
/******************************************************************************
 * @brief      Disable message Extended Identifier mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMessageExtendedIdentifierMask(CANx, u8MBoxId )                 \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_IDE_Msk )
/******************************************************************************
 * @brief      Is enable message Extended Identifier mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - IDE mask is disabled
 *             not 0 - IDE mask is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMessageExtendedIdentifierMask(CANx, u8MBoxId )                \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_IDE_Msk )




/******************************************************************************
 * @brief      Set message frame type
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  eTyp   : Message frame type, which type is CAN_FrameTypeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_SetMessageFrameType(CANx, u8MBoxId, eTyp )                            \
    WRITE_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_RTR_Msk, CANMBOXFID_RTR_Pos, (eTyp) )
/******************************************************************************
 * @brief      Get message frame type
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message frame type, which type is CAN_FrameTypeEnum
 *
 ******************************************************************************/
#define CAN_GetMessageFrameType(CANx, u8MBoxId )                                  \
    READ_FIELD( (CANx)->CANMBOX[u8MBoxId].CANMBOXFID, CANMBOXFID_RTR_Msk, CANMBOXFID_RTR_Pos )
/******************************************************************************
 * @brief      Enable message frame type mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_EnableMessageFrameTypeMask(CANx, u8MBoxId )                           \
    SET_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_RTR_Msk )
/******************************************************************************
 * @brief      Disable message frame type mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_DisableMessageFrameTypeMask(CANx, u8MBoxId )                          \
    CLEAR_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_RTR_Msk )
/******************************************************************************
 * @brief      Is enable message frame type mask
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     0     - RTR mask is disabled
 *             not 0 - RTR mask is enabled
 *
 ******************************************************************************/
#define CAN_IsEnableMessageFrameTypeMask(CANx, u8MBoxId )                         \
    READ_BITS( (CANx)->CANMBOX[u8MBoxId].CANMBOXFMSK, CANMBOXFMSK_RTR_Msk )




/******************************************************************************
 * @brief      Set message frame format type
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 * @param[in]  eFmt   : Message frame format, which type is CAN_FrameFormatEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CAN_SetMessageFrameFormat(CANx, u8MBoxId, eFmt)                           \
{                                                                               \
    ( (eFmt) & 0x1 ) ? CAN_EnableMessageExtendedIdentifier ( (CANx), (u8MBoxId) ) \
                     : CAN_DisableMessageExtendedIdentifier( (CANx), (u8MBoxId) ) \
                     ;                                                          \
    ( (eFmt) & 0x2 ) ? CAN_EnableMessageFlexibleDataRate   ( (CANx), (u8MBoxId) ) \
                     : CAN_DisableMessageFlexibleDataRate  ( (CANx), (u8MBoxId) ) \
                     ;                                                          \
}
/******************************************************************************
 * @brief      Get message frame format type
 *
 * @param[in]  CANx   : Select the CAN module
 * @param[in]  u8MBoxId : Mailbox index
 *
 * @return     Message frame format, which type is CAN_FrameFormatEnum
 *
 ******************************************************************************/
__STATIC_INLINE uint32_t CAN_GetMessageFrameFormat(CAN_REGS *CANx, uint32_t u8MBoxId)
{
    uint32_t u32FrameFormatType = (CAN_IsEnableMessageExtendedIdentifier ( (CANx), (u8MBoxId) ) ? 0x1U : 0x0U );
    u32FrameFormatType |= (CAN_IsEnableMessageFlexibleDataRate   ( (CANx), (u8MBoxId) ) ? 0x2U : 0x0U );

    return u32FrameFormatType;
}

/******************************************************************************
 * @brief      Set message data by word
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u8MBoxId  : Mailbox index
 * @param[in]  u8WIdx  : Message data word index, valid range is 0 to 15
 * @param[in]  u32Data : Message data
 *
 * @return     None
 *
 * @note       Only support 32-bit write mailbox
 *
 ******************************************************************************/
#define CAN_SetMessageDataByWord(CANx, u8MBoxId, u8WIdx, u32Data)              \
    WRITE_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXFDW[(u8WIdx)], (u32Data) )
/******************************************************************************
 * @brief      Get message data by word
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u8MBoxId  : Mailbox index
 * @param[in]  u8WIdx  : Message data word index, valid range is 0 to 15
 *
 * @return     Message data, which type is uint32_t
 *
 ******************************************************************************/
#define CAN_GetMessageDataByWord(CANx, u8MBoxId, u8WIdx)                          \
    READ_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXFDW[(u8WIdx)] )
/******************************************************************************
 * @brief      Get message data by byte
 *
 * @param[in]  CANx    : Select the CAN module
 * @param[in]  u8MBoxId  : Mailbox index
 * @param[in]  u8BIdx  : Message data byte index, valid range is 0 to 63
 *
 * @return     Message data, which type is uint8_t
 *
 ******************************************************************************/
#define CAN_GetMessageDataByByte(CANx, u8MBoxId, u8BIdx)                          \
    ( 0xFFU & ( READ_REG( (CANx)->CANMBOX[u8MBoxId].CANMBOXFDW[(u8BIdx) >> 2] ) >> ( ( (u8BIdx) & 0x3U ) << 3 ) ) )




/******************************************************************************
 *
 * @brief Enable auto bus off recovery sequence
 *
 * @param[in] CANx : Select the CAN module
 * @param[in] u16BusOffDelay : Bus off recovery delay based on nominal bit time
 *
 * @return None
 *
 ******************************************************************************/
__STATIC_INLINE void CAN_EnableAutoBusOffRecovery(CAN_REGS *CANx, uint16_t u16BusOffDelay) 
{ 
    SET_BITS( (CANx)->CANCTL, CANCTL_AUTOON_Msk ); 
    WRITE_FIELD( (CANx)->CANBRDLY, CANBRDLY_DLY_Msk, CANBRDLY_DLY_Pos, u16BusOffDelay ); 
}




/******************************************************************************
*
* @brief Disable auto bus off recovery sequence
*
* @param[in] CANx : Select the CAN module
*
* @return None
*
******************************************************************************/
__STATIC_INLINE void CAN_DisabeAutoBusOffRecovery(CAN_REGS *CANx) 
{ 
    CLEAR_BITS( (CANx)->CANCTL, CANCTL_AUTOON_Msk ); 
    WRITE_FIELD( (CANx)->CANBRDLY, CANBRDLY_DLY_Msk, CANBRDLY_DLY_Pos, 1 ); 
}




ErrorStatus CAN_Reset( CAN_REGS *CANx ) ;

void        CAN_InitMessageRAM( CAN_REGS *CANx ) ;

uint8_t     CAN_EncodeDataLength( uint8_t u8DataLen ) ;
uint8_t     CAN_DecodeDataLength( uint8_t u8DLC ) ;
void        CAN_SetMessageData( CAN_REGS *CANx, uint8_t u8MBoxId, uint8_t *pu8Data, uint8_t u8Size ) ;
void        CAN_GetMessageData( CAN_REGS *CANx, uint8_t u8MBoxId, uint8_t *pu8Data, uint8_t u8Size ) ;

ErrorStatus CAN_SetMessage( CAN_REGS *CANx, CAN_MessageTypeDef *pMsg ) ;
void        CAN_GetMessage( CAN_REGS *CANx, CAN_MessageTypeDef *pMsg ) ;
ErrorStatus CAN_AbortMessageTransferRequest(CAN_REGS *CANx, uint8_t u8MBoxId);




#ifdef __cplusplus
}
#endif

#endif /* CAN_TEST_H */

/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
