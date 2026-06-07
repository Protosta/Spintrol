/******************************************************************************
 * @file     i2c.h
 * @brief    I2C driver header file.
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


#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  I2C Operation Mode Type Definition
 */
typedef enum
{
    I2C_MASTER              = 0x1,  /*!< Master mode  */
    I2C_SLAVE               = 0x0,  /*!< Slave  mode  */
} I2C_ModeEnum;




/**
 *  @brief I2C Speed Mode Type Definition
 */
typedef enum
{
    I2C_SPEED_STANDARD      = 0x0,  /*!< */
    I2C_SPEED_FAST          = 0x1,  /*!< */
    I2C_SPEED_HIGH          = 0x2,  /*!< */
} I2C_SpeedModeEnum;




/**
 *  @brief I2C Address Mode Type Definition
 */
typedef enum
{
    I2C_ADDR_7BIT           = 0x0,  /*!< I2C 7 bits address mode  */
    I2C_ADDR_10BIT          = 0x1,  /*!< I2C 10 bits address mode */
} I2C_AddrModeEnum;




/**
 *  @brief I2C Interrupt Type Definition
 */
typedef enum
{
    I2C_INT_RX_UNDERFLOW      = (1U << 0),    /*!< Receive FIFO underflow interrupt                                                   */
    I2C_INT_RX_OVERFLOW       = (1U << 1),    /*!< Receive FIFO overflow interrupt                                                    */
    I2C_INT_RX_REQ            = (1U << 2),    /*!< Receive data available interrupt. (LVL > TH)                                       */
    I2C_INT_TX_OVERFLOW       = (1U << 3),    /*!< Transmit FIFO overflow interrupt                                                   */
    I2C_INT_TX_REQ            = (1U << 4),    /*!< Transmit request data interrupt. (LVL <= TH)                                       */
    I2C_INT_READ_REQ          = (1U << 5),    /*!< Read request interrupt. It is set when I2C as a slave has been addressed
                                                 by a remote master that is asking for data to be transferred                         */
    I2C_INT_TX_ABORT          = (1U << 6),    /*!< Transmit abort interrupt                                                           */
    I2C_INT_RX_DONE           = (1U << 7),    /*!< Transmit done interrupt. When I2C is acting as a slave-transmitter, this bit
                                                 is set to 1 if the master does not acknowledge a transmitted byte. This
                                                 occurs on the last byte of the transmission, indicating that the transmission
                                                 is done                                                                              */
    I2C_INT_ACTIVITY          = (1U << 8),    /*!< Activity has been detected on I2C interface interrupt                              */
    I2C_INT_ACK_DETECT        = (1U << 9),    /*!< ACK is detected interrupt                                                          */
    I2C_INT_STOP_DETECT       = (1U << 10),   /*!< Stop condition occur interrupt.Indicates whether a STOP condition has occurred
                                                 on the I2C interface                                                                 */
    I2C_INT_START_DETECT      = (1U << 11),   /*!< Start condition occur interrupt. Indicates whether a START or RESTART condition
                                                 has occurred on the I2C interface                                                    */
    I2C_INT_GENERAL_CALL      = (1U << 12),   /*!< General call interrupt. Set only when a General Call address is received and
                                                 it is acknowledged                                                                   */
    I2C_INT_GLOBAL            = (1U << 13),   /*!< Global interrupt, only used for query interrupt flag or clear interrupt flag       */
    I2C_INT_ALL               = (0x3FFFU),    /*!< All interrupt                                                                      */
} I2C_IntEnum;




/**
 *  @brief I2C TX Abort Source Type Definition
 */
