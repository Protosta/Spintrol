/******************************************************************************
 * @file     spi.h
 * @brief    SPI module header file.
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
 *
 * @attention
 * THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION REGARDING
 * THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM. SPINTROL S NOT BE
 * LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL DOES NOT GUARANTEE THE
 * CORRECTNESS OF THIS SOFTWARE AND RESERVES THE RIGHT TO MODIFY THE SOFTWARE
 * WITHOUT NOTIFICATION.
 *
 ******************************************************************************/


#ifndef SPI_H
#define SPI_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  SPI FIFO Depth (32-bits width)
 */
#define SPI_FIFO_DEPTH          (16)




/**
 *  @brief  SPI PSP Net Mode Slot Number
 */
#define PSP_SLOT_NUM            (8)




/**
 *  @brief  SPI Operation Mode Type Definition
 */
typedef enum
{
    SPI_MASTER                = 0x0,  /*!< Master mode  */
    SPI_SLAVE                 = 0x1,  /*!< Slave  mode  */
} SPI_ModeEnum;




/**
 *  @brief  SPI Protocol Type Definition
 */
typedef enum
{
    SPI_SPI                   = 0x0,  /*!< Motorola Serial Peripheral Interface          */
    SPI_SSP                   = 0x1,  /*!< Texas Instruments Synchronous Serial Protocol */
    SPI_MWIRE                 = 0x2,  /*!< National Semiconductor Microwire              */
    SPI_PSP                   = 0x3,  /*!< Programmable Serial Protocol                  */
    SPI_PSP_NET               = 0x4   /*!< Programmable Serial Protocol Net Mode         */
} SPI_ProtocolEnum;




/**
 *  @brief  SPI Pin (TXD) Tri-state Output Mode Type Definition
 */
typedef enum
{
    SPI_TRIOUT_ON_MIDDLE_LSB  = 0,  /*!< TXD is tri-stated 1/2 clock cycle after the beginning of the LSB.  */
    SPI_TRIOUT_ON_END_LSB     = 1   /*!< TXD is tri-stated on the clock edge that ends the LSB.             */
} SPI_TriOutEnum;




/**
 *  @brief  SPI Mode Type Definition
 */
typedef enum
{
    SPI_MODE_PHS_POL_00       = 0x0,  /*!< PHS = 0, POL = 0 */
    SPI_MODE_PHS_POL_01       = 0x1,  /*!< PHS = 0, POL = 1 */
    SPI_MODE_PHS_POL_10       = 0x2,  /*!< PHS = 1, POL = 0 */
    SPI_MODE_PHS_POL_11       = 0x3   /*!< PHS = 1, POL = 1 */
} SPI_SPIModeEnum;




/**
 *  @brief  MWIRE Transmit Command Data Size Type Definition
 *          Only used for MWIRE.
 */
typedef enum
{
    MWIRE_CMD_8BIT            = 0,    /*!< 8-bit command words are transmitted.    */
    MWIRE_CMD_16BIT           = 1     /*!< 16-bit command words are transmitted.   */
} MWIRE_CommandSizeEnum;




/**
 *  @brief  PSP Mode Type Definition
 */
typedef enum
{
    PSP_MODE_DF_SR_IL         = 0x0,  /*!< Data Driven (Falling), Data Sampled (Rising ), Idle State (Low )  */
    PSP_MODE_DR_SF_IL         = 0x1,  /*!< Data Driven (Rising ), Data Sampled (Falling), Idle State (Low )  */
    PSP_MODE_DR_SF_IH         = 0x2,  /*!< Data Driven (Rising ), Data Sampled (Falling), Idle State (High)  */
    PSP_MODE_DF_SR_IH         = 0x3   /*!< Data Driven (Falling), Data Sampled (Rising ), Idle State (High)  */
} PSP_ModeEnum;




/**
 *  @brief  End Of Transfer Data State Type Definition
 */
typedef enum
{
    SPI_TRANS_END_STATE_0     = 0,  /*!< Level low.            */
    SPI_TRANS_END_STATE_LSB   = 1   /*!< Level of LSB value.   */
} SPI_TransferEndStateEnum;




/**
 *  @brief  PSP Frame Sync Mode Type Definition
 */
typedef enum
{
    PSP_SYNC_AFTER_DMYSTOP    = 0,  /*!< Next frame is asserted after the end of the DMYSTOP timing.*/
    PSP_SYNC_AFTER_LSB        = 1   /*!< Next frame is asserted with the LSB of the previous frame. */
} PSP_SyncEnum;




/**
 *  @brief  PSP Slot Selection Type Definition
 */
typedef enum
{
    PSP_SLOT_NONE             = ( 0x00U),   /*!< No time slot active       */
    PSP_SLOT_0                = (0 << 0),   /*!< TX/RX time slot 0 active. */
    PSP_SLOT_1                = (1 << 1),   /*!< TX/RX time slot 1 active. */
    PSP_SLOT_2                = (1 << 2),   /*!< TX/RX time slot 2 active. */
    PSP_SLOT_3                = (1 << 3),   /*!< TX/RX time slot 3 active. */
    PSP_SLOT_4                = (1 << 4),   /*!< TX/RX time slot 4 active. */
    PSP_SLOT_5                = (1 << 5),   /*!< TX/RX time slot 5 active. */
    PSP_SLOT_6                = (1 << 6),   /*!< TX/RX time slot 6 active. */
    PSP_SLOT_7                = (1 << 7),   /*!< TX/RX time slot 7 active. */
    PSP_SLOT_ALL              = 0xFF        /*!< All time slot.            */
} PSP_SlotEnum;




/**
 *  @brief  SPI Status Type Definition
 */
