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
#include "spd1179.h"
#include "eeprom_lib.h"
#include <stdio.h>

#define FLASH_SECTOR_ADDR                        ((uint32_t)(0x1000F000))

/* EEPROM Page0 start and end address */
#define EEPROM_PAGE0_NEXTADDR_START_ADDR         ((uint32_t)(EEPROM_PAGE0_START_ADDR + EEPROM_HEADER_SIZE))
#define EEPROM_PAGE0_NEXTADDR_END_ADDR           ((uint32_t)(EEPROM_PAGE0_START_ADDR + EEPROM_PAGE_SIZE - EEPROM_ELEMENT_SIZE))

/* EEPROM Page1 start and end address */
#define EEPROM_PAGE1_NEXTADDR_START_ADDR         ((uint32_t)(EEPROM_PAGE1_START_ADDR + EEPROM_HEADER_SIZE))
#define EEPROM_PAGE1_NEXTADDR_END_ADDR           ((uint32_t)(EEPROM_PAGE1_START_ADDR + EEPROM_PAGE_SIZE - EEPROM_ELEMENT_SIZE))

/* EEPROM Page2 start and end address */
#define EEPROM_PAGE2_NEXTADDR_START_ADDR         ((uint32_t)(EEPROM_PAGE2_START_ADDR + EEPROM_HEADER_SIZE))
#define EEPROM_PAGE2_NEXTADDR_END_ADDR           ((uint32_t)(EEPROM_PAGE2_START_ADDR + EEPROM_PAGE_SIZE - EEPROM_ELEMENT_SIZE))

#define               TOTAL_WORD_NUMBER              100

uint32_t              au32Buf[TOTAL_WORD_NUMBER  * 2] = {
                                                        1,  0x12345678, 
                                                        2,  0x55555555, 
                                                        3,  0x5a5a5a5a,
                                                        4,  0x11111111,
                                                        5,  0x22222222,
                                                        6,  0x12345678, 
                                                        7,  0x55555555, 
                                                        8,  0x5a5a5a5a,
                                                        9,  0x11111111,
                                                       10,  0x22222222,
    
                                                       11,  0x12345678, 
                                                       12,  0x55555555, 
                                                       13,  0x5a5a5a5a,
                                                       14,  0x11111111,
                                                       15,  0x22222222,
                                                       16,  0x12345678, 
                                                       17,  0x55555555, 
                                                       18,  0x5a5a5a5a,
                                                       19,  0x11111111,
                                                       20,  0x22222222,
                                                       
                                                       21,  0x12345678, 
                                                       22,  0x55555555, 
                                                       23,  0x5a5a5a5a,
                                                       24,  0x11111111,
                                                       25,  0x22222222,
                                                       26,  0x12345678, 
                                                       27,  0x55555555, 
                                                       28,  0x5a5a5a5a,
                                                       29,  0x11111111,
                                                       30,  0x22222222,
                                                       
                                                       31,  0x12345678, 
                                                       32,  0x55555555, 
                                                       33,  0x5a5a5a5a,
                                                       34,  0x11111111,
                                                       35,  0x22222222,
                                                       36,  0x12345678, 
                                                       37,  0x55555555, 
                                                       38,  0x5a5a5a5a,
                                                       39,  0x11111111,
                                                       40,  0x22222222,
                                                       
                                                       41,  0x12345678, 
                                                       42,  0x55555555, 
                                                       43,  0x5a5a5a5a,
                                                       44,  0x11111111,
                                                       45,  0x22222222,
                                                       46,  0x12345678, 
                                                       47,  0x55555555, 
                                                       48,  0x5a5a5a5a,
                                                       49,  0x11111111,
                                                       50,  0x22222222,
                                                       
                                                       51,  0x12345678, 
                                                       52,  0x55555555, 
                                                       53,  0x5a5a5a5a,
                                                       54,  0x11111111,
                                                       55,  0x22222222,
                                                       56,  0x12345678, 
                                                       57,  0x55555555, 
                                                       58,  0x5a5a5a5a,
                                                       59,  0x11111111,
                                                       60,  0x22222222,
                                                       
                                                       61,  0x12345678, 
                                                       62,  0x55555555, 
                                                       63,  0x5a5a5a5a,
                                                       64,  0x11111111,
                                                       65,  0x22222222,
                                                       66,  0x12345678, 
                                                       67,  0x55555555, 
                                                       68,  0x5a5a5a5a,
                                                       69,  0x11111111,
                                                       70,  0x22222222,
                                                       
                                                       71,  0x12345678, 
                                                       72,  0x55555555, 
                                                       73,  0x5a5a5a5a,
                                                       74,  0x11111111,
                                                       75,  0x22222222,
                                                       76,  0x12345678, 
                                                       77,  0x55555555, 
                                                       78,  0x5a5a5a5a,
                                                       79,  0x11111111,
                                                       80,  0x22222222,
                                                       
                                                       81,  0x12345678, 
                                                       82,  0x55555555, 
                                                       83,  0x5a5a5a5a,
                                                       84,  0x11111111,
                                                       85,  0x22222222,
                                                       86,  0x12345678, 
                                                       87,  0x55555555, 
                                                       88,  0x5a5a5a5a,
                                                       89,  0x11111111,
                                                       90,  0x22222222,
                                                       
                                                       91,  0x12345678, 
                                                       92,  0x55555555, 
                                                       93,  0x5a5a5a5a,
                                                       94,  0x11111111,
                                                       95,  0x22222222,
                                                       96,  0x12345678, 
                                                       97,  0x55555555, 
                                                       98,  0x5a5a5a5a,
                                                       99,  0x11111111,
                                                      100,  0x22222222,
};
uint32_t              au32BufTemp[TOTAL_WORD_NUMBER  * 2] = {0};