typedef enum
{
    I2C_SLV_TX_ABORT_BY_CMD_ERR                   = ( 1U << 15),
    I2C_SLV_TX_ABORT_BY_LOST_ARB                  = ( 1U << 14),
    I2C_SLV_TX_ABORT_BY_CLR_TXFIFO                = ( 1U << 13),
    I2C_MST_TX_ABORT_BY_LOST_ARB                  = ( 1U << 12),
    I2C_MST_TX_ABORT_BY_DISABLED                  = ( 1U << 11),
    I2C_MST_TX_ABORT_BY_TX_A10B_WITHOUT_RESTART   = ( 1U << 10),
    I2C_MST_TX_ABORT_BY_TX_START_WITHOUT_RESTART  = ( 1U << 9 ),
    I2C_MST_TX_ABORT_BY_HIGH_SPEED_NORESTART      = ( 1U << 8 ),
    I2C_MST_TX_ABORT_BY_START_ACK                 = ( 1U << 7 ),
    I2C_MST_TX_ABORT_BY_HIGH_SPEED_ACK            = ( 1U << 6 ),
    I2C_MST_TX_ABORT_BY_GCALL_READ                = ( 1U << 5 ),
    I2C_MST_TX_ABORT_BY_GCALL_NAK                 = ( 1U << 4 ),
    I2C_MST_TX_ABORT_BY_TX_DATA_NAK               = ( 1U << 3 ),
    I2C_MST_TX_ABORT_BY_TX_A10B2_NAK              = ( 1U << 2 ),
    I2C_MST_TX_ABORT_BY_TX_A10B1_NAK              = ( 1U << 1 ),
    I2C_MST_TX_ABORT_BY_TX_A7B_NAK                = ( 1U << 0 ),
    I2C_TX_ABORT_ALL                              = 0xFFFF,
} I2C_TxAbortSourceEnum;




/**
 *  @brief  I2C Status Type Definition
 */
typedef enum
{
    I2C_STS_ALL               = (0x3FFU),  /*!< Used for all status                                             */
    I2C_STS_SRX_D_LOST        = (1 << 9),  /*!< Slave receiver operation is aborted with at least one data byte
                                            received from an I2C transfer when I2CENABLE is changed from 1 to 0 */
    I2C_STS_SRX_ABORT         = (1 << 8),  /*!< I2CENABLE is changed from 1 to 0 when I2C slave is receiving from a remote mater on
                                           (a) The address byte of the slave transmitter
                                           (b) The address and data bytes of the slave receiver                 */
    I2C_STS_ENABLE            = (1 << 7),  /*!< I2C enabled status.                                             */
    I2C_STS_RX_FULL           = (1 << 6),  /*!< Receive FIFO completely full.                                   */
    I2C_STS_RX_NOT_EMPTY      = (1 << 5),  /*!< Receive FIFO not empty (so can read data from it).              */
    I2C_STS_TX_NOT_FULL       = (1 << 4),  /*!< Transmit FIFO not full (so can write data to it).               */
    I2C_STS_TX_EMPTY          = (1 << 3),  /*!< Transmit FIFO completely empty.                                 */
    I2C_STS_SLAVE_ACTIVITY    = (1 << 2),  /*!< Slave FSM is not in IDLE state (Active)                         */
    I2C_STS_MASTER_ACTIVITY   = (1 << 1),  /*!< Master FSM is not in IDLE state (Active)                        */
    I2C_STS_ACTIVITY          = (1 << 0)   /*!< Either master or slave FSM is active                            */
} I2C_StatusEnum;




