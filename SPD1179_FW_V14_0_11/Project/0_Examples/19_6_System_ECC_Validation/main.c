/******************************************************************************
 * @file     main.c
 * @brief    Main program body
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


#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif

#include <stdio.h>
#include <stdlib.h>


/**
 *  @brief  Software forced memory access error options
 */
typedef enum
{
    READ_ROM_ERROR          = (1U << 0 ),   /* Error when read ROM              */
    READ_FLASH_ERROR        = (1U << 1 ),   /* Error when read FLASH            */
    READ_RAM0_ERROR         = (1U << 2 ),   /* Error when read RAM0             */
    READ_RAM1_ERROR         = (1U << 3 ),   /* Error when read RAM1             */
    READ_CAN_ERROR          = (1U << 4 ),   /* Error when read CAN              */

    WRITE_FLASH_ERROR       = (1U << 17),   /* Error when write FLASH           */
    WRITE_RAM0_ERROR        = (1U << 18),   /* Error when write RAM0            */
    WRITE_RAM1_ERROR        = (1U << 19),   /* Error when write RAM1            */
    WRITE_CAN_ERROR         = (1U << 20),   /* Error when write CAN             */

    MEMORY_ACCESS_ERROR_ALL = 0x001E001FU   /* All memory access error          */
} ENGR_MemoryAccessErrorEnum;


uint32_t u32Addr;
uint32_t u32IntCnt;
uint32_t u32IntEvt;
ErrorStatus status = SUCCESS;


/******************************************************************************
 * @brief      Enable write access to the protected ENGR registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_WALLOW()                                                          \
    WRITE_REG(*((__IO uint32_t*)(uint32_t)0x40000F70), 0x1ACCE551U)




/******************************************************************************
 * @brief      Force bit error pattern
 *
 * @param[in]  u8Idx  :  Bit range selection to force the memory error
 *                       0 - Bit [31: 0]
 *                       1 - Bit [63:32]
 *                       2 - Bit [95:64]
 * @param[in]  u32Pat :  Bit error pattern for the selected 32-bit
 *                       0 - Do not force errror on the bit
 *                       1 - Force error on the bit
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_ForceMemoryErrorPattern(u8Idx, u32Pat)                            \
    WRITE_REG(*((__IO uint32_t*)(uint32_t)(0x40000F58 + 4 * (u8Idx))), (u32Pat))




/******************************************************************************
 * @brief      Force memory access error
 *
 * @param[in]  eErr: Select the memory access type to force the error
 *                   Please refer to ENGR_MemoryAccessErrorEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_ForceMemoryAccessError(eErr)                                      \
    SET_BITS(*((__IO uint32_t*)(uint32_t)0x40000F64), (eErr))




void ROM_ReadErrorIntCheck(uint32_t u32Base, uint32_t u32Size, 
    uint8_t u8ErrorBitNum, uint32_t u32Access)
{
    uint32_t    i;
    uint32_t    u32Bit0;
    uint32_t    u32Bit1;

    u32IntCnt = 0U;
    ENGR_WALLOW();

    for (i = 0U; i < 3U; i++)
    {
        /* Select the test address */
        switch (rand() & 7U)
        {
            case 0U:    
                u32Addr = u32Base;                          
                break;
            case 1U:    
                u32Addr = u32Base + u32Size - 1U;           
                break;
            default:    
                u32Addr = ((rand() % u32Size) + u32Base);   
                break;
        }

        /* Generate error data */
        if (u8ErrorBitNum == 1U)
        {
            u32Bit0 = rand() % 39U;
            ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
        }
        if (u8ErrorBitNum == 2U)
        {
            do
            {
                u32Bit0 = rand() % 39U;
                u32Bit1 = rand() % 39U;
            } while (u32Bit0 == u32Bit1);
            if ((u32Bit0 >> 5) == (u32Bit1 >> 5))
            {
                ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 
                (1U << (u32Bit0 & 31U)) | (1U << (u32Bit1 & 31U)));
            }
            else
            {
                ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
                ENGR_ForceMemoryErrorPattern(u32Bit1 >> 5, 1U << (u32Bit1 & 31U));
            }
        }
        
        /* Force error event */
        ENGR_ForceMemoryAccessError(u32Access);

        /* Read from test address */
        switch (i)
        {
            case 0U:                        
                SYSTEM_SetNVREG1(*((__IO uint8_t *)(uint32_t)u32Addr)); 
                break;
            case 1U: 
                u32Addr &= 0xfffffffe; 
                SYSTEM_SetNVREG1(*((__IO uint16_t*)(uint32_t)u32Addr));
                break;
            case 2U: 
                u32Addr &= 0xfffffffc; 
                SYSTEM_SetNVREG1(*((__IO uint32_t*)(uint32_t)u32Addr)); 
                break;
            case 3U: 
                u32Addr &= 0xfffffff8; 
                SYSTEM_SetNVREG1(*((__IO uint64_t*)(uint32_t)u32Addr));
                break;
        }
        while (u32IntCnt == i);
    }
}



