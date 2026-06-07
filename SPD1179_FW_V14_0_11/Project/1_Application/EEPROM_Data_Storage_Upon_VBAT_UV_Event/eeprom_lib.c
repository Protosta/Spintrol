/******************************************************************************
 * @file     meeprom_lib.c
 * @brief    EEPROM library firmware functions.
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



#include "eeprom_lib.h"




/**
 *  @brief Private Function Prototype Declaration
 */
_RAM_FUNC_ uint32_t EEPROM_CreateMap(uint32_t u32ActivePageBase);
_RAM_FUNC_ uint32_t EEPROM_FindPage(void);
_RAM_FUNC_ uint32_t EEPROM_VerifyPageFullWrite(uint32_t u32Addr, uint32_t u32Data, uint32_t u32TransferFlag);
_RAM_FUNC_ uint16_t EEPROM_CalElementParity(uint32_t u32Addr, uint32_t u32Data);
_RAM_FUNC_ uint32_t EEPROM_CheckElementParity(uint32_t u32EntryH, uint32_t u32EntryL);
_RAM_FUNC_ uint32_t EEPROM_GetPageState(uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t EEPROM_SetPageState(uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t EEPROM_ErasePage(uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t EEPROM_VerifyTransferPage(void);
_RAM_FUNC_ uint32_t EEPROM_VerifyErasePage(uint32_t u32PageAddr);
_RAM_FUNC_ uint32_t EEPROM_TransferPage(void);


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
 * @param[in]  none
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
 *
 ******************************************************************************/
uint32_t EEPROM_Init(void)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Page states */
    uint32_t u32PageState0 = 0U;
    uint32_t u32PageState1 = 0U;
    uint32_t u32PageState2 = 0U;

    uint32_t u32Idx;


    /* Get Page0 state */
    for (u32Idx = 0; u32Idx < 3U; u32Idx++)
    {
        u32PageState0 = EEPROM_GetPageState(EEPROM_PAGE0_START_ADDR);
        if (u32PageState0 == EEPROM_PAGE_STATE_VALID)
        {
            break;
        }
    }

    /* Get Page1 state */
    for (u32Idx = 0; u32Idx < 3U; u32Idx++)
    {
        u32PageState1 = EEPROM_GetPageState(EEPROM_PAGE1_START_ADDR);
        if (u32PageState1 == EEPROM_PAGE_STATE_VALID)
        {
            break;
        }
    }

    /* Get Page2 status */
    for (u32Idx = 0; u32Idx < 3U; u32Idx++)
    {
        u32PageState2 = EEPROM_GetPageState(EEPROM_PAGE2_START_ADDR);
        if (u32PageState2 == EEPROM_PAGE_STATE_VALID)
        {
            break;
        }
    }


    /* Check for invalid page states and repair if necessary */
    if(u32PageState0 == EEPROM_PAGE_STATE_INVALID)
    {
        switch(u32PageState1)
        {
            case EEPROM_PAGE_STATE_INVALID:
                if(u32PageState2 == EEPROM_PAGE_STATE_VALID)           /* Page0 invalid, Page1 invalid, Page2 valid */
                {
                    /* Erase Page0 */
                    u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE0_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Erase Page1 */
                        u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE1_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = EEPROM_CreateMap(EEPROM_PAGE2_START_ADDR);
                    }

                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        u32EepromStatus = EEPROM_VerifyTransferPage();
                    }
                }
                else /* Invalid state - Page0 invalid, Page1 invalid, Page2 invalid */
                {
                    /* Set invalid header flag */
                    u32EepromStatus = EEPROM_STATUS_INVALID_HEADER;
                }
                break;

            case EEPROM_PAGE_STATE_VALID:
                if(u32PageState2 == EEPROM_PAGE_STATE_INVALID) /* Page0 invalid, Page1 valid, Page2 invalid */
                {
                    /* Erase Page0 */
                    u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE0_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Erase Page2 */
                        u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE2_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = EEPROM_CreateMap(EEPROM_PAGE1_START_ADDR);
                    }

                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        u32EepromStatus = EEPROM_VerifyTransferPage();
                    }
                }
                else        /* Page0 invalid, Page1 valid, Page2 valid */
                {
                    /* Erase Page0 */
                    u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE0_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Erase Page1 */
                        u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE1_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = EEPROM_CreateMap(EEPROM_PAGE2_START_ADDR);
                    }
                }
                break;

            default:  /* Any other state */
              /* TODO Nothing*/
                break;
        }
    }
    else if(u32PageState0 == EEPROM_PAGE_STATE_VALID)
    {
        switch(u32PageState1)
        {
            case EEPROM_PAGE_STATE_INVALID:
                if(u32PageState2 == EEPROM_PAGE_STATE_INVALID)   /* Page0 valid, Page1 invalid, Page2 invalid */
                {
                    /* Erase Page1 */
                    u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE1_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Erase Page2 */
                        u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE2_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = EEPROM_CreateMap(EEPROM_PAGE0_START_ADDR);
                    }

                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        u32EepromStatus = EEPROM_VerifyTransferPage();
                    }
                }
                else    /* Page0 valid, Page1 invalid, Page2 valid */
                {
                    /* Erase Page1 */
                    u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE1_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Erase Page2 */
                        u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE2_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = EEPROM_CreateMap(EEPROM_PAGE0_START_ADDR);
                    }
                }

                break;

            case EEPROM_PAGE_STATE_VALID:
                if(u32PageState2 == EEPROM_PAGE_STATE_INVALID)   /* Page0 valid, Page1 valid, Page2 invalid */
                {
                    /* Erase Page2 */
                    u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE2_START_ADDR);
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Erase Page0 */
                        u32EepromStatus = EEPROM_VerifyErasePage(EEPROM_PAGE0_START_ADDR);
                    }
                    
                    if(u32EepromStatus == EEPROM_STATUS_OK)
                    {
                        /* Init EEPROM Registers */
                        u32EepromStatus = EEPROM_CreateMap(EEPROM_PAGE1_START_ADDR);
                    }
                }
                else    /* Invalid state - Page0 valid, Page1 valid, Page2 valid */
                {
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

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Erases EEPROM pages and Select a page as VALID
 *
 * @param[in]  none
 *
 * @return     - EEPROM_STATUS_OK         : If format success
 *             - EEPROM_STATUS_ERASE_ERROR: If Flash erase error
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR: If set page header error
 *
 ******************************************************************************/
uint32_t EEPROM_Format(void)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    uint32_t i;
    uint32_t u32Code = 0U;
    uint32_t u32Page = EEPROM_PAGE_0;


    /* Erase Page0 */
    status = pHWLIB->FLASHC_VerifyErase(EEPROM_PAGE0_START_ADDR, EEPROM_PAGE_SIZE);
    if(status != FLASH_OP_SUCCESS)
    {
        u32EepromStatus = EEPROM_ErasePage(EEPROM_PAGE0_START_ADDR);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            status = pHWLIB->FLASHC_VerifyErase(EEPROM_PAGE0_START_ADDR, EEPROM_PAGE_SIZE);
            if(status != FLASH_OP_SUCCESS)
            {
                u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
            }
        }
    }
    else
    {
        u32Code |= 0x4U;
    }

    if (u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Erase Page1 */
        status = pHWLIB->FLASHC_VerifyErase(EEPROM_PAGE1_START_ADDR, EEPROM_PAGE_SIZE);
        if(status != FLASH_OP_SUCCESS)
        {
            u32EepromStatus = EEPROM_ErasePage(EEPROM_PAGE1_START_ADDR);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                status = pHWLIB->FLASHC_VerifyErase(EEPROM_PAGE1_START_ADDR, EEPROM_PAGE_SIZE);
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
    }

    if (u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Erase Page2 */
        status = pHWLIB->FLASHC_VerifyErase(EEPROM_PAGE2_START_ADDR, EEPROM_PAGE_SIZE);
        if(status != FLASH_OP_SUCCESS)
        {
            u32EepromStatus = EEPROM_ErasePage(EEPROM_PAGE2_START_ADDR);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                status = pHWLIB->FLASHC_VerifyErase(EEPROM_PAGE2_START_ADDR, EEPROM_PAGE_SIZE);
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
                u32Page = EEPROM_PAGE_0;
                break;

            case 1:
                u32Page = EEPROM_PAGE_2;
                break;

            case 2:
                u32Page = EEPROM_PAGE_1;
                break;

            case 3:
                u32Page = EEPROM_PAGE_1;
                break;

            case 4:
                u32Page = EEPROM_PAGE_0;
                break;

            case 5:
                u32Page = EEPROM_PAGE_2;
                break;

            case 6:
                u32Page = EEPROM_PAGE_0;
                break;

            case 7:
                u32Page = EEPROM_PAGE_1;
                break;

            default:
                u32Page = EEPROM_PAGE_2;
                break;
        }


        /* Enable EEPROM register write access */
        EEPROM->EEPROMREGKEY = 0xFEEDBEEFU;
        EEPROM->EEPROMREGKEY = 0x1ACCE551U;

        /* Reset EEPROM register */
        for (i = 0U; i < EEPROM_NUM_OF_VAR; i++)
        {
            EEPROM->EEPROMENTRYADDR[i] = EEPROM_DEFAULT_ENTRY_REG_VAL;
        }

        EEPROM->EEPROMNEXTADDR = EEPROM_PAGE0_START_ADDR + (u32Page * EEPROM_PAGE_SIZE) + EEPROM_HEADER_SIZE;

        /* Disable EEPROM register write access */
        EEPROM->EEPROMREGKEY = 0U;

        /* Set Page in VALID state */
        u32EepromStatus = EEPROM_SetPageState((EEPROM_PAGE0_START_ADDR + (u32Page * EEPROM_PAGE_SIZE)));
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Init EEPROM according to a active page
 *
 * @param[in]  u32ActivePageBase:  Active page start address
 *
 * @return     - EEPROM_STATUS_OK               : if format success
 *             - EEPROM_STATUS_PARITY_ERROR     : if parity check fail
 *             - EEPROM_STATUS_INVALID_ADDR     : if variable address is invalid
 *
 ******************************************************************************/
uint32_t EEPROM_CreateMap(uint32_t u32ActivePageBase)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* The start address of page */
    uint32_t u32PageStartAddr;
    /* The element address in the page */
    uint32_t u32PageAddr;

    /* The element address and data field value */
    uint32_t u32AddrVal, u32DataVal;

    uint32_t u32Temp, u32Flag;


    /* Enable EEPROM register write access */
    EEPROM->EEPROMREGKEY = 0xFEEDBEEFU;
    EEPROM->EEPROMREGKEY = 0x1ACCE551U;

    /* Init next entry address - Assume that current active page is full */
    EEPROM->EEPROMNEXTADDR = u32ActivePageBase + EEPROM_PAGE_SIZE;

    /* Reset EEPROM register */
    for(u32Temp = 0U; u32Temp < EEPROM_NUM_OF_VAR; u32Temp++)
    {
        EEPROM->EEPROMENTRYADDR[u32Temp] = EEPROM_DEFAULT_ENTRY_REG_VAL;
    }

    /* Get the active page start address */
    u32PageStartAddr = (uint32_t)(u32ActivePageBase + EEPROM_HEADER_SIZE);

    /* Get the active page end address */
    u32PageAddr = (uint32_t)(u32ActivePageBase + EEPROM_PAGE_SIZE - 8U);

    u32Flag = 0U;
    /* Check each active page address starting from end */
    while(u32PageAddr >= u32PageStartAddr)
    {
        /* Get the address of Variable address-field */
        u32Temp = u32PageAddr + 4U;

        /* Get current location content */
        u32DataVal = GET_EEPROM_DATA(u32PageAddr);
        u32AddrVal = GET_EEPROM_DATA(u32Temp);

        /* Check the content */
        if((u32DataVal == 0xFFFFFFFFU) && (u32AddrVal == 0xFFFFFFFFU))
        {
            /* Dirty element not found */
            if(u32Flag == 0U)
            {
                /* Empty entry */
                EEPROM->EEPROMNEXTADDR = u32PageAddr;
            }
        }
        else
        {
            /* Dirty element found */
            u32Flag = 1U;

            /* Check entry parity */
            u32EepromStatus = EEPROM_CheckElementParity(u32AddrVal, u32DataVal);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                /* Real variable address */
                u32AddrVal &= 0x0000FFFFU;

                /* Check variable address */
                if(u32AddrVal < EEPROM_NUM_OF_VAR)
                {
                    /* If the first variable record, update variable entry address register */
                    if(EEPROM->EEPROMENTRYADDR[u32AddrVal] == EEPROM_DEFAULT_ENTRY_REG_VAL)
                    {
                        EEPROM->EEPROMENTRYADDR[u32AddrVal] = u32PageAddr;
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

    /* Disable EEPROM register write access */
    EEPROM->EEPROMREGKEY = 0U;

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Find suitable page for read/write operation
 *
 * @param[in]  none
 *
 * @return     - Page index       : if success (EEPROM_PAGE_0 ~ EEPROM_PAGE_2)
 *             - EEPROM_PAGE_NONE : if an error occurs
 *
 ******************************************************************************/
uint32_t EEPROM_FindPage(void)
{
    uint32_t u32PageIndex;
    uint32_t u32PageState0 = 0U;
    uint32_t u32PageState1 = 0U;
    uint32_t u32PageState2 = 0U;


    /* Get Page0 state */
    u32PageState0 = EEPROM_GetPageState(EEPROM_PAGE0_START_ADDR);

    /* Get Page1 state */
    u32PageState1 = EEPROM_GetPageState(EEPROM_PAGE1_START_ADDR);

    /* Get Page2 state */
    u32PageState2 = EEPROM_GetPageState(EEPROM_PAGE2_START_ADDR);


    if (u32PageState0 == EEPROM_PAGE_STATE_VALID)
    {
        u32PageIndex = EEPROM_PAGE_0;     /* Page0 valid */
    }
    else if(u32PageState1 == EEPROM_PAGE_STATE_VALID)
    {
        u32PageIndex = EEPROM_PAGE_1;     /* Page1 valid */
    }
    else if(u32PageState2 == EEPROM_PAGE_STATE_VALID)
    {
        u32PageIndex = EEPROM_PAGE_2;     /* Page2 valid */
    }
    else
    {
        u32PageIndex = EEPROM_PAGE_NONE;  /* No suitable page found */
    }

    return u32PageIndex;
}









/******************************************************************************
 * @brief      Verify if pages are full,
 *             then if not the case, writes variable in EEPROM
 *
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
uint32_t EEPROM_VerifyPageFullWrite(uint32_t u32Addr, uint32_t u32Data, uint32_t u32TransferFlag)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Active page for write operation */
    uint32_t u32Page = EEPROM_PAGE_0;

    /* The start and end address of the active page */
    uint32_t u32StartAddr, u32EndAddr;
    /* Entry address for write */
    uint32_t u32EntryAddr, u32EntryAddrH;
    /* Element address and data field value */
    uint32_t u32AddrVal, u32DataVal;

    uint32_t u32Temp;


    /* Check the variable address */
    if (u32Addr < EEPROM_NUM_OF_VAR)
    {
        /* Get active page for write operation */
        u32Page = EEPROM_FindPage();

        /* Check if there is no active page */
        if (u32Page == EEPROM_PAGE_NONE)
        {
            u32EepromStatus = EEPROM_STATUS_NO_PAGE_FOUND;
        }
        else
        {
            /* For page transfer operation */
            if (u32TransferFlag == 1U)
            {
                /* Page to receive data */
                if (u32Page == EEPROM_PAGE_2)
                {
                    u32Page = EEPROM_PAGE_0;
                }
                else
                {
                    u32Page = u32Page + 1U;
                }
            }

            /* Get entry address for write */
            u32EntryAddr = EEPROM->EEPROMNEXTADDR;

            /* Get the active page start address */
            u32StartAddr = (uint32_t)((EEPROM_START_ADDR + EEPROM_HEADER_SIZE) + (uint32_t)(u32Page * EEPROM_PAGE_SIZE));

            /* Get the active page end address */
            u32EndAddr = (uint32_t)((EEPROM_START_ADDR - 8U) + (uint32_t)((1U + u32Page) * EEPROM_PAGE_SIZE));

            /* Check entry address */
            if ( (u32EntryAddr >= u32StartAddr) && (u32EntryAddr <= u32EndAddr) )
            {
                /* Enable EEPROM register write access */
                EEPROM->EEPROMREGKEY = 0xFEEDBEEFU;
                EEPROM->EEPROMREGKEY = 0x1ACCE551U;

                /* Update next entry address for write at first */
                EEPROM->EEPROMNEXTADDR = u32EntryAddr + 8U;

                /* Get the address of Variable address-field */
                u32EntryAddrH = u32EntryAddr + 4U;

                /* Get the current location content */
                u32AddrVal = GET_EEPROM_DATA(u32EntryAddrH);
                u32DataVal = GET_EEPROM_DATA(u32EntryAddr);

                /* Verify if current location is empty */
                if((u32DataVal == 0xFFFFFFFFU) && (u32AddrVal == 0xFFFFFFFFU))
                {
                    /* Calculate element parity */
                    u32Temp = (uint32_t)EEPROM_CalElementParity(u32Addr, u32Data);

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
                        u32AddrVal = GET_EEPROM_DATA(u32EntryAddrH);
                        u32DataVal = GET_EEPROM_DATA(u32EntryAddr);

                        /* Check written data */
                        if((u32AddrVal == u32Temp) && (u32DataVal == u32Data))
                        {
                            /* Update entry address */
                            EEPROM->EEPROMENTRYADDR[u32Addr] = u32EntryAddr;

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

                /* Disable EEPROM register write access */
                EEPROM->EEPROMREGKEY = 0x0U;

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
 * @param[in]  none
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
 *             - EEPROM_STATUS_PARITY_ERROR      : if element parity check fail
 *             - EEPROM_STATUS_ADDR_MISMATCH     : if variable address is not equal
 *                                                with the address in EEPROM entry
 *
 ******************************************************************************/
uint32_t EEPROM_VerifyTransferPage(void)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    uint32_t u32Idx;

    /* New page start address */
    uint32_t u32NewPageAddr;
    /* Old page start address */
    uint32_t u32OldPageAddr;
    uint32_t u32DataVar;

    /* Check mapping result - valid page is full, perform page transfer */
    if(EEPROM->EEPROMNEXTADDR == (EEPROM_PAGE2_START_ADDR + EEPROM_PAGE_SIZE))
    {   
        /* New page address where variable will be moved to */
        u32NewPageAddr = EEPROM_PAGE0_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = EEPROM_PAGE2_START_ADDR;
    }
    /* Check mapping result - valid page is full, perform page transfer */
    else if(EEPROM->EEPROMNEXTADDR == EEPROM_PAGE2_START_ADDR)
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = EEPROM_PAGE2_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = EEPROM_PAGE1_START_ADDR;
    }
    /* Check mapping result - valid page is full, perform page transfer */
    else if(EEPROM->EEPROMNEXTADDR == EEPROM_PAGE1_START_ADDR)
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = EEPROM_PAGE1_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = EEPROM_PAGE0_START_ADDR;
    }
    else
    {
        /* Current page is not full, do not need to transfer current page to empty page. 
        Return EEPROM_STATUS_OK directly */
        return u32EepromStatus;
    }

    /* Enable EEPROM register write access */
    EEPROM->EEPROMREGKEY = 0xFEEDBEEFU;
    EEPROM->EEPROMREGKEY = 0x1ACCE551U;

    /* Update next entry address */
    EEPROM->EEPROMNEXTADDR = u32NewPageAddr + EEPROM_HEADER_SIZE;

    /* Disable EEPROM register write access */
    EEPROM->EEPROMREGKEY = 0x0U;

    /* Transfer data from OldPage to NewPage */
    for(u32Idx = 0U; u32Idx < EEPROM_NUM_OF_VAR; u32Idx++)
    {
        /* Read the last data updates */
        u32EepromStatus = EEPROM_ReadWord(u32Idx, &u32DataVar);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            /* Transfer the data to the new active page */
            u32EepromStatus = EEPROM_VerifyPageFullWrite(u32Idx, u32DataVar, 1U);
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
        u32EepromStatus = EEPROM_SetPageState(u32NewPageAddr);
    }

    /* Erase OldPage */
    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        u32EepromStatus = EEPROM_ErasePage(u32OldPageAddr);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            status = pHWLIB->FLASHC_VerifyErase(u32OldPageAddr, EEPROM_PAGE_SIZE);
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
uint16_t EEPROM_CalElementParity(uint32_t u32Addr, uint32_t u32Data)
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
uint32_t EEPROM_CheckElementParity(uint32_t u32EntryH, uint32_t u32EntryL)
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
uint32_t EEPROM_GetPageState(uint32_t u32PageAddr)
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
        u32PageState = EEPROM_PAGE_STATE_VALID;
    }
    else
    {
        u32PageState = EEPROM_PAGE_STATE_INVALID;
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
 *             - EEPROM_STATUS_OK              : if success
 *             - EEPROM_STATUS_PAGE_HEADER_ERROR: if read-back check fail
 *
 ******************************************************************************/
uint32_t EEPROM_SetPageState(uint32_t u32PageAddr)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Set new page state to VALID state */
    status = pHWLIB->FLASHC_ProgramDWord(u32PageAddr, (uint32_t)EEPROM_PAGE_HEADER_VALID, (uint32_t)(EEPROM_PAGE_HEADER_VALID >> 32));
    if (status != FLASH_OP_SUCCESS)
    {
        u32EepromStatus = EEPROM_STATUS_PAGE_HEADER_ERROR;
    }
    else
    {
        /* Get page state information from page */
        if(EEPROM_GetPageState(u32PageAddr) != EEPROM_PAGE_STATE_VALID)
        {
            u32EepromStatus = EEPROM_STATUS_PAGE_HEADER_ERROR;
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Erase EEPROM page
 *
 * @param[in]  u32PageAddr  :  Address of the EEPROM page
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK         : if success
 *             - EEPROM_STATUS_ERASE_ERROR: if erase fail
 *
 ******************************************************************************/
uint32_t EEPROM_ErasePage(uint32_t u32PageAddr)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Erase Page */
    status = pHWLIB->FLASHC_EraseSector((u32PageAddr));
    if(status != FLASH_OP_SUCCESS)
    {
        u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      If EEPROM page is not erased, erase EEPROM page
 *
 * @param[in]  u32PageAddr  :  Address of the EEPROM page
 *
 * @return     Success or error status:
 *             - EEPROM_STATUS_OK         : if success
 *             - EEPROM_STATUS_ERASE_ERROR: if erase fail
 *
 ******************************************************************************/
uint32_t EEPROM_VerifyErasePage(uint32_t u32PageAddr)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    status = pHWLIB->FLASHC_VerifyErase(u32PageAddr, EEPROM_PAGE_SIZE);
    if(status != FLASH_OP_SUCCESS)
    {
        u32EepromStatus = EEPROM_ErasePage(u32PageAddr);
        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            status = pHWLIB->FLASHC_VerifyErase(u32PageAddr, EEPROM_PAGE_SIZE);
            if(status != FLASH_OP_SUCCESS)
            {
                u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
            }
        }
    }

    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Returns the last stored variable, if found, which correspond to
 *             the passed variable address
 *
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
 *
 ******************************************************************************/
uint32_t EEPROM_ReadWord(uint32_t u32Addr, uint32_t *pu32Data)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_NO_DATA;
    uint32_t u32Page = EEPROM_PAGE_NONE;

    /* The start address and end address of active page */
    uint32_t u32StartAddr, u32EndAddr;
    /* The element address of the variable to be read */
    uint32_t u32EntryAddr;
    /* The address value and data value of the element */
    uint32_t u32AddrVal, u32DataVal;
    uint32_t u32Temp;

    /* Check the variable address */
    if (u32Addr < EEPROM_NUM_OF_VAR)
    {
        /* Get active page for read operation */
        u32Page = EEPROM_FindPage();

        /* Check if there is no active page */
        if (u32Page == EEPROM_PAGE_NONE)
        {
            u32EepromStatus = EEPROM_STATUS_NO_PAGE_FOUND;
        }
        else
        {
            /* Get the active page start address */
            u32StartAddr = (uint32_t)((EEPROM_START_ADDR + EEPROM_HEADER_SIZE) + (uint32_t)(u32Page * EEPROM_PAGE_SIZE));

            /* Get the active page end address */
            u32EndAddr   = (uint32_t)((EEPROM_START_ADDR - 8U) + (uint32_t)((1U + u32Page) * EEPROM_PAGE_SIZE));

            /* Get EEPROM element address for read */
            u32EntryAddr = EEPROM->EEPROMENTRYADDR[u32Addr];

            /* Check the element address */
            if ((u32EntryAddr >= u32StartAddr) && (u32EntryAddr <= u32EndAddr))
            {
                /* Get the address of Variable address-field */
                u32Temp = u32EntryAddr + 4U;

                /* Get the current location content */
                u32DataVal = GET_EEPROM_DATA(u32EntryAddr);
                u32AddrVal = GET_EEPROM_DATA(u32Temp);

                /* Check element parity */
                u32EepromStatus = EEPROM_CheckElementParity(u32AddrVal, u32DataVal);
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
            else if(u32EntryAddr == EEPROM_DEFAULT_ENTRY_REG_VAL)
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

    /* Return status */
    return u32EepromStatus;
}




/******************************************************************************
 * @brief      Transfers last updated elements from full pages to
 *             empty pages in any cases
 *
 * @param[in]  none
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
uint32_t EEPROM_TransferPage(void)
{
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Active page for read operation */
    uint32_t u32Page = EEPROM_PAGE_0;

    uint32_t u32Idx;
    uint32_t u32DataVar;

    /* New page start address */
    uint32_t u32NewPageAddr;
    /* Old page start address */
    uint32_t u32OldPageAddr;


    /* Get active page for read operation */
    u32Page = EEPROM_FindPage();

    if(u32Page == EEPROM_PAGE_2)          /* Page2 active */
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = EEPROM_PAGE0_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = EEPROM_PAGE2_START_ADDR;
    }
    else if(u32Page == EEPROM_PAGE_1)     /* Page1 active */
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = EEPROM_PAGE2_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = EEPROM_PAGE1_START_ADDR;
    }
    else if (u32Page == EEPROM_PAGE_0)    /* Page0 active */
    {
        /* New page address where variable will be moved to */
        u32NewPageAddr = EEPROM_PAGE1_START_ADDR;

        /* Old page address where variable will be taken from */
        u32OldPageAddr = EEPROM_PAGE0_START_ADDR;
    }
    else
    {
        /* No active Page */
        u32EepromStatus = EEPROM_STATUS_NO_PAGE_FOUND;
    }


    if(u32EepromStatus == EEPROM_STATUS_OK)
    {
        /* Erase the New page */
        status = pHWLIB->FLASHC_VerifyErase(u32NewPageAddr, EEPROM_PAGE_SIZE);
        if(status != FLASH_OP_SUCCESS)
        {
            u32EepromStatus = EEPROM_ErasePage(u32NewPageAddr);
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                status = pHWLIB->FLASHC_VerifyErase(u32NewPageAddr, EEPROM_PAGE_SIZE);
                if(status != FLASH_OP_SUCCESS)
                {
                    u32EepromStatus = EEPROM_STATUS_ERASE_ERROR;
                }
            }
        }

        if(u32EepromStatus == EEPROM_STATUS_OK)
        {
            /* Enable EEPROM register write access */
            EEPROM->EEPROMREGKEY = 0xFEEDBEEFU;
            EEPROM->EEPROMREGKEY = 0x1ACCE551U;

            /* Update next entry address */
            EEPROM->EEPROMNEXTADDR = u32NewPageAddr + EEPROM_HEADER_SIZE;

            /* Disable EEPROM register write access */
            EEPROM->EEPROMREGKEY = 0x0U;

            /* Transfer process: transfer variable from old to the new active page */
            for(u32Idx = 0U; u32Idx < EEPROM_NUM_OF_VAR; u32Idx++)
            {
                /* Read the other last varaible updates */
                u32EepromStatus = EEPROM_ReadWord(u32Idx, &u32DataVar);
                if(u32EepromStatus == EEPROM_STATUS_OK)
                {
                    /* Transfer the data to the new active page */
                    u32EepromStatus = EEPROM_VerifyPageFullWrite(u32Idx, u32DataVar, 1U);
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
                u32EepromStatus = EEPROM_SetPageState(u32NewPageAddr);
            }

            /* Erase the old page: Set old page state to INVALID state */
            if(u32EepromStatus == EEPROM_STATUS_OK)
            {
                u32EepromStatus = EEPROM_ErasePage(u32OldPageAddr);
                if(u32EepromStatus == EEPROM_STATUS_OK)
                {
                    /* Verify Erase */
                    status = pHWLIB->FLASHC_VerifyErase(u32OldPageAddr, EEPROM_PAGE_SIZE);
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
 *
 ******************************************************************************/
uint32_t EEPROM_WriteWord(uint32_t u32Addr, uint32_t u32Data)
{
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;

    /* Write the varaiable address and value in the EEPROM */
    u32EepromStatus = EEPROM_VerifyPageFullWrite(u32Addr, u32Data, 0U);

    /* In case the EEPROM active page is full */
    if((u32EepromStatus & EEPROM_STATUS_PAGE_FULL) == EEPROM_STATUS_PAGE_FULL)
    {
        if ((u32EepromStatus & EEPROM_STATUS_OK) == EEPROM_STATUS_OK)
        {
            /* Perform page transfer */
            u32EepromStatus = EEPROM_TransferPage();
            if(u32EepromStatus != EEPROM_STATUS_OK)
            {
                u32EepromStatus |= EEPROM_STATUS_TRANSFER_ERROR;
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

