/******************************************************************************
* @file     iap.h
* @brief    Image header file.
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
#ifndef IAP_H
#define IAP_H


#ifdef __cplusplus
extern "C" {
#endif

#include "comdef.h"
#include "target.h"
#include <stdint.h>
#include "spd1179_hv.h"

/**
 *  @brief  Define for sector flag
 */

#define IAP_CORE_CLK                       (100000000U)

/*!< Makesure this coefficient' value is reasonable or not,one loop 64 clock(base on -o0 optimisition, run in flash ) */
#define IAP_DELAY_WEIGHTS                   (64U)
#define IAP_ONCE_SWAP_SIZE (128U)  /* Must be divisible by 8 */

#define IAP_CMD_TIME_OUT_MILLISECOND      ((IAP_CORE_CLK/1000U)/IAP_DELAY_WEIGHTS)


#define IAP_DOWNLOAD_EACHSN_TIMEOUT_MS    (5000U*IAP_CMD_TIME_OUT_MILLISECOND)


#define IAP_SEND_TIMEOUT_MS               (1000U *IAP_CMD_TIME_OUT_MILLISECOND)
#define IAP_DATA_STORM_OVWEFLOW_BYTE      (600U)


#define MODECHECK_UART_TIME_WAIT_MS            (20U)     /*FIXME */
#define MODECHECK_LIN_TIME_WAIT_MS             (20U)     /*FIXME */

/* If IAP_INTERFACE is 
 *  LIN, set the macro as 1
 *  UART, set the macro as 0  
 */
#define IAP_INTERFACE                           (1U)

#define MODECHECK_UART_IAP_HANDSHAKE          (0x5AU)

#define IAP_CMD_FIRST_HANDSHAKE        (0x5AU)
#define IAP_CMD_SECOND_HANDSHAKE       (0xA5U)
#define IAP_CMD_WRITE_DATA             (0xA1U)
#define IAP_CMD_ERASE_DATA             (0xA3U)
#define IAP_CMD_UPDATE_KEY             (0x91U)
#define IAP_CMD_LOADROOT_KEY           (0x95U)
#define IAP_CMD_SECURE_RESET           (0x99U)
#define IAP_IS_AVAILD_CMD(u8Cmd)    ((u8Cmd == IAP_CMD_WRITE_DATA)   ||   \
                                     (u8Cmd == IAP_CMD_UPDATE_KEY)   ||   \
                                     (u8Cmd == IAP_CMD_LOADROOT_KEY) ||   \
                                     (u8Cmd == IAP_CMD_SECURE_RESET) ||   \
                                     (u8Cmd == IAP_CMD_ERASE_DATA))


#define IAP_ERROR_FIRST_HANDSHAKE_TIMEOUT  (0x01U)
#define IAP_ERROR_SECOND_HANDSHAKE_TIMEOUT (0x02U)
#define IAP_ERROR_HANDSHAKE_STATUS         (0x03U)
#define IAP_ERROR_HANDSHAKE_PACKNUM        (0x04U)
#define IAP_ERROR_WRITE_DATA_TIMEOUT       (0x05U)
#define IAP_ERROR_CMD_1                    (0x06U)
#define IAP_ERROR_CMD_2                    (0x07U)
#define IAP_ERROR_CMD_3                    (0x08U)
#define IAP_ERROR_PACK_SN_1                (0x09U)
#define IAP_ERROR_PACK_SN_2                (0x0AU)
#define IAP_ERROR_PACK_SN_3                (0x0BU)
#define IAP_ERROR_WRITE_FLASH              (0x0CU)
#define IAP_ERROR_ERASE_FLASH              (0x0DU)
#define IAP_ERROR_SECOND_HANDSHAKE_CMD     (0x0EU)
#define IAP_ERROR_MAX_LEN                  (0x0FU)
#define IAP_ERROR_DATA_CRC          	     (0x10U)
#define IAP_ERROR_ADDR_VAILD               (0x11U)
#define IAP_ERROR_ERROR_LEN                (0x12U)
#define IAP_ERROR_WRITE_AGLIN              (0x13U)

#define IAP_CMD_BUFFER_SIZE                (512U)

#define IAP_PACK_CRC_LEN                   (2U)
#define IAP_PACK_LEN_OFFSET                (0U)
#define IAP_PACK_CMD_OFFSET                (2U)
#define IAP_PACK_DATA_ALL_OFFSET           (3U)


/*!< use for handshark cmd*/
#define IAP_PACKNUM_OFFSET_FROM_DATA_ALL         (0U)
#define IAP_PACKSN_OFFSET_FROM_DATA_ALL          (0U)
#define IAP_PACKSN_SIZE                          (2U)
/*!< use for write cmd */
#define IAP_WRITECMD_ADDR_OFFSET_FROM_DATA_ALL   (IAP_PACKNUM_OFFSET_FROM_DATA_ALL+IAP_PACKSN_SIZE)
#define IAP_WRITECMD_ADDR_SIZE                   (4U)
#define IAP_WRITECMD_DATA_OFFSET_FROM_DATA_ALL   (IAP_WRITECMD_ADDR_OFFSET_FROM_DATA_ALL+IAP_WRITECMD_ADDR_SIZE)

#define IAP_FIRST_SN                       (1U)
#define IAP_FLASHBUFFER_SIZE       		     (1024U)
#define IAP_ENV_BUFFER_SIZE                (2U)




typedef ErrorStatus(*IapSend)(const uint8_t au8Buf[], uint32_t u32Count, uint32_t timeout);
typedef ErrorStatus(*IapReceive)(const uint8_t au8Buf[], uint32_t u32Count, uint32_t timeout);

typedef enum
{
    IAP_BY_UART = 0x55,
    IAP_BY_LIN  = 0xAA,
    IAP_BY_NONE = 0xFF
}IAP_ComTypeEnum;

typedef enum
{
    IAP_UART_WAIT_AOUTBAUD     = 0x51,
    IAP_UART_AUTOBAND_CONFIRM  = 0x52,
}IAP_UART_AUTOBAUD_STEP;

typedef struct
{
    ErrorStatus(*IapSend)(uint8_t au8Buf[], uint32_t u32Count, uint32_t timeout);
    ErrorStatus(*IapReceive)(uint8_t au8Buf[], uint32_t u32Count, uint32_t timeout);
    IAP_ComTypeEnum eComType;
}IAP_ComInterfaceDef;


typedef enum
{
    IAP_STATUS_WAIT_FIRST_HANDSHAKE = 0x31,
    IAP_STATUS_WAIT_SECOND_HANDSHAKE= 0x33,
    IAP_STATUS_HANDSHAKE_SUCCESS    = 0x35,
    IAP_STATUS_TRANSFER_DATA        = 0x37,
    IAP_STATUS_TRANSFER_COMPLETE    = 0x39,
    IAP_STATUS_SECURE_CMD_ERROR     = 0x3F
}IAP_Status_enum;


typedef enum
{
    REPORT_ACK_HANDSHAKE           = 0x17,
    REPORT_ACK                     = 0x65,
    REPORT_NACK                    = 0x9A,
    REPORT_NACK_SECURE             = 0x5A,
}IAP_Report_enum;



/**
 *  @brief  Function declaration
 */
int32_t IAP_Entry(void);




#ifdef __cplusplus
}
#endif

#endif /* !IAP_H */