void RAM_AccessErrorIntCheck(uint32_t u32Base, uint32_t u32Size, 
    uint8_t u8ErrorBitNum, uint32_t u32Access)
{
    uint32_t    i;
    uint32_t    u32Byte;
    uint32_t    u32Bit0;
    uint32_t    u32Bit1;

    u32IntCnt = 0U;
    ENGR_WALLOW();

    for (i = 0U; i < 3U; i++)
    {
        /* Select the test address */
        switch (rand() & 7U)
        {
            case 0U:    
                u32Addr = u32Base;                          
                break;
            case 1U:    
                u32Addr = u32Base + u32Size - 1U;           
                break;
            default:    
                u32Addr = ((rand() % u32Size) + u32Base);   
                break;
        }

        switch (i)
        {
            case 0U:                            
                break;
            case 1U: u32Addr &= 0xfffffffeU;    
                break;
            case 2U: u32Addr &= 0xfffffffcU;    
                break;
            case 3U: u32Addr &= 0xfffffff8U;    
                break;
        }

        /* Save test address to NVREG0 */
        SYSTEM_SetNVREG0(u32Addr);
        
        /* Generate error data */
        if (u8ErrorBitNum == 1U)
        {
            u32Bit0 = rand() % 13U;
            u32Bit0 += (u32Addr & 0x3) * 13U;
            u32Bit0 += (rand() % (1 << i)) * 13U;
            ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
        }
        if (u8ErrorBitNum == 2U)
        {
            do
            {
                u32Byte = rand() % (1 << i);
                u32Bit0 = rand() % 13U;
                u32Bit1 = rand() % 13U;
                u32Bit0 += (u32Addr & 0x3) * 13U;
                u32Bit1 += (u32Addr & 0x3) * 13U;
                u32Bit0 += u32Byte * 13U;
                u32Bit1 += u32Byte * 13U;
            } while (u32Bit0 == u32Bit1);
            if ((u32Bit0 >> 5) == (u32Bit1 >> 5))
            {
                ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 
                (1U << (u32Bit0 & 31U)) | (1U << (u32Bit1 & 31U)));
            }
            else
            {
                ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
                ENGR_ForceMemoryErrorPattern(u32Bit1 >> 5, 1U << (u32Bit1 & 31U));
            }
        }
        
        /* Force error event */
        ENGR_ForceMemoryAccessError(u32Access); 
        
        /* Write data to test address */
        /* Read data from test address */
        switch (i)
        {
            case 0U: 
                *((__IO uint8_t *)(uint32_t)SYSTEM_GetNVREG0()) = rand(); 
                SYSTEM_SetNVREG0(*((__IO uint8_t *)(uint32_t)SYSTEM_GetNVREG0()));
                break;
            case 1U: 
                *((__IO uint16_t*)(uint32_t)SYSTEM_GetNVREG0()) = rand(); 
                SYSTEM_SetNVREG0(*((__IO uint16_t*)(uint32_t)SYSTEM_GetNVREG0())); 
                break;
            case 2U: 
                *((__IO uint32_t*)(uint32_t)SYSTEM_GetNVREG0()) = rand(); 
                SYSTEM_SetNVREG0(*((__IO uint32_t*)(uint32_t)SYSTEM_GetNVREG0())); 
                break;
            case 3U: 
                *((__IO uint64_t*)(uint32_t)SYSTEM_GetNVREG0()) = rand(); 
                SYSTEM_SetNVREG0(*((__IO uint64_t*)(uint32_t)SYSTEM_GetNVREG0())); 
                break;
        }
        while (u32IntCnt == i);
        switch (i)
        {
            case 0U:    
                *((__IO uint8_t *)(uint32_t)u32Addr) = 0;  
                break;
            case 1U:    
                *((__IO uint16_t*)(uint32_t)u32Addr) = 0;   
                break;
            case 2U:    
                *((__IO uint32_t*)(uint32_t)u32Addr) = 0;   
                break;
            case 3U:    
                *((__IO uint64_t*)(uint32_t)u32Addr) = 0;   
                break;
        }
    }
}




