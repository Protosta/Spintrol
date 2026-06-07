/******************************************************************************
 * @file     meeprom_lib.c
 * @brief    MEEPROM library firmware functions.
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

#include "meeprom_lib.h"


/**
 *  @brief Private Function Prototype Declaration
 */
_RAM_FUNC_ uint32_t MEEPROM_CreateMap(MEEPROM_CB* psCB, uint32_t u32ValidPageBase);
_RAM_FUNC_ uint32_t MEEPROM_FindPage(MEEPROM_CB* psCB);
_RAM_FUNC_ uint32_t MEEPROM_VerifyPageFullWrite(MEEPROM_CB* psCB, uint32_t u32Addr, uint32_t u32Data, uint32_t u32TransferFlag);
_RAM_FUNC_ uint16_t MEEPROM_CalElementParity(uint32_t u32Addr, uint32_t u32Data);
_RAM_FUNC_ uint32_t MEEPROM_CheckElementParity(uint32_t u32EntryH, uint32_t u32EntryL);
_RAM_FUNC_ uint32_t MEEPROM_GetPageState(uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t MEEPROM_SetPageState(uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t MEEPROM_ErasePage(uint32_t u32PageAddr, uint32_t u32SectorNum);
_RAM_FUNC_ uint32_t MEEPROM_GetValidElementNum(uint32_t u32ActivePageBase, uint32_t u32PageSize, uint32_t u32MaxAddr);
_RAM_FUNC_ uint32_t MEEPROM_CheckCB(MEEPROM_CB* psCB);
_RAM_FUNC_ uint32_t MEEPROM_VerifyTransferPage(MEEPROM_CB* psCB);
_RAM_FUNC_ uint32_t MEEPROM_VerifyErasePage(MEEPROM_CB* psCB, uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t MEEPROM_TransferPage(MEEPROM_CB* psCB);

/* IAR can only use c file Options to rise the level of optimization */
#if defined (__CC_ARM )
    #pragma push
    #pragma O2
#elif defined (__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O2")
#endif
/******************************************************************************
 * @brief      Restore the pages to a known good state in case of page's status
 *             corruption after a power loss
 *             If a page is full, resume transfer.
 *
 * @param[in]  psCB : Pointer to the MEEPROM control block structure
 *
 * @return     - EEPROM_STATUS_OK               : if init success
 *             - EEPROM_STATUS_WRITE_ERROR      : if init error, due to flash write error
 *             - EEPROM_STATUS_ERASE_ERROR      : if init error, due to flash erase error
 *             - EEPROM_STATUS_INVALID_ADDR     : if variable address is invalid
 *             - EEPROM_STATUS_NO_PAGE_FOUND    : if no active page was found
 *             - EEPROM_STATUS_INVALID_ENTRY    : if entry address is invalid
 *             - EEPROM_STATUS_ADDR_MISMATCH    : if variable address is not equal
 *                                                with the address in EEPROM entry
 *             - EEPROM_STATUS_PARITY_ERROR     : if element parity check fail
 *             - EEPROM_STATUS_WRITE_CHECK_FAIL : if write check fail
 *             - EEPROM_STATUS_ELEMENT_NOT_EMPTY: if element content is not empty
 *             - EEPROM_STATUS_INVALID_HEADER   : if header status is invalid
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR: if set page header error
 *             - EEPROM_STATUS_TRANSFER_ERROR   : if perform page transfer error,
 *                                                ORed with other status
 *             - EEPROM_STATUS_INVALID_CB       : if control block is invalid
 *
 ******************************************************************************/
uint32_t MEEPROM_Init(MEEPROM_CB* psCB)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Page states */
    uint32_t u32PageState0 = 0U;
    uint32_t u32PageState1 = 0U;

    uint32_t u32Cnt0 = 0U;
    uint32_t u32Cnt1 = 0U;

    uint32_t u32Idx;

    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;
    /* EE Page0 Start address */
    uint32_t MEEPROM_PAGE0_START_ADDR = psCB->BASE_ADDR;
    /* EE Page1 Start address */
    uint32_t MEEPROM_PAGE1_START_ADDR = psCB->BASE_ADDR + MEEPROM_PAGE_SIZE;


    /* Check MEEPROM control block parameter */
    u32EepromStatus = MEEPROM_CheckCB(psCB);
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Get Page0 state */
        for (u32Idx = 0; u32Idx < 3U; u32Idx++)
        {
            u32PageState0 = MEEPROM_GetPageState(MEEPROM_PAGE0_START_ADDR);
            if (u32PageState0 == MEEPROM_PAGE_STATE_VALID)
            {
                break;
            }
        }

        /* Get Page1 state */
        for (u32Idx = 0; u32Idx < 3U; u32Idx++)
        {
            u32PageState1 = MEEPROM_GetPageState(MEEPROM_PAGE1_START_ADDR);
            if (u32PageState1 == MEEPROM_PAGE_STATE_VALID)
            {
                break;
            }
        }


        /* Check for invalid page states and repair if necessary */
        if(u32PageState0 == MEEPROM_PAGE_STATE_INVALID)
        {
            switch(u32PageState1)
            {
                case MEEPROM_PAGE_STATE_INVALID:     /* Page0 invalid, Page1 invalid */
                    /* Set invalid header flag */
                    u32EepromStatus = EEPROM_STATUS_INVALID_HEADER;

                    break;

                case MEEPROM_PAGE_STATE_VALID:       /* Page0 invalid, Page1 valid */
                    /* Erase Page0 */
                    u32EepromStatus = MEEPROM_VerifyErasePage(psCB, MEEPROM_PAGE0_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = MEEPROM_CreateMap(psCB, MEEPROM_PAGE1_START_ADDR);
                    }

                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        u32EepromStatus = MEEPROM_VerifyTransferPage(psCB);
                    }
                    break;

                default:  /* Any other state */
                    /* TODO Nothing*/
                    break;
            }
        }
        else if(u32PageState0 == MEEPROM_PAGE_STATE_VALID)
        {
            switch(u32PageState1)
            {
                case MEEPROM_PAGE_STATE_INVALID:     /* Page0 valid, Page1 invalid */
                    /* Erase Page1 */
                    u32EepromStatus = MEEPROM_VerifyErasePage(psCB, MEEPROM_PAGE1_START_ADDR);

                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = MEEPROM_CreateMap(psCB, MEEPROM_PAGE0_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        u32EepromStatus = MEEPROM_VerifyTransferPage(psCB);
                    }

                    break;

                case MEEPROM_PAGE_STATE_VALID:       /* Page0 valid, Page1 valid */
                    /* Get Page valid element count */
                    u32Cnt0 = MEEPROM_GetValidElementNum(MEEPROM_PAGE0_START_ADDR, MEEPROM_PAGE_SIZE, psCB->u32MaxVarNum);
                    u32Cnt1 = MEEPROM_GetValidElementNum(MEEPROM_PAGE1_START_ADDR, MEEPROM_PAGE_SIZE, psCB->u32MaxVarNum);

                    if(u32Cnt0 < u32Cnt1)
                    {
                        /* Erase Page1 */
                        u32EepromStatus = MEEPROM_ErasePage(MEEPROM_PAGE1_START_ADDR, psCB->u32SectorNumOfPage);
                        if(u32EepromStatus == EEPROM_STATUS_OK)
                        {
                            status = pHWLIB->FLASHC_VerifyErase(MEEPROM_PAGE1_START_ADDR, MEEPROM_PAGE_SIZE);
                            if(status != FLASH_OP_SUCCESS)
                            {
                                u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                            }
                        }

                        if(u32EepromStatus == EEPROM_STATUS_OK)
                        {
                            /* Init EEPROM Registers */
                            u32EepromStatus = MEEPROM_CreateMap(psCB, MEEPROM_PAGE0_START_ADDR);
                        }
                    }
                    else if ( u32Cnt0 > u32Cnt1)
                    {
                        /* Erase Page0 */
                        u32EepromStatus = MEEPROM_ErasePage(MEEPROM_PAGE0_START_ADDR, psCB->u32SectorNumOfPage);
                        if(u32EepromStatus == EEPROM_STATUS_OK)
                        {
                            status = pHWLIB->FLASHC_VerifyErase(MEEPROM_PAGE0_START_ADDR, MEEPROM_PAGE_SIZE);
                            if(status != FLASH_OP_SUCCESS)
                            {
                                 u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                            }
                        }
                        if(u32EepromStatus == EEPROM_STATUS_OK)
                        {
                            /* Init EEPROM Registers */
                            u32EepromStatus = MEEPROM_CreateMap(psCB, MEEPROM_PAGE1_START_ADDR);
                        }
                    }
                    else
                    {
                        /* Set invalid header flag */
                        u32EepromStatus = EEPROM_STATUS_INVALID_HEADER;
                    }

                    break;

                default:  /* Any other state */
                    /* TODO Nothing*/
                    break;
            }
        }
        else
        {
            /* TODO Nothing*/
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Erases EEPROM pages and Select a page as VALID
 *
 * @param[in]  psCB : Pointer to the MEEPROM control block structure
 *
 * @return     - EEPROM_STATUS_OK               : if format success
 *             - EEPROM_STATUS_ERASE_ERROR      : if Flash erase error
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR: if set page header error
 *             - EEPROM_STATUS_INVALID_CB       : if control block is invalid
 *
 ******************************************************************************/
uint32_t MEEPROM_Format(MEEPROM_CB* psCB)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    uint32_t i;
    uint32_t u32Code = 0U;
    uint32_t u32Page = MEEPROM_PAGE_0;

    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;
    /* EE Page0 Start address */
    uint32_t MEEPROM_PAGE0_START_ADDR = psCB->BASE_ADDR;
    /* EE Page1 Start address */
    uint32_t MEEPROM_PAGE1_START_ADDR = psCB->BASE_ADDR + MEEPROM_PAGE_SIZE;


    /* Check MEEPROM control block parameter */
    u32EepromStatus = MEEPROM_CheckCB(psCB);
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Erase Page0 */
        status = pHWLIB->FLASHC_VerifyErase(MEEPROM_PAGE0_START_ADDR, MEEPROM_PAGE_SIZE);
        if(status != FLASH_OP_SUCCESS)
        {
            u32EepromStatus = MEEPROM_ErasePage(MEEPROM_PAGE0_START_ADDR, psCB->u32SectorNumOfPage);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                status = pHWLIB->FLASHC_VerifyErase(MEEPROM_PAGE0_START_ADDR, MEEPROM_PAGE_SIZE);
                if(status != FLASH_OP_SUCCESS)
                {
                    u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                }
            }
        }
        else
        {
            u32Code |= 0x2U;
        }
        
        if (u32EepromStatus == EEPROM_STATUS_OK)
        {
            /* Erase Page1 */
            status = pHWLIB->FLASHC_VerifyErase(MEEPROM_PAGE1_START_ADDR, MEEPROM_PAGE_SIZE);
            if(status != FLASH_OP_SUCCESS)
            {
                u32EepromStatus = MEEPROM_ErasePage(MEEPROM_PAGE1_START_ADDR, psCB->u32SectorNumOfPage);
                if(u32EepromStatus == EEPROM_STATUS_OK)
                {
                    status = pHWLIB->FLASHC_VerifyErase(MEEPROM_PAGE1_START_ADDR, MEEPROM_PAGE_SIZE);
                    if(status != FLASH_OP_SUCCESS)
                    {
                        u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                    }
                }
            }
            else
            {
                u32Code |= 0x1U;
            }
        }

        if (u32EepromStatus == EEPROM_STATUS_OK)
        {
            switch(u32Code)
            {
                case 0:
                    u32Page = MEEPROM_PAGE_0;
                    break;

                case 1:
                    u32Page = MEEPROM_PAGE_1;
                    break;

                case 2:
                    u32Page = MEEPROM_PAGE_0;
                    break;

                case 3:
                    u32Page = MEEPROM_PAGE_1;
                    break;

                default:
                    u32Page = MEEPROM_PAGE_0;
                    break;
            }

            /* Reset EEPROM register */
            for (i = 0U; i < psCB->u32MaxVarNum; i++)
            {
                psCB->pEntryTable[i] = MEEPROM_DEFAULT_ENTRY_ADDR;
            }

            psCB->u32Next = MEEPROM_PAGE0_START_ADDR + (u32Page * MEEPROM_PAGE_SIZE) + MEEPROM_HEADER_SIZE;

            /* Set Page in VALID state */
            u32EepromStatus = MEEPROM_SetPageState((MEEPROM_PAGE0_START_ADDR + (u32Page * MEEPROM_PAGE_SIZE)));
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Init MEEPROM_CB according to a active page
 *
 * @param[in]  psCB             : Pointer to the MEEPROM control block structure
 * @param[in]  u32ActivePageBase:  Active page start address
 *
 * @return     - EEPROM_STATUS_OK               : if format success
 *             - EEPROM_STATUS_PARITY_ERROR     : if parity check fail
 *             - EEPROM_STATUS_INVALID_ADDR     : if variable address is invalid
 *
 ******************************************************************************/
uint32_t MEEPROM_CreateMap(MEEPROM_CB* psCB, uint32_t u32ActivePageBase)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* The start address of page */
    uint32_t u32PageStartAddr;
    /* The element address in the page */
    uint32_t u32PageAddr;

    /* The element address and data field value */
    uint32_t u32AddrVal, u32DataVal;

    uint32_t u32Temp, u32Flag;

    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;


    /* Init next entry address - Assume that current active page is full */
    psCB->u32Next = u32ActivePageBase + MEEPROM_PAGE_SIZE;

    /* Reset EEPROM register */
    for(u32Temp = 0U; u32Temp < psCB->u32MaxVarNum; u32Temp++)
    {
        psCB->pEntryTable[u32Temp] = MEEPROM_DEFAULT_ENTRY_ADDR;
    }

    /* Get the active page start address */
    u32PageStartAddr = (uint32_t)(u32ActivePageBase + MEEPROM_HEADER_SIZE);

    /* Get the active page end address */
    u32PageAddr = (uint32_t)(u32ActivePageBase + MEEPROM_PAGE_SIZE - 8U);

    u32Flag = 0U;
    /* Check each active page address starting from end */
    while(u32PageAddr >= u32PageStartAddr)
    {
        /* Get the address of Variable address-field */
        u32Temp = u32PageAddr + 4U;

        /* Get current location content */
        u32DataVal = GET_MEEPROM_DATA(u32PageAddr);
        u32AddrVal = GET_MEEPROM_DATA(u32Temp);

        /* Check the content */
        if((u32DataVal == 0xFFFFFFFFU) && (u32AddrVal == 0xFFFFFFFFU))
        {
            /* Dirty element not found */
            if(u32Flag == 0U)
            {
                /* Empty entry */
                psCB->u32Next = u32PageAddr;
            }
        }
        else
        {
            /* Dirty element found */
            u32Flag = 1U;

            /* Check entry parity */
            u32EepromStatus = MEEPROM_CheckElementParity(u32AddrVal, u32DataVal);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                /* Real variable address */
                u32AddrVal &= 0x0000FFFFU;

                /* Check variable address */
                if(u32AddrVal < psCB->u32MaxVarNum)
                {
                    /* If the first variable record, update variable entry address register */
                    if(psCB->pEntryTable[u32AddrVal] == MEEPROM_DEFAULT_ENTRY_ADDR)
                    {
                        psCB->pEntryTable[u32AddrVal] = u32PageAddr;
                    }
                }
                else
                {
                    u32EepromStatus = EEPROM_STATUS_INVALID_ADDR;
                    break;
                }
            }
            else
            {
                break;
            }
        }

        /* Next address location */
        u32PageAddr = u32PageAddr - 8U;
    }
    
    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Find suitable page for read/write operation
 *
 * @param[in]  psCB : Pointer to the MEEPROM control block structure
 *
 * @return     - Page index        : if success (MEEPROM_PAGE_0 ~ MEEPROM_PAGE_1)
 *             - MEEPROM_PAGE_NONE : if an error occurs
 *
 ******************************************************************************/
uint32_t MEEPROM_FindPage(MEEPROM_CB* psCB)
{
    uint32_t u32PageIndex;
    uint32_t u32PageState0 = 0U;
    uint32_t u32PageState1 = 0U;

    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE        = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;
    /* EE Page0 start address */
    uint32_t MEEPROM_PAGE0_START_ADDR = psCB->BASE_ADDR;
    /* EE Page1 start address */
    uint32_t MEEPROM_PAGE1_START_ADDR = psCB->BASE_ADDR + MEEPROM_PAGE_SIZE;


    /* Get Page0 state */
    u32PageState0 = MEEPROM_GetPageState(MEEPROM_PAGE0_START_ADDR);

    /* Get Page1 state */
    u32PageState1 = MEEPROM_GetPageState(MEEPROM_PAGE1_START_ADDR);


    if (u32PageState0 == MEEPROM_PAGE_STATE_VALID)
    {
        u32PageIndex = MEEPROM_PAGE_0;     /* Page0 valid */
    }
    else if(u32PageState1 == MEEPROM_PAGE_STATE_VALID)
    {
        u32PageIndex = MEEPROM_PAGE_1;     /* Page1 valid */
    }
    else
    {
        u32PageIndex = MEEPROM_PAGE_NONE;  /* No suitable page found */
    }

    return u32PageIndex;
}




/******************************************************************************
 * @brief      Verify if pages are full,
 *             then if not the case, writes variable in EEPROM
 *
 * @param[in]  psCB    : Pointer to the MEEPROM control block structure
 * @param[in]  u32Addr :  Varaible address, can be 0 ~ 255
 * @param[in]  u32Data :  32-bit data to be written
 * @param[in]  u32TransferFlag :  Page transfer indicator flag
 *
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK               : if variable was written success
 *             - EEPROM_STATUS_WRITE_ERROR      : if flash operation error
 *             - EEPROM_STATUS_INVALID_ADDR     : if variable address is invalid
 *             - EEPROM_STATUS_WRITE_CHECK_FAIL : if write check fail
 *             - EEPROM_STATUS_PAGE_FULL        : if valid page is full, ORed with other status
 *             - EEPROM_STATUS_NO_PAGE_FOUND    : if no active page was found
 *             - EEPROM_STATUS_INVALID_ENTRY    : if entry address value is invalid
 *             - EEPROM_STATUS_ELEMENT_NOT_EMPTY: if element content is not empty
 *
 ******************************************************************************/
uint32_t MEEPROM_VerifyPageFullWrite(MEEPROM_CB* psCB, uint32_t u32Addr, uint32_t u32Data, uint32_t u32TransferFlag)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Active page for write operation */
    uint32_t u32Page = MEEPROM_PAGE_0;

    /* The start and end address of the active page */
    uint32_t u32StartAddr, u32EndAddr;
    /* Entry address for write */
    uint32_t u32EntryAddr, u32EntryAddrH;
    /* Element address and data field value */
    uint32_t u32AddrVal, u32DataVal;

    uint32_t u32Temp;

    /* EE Start address */
    uint32_t MEEPROM_START_ADDR = psCB->BASE_ADDR;
    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;


    /* Check the variable address */
    if (u32Addr < psCB->u32MaxVarNum)
    {
        /* Get active page for write operation */
        u32Page = MEEPROM_FindPage(psCB);

        /* Check if there is no active page */
        if (u32Page == MEEPROM_PAGE_NONE)
        {
            u32EepromStatus = EEPROM_STATUS_NO_PAGE_FOUND;
        }
        else
        {
            /* For page transfer operation */
            if (u32TransferFlag == 1U)
            {
                /* Page to receive data */
                if (u32Page == MEEPROM_PAGE_1)
                {
                    u32Page = MEEPROM_PAGE_0;
                }
                else
                {
                    u32Page = MEEPROM_PAGE_1;
                }
            }

            /* Get entry address for write */
            u32EntryAddr = psCB->u32Next;

            /* Get the active page start address */
            u32StartAddr = (uint32_t)((MEEPROM_START_ADDR + MEEPROM_HEADER_SIZE) + (uint32_t)(u32Page * MEEPROM_PAGE_SIZE));

            /* Get the active page end address */
            u32EndAddr = (uint32_t)((MEEPROM_START_ADDR - 8U) + (uint32_t)((1U + u32Page) * MEEPROM_PAGE_SIZE));

            /* Check entry address */
            if ( (u32EntryAddr >= u32StartAddr) && (u32EntryAddr <= u32EndAddr) )
            {
                /* Update next entry address for write at first */
                psCB->u32Next = u32EntryAddr + 8U;

                /* Get the address of Variable address-field */
                u32EntryAddrH = u32EntryAddr + 4U;

                /* Get the current location content */
                u32AddrVal = GET_MEEPROM_DATA(u32EntryAddrH);
                u32DataVal = GET_MEEPROM_DATA(u32EntryAddr);

                /* Verify if current location is empty */
                if((u32DataVal == 0xFFFFFFFFU) && (u32AddrVal == 0xFFFFFFFFU))
                {
                    /* Calculate element parity */
                    u32Temp = (uint32_t)MEEPROM_CalElementParity(u32Addr, u32Data);

                    /* Update High-32 bit data */
                    u32Temp <<= 16U;
                    u32Temp |= u32Addr;

                    /* Write variable to EEPROM */
                    status = pHWLIB->FLASHC_ProgramDWord(u32EntryAddr, u32Data, u32Temp);
                    if(status != FLASH_OP_SUCCESS)
                    {
                        /* Flash Program fail */
                        u32EepromStatus = EEPROM_STATUS_WRITE_ERROR;
                    }
                    else
                    {
                        /* Read back */
                        u32AddrVal = GET_MEEPROM_DATA(u32EntryAddrH);
                        u32DataVal = GET_MEEPROM_DATA(u32EntryAddr);

                        /* Check written data */
                        if((u32AddrVal == u32Temp) && (u32DataVal == u32Data))
                        {
                            /* Update entry address */
                            psCB->pEntryTable[u32Addr] = u32EntryAddr;

                            /* Data was written success */
                            u32EepromStatus = EEPROM_STATUS_OK;
                        }
                        else
                        {
                            /* Write check fail */
                            u32EepromStatus = EEPROM_STATUS_WRITE_CHECK_FAIL;
                        }
                    }
                }
                else
                {
                    /* Element content is not empty */
                    u32EepromStatus = EEPROM_STATUS_ELEMENT_NOT_EMPTY;
                }

                /* Check if pages are full */
                if (u32EntryAddr == u32EndAddr)
                {
                    u32EepromStatus |= EEPROM_STATUS_PAGE_FULL;
                }
            }
            else
            {
                /* Entry address is not valid */
                u32EepromStatus = EEPROM_STATUS_INVALID_ENTRY;
            }
        }
    }
    else
    {
        /* Invalid variable address */
        u32EepromStatus = EEPROM_STATUS_INVALID_ADDR;
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      If current page is full, transfer current page to empty page
 *
 * @param[in]  psCB : Pointer to the MEEPROM control block structure
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK                : if page transfer success
 *             - EEPROM_STATUS_WRITE_ERROR       : if flash program error
 *             - EEPROM_STATUS_ERASE_ERROR       : if flash erase error
 *             - EEPROM_STATUS_INVALID_ADDR      : if variable address is invalid
 *             - EEPROM_STATUS_WRITE_CHECK_FAIL  : if write check fail
 *             - EEPROM_STATUS_NO_PAGE_FOUND     : if no active page was found
 *             - EEPROM_STATUS_INVALID_ENTRY     : if entry address value is invalid
 *             - EEPROM_STATUS_ELEMENT_NOT_EMPTY : if element content is not empty
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR : if set page header error
 *             - EEPROM_STATUS_TRANSFER_ERROR    : if perform page transfer error,
 *                                                ORed with other status
 *             - EEPROM_STATUS_INVALID_CB        : if control block is invalid
 *             - EEPROM_STATUS_PARITY_ERROR      : if element parity check fail
 *             - EEPROM_STATUS_ADDR_MISMATCH     : if variable address is not equal
 *                                                with the address in EEPROM entry
 *
 ******************************************************************************/
uint32_t MEEPROM_VerifyTransferPage(MEEPROM_CB* psCB)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;
    uint32_t u32Idx;
    uint32_t u32NewPageAddr;
    uint32_t u32OldPageAddr;
    uint32_t u32DataVar;
    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;
    /* EE Page0 Start address */
    uint32_t MEEPROM_PAGE0_START_ADDR = psCB->BASE_ADDR;
    /* EE Page1 Start address */
    uint32_t MEEPROM_PAGE1_START_ADDR = psCB->BASE_ADDR + MEEPROM_PAGE_SIZE;
    
    /* Check mapping result - valid page is full, perform page transfer */
    if(psCB->u32Next == (MEEPROM_PAGE1_START_ADDR + MEEPROM_PAGE_SIZE))
    {
        psCB->u32Next = MEEPROM_PAGE0_START_ADDR + MEEPROM_HEADER_SIZE;
        
        /* New page address where variable will be moved to */
        u32NewPageAddr = MEEPROM_PAGE0_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = MEEPROM_PAGE1_START_ADDR;
    }
    /* Check mapping result - valid page is full, perform page transfer */
    else if(psCB->u32Next == MEEPROM_PAGE1_START_ADDR)
    {
        psCB->u32Next = MEEPROM_PAGE1_START_ADDR + MEEPROM_HEADER_SIZE;
        
        /* New page address where variable will be moved to */
        u32NewPageAddr = MEEPROM_PAGE1_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = MEEPROM_PAGE0_START_ADDR;
    }
    else
    {
        /* Current page is not full, do not need to transfer current page to empty page. 
        Return EEPROM_STATUS_OK directly */
        return u32EepromStatus;
    }

    /* Transfer data from OldPage to NewPage */
    for(u32Idx = 0U; u32Idx < psCB->u32MaxVarNum; u32Idx++)
    {
        /* Read the last data updates */
        u32EepromStatus = MEEPROM_ReadWord(psCB, u32Idx, &u32DataVar);
        /* In case data corresponding to the specified address was found */
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            /* Transfer the data to the new active page */
            u32EepromStatus = MEEPROM_VerifyPageFullWrite(psCB, u32Idx, u32DataVar, 1U);
        }
        else if (u32EepromStatus == EEPROM_STATUS_NO_DATA)
        {
            u32EepromStatus = EEPROM_STATUS_OK;
        }

        /* If read or write operation was failed */
        if(u32EepromStatus != EEPROM_STATUS_OK)
        {
            u32EepromStatus |= EEPROM_STATUS_TRANSFER_ERROR;
            break;
        }
    }

    /* Mark NewPage as valid */
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        u32EepromStatus = MEEPROM_SetPageState(u32NewPageAddr);
    }

    /* Erase OldPage */
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        u32EepromStatus = MEEPROM_ErasePage(u32OldPageAddr, psCB->u32SectorNumOfPage);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            status = pHWLIB->FLASHC_VerifyErase(u32OldPageAddr, MEEPROM_PAGE_SIZE);
            if(status != FLASH_OP_SUCCESS)
            {
                u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
            }
        }
    }
    
    /* Return operation status */
    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Calculate the EEPROM element parity
 *
 * @param[in]  u32Addr :  Variable address, can be 0 ~ 255
 * @param[in]  u32Data :  32-bit data
 *
 * @return     Parity of EEPROM element
 *
 ******************************************************************************/