/* PRE-DRIVER mode ID */
uint16_t              u16PREDRIID;

/* Data read from PRE-DRIVER */
uint16_t              u16PREDRIDATA                      = 0;




/*************************************************************************************************************************
 *
 * @brief      This case show how to use VBAT under-voltage to save data
 *
 *              Key_points:
 *                        (1)Need to erase RDN0 RDN1 RDN2 to make sure the EEPROM is clean at the first time.
 *
 *************************************************************************************************************************/

ErrorStatus IdleSpaceInCurrentPage(uint32_t *pu32IdleSpace)
{
    ErrorStatus eErrorState = SUCCESS;
    
    /* Caculate the idle space in current Page */
    if ((EEPROM->EEPROMNEXTADDR  >= EEPROM_PAGE0_NEXTADDR_START_ADDR) && (EEPROM->EEPROMNEXTADDR  <= EEPROM_PAGE0_NEXTADDR_END_ADDR))
    {
        *pu32IdleSpace = ((EEPROM_PAGE0_NEXTADDR_END_ADDR - EEPROM->EEPROMNEXTADDR) >> 3) + 1;
    }
    else if ((EEPROM->EEPROMNEXTADDR  >= EEPROM_PAGE1_NEXTADDR_START_ADDR) && (EEPROM->EEPROMNEXTADDR  <= EEPROM_PAGE1_NEXTADDR_END_ADDR))
    {
        *pu32IdleSpace = ((EEPROM_PAGE1_NEXTADDR_END_ADDR - EEPROM->EEPROMNEXTADDR) >> 3) + 1;
    }
    else if ((EEPROM->EEPROMNEXTADDR  >= EEPROM_PAGE2_NEXTADDR_START_ADDR) && (EEPROM->EEPROMNEXTADDR  <= EEPROM_PAGE2_NEXTADDR_END_ADDR))
    {
        *pu32IdleSpace = ((EEPROM_PAGE2_NEXTADDR_END_ADDR - EEPROM->EEPROMNEXTADDR) >> 3) + 1;
    }
    else
    {
        eErrorState = ERROR;
    }

    return eErrorState;
}  


ErrorStatus WriteWord(uint32_t *pu32Buf, uint32_t u32NumWords)
{
    uint32_t i;
    ErrorStatus eErrorState = SUCCESS;
    uint32_t u32IdleItem  = 0;
    
    /* Caculate the idle space in current Page */
    eErrorState = IdleSpaceInCurrentPage(&u32IdleItem);

    if (eErrorState == SUCCESS)
    {
        /* If idle space is enough, write to EEPROM */
        if (u32NumWords < u32IdleItem)
        {
            for (i = 0; i < u32NumWords; i++)
            {
                EEPROM_WriteWord(pu32Buf[2*i], pu32Buf[2*i+1]);
            }
        }
        /* Write to Flash sector */
        else
        {
            pHWLIB->FLASHC_Program(pu32Buf, FLASH_SECTOR_ADDR, TOTAL_WORD_NUMBER * 2);
        }
        
    }
    return eErrorState;
}    


