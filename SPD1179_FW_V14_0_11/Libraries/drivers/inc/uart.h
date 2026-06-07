/******************************************************************************
 * @file     uart.h
 * @brief    UART module header file.
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


#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  UART NRZ type definition
 */
typedef enum
{
    UART_NRZ_LEVEL                  = 0,  /*!< NRZ level coding. High level for 1 and low level for 0.  */
    UART_NRZ_SPACE                  = 2,  /*!< NRZ space coding. Keep constant on 1 and toggle on 0.    */
    UART_NRZ_MARK                   = 3,  /*!< NRZ mark coding. Keep constant on 0 and toggle on 1.     */
} UART_NRZModeEnum;




/**
 *  @brief  UART data bit type definition
 */
typedef enum
{
    UART_5_DATA_BIT                 = 0,  /*!< Data is 5-bit          */
    UART_6_DATA_BIT                 = 1,  /*!< Data is 6-bit          */
    UART_7_DATA_BIT                 = 2,  /*!< Data is 7-bit          */
    UART_8_DATA_BIT                 = 3,  /*!< Data is 8-bit          */
} UART_DataBitEnum;




/**
 *  @brief  UART parity bit type definition
 */
typedef enum
{
    UART_NO_PARITY                  = 0,  /*!< No parity bit          */
    UART_EVEN_PARITY                = 4,  /*!< Even parity            */
    UART_ODD_PARITY                 = 5,  /*!< Odd parity             */
    UART_STICKY_HIGH_PARITY         = 6,  /*!< Parity bit is always 1 */
    UART_STICKY_LOW_PARITY          = 7,  /*!< Parity bit is always 0 */
} UART_ParityBitEnum;




/**
 *  @brief  UART stop bit type definition
 */
typedef enum
{
    UART_1_STOP_BIT                 = 0,  /*!< 1 stop-bit         */
    UART_2_STOP_BIT                 = 1,  /*!< 2 stop-bit         */
} UART_StopBitEnum;




/**
 *  @brief  UART FIFO access width type definition
 */
typedef enum
{
    UART_FIFO_ACCESS_IN_BYTE      = 0,  /*!< Access in Byte     */
    UART_FIFO_ACCESS_IN_WORD      = 1,  /*!< Access in Word     */
} UART_FIFOAccessWidthEnum;




/**
 *  @brief  UART SIR TX format type definition
 */
typedef enum
{
    UART_SIR_TX_BY_DUTY             = 0,  /*!< Transmit pulse has a constant duty cyle as 3/16 bit time             */
    UART_SIR_TX_BY_CYCLE            = 1,  /*!< Transmit pulse has a constant width as specified UART clock cycles   */
} UART_SIRTxFormatEnum;




/**
 *  @brief  UART auto baud update method type definition
 */
typedef enum
{
    UART_BAUD_COUNT_UPDATE_BY_HARDWARE  = 0,    /*!< Baud count is updated by hardware upon auto-baud lock event            */
    UART_BAUD_COUNT_UPDATE_BY_SOFTWARE  = 1,    /*!< Baud count is updated by software even auto-baud detection is enabled  */
} UART_BaudCountUpdateEnum;




/**
 *  @brief  UART SIR polariy type definition
 */
typedef enum
{
    UART_SIR_NEGATIVE_PULSE_AS_ZERO = 0,  /*!< Negative pulse is regarded as 0  */
    UART_SIR_POSITIVE_PULSE_AS_ZERO = 1,  /*!< Positive pulse is regarded as 0  */
} UART_SIRPolarityEnum;




/**
 *  @brief  LIN mode definition
 */
typedef enum
{
    LIN_SLAVE                       = 0,  /*!< Operates as LIN slave            */
    LIN_MASTER                      = 1,  /*!< Operates as LIN master           */
} LIN_ModeEnum;




/**
 *  @brief  LIN synchronization break filed length definition
 */
typedef enum
{
    LIN_SBRKLEN_13_BIT              = 0,  /*!< Synchronization break field is 13-bit  */
    LIN_SBRKLEN_14_BIT              = 1,  /*!< Synchronization break field is 14-bit  */
    LIN_SBRKLEN_15_BIT              = 2,  /*!< Synchronization break field is 15-bit  */
    LIN_SBRKLEN_16_BIT              = 3,  /*!< Synchronization break field is 16-bit  */
    LIN_SBRKLEN_17_BIT              = 4,  /*!< Synchronization break field is 17-bit  */
    LIN_SBRKLEN_18_BIT              = 5,  /*!< Synchronization break field is 18-bit  */
    LIN_SBRKLEN_19_BIT              = 6,  /*!< Synchronization break field is 19-bit  */
    LIN_SBRKLEN_20_BIT              = 7,  /*!< Synchronization break field is 20-bit  */
} LIN_SyncBreakLenEnum;




/**
 *  @brief  LIN synchronization break delimiter length definition
 */
typedef enum
{
    LIN_SBRKDEL_1_BIT               = 0,  /*!< Synchronization break delimiter is 1-bit  */
    LIN_SBRKDEL_2_BIT               = 1,  /*!< Synchronization break delimiter is 2-bit  */
    LIN_SBRKDEL_3_BIT               = 2,  /*!< Synchronization break delimiter is 3-bit  */
    LIN_SBRKDEL_4_BIT               = 3,  /*!< Synchronization break delimiter is 4-bit  */
} LIN_SyncBreakDelimiterEnum;




/**
 *  @brief  LIN response type definition
 */
typedef enum
{
    LIN_RESPONSE_NONE               = 0,  /*!< No response                                      */
    LIN_RESPONSE_RX                 = 1,  /*!< Response with data receiver                      */
    LIN_RESPONSE_TX                 = 2,  /*!< Response with data transmitter                   */
    LIN_RESPONSE_TR                 = 3,  /*!< Response with both data receiver and transmitter */
} LIN_ResponseEnum;




/**
 *  @brief  LIN response field length definition
 */
typedef enum
{
    LIN_RESPONSE_X_BYTE             = 0,  /*!< Response filed length is decided by LINID[5:4] */
    LIN_RESPONSE_1_BYTE             = 1,  /*!< Response filed length is 1-byte                */
    LIN_RESPONSE_2_BYTE             = 2,  /*!< Response filed length is 2-byte                */
    LIN_RESPONSE_3_BYTE             = 3,  /*!< Response filed length is 3-byte                */
    LIN_RESPONSE_4_BYTE             = 4,  /*!< Response filed length is 4-byte                */
    LIN_RESPONSE_5_BYTE             = 5,  /*!< Response filed length is 5-byte                */
    LIN_RESPONSE_6_BYTE             = 6,  /*!< Response filed length is 6-byte                */
    LIN_RESPONSE_7_BYTE             = 7,  /*!< Response filed length is 7-byte                */
    LIN_RESPONSE_8_BYTE             = 8,  /*!< Response filed length is 8-byte                */
} LIN_ResponseLenEnum;




/**
 *  @brief  LIN Rx FIFO mode definition
 */