typedef enum
{
    SPI_STS_ALL               = (0x1FFFU),  /*!< Used for all status                                             */
    SPI_STS_SFRM_LOCKED       = (1 << 12),  /*!< FIXME : SFRM locked                                             */
    SPI_STS_NET_BUSY          = (1 << 11),  /*!< SPI Port is in Network Mode and a frame is currently active.    */
    SPI_STS_RX_EVEN_SAMPLE    = (1 << 7),   /*!< Receive FIFO entry has an even number of samples.               */
    SPI_STS_TX_EVEN_SAMPLE    = (1 << 6),   /*!< Transmit FIFO entry has an even number of samples.              */
    SPI_STS_SLAVE_NOT_READY   = (1 << 5),   /*!< SPI is Not Ready to Tranceive Data. Only Used for Slave Mode.   */
    SPI_STS_BUSY              = (1 << 4),   /*!< SPI is Busy.                                                    */
    SPI_STS_RX_NOT_EMPTY      = (1 << 3),   /*!< Receive FIFO Not Empty.                                         */
    SPI_STS_RX_FULL           = (1 << 2),   /*!< Receive FIFO Full.                                              */
    SPI_STS_TX_EMPTY          = (1 << 1),   /*!< Transmit FIFO Empty.                                            */
    SPI_STS_TX_NOT_FULL       = (1 << 0)    /*!< Transmit FIFO Not Full.                                         */
} SPI_StatusEnum;




/**
 *  @brief  SPI Interrupt Type Definition
 */
typedef enum
{
    SPI_INT_ALL              = (0x7FFU),  /*!< Used for all int                                             */
    SPI_INT_GLOBAL           = (1 << 10), /*!< Global Interrupt Flag.
                                             Only used for query or clear interrupt flag.                   */
    SPI_INT_DMA_EOC          = (1 << 9),  /*!< DMA End of Chain Interrupt.                                  */
    SPI_INT_TRAIL_BYTE       = (1 << 8),  /*!< Trailing Byte Interrupt.                                     */
    SPI_INT_BIT_CNT_ERROR    = (1 << 7),  /*!< Bit Count Error Interrupt.                                   */
    SPI_INT_TX_REQ           = (1 << 6),  /*!< Transmit request data interrupt. (LVL <= TH)                 */
    SPI_INT_TX_OVERFLOW      = (1 << 5),  /*!< Transmit FIFO Overflow Interrupt.                            */
    SPI_INT_TX_UNDERFLOW     = (1 << 4),  /*!< Transmit FIFO Underflow Interrupt. Occurred in Network Mode. */
    SPI_INT_RX_TIMEOUT       = (1 << 3),  /*!< Receiver Timeout Interrupt                                   */
    SPI_INT_RX_REQ           = (1 << 2),  /*!< Receive data available interrupt. (LVL > TH)                 */
    SPI_INT_RX_OVERFLOW      = (1 << 1),  /*!< Receive FIFO Overflow Interrupt                              */
    SPI_INT_RX_UNDERFLOW     = (1 << 0)   /*!< Receive FIFO Underflow Interrupt                             */
} SPI_IntEnum;




/******************************************************************************
 * @brief      Enable/Disable/Get status of SPI port
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_Enable(SPIx)                                                        \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_EN_Msk)

#define SPI_Disable(SPIx)                                                       \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_EN_Msk)

#define SPI_IsEnable(SPIx)                                                      \
    ((SPIx)->SPICTL0 & SPICTL0_EN_Msk)




/******************************************************************************
 * @brief      Set/Get baud count
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  u32Data:  Baud count
 *
 * @return     None
 * @return     Unsigned 32bits baud count
 *
 ******************************************************************************/
#define SPI_SetBaudCount(SPIx, u32Data)                                         \
    WRITE_REG((SPIx)->SPIBDCNT, (u32Data - 1U) & 0xFFFFU)

#define SPI_GetBaudCount(SPIx)                                                  \
    ( 1U + READ_REG((SPIx)->SPIBDCNT) )




/******************************************************************************
 * @brief      Set/Get SPI mode
 *
 * @param[in]  SPIx :  Select the SPI module
 * @param[in]  eMode:  SPI mode defined by SPI_ModeEnum
 *                     Following values are valid:
 *                       - \ref SPI_MASTER
 *                       - \ref SPI_SLAVE
 *
 * @return     None
 * @return     SPI mode defined by SPI_ModeEnum
 *
 ******************************************************************************/
#define SPI_SetMode(SPIx, eMode)                                                \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_SELSLV_Msk, SPICTL0_SELSLV_Pos,(eMode))

#define SPI_GetMode(SPIx)                                                       \
    READ_FIELD((SPIx)->SPICTL0, SPICTL0_SELSLV_Msk, SPICTL0_SELSLV_Pos)




/******************************************************************************
 * @brief      Set/Get protocol
 *
 * @param[in]  SPIx     :  Select the SPI module
 * @param[in]  eProtocol:  Protocol defined by SPI_ProtocolEnum
 *                         Following values are valid:
 *                           - \ref SPI_SPI
 *                           - \ref SPI_SSP
 *                           - \ref SPI_MWIRE
 *                           - \ref SPI_PSP
 *                           - \ref SPI_PSP_NET
 *
 * @return     None
 * @return     Protocol defined by SPI_ProtocolEnum
 *
 * @note       Setting SPI_PSP_NET causes the SCLK to run continuously,
 *             if the SPI port is a master of the clock.
 *
 ******************************************************************************/
#define SPI_SetProtocol(SPIx, eProtocol)                                        \
    MODIFY_REG((SPIx)->SPICTL0,                                                 \
               ( SPICTL0_FRMFMT_Msk | SPICTL0_MODE_Msk ),                       \
               (((eProtocol & 0x3) << SPICTL0_FRMFMT_Pos)|(((eProtocol & 0x4)>> 2) << SPICTL0_MODE_Pos))                                                                           \
              )

#define SPI_GetProtocol(SPIx)                                                   \
    (( READ_FIELD((SPIx)->SPICTL0,   SPICTL0_MODE_Msk,SPICTL0_MODE_Pos) << 2)   \
     |READ_FIELD((SPIx)->SPICTL0, SPICTL0_FRMFMT_Msk, SPICTL0_FRMFMT_Pos))