uint16_t MEEPROM_CalElementParity(uint32_t u32Addr, uint32_t u32Data)
{
    uint16_t u16Parity;
    uint16_t u16Temp;

    /* Calculate parity */
    u16Temp = (uint16_t)(u32Data & 0x0000FFFFU);
    u16Parity = u16Temp;

    u16Temp = (uint16_t)((u32Data & 0xFFFF0000U) >> 16);
    u16Parity ^= u16Temp;

    u16Temp = (uint16_t)(u32Addr & 0x0000FFFFU);
    u16Parity ^= u16Temp;

    return u16Parity;
}




/******************************************************************************
 * @brief      Check the EEPROM element parity
 *
 * @param[in]  u32EntryH :  EEPROM element High 32-bit data
 * @param[in]  u32EntryL :  EEPROM element Low 32-bit data
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK          : if parity check OK
 *             - EEPROM_STATUS_PARITY_ERROR: if parity check fail
 *
 ******************************************************************************/
uint32_t MEEPROM_CheckElementParity(uint32_t u32EntryH, uint32_t u32EntryL)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* The original value in element parity field */
    uint16_t u16ParityOri;

    /* The calculated parity value */
    uint16_t u16Parity;

    uint16_t u16Temp;


    /* EEPROM entry original parity */
    u16ParityOri = (uint16_t)((u32EntryH & 0xFFFF0000U) >> 16);

    /* Calculate parity of EEPROM entry data */
    u16Temp = (uint16_t)(u32EntryL & 0x0000FFFFU);
    u16Parity = u16Temp;

    u16Temp = (uint16_t)((u32EntryL & 0xFFFF0000U) >> 16);
    u16Parity ^= u16Temp;

    u16Temp = (uint16_t)(u32EntryH & 0x0000FFFFU);
    u16Parity ^= u16Temp;

    /* Check parity */
    if(u16ParityOri != u16Parity)
    {
        /* Parity check fail */
        u32EepromStatus = EEPROM_STATUS_PARITY_ERROR;
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Get page state in page header
 *
 * @param[in]  u32PageAddr :  Address of the EEPROM page
 *
 * @return     State of the page
 *
 ******************************************************************************/
uint32_t MEEPROM_GetPageState(uint32_t u32PageAddr)
{
    uint32_t u32PageState   = 0U;
    uint32_t u32PageHeaderL = 0U;
    uint32_t u32PageHeaderH = 0U;

    /* Get page state information from page header */
    u32PageHeaderL = (*(__IO uint32_t*)(u32PageAddr));
    u32PageHeaderH = (*(__IO uint32_t*)(u32PageAddr + 4U));

    /* Return VALID state */
    if ((u32PageHeaderL == 0x1ACCE551U) || (u32PageHeaderH == 0x1ACCE551U))
    {
        u32PageState = MEEPROM_PAGE_STATE_VALID;
    }
    else
    {
        u32PageState = MEEPROM_PAGE_STATE_INVALID;
    }

    return u32PageState;
}




/******************************************************************************
 * @brief      Set page state in page header
 *
 * @param[in]  u32PageAddr :  Address of the EEPROM page
 * @param[in]  ePageState  :  State of the page
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK               : if success
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR: if read-back check fail
 *
 ******************************************************************************/
uint32_t MEEPROM_SetPageState(uint32_t u32PageAddr)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Set new page state to VALID state */
    status = pHWLIB->FLASHC_ProgramDWord(u32PageAddr, (uint32_t)MEEPROM_PAGE_HEADER_VALID, (uint32_t)(MEEPROM_PAGE_HEADER_VALID >> 32));
    if (status != FLASH_OP_SUCCESS)
    {
        u32EepromStatus = EEPROM_STATUS_PAGE_HEADER_ERROR;
    }
    else
    {
        /* Get page state information from page */
        if(MEEPROM_GetPageState(u32PageAddr) != MEEPROM_PAGE_STATE_VALID)
        {
            u32EepromStatus = EEPROM_STATUS_PAGE_HEADER_ERROR;
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Erase MEEPROM page
 *
 * @param[in]  u32PageAddr  :  Address of the MEEPROM page
 * @param[in]  u32SectorNum :  Sector number of the page
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK         : if success
 *             - EEPROM_STATUS_ERASE_ERROR: if erase fail
 *
 ******************************************************************************/
uint32_t MEEPROM_ErasePage(uint32_t u32PageAddr, uint32_t u32SectorNum)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    uint32_t i;

    /* Erase Page */
    for(i = 0U; i < u32SectorNum; i++)
    {
        status = pHWLIB->FLASHC_EraseSector((u32PageAddr + i * FLASH_SECTOR_SIZE));
        if(status != FLASH_OP_SUCCESS)
        {
            u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
            break;
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      If MEEPROM page is not erased, erase MEEPROM page
 *
 * @param[in]  psCB : Pointer to the MEEPROM control block structure
 * @param[in]  u32PageAddr  :  Address of the MEEPROM page
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK         : if success
 *             - EEPROM_STATUS_ERASE_ERROR: if erase fail
 *
 ******************************************************************************/
uint32_t MEEPROM_VerifyErasePage(MEEPROM_CB* psCB, uint32_t u32PageAddr)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;
    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;

    status = pHWLIB->FLASHC_VerifyErase(u32PageAddr, MEEPROM_PAGE_SIZE);
    if(status != FLASH_OP_SUCCESS)
    {
        u32EepromStatus = MEEPROM_ErasePage(u32PageAddr, psCB->u32SectorNumOfPage);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            status = pHWLIB->FLASHC_VerifyErase(u32PageAddr, MEEPROM_PAGE_SIZE);
            if(status != FLASH_OP_SUCCESS)
            {
                u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
            }
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Get valid element count in a page
 *
 * @param[in]  u32ActivePageBase : Address of the EEPROM page
 * @param[in]  u32PageSize       : Page size
 * @param[in]  u32MaxAddr        : Maximum variable address
 *
 * @return     Valid element count
 *
 ******************************************************************************/
uint32_t MEEPROM_GetValidElementNum(uint32_t u32ActivePageBase, uint32_t u32PageSize, uint32_t u32MaxAddr)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;
    uint32_t u32ValidCnt = 0U;

    /* The start address of page */
    uint32_t u32PageStartAddr;
    /* The element address in the page */
    uint32_t u32PageAddr;

    /* The element address and data field value */
    uint32_t u32AddrVal, u32DataVal;


    /* Get the active page start address */
    u32PageStartAddr = (uint32_t)(u32ActivePageBase + MEEPROM_HEADER_SIZE);

    /* Get the active page end address */
    u32PageAddr = (uint32_t)(u32ActivePageBase + u32PageSize - 8U);

    /* Check each active page address starting from end */
    while(u32PageAddr >= u32PageStartAddr)
    {
        /* Get current location content */
        u32DataVal = GET_MEEPROM_DATA(u32PageAddr);
        u32AddrVal = GET_MEEPROM_DATA((u32PageAddr + 4U));

        /* Check entry parity */
        u32EepromStatus = MEEPROM_CheckElementParity(u32AddrVal, u32DataVal);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            /* Real variable address */
            u32AddrVal &= 0x0000FFFFU;

            /* Check variable address */
            if(u32AddrVal < u32MaxAddr)
            {
                u32ValidCnt = u32ValidCnt + 1U;
            }
        }

        /* Next address location */
        u32PageAddr = u32PageAddr - 8U;
    }

    return u32ValidCnt;
}




/******************************************************************************
 * @brief      Check MEEPROM control block parameter
 *
 * @param[in]  psCB : Pointer to MEEPROM control block
 *
 * @return     - EEPROM_STATUS_OK         : if control block parameter ok
 *             - EEPROM_STATUS_INVALID_CB : if control block parameter invlid
 *
 ******************************************************************************/
uint32_t MEEPROM_CheckCB(MEEPROM_CB* psCB)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Variable for flash main array stop address */
    uint32_t u32FlashMainStopAddr = (((*((__IO uint32_t*)0x400000b0) & 6U) + 2U) << 14) + FLASH_BASE_ADDR_MAIN;


    /* Invalid start address */
    if((psCB->BASE_ADDR < FLASH_BASE_ADDR_MAIN) || (psCB->BASE_ADDR >= u32FlashMainStopAddr))
    {
        if((psCB->BASE_ADDR != FLASH_BASE_ADDR_RDN0) && (psCB->BASE_ADDR != FLASH_BASE_ADDR_RDN1))
        {
            u32EepromStatus = EEPROM_STATUS_INVALID_CB;
        }
    }

    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Invalid sector number or Max variable number */
        if((psCB->u32SectorNumOfPage == 0U) || (psCB->u32MaxVarNum == 0U))
        {
            u32EepromStatus = EEPROM_STATUS_INVALID_CB;
        }
    }

    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Actual maximum variable number is half of space*/
        if(psCB->u32MaxVarNum > (psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE / MEEPROM_ELEMENT_SIZE / 2))
        {
            u32EepromStatus = EEPROM_STATUS_INVALID_CB;
        }
    }
    
    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Returns the last stored variable, if found, which correspond to
 *             the passed variable address
 *
 * @param[in]  psCB     : Pointer to the MEEPROM control block structure
 * @param[in]  u32Addr  :  Variable address, can be 0 ~ 255
 * @param[in]  pu32Data :  Pointer to the readed variable value
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK           : if variable was found
 *             - EEPROM_STATUS_NO_DATA      : if variable was not found
 *             - EEPROM_STATUS_INVALID_ADDR : if variable address is invalid
 *             - EEPROM_STATUS_NO_PAGE_FOUND: if no active page was found
 *             - EEPROM_STATUS_INVALID_ENTRY: if entry address is invalid
 *             - EEPROM_STATUS_ADDR_MISMATCH: if variable address is not equal
 *                                            with the address in EEPROM entry
 *             - EEPROM_STATUS_PARITY_ERROR : if element parity check fail
 *             - EEPROM_STATUS_INVALID_CB   : if control block is invalid
 *
 ******************************************************************************/
uint32_t MEEPROM_ReadWord(MEEPROM_CB* psCB, uint32_t u32Addr, uint32_t *pu32Data)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_NO_DATA;
    uint32_t u32Page = MEEPROM_PAGE_NONE;

    /* The start address and end address of active page */
    uint32_t u32StartAddr, u32EndAddr;
    /* The element address of the variable to be read */
    uint32_t u32EntryAddr;
    /* The address value and data value of the element */
    uint32_t u32AddrVal, u32DataVal;
    uint32_t u32Temp;

    /* EE Start address */
    uint32_t MEEPROM_START_ADDR = psCB->BASE_ADDR;
    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;

    /* Check MEEPROM control block parameter */
    u32EepromStatus = MEEPROM_CheckCB(psCB);
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Check the variable address */
        if (u32Addr < psCB->u32MaxVarNum)
        {
            /* Get active page for read operation */
            u32Page = MEEPROM_FindPage(psCB);

            /* Check if there is no active page */
            if (u32Page == MEEPROM_PAGE_NONE)
            {
                u32EepromStatus = EEPROM_STATUS_NO_PAGE_FOUND;
            }
            else
            {
                /* Get the active page start address */
                u32StartAddr = (uint32_t)((MEEPROM_START_ADDR + MEEPROM_HEADER_SIZE) + (uint32_t)(u32Page * MEEPROM_PAGE_SIZE));

                /* Get the active page end address */
                u32EndAddr   = (uint32_t)((MEEPROM_START_ADDR - 8U) + (uint32_t)((1U + u32Page) * MEEPROM_PAGE_SIZE));

                /* Get EEPROM element address for read */
                u32EntryAddr = psCB->pEntryTable[u32Addr];

                /* Check the element address */
                if ((u32EntryAddr >= u32StartAddr) && (u32EntryAddr <= u32EndAddr))
                {
                    /* Get the address of Variable address-field */
                    u32Temp = u32EntryAddr + 4U;

                    /* Get the current location content */
                    u32DataVal = GET_MEEPROM_DATA(u32EntryAddr);
                    u32AddrVal = GET_MEEPROM_DATA(u32Temp);

                    /* Check element parity */
                    u32EepromStatus = MEEPROM_CheckElementParity(u32AddrVal, u32DataVal);
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Real variable address */
                        u32AddrVal &= 0x0000FFFFU;

                        /* Compare the readed address with the specified address */
                        if(u32AddrVal == u32Addr)
                        {
                            /* Get variable value */
                            *pu32Data = u32DataVal;

                            /* In case variable value is readed, set status flag */
                            u32EepromStatus = EEPROM_STATUS_OK;
                        }
                        else
                        {
                            /* The varaible address is not equal to that in EEPROM element */
                            u32EepromStatus = EEPROM_STATUS_ADDR_MISMATCH;
                        }
                    }
                    else
                    {
                        /* Element parity check fail */
                        u32EepromStatus = EEPROM_STATUS_PARITY_ERROR;
                    }
                }
                else if(u32EntryAddr == MEEPROM_DEFAULT_ENTRY_ADDR)
                {
                    /* Variable not found */
                    u32EepromStatus = EEPROM_STATUS_NO_DATA;
                }
                else
                {
                    /* Entry address is not valid */
                    u32EepromStatus = EEPROM_STATUS_INVALID_ENTRY;
                }
            }
        }
        else
        {
            /* Invalid variable address */
            u32EepromStatus = EEPROM_STATUS_INVALID_ADDR;
        }
    }

    /* Return status */
    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Transfers last updated elements from full pages to
 *             empty pages in any cases
 *
 * @param[in]  psCB : Pointer to the MEEPROM control block structure
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK                : if page transfer success
 *             - EEPROM_STATUS_WRITE_ERROR       : if flash program error
 *             - EEPROM_STATUS_ERASE_ERROR       : if flash erase error
 *             - EEPROM_STATUS_INVALID_ADDR      : if variable address is invalid
 *             - EEPROM_STATUS_WRITE_CHECK_FAIL  : if write check fail
 *             - EEPROM_STATUS_NO_PAGE_FOUND     : if no active page was found
 *             - EEPROM_STATUS_INVALID_ENTRY     : if entry address value is invalid
 *             - EEPROM_STATUS_ELEMENT_NOT_EMPTY : if element content is not empty
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR : if set page header error
 *
 ******************************************************************************/
