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


#ifndef EEPROM_LIB_H
#define EEPROM_LIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"

#if defined ( __ICCARM__ )
    #define         _RAM_FUNC_       __ramfunc
#else
    #define         _RAM_FUNC_       __attribute__ ((section("RAMCODE")))
#endif



/**
 *  @brief  Structure type to access the EEPROM Controller (EEPROM).
 */
typedef struct
{
  __IO uint32_t         EEPROMENTRYADDR[256]  ;   /*!< Offset: 0x00000000 (RW  )  EEPROM Entry Address Register            */
  __IO uint32_t         EEPROMREGKEY          ;   /*!< Offset: 0x00000400 (RW  )  EEPROM Register Write-Allow Key Register */
  __IO uint32_t         EEPROMNEXTADDR        ;   /*!< Offset: 0x00000404 (RW  )  EEPROM Next Available Address Register   */
} EEPROM_REGS;




#define FLASH_BASE_ADDR_RDN0      (0x11002000U)   /*!< Flash Redundant sector 0 base address  */
#define FLASH_BASE_ADDR_RDN1      (0x11003000U)   /*!< Flash Redundant sector 1 base address  */
#define FLASH_BASE_ADDR_RDN2      (0x11004000U)   /*!< Flash Redundant sector 2 base address  */




/**
 *  @brief  EEPROM Peripheral Declaration
 */
#define EEPROM_BASE                     ((uint32_t)0x40000800U)             /*!< EEPROM Base Address                   */
#define EEPROM                          ((EEPROM_REGS *) EEPROM_BASE)       /*!< EEPROM Peripheral Declaration         */




/**
 *  @brief  Define the information of the pages to be used
 */
#define EEPROM_PAGE_SIZE                ((uint32_t)FLASH_SECTOR_SIZE)       /* Page size = 4KByte                      */
#define EEPROM_START_ADDR               ((uint32_t)FLASH_BASE_ADDR_RDN0)    /* EEPROM start address: from RND sector 0 */

/* EEPROM Page0 start and end address */
#define EEPROM_PAGE0_START_ADDR         ((uint32_t)(FLASH_BASE_ADDR_RDN0))
#define EEPROM_PAGE0_END_ADDR           ((uint32_t)(FLASH_BASE_ADDR_RDN0 + (EEPROM_PAGE_SIZE - 1U)))

/* EEPROM Page1 start and end address */
#define EEPROM_PAGE1_START_ADDR         ((uint32_t)(FLASH_BASE_ADDR_RDN1))
#define EEPROM_PAGE1_END_ADDR           ((uint32_t)(FLASH_BASE_ADDR_RDN1 + (EEPROM_PAGE_SIZE - 1U)))

/* EEPROM Page2 start and end address */
#define EEPROM_PAGE2_START_ADDR         ((uint32_t)(FLASH_BASE_ADDR_RDN2))
#define EEPROM_PAGE2_END_ADDR           ((uint32_t)(FLASH_BASE_ADDR_RDN2 + (EEPROM_PAGE_SIZE - 1U)))

/* Number of variables */
#define EEPROM_NUM_OF_VAR               (256U)

/* Default entry address register value */
#define EEPROM_DEFAULT_ENTRY_REG_VAL    ((uint32_t)0x11005FF0U)




/**
 *  @brief  Define the pages for EEPROM emulation
 */
#define EEPROM_PAGE_0                   ((uint32_t)0x00U)                 /* Page 0     */
#define EEPROM_PAGE_1                   ((uint32_t)0x01U)                 /* Page 1     */
#define EEPROM_PAGE_2                   ((uint32_t)0x02U)                 /* Page 2     */
#define EEPROM_PAGE_NONE                ((uint32_t)0xFFFF)




/**
 *  @brief  EEPROM page header definitions
 */
#define EEPROM_PAGE_HEADER_ERASED       ((uint64_t)0xFFFFFFFFFFFFFFFFU)   /* State saved in page header */
#define EEPROM_PAGE_HEADER_VALID        ((uint64_t)0x1ACCE5511ACCE551U)   /* State saved in page header */




/**
 *  @brief  EEPROM page state definitions
 */
#define EEPROM_PAGE_STATE_VALID         ((uint32_t)0x1U)                  /* Page contains valid data              */
#define EEPROM_PAGE_STATE_INVALID       ((uint32_t)0x2U)                  /* Page invliad state: receive or erased */




/**
 *  @brief  Description of the 8 Bytes (64 bits) element in flash
 */
/* Bit:  0                  31  32        47  48         63  */
/*       <--- Data Value ---->  <-Vir Addr->  <- Parity  ->  */
#define EEPROM_HEADER_SIZE              (8U)                              /*!< Size of page header in Bytes */
#define EEPROM_ELEMENT_SIZE             (8U)                              /*!< Size of element in Bytes     */




/**
 *  @brief  Get EEPROM variable value
 */
#define GET_EEPROM_DATA(u32Addr)        (*(__IO uint32_t*)(u32Addr))




/**
 *  @brief EEPROM Public Function Declaration
 */
_RAM_FUNC_ uint32_t EEPROM_Init(void);
_RAM_FUNC_ uint32_t EEPROM_Format(void);
_RAM_FUNC_ uint32_t EEPROM_ReadWord(uint32_t u32Addr, uint32_t *pu32Data);
_RAM_FUNC_ uint32_t EEPROM_WriteWord(uint32_t u32Addr, uint32_t u32Data);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* EEPROM_LIB_H */


/******************* (C) COPYRIGHT 2022 SPINTROL ************* END OF FILE ****/

