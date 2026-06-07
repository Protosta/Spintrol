/******************************************************************************
 * @file     dma.h
 * @brief    DMA driver header file.
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


#ifndef DMA_H
#define DMA_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief DMA channel definition
 */
typedef enum
{
    DMA_CH_ALL            = (0xFFU),         /*!< DMA all channels */
    DMA_CH0               = (1U << 0),       /*!< DMA channel 0    */
    DMA_CH1               = (1U << 1),       /*!< DMA channel 1    */
    DMA_CH2               = (1U << 2),       /*!< DMA channel 2    */
    DMA_CH3               = (1U << 3),       /*!< DMA channel 3    */
    DMA_CH4               = (1U << 4),       /*!< DMA channel 4    */
    DMA_CH5               = (1U << 5),       /*!< DMA channel 5    */
    DMA_CH6               = (1U << 6),       /*!< DMA channel 6    */
    DMA_CH7               = (1U << 7),       /*!< DMA channel 7    */
} DMA_ChannelEnum;




/**
 *  @brief DMA global interrupt definition
 */
typedef enum
{
    DMA_INT_ALL               = ((1U << 0) | (1U << 4)),
    DMA_INT_TRANSFER_COMPLETE = (1U << 0),       /*!<     */
    DMA_INT_TRANSFER_ERROR    = (1U << 4),       /*!<     */
} DMA_GlobalIntEnum;




/**
 *  @brief DMA transfer type definition
 */
typedef enum
{
    DMA_MEMORY_TO_MEMORY            = 0,      /*!< Memory to Memory         */
    DMA_MEMORY_TO_PERIPHERAL        = 1,      /*!< Memory to Peripheral     */
    DMA_PERIPHERAL_TO_MEMORY        = 2,      /*!< Peripheral to Memory     */
    DMA_PERIPHERAL_TO_PERIPHERAL    = 3,      /*!< Peripheral to Peripheral */
} DMA_TransferTypeEnum;




/**
 *  @brief DMA transfer width definition
 */
typedef enum
{
    DMA_TRANSFER_IN_BYTE            = 0,      /*!< Byte      (8-bit)        */
    DMA_TRANSFER_IN_HALF_WORD       = 1,      /*!< Half-word (16-bit)       */
    DMA_TRANSFER_IN_WORD            = 2,      /*!< Word      (32-bit)       */
} DMA_TransferWidthEnum;




/**
 *  @brief DMA burst transaction length definition
 */
typedef enum
{
    DMA_BURST_LENGTH_1_WORD         = 0,      /*!< 1 word (a word = 32 bit) */
    DMA_BURST_LENGTH_4_WORDS        = 1,      /*!< 4 words                  */
    DMA_BURST_LENGTH_8_WORDS        = 2,      /*!< 8 words                  */
    DMA_BURST_LENGTH_16_WORDS       = 3,      /*!< 16 words                 */
    DMA_BURST_LENGTH_32_WORDS       = 4,      /*!< 32 words                 */
} DMA_BurstTransferLenEnum;




/**
 *  @brief DMA address mode definition
 */
typedef enum
{
    DMA_ADDRESS_MODE_INCREASE       = 0,      /*!< Address increment   */
    DMA_ADDRESS_MODE_DECREASE       = 1,      /*!< Address decrement   */
    DMA_ADDRESS_NO_CHANGE           = 2,      /*!< Address no-change   */
} DMA_AddressModeEnum;




/**
 *  @brief DMA channel priority definition
 */
typedef enum
{
    DMA_PRIORITY_8                  = 0,      /*!< Channel priority, lowest priority */
    DMA_PRIORITY_7                  = 1,      /*!< Channel priority    */
    DMA_PRIORITY_6                  = 2,      /*!< Channel priority    */
    DMA_PRIORITY_5                  = 3,      /*!< Channel priority    */
    DMA_PRIORITY_4                  = 4,      /*!< Channel priority    */
    DMA_PRIORITY_3                  = 5,      /*!< Channel priority    */
    DMA_PRIORITY_2                  = 6,      /*!< Channel priority    */
    DMA_PRIORITY_1                  = 7,      /*!< Channel priority    */
} DMA_PriorityEnum;




/**
 *  @brief DMA FIFO threshold definition
 */
typedef enum
{
    DMA_FIFO_SINGLE_ENTRY           = 0,      /*!< Whenever data or space is available */
    DMA_FIFO_HALF_DEPTH             = 1,      /*!< 1/2 FIFO depth                      */
} DMA_FIFOThresholdEnum;




/**
 *  @brief DMA handshaking type definition
 */