uint32_t MEEPROM_TransferPage(MEEPROM_CB* psCB)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Active page for read operation */
    uint32_t u32Page = MEEPROM_PAGE_0;

    uint32_t u32Idx;
    uint32_t u32DataVar;

    /* New page start address */
    uint32_t u32NewPageAddr;
    /* Old page start address */
    uint32_t u32OldPageAddr;

    /* EE Start address */
    uint32_t MEEPROM_START_ADDR = psCB->BASE_ADDR;
    /* EE Page size */
    uint32_t MEEPROM_PAGE_SIZE = psCB->u32SectorNumOfPage * FLASH_SECTOR_SIZE;


    /* Get active page for read operation */
    u32Page = MEEPROM_FindPage(psCB);

    if(u32Page == MEEPROM_PAGE_1)          /* Page1 active */
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = MEEPROM_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = MEEPROM_START_ADDR + MEEPROM_PAGE_SIZE;
    }
    else if (u32Page == MEEPROM_PAGE_0)    /* Page0 active */
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = MEEPROM_START_ADDR + MEEPROM_PAGE_SIZE;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = MEEPROM_START_ADDR;
    }
    else
    {
        /* No active Page */
        u32EepromStatus = EEPROM_STATUS_NO_PAGE_FOUND;
    }


    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Erase the New page */
        status = pHWLIB->FLASHC_VerifyErase(u32NewPageAddr, MEEPROM_PAGE_SIZE);
        if(status != FLASH_OP_SUCCESS)
        {
            u32EepromStatus = MEEPROM_ErasePage(u32NewPageAddr, psCB->u32SectorNumOfPage);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                status = pHWLIB->FLASHC_VerifyErase(u32NewPageAddr, MEEPROM_PAGE_SIZE);
                if(status != FLASH_OP_SUCCESS)
                {
                    u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                }
            }
        }

        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            /* Update next entry address */
            psCB->u32Next = u32NewPageAddr + MEEPROM_HEADER_SIZE;

            /* Transfer process: transfer variable from old to the new active page */
            for(u32Idx = 0U; u32Idx < psCB->u32MaxVarNum; u32Idx++)
            {
                /* Read the other last varaible updates */
                u32EepromStatus = MEEPROM_ReadWord(psCB, u32Idx, &u32DataVar);
                if(u32EepromStatus == EEPROM_STATUS_OK)
                {
                    /* Transfer the data to the new active page */
                    u32EepromStatus = MEEPROM_VerifyPageFullWrite(psCB, u32Idx, u32DataVar, 1U);
                }
                else if (u32EepromStatus == EEPROM_STATUS_NO_DATA)
                {
                    u32EepromStatus = EEPROM_STATUS_OK;
                }

                /* If read or write operation was failed */
                if (u32EepromStatus != EEPROM_STATUS_OK)
                {
                    break;
                }
            }


            /* Set new page state to VALID */
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                u32EepromStatus = MEEPROM_SetPageState(u32NewPageAddr);
            }

            /* Erase the old page: Set old page state to INVALID state */
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                u32EepromStatus = MEEPROM_ErasePage(u32OldPageAddr, psCB->u32SectorNumOfPage);
                if(u32EepromStatus == EEPROM_STATUS_OK)
                {
                    /* Verify Erase */
                    status = pHWLIB->FLASHC_VerifyErase(u32OldPageAddr, MEEPROM_PAGE_SIZE);
                    if(status != FLASH_OP_SUCCESS)
                    {
                        u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                    }
                }
            }
        }
    }

    /* Return operation status */
    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Writes/upadtes variable in EEPROM
 *             Trigger internal pages transfer if the pages are full
 *
 * @param[in]  psCB    : Pointer to the MEEPROM control block structure
 * @param[in]  u32Addr :  Variable address, can be 0 ~ 255
 * @param[in]  u32Data :  32-bit data to be written
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK               : if variable was written success
 *             - EEPROM_STATUS_WRITE_ERROR      : if flash program error
 *             - EEPROM_STATUS_INVALID_ADDR     : if variable address is invalid
 *             - EEPROM_STATUS_WRITE_CHECK_FAIL : if write check fail
 *             - EEPROM_STATUS_NO_PAGE_FOUND    : if no active page was found
 *             - EEPROM_STATUS_INVALID_ENTRY    : if entry address value is invalid
 *             - EEPROM_STATUS_ELEMENT_NOT_EMPTY: if element content is not empty
 *             - EEPROM_STATUS_TRANSFER_ERROR   : if perform page transfer error,
 *                                                this flag is ORed with other status
 *             - EEPROM_STATUS_INVALID_CB       : if control block is invalid
 *
 ******************************************************************************/
uint32_t MEEPROM_WriteWord(MEEPROM_CB* psCB, uint32_t u32Addr, uint32_t u32Data)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Check MEEPROM control block parameter */
    u32EepromStatus = MEEPROM_CheckCB(psCB);
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Write the varaiable address and value in the EEPROM */
        u32EepromStatus = MEEPROM_VerifyPageFullWrite(psCB, u32Addr, u32Data, 0U);
        
        /* In case the EEPROM active page is full */
        if((u32EepromStatus & EEPROM_STATUS_PAGE_FULL) == EEPROM_STATUS_PAGE_FULL)
        {
            if ((u32EepromStatus & EEPROM_STATUS_OK) == EEPROM_STATUS_OK)
            {
                /* Perform page transfer */
                u32EepromStatus = MEEPROM_TransferPage(psCB);
                if(u32EepromStatus != EEPROM_STATUS_OK)
                {
                    u32EepromStatus |= EEPROM_STATUS_TRANSFER_ERROR;
                }
            }
        }
    }

    return u32EepromStatus;
}
#if defined (__CC_ARM )
    #pragma pop
#elif defined (__GNUC__)
    #pragma GCC pop_options
#endif




/******************* (C) COPYRIGHT 2022 SPINTROL ************* END OF FILE ****/