/******************************************************************************
 * @brief      Enable/Disable Clock stretch when Rx FIFO full
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_EnableClockStretchWhenRxFull(I2Cx)                                  \
    SET_BITS( (I2Cx)->I2CCTL, I2CCTL_CLKSTRETCH_Msk )

#define I2C_DisableClockStretchWhenRxFull(I2Cx)                                 \
    CLEAR_BITS( (I2Cx)->I2CCTL, I2CCTL_CLKSTRETCH_Msk )

#define I2C_IsEnableClockStretchWhenRxFull(I2Cx)                                \
    READ_BITS( (I2Cx)->I2CCTL, I2CCTL_CLKSTRETCH_Msk )




/******************************************************************************
 * @brief      Enable/Disable I2C General Call ACK function (Slave mode)
 *             I2C responses with a ACK when it receives a general call
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_AckGeneralCall(I2Cx)                                                \
    SET_BITS( (I2Cx)->I2CCTL, I2CCTL_ACKGC_Msk )

#define I2C_NotAckGeneralCall(I2Cx)                                             \
    CLEAR_BITS( (I2Cx)->I2CCTL, I2CCTL_ACKGC_Msk )

#define I2C_IsAckGeneralCall(I2Cx)                                              \
    READ_BITS( (I2Cx)->I2CCTL, I2CCTL_ACKGC_Msk )




/******************************************************************************
 * @brief      Enable/Disable RESTART conditions (Master mode)
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_EnableRestart(I2Cx)                                                 \
    SET_BITS( (I2Cx)->I2CCTL, I2CCTL_RESTARTEN_Msk )

#define I2C_DisableRestart(I2Cx)                                                \
    CLEAR_BITS( (I2Cx)->I2CCTL, I2CCTL_RESTARTEN_Msk )

#define I2C_IsEnableRestart(I2Cx)                                               \
    READ_BITS( (I2Cx)->I2CCTL, I2CCTL_RESTARTEN_Msk )




/******************************************************************************
 * @brief      Set addressing mode
 *
 * @param[in]  I2Cx     :  Select the I2C module
 * @param[in]  eAddrMode:  Addressing mode
 *                         Please refer to I2C_AddrModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetAddressMode(I2Cx,eAddrMode)                                      \
    WRITE_FIELD( (I2Cx)->I2CCTL, I2CCTL_ADDRMODE_Msk, I2CCTL_ADDRMODE_Pos, eAddrMode )

#define I2C_GetAddressMode(I2Cx)                                                \
    READ_FIELD( (I2Cx)->I2CCTL, I2CCTL_ADDRMODE_Msk, I2CCTL_ADDRMODE_Pos )




/******************************************************************************
 * @brief      Set I2C mode
 *
 * @param[in]  I2Cx :  Select the I2C module
 * @param[in]  eMode:  I2C mode defined by I2C_ModeEnum
 *                     Following values are valid:
 *                       - \ref I2C_MASTER
 *                       - \ref I2C_SLAVE
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetMode(I2Cx, eMode)                                                \
    WRITE_FIELD( (I2Cx)->I2CCTL, I2CCTL_MODE_Msk, I2CCTL_MODE_Pos, (eMode) )

#define I2C_GetMode(I2Cx)                                                       \
    READ_FIELD( (I2Cx)->I2CCTL, I2CCTL_MODE_Msk, I2CCTL_MODE_Pos )




/******************************************************************************
 * @brief      Set target address for any master transaction
 *
 * @param[in]  I2Cx   :  Select the I2C module
 * @param[in]  u16Addr:  Target address
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetTargetAddress(I2Cx,u16Addr)                                      \
    WRITE_FIELD((I2Cx)->I2CMADDR, I2CMADDR_TARADDR_Msk, I2CMADDR_TARADDR_Pos, u16Addr)

#define I2C_GetTargetAddress(I2Cx)                                              \
    READ_FIELD( (I2Cx)->I2CMADDR, I2CMADDR_TARADDR_Msk, I2CMADDR_TARADDR_Pos )




/******************************************************************************
 * @brief      Set master code for high speed mode
 *
 * @param[in]  I2Cx   :  Select the I2C module
 * @param[in]  u8Code :  Code, 3-bits width
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetHighSpeedCode(I2Cx, u8Code)                                      \
    WRITE_FIELD( (I2Cx)->I2CMADDR, I2CMADDR_HSMCODE_Msk, I2CMADDR_HSMCODE_Pos, 0x08U | ( (u8Code) & 0x07U ) )

#define I2C_GetHighSpeedCode(I2Cx)                                              \
    ( READ_FIELD( (I2Cx)->I2CMADDR, I2CMADDR_HSMCODE_Msk, I2CMADDR_HSMCODE_Pos ) & 0x07U )




/******************************************************************************
 * @brief      Set slave address
 *
 * @param[in]  I2Cx   :  Select the I2C module
 * @param[in]  u16Addr:  Slave address
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetSlaveAddress(I2Cx,u16Addr)                                       \
    WRITE_REG( (I2Cx)->I2CSADDR, (u16Addr) )

#define I2C_GetSlaveAddress(I2Cx)                                               \
    READ_REG( (I2Cx)->I2CSADDR )




/******************************************************************************
 * @brief      Enable/Disable General Call
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 * FIXME update I2CMADDR_SPECIALCMD_GENERAL_CALL to enum variable
 ******************************************************************************/
#define I2C_EnableGeneralCall(I2Cx)                                             \
    ((I2Cx)->I2CMADDR = ((I2Cx)->I2CMADDR & ~I2CMADDR_SPECIALCMD_Msk) | I2CMADDR_SPECIALCMD_GENERAL_CALL)