typedef enum
{
    DMA_HANDSHAKE_BY_HARDWARE       = 0,      /*!< Hardware handshaking */
    DMA_HANDSHAKE_BY_SOFTWARE       = 1,      /*!< Software handshaking */
} DMA_HandshakeTypeEnum;




/**
 *  @brief DMA handshaking polarity definition
 */
typedef enum
{
    DMA_HANDSHAKE_POL_ACTIVE_HIGH   = 0,      /*!< Handshaking interface polarity = Active High */
    DMA_HANDSHAKE_POL_ACTIVE_LOW    = 1,      /*!< Handshaking interface polarity = Active Low  */
} DMA_HandshakePolEnum;




/**
 *  @brief DMA source peripheral definition
 */
typedef enum
{
    DMA_SPER_UART0_RX     = 0,        /*!< UART0_RX   */
    DMA_DPER_UART0_TX     = 1,        /*!< UART0_TX   */

    DMA_SPER_UART1_RX     = 2,        /*!< UART1_RX   */
    DMA_DPER_UART1_TX     = 3,        /*!< UART1_TX   */

    DMA_SPER_SPI0_RX      = 4,        /*!< SPI0_RX    */
    DMA_DPER_SPI0_TX      = 5,        /*!< SPI0_TX    */

    DMA_SPER_SPI1_RX      = 6,        /*!< SPI1_RX    */
    DMA_DPER_SPI1_TX      = 7,        /*!< SPI1_TX    */

    DMA_SPER_ADCRESULT0   = 8,        /*!< ADCRESULT0 */
    DMA_SPER_ADCRESULT1   = 9,        /*!< ADCRESULT1 */
    DMA_SPER_ADCRESULT2   = 10,       /*!< ADCRESULT2 */
    DMA_SPER_ADCRESULT3   = 11,       /*!< ADCRESULT3 */
    DMA_SPER_ADCRESULT4   = 12,       /*!< ADCRESULT4 */
    DMA_SPER_ADCRESULT5   = 13,       /*!< ADCRESULT5 */
    DMA_SPER_ADCRESULT6   = 14,       /*!< ADCRESULT6 */
    DMA_SPER_ADCRESULT7   = 15,       /*!< ADCRESULT7 */
} DMA_PeripheralEnum;




/******************************************************************************
 * @brief      Set DMA channel source address
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  u32Addr:  Source address
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSourceAddr(DMACHx, u32Addr)      ((DMACHx)->DMACHSA = (u32Addr))




/******************************************************************************
 * @brief      Get DMA channel source address
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Current source address of the channel
 *
 ******************************************************************************/
#define DMA_GetSourceAddr(DMACHx)               ((DMACHx)->DMACHSA)




/******************************************************************************
 * @brief      Set DMA channel destination address
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  u32Addr:  Destination address
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetDestinationAddr(DMACHx, u32Addr) ((DMACHx)->DMACHDA = (u32Addr))




/******************************************************************************
 * @brief      Get DMA channel destination address
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Current destination address of the channel
 *
 ******************************************************************************/
#define DMA_GetDestinationAddr(DMACHx)          ((DMACHx)->DMACHDA)




/******************************************************************************
 * @brief      Set DMA transfer type
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eType :  DMA transfer type defined by DMA_TransferTypeEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_MEMORY_TO_MEMORY
 *                        - \ref DMA_MEMORY_TO_PERIPHERAL
 *                        - \ref DMA_PERIPHERAL_TO_MEMORY
 *                        - \ref DMA_PERIPHERAL_TO_PERIPHERAL
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetTransferType(DMACHx, eType)                                      \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_TT_Msk, DMACHCTL0_TT_Pos,          \
                (eType)                                                                     \
               )




/******************************************************************************
 * @brief      Get DMA transfer type
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     DMA transfer type defined by DMA_TransferTypeEnum
 *
 ******************************************************************************/
#define DMA_GetTransferType(DMACHx)                                             \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_TT_Msk, DMACHCTL0_TT_Pos)




/******************************************************************************
 * @brief      Set source-end transfer width
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eWidth:  Transfer width defined by DMA_TransferWidthEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_TRANSFER_IN_BYTE
 *                        - \ref DMA_TRANSFER_IN_HALF_WORD
 *                        - \ref DMA_TRANSFER_IN_WORD
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSourceTransferWidth(DMACHx, eWidth)                              \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_SWIDTH_Msk, DMACHCTL0_SWIDTH_Pos,  \
                (eWidth)                                                                    \
               )




/******************************************************************************
 * @brief      Get source-end transfer width
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Transfer width defined by DMA_TransferWidthEnum
 *
 ******************************************************************************/
#define DMA_GetSourceTransferWidth(DMACHx)                                      \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_SWIDTH_Msk, DMACHCTL0_SWIDTH_Pos)