void FLASH_AccessErrorIntCheck(uint32_t u32Base, uint32_t u32Size, 
    uint8_t u8ErrorBitNum, uint32_t u32Access)
{
    uint32_t    i;
    uint32_t    u32Bit0;
    uint32_t    u32Bit1;

    u32IntCnt = 0U;
    ENGR_WALLOW();

    /* Erase sector */
    pHWLIB->FLASHC_EraseSector(u32Base);

    /* Generate error data */
    if (u8ErrorBitNum == 1U)
    {
        u32Bit0 = rand() % 72U;
        ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
    }
    if (u8ErrorBitNum == 2U)
    {
        do
        {
            u32Bit0 = rand() % 72U;
            u32Bit1 = rand() % 72U;
        } while (u32Bit0 == u32Bit1);
        if ((u32Bit0 >> 5) == (u32Bit1 >> 5))
        {
            ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 
            (1U << (u32Bit0 & 31U)) | (1U << (u32Bit1 & 31U)));
        }
        else
        {
            ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
            ENGR_ForceMemoryErrorPattern(u32Bit1 >> 5, 1U << (u32Bit1 & 31U));
        }
    }
    
    /* Select the test address */
    switch (rand() & 7U)
    {
        case 0U:    
            u32Addr = u32Base;                          
            break;
        case 1U:    
            u32Addr = u32Base + u32Size - 1U;           
            break;
        default:    
            u32Addr = ((rand() % u32Size) + u32Base);   
            break;
    }
    u32Addr = u32Addr & 0xfffffff8U;
    
    /* Force error event */
    ENGR_ForceMemoryAccessError(u32Access);
    
    /* Flash write */
    pHWLIB->FLASHC_ProgramDWord(u32Addr, rand(), rand());
    
    /* Do not force errror on the bit */
    ENGR_ForceMemoryErrorPattern(0, 0);
    ENGR_ForceMemoryErrorPattern(1, 0);
    ENGR_ForceMemoryErrorPattern(2, 0);

    for (i = 0U; i < 3U; i++)
    {
        /* Select the test address */
        switch (i)
        {
            case 0U: 
                SYSTEM_SetNVREG0(u32Addr + ( rand() & 7U      ));  
                break;
            case 1U: 
                SYSTEM_SetNVREG0(u32Addr + ((rand() & 3U) << 1));  
                break;
            case 2U: 
                SYSTEM_SetNVREG0(u32Addr + ((rand() & 1U) << 2));  
                break;
        }
        
        /* Generate error data */
        if (u8ErrorBitNum == 1U)
        {
            u32Bit0 = rand() % 72U;
            ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
        }
        if (u8ErrorBitNum == 2U)
        {
            do
            {
                u32Bit0 = rand() % 72U;
                u32Bit1 = rand() % 72U;
            } while (u32Bit0 == u32Bit1);
            if ((u32Bit0 >> 5) == (u32Bit1 >> 5))
            {
                ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 
                (1U << (u32Bit0 & 31U)) | (1U << (u32Bit1 & 31U)));
            }
            else
            {
                ENGR_ForceMemoryErrorPattern(u32Bit0 >> 5, 1U << (u32Bit0 & 31U));
                ENGR_ForceMemoryErrorPattern(u32Bit1 >> 5, 1U << (u32Bit1 & 31U));
            }
        }
        
        /* Force error event */
        ENGR_ForceMemoryAccessError(u32Access);
        
        /* Read data from test address */
        switch (i)
        {
            case 0U: 
                SYSTEM_SetNVREG0(*((__IO uint8_t *)(uint32_t)SYSTEM_GetNVREG0())); 
                break;
            case 1U: 
                SYSTEM_SetNVREG0(*((__IO uint16_t*)(uint32_t)SYSTEM_GetNVREG0()));
                break;
            case 2U: 
                SYSTEM_SetNVREG0(*((__IO uint32_t*)(uint32_t)SYSTEM_GetNVREG0())); 
                break;
            case 3U: 
                SYSTEM_SetNVREG0(*((__IO uint64_t*)(uint32_t)SYSTEM_GetNVREG0())); 
                break;
        }
        while (u32IntCnt == i);
    }
}




