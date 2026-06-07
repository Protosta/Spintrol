/******************************************************************************
 * @file     crc.h
 * @brief    CRC module header file.
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

#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"


/**
 *  @brief  CRC interrupt type definition
 */
typedef enum
{
    CRC_INT_OPERATION_DONE      = (1U << 0),        /*!< Masked CRC calculation done interrupt       */
    CRC_INT_STREAM_OVERFLOW     = (1U << 1),        /*!< Masked CRC stream overflow interrupt        */
    CRC_INT_GLOBAL              = (1U << 2),        /*!< Global CRC interrupt flag issued to CPU     */
    CRC_INT_ALL                 = (0x7U),           /*!< Used for all interrupts                     */
} CRC_IntEnum;




/**
 *  @brief  CRC mode type definition
 */
typedef enum
{
    CRC_MODE_8_AUTOSAR_2F       = 0,        /*!< CRC-8-AUTOSAR_2F   */
    CRC_MODE_16_CCITT           = 2,        /*!< CRC-16-CCITT       */
    CRC_MODE_16_IBM             = 3,        /*!< CRC-16-IBM         */
    CRC_MODE_16_T10_DIF         = 4,        /*!< CRC-16-T10-DIF     */
    CRC_MODE_16_DNP             = 5,        /*!< CRC-16-DNP         */
    CRC_MODE_32_IEEE802P3       = 7,        /*!< CRC-32-IEEE802_3   */
} CRC_ModeEnum;




/**
 *  @brief  CRC input and output data reverse operation type definition
 */
typedef enum
{
    CRC_DATA_REVERSE           = 0,        /*!< For input data, the byte sequence remains unchanged
                                                only bit sequence in each byte is reversed.
                                                For output data, the entire data is reversed by bit */
    CRC_DATA_NOT_REVERSE       = 1,        /*!< Sequence remains unchanged                          */
} CRC_DataReverseEnum;




/**
 *  @brief  CRC output data xor operation type definition
 */
typedef enum
{
    CRC_OUTPUTDATA_XOR_ALL_0          = 0,        /*!< Output data xor all 0       */
    CRC_OUTPUTDATA_XOR_ALL_1          = 1,        /*!< Output data xor all 1       */
} CRC_OutputDataXorEnum;




/**
 *  @brief  The data format for each write to the CRCSTRIN register
 */
typedef enum
{
    CRC_FEED_PER_WORD           = 0,        /*!< CRCSTRIN is written per word (4 bytes) */
    CRC_FEED_PER_BYTE           = 1,        /*!< CRCSTRIN is written per byte           */
} CRC_FeedFormatEnum;




/******************************************************************************
 * @brief      Enable/Disable CRC calculate
 *
 * @param[in]  CRCx :  Select the CRC module
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_Enable(CRCx)                                                       \
    WRITE_FIELD((CRCx)->CRCCTL, CRCCTL_EN_Msk, CRCCTL_EN_Pos, 0x1)

#define CRC_Disable(CRCx)                                                      \
    WRITE_FIELD((CRCx)->CRCCTL, CRCCTL_EN_Msk, CRCCTL_EN_Pos, 0x0)




/******************************************************************************
 * @brief      Set CRC mode
 *
 * @param[in]  CRCx  :  Select the CRC module
 * @param[in]  eMode :  CRC mode defined by CRC_ModeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_SetMode(CRCx, eMode)                                               \
    WRITE_FIELD((CRCx)->CRCCTL, CRCCTL_MODE_Msk, CRCCTL_MODE_Pos, (eMode))




/******************************************************************************
 * @brief      Enable/Disable CRC Continuous Frame
 *
 * @param[in]  CRCx :  Select the CRC module
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_EnableContinuousFrame(CRCx)                                        \
    WRITE_FIELD((CRCx)->CRCCTL, CRCCTL_CONTINUOUS_Msk, CRCCTL_CONTINUOUS_Pos, 0x1)

#define CRC_DisableContinuousFrame(CRCx)                                       \
    WRITE_FIELD((CRCx)->CRCCTL, CRCCTL_CONTINUOUS_Msk, CRCCTL_CONTINUOUS_Pos, 0x0)




/******************************************************************************
 * @brief      Reverse CRC Data
 *
 * @param[in]  CRCx        :  Select the CRC module
 * @param[in]  eReverse    :  Reverse CRC Data
 *                            Please refer to CRC_DataReverseEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_ReverseData(CRCx, eReverse)                                        \
    MODIFY_REG((CRCx)->CRCCTL,                                                 \
               (CRCCTL_ENDIANIN_Msk | CRCCTL_ENDIANOUT_Msk),                   \
               ((eReverse) << CRCCTL_ENDIANIN_Pos) | ((eReverse) << CRCCTL_ENDIANOUT_Pos))




/******************************************************************************
 * @brief      Xor CRC Output Data
 *
 * @param[in]  CRCx        :  Select the CRC module
 * @param[in]  eXor        :  Xor CRC output Data
 *                            Please refer to CRC_OutputDataXorEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_XorOutputData(CRCx, eXor)                                          \
    MODIFY_REG((CRCx)->CRCCTL, (CRCCTL_INVOUT_Msk),                            \
               ((eXor) << CRCCTL_INVOUT_Pos))




/******************************************************************************
 * @brief      Set CRC Feed data format
 *
 * @param[in]  CRCx        :  Select the CRC module
 * @param[in]  eFeedFormat :  Data format for each write
 *                            Please refer to CRC_FeedFormatEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_SetFeedFormat(CRCx, eFeedFormat)                                      \
    WRITE_FIELD((CRCx)->CRCCTL, CRCCTL_PERBYTE_Msk, CRCCTL_PERBYTE_Pos, (eFeedFormat))




/******************************************************************************
 * @brief      Set CRC stream data length
 *
 * @param[in]  CRCx      :  Select the CRC module
 * @param[in]  u32StrLen :  Stream data length in byte
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_SetStreamLen(CRCx,u32StrLen)            ((CRCx)->CRCSTRLEN = ((u32StrLen) - 1U))




/******************************************************************************
 * @brief      Feed data into CRC stream
 *
 * @param[in]  CRCx    :  Select the CRC module
 * @param[in]  u32Data :  Input data
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_FeedData(CRCx,u32Data)                  ((CRCx)->CRCSTRIN = (u32Data))




/******************************************************************************
 * @brief      Get CRC result
 *
 * @param[in]  CRCx :  Select the CRC module
 *
 * @return     CRC calculation result
 *
 ******************************************************************************/