#define I2C_DisableGeneralCall(I2Cx)                                            \
    CLEAR_BITS( (I2Cx)->I2CMADDR, I2CMADDR_SPECIALCMD_Msk )

#define I2C_IsEnableGeneralCall(I2Cx)                                           \
    ( ( (I2Cx)->I2CMADDR & I2CMADDR_SPECIALCMD_Msk ) == I2CMADDR_SPECIALCMD_GENERAL_CALL )




/******************************************************************************
 * @brief      Enable/Disable Start Byte
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 * FIXME update I2CMADDR_SPECIALCMD_GENERAL_CALL to enum variable
 ******************************************************************************/
#define I2C_EnableStartByte(I2Cx)                                               \
    ((I2Cx)->I2CMADDR = ((I2Cx)->I2CMADDR & ~I2CMADDR_SPECIALCMD_Msk) | I2CMADDR_SPECIALCMD_START_BYTE)

#define I2C_DisableStartByte(I2Cx)                                              \
    CLEAR_BITS((I2Cx)->I2CMADDR, I2CMADDR_SPECIALCMD_Msk)

#define I2C_IsEnableStartByte(I2Cx)                                             \
    ( ( (I2Cx)->I2CMADDR & I2CMADDR_SPECIALCMD_Msk ) == I2CMADDR_SPECIALCMD_START_BYTE )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 * @param[in]  eSpeedMode: Select the speed mode, defined by I2C_SpeedModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetSpeedMode(I2Cx, eSpeedMode)                                      \
    WRITE_FIELD( (I2Cx)->I2CCTL, I2CCTL_SPEED_Msk, I2CCTL_SPEED_Pos, (eSpeedMode) )

#define I2C_GetSpeedMode(I2Cx)                                                  \
    READ_FIELD( (I2Cx)->I2CCTL, I2CCTL_SPEED_Msk, I2CCTL_SPEED_Pos )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 5 : 0x00010000UL ] } )
 *
 ******************************************************************************/
#define I2C_SetStandardSpeedLowCount(I2Cx, u32Data)                             \
    WRITE_REG( (I2Cx)->I2CSSLCNT, (u32Data) - 1 )

#define I2C_GetStandardSpeedLowCount(I2Cx)                                      \
    ( READ_REG( (I2Cx)->I2CSSLCNT ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 6 : 0x00010000UL ] } )
 *
 ******************************************************************************/
#define I2C_SetStandardSpeedHighCount(I2Cx, u32Data)                            \
    WRITE_REG( (I2Cx)->I2CSSHCNT, (u32Data) - 1 )

#define I2C_GetStandardSpeedHighCount(I2Cx)                                     \
    ( READ_REG( (I2Cx)->I2CSSHCNT ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 5 : 0x00010000UL ] } )
 *
 ******************************************************************************/
#define I2C_SetFastSpeedLowCount(I2Cx, u32Data)                                 \
    WRITE_REG( (I2Cx)->I2CFSLCNT, (u32Data) - 1 )

#define I2C_GetFastSpeedLowCount(I2Cx)                                          \
    ( READ_REG( (I2Cx)->I2CFSLCNT ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 6 : 0x00010000UL ] } )
 *
 ******************************************************************************/
#define I2C_SetFastSpeedHighCount(I2Cx, u32Data)                                \
    WRITE_REG( (I2Cx)->I2CFSHCNT, (u32Data) - 1 )

#define I2C_GetFastSpeedHighCount(I2Cx)                                         \
    ( READ_REG( (I2Cx)->I2CFSHCNT ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 5 : 0x00010000UL ] } )
 *
 ******************************************************************************/
#define I2C_SetHighSpeedLowCount(I2Cx, u32Data)                                 \
    WRITE_REG( (I2Cx)->I2CHSLCNT, (u32Data) - 1 )

#define I2C_GetHighSpeedLowCount(I2Cx)                                          \
    ( READ_REG( (I2Cx)->I2CHSLCNT ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 2 : 0x00010000UL ] } )
 *
 ******************************************************************************/
#define I2C_SetHighSpeedHighCount(I2Cx, u32Data)                                \
    WRITE_REG( (I2Cx)->I2CHSHCNT, (u32Data) - 1 )