#define DMA_GetSourceTransferWidthInByte(DMACHx)                                \
    (1U << DMA_GetSourceTransferWidth((DMACHx)))




/******************************************************************************
 * @brief      Set destination-end transfer width
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eWidth:  Transfer width defined by DMA_TransferWidthEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_TRANSFER_IN_BYTE
 *                        - \ref DMA_TRANSFER_IN_HALF_WORD
 *                        - \ref DMA_TRANSFER_IN_WORD
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetDestinationTransferWidth(DMACHx, eWidth)                         \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_DWIDTH_Msk, DMACHCTL0_DWIDTH_Pos,  \
                (eWidth)                                                                    \
               )




/******************************************************************************
 * @brief      Get destination-end transfer width
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Transfer width defined by DMA_TransferWidthEnum
 *
 ******************************************************************************/
#define DMA_GetDestinationTransferWidth(DMACHx)                                 \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_DWIDTH_Msk, DMACHCTL0_DWIDTH_Pos)

#define DMA_GetDestinationTransferWidthInByte(DMACHx)                           \
    (1U << DMA_GetDestinationTransferWidth((DMACHx)))




/******************************************************************************
 * @brief      Set source-end burst transaction length
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eLen  :  Number of data items to be read from the source every time
 *                      when a source burst transaction request is made.
 *                      Defined by DMA_BurstTransferLenEnum.
 *                      Only the following values are valid:
 *                        - \ref DMA_BURST_LENGTH_1_WORD
 *                        - \ref DMA_BURST_LENGTH_4_WORDS
 *                        - \ref DMA_BURST_LENGTH_8_WORDS
 *                        - \ref DMA_BURST_LENGTH_16_WORDS
 *                        - \ref DMA_BURST_LENGTH_32_WORDS
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSourceBurstLen(DMACHx, eLen)                                     \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_SSIZE_Msk, DMACHCTL0_SSIZE_Pos,    \
                (eLen)                                                                      \
               )




/******************************************************************************
 * @brief      Set source-end burst transaction length
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Number of data items to be read from the source every time
 *             when a source burst transaction request is made.
 *             Defined by DMA_BurstTransferLenEnum.
 *
 ******************************************************************************/
#define DMA_GetSourceBurstLen(DMACHx)                                           \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_SSIZE_Msk, DMACHCTL0_SSIZE_Pos)

#define DMA_GetSourceBurstLenInWord(DMACHx)                                     \
    ( ( DMA_GetSourceBurstLen(DMACHx) == 0 ) ? 1 :                                \
      ( 1U << ( 1 + DMA_GetSourceBurstLen(DMACHx) ) )                           \
    )




/******************************************************************************
 * @brief      Set destination-end burst transaction length
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eLen  :  Number of data items to be read from the source every time
 *                      when a source burst transaction request is made.
 *                      Defined by DMA_BurstTransferLenEnum.
 *                      Only the following values are valid:
 *                        - \ref DMA_BURST_LENGTH_1_WORD
 *                        - \ref DMA_BURST_LENGTH_4_WORDS
 *                        - \ref DMA_BURST_LENGTH_8_WORDS
 *                        - \ref DMA_BURST_LENGTH_16_WORDS
 *                        - \ref DMA_BURST_LENGTH_32_WORDS
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetDestinationBurstLen(DMACHx, eLen)                                \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_DSIZE_Msk, DMACHCTL0_DSIZE_Pos,    \
                (eLen)                                                                      \
               )




/******************************************************************************
 * @brief      Set destination-end burst transaction length
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Number of data items to be read from the source every time
 *             when a source burst transaction request is made.
 *             Defined by DMA_BurstTransferLenEnum.
 *
 ******************************************************************************/
#define DMA_GetDestinationBurstLen(DMACHx)                                      \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_DSIZE_Msk, DMACHCTL0_DSIZE_Pos)

#define DMA_GetDestinationBurstLenInWord(DMACHx)                                \
    ( ( DMA_GetDestinationBurstLen(DMACHx) == 0 ) ? 1 :                           \
      ( 1U << ( 1 + DMA_GetDestinationBurstLen(DMACHx) ) )                      \
    )




/******************************************************************************
 * @brief      Set source-end address mode
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eMode :  Address mode defined by DMA_AddressModeEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_ADDRESS_MODE_INCREASE
 *                        - \ref DMA_ADDRESS_MODE_DECREASE
 *                        - \ref DMA_ADDRESS_NO_CHANGE
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSourceAddrMode(DMACHx, eMode)                                    \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_SINC_Msk, DMACHCTL0_SINC_Pos,      \
                (eMode)                                                                     \
               )




/******************************************************************************
 * @brief      Get source-end address mode
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Address mode defined by DMA_AddressModeEnum
 *
 ******************************************************************************/