typedef enum
{
    LIN_SAVE_ALL_DATA_AND_CHECKSUM  = 0,  /*!< Save the frame data and checksum byte into the Rx FIFO */
    LIN_SAVE_CORRECT_DATA           = 1,  /*!< Save only the frame data when the checksum is correct  */
} LIN_RxFIFOModeEnum;




/**
 *  @brief  LIN checksum type definition
 */
typedef enum
{
    LIN_CLASSIC_CHECKSUM            = 0,  /*!< Calculate checksum on data bytes             */
    LIN_ENHANCED_CHECKSUM           = 1,  /*!< Calculate checksum on data bytes and the PID */
} LIN_ChecksumModeEnum;




/**
 *  @brief  UART Status
 */
typedef enum
{
    UART_STS_ALL                   = (0x3FFU),      /*!< Used for all status                         */
    UART_STS_TX_BUSY               = (1U << 9),     /*!< Indicate the UART is transmitting           */
    UART_STS_RX_BUSY               = (1U << 8),     /*!< Indicate the UART is receiving              */
    UART_STS_RX_ERROR              = (1U << 7),    /*!< Indicate there is parity error, frame error
                                                      or break condition for the un-read data in
                                                      the receiver FIFO                           */
    UART_STS_RX_BREAK              = (1U << 6),    /*!< Break condition indicator for the data just
                                                      read out from the receiver FIFO             */
    UART_STS_RX_FRAME_ERROR        = (1U << 5),    /*!< Frame error indicator for the data just read
                                                      out from the receiver FIFO                  */
    UART_STS_RX_PARITY_ERROR       = (1U << 4),    /*!< Parity error indicator for the data just
                                                      read out from the receiver FIFO             */
    UART_STS_TX_NOT_FULL           = (1U << 3),     /*!< Transmit FIFO not full (i.e. UARTTFLVL<64)  */
    UART_STS_TX_EMPTY              = (1U << 2),     /*!< Transmit FIFO empty                         */
    UART_STS_RX_FULL               = (1U << 1),     /*!< Receive FIFO full                           */
    UART_STS_RX_NOT_EMPTY          = (1U << 0)      /*!< Receive FIFO not empty (i.e. UARTRFLVL>0)   */
} UART_StatusEnum;




/**
 *  @brief  UART interrupt type definition
 */
typedef enum
{
    UART_INT_ALL                   = (0x27FFFU),    /*!< Used for all int                             */
    UART_INT_GLOBAL                = (1U << 17),    /*!< Global Interrupt Flag
                                                         Only used for query or clear interrupt flag  */
    UART_INT_LIN_BUS_IDLE          = (1U << 14),    /*!< LIN bus idle interrupt                       */
    UART_INT_LIN_SYNC_BYTE_ERROR   = (1U << 13),    /*!< LIN sync byte eorr interrupt                 */
    UART_INT_LIN_CHECKSUM_ERROR    = (1U << 12),    /*!< LIN checksum error interrupt                 */
    UART_INT_LIN_BIT_ERROR         = (1U << 11),    /*!< LIN bit error interrupt                      */
    UART_INT_LIN_ID_MATCH          = (1U << 10),    /*!< LIN received ID match interrupt              */
    UART_INT_AUTOBAUD_LOCK         = (1U << 9),     /*!< Auto-baud lock interrupt                     */
    UART_INT_TX_REQ                = (1U << 8),     /*!< Transmit request data interrupt (LVL <= TH)  */
    UART_INT_TX_OVERFLOW           = (1U << 7),     /*!< Transmit overflow interrupt                  */
    UART_INT_RX_TIMEOUT            = (1U << 6),    /*!< Time out detected interrupt
                                                       For UART mode, it means data was received and
                                                       un-read in the FIFO but no new data was
                                                       received within the 4 frame time window
                                                       afterwards.
                                                       For LIN mode, it means that no enough
                                                       responses is received when time out according
                                                       to LIN specifications.                       */
    UART_INT_RX_BREAK              = (1U << 5),     /*!< Receive break condition interrupt            */
    UART_INT_RX_FRAME_ERROR        = (1U << 4),     /*!< Receive frame error interrupt                */
    UART_INT_RX_PARITY_ERROR       = (1U << 3),     /*!< Receive parity error interrupt               */
    UART_INT_RX_REQ                = (1U << 2),     /*!< Receive data available interrupt (LVL > TH)  */
    UART_INT_RX_OVERFLOW           = (1U << 1),     /*!< Receive overflow interrupt                   */
    UART_INT_RX_UNDERFLOW          = (1U << 0)      /*!< Receive underflow interrupt                  */
} UART_IntEnum;




/******************************************************************************
 * @brief      Define UART FIFO depth for transmitter and receiver
 *
 ******************************************************************************/
#define UART_FIFO_DEPTH         (64)




/******************************************************************************
 * @brief      Send one byte data or one word data to the UART/LIN peripheral
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u8Data  :  Byte data to be sent
 * @param[in]  u32Data :  Word data to be sent
 *
 * @return     None
 *
 * @note       Both functions are the same to write data to the whole 32-bit register.
 *             They are provided to improve the readability for user’s code.
 *             The actual data width is determined by hardware and can be set by
 *             UART_SetFIFOAccessWidth().
 *             When it is set as 8-bit, only the lowest byte will be written.
 *             When it is set as 32-bit, all the 4 bytes will be written in the
 *             order from the lowest byte to the highest byte
 ******************************************************************************/
#define UART_WriteByte(UARTx, u8Data)       ((UARTx)->UARTDAT = (u8Data))
#define UART_WriteWord(UARTx, u32Data)      ((UARTx)->UARTDAT = (u32Data))

#define LIN_WriteByte(UARTx, u8Data)        ((UARTx)->UARTDAT = (u8Data))
#define LIN_WriteWord(UARTx, u32Data)       ((UARTx)->UARTDAT = (u32Data))




/******************************************************************************
 * @brief      Receive one byte data or one word data from the UART/LIN peripheral
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     One byte data or one word data received from the UART/LIN peripheral
 *
 * @note       Both functions are the same to read data from the whole 32-bit register.
 *             They are provided to improve the readability for user’s code.
 *             The actual valid data width is determined by hardware and can be set by
 *             UART_SetFIFOAccessWidth().
 *             When it is set as 8-bit, only the lowest byte is valid and all other
 *             3 bytes are always 0.
 *             When it is set as 32-bit, all the 4 bytes are valid with values filled
 *             from FIFO in the order from lowest byte to highest byte
 *
 ******************************************************************************/
#define UART_ReadByte(UARTx)                ((UARTx)->UARTDAT)
#define UART_ReadWord(UARTx)                ((UARTx)->UARTDAT)

#define LIN_ReadByte(UARTx)                 ((UARTx)->UARTDAT)
#define LIN_ReadWord(UARTx)                 ((UARTx)->UARTDAT)