int main(void)
{
    ErrorStatus           eErrorState;
    FlashOperationStatus status = FLASH_OP_SUCCESS;
    uint32_t u32EepromStatus = EEPROM_STATUS_OK;
    uint32_t i;
    uint32_t j;
    uint32_t u32Timeout;
    
    CLOCK_InitWithRCO(100000000);

    Delay_Init();

    /*
     * Init the UART
     */
    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    printf("Enter the test\n");
    
    status = pHWLIB->FLASHC_Init();    
    if (status != FLASH_OP_SUCCESS)
    {
        printf("FLASHC_Init Error\n");
        return 1;
    }

    /* Init eeprom struct */
    u32EepromStatus = EEPROM_Init();
    if (u32EepromStatus != EEPROM_STATUS_OK)
    {
        if (u32EepromStatus == EEPROM_STATUS_INVALID_HEADER)
        {
            u32EepromStatus = EEPROM_Format();
            if (u32EepromStatus != EEPROM_STATUS_OK)
            {
                printf("Erases EEPROM pages and Select a page FAIL!\n");
                return 1;
            }
            else
            {
                printf("Erases EEPROM pages and Select a page as VALID SUCCESS\n");
            }
        }
        else
        {
            printf("status %x\n", status);
            
            /* Add operation here, for example MEEPROM_Format */
            u32EepromStatus = EEPROM_Format();
            if (u32EepromStatus != EEPROM_STATUS_OK)
            {
                printf("Erases EEPROM pages and Select a page FAIL!\n");
                return 1;
            }
            else
            {
                printf("Erases EEPROM pages and Select a page as VALID SUCCESS\n");
            }
        }
    }

    IdleSpaceInCurrentPage(&j);
    printf("Free space before write %d\n", j);
        
    /* Judge if need to use FLASH_SECTOR to update MEEPROM */
    status = pHWLIB->FLASHC_Read(au32BufTemp ,FLASH_SECTOR_ADDR, TOTAL_WORD_NUMBER * 2);
    if (status != FLASH_OP_SUCCESS)
    {
        printf("FLASHC_Read Error\n");
        return 1;
    }
    else
    {
        /* If first address is valid */
        if (au32BufTemp[0] != 0xFFFFFFFF)
        {
            for (i = 0; i < TOTAL_WORD_NUMBER; i++)
            {
                EEPROM_WriteWord(au32BufTemp[2*i], au32BufTemp[2*i+1]);
                printf("Write EEPROM %d %x\n", au32BufTemp[2*i], au32BufTemp[2*i+1]);
            }
        }
        
        /* Erase FLASH_SECTOR_ADDR */
        pHWLIB->FLASHC_EraseSector(FLASH_SECTOR_ADDR);
    }
    
    IdleSpaceInCurrentPage(&j);
    printf("Free space after write %d\n", j);
    
    /* HV reset */
    eErrorState = HV_Reset();
    if (eErrorState == ERROR)
    {
        printf("HV_Reset FAIL\n");
        return 0;
    }
    else
    {
        printf("HV_Reset SUCCESS\n");
    }

    /* HV init */
    eErrorState = HV_Init(&u16PREDRIID);
    if (eErrorState == ERROR)
    {
        printf("Init HV mode FAIL\n");
        return 0;
    }
    else
    {
        printf("Init HV mode SUCCESS[ID:%d]\n", u16PREDRIID);
    }

    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
        return 0;
    }

    /* Power up PRE-DRIVER mode */
    eErrorState = EPWR_WriteRegisterField(HV_REG_PDRVCTL0, PDRVCTL0_EN_Msk, PDRVCTL0_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("Power up PRE-DRIVER FAIL\n");
        return 0;
    }

    /* Wait for PRE-DRIVER mode become enable */
    for(u32Timeout = 0xFFFFFFFF; u32Timeout > 0x00000000; u32Timeout--)
    {
        if ((u16PREDRIDATA & PMUSTS_CPRDY_READY) != 0)
        {
            break;
        }

        Delay_Ms(10);

        eErrorState = EPWR_ReadRegister(HV_REG_PMUSTS, &u16PREDRIDATA);
        if (eErrorState == ERROR)
        {
            printf("Read Register FAIL[%02x]\n", u16PREDRIDATA);
            return 0;
        }
    }
    if (u32Timeout == 0)
    {
        printf("Enable PRE-DRIVER error\n");
        return 0;
    }

    /* Set the VBAT under-voltage threshold */
    eErrorState = EPWR_WriteRegisterField(HV_REG_EVTTHCTL0, EVTTHCTL0_VBATUV_Msk, EVTTHCTL0_VBATUV_9P6V);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegisterField FAIL\n");
        return 0;
    }

    /* Enable VBAT under-voltage interrupt */
    eErrorState = EPWR_WriteRegister(HV_REG_TZIE0, TZIE0_VBATUV_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegister FAIL\n");
        return 0;
    }

    /* Enable TripEvent */
    EPWR_EnableTripEvent(EPWR_TRIP_EVENT_TZ0);

    /* Set the input signal of EPWRTZ0 event as high */
    EPWR_SetTripEventInputActiveHigh(EPWR_TRIP_EVENT_TZ0);

    NVIC_EnableIRQ(EPWRTZ0_IRQn);


    while (1)
    {

    }
}

void EPWRTZ0_IRQHandler()
{
    printf("EPWRTZ0 happened\n");
    
    __disable_irq();
    
    WriteWord(au32Buf, TOTAL_WORD_NUMBER);
    
    __enable_irq();
    
    EPWR_DisableTripEvent(EPWR_TRIP_EVENT_TZ0);
}
/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