#define DMA_GetSourceAddrMode(DMACHx)                                           \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_SINC_Msk, DMACHCTL0_SINC_Pos)




/******************************************************************************
 * @brief      Set destination-end address mode
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eMode :  Address mode defined by DMA_AddressModeEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_ADDRESS_MODE_INCREASE
 *                        - \ref DMA_ADDRESS_MODE_DECREASE
 *                        - \ref DMA_ADDRESS_NO_CHANGE
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetDestinationAddrMode(DMACHx, eMode)                               \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_DINC_Msk, DMACHCTL0_DINC_Pos,      \
                (eMode)                                                                     \
               )




/******************************************************************************
 * @brief      Get destination-end address mode
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Address mode defined by DMA_AddressModeEnum
 *
 ******************************************************************************/
#define DMA_GetDestinationAddrMode(DMACHx)                                      \
    READ_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_DINC_Msk, DMACHCTL0_DINC_Pos)




/******************************************************************************
 * @brief      Enable DMA channel interrupt
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_EnableChannelInt(DMACHx)                                            \
    SET_BITS((DMACHx)->DMACHCTL0, DMACHCTL0_IE_Msk)




/******************************************************************************
 * @brief      Disable DMA channel interrupt
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_DisableChannelInt(DMACHx)                                           \
    CLEAR_BITS((DMACHx)->DMACHCTL0, DMACHCTL0_IE_Msk)




/******************************************************************************
 * @brief      Set DMA channel interrupt
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                        - \ref ENABLE
 *                        - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetChannelInt(DMACHx, eEnable)                                      \
    WRITE_FIELD((DMACHx)->DMACHCTL0, DMACHCTL0_IE_Msk, DMACHCTL0_IE_Pos,          \
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Is Enable DMA channel interrupt
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Defined by FunctionalState
 *
 ******************************************************************************/
#define DMA_IsEnableChannelInt(DMACHx)                                          \
    READ_BITS((DMACHx)->DMACHCTL0, DMACHCTL0_IE_Msk)




/******************************************************************************
 * @brief      Set DMA channel block transfer size
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  u16Size:  Block transfer size
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetBlockTransferSize(DMACHx, u16Size)                               \
    WRITE_FIELD((DMACHx)->DMACHCTL1, DMACHCTL1_BLKTS_Msk, DMACHCTL1_BLKTS_Pos,    \
                (u16Size)                                                                   \
               )




/******************************************************************************
 * @brief      Get DMA channel block transfer size
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Block transfer size
 *
 ******************************************************************************/
#define DMA_GetBlockTransferSize(DMACHx)                                        \
    READ_FIELD((DMACHx)->DMACHCTL1, DMACHCTL1_BLKTS_Msk, DMACHCTL1_BLKTS_Pos)




/******************************************************************************
 * @brief      Set source-end handshaking interface
 *
 * @param[in]  DMACHx: Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eType : Handshaking type defined by DMA_HandshakeTypeEnum
 *                     Only the following values are valid:
 *                       - \ref DMA_HANDSHAKE_BY_HARDWARE
 *                       - \ref DMA_HANDSHAKE_BY_SOFTWARE
 * @param[in]  ePol  : Handshaking interface polarity defined by DMA_HandshakePolEnum
 *                     Only the following values are valid:
 *                       - \ref DMA_HANDSHAKE_POL_ACTIVE_HIGH
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSourceHandShake(DMACHx, eType, ePol)                             \
    MODIFY_REG((DMACHx)->DMACHCFG0, DMACHCFG0_SSWHS_Msk|DMACHCFG0_SHSPOL_Msk,     \
               ((eType) << DMACHCFG0_SSWHS_Pos) | ((ePol) << DMACHCFG0_SHSPOL_Pos)         \
              )




/******************************************************************************
 * @brief      Get source-end handshaking type
 *
 * @param[in]  DMACHx: Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Handshaking type defined by DMA_HandshakeTypeEnum
 *
 ******************************************************************************/
#define DMA_GetSourceHandShakeType(DMACHx)                                      \
    READ_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_SSWHS_Msk, DMACHCFG0_SSWHS_Pos)




/******************************************************************************
 * @brief      Get source-end handshaking polarity
 *
 * @param[in]  DMACHx: Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Handshaking interface polarity defined by DMA_HandshakePolEnum
 *
 ******************************************************************************/
#define DMA_GetSourceHandShakePolarity(DMACHx)                                  \
    READ_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_SHSPOL_Msk, DMACHCFG0_SHSPOL_Pos)