/******************************************************************************
 * @brief      Enable UART module receiver run
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableRx(UARTx)                                                    \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_RXEN_Msk)




/******************************************************************************
 * @brief      Disable UART module receiver run
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableRx(UARTx)                                                   \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_RXEN_Msk)




/******************************************************************************
 * @brief      Set UART module receiver run
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetRx(UARTx, eEnable)                                              \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_RXEN_Msk, UARTCTL_RXEN_Pos,             \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get UART module receiver run status
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableRx(UARTx)                                                  \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_RXEN_Msk, UARTCTL_RXEN_Pos)




/******************************************************************************
 * @brief      Enable UART module transmitter run
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableTx(UARTx)                                                    \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_TXEN_Msk)




/******************************************************************************
 * @brief      Disable UART module transmitter run
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableTx(UARTx)                                                   \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_TXEN_Msk)




/******************************************************************************
 * @brief      Set UART module transmitter run
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetTx(UARTx, eEnable)                                              \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_TXEN_Msk, UARTCTL_TXEN_Pos,             \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get UART module transmitter run status
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableTx(UARTx)                                                  \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_TXEN_Msk, UARTCTL_TXEN_Pos)




/******************************************************************************
 * @brief      Enable UART module for both transmitter and receiver
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_Enable(UARTx)                                                      \
    SET_BITS((UARTx)->UARTCTL, (UARTCTL_TXEN_Msk|UARTCTL_RXEN_Msk))




/******************************************************************************
 * @brief      Disable UART module for both transmitter and receiver
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_Disable(UARTx)                                                     \
    CLEAR_BITS((UARTx)->UARTCTL, (UARTCTL_TXEN_Msk|UARTCTL_RXEN_Msk))




/******************************************************************************
 * @brief      Enable UART module receiver DMA
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableRxDMA(UARTx)                                                 \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_RXDMAEN_Msk)




/******************************************************************************
 * @brief      Disable UART module receiver DMA
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableRxDMA(UARTx)                                                \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_RXDMAEN_Msk)




/******************************************************************************
 * @brief      Set UART module receiver DMA run
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetRxDMA(UARTx, eEnable)                                           \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_RXDMAEN_Msk, UARTCTL_RXDMAEN_Pos,       \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get UART module receiver DMA run status
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableRxDMA(UARTx)                                               \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_RXDMAEN_Msk, UARTCTL_RXDMAEN_Pos)




/******************************************************************************
 * @brief      Enable UART module transmitter DMA
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableTxDMA(UARTx)                                                 \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_TXDMAEN_Msk)




/******************************************************************************
 * @brief      Disable UART module transmitter
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableTxDMA(UARTx)                                                \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_TXDMAEN_Msk)




/******************************************************************************
 * @brief      Set UART module transmitter DMA run
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetTxDMA(UARTx, eEnable)                                           \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_TXDMAEN_Msk, UARTCTL_TXDMAEN_Pos,       \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get UART module transmitter DMA run status
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableTxDMA(UARTx)                                               \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_TXDMAEN_Msk, UARTCTL_TXDMAEN_Pos)




/******************************************************************************
 * @brief      Enable UART module DMA for both transmitter and receiver
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableDMA(UARTx)                                                   \
    SET_BITS((UARTx)->UARTCTL, (UARTCTL_TXDMAEN_Msk|UARTCTL_RXDMAEN_Msk))




/******************************************************************************
 * @brief      Disable UART module DMA for both transmitter and receiver
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableDMA(UARTx)                                                  \
    CLEAR_BITS((UARTx)->UARTCTL, (UARTCTL_TXDMAEN_Msk|UARTCTL_RXDMAEN_Msk))




/******************************************************************************
 * @brief      Clear receiver FIFO
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_ClearRxFIFO(UARTx)    SET_BITS((UARTx)->UARTCTL, UARTCTL_CLRRF_Msk)




/******************************************************************************
 * @brief      Clear transmitter FIFO
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_ClearTxFIFO(UARTx)    SET_BITS((UARTx)->UARTCTL, UARTCTL_CLRTF_Msk)




/******************************************************************************
 * @brief      Clear both receiver FIFO and transmitter FIFO
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_ClearFIFO(UARTx)                                                   \
    SET_BITS((UARTx)->UARTCTL, (UARTCTL_CLRRF_Msk|UARTCTL_CLRTF_Msk))




/******************************************************************************
 * @brief      Set break
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 * @note       This field is self clear bit after take action
 *
 ******************************************************************************/
#define UART_SetBreak(UARTx)                                                    \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_SETBRK_Msk)




/******************************************************************************
 * @brief      Check whether set break is still ongoing
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     Set break ongoing status
 *
 ******************************************************************************/
#define UART_IsSetBreak(UARTx)                                                  \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_SETBRK_Msk, UARTCTL_SETBRK_Pos)




/******************************************************************************
 * @brief      Run / stop bus idle counter
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_RunBusIdleCounter(UARTx)                                           \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_IDLECNTEN_Msk)
#define UART_StopBusIdleCounter(UARTx)                                          \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_IDLECNTEN_Msk)




/******************************************************************************
 * @brief      Get bus idle counter run status
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsRunBusIdleCounter(UARTx)                                         \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_IDLECNTEN_Msk, UARTCTL_IDLECNTEN_Pos)




/******************************************************************************
 * @brief      Set bus idle threshold
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  u32Cnt :  Number of clock cycles to report bus idle
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_SetBusIdleThreshold(UARTx, u32Cnt)                                 \
    ((UARTx)->BUSIDLETH = ((u32Cnt) - 1))




/******************************************************************************
 * @brief      Enable auto baud
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 * @note       This field is self clear bit after action finished
 *
 ******************************************************************************/
#define UART_EnableAutoBaud(UARTx)                                              \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_ABEN_Msk)




/******************************************************************************
 * @brief      Disable auto baud
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableAutoBaud(UARTx)                                             \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_ABEN_Msk)




/******************************************************************************
 * @brief      Set auto baud run
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetAutoBaud(UARTx, eEnable)                                        \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_ABEN_Msk, UARTCTL_ABEN_Pos,             \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get auto baud run status
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableAutoBaud(UARTx)                                            \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_ABEN_Msk, UARTCTL_ABEN_Pos)




/******************************************************************************
 * @brief      Baud count is updated by hardware after auto-baud is locked
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_UpdateBaudCountByHW(UARTx)                                         \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_ABUP_Msk)




/******************************************************************************
 * @brief      Baud count is updated by software after auto-baud is locked
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_UpdateBaudCountBySW(UARTx)                                         \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_ABUP_Msk)




/******************************************************************************
 * @brief      Set auto baud count update method
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eMethod:  Baud count update method defined by UART_BaudCountUpdateEnum
 *                       Only the following values are valid:
 *                         - \ref UART_BAUD_COUNT_UPDATE_BY_HARDWARE
 *                         - \ref UART_BAUD_COUNT_UPDATE_BY_SOFTWARE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetBaudCountUpdateMethod(UARTx, eMethod)                           \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_ABUP_Msk, UARTCTL_ABUP_Pos, (eMethod))




/******************************************************************************
 * @brief      Get auto baud count update method
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Baud count update method defined by UART_BaudCountUpdateEnum
 *
 ******************************************************************************/