/******************************************************************************
 * @brief      Set/Get SPI mode
 *
 * @param[in]  SPIx :  Select the SPI module
 * @param[in]  eMode:  SPI mode defined by SPI_SPIModeEnum
 *                     Following values are valid:
 *                       - \ref SPI_MODE_PHS_POL_00
 *                       - \ref SPI_MODE_PHS_POL_01
 *                       - \ref SPI_MODE_PHS_POL_10
 *                       - \ref SPI_MODE_PHS_POL_11
 *
 * @return     None
 * @return     SPI mode defined by SPI_SPIModeEnum
 *
 ******************************************************************************/
#define SPI_SetSPIMode(SPIx, eMode)                                             \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_SPIMODE_Msk, SPICTL0_SPIMODE_Pos,(eMode))

#define SPI_GetSPIMode(SPIx)                                                    \
    READ_FIELD((SPIx)->SPICTL0, SPICTL0_SPIMODE_Msk, SPICTL0_SPIMODE_Pos)




/******************************************************************************
 * @brief      Set/Get MWIRE Command Size
 *
 * @param[in]  SPIx :  Select the SPI module
 * @param[in]  eSize:  MWIRE command size defined by MWIRE_CommandSizeEnum
 *                     Following values are valid:
 *                       - \ref MWIRE_CMD_8BIT
 *                       - \ref MWIRE_CMD_16BIT
 *
 * @return     None
 * @return     MWIRE command size defined by MWIRE_CommandSizeEnum
 *
 ******************************************************************************/
#define SPI_SetMWIRECmdSize(SPIx, eSize)                                        \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_MWIREDS_Msk, SPICTL0_MWIREDS_Pos,(eSize))

#define SPI_GetMWIRECmdSize(SPIx)                                               \
    READ_FIELD((SPIx)->SPICTL0, SPICTL0_MWIREDS_Msk, SPICTL0_MWIREDS_Pos)




/******************************************************************************
 * @brief      Set/Get PSP mode
 *
 * @param[in]  SPIx :  Select the SPI module
 * @param[in]  eSize:  PSP mode defined by PSP_ModeEnum
 *                     Following values are valid:
 *                       - \ref PSP_MODE_DF_SR_IL
 *                       - \ref PSP_MODE_DR_SF_IL
 *                       - \ref PSP_MODE_DR_SF_IH
 *                       - \ref PSP_MODE_DF_SR_IH
 *
 * @return     None
 * @return     PSP mode defined by PSP_ModeEnum
 *
 ******************************************************************************/
#define SPI_SetPSPMode(SPIx, eMode)                                             \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_CLKMODE_Msk, SPIPSP_CLKMODE_Pos, (eMode) )

#define SPI_GetPSPMode(SPIx)                                                    \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_CLKMODE_Msk, SPIPSP_CLKMODE_Pos)




/******************************************************************************
 * @brief      Set/Get End Of Transfer Data State
 *
 * @param[in]  SPIx      :  Select the SPI module
 * @param[in]  eTranState:  End of transfer data state defined by SPI_TransferEndStateEnum
 *                          Following values are valid:
 *                            - \ref SPI_TRANS_END_STATE_0
 *                            - \ref SPI_TRANS_END_STATE_LSB
 *
 * @return     None
 * @return     End of transfer data state defined by SPI_TransferEndStateEnum
 *
 * @note       Only worked when tri-state output disabled for master mode
 *
 ******************************************************************************/
#define SPI_SetEndOfTransferState(SPIx, eTranState)                             \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_ETDS_Msk, SPIPSP_ETDS_Pos, (eTranState) )

#define SPI_GetEndOfTransferState(SPIx)                                         \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_ETDS_Msk, SPIPSP_ETDS_Pos )




/******************************************************************************
 * @brief      Set/Get PSP start delay
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Data:  Number of non-active clocks (SCLK) that define the
 *                      duration of idle time.
 *                      Valid range: [0:7]
 *
 * @return     None
 * @return     Number of non-active clocks (SCLK) that define the duration of idle time
 *             Valid range: [0:7]
 *
 * @note       Must be 0 in SPI_PSP_NET mode
 *
 ******************************************************************************/
#define SPI_SetPSPStartDelay(SPIx, u8Data)                                      \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_STARTDLY_Msk, SPIPSP_STARTDLY_Pos,((u8Data) & 0x7 ))

#define SPI_GetPSPStartDelay(SPIx)                                              \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_STARTDLY_Msk, SPIPSP_STARTDLY_Pos)




/******************************************************************************
 * @brief      Set/Get PSP dummy start
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Data:  Number of active clocks (SCLKs) between the end of
 *                      start delay and when the MSB of transmit/receive data
 *                      is driven.
 *                      Valid range: [0:15]
 *
 * @return     None
 * @return     Number of active clocks (SCLKs) between the end of start delay
 *             and when the MSB of transmit/receive data is driven.
 *             Valid range: [0:15]
 *
 * @note       Must be 0 in SPI_PSP_NET mode
 *
 ******************************************************************************/
#define SPI_SetPSPDummyStart(SPIx, u8Data)                                      \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_DMYSTART_Msk, SPIPSP_DMYSTART_Pos,( (u8Data) & 0xF ))

#define SPI_GetPSPDummyStart(SPIx)                                              \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_DMYSTART_Msk, SPIPSP_DMYSTART_Pos)




/******************************************************************************
 * @brief      Set/Get PSP frame delay
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Data:  Number of active one-half clocks (SCLK), asserted from
 *                      the MSB of TXD or RXD being driven to SFRMx.
 *                      Valid range: [0:127]
 *
 * @return     None
 * @return     Number of active one-half clocks (SCLK), asserted from the MSB
 *             of TXD or RXD being driven to SFRMx.
 *             Valid range: [0:127]
 *
 * @note       Must be 0 in Network mode
 *
 ******************************************************************************/