/******************************************************************************
 * @brief      Set destination-end handshaking interface
 *
 * @param[in]  DMACHx: Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eType : Handshaking type defined by DMA_HandshakeTypeEnum
 *                     Only the following values are valid:
 *                       - \ref DMA_HANDSHAKE_BY_HARDWARE
 *                       - \ref DMA_HANDSHAKE_BY_SOFTWARE
 * @param[in]  ePol  : Handshaking interface polarity defined by DMA_HandshakePolEnum
 *                     Only the following values are valid:
 *                       - \ref DMA_HANDSHAKE_POL_ACTIVE_HIGH
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetDestinationHandShake(DMACHx, eType, ePol)                        \
    MODIFY_REG((DMACHx)->DMACHCFG0, DMACHCFG0_DSWHS_Msk|DMACHCFG0_DHSPOL_Msk,     \
               ((eType) << DMACHCFG0_DSWHS_Pos) | ((ePol) << DMACHCFG0_DHSPOL_Pos)         \
              )




/******************************************************************************
 * @brief      Get destination-end handshaking type
 *
 * @param[in]  DMACHx: Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Handshaking type defined by DMA_HandshakeTypeEnum
 *
 ******************************************************************************/
#define DMA_GetDestinationHandShakeType(DMACHx)                                 \
    READ_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_DSWHS_Msk, DMACHCFG0_DSWHS_Pos)




/******************************************************************************
 * @brief      Get destination-end handshaking polarity
 *
 * @param[in]  DMACHx: Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Handshaking interface polarity defined by DMA_HandshakePolEnum
 *
 ******************************************************************************/
#define DMA_GetDestinationHandShakePolarity(DMACHx)                             \
    READ_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_DHSPOL_Msk, DMACHCFG0_DHSPOL_Pos)




/******************************************************************************
 * @brief      Get the channel FIFO state (empty or not)
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return      0 - FIFO not empty
 *              1 - FIFO empty
 *
 ******************************************************************************/
#define DMA_IsFIFOEmpty(DMACHx)                                                 \
    READ_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_FIFOEMPTY_Msk,                      \
               DMACHCFG0_FIFOEMPTY_Pos                                                     \
              )




/******************************************************************************
 * @brief      Enable DMA channel Suspend
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_EnableSuspend(DMACHx)                                               \
    SET_BITS((DMACHx)->DMACHCFG0, DMACHCFG0_SUSPEND_Msk)




/******************************************************************************
 * @brief      Disable DMA channel suspend
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_DisableSuspend(DMACHx)                                              \
    CLEAR_BITS((DMACHx)->DMACHCFG0, DMACHCFG0_SUSPEND_Msk)




/******************************************************************************
 * @brief      Set DMA channel suspend
 *
 * @param[in]  DMACHx :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eEnable:  Defined by FunctionalState
 *                       Only the following values are valid:
 *                        - \ref ENABLE
 *                        - \ref DISABLE
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSuspend(DMACHx, eEnable)                                         \
    WRITE_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_SUSPEND_Msk, DMACHCFG0_SUSPEND_Pos,\
                (eEnable)                                                                   \
               )




/******************************************************************************
 * @brief      Is Enable DMA channel suspend
 *
 * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     0     - Not Enable DMA channel suspend;
 *             not 0 - Is Enable DMA channel suspend.
 *
 ******************************************************************************/
#define DMA_IsEnableSuspend(DMACHx)                                             \
    READ_BITS((DMACHx)->DMACHCFG0, DMACHCFG0_SUSPEND_Msk)




/******************************************************************************
 * @brief      Set DMA channel priority
 *
 * @param[in]  DMACHx    :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  u8Priority:  Channel priority defined by DMA_PriorityEnum
 *                          Only the following values are valid:
 *                            - \ref DMA_PRIORITY_8
 *                            - \ref DMA_PRIORITY_7
 *                            - \ref DMA_PRIORITY_6
 *                            - \ref DMA_PRIORITY_5
 *                            - \ref DMA_PRIORITY_4
 *                            - \ref DMA_PRIORITY_3
 *                            - \ref DMA_PRIORITY_2
 *                            - \ref DMA_PRIORITY_1
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetPriority(DMACHx, u8Priority)                                     \
    WRITE_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_PRIORITY_Msk,                      \
                DMACHCFG0_PRIORITY_Pos,                                                     \
                (u8Priority)                                                                \
               )




/******************************************************************************
 * @brief      Get DMA channel priority
 *
 * @param[in]  DMACHx    :  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Channel priority defined by DMA_PriorityEnum
 *
 ******************************************************************************/