#define UART_GetBaudCountUpdateMethod(UARTx)                                    \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_ABUP_Msk, UARTCTL_ABUP_Pos)




/******************************************************************************
 * @brief      Set UART NRZ mode
 *
 * @param[in]  UARTx:  Select the UART module
 * @param[in]  eMode:  NRZ mode defined by UART_NRZModeEnum
 *                     Only the following values are valid:
 *                       - \ref UART_NRZ_LEVEL
 *                       - \ref UART_NRZ_SPACE
 *                       - \ref UART_NRZ_MARK
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetNRZMode(UARTx, eMode)                                           \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_NRZMODE_Msk, UARTCTL_NRZMODE_Pos,       \
                (eMode)                                                                     \
               )




/******************************************************************************
 * @brief      Get UART NRZ mode
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     NRZ mode defined by UART_NRZModeEnum
 *
 ******************************************************************************/
#define UART_GetNRZMode(UARTx)                                                  \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_NRZMODE_Msk, UARTCTL_NRZMODE_Pos)




/******************************************************************************
 * @brief      Set UART data bit
 *
 * @param[in]  UARTx:     Select the UART module
 * @param[in]  eDataBit:  Data bit length defined by UART_DataBitEnum
 *                        Only the following values are valid:
 *                          - \ref UART_5_DATA_BIT
 *                          - \ref UART_6_DATA_BIT
 *                          - \ref UART_7_DATA_BIT
 *                          - \ref UART_8_DATA_BIT
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetDataBit(UARTx, eDataBit)                                        \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_DATABIT_Msk, UARTCTL_DATABIT_Pos,       \
                (eDataBit)                                                                  \
               )




/******************************************************************************
 * @brief      Get UART data bit
 *
 * @param[in]  UARTx:     Select the UART module
 *
 * @return     Data bit length defined by UART_DataBitEnum
 *
 ******************************************************************************/
#define UART_GetDataBit(UARTx)                                                  \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_DATABIT_Msk, UARTCTL_DATABIT_Pos)




/******************************************************************************
 * @brief      Set UART parity bit
 *
 * @param[in]  UARTx:       Select the UART module
 * @param[in]  eParityBit:  Parity bit defined by UART_ParityBitEnum
 *                          Only the following values are valid:
 *                            - \ref UART_NO_PARITY
 *                            - \ref UART_EVEN_PARITY
 *                            - \ref UART_ODD_PARITY
 *                            - \ref UART_STICKY_HIGH_PARITY
 *                            - \ref UART_STICKY_LOW_PARITY
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetParityBit(UARTx, eParityBit)                                    \
    WRITE_FIELD((UARTx)->UARTCTL, (UARTCTL_PRTYEN_Msk|UARTCTL_PRTYBIT_Msk),       \
                UARTCTL_PRTYBIT_Pos,                                                        \
                (eParityBit)                                                                \
               )




/******************************************************************************
 * @brief      Get UART parity bit
 *
 * @param[in]  UARTx:       Select the UART module
 *
 * @return     Parity bit defined by UART_ParityBitEnum
 *
 ******************************************************************************/
#define UART_GetParityBit(UARTx)                                                \
    READ_FIELD((UARTx)->UARTCTL, (UARTCTL_PRTYEN_Msk|UARTCTL_PRTYBIT_Msk),        \
               UARTCTL_PRTYBIT_Pos                                                         \
              )




/******************************************************************************
 * @brief      Set UART stop bit
 *
 * @param[in]  UARTx:     Select the UART module
 * @param[in]  eStopBit:  Stop bit defined by UART_StopBitEnum
 *                        Only the following values are valid:
 *                          - \ref UART_1_STOP_BIT
 *                          - \ref UART_2_STOP_BIT
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetStopBit(UARTx, eStopBit)                                        \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_STOPBIT_Msk, UARTCTL_STOPBIT_Pos,       \
                (eStopBit)                                                                  \
               )




/******************************************************************************
 * @brief      Get UART stop bit
 *
 * @param[in]  UARTx:     Select the UART module
 *
 * @return     Stop bit defined by UART_StopBitEnum
 *
 ******************************************************************************/
#define UART_GetStopBit(UARTx)                                                  \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_STOPBIT_Msk, UARTCTL_STOPBIT_Pos)




/******************************************************************************
 * @brief      Set UART data bus width to 8-bit
 * @brief      Set UART data bus width to 32-bit
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 * @note       Legacy setting functions, will be removed in the future
 *
 ******************************************************************************/
#define UART_Set8BitBusWidth(UARTx)   CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_BUS32_Msk)
#define UART_Set32BitBusWidth(UARTx)  SET_BITS((UARTx)->UARTCTL, UARTCTL_BUS32_Msk)




/******************************************************************************
 * @brief      Set UART FIFO access width
 *
 * @param[in]  UARTx :  Select the UART module
 * @param[in]  eWidth:  Bus width defined by UART_FIFOAccessWidthEnum
 *                      Only the following values are valid:
 *                        - \ref UART_FIFO_ACCESS_IN_BYTE
 *                        - \ref UART_FIFO_ACCESS_IN_WORD
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetFIFOAccessWidth(UARTx, eWidth)                                 \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_BUS32_Msk, UARTCTL_BUS32_Pos, (eWidth))




/******************************************************************************
 * @brief      Get UART FIFO access width
 *
 * @param[in]  UARTx :  Select the UART module
 * @param[in]  eWidth:  Bus width defined by UART_FIFOAccessWidthEnum
 *                      Only the following values are valid:
 *                        - \ref UART_FIFO_ACCESS_IN_BYTE
 *                        - \ref UART_FIFO_ACCESS_IN_WORD
 *
 * @return     Bus width defined by UART_FIFOAccessWidthEnum
 *
 ******************************************************************************/
#define UART_GetFIFOAccessWidth(UARTx)                                         \
    READ_FIELD((UARTx)->UARTCTL, UARTCTL_BUS32_Msk, UARTCTL_BUS32_Pos)




/******************************************************************************
 * @brief      Enable loopback mode
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableLoopback(UARTx)                                              \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_LPBK_Msk)




/******************************************************************************
 * @brief      Disable loopback mode
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableLoopback(UARTx)                                             \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_LPBK_Msk)




/******************************************************************************
 * @brief      Set loopback mode
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetLoopback(UARTx, eEnable)                                        \
    WRITE_FIELD((UARTx)->UARTCTL, UARTCTL_LPBK_Msk, UARTCTL_LPBK_Pos, (eEnable) )




/******************************************************************************
 * @brief      Is enable loopback mode
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     0     - Loopback mode is disabled
 *             not 0 - Loopback mode is enabled
 *
 ******************************************************************************/
#define UART_IsEnableLoopback(UARTx)                                            \
    READ_BITS((UARTx)->UARTCTL, UARTCTL_LPBK_Msk)