#define SPI_SetPSPFrameDelay(SPIx, u8Data)                                      \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_FRMDLY_Msk, SPIPSP_FRMDLY_Pos,( (u8Data) & 0x7F ))

#define SPI_GetPSPFrameDelay(SPIx)                                              \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_FRMDLY_Msk, SPIPSP_FRMDLY_Pos)




/******************************************************************************
 * @brief      Set/Get PSP frame width
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Data:  Frame width based on clocks (SCLK).
 *                      Valid range: [1:63]
 *
 * @return     None
 * @return     Frame width based on clocks (SCLK).
 *             Valid range: [1:63]
 *
 * @note       write 0 will be treated as 1 SCLK period for PSP mode
 *
 ******************************************************************************/
#define SPI_SetPSPFrameWidth(SPIx, u8Data)                                      \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_FRMWIDTH_Msk, SPIPSP_FRMWIDTH_Pos,((u8Data) & 0x3F ))

#define SPI_GetPSPFrameWidth(SPIx)                                              \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_FRMWIDTH_Msk, SPIPSP_FRMWIDTH_Pos)




/******************************************************************************
 * @brief      Set/Get PSP dummy stop
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Data:  Number of active SCLK that follow the end of the
 *                      transmitted data.
 *                      Valid range: [0:31]
 *
 * @return     None
 * @return     Number of active SCLK that follow the end of the transmitted data.
 *             Valid range: [0:31]
 *
 * @note       Must be 0 in Network mode
 *
 ******************************************************************************/
#define SPI_SetPSPDummyStop(SPIx, u8Data)                                       \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_DMYSTOP_Msk,  SPIPSP_DMYSTOP_Pos,( (u8Data) & 0x1F ))

#define SPI_GetPSPDummyStop(SPIx)                                               \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_DMYSTOP_Msk,  SPIPSP_DMYSTOP_Pos)




/******************************************************************************
 * @brief      Set/Get PSP Frame Sync Relative Timing Bit
 *
 * @param[in]  SPIx     :  Select the SPI module
 * @param[in]  eSyncMode:  Sync mode defined by PSP_SyncEnum
 *                         Following values are valid:
 *                           - \ref PSP_SYNC_AFTER_DMYSTOP
 *                           - \ref PSP_SYNC_AFTER_LSB
 *
 * @return     None
 * @return     Sync mode defined by PSP_SyncEnum
 *
 ******************************************************************************/
#define SPI_SetPSPFrameSync(SPIx, eSyncMode)                                    \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_SYNC_Msk, SPIPSP_SYNC_Pos, (eSyncMode) )

#define SPI_GetPSPFrameSync(SPIx)                                               \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_SYNC_Msk, SPIPSP_SYNC_Pos )




/******************************************************************************
 * @brief      Set/Get slot per frame
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Data:  Slot number
 *                      Valid range: [1:PSP_SLOT_NUM]
 *
 * @return     None
 * @return     Slot number
 *             Valid range: [1:PSP_SLOT_NUM]
 *
 * @note       only for SPI_PSP_NET mode
 *
 ******************************************************************************/
#define SPI_SetPSPNetFrameSlotNum(SPIx, u8Data)                                 \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_FRMSLOT_Msk, SPICTL0_FRMSLOT_Pos,((u8Data) - 1U))

#define SPI_GetPSPNetFrameSlotNum(SPIx)                                         \
    (1U + READ_FIELD((SPIx)->SPICTL0, SPICTL0_FRMSLOT_Msk, SPICTL0_FRMSLOT_Pos))




/******************************************************************************
 * @brief      Set SPI Tx active slot
 *
 * @param[in]  SPIx   : Select the SPI module
 * @param[in]  u32Slot: Time slot defined by PSP_SlotEnum
 *                      ORed of the following values are valid:
 *                        - \ref PSP_SLOT_ALL
 *                        - \ref PSP_SLOT_0
 *                        - \ref PSP_SLOT_1
 *                        - \ref PSP_SLOT_2
 *                        - \ref PSP_SLOT_3
 *                        - \ref PSP_SLOT_4
 *                        - \ref PSP_SLOT_5
 *                        - \ref PSP_SLOT_6
 *                        - \ref PSP_SLOT_7
 *
 * @return     None
 *
 ******************************************************************************/
/* #define SPI_SetPSPNetFrameTxActiveSlot(SPIx, u32Slot)                           \
   WRITE_REG((SPIx)->SPITSLOTEN, (u32Slot)) */





/******************************************************************************
 * @brief      Get SPI Tx active slot
 *
 * @param[in]  SPIx   : Select the SPI module
 * @param[in]  u32Slot: Time slot defined by PSP_SlotEnum
 *                      ORed of the following values are valid:
 *                        - \ref PSP_SLOT_ALL
 *                        - \ref PSP_SLOT_0
 *                        - \ref PSP_SLOT_1
 *                        - \ref PSP_SLOT_2
 *                        - \ref PSP_SLOT_3
 *                        - \ref PSP_SLOT_4
 *                        - \ref PSP_SLOT_5
 *                        - \ref PSP_SLOT_6
 *                        - \ref PSP_SLOT_7
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
/* #define SPI_IsEnablePSPNetFrameTxActiveSlot(SPIx, u32Slot)                         \
   ((SPIx)->SPITSLOTEN & (u32Slot)) */




/******************************************************************************
 * @brief      Set SPI Rx active slot
 *
 * @param[in]  SPIx   : Select the SPI module
 * @param[in]  u32Slot: Time slot defined by PSP_SlotEnum
 *                      ORed of the following values are valid:
 *                        - \ref PSP_SLOT_ALL
 *                        - \ref PSP_SLOT_0
 *                        - \ref PSP_SLOT_1
 *                        - \ref PSP_SLOT_2
 *                        - \ref PSP_SLOT_3
 *                        - \ref PSP_SLOT_4
 *                        - \ref PSP_SLOT_5
 *                        - \ref PSP_SLOT_6
 *                        - \ref PSP_SLOT_7
 *
 * @return     None
 *
 ******************************************************************************/