#define I2C_GetHighSpeedHighCount(I2Cx)                                         \
    ( READ_REG( (I2Cx)->I2CHSHCNT ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 2 : 0x00000100UL ] } )
 *
 ******************************************************************************/
#define I2C_SetFastSpeedSpikeCount(I2Cx, u32Data)                               \
    WRITE_REG( (I2Cx)->I2CFSSPKLEN, (u32Data) - 1 )

#define I2C_GetFastSpeedSpikeCount(I2Cx)                                        \
    ( READ_REG( (I2Cx)->I2CFSSPKLEN ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 2 : 0x00000100UL ] } )
 *
 ******************************************************************************/
#define I2C_SetHighSpeedSpikeCount(I2Cx, u32Data)                               \
    WRITE_REG( (I2Cx)->I2CHSSPKLEN, (u32Data) - 1 )

#define I2C_GetHighSpeedSpikeCount(I2Cx)                                        \
    ( READ_REG( (I2Cx)->I2CHSSPKLEN ) + 1 )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 2 : 0x000000FFUL ] } )
 *             FIXME if need 1 I2C_CLK, set this field value 2
 ******************************************************************************/
#define I2C_SetSDASetupCount(I2Cx, u32Data)                                     \
    WRITE_REG( (I2Cx)->I2CSDASETUP, (u32Data) )

#define I2C_GetSDASetupCount(I2Cx)                                              \
    READ_REG( (I2Cx)->I2CSDASETUP )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx      : Select the I2C module
 *
 * @return     None
 *
 * @note       assert ( u32Data inside { [ 1 : 0x0000FFFFUL ] } )
 ******************************************************************************/
#define I2C_SetSDAHoldCount(I2Cx, u32Data)                                      \
    WRITE_REG( (I2Cx)->I2CSDAHOLD, (u32Data) )

#define I2C_GetSDAHoldCount(I2Cx)                                               \
    READ_REG( (I2Cx)->I2CSDAHOLD )




/******************************************************************************
 * @brief      FIXME
 *
 * @param[in]  I2Cx     : Select the I2C module
 * @param[in]  u32Query : ORed by I2C_TxAbortSourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_GetTxAbortSource(I2Cx, u32Query)                                    \
    ( READ_REG( (I2Cx)->I2CTXABRTSRC ) & (u32Query) )




/******************************************************************************
 * @brief      Master read request (Act as a master)
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_MasterReadCmd(I2Cx)                                                 \
    WRITE_REG( (I2Cx)->I2CDATACMD, 0x100U )




/******************************************************************************
 * @brief      Send one byte data
 *
 * @param[in]  I2Cx  : Select the I2C module
 * @param[in]  u8Data: Byte data to be sent
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_WriteByte(I2Cx,u8Data)                                              \
    WRITE_REG( (I2Cx)->I2CDATACMD, ( (uint32_t)(u8Data) & 0xFFU ) )




/******************************************************************************
 * @brief      I2c read one byte
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     The received data(8-bit)
 *
 ******************************************************************************/
#define I2C_ReadByte(I2Cx)                                                      \
    ( (uint8_t)( READ_REG( (I2Cx)->I2CDATACMD ) & 0xFFU ) )




/******************************************************************************
 * @brief      Set the Transmit FIFO threshold
 *
 * @param[in]  I2Cx    :  Select the I2C module
 * @param[in]  u32Level:  Transmit FIFO threshold level
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetTxFIFOThreshold(I2Cx,u32Level)                                   \
    WRITE_REG( (I2Cx)->I2CTXTH, (u32Level) )

#define I2C_GetTxFIFOThreshold(I2Cx)                                            \
    READ_REG( (I2Cx)->I2CTXTH )




/******************************************************************************
 * @brief      Set the Receive FIFO threshold
 *
 * @param[in]  I2Cx    :  Select the I2C module
 * @param[in]  u32Level:  Receive FIFO threshold level
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_SetRxFIFOThreshold(I2Cx,u32Level)                                   \
    WRITE_REG( (I2Cx)->I2CRXTH, (u32Level) )

#define I2C_GetRxFIFOThreshold(I2Cx)                                            \
    READ_REG( (I2Cx)->I2CRXTH )




/******************************************************************************
 * @brief      Get the Transmit FIFO level
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     The number of valid data entries in the transmit FIFO
 *
 ******************************************************************************/