/******************************************************************************
 * @brief      Enable error report when Rx FIFO is full
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableErrorReportWhenRxFull(UARTx)                           \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_RFEMODE_Msk)




/******************************************************************************
 * @brief      Disable error report when Rx FIFO is full
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableErrorReportWhenRxFull(UARTx)                          \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_RFEMODE_Msk)




/******************************************************************************
 * @brief      Is enable error report when Rx FIFO is full
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     0     - Do not report error when Rx FIFO is full
 *             not 0 - Report error when Rx FIFO is full
 *
 ******************************************************************************/
#define UART_IsEnableErrorReportWhenRxFull(UARTx)                         \
    READ_BITS((UARTx)->UARTCTL, UARTCTL_RFEMODE_Msk)




/******************************************************************************
 * @brief      Enable swap TXD/RXD pin
 *
 * @param[in]  UARTx : Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnablePinSwap(UARTx)                                               \
    SET_BITS((UARTx)->UARTCTL, UARTCTL_SWAPPIN_Msk)




/******************************************************************************
 * @brief      Disable swap TXD/RXD pin
 *
 * @param[in]  UARTx : Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisablePinSwap(UARTx)                                              \
    CLEAR_BITS((UARTx)->UARTCTL, UARTCTL_SWAPPIN_Msk)




/******************************************************************************
 * @brief      Is enable swap TXD/RXD pin
 *
 * @param[in]  UARTx : Select the UART module
 *
 * @return     0     - Swap TXD/RXD pin is disabled
 *             not 0 - Swap TXD/RXD pin is enabled
 *
 ******************************************************************************/
#define UART_IsEnablePinSwap(UARTx)                                             \
    READ_BITS((UARTx)->UARTCTL, UARTCTL_SWAPPIN_Msk)




/******************************************************************************
 * @brief      Enable LIN mode
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_Enable(UARTx)                                                       \
    SET_BITS((UARTx)->LINCTL, LINCTL_LINEN_Msk)




/******************************************************************************
 * @brief      Disable LIN mode
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_Disable(UARTx)                                                      \
    CLEAR_BITS((UARTx)->LINCTL, LINCTL_LINEN_Msk)




/******************************************************************************
 * @brief      Set LIN mode enable or disable
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_Set(UARTx, eEnable)                                                 \
    WRITE_FIELD((UARTx)->LINCTL, LINCTL_LINEN_Msk, LINCTL_LINEN_Pos, (eEnable))




/******************************************************************************
 * @brief      Get LIN mode enable or disable
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define LIN_IsEnable(UARTx)                                                     \
    READ_FIELD((UARTx)->LINCTL, LINCTL_LINEN_Msk, LINCTL_LINEN_Pos)




/******************************************************************************
 * @brief      Enable LIN ID parity
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_EnableIDParity(UARTx)           ((UARTx)->UARTCTL |= UARTCTL_PRTYEN_PARITY_ENABLE)




/******************************************************************************
 * @brief      Disable LIN ID parity
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_DisableIDParity(UARTx)          ((UARTx)->UARTCTL &= (~UARTCTL_PRTYEN_PARITY_ENABLE))




/******************************************************************************
 * @brief      Set LIN role (master or slave)
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  eMode: Select the LIN mode
 *                    Please refer to LIN_ModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetMode(UARTx, eMode)           ((UARTx)->LINCTL = (((UARTx)->LINCTL & (~LINCTL_MASTER_Msk)) | ((eMode) << LINCTL_MASTER_Pos)))




/******************************************************************************
 * @brief      Set LIN synchronization break
 *
 * @param[in]  UARTx:   Select the UART module
 * @param[in]  eBrkLen: Select the synchronization break length
 *                      Please refer to LIN_SyncBreakLenEnum
 * @param[in]  eBrkDel: Select the synchronization break delimiter
 *                      Please refer to LIN_SyncBreakDelimiterEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetSyncBreak(UARTx, eBrkLen, eBrkDel)   ((UARTx)->LINCTL = (((UARTx)->LINCTL & (~(LINCTL_SBRKLEN_Msk | LINCTL_SBRKDEL_Msk))) | ((eBrkLen) << LINCTL_SBRKLEN_Pos) | ((eBrkDel) << LINCTL_SBRKDEL_Pos)))




/******************************************************************************
 * @brief      Set LIN response
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  eResp: Select the LIN response
 *                    Please refer to LIN_ResponseEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetResponse(UARTx, eResp)       ((UARTx)->LINCTL = (((UARTx)->LINCTL & (~LINCTL_RESP_Msk)) | ((eResp) << LINCTL_RESP_Pos)))




/******************************************************************************
 * @brief      Set LIN response length
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  eLen : Select the LIN response length
 *                    Please refer to LIN_ResponseLenEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetResponseLen(UARTx, eLen)     ((UARTx)->LINCTL = (((UARTx)->LINCTL & (~LINCTL_RESPLEN_Msk)) | ((eLen) << LINCTL_RESPLEN_Pos)))




/******************************************************************************
 * @brief      Set LIN checksum mode
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  eMode: Select the LIN checksum mode
 *                    Please refer to LIN_ChecksumModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetCheckSumMode(UARTx, eMode)   ((UARTx)->LINCTL = (((UARTx)->LINCTL & (~LINCTL_CHKSUM_Msk)) | ((eMode) << LINCTL_CHKSUM_Pos)))




/******************************************************************************
 * @brief      Set LIN Rx FIFO mode
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  eMode: Select the LIN Rx FIFO mode
 *                    Please refer to LIN_RxFIFOModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetRxFIFOMode(UARTx, eMode)                                         \
    WRITE_FIELD((UARTx)->LINCTL, LINCTL_RFMODE_Msk, LINCTL_RFMODE_Pos, (eMode))




/******************************************************************************
 * @brief      Set LIN ID to transmitter
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  u8ID : LIN ID to transmitter
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetTxID(UARTx, u8ID)            ((UARTx)->LINID = (u8ID))




/******************************************************************************
 * @brief      Get LIN ID received
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     Recevied LIN ID
 *
 ******************************************************************************/
#define LIN_GetRxID(UARTx)                  ((UARTx)->LINID)




/******************************************************************************
 * @brief      Set LIN ID filter
 *
 * @param[in]  UARTx   : Select the UART module
 * @param[in]  u8RefID : Reference ID to compare
 * @param[in]  u8IDMask: ID bit-wise mask
 *                       0 - Do not compared this bit
 *                       1 - Compare this bit
 *
 * @return     None
 *
 ******************************************************************************/
#define LIN_SetIDFilter(UARTx, u8RefID, u8IDMask)                               \
    ((UARTx)->LINIDFILT = (   (((u8IDMask) & 0xff) << LINIDFILT_MASK_Pos)         \
                              | ((u8RefID) & 0xff)                                  \
                          )                                                       \
    )