/* #define SPI_SetPSPNetFrameRxActiveSlot(SPIx, u32Slot)                           \
   WRITE_REG((SPIx)->SPIRSLOTEN, (u32Slot)) */




/******************************************************************************
 * @brief      Get SPI Rx active slot
 *
 * @param[in]  SPIx   : Select the SPI module
 * @param[in]  u32Slot: Time slot defined by PSP_SlotEnum
 *                      ORed of the following values are valid:
 *                        - \ref PSP_SLOT_ALL
 *                        - \ref PSP_SLOT_0
 *                        - \ref PSP_SLOT_1
 *                        - \ref PSP_SLOT_2
 *                        - \ref PSP_SLOT_3
 *                        - \ref PSP_SLOT_4
 *                        - \ref PSP_SLOT_5
 *                        - \ref PSP_SLOT_6
 *                        - \ref PSP_SLOT_7
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
/* #define SPI_IsEnablePSPNetFrameRxActiveSlot(SPIx, u32Slot)                         \
   ((SPIx)->SPIRSLOTEN & (u32Slot)) */




/******************************************************************************
 * @brief      Enable/Disable SPI slave clock free running
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 * @note       Only used for slave Mode
 *             Must be set for SPI slave mode
 *
 ******************************************************************************/
#define SPI_EnableSlaveClockFreeRun(SPIx)                                       \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_SLVCKRUN_Msk)

#define SPI_DisableSlaveClockFreeRun(SPIx)                                      \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_SLVCKRUN_Msk)




/******************************************************************************
 * @brief      Set/Get status of SPI slave clock free running
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 * @note       Only used for slave Mode
 *             Must be set for SPI slave mode
 *
 ******************************************************************************/
#define SPI_SetSlaveClockFreeRun(SPIx, eEnable)                                 \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_SLVCKRUN_Msk, SPICTL0_SLVCKRUN_Pos,(eEnable))

#define SPI_IsEnbleSlaveClockFreeRun(SPIx)                                      \
    ((SPIx)->SPICTL0 & SPICTL0_SLVCKRUN_Msk)




/******************************************************************************
 * @brief      Set/Get SFRM polarity for PSP/PSP_NET mode
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  eLevel:  Defined by LEVEL
 *                      Only the following values are valid:
 *                        - \ref LOW
 *                        - \ref HIGH
 *
 * @return     None
 * @return     Defined by LEVEL
 *
 * @note       Only worked for PSP/PSP_NET mode
 *
 ******************************************************************************/
#define SPI_SetPSPSFRMPolarity(SPIx, eLevel)                                    \
    WRITE_FIELD((SPIx)->SPIPSP, SPIPSP_SFRMPOL_Msk, SPIPSP_SFRMPOL_Pos, (eLevel) )

#define SPI_GetPSPSFRMPolarity(SPIx)                                            \
    READ_FIELD((SPIx)->SPIPSP, SPIPSP_SFRMPOL_Msk, SPIPSP_SFRMPOL_Pos )




/******************************************************************************
 * @brief      Enable/Disable invert SPI SFRM signal
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_EnableSFRMInvert(SPIx)                                              \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_SFRMINV_Msk)

#define SPI_DisableSFRMInvert(SPIx)                                             \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_SFRMINV_Msk)




/******************************************************************************
 * @brief      Set/Get status of SPI SFRM signal invert
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_SetSFRMInvert(SPIx, eEnable)                                        \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_SFRMINV_Msk, SPICTL0_SFRMINV_Pos,(eEnable))

#define SPI_IsEnableSFRMInvert(SPIx)                                            \
    ((SPIx)->SPICTL0 & SPICTL0_SFRMINV_Msk)




/******************************************************************************
 * @brief      Enable/Disable TXD tri-state output
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_EnableTriOutput(SPIx)                                               \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_TRIEN_Msk)

#define SPI_DisableTriOutput(SPIx)                                              \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_TRIEN_Msk)




/******************************************************************************
 * @brief      Set/Get status of TXD tri-state output
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_SetTriOutput(SPIx, eEnable)                                         \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_TRIEN_Msk, SPICTL0_TRIEN_Pos,(eEnable))

#define SPI_IsEnableTriOutput(SPIx)                                             \
    ((SPIx)->SPICTL0 & SPICTL0_TRIEN_Msk)




/******************************************************************************
 * @brief      Set/Get TXD tri-state output phase mode
 *
 * @param[in]  SPIx     :  Select the SPI module
 * @param[in]  eTriPhase:  Tri-state phase defined by SPI_TriOutEnum
 *                         Following values are valid:
 *                           - \ref SPI_TRIOUT_ON_MIDDLE_LSB
 *                           - \ref SPI_TRIOUT_ON_END_LSB
 *
 * @return     None
 * @return     Tri-state phase defined by SPI_TriOutEnum
 *
 * @note       must be SPI_TRIOUT_ON_MIDDLE_LSB for SPI/MWIRE format
 *
 ******************************************************************************/
#define SPI_SetTriPhase(SPIx, eTriPhase)                                        \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_TRIPHS_Msk, SPICTL0_TRIPHS_Pos,(eTriPhase))

#define SPI_GetTriPhase(SPIx)                                                   \
    READ_FIELD((SPIx)->SPICTL0, SPICTL0_TRIPHS_Msk, SPICTL0_TRIPHS_Pos)




/******************************************************************************
 * @brief      Set/Get data size
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Size:  Data size
 *                      Valid range: [1:32] bits
 *
 * @return     None
 * @return     Data size
 *             Valid range: [1:32] bits
 *
 ******************************************************************************/