#define DMA_GetPriority(DMACHx)                                                 \
    READ_FIELD((DMACHx)->DMACHCFG0, DMACHCFG0_PRIORITY_Msk,                       \
               DMACHCFG0_PRIORITY_Pos                                                      \
              )




/******************************************************************************
 * @brief      Set destination-end peripheral device
 *
 * @param[in]  DMACHx : Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  ePer   : Peripheral device defined by DMA_PeripheralEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_DPER_UART0_TX
 *                        - \ref DMA_DPER_UART1_TX
 *                        - \ref DMA_DPER_SPI0_TX
 *                        - \ref DMA_DPER_SPI1_TX
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetDestinationPeripheral(DMACHx, ePer)                              \
    WRITE_FIELD((DMACHx)->DMACHCFG1, DMACHCFG1_DPER_Msk, DMACHCFG1_DPER_Pos,      \
                (ePer)                                                                      \
               )




/******************************************************************************
 * @brief      Get destination-end peripheral device
 *
 * @param[in]  DMACHx : Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Peripheral device defined by DMA_PeripheralEnum
 *
 ******************************************************************************/
#define DMA_GetDestinationPeripheral(DMACHx)                                    \
    READ_FIELD((DMACHx)->DMACHCFG1, DMACHCFG1_DPER_Msk, DMACHCFG1_DPER_Pos)




/******************************************************************************
 * @brief      Set source-end peripheral device
 *
 * @param[in]  DMACHx : Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  ePer   : Peripheral device defined by DMA_PeripheralEnum
 *                      Only the following values are valid:
 *                        - \ref DMA_SPER_UART0_RX
 *                        - \ref DMA_SPER_UART1_RX
 *                        - \ref DMA_SPER_SPI0_RX
 *                        - \ref DMA_SPER_SPI1_RX
 *                        - \ref DMA_SPER_ADCRESULT0
 *                        - \ref DMA_SPER_ADCRESULT1
 *                        - \ref DMA_SPER_ADCRESULT2
 *                        - \ref DMA_SPER_ADCRESULT3
 *                        - \ref DMA_SPER_ADCRESULT4
 *                        - \ref DMA_SPER_ADCRESULT5
 *                        - \ref DMA_SPER_ADCRESULT6
 *                        - \ref DMA_SPER_ADCRESULT7
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetSourcePeripheral(DMACHx, ePer)                                   \
    WRITE_FIELD((DMACHx)->DMACHCFG1, DMACHCFG1_SPER_Msk, DMACHCFG1_SPER_Pos,      \
                (ePer)                                                                      \
               )




/******************************************************************************
 * @brief      Get source-end peripheral device
 *
 * @param[in]  DMACHx : Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     Peripheral device defined by DMA_PeripheralEnum
 *
 ******************************************************************************/
#define DMA_GetSourcePeripheral(DMACHx)                                         \
    READ_FIELD((DMACHx)->DMACHCFG1, DMACHCFG1_SPER_Msk, DMACHCFG1_SPER_Pos)




/******************************************************************************
 * @brief      Set FIFO mode for servicing a burst transaction
 *
 * @param[in]  DMACHx  :  Select the DMA channel (DMACH0 ~ DMACH7)
 * @param[in]  eFIFOLvl:  FIFO threshold defined by DMA_FIFOThresholdEnum
 *                        Only the following values are valid:
 *                          - \ref DMA_FIFO_SINGLE_ENTRY
 *                          - \ref DMA_FIFO_HALF_DEPTH
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_SetFIFOThreshold(DMACHx, eFIFOLvl)                                  \
    WRITE_FIELD((DMACHx)->DMACHCFG1, DMACHCFG1_FIFOTH_Msk, DMACHCFG1_FIFOTH_Pos,  \
                (eFIFOLvl)                                                                  \
               )




/******************************************************************************
 * @brief      Get FIFO mode for servicing a burst transaction
 *
 * @param[in]  DMACHx  :  Select the DMA channel (DMACH0 ~ DMACH7)
 *
 * @return     FIFO threshold defined by DMA_FIFOThresholdEnum
 *
 ******************************************************************************/
#define DMA_GetFIFOThreshold(DMACHx)                                            \
    READ_FIELD((DMACHx)->DMACHCFG1, DMACHCFG1_FIFOTH_Msk, DMACHCFG1_FIFOTH_Pos)




