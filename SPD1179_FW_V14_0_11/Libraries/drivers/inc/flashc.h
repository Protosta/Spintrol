/******************************************************************************
 * @file     flash.h
 * @brief    FLASH module header file.
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
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


#ifndef FLASHC_H
#define FLASHC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  Flash Operation Status Type Definition
 */
typedef enum {
    FLASH_OP_SUCCESS                = 0x0,
    FLASH_OP_TIMEOUT                = 0x1,
    FLASH_OP_SET_TIMING_FAIL        = 0x2,
    FLASH_OP_INVALID_PARAMETER      = 0x3,
    FLASH_OP_INVALID_READ_ADDRESS   = 0x4,
    FLASH_OP_INVALID_WRITE_ADDRESS  = 0x5,
    FLASH_OP_VERIFY_ERASE_FAIL      = 0x6,
    FLASH_OP_NO_PERMISSION          = 0x7,
} FlashOperationStatus;




/**
 *  @brief  Flash Data Pattern Type Definition
 */
typedef enum {
    FLASH_DATA_PATTERN_NONE  = 0x0U, // Input is set by FLASHDIN{E|H|L}
                                     // Output has no special pattern
    FLASH_DATA_PATTERN_ALL0  = 0x4U, // All 0's
    FLASH_DATA_PATTERN_CB01  = 0x5U, // All 0x55 checkboard bytes
    FLASH_DATA_PATTERN_CB10  = 0x6U, // All 0xAA checkboard bytes
    FLASH_DATA_PATTERN_ALL1  = 0x7U, // All 1's
} FlashDataPatternTypeEnum;




/**
 *  @brief  FLASH information
 */
#define FLASH_CHIP_SIZE           (0x20000U   )     /*!< Flash Size = 128KB                     */
#define FLASH_SECTOR_SIZE         (0x1000U    )     /*!< Flash Sector Size = 4KB                */

#define FLASH_BASE_ADDR           (0x10000000U)     /*!< Flash start address                    */




/******************************************************************************
 * @brief      Enable XIP interface
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_EnableXIP()                  (FLASHC->FLASHCTL |= FLASHCTL_XIPEN_ENABLE)




/******************************************************************************
 * @brief      Disable XIP interface
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_DisableXIP()                 (FLASHC->FLASHCTL &= ~FLASHCTL_XIPEN_Msk)




/******************************************************************************
 * @brief      Issue FLASH controller command
 *
 * @param[in]  eCommand:  FLASH controller command
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_IssueCommand(eCommand)       (FLASHC->FLASHCTL = (eCommand) | FLASHCTL_EXECUTION_EXECUTION)




/******************************************************************************
 * @brief      Is Flash controller executing command
 *
 * @param[in]  None
 *
 * @return     0 - Flash controller has finished last command execution
 *             1 - Flash controller is still executing command
 *
 ******************************************************************************/
#define FLASHC_IsExecution()                ((FLASHC->FLASHCTL & FLASHCTL_EXECUTION_Msk) >> FLASHCTL_EXECUTION_Pos)




/******************************************************************************
 * @brief      Is data acceptable for Flash controller
 *
 * @param[in]  None
 *
 * @return     0 - Flash controller does not accept new data
 *             1 - Flash controller accepts new data
 *
 ******************************************************************************/
#define FLASHC_IsDataAcceptable()           ((FLASHC->FLASHCTL & FLASHCTL_DATAACCEPT_Msk) >> FLASHCTL_DATAACCEPT_Pos)




/******************************************************************************
 * @brief      Write low word of the 64-bit data to be programmed to the Flash
 *
 * @param[in]  u32Data: Low word of the 64-bit data to be programmed
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_WriteLowWord(u32Data)        (FLASHC->FLASHDINL = (u32Data))




/******************************************************************************
 * @brief      Write high word of the 64-bit data to be programmed to the Flash
 *
 * @param[in]  u32Data: High word of the 64-bit data to be programmed
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_WriteHighWord(u32Data)       (FLASHC->FLASHDINH = (u32Data))




/******************************************************************************
 * @brief      Write ECC byte for the 64-bit data to be programmed to the Flash
 *
 * @param[in]  u8Data: 8-bit ECC data to be programed
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_WriteECCByte(u8Data)         (FLASHC->FLASHDINE = (u8Data))




/******************************************************************************
 * @brief      Write 72-bit data to be programmed to the Flash
 *
 * @param[in]  ePattern: 72-bit data pattern as defined by FLASH_DataPatternTypeEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_WriteDataPattern(ePattern)   (FLASHC->FLASHDINP = (ePattern))




/******************************************************************************
 * @brief      Read low word of the 64-bit data from the Flash
 *
 * @param[in]  None
 *
 * @return     Low word of the 64-bit data read from the Flash
 *
 ******************************************************************************/
#define FLASHC_ReadLowWord()                (FLASHC->FLASHDOUTL)




/******************************************************************************
 * @brief      Read high word of the 64-bit data from the Flash
 *
 * @param[in]  None
 *
 * @return     High word of the 64-bit data read from the Flash
 *
 ******************************************************************************/
#define FLASHC_ReadHighWord()               (FLASHC->FLASHDOUTH)




/******************************************************************************
 * @brief      Read ECC byte for the 64-bit data from the Flash
 *
 * @param[in]  None
 *
 * @return     ECC byte for the 64-bit data read from the Flash
 *
 ******************************************************************************/
#define FLASHC_ReadECCByte()                (FLASHC->FLASHDOUTE)




/******************************************************************************
 * @brief      Read data pattern for the 72-bit data from the Flash
 *
 * @param[in]  None
 *
 * @return     Recognized data pattern for the 72-bit data read from the Flash
 *             It can be one of the pattern below:
 *             - \ref FLASH_DATA_PATTERN_NONE
 *             - \ref FLASH_DATA_PATTERN_ALL0
 *             - \ref FLASH_DATA_PATTERN_CB01
 *             - \ref FLASH_DATA_PATTERN_CB10
 *             - \ref FLASH_DATA_PATTERN_ALL1
 *
 ******************************************************************************/
#define FLASHC_ReadDataPattern()            (FLASHC->FLASHDOUTP)




/******************************************************************************
 * @brief      Set Flash controller accessed address
 *
 * @param[in]  u32Addr: The address to be accessed
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_SetAddress(u32Addr)          (FLASHC->FLASHADDR = (u32Addr))




/******************************************************************************
 * @brief      Relax XIP timing
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_RelaxXIPTiming()                                                 \
    {FLASHC->FLASHCREGKEY = 0x1ACCE551U;                                        \
    *((uint8_t*)(FLASHC_BASE + 0x47)) = 3U;                                     \
    FLASHC->FLASHCREGKEY = 0x0U;}




/******************************************************************************
 * @brief      Enable write access to the protected FLASH registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_WALLOW()                     (FLASHC->FLASHCREGKEY = 0x1ACCE551U)




/******************************************************************************
 * @brief      Disable write access to the protected FLASH registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define FLASHC_WDIS()                       (FLASHC->FLASHCREGKEY = 0x0U)




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* FLASHC_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