/******************************************************************************
 * @brief      Set UART baud count
 *
 * @param[in]  UARTx     :  Select the UART module
 * @param[in]  u32BaudCnt:  Baud count
 *
 * @return     None
 *
 * @note       The minimum valid value is 16,
 *             and write a value below 16 will be reset to 16.
 *
 ******************************************************************************/
#define UART_SetBaudCount(UARTx, u32BaudCnt)                                    \
    ((UARTx)->UARTBDCNT = (u32BaudCnt))




/******************************************************************************
 * @brief      Get UART baud count
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     Current baud count
 *
 ******************************************************************************/
#define UART_GetBaudCount(UARTx)                           ((UARTx)->UARTBDCNT)




/******************************************************************************
 * @brief      Get UART auto-baud count
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     Auto-baud count
 *
 ******************************************************************************/
#define UART_GetAutoBaudCount(UARTx)                       ((UARTx)->UARTABCNT)




/******************************************************************************
 * @brief      Get UART receiver FIFO level
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     Current receiver FIFO level
 *
 ******************************************************************************/
#define UART_GetRxFIFOLevel(UARTx)                         ((UARTx)->UARTRXLVL)




/******************************************************************************
 * @brief      Get UART transmitter FIFO level
 *
 * @param[in]  UARTx:  Select the UART module
 *
 * @return     Current transmitter FIFO level
 *
 ******************************************************************************/
#define UART_GetTxFIFOLevel(UARTx)                         ((UARTx)->UARTTXLVL)




/******************************************************************************
 * @brief      Set UART receiver FIFO data available threshold
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  u32Th: Threshold for receiver FIFO
 *                    Trigger receiver data available interrupt when the
 *                    receiver FIFO level > u32Th
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetRxFIFOThreshold(UARTx, u32Th)     ((UARTx)->UARTRXTH = (u32Th))




/******************************************************************************
 * @brief      Get UART receiver FIFO data available threshold
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     Threshold for receiver FIFO
 *             Trigger receiver data available interrupt when the
 *             receiver FIFO level > u32Th
 *
 ******************************************************************************/
#define UART_GetRxFIFOThreshold(UARTx)                      ((UARTx)->UARTRXTH)




/******************************************************************************
 * @brief      Set UART transmitter FIFO data request threshold
 *
 * @param[in]  UARTx: Select the UART module
 * @param[in]  u32Th: Threshold for transmitter FIFO
 *                    Trigger transmitter data request interrupt when the transmitter
 *                    FIFO level <= u32Th
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetTxFIFOThreshold(UARTx, u32Th)     ((UARTx)->UARTTXTH = (u32Th))




/******************************************************************************
 * @brief      Get UART transmitter FIFO data request threshold
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     Threshold for transmitter FIFO
 *             Trigger transmitter data request interrupt when the transmitter
 *             FIFO level <= u32Th
 *
 ******************************************************************************/
#define UART_GetTxFIFOThreshold(UARTx)                      ((UARTx)->UARTTXTH)




/******************************************************************************
 * @brief      Enable SIR mode for UART receiver
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableRxSIR(UARTx)                                                 \
    SET_BITS((UARTx)->UARTSIRCTL, UARTSIRCTL_RXSIREN_Msk)




/******************************************************************************
 * @brief      Disable SIR mode for UART receiver
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableRxSIR(UARTx)                                                \
    CLEAR_BITS((UARTx)->UARTSIRCTL, UARTSIRCTL_RXSIREN_Msk)




/******************************************************************************
 * @brief      Set SIR mode for UART receiver
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetRxSIR(UARTx, eEnable)                                           \
    WRITE_FIELD((UARTx)->UARTSIRCTL,                                              \
                UARTSIRCTL_RXSIREN_Msk, UARTSIRCTL_RXSIREN_Pos,                             \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get SIR mode for UART receiver
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableRxSIR(UARTx)                                               \
    READ_FIELD((UARTx)->UARTSIRCTL,                                               \
               UARTSIRCTL_RXSIREN_Msk, UARTSIRCTL_RXSIREN_Pos                              \
              )




/******************************************************************************
 * @brief      Enable SIR mode for UART transmitter
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableTxSIR(UARTx)                                                 \
    SET_BITS((UARTx)->UARTSIRCTL, UARTSIRCTL_TXSIREN_Msk)




/******************************************************************************
 * @brief      Disable SIR mode for UART transmitter
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableTxSIR(UARTx)                                                \
    CLEAR_BITS((UARTx)->UARTSIRCTL, UARTSIRCTL_TXSIREN_Msk)




/******************************************************************************
 * @brief      Set SIR mode for UART transmitter
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetTxSIR(UARTx, eEnable)                                           \
    WRITE_FIELD((UARTx)->UARTSIRCTL,                                              \
                UARTSIRCTL_TXSIREN_Msk, UARTSIRCTL_TXSIREN_Pos,                             \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Get SIR mode for UART transmitter
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define UART_IsEnableTxSIR(UARTx)                                               \
    READ_FIELD((UARTx)->UARTSIRCTL,                                               \
               UARTSIRCTL_TXSIREN_Msk, UARTSIRCTL_TXSIREN_Pos                              \
              )




/******************************************************************************
 * @brief      Enable SIR mode for both transmitter and receiver
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableSIR(UARTx)                                                   \
    SET_BITS((UARTx)->UARTSIRCTL,                                                 \
             (UARTSIRCTL_TXSIREN_Msk|UARTSIRCTL_RXSIREN_Msk)                             \
            )




/******************************************************************************
 * @brief      Disable SIR mode for both transmitter and receiver
 *
 * @param[in]  UARTx :  Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableSIR(UARTx)                                                  \
    CLEAR_BITS((UARTx)->UARTSIRCTL,                                               \
               (UARTSIRCTL_TXSIREN_Msk|UARTSIRCTL_RXSIREN_Msk)                             \
              )




/******************************************************************************
 * @brief      Set SIR mode polarity for UART receiver
 *
 * @param[in]  UARTx    : Select the UART module
 * @param[in]  ePolarity: Data polarity defined by UART_SIRPolarityEnum
 *                        Only the following values are valid:
 *                          - \ref UART_SIR_NEGATIVE_PULSE_AS_ZERO
 *                          - \ref UART_SIR_POSITIVE_PULSE_AS_ZERO
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetRxSIRPolarity(UARTx, ePolarity)                                 \
    WRITE_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_RXPOL_Msk, UARTSIRCTL_RXPOL_Pos,  \
                (ePolarity)                                                                 \
               )




/******************************************************************************
 * @brief      Get SIR mode polarity for UART receiver
 *
 * @param[in]  UARTx    : Select the UART module
 *
 * @return     Data polarity defined by UART_SIRPolarityEnum
 *
 ******************************************************************************/
#define UART_GetRxSIRPolarity(UARTx)                                            \
    READ_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_RXPOL_Msk, UARTSIRCTL_RXPOL_Pos)