#define I2C_GetTxFIFOLevel(I2Cx)                                                \
    READ_REG((I2Cx)->I2CTXLVL)




/******************************************************************************
 * @brief      Get the Receive FIFO level
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     The number of valid data entries in the receive FIFO
 *
 ******************************************************************************/
#define I2C_GetRxFIFOLevel(I2Cx)                                                \
    READ_REG((I2Cx)->I2CRXLVL)




/******************************************************************************
 * @brief      Enable/Disable I2C module Receive DMA
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
/* #define I2C_EnableRxDMA(I2Cx)                                                   \
   SET_BITS( (I2Cx)->I2CDMAEN, I2CDMAEN_RXDMAEN_Msk )

#define I2C_DisableRxDMA(I2Cx)                                                  \
   CLEAR_BITS( (I2Cx)->I2CDMAEN, I2CDMAEN_RXDMAEN_Msk )

#define I2C_IsEnableRxDMA(I2Cx)                                                 \
   READ_BITS( (I2Cx)->I2CDMAEN, I2CDMAEN_RXDMAEN_Msk ) */




/******************************************************************************
 * @brief      Enable/Disable I2C module Transmit DMA
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
/* #define I2C_EnableTxDMA(I2Cx)                                                   \
   SET_BITS( (I2Cx)->I2CDMAEN, I2CDMAEN_TXDMAEN_Msk )

#define I2C_DisableTxDMA(I2Cx)                                                  \
   CLEAR_BITS( (I2Cx)->I2CDMAEN, I2CDMAEN_TXDMAEN_Msk )

#define I2C_IsEnableTxDMA(I2Cx)                                                 \
   READ_BITS( (I2Cx)->I2CDMAEN, I2CDMAEN_TXDMAEN_Msk ) */




/******************************************************************************
 * @brief      Enable/Disable I2C module both Transmit and Receive DMA
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     None
 *
 ******************************************************************************/
/* #define I2C_EnableDMA(I2Cx)                                                     \
   SET_BITS( (I2Cx)->I2CDMAEN, (I2CDMAEN_TXDMAEN_Msk | I2CDMAEN_RXDMAEN_Msk) )

#define I2C_DisableDMA(I2Cx)                                                    \
   CLEAR_BITS( (I2Cx)->I2CDMAEN, (I2CDMAEN_TXDMAEN_Msk | I2CDMAEN_RXDMAEN_Msk) ) */




/******************************************************************************
 * @brief      Set the DMA Transmit data level
 *
 * @param[in]  I2Cx    :  Select the I2C module
 * @param[in]  u32Level:  Transmit data level
 *
 * @return     None
 *
 ******************************************************************************/
/* #define I2C_SetDMATxFIFOThreshold(I2Cx,u32Level)                                \
   WRITE_REG( (I2Cx)->I2CDMATXTH, (u32Level) )

#define I2C_GetDMATxFIFOThreshold(I2Cx)                                         \
   READ_REG( (I2Cx)->I2CDMATXTH ) */




/******************************************************************************
 * @brief      Set the DMA Receive data level
 *
 * @param[in]  I2Cx    :  Select the I2C module
 * @param[in]  u32Level:  Receive data level
 *
 * @return     None
 *
 ******************************************************************************/
/* #define I2C_SetDMARxFIFOThreshold(I2Cx,u32Level)                                \
   WRITE_REG( (I2Cx)->I2CDMARXTH, (u32Level) )

#define I2C_GetDMARxFIFOThreshold(I2Cx)                                         \
   READ_REG( (I2Cx)->I2CDMARXTH ) */




/******************************************************************************
 * @brief      Get I2C status
 *
 * @param[in]  I2Cx    :  Select the I2C module
 * @param[in]  u32Query:  The status defined by I2C_StatusEnum
 *                        Multiple status can be ORed simultaneously
 *
 * @return     0     - None of the queried statuses occurred;
 *             not 0 - Corresponding statuses for non-zero bit occurred.
 *
 ******************************************************************************/
#define I2C_GetStatus(I2Cx, u32Query)                                           \
    ( READ_REG( (I2Cx)->I2CSTS ) & (u32Query) )




