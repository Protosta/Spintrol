/******************************************************************************
 * @file     target.h
 * @brief    Hardware operation header file.
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2025 Spintrol Electronic Technology (Shanghai) Co., Ltd.
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
#ifndef TARGET_H
#define TARGET_H

#ifdef __cplusplus
extern "C" {
#endif




#include <stdint.h>
#include <string.h>
#include "spc1169.h"
#include "pin.h"
#include "clock.h"
#include "uart.h"
#include "flashc.h"
#include "crc.h"
#include "hwlib.h"
#include "wdt.h"
#include "system.h"
#include "epwr.h"




#define CONFIG_UART            (UART1)
#define CONFIG_UART_CLOCK      (UART1_MODULE)
#define CONFIG_IAP_UART_BPS    (38400)
#define CONFIG_LIN             (UART1)
#define CONFIG_LIN_CLOCK       (UART1_MODULE)
#define CONFIG_LIN_RECEIVE_ID  (0x31U)           /* Reference receive ID    */
#define CONFIG_LIN_SEND_ID     (0x32U)           /* Reference send ID       */
#define CONFIG_LIN_IDMASK      (0x3FU)           /* IDMASK State       */
#define CONFIG_IAP_LIN_BPS     (50000)

#define TATGET_ENTRY_LOCATION_ADDR     (0x1000F000)
#define TARGET_ASSERT_STARTADDR_IN_MAIN_C_FLASH(u32start,u32size)      \
    ((u32start >= 0x10000000) && ((u32start + u32size - 1U) <= 0x1001FFFF))
#define TARGET_MemCpy(pDest, pSrc, u32Size)     memcpy(pDest, pSrc, u32Size)
#define TARGET_MemSet(pStr, i32Value, u32Size)  memset(pStr, i32Value, u32Size)
#define TARGET_MemCmp(pStr1, pStr2, u32Size)    memcmp(pStr1, pStr2, u32Size)


#define TARGET_SET_UART_PIN()           do{PIN_SetChannel(PIN_GPIO6, PIN_CH2);PIN_SetChannel(PIN_GPIO7, PIN_CH2);}while(0)
#define TARGET_RESTORE_UART_PIN()       WRITE_REG(PINMUX->GPIO6    ,0x05000100);WRITE_REG(PINMUX->GPIO7    ,0x05000100);

#define TARGET_SET_LIN_PIN()            do{PIN_SetChannel(PIN_GPIO25, PIN_CH1);PIN_SetChannel(PIN_GPIO26, PIN_CH1);}while(0)
#define TARGET_RESTORE_LIN_PIN()        WRITE_REG(PINMUX->GPIO25    ,0x0F000100);WRITE_REG(PINMUX->GPIO26    ,0x0F000100);

#define TARGET_LIN_DATA_WIDTH                          (8U)
#define TARGET_UART_DATA_WIDTH                         (1U)

#define ISP_RECORD_1_4BIT_NUM    	      (0U)
#define ISP_RECORD_2_4BIT_NUM    	      (1U)
#define IAP_BOOT_FLASH_4BIT_NUM         (2U)
#define IAP_FLOW_4BIT_1_NUM             (3U)
#define IAP_FLOW_4BIT_2_NUM             (4U)
#define IAP_FLOW_4BIT_3_NUM             (5U)
#define BOOT_FLOW_4BIT_NUM              (6U)
#define CODE_VERIFY_4BIT_NUM            (7U)

#define RECORD_FLASH_WRITE_ERROR_1         (0x01)
#define RECORD_FLASH_WRITE_ERROR_2         (0x02)
#define RECORD_FLASH_ERASECHIP_ERROR_1     (0x03)
#define RECORD_FLASH_ERASECHIP_ERROR_2     (0x04)
#define RECORD_FLASH_ERASESECTOR_ERROR_1   (0x05)
#define RECORD_FLASH_ERASESECTOR_ERROR_2   (0x06)
#define RECORD_FLASH_ERASESECTOR_ERROR_3   (0x07)

BOOL TARGET_IsUartRxFifoEmpty(UART_REGS* pstUart);
BOOL TARGET_IsUartTxFifoEmpty(void);
ErrorStatus TARGET_UartReceive(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout);
ErrorStatus TARGET_UartSend(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout);
void TARGET_UartSendDone(UART_REGS* pstUart);
void TARGET_RestoreUart(void); 
void TARGET_RestoreLin(void); 
BOOL TARGET_IsLINIdMatch(void);
ErrorStatus TARGET_LinSend(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout);
ErrorStatus TARGET_LinReceive(uint8_t au8Buf[], uint32_t u32Count, uint32_t u32timeout);

uint32_t BufferToUint32_LE(const uint8_t p_p8Input[]);
uint16_t BufferToUint16_LE(const uint8_t p_p8Input[]);
void TARGET_CalculateCRC16(uint32_t u32Startaddr,uint32_t u32Size,uint32_t* p32Crc);
BOOL TARGET_GetJumpFunAddr(uint32_t u32StartAddr , uint32_t *p32Entry);

BOOL TARGET_IsEnableUARTIAP(void);
BOOL TARGET_IsEnableLINIAP(void);
void TARGET_RecordErrorInfo(uint8_t u8Bit4Num, uint8_t u8ByteValue);
void TARGET_DisableWDT(void);



#ifdef __cplusplus
}
#endif

#endif /* !TARGET_H */