/************************************************************************
 *
 * @brief      In this case, code and data in RAM1, 
 *             test Flash, ROM, RAM0 ECC error.      
 *
 * @KeyPoint   :   None
 *
 * @TestMethod :   Run code
 * 
 * @TestResult :   Serial display "Test success" 
 *
 ************************************************************************/
int main(void)
{
    uint32_t u32SectorAddr;
    status = SUCCESS;
    
    CLOCK_InitWithRCO(100000000);
    
    Delay_Init();

    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    printf("Just a Sample....\n");
    
    /* Enable MEM_IRQHandler */
    NVIC_EnableIRQ(MEM_IRQn);
    
    /* Disable all Reset Event */
    SYSTEM_DisableResetEvent    (RESET_EVENT_ALL);
    
    /* Disable NMI and Memory Int */
    SYSTEM_DisableNonMaskableInt(NMI_EVENT_ALL);
    SYSTEM_DisableMemoryInt     (MEM_INT_ALL);
    
    /* Enable NMI and Memory Int */
    SYSTEM_EnableNonMaskableInt ( NMI_EVENT_ROM_MULTI_BIT_ERROR
                                | NMI_EVENT_RAM0_MULTI_BIT_ERROR
                                | NMI_EVENT_RAM1_MULTI_BIT_ERROR
                                | NMI_EVENT_FLASH_MULTI_BIT_ERROR
                                );
    SYSTEM_EnableMemoryInt      ( MEM_INT_ROM_SINGLE_BIT_ERROR
                                | MEM_INT_RAM0_SINGLE_BIT_ERROR
                                | MEM_INT_RAM1_SINGLE_BIT_ERROR
                                | MEM_INT_FLASH_SINGLE_BIT_ERROR
                                );
 

    u32SectorAddr = 0x1000F000;
    
    /* Single-bit error during read */
    u32IntEvt = MEM_INT_FLASH_SINGLE_BIT_ERROR;
    FLASH_AccessErrorIntCheck(u32SectorAddr, 0x1000, 1, READ_FLASH_ERROR);

    /* Single-bit error during write */
    u32IntEvt = MEM_INT_FLASH_SINGLE_BIT_ERROR;
    FLASH_AccessErrorIntCheck(u32SectorAddr, 0x1000, 1, WRITE_FLASH_ERROR);
    
    /* ROM: Read single bit error */
    u32IntEvt = MEM_INT_ROM_SINGLE_BIT_ERROR;
    ROM_ReadErrorIntCheck   (0x00001000U, 0x40, 1, READ_ROM_ERROR);
    
    /* RAM1: Read single bit error */
    u32IntEvt = MEM_INT_RAM0_SINGLE_BIT_ERROR;
    RAM_AccessErrorIntCheck (0x1fffb000U, 0x1000, 1, READ_RAM0_ERROR);

    /* RAM1: Write single bit error */
    u32IntEvt = MEM_INT_RAM0_SINGLE_BIT_ERROR;
    RAM_AccessErrorIntCheck (0x1fffb000U, 0x1000, 1, WRITE_RAM0_ERROR);

    /* Two-bit error during read */
    u32IntEvt = NMI_EVENT_FLASH_MULTI_BIT_ERROR;
    FLASH_AccessErrorIntCheck(u32SectorAddr, 0x1000, 2, READ_FLASH_ERROR);

    /* Two-bit error during write */
    u32IntEvt = NMI_EVENT_FLASH_MULTI_BIT_ERROR;
    FLASH_AccessErrorIntCheck(u32SectorAddr, 0x1000, 2, WRITE_FLASH_ERROR);
    
    /* ROM: Read multi bit error */
    u32IntEvt = NMI_EVENT_ROM_MULTI_BIT_ERROR;
    ROM_ReadErrorIntCheck   (0x00001000U, 0x40, 2, READ_ROM_ERROR);

    /* RAM1: Read multi bit error */
    u32IntEvt = NMI_EVENT_RAM0_MULTI_BIT_ERROR;
    RAM_AccessErrorIntCheck (0x1fffb000U, 0x1000, 2, READ_RAM0_ERROR);

    /* RAM1: Write multi bit error */
    u32IntEvt = NMI_EVENT_RAM0_MULTI_BIT_ERROR;
    RAM_AccessErrorIntCheck (0x1fffb000U, 0x1000, 2, WRITE_RAM0_ERROR);

    if (status == SUCCESS)
    {
        printf("Test success\n");
    }

    while (1)
    {
    }
}