#define SPI_SetDataSize(SPIx, u8Size)                                           \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_SIZE_Msk, SPICTL0_SIZE_Pos,((u8Size) - 1))

#define SPI_GetDataSize(SPIx)                                                   \
    ( 1U + READ_FIELD((SPIx)->SPICTL0, SPICTL0_SIZE_Msk, SPICTL0_SIZE_Pos) )




/******************************************************************************
 * @brief      Send one data
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  u32Data:  The data to be sent
 *
 * @return     None
 *
 * @note       write 32bits, but valid bits are decided by pre-defined data size.
 *             invalid bits are ignored by hardware.
 *
 ******************************************************************************/
#define SPI_SendData(SPIx, u32Data)                                             \
    WRITE_REG((SPIx)->SPIDATA, (u32Data))




/******************************************************************************
 * @brief      Receive one data
 *
 * @param[in]  SPIx   :  Select the SPI module
 *
 * @return     Unsigned data
 *
 * @note       read back valid bits are decided by pre-defined data size.
 *             Other bits are filled with 0.
 *
 ******************************************************************************/
#define SPI_ReceiveData(SPIx)                                                   \
    READ_REG((SPIx)->SPIDATA)




/******************************************************************************
 * @brief      Enable receive only for slave mode
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 * @note       Only used for slave mode
 *
 ******************************************************************************/
#define SPI_EnableSlaveReceiveOnly(SPIx)                                        \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_RXONLY_Msk)

#define SPI_DisableSlaveReceiveOnly(SPIx)                                       \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_RXONLY_Msk)




/******************************************************************************
 * @brief      Set/Get status of receive only
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 * @note       Only used for PSP slave mode
 *
 ******************************************************************************/
#define SPI_SetSlaveReceiveOnly(SPIx, eEnable)                                  \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_RXONLY_Msk, SPICTL0_RXONLY_Pos,(eEnable))

#define SPI_IsEnableSlaveReceiveOnly(SPIx)                                      \
    ((SPIx)->SPICTL0 & SPICTL0_RXONLY_Msk)




/******************************************************************************
 * @brief      Enable,disable FIFO pack mode
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_EnableFIFOPack(SPIx)                                                \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_FPACK_Msk)

#define SPI_DisableFIFOPack(SPIx)                                               \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_FPACK_Msk)




/******************************************************************************
 * @brief      Set/Get status of FIFO pack mode
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_SetFIFOPack(SPIx, eEnable)                                          \
    WRITE_FIELD( (SPIx)->SPICTL0, SPICTL0_FPACK_Msk, SPICTL0_FPACK_Pos,(eEnable))

#define SPI_IsEnableFIFOPack(SPIx)                                              \
    ((SPIx)->SPICTL0 & SPICTL0_FPACK_Msk)




/******************************************************************************
 * @brief      Set/Get Tx FIFO threshold
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Ths :  Trigger threshold
 *                      Valid range: [0:15]
 *
 * @return     None
 * @return     Trigger threshold
 *             Valid range: [0:15]
 *
 * @note       Trigger request when TXLVL <= TXTHS.
 *
 ******************************************************************************/
#define SPI_SetTxFIFOThreshold(SPIx, u8Ths)           WRITE_REG((SPIx)->SPITFTH, (u8Ths))
#define SPI_GetTxFIFOThreshold(SPIx)                  READ_REG((SPIx)->SPITFTH)




/******************************************************************************
 * @brief      Set/Get Rx FIFO threshold
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u8Ths :  Trigger threshold
 *                      Valid range: [0:15]
 *
 * @return     None
 * @return     Trigger threshold
 *             Valid range: [0:15]
 *
 *
 * @note       Trigger request when RXLVL > RXTHS.
 *
 ******************************************************************************/
#define SPI_SetRxFIFOThreshold(SPIx, u8Ths)           WRITE_REG((SPIx)->SPIRFTH, (u8Ths))
#define SPI_GetRxFIFOThreshold(SPIx)                  READ_REG((SPIx)->SPIRFTH)




/******************************************************************************
 * @brief      Get Transmit FIFO Level
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     Number of valid data entries in TxFIFO
 *
 ******************************************************************************/
#define SPI_GetTxFIFOLevel(SPIx)                                                \
    READ_FIELD((SPIx)->SPITFLVL, SPITFLVL_VAL_Msk, SPITFLVL_VAL_Pos)




/******************************************************************************
 * @brief      Get Receive FIFO Level
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     Number of valid data entries in RXFIFO
 *
 ******************************************************************************/
#define SPI_GetRxFIFOLevel(SPIx)                                                \
    READ_FIELD((SPIx)->SPIRFLVL, SPIRFLVL_VAL_Msk, SPIRFLVL_VAL_Pos)