/******************************************************************************
 * @brief      Enable/Disable I2C interrupt
 *
 * @param[in]  I2Cx  :  Select the I2C module
 * @param[in]  u32Int:  Select the interrupt, defined by I2C_IntEnum
 *                      Multiple interrupts can be ORed simultaneously
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_EnableInt(I2Cx, u32Int)                                             \
    SET_BITS( (I2Cx)->I2CIE, (u32Int) )

#define I2C_DisableInt(I2Cx, u32Int)                                            \
    CLEAR_BITS( (I2Cx)->I2CIE, (u32Int) )

#define I2C_IsEnableInt(I2Cx, u32Int)                                           \
    ( READ_REG( (I2Cx)->I2CIE ) & (u32Int) )





/******************************************************************************
 * @brief      Clear I2C interrupt
 *
 * @param[in]  I2Cx:  Select the I2C module
 * @param[in]  u32Int:  Select the interrupt, defined by I2C_IntEnum
 *                    Multiple interrupts can be ORed simultaneously
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_ClearInt(I2Cx, u32Int)                                              \
    WRITE_REG( (I2Cx)->I2CIC, (u32Int) )




/******************************************************************************
 * @brief      Get I2C interrupt status
 *
 * @param[in]  I2Cx:  Select the I2C module
 * @param[in]  u32Int:  Select the interrupt, defined by I2C_IntEnum
 *                    Multiple interrupts can be ORed simultaneously
 *
 * @return     0 - None of the queried interrupts occurred
 *             Not 0 - Corresponding interrupts for non-zero bit occurred
 *
 ******************************************************************************/
#define I2C_GetIntFlag(I2Cx, u32Int)                                            \
    ( READ_REG( (I2Cx)->I2CIF ) & (u32Int) )




/******************************************************************************
 * @brief      Get I2C event raw status
 *
 * @param[in]  I2Cx:  Select the I2C module
 * @param[in]  u32Int:  Select the interrupt, defined by I2C_IntEnum
 *                    Multiple interrupts can be ORed simultaneously
 *
 * @return     0 - None of the queried events occurred
 *             Not 0 - Corresponding events for non-zero bit occurred
 *
 ******************************************************************************/
#define I2C_GetIntRawFlag(I2Cx, u32Int)                                         \
    ( READ_REG( (I2Cx)->I2CRAWIF ) & (u32Int) )




/******************************************************************************
 * @brief      Enable/Disable write access to the protected I2C registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define I2C_WALLOW(I2Cx)                                                        \
      WRITE_REG( (I2Cx)->I2CREGKEY, 0x1ACCE551U )

#define I2C_WDIS(I2Cx)                                                          \
      WRITE_REG( (I2Cx)->I2CREGKEY, 0x0U )




/**
 *  @brief  I2C Public Function Declaration
 */
ErrorStatus I2C_InitStandardSpeed(I2C_REGS *I2Cx, uint32_t u32Speed, I2C_ModeEnum eMode);
ErrorStatus I2C_InitFastSpeed(I2C_REGS *I2Cx, uint32_t u32Speed, I2C_ModeEnum eMode);
ErrorStatus I2C_InitHighSpeed(I2C_REGS *I2Cx, uint8_t u8MasterCode, uint32_t u32Speed0, uint32_t u32Speed1, I2C_ModeEnum eMode);

void I2C_MasterInit(I2C_REGS *I2Cx);
void I2C_SlaveInit(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode, uint16_t u16SlvAddr);

void I2C_Enable(I2C_REGS *I2Cx);
void I2C_Disable(I2C_REGS *I2Cx);

ErrorStatus I2C_MasterWrite(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode, uint16_t u16TargetAddr, uint8_t *pu8WriteBuf, uint32_t u32Count);
ErrorStatus I2C_SlaveRead(I2C_REGS *I2Cx, uint8_t *pu8ReadBuf, uint32_t u32Count);

ErrorStatus I2C_MasterRead(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode, uint16_t u16TargetAddr, uint8_t *pu8ReadBuf, uint32_t u32Count);
ErrorStatus I2C_SlaveWrite(I2C_REGS *I2Cx, uint8_t *pu8WriteBuffer, uint32_t u32Count);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* I2C_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