/******************************************************************************
 * @brief      Set SIR mode polarity for UART transmitter
 *
 * @param[in]  UARTx    : Select the UART module
 * @param[in]  ePolarity: Data polarity defined by UART_SIRPolarityEnum
 *                        Only the following values are valid:
 *                          - \ref UART_SIR_NEGATIVE_PULSE_AS_ZERO
 *                          - \ref UART_SIR_POSITIVE_PULSE_AS_ZERO
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetTxSIRPolarity(UARTx, ePolarity)                                 \
    WRITE_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_TXPOL_Msk, UARTSIRCTL_TXPOL_Pos,  \
                (ePolarity)                                                                 \
               )




/******************************************************************************
 * @brief      Get SIR mode polarity for UART transmitter
 *
 * @param[in]  UARTx    : Select the UART module
 *
 * @return     Data polarity defined by UART_SIRPolarityEnum
 *
 ******************************************************************************/
#define UART_GetTxSIRPolarity(UARTx)                                            \
    READ_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_TXPOL_Msk, UARTSIRCTL_TXPOL_Pos)




/******************************************************************************
 * @brief      Set TX format for UART transmitter in SIR mode
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  eFormat:  Format defined by UART_SIRTxFormatEnum
 *                       Only the following values are valid:
 *                         - \ref UART_SIR_TX_BY_DUTY
 *                         - \ref UART_SIR_TX_BY_CYCLE
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetSIRTxFormat(UARTx, eFormat)                                     \
    WRITE_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_XMODE_Msk, UARTSIRCTL_XMODE_Pos,  \
                (eFormat)                                                                   \
               )




/******************************************************************************
 * @brief      Get TX format for UART transmitter in SIR mode
 *
 * @param[in]  UARTx  :  Select the UART module
 *
 * @return     Format defined by UART_SIRTxFormatEnum
 *
 ******************************************************************************/
#define UART_GetSIRTxFormat(UARTx)                                              \
    READ_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_XMODE_Msk, UARTSIRCTL_XMODE_Pos)




/******************************************************************************
 * @brief      Set TX active pulse cycle number for UART transmitter in SIR mode
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Width:  Pulse width (number of UART clock cycles), 1 ~ 511
 *
 * @return     None
 *
 * @note       Valid for UART_GetSIRTxFormat(UARTx) == UART_SIR_TX_BY_CYCLE
 *
 ******************************************************************************/
#define UART_SetSIRTxActivePulseWidth(UARTx, u32Width)                          \
    WRITE_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_TXPW_Msk, UARTSIRCTL_TXPW_Pos,    \
                (u32Width)                                                                  \
               )




/******************************************************************************
 * @brief      Get TX active pulse cycle number for UART transmitter in SIR mode
 *
 * @param[in]  UARTx   :  Select the UART module
 *
 * @return     Pulse width (number of UART clock cycles)
 *
 * @note       Valid for UART_GetSIRTxFormat(UARTx) == UART_SIR_TX_BY_CYCLE
 *
 ******************************************************************************/
#define UART_GetSIRTxActivePulseWidth(UARTx)                                    \
    READ_FIELD((UARTx)->UARTSIRCTL, UARTSIRCTL_TXPW_Msk, UARTSIRCTL_TXPW_Pos)




/******************************************************************************
 * @brief      Set TX active pulse by duty for UART transmitter in SIR mode
 *
 * @param[in]  UARTx: Select the UART module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetSIRTxActivePulseByDuty(UARTx)                                   \
    CLEAR_BITS((UARTx)->UARTSIRCTL, UARTSIRCTL_XMODE_Msk)




/******************************************************************************
 * @brief      Set TX active pulse by cycle and set pulse width for
 *             UART transmitter in SIR mode
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Width:  Pulse width (number of UART clock cycles)
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_SetSIRTxActivePulseByCycle(UARTx, u32Width)                        \
    ((UARTx)->UARTSIRCTL = (((UARTx)->UARTSIRCTL & (~UARTSIRCTL_TXPW_Msk))        \
                            | ((u32Width) << UARTSIRCTL_TXPW_Pos)                    \
                            | UARTSIRCTL_XMODE_Msk)                                  \
    )




/******************************************************************************
 * @brief      Get UART status
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Query:  The status defined by UART_StatusEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_STS_ALL
 *                          - \ref UART_STS_TX_BUSY
 *                          - \ref UART_STS_RX_BUSY
 *                          - \ref UART_STS_RX_ERR
 *                          - \ref UART_STS_RX_BREAK
 *                          - \ref UART_STS_RX_FRAME_ERR
 *                          - \ref UART_STS_RX_PARITY_ERR
 *                          - \ref UART_STS_TX_NOT_FULL
 *                          - \ref UART_STS_TX_EMPTY
 *                          - \ref UART_STS_RX_FULL
 *                          - \ref UART_STS_RX_NOT_EMPTY
 *
 * @return     0     - None of the queried statuses occurred;
 *             not 0 - Corresponding statuses for non-zero bit occurred.
 *
 ******************************************************************************/
#define UART_GetStatus(UARTx, u32Query)         ((UARTx)->UARTSTS & (u32Query))