#define CRC_GetResult(CRCx)                         ((CRCx)->CRCRESULT)




/******************************************************************************
 * @brief      Enable/Disable CRC interrupt
 *
 * @param[in]  CRCx   :  Select the CRC module
 * @param[in]  eEvent :  Select the CRC event
 *                       Please refer to CRC_IntEnum
 * @return     None
 *
 ******************************************************************************/
#define CRC_EnableInt(CRCx,eEvent)                  SET_BITS((CRCx)->CRCIE, eEvent)
#define CRC_DisableInt(CRCx,eEvent)                 CLEAR_BITS((CRCx)->CRCIE, eEvent)




/******************************************************************************
 * @brief      Clear CRC interrupt flag
 *
 * @param[in]  CRCx   :  Select the CRC module
 * @param[in]  eEvent :  Select the CRC event
 *                       Please refer to CRC_IntEnum
 * @return     None
 *
 ******************************************************************************/
#define CRC_ClearInt(CRCx,eEvent)                   ((CRCx)->CRCIC = (eEvent))




/******************************************************************************
 * @brief      Get CRC interrupt flag
 *
 * @param[in]  CRCx   :  Select the CRC module
 * @param[in]  eEvent :  Select the CRC event
 *                       Please refer to CRC_IntEnum
 * @return     0     - Interrupt did not occur
 *             not 0 - Interrupt occurred
 *
 ******************************************************************************/
#define CRC_GetIntFlag(CRCx,eEvent)                 ((CRCx)->CRCIF & (eEvent))




/******************************************************************************
 * @brief      Get CRC event raw flag
 *
 * @param[in]  CRCx   :  Select the CRC module
 * @param[in]  eEvent :  Select the CRC event
 *                       Please refer to CRC_IntEnum
 * @return     0     - Event did not occur
 *             not 0 - Event occurred
 *
 ******************************************************************************/
#define CRC_GetIntRawFlag(CRCx,eEvent)              ((CRCx)->CRCRAWIF & (eEvent))




/******************************************************************************
 * @brief      Enable/Disable write access to the protected CRC registers
 *
 * @param[in]  CRCx :  Select the CRC module
 *
 * @return     None
 *
 ******************************************************************************/
#define CRC_WALLOW(CRCx)                            ((CRCx)->CRCREGKEY = 0x1ACCE551)
#define CRC_WDIS(CRCx)                              ((CRCx)->CRCREGKEY = 0x0)




/**
 *  @brief  CRC Public Function Declaration
 */
void CRC_Init(CRC_REGS *CRCx, CRC_ModeEnum eMode);
uint32_t CRC_CalculateWithInitValueIsNotZero(CRC_REGS *CRCx, const uint8_t *pu8DataStr, uint32_t u32DataLen, uint32_t u32FrameHead);
uint32_t CRC_CalculateWithInitValueIsZero(CRC_REGS *CRCx, const uint8_t *pu8DataStr, uint32_t u32DataLen);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* CRC_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