void MEM_IRQHandler(void)
{
    uint32_t u32ErrorAddr = 0;

    if (SYSTEM_GetMemoryIntFlag(MEM_INT_ALL) != (u32IntEvt | MEM_INT_GLOBAL))
    {
        status = ERROR;
        printf("MEMIF: Expect 0x%08x but read 0x%08x\n", 
        u32IntEvt | MEM_INT_GLOBAL, SYSTEM_GetMemoryIntFlag(MEM_INT_ALL));
    }

    switch(u32IntEvt)
    {
        case (MEM_INT_ROM_SINGLE_BIT_ERROR):    
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_ROM);      
            break;
        case (MEM_INT_RAM0_SINGLE_BIT_ERROR):   
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_RAM0);    
            break;
        case (MEM_INT_RAM1_SINGLE_BIT_ERROR):   
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_RAM1);     
            break;
        case (MEM_INT_FLASH_SINGLE_BIT_ERROR):  
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_FLASH);    
            break;
    }

    if (u32ErrorAddr != u32Addr)
    {
        status = ERROR;
        printf("ECC error should be detected at 0x%08x, not 0x%08x\n", 
        u32Addr, u32ErrorAddr);
    }

    u32IntCnt++;
    
    SYSTEM_ClearMemoryInt(MEM_INT_GLOBAL | u32IntEvt);
}




void NMI_Handler(void)
{
    uint32_t u32ErrorAddr = 0;

    if (SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_ALL) != (u32IntEvt | NMI_EVENT_GLOBAL))
    {
        status = ERROR;
        printf("NMIF: Expect 0x%08x but read 0x%08x\n", 
        u32IntEvt | NMI_EVENT_GLOBAL, SYSTEM_GetNonMaskableIntFlag(NMI_EVENT_ALL));
    }

    switch(u32IntEvt)
    {
        case (NMI_EVENT_ROM_MULTI_BIT_ERROR):   
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_ROM);      
            break;
        case (NMI_EVENT_RAM0_MULTI_BIT_ERROR):  
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_RAM0);     
            break;
        case (NMI_EVENT_RAM1_MULTI_BIT_ERROR):  
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_RAM1);     
            break;
        case (NMI_EVENT_FLASH_MULTI_BIT_ERROR): 
            u32ErrorAddr = SYSTEM_GetMemErrorAddress(MEM_FLASH);    
            break;
    }

    if (u32ErrorAddr != u32Addr)
    {
        status = ERROR;
        printf("ECC error should be detected at 0x%08x, not 0x%08x\n", 
        u32Addr, u32ErrorAddr);
    }

    u32IntCnt++;
    
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_GLOBAL | u32IntEvt);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