/******************************************************************************
 * @brief      Enable/Disable Rx DMA
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_EnableRxDMA(SPIx)                                                   \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_DMARXREQ_Msk)

#define SPI_DisableRxDMA(SPIx)                                                  \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_DMARXREQ_Msk)




/******************************************************************************
 * @brief      Set/Get status of Rx DMA
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_SetRxDMA(SPIx, eEnable)                                             \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_DMARXREQ_Msk, SPICTL0_DMARXREQ_Pos,(eEnable))

#define SPI_IsEnableRxDMA(SPIx)                                                 \
    ((SPIx)->SPICTL0 & SPICTL0_DMARXREQ_Msk)




/******************************************************************************
 * @brief      Enable/Disable Tx DMA
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_EnableTxDMA(SPIx)                                                   \
    SET_BITS((SPIx)->SPICTL0, SPICTL0_DMATXREQ_Msk)

#define SPI_DisableTxDMA(SPIx)                                                  \
    CLEAR_BITS((SPIx)->SPICTL0, SPICTL0_DMATXREQ_Msk)




/******************************************************************************
 * @brief      Set/Get status of Tx DMA
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_SetTxDMA(SPIx, eEnable)                                             \
    WRITE_FIELD((SPIx)->SPICTL0, SPICTL0_DMATXREQ_Msk, SPICTL0_DMATXREQ_Pos,(eEnable))

#define SPI_IsEnableTxDMA(SPIx)                                                 \
    ((SPIx)->SPICTL0 & SPICTL0_DMATXREQ_Msk)




/******************************************************************************
 * @brief      Get SPI status
 *
 * @param[in]  SPIx    :  Select the SPI module
 * @param[in]  u32Query:  The status defined by SPI_StatusEnum
 *                        ORed of the following values are valid:
 *                          - \ref SPI_STS_ALL
 *                          - \ref SPI_STS_SFRM_LOCKED
 *                          - \ref SPI_STS_NET_BUSY
 *                          - \ref SPI_STS_RX_EVEN_SAMPLE
 *                          - \ref SPI_STS_TX_EVEN_SAMPLE
 *                          - \ref SPI_STS_SLAVE_NOT_READY
 *                          - \ref SPI_STS_BUSY
 *                          - \ref SPI_STS_RX_NOT_EMPTY
 *                          - \ref SPI_STS_RX_FULL
 *                          - \ref SPI_STS_TX_EMPTY
 *                          - \ref SPI_STS_TX_NOT_FULL
 *
 * @return     0     - None of the queried statuses occurred;
 *             not 0 - Corresponding statuses for non-zero bit occurred.
 *
 ******************************************************************************/
#define SPI_GetStatus(SPIx, u32Query)             ((SPIx)->SPISTS & (u32Query))




/******************************************************************************
 * @brief      Current active time slot
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_GetActiveSlot(SPIx)                                                 \
    READ_FIELD((SPIx)->SPISTS, SPISTS_ACTSLOT_Msk, SPISTS_ACTSLOT_Pos)




/******************************************************************************
 * @brief      Get raw event flag
 *
 * @param[in]  SPIx    :  Select the SPI module
 * @param[in]  u32Query:  Interrupt defined by SPI_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref SPI_INT_ALL
 *                          - \ref SPI_INT_DMA_EOC
 *                          - \ref SPI_INT_TRAIL_BYTE
 *                          - \ref SPI_INT_BIT_CNT_ERROR
 *                          - \ref SPI_INT_TX_REQ
 *                          - \ref SPI_INT_TX_OVERFLOW
 *                          - \ref SPI_INT_TX_UNDERFLOW
 *                          - \ref SPI_INT_RX_TIMEOUT
 *                          - \ref SPI_INT_RX_REQ
 *                          - \ref SPI_INT_RX_OVERFLOW
 *                          - \ref SPI_INT_RX_UNDERFLOW
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 * @note       u32Query : Can be ORed by SPI_IntEnum
 *
 ******************************************************************************/
#define SPI_GetIntRawFlag(SPIx, u32Query)   ((SPIx)->SPIRAWIF & (u32Query))




/******************************************************************************
 * @brief      Get interrupt flag
 *
 * @param[in]  SPIx    :  Select the SPI module
 * @param[in]  u32Query:  Interrupt defined by SPI_IntEnum
 *                        ORed of the following values are valid:
 *                          - \ref SPI_INT_ALL
 *                          - \ref SPI_INT_GLOBAL
 *                          - \ref SPI_INT_DMA_EOC
 *                          - \ref SPI_INT_TRAIL_BYTE
 *                          - \ref SPI_INT_BIT_CNT_ERROR
 *                          - \ref SPI_INT_TX_REQ
 *                          - \ref SPI_INT_TX_OVERFLOW
 *                          - \ref SPI_INT_TX_UNDERFLOW
 *                          - \ref SPI_INT_RX_TIMEOUT
 *                          - \ref SPI_INT_RX_REQ
 *                          - \ref SPI_INT_RX_OVERFLOW
 *                          - \ref SPI_INT_RX_UNDERFLOW
 *
 * @return     0     - None of the queried interrupts  occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define SPI_GetIntFlag(SPIx, u32Query)      ((SPIx)->SPIIF & (u32Query))




/******************************************************************************
 * @brief      Enable/Disable/Get status of SPI interrupts
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u32Int:  Interrupt defined by SPI_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref SPI_INT_ALL
 *                        - \ref SPI_INT_DMA_EOC
 *                        - \ref SPI_INT_TRAIL_BYTE
 *                        - \ref SPI_INT_BIT_CNT_ERROR
 *                        - \ref SPI_INT_TX_REQ
 *                        - \ref SPI_INT_TX_OVERFLOW
 *                        - \ref SPI_INT_TX_UNDERFLOW
 *                        - \ref SPI_INT_RX_TIMEOUT
 *                        - \ref SPI_INT_RX_REQ
 *                        - \ref SPI_INT_RX_OVERFLOW
 *                        - \ref SPI_INT_RX_UNDERFLOW
 *
 * @return     None
 * @return     0     - None of the queried interrupts is enabled;
 *             not 0 - Corresponding interrupts for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_EnableInt(SPIx, u32Int)         SET_BITS((SPIx)->SPIIE, (u32Int))
#define SPI_DisableInt(SPIx, u32Int)        CLEAR_BITS((SPIx)->SPIIE, (u32Int))
#define SPI_IsEnableInt(SPIx, u32Int)       ((SPIx)->SPIIE & (u32Int))




/******************************************************************************
 * @brief      Clear interrupts
 *
 * @param[in]  SPIx  :  Select the SPI module
 * @param[in]  u32Int:  Interrupt defined by SPI_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref SPI_INT_ALL
 *                        - \ref SPI_INT_DMA_EOC
 *                        - \ref SPI_INT_TRAIL_BYTE
 *                        - \ref SPI_INT_BIT_CNT_ERROR
 *                        - \ref SPI_INT_TX_REQ
 *                        - \ref SPI_INT_TX_OVERFLOW
 *                        - \ref SPI_INT_TX_UNDERFLOW
 *                        - \ref SPI_INT_RX_TIMEOUT
 *                        - \ref SPI_INT_RX_REQ
 *                        - \ref SPI_INT_RX_OVERFLOW
 *                        - \ref SPI_INT_RX_UNDERFLOW
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_ClearInt(SPIx, u32Int)          WRITE_REG((SPIx)->SPIIC, (u32Int))




/******************************************************************************
 * @brief      Set/Get timeout count value
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  u32Data:  Timeout count value
 *                       Valid range: [0:0xFFFFFF]
 *
 * @return     None
 * @return     Timeout count value
 *
 * @note       The timeout timer is reset after a new data sample is received
 *             into the RXFIFO.
 *             it must be cleared by SPI_ClearInt(SPIx, SPI_INT_RX_TIMEOUT).
 *
 *             step1: receive at least one frame, timeout counter start count;
 *             step2: then no more data received until timeout occurred.
 *             step3: new data received, timeout counter reload.
 *             step4: if timeout occurred and no more data received, clear timeout
 *             interrupt flag, then will no more timeout interrupt flag.
 *             repeat step1/2 can get new timeout event
 *
 *             if SPITO == 0 , no timeout function enabled
 *             SPITO * CLK_SPI
 *
 ******************************************************************************/
