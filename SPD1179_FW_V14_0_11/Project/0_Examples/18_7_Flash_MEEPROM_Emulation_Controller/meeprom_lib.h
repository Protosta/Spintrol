/******************************************************************************
 * @file     meeprom_lib.h
 * @brief    MEEPROM library header file.
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

#ifndef MEEPROM_LIB_H
#define MEEPROM_LIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"


#if defined ( __ICCARM__ )
    #define         _RAM_FUNC_       __ramfunc
#else
    #define         _RAM_FUNC_       __attribute__ ((section("RAMCODE")))
#endif


#define FLASH_BASE_ADDR_MAIN      (0x10000000U)   /*!< Flash main memory base address         */
#define FLASH_BASE_ADDR_RDN0      (0x11002000U)   /*!< Flash Redundant sector 0 base address  */
#define FLASH_BASE_ADDR_RDN1      (0x11003000U)   /*!< Flash Redundant sector 1 base address  */

/* Default entry address register value */
#define MEEPROM_DEFAULT_ENTRY_ADDR          ((uint32_t)0x0U)




/**
 *  @brief  Define the pages for EEPROM emulation
 */
#define MEEPROM_PAGE_0                      ((uint32_t)0x00U)                 /* Page 0     */
#define MEEPROM_PAGE_1                      ((uint32_t)0x01U)                 /* Page 1     */
#define MEEPROM_PAGE_NONE                   ((uint32_t)0xFFFF)




/**
 *  @brief  EEPROM page header definitions
 */
#define MEEPROM_PAGE_HEADER_ERASED          ((uint64_t)0xFFFFFFFFFFFFFFFFU)   /* State saved in page header */
#define MEEPROM_PAGE_HEADER_VALID           ((uint64_t)0x1ACCE5511ACCE551U)   /* State saved in page header */




/**
 *  @brief  EEPROM page state definitions
 */
#define MEEPROM_PAGE_STATE_VALID            ((uint32_t)0x1U)                  /* Page contains valid data              */
#define MEEPROM_PAGE_STATE_INVALID          ((uint32_t)0x2U)                  /* Page invliad state: receive or erased */




/**
 *  @brief  Description of the 8 Bytes (64 bits) element in flash
 */
/* Bit:  0                  31  32        47  48         63  */
/*       <--- Data Value ---->  <-Vir Addr->  <- Parity  ->  */
#define MEEPROM_HEADER_SIZE                 (8U)                              /*!< Size of page header in Bytes */
#define MEEPROM_ELEMENT_SIZE                (8U)                              /*!< Size of element in Bytes     */




/**
 *  @brief  Get EEPROM variable value
 */
#define GET_MEEPROM_DATA(u32Addr)           (*(__IO uint32_t*)(u32Addr))




/**
 *  @brief EEPROM Public Function Declaration
 */
_RAM_FUNC_ uint32_t MEEPROM_Init(MEEPROM_CB* psCB);
_RAM_FUNC_ uint32_t MEEPROM_Format(MEEPROM_CB* psCB);
_RAM_FUNC_ uint32_t MEEPROM_WriteWord(MEEPROM_CB* psCB, uint32_t u32Addr, uint32_t u32Data);
_RAM_FUNC_ uint32_t MEEPROM_ReadWord(MEEPROM_CB* psCB, uint32_t u32Addr, uint32_t *pu32Data);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* MEEPROM_LIB_H */


/******************* (C) COPYRIGHT 2022 SPINTROL ************* END OF FILE ****/