/******************************************************************************
 * @brief      Get transfer complete raw event flag
 *
 * @param[in]  u32Query:  Interrupt items defined by DMA_ChannelEnum
 *                        ORed of the following values are valid:
 *                          - \ref DMA_CH_ALL
 *                          - \ref DMA_CH0
 *                          - \ref DMA_CH1
 *                          - \ref DMA_CH2
 *                          - \ref DMA_CH3
 *                          - \ref DMA_CH4
 *                          - \ref DMA_CH5
 *                          - \ref DMA_CH6
 *                          - \ref DMA_CH7
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define DMA_GetTransferCompleteIntRawFlag(u32Query)                             \
    (DMAC->DMATCRAWIF & (u32Query))




/******************************************************************************
 * @brief      Get transfer complete interrupt flag
 *
 * @param[in]  u32Query:  Interrupt items defined by DMA_ChannelEnum
 *                        ORed of the following values are valid:
 *                          - \ref DMA_CH_ALL
 *                          - \ref DMA_CH0
 *                          - \ref DMA_CH1
 *                          - \ref DMA_CH2
 *                          - \ref DMA_CH3
 *                          - \ref DMA_CH4
 *                          - \ref DMA_CH5
 *                          - \ref DMA_CH6
 *                          - \ref DMA_CH7
 *
 * @return     0     - None of the queried interrupts occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define DMA_GetTransferCompleteIntFlag(u32Query)                             \
    (DMAC->DMATCIF & (u32Query))




/******************************************************************************
 * @brief      Enable channel transfer complete interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @example    DMA_EnableTransferCompleteInt(DMA_CH0);
 *             DMA_EnableTransferCompleteInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_EnableTransferCompleteInt(u32Int)                                   \
    WRITE_REG(DMAC->DMATCIE, (u32Int) | ((u32Int) << (DMATCIE_CH0WE_Pos)) )




/******************************************************************************
 * @brief      Disable channel transfer complete interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @example    DMA_DisableTransferCompleteInt(DMA_CH0);
 *             DMA_DisableTransferCompleteInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_DisableTransferCompleteInt(u32Int)                                  \
    WRITE_REG(DMAC->DMATCIE, ((u32Int) << (DMATCIE_CH0WE_Pos)) )




/******************************************************************************
 * @brief      Get channel transfer complete interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     0     - None of the queried interrupts is enabled;
 *             not 0 - Corresponding interrupts for non-zero bit is enabled.
 *
 * @example    DMA_IsEnableTransferCompleteInt(DMA_CH0);
 *             DMA_IsEnableTransferCompleteInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_IsEnableTransferCompleteInt(u32Int)           (DMAC->DMATCIE & (u32Int))




/******************************************************************************
 * @brief      Clear channel transfer complete interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @example    DMA_ClearTransferCompleteInt(DMA_CH0);
 *             DMA_ClearTransferCompleteInt(DMA_CH0 | DMA_CH1);
 *
 ******************************************************************************/
#define DMA_ClearTransferCompleteInt(eDMACH)         (DMAC->DMATCIC = (eDMACH))