#define SPI_SetTimeout(SPIx, u32Data)                   WRITE_REG((SPIx)->SPITO, (u32Data))
#define SPI_GetTimeout(SPIx)                            READ_REG((SPIx)->SPITO)




/******************************************************************************
 * @brief      Enable/Disable loopback mode
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 * @note       Set this function before enable SPI module,
 *             Else will be not work even if this filed is enabled
 *
 ******************************************************************************/
#define SPI_EnableLoopback(SPIx)                                                \
    SET_BITS((SPIx)->SPITCTL, SPITCTL_LOOP_Msk)

#define SPI_DisableLoopback(SPIx)                                               \
    CLEAR_BITS((SPIx)->SPITCTL, SPITCTL_LOOP_Msk)




/******************************************************************************
 * @brief      Set/Get status of loopback mode
 *
 * @param[in]  SPIx   :  Select the SPI module
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                         - \ref ENABLE
 *                         - \ref DISABLE
 *
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SPI_SetLoopback(SPIx, eEnable)                                          \
    WRITE_FIELD((SPIx)->SPITCTL, SPITCTL_LOOP_Msk, SPITCTL_LOOP_Pos, (eEnable) )

#define SPI_IsEnableLoopback(SPIx)                                              \
    ((SPIx)->SPITCTL & SPITCTL_LOOP_Msk)




/******************************************************************************
 * @brief      Enable/Disable/Get status of lock SFRM output
 *
 * @param[in]  SPIx   :  Select the SPI module
 *
 * @return     None
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 * @note       only valid for SPI master, and need set
 *             SPI_EnableTestSFRMLock(SPIx) first.
 *
 *             After enable SFRM lock function, SFRM will be always active after
 *             first frame send out, until release SFRM lock status.
 *
 ******************************************************************************/
#define SPI_EnableSFRMLock(SPIx)                                          \
    SET_BITS((SPIx)->SPICTL1, SPICTL1_SFRMLCK_Msk)

#define SPI_DisableSFRMLock(SPIx)                                         \
    CLEAR_BITS((SPIx)->SPICTL1, SPICTL1_SFRMLCK_Msk)

#define SPI_IsEnableSFRMLock(SPIx)                                        \
    ((SPIx)->SPICTL1 & SPICTL1_SFRMLCK_Msk)




/******************************************************************************
 * @brief      Enable/Disable/Get status of test lock SFRM output
 *
 * @param[in]  SPIx   :  Select the SPI module
 *
 * @return     None
 * @return     None
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 * @note       only valid for SPI master
 *
 ******************************************************************************/
#define SPI_EnableTestSFRMLock(SPIx)                                          \
    SET_BITS((SPIx)->SPITCTL, (0x1U << 6))

#define SPI_DisableTestSFRMLock(SPIx)                                         \
    CLEAR_BITS((SPIx)->SPITCTL, (0x1U << 6))

#define SPI_IsEnableTestSFRMLock(SPIx)                                        \
    ((SPIx)->SPITCTL & (0x1U << 6))




/******************************************************************************
 * @brief      Enable/Disable write access to the protected SPI registers
 *
 * @param[in]  SPIx:  Select the SPI module
 *
 * @return     None
 *
 ******************************************************************************/
#define SPI_WALLOW(SPIx)                    ((SPIx)->SPIREGKEY = 0x1ACCE551U)
#define SPI_WDIS(SPIx)                      ((SPIx)->SPIREGKEY = 0x0U)




/**
 *  @brief  SPI Public Function Declaration
 */
ErrorStatus SPI_InitSpeed(SPI_REGS *SPIx, uint32_t u32BaudRate);
void SPI_InitIO(SPI_REGS *SPIx);

void SPI_Init(SPI_REGS *SPIx, SPI_ModeEnum eMode, SPI_SPIModeEnum eSPIMode, uint8_t u8DataSize, uint32_t u32Baudrate);
void SPI_InitEasy(SPI_REGS *SPIx, SPI_ModeEnum eMode, uint8_t u8DataSize, uint32_t u32Baudrate);

void SPI_ExitNetMode(SPI_REGS *SPIx);

void SPI_FullDuplexTransceive(SPI_REGS *SPIx, uint32_t *pu32WriteBuffer, uint32_t *pu32ReadBuffer, uint32_t u32Size);
void SPI_HalfDuplexTx(SPI_REGS *SPIx, uint32_t *pu32WriteBuffer, uint32_t u32Size);
void SPI_HalfDuplexRx(SPI_REGS *SPIx, uint32_t *pu32ReadBuffer, uint32_t u32Size);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SPI_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