/******************************************************************************
 * @brief      Get raw event flag
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Query:  Interrupt defined by UART_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_INT_ALL
 *                          - \ref UART_INT_LIN_CHECK_ERR
 *                          - \ref UART_INT_LIN_BIT_ERR
 *                          - \ref UART_INT_LIN_ID_MATCH
 *                          - \ref UART_INT_AUTOBAUD_LOCK
 *                          - \ref UART_INT_TX_REQ
 *                          - \ref UART_INT_TX_OVERFLOW
 *                          - \ref UART_INT_RX_TIMEOUT
 *                          - \ref UART_INT_RX_BREAK
 *                          - \ref UART_INT_RX_FRAME_ERR
 *                          - \ref UART_INT_RX_PARITY_ERR
 *                          - \ref UART_INT_RX_REQ
 *                          - \ref UART_INT_RX_OVERFLOW
 *                          - \ref UART_INT_RX_UNDERFLOW
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define UART_GetIntRawFlag(UARTx, u32Query)   ((UARTx)->UARTRAWIF & (u32Query))




/******************************************************************************
 * @brief      Get interrupt flag
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Query:  Interrupt defined by UART_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_INT_ALL
 *                          - \ref UART_INT_GLOBAL
 *                          - \ref UART_INT_LIN_CHECK_ERR
 *                          - \ref UART_INT_LIN_BIT_ERR
 *                          - \ref UART_INT_LIN_ID_MATCH
 *                          - \ref UART_INT_AUTOBAUD_LOCK
 *                          - \ref UART_INT_TX_REQ
 *                          - \ref UART_INT_TX_OVERFLOW
 *                          - \ref UART_INT_RX_TIMEOUT
 *                          - \ref UART_INT_RX_BREAK
 *                          - \ref UART_INT_RX_FRAME_ERR
 *                          - \ref UART_INT_RX_PARITY_ERR
 *                          - \ref UART_INT_RX_REQ
 *                          - \ref UART_INT_RX_OVERFLOW
 *                          - \ref UART_INT_RX_UNDERFLOW
 *
 * @return     0     - None of the queried interrupts occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define UART_GetIntFlag(UARTx, u32Query)         ((UARTx)->UARTIF & (u32Query))




/******************************************************************************
 * @brief      Enable interrputs
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Int  :  Interrupt defined by UART_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_INT_ALL
 *                          - \ref UART_INT_LIN_CHECK_ERR
 *                          - \ref UART_INT_LIN_BIT_ERR
 *                          - \ref UART_INT_LIN_ID_MATCH
 *                          - \ref UART_INT_AUTOBAUD_LOCK
 *                          - \ref UART_INT_TX_REQ
 *                          - \ref UART_INT_TX_OVERFLOW
 *                          - \ref UART_INT_RX_TIMEOUT
 *                          - \ref UART_INT_RX_BREAK
 *                          - \ref UART_INT_RX_FRAME_ERR
 *                          - \ref UART_INT_RX_PARITY_ERR
 *                          - \ref UART_INT_RX_REQ
 *                          - \ref UART_INT_RX_OVERFLOW
 *                          - \ref UART_INT_RX_UNDERFLOW
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_EnableInt(UARTx, u32Int)       SET_BITS((UARTx)->UARTIE, (u32Int))




/******************************************************************************
 * @brief      Disable interrputs
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Int  :  Interrupt defined by UART_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_INT_ALL
 *                          - \ref UART_INT_LIN_CHECK_ERR
 *                          - \ref UART_INT_LIN_BIT_ERR
 *                          - \ref UART_INT_LIN_ID_MATCH
 *                          - \ref UART_INT_AUTOBAUD_LOCK
 *                          - \ref UART_INT_TX_REQ
 *                          - \ref UART_INT_TX_OVERFLOW
 *                          - \ref UART_INT_RX_TIMEOUT
 *                          - \ref UART_INT_RX_BREAK
 *                          - \ref UART_INT_RX_FRAME_ERR
 *                          - \ref UART_INT_RX_PARITY_ERR
 *                          - \ref UART_INT_RX_REQ
 *                          - \ref UART_INT_RX_OVERFLOW
 *                          - \ref UART_INT_RX_UNDERFLOW
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_DisableInt(UARTx, u32Int)    CLEAR_BITS((UARTx)->UARTIE, (u32Int))




/******************************************************************************
 * @brief      Get interrputs setting
 *
 * @param[in]  UARTx   :  Select the UART module
 * @param[in]  u32Int  :  Interrupt defined by UART_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_INT_ALL
 *                          - \ref UART_INT_LIN_CHECK_ERR
 *                          - \ref UART_INT_LIN_BIT_ERR
 *                          - \ref UART_INT_LIN_ID_MATCH
 *                          - \ref UART_INT_AUTOBAUD_LOCK
 *                          - \ref UART_INT_TX_REQ
 *                          - \ref UART_INT_TX_OVERFLOW
 *                          - \ref UART_INT_RX_TIMEOUT
 *                          - \ref UART_INT_RX_BREAK
 *                          - \ref UART_INT_RX_FRAME_ERR
 *                          - \ref UART_INT_RX_PARITY_ERR
 *                          - \ref UART_INT_RX_REQ
 *                          - \ref UART_INT_RX_OVERFLOW
 *                          - \ref UART_INT_RX_UNDERFLOW
 *
 * @return     0     - None of the queried interrupts is enabled;
 *             not 0 - Corresponding interrupts for non-zero bit is enabled.
 *
 ******************************************************************************/
#define UART_IsEnableInt(UARTx, u32Int)             ((UARTx)->UARTIE & (u32Int))




/******************************************************************************
 * @brief      Clear interrupts
 *
 * @param[in]  UARTx  :  Select the UART module
 * @param[in]  u32Int :  Interrupt defined by UART_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref UART_INT_ALL
 *                          - \ref UART_INT_GLOBAL
 *                          - \ref UART_INT_LIN_CHECK_ERR
 *                          - \ref UART_INT_LIN_BIT_ERR
 *                          - \ref UART_INT_LIN_ID_MATCH
 *                          - \ref UART_INT_AUTOBAUD_LOCK
 *                          - \ref UART_INT_TX_REQ
 *                          - \ref UART_INT_TX_OVERFLOW
 *                          - \ref UART_INT_RX_TIMEOUT
 *                          - \ref UART_INT_RX_BREAK
 *                          - \ref UART_INT_RX_FRAME_ERR
 *                          - \ref UART_INT_RX_PARITY_ERR
 *                          - \ref UART_INT_RX_REQ
 *                          - \ref UART_INT_RX_OVERFLOW
 *                          - \ref UART_INT_RX_UNDERFLOW
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_ClearInt(UARTx, u32Int)        WRITE_REG((UARTx)->UARTIC, (u32Int))




/******************************************************************************
 * @brief      Set/Get Rx timeout threshold
 *
 * @param[in]  UARTx :  Select the UART module
 * @param[in]  u8Ths :  Number of UART baud cycles for the specified condition 
 *                      to keep before the timeout event is generated
 *                      For UART mode, the condition is that there is unread 
 *                      received data in the FIFO and the RXD bus keeps high
 *                      For LIN mode, the condition is that the received data 
 *                      length is below the expectation when the response field
 *                      is timeout.
 *                      Valid range: [1:255]
 *
 * @return     None
 * @return     Trigger Rx timeout threshold
 *             Valid range: [1:255]
 *
 * @note       The minimum allowed number is 1. Write a value as 0 will be reset to 1
 *
 ******************************************************************************/
#define UART_SetRxTimeoutThreshold(UARTx, u8Ths)           WRITE_REG((UARTx)->UARTTOTH, (u8Ths))
#define UART_GetRxTimeoutThreshold(UARTx)                  READ_REG((UARTx)->UARTTOTH)




/******************************************************************************
 * @brief      Enable write access to the protected UART registers
 *
 * @param[in]  UARTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_WALLOW(UARTx)                  ((UARTx)->UARTREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected UART registers
 *
 * @param[in]  UARTx:  Select the watchdog module
 *
 * @return     None
 *
 ******************************************************************************/
#define UART_WDIS(UARTx)                    ((UARTx)->UARTREGKEY = 0x0)




/**
 *  @brief  UART Public Function Declaration
 */
void UART_InitSpeed(UART_REGS *UARTx, uint32_t u32BaudRate);
void UART_Init(UART_REGS *UARTx, uint32_t u32BaudRate);
ErrorStatus UART_WaitAutoBaudReady(UART_REGS *UARTx);
void LIN_Init(UART_REGS *UARTx, LIN_ModeEnum eMode, uint32_t u32BaudRate);

void UART_Write(UART_REGS *UARTx, uint8_t *pu8Buffer, uint32_t u32Offset, uint32_t u32Count);
void UART_WriteText(UART_REGS *UARTx, const uint8_t *pu8Text);

ErrorStatus UART_Read(UART_REGS *UARTx, uint8_t *pu8Buffer, uint32_t u32Offset, uint32_t u32Count);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* UART_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