/******************************************************************************
 * @brief      Get transfer error raw event flag
 *
 * @param[in]  u32Query:  Interrupt items defined by DMA_ChannelEnum
 *                        ORed of the following values are valid:
 *                          - \ref DMA_CH_ALL
 *                          - \ref DMA_CH0
 *                          - \ref DMA_CH1
 *                          - \ref DMA_CH2
 *                          - \ref DMA_CH3
 *                          - \ref DMA_CH4
 *                          - \ref DMA_CH5
 *                          - \ref DMA_CH6
 *                          - \ref DMA_CH7
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define DMA_GetTransferErrorIntRawFlag(u32Query)                                \
    (DMAC->DMAERRRAWIF & (u32Query))




/******************************************************************************
 * @brief      Get transfer error interrupt flag
 *
 * @param[in]  u32Query:  Interrupt items defined by DMA_ChannelEnum
 *                        ORed of the following values are valid:
 *                          - \ref DMA_CH_ALL
 *                          - \ref DMA_CH0
 *                          - \ref DMA_CH1
 *                          - \ref DMA_CH2
 *                          - \ref DMA_CH3
 *                          - \ref DMA_CH4
 *                          - \ref DMA_CH5
 *                          - \ref DMA_CH6
 *                          - \ref DMA_CH7
 *
 * @return     0     - None of the queried interrupts occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define DMA_GetTransferErrorIntFlag(u32Query)                                   \
    (DMAC->DMAERRIF & (u32Query))




/******************************************************************************
 * @brief      Enable channel transfer error interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @example    DMA_EnableErrorInt(DMA_CH0);
 *             DMA_EnableErrorInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_EnableTransferErrorInt(u32Int)                                      \
    WRITE_REG(DMAC->DMAERRIE, (u32Int) | ((u32Int) << (DMAERRIE_CH0WE_Pos)) )




/******************************************************************************
 * @brief      Disable channel transfer error interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @example    DMA_DisableErrorInt(DMA_CH0);
 *             DMA_DisableErrorInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_DisableTransferErrorInt(u32Int)                                     \
    WRITE_REG(DMAC->DMAERRIE, ((u32Int) << (DMAERRIE_CH0WE_Pos)) )




/******************************************************************************
 * @brief      Get channel transfer error interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     0     - None of the queried interrupts is enabled;
 *             not 0 - Corresponding interrupts for non-zero bit is enabled.
 *
 * @example    DMA_IsEnableTransferErrorInt(DMA_CH0);
 *             DMA_IsEnableTransferErrorInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_IsEnableTransferErrorInt(u32Int)             (DMAC->DMAERRIE & (u32Int))




/******************************************************************************
 * @brief      Clear channel transfer error interrupt
 *
 * @param[in]  u32Int:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * #example    DMA_ClearErrorInt(DMA_CH0);
 *             DMA_ClearErrorInt(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_ClearTransferErrorInt(eDMACH)           (DMAC->DMAERRIC = (eDMACH))




/******************************************************************************
 * @brief      Get global interrupt flag, which combined by each channel
 *             interrupt flag
 *
 * @param[in]  u32Query:  Interrupt items defined by DMA_GlobalIntEnum
 *                        ORed of the following values are valid:
 *                          - \ref DMA_INT_ALL
 *                          - \ref DMA_INT_TRANSFER_COMPLETE
 *                          - \ref DMA_INT_TRANSFER_ERROR
 *
 * @return     0     - None of the queried interrupts occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define DMA_GetGlobalIntFlag(u32Query)              (DMAC->DMAIF & (u32Query))




/******************************************************************************
 * @brief      Enable DMA controller
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define DMA_Enable()                        (DMAC->DMAEN = DMAEN_EN_ENABLE)




/******************************************************************************
 * @brief      Disable DMA controller
 *
 * @param[in]  None
 *
 * @return     None
 *
 * @note       Hardware will clear the enable bit once all channel transfer
 *             is completed after excute DMA_Disable()
 *
 ******************************************************************************/
#define DMA_Disable()                       (DMAC->DMAEN = DMAEN_EN_DISABLE)




/******************************************************************************
 * @brief      Is DMA controller enabled
 *
 * @param[in]  None
 *
 * @return     0 - DMA controller is not disabled
 *             1 - DMA controller is enabled
 *
 ******************************************************************************/
#define DMA_IsEnable()                      (DMAC->DMAEN)




/******************************************************************************
 * @brief      Enable DMA channel transfer
 *
 * @param[in]  u32Chn:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @note       Hardware will clear the enable bits once transfer is completed
 *
 * @example    DMA_EnableChannelTransfer(DMA_CH0);
 *             DMA_EnableChannelTransfer(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_EnableChannelTransfer(u32Chn)                                       \
    WRITE_REG(DMAC->DMACHEN, (u32Chn) | ((u32Chn) << (DMACHEN_CH0WE_Pos)) )




/******************************************************************************
 * @brief      Disable DMA channel transfer
 *
 * @param[in]  u32Chn:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     None
 *
 * @example    DMA_DisableChannelTransfer(DMA_CH0);
 *             DMA_DisableChannelTransfer(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_DisableChannelTransfer(u32Chn)                                      \
    WRITE_REG(DMAC->DMACHEN, ((u32Chn) << (DMACHEN_CH0WE_Pos)) )




/******************************************************************************
 * @brief      Get channel transfer status
 *
 * @param[in]  u32Chn:  Interrupt items defined by DMA_ChannelEnum
 *                      ORed of the following values are valid:
 *                        - \ref DMA_CH_ALL
 *                        - \ref DMA_CH0
 *                        - \ref DMA_CH1
 *                        - \ref DMA_CH2
 *                        - \ref DMA_CH3
 *                        - \ref DMA_CH4
 *                        - \ref DMA_CH5
 *                        - \ref DMA_CH6
 *                        - \ref DMA_CH7
 *
 * @return     0     - None of the queried channels completed;
 *             not 0 - Corresponding channels for non-zero bit completed
 *
 * @example    DMA_IsEnableChannelTransfer(DMA_CH0);
 *             DMA_IsEnableChannelTransfer(DMA_CH1|DMA_CH2);
 *
 ******************************************************************************/
#define DMA_IsEnableChannelTransfer(u32Chn)               (DMAC->DMACHEN & (u32Chn))




/**
 *  @brief Power Public Function Declaration
 */
void DMA_SetHandShakeWithPeripheral(DMACH_REGS *DMACHx, DMA_PeripheralEnum ePeripheral);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* DMA_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
