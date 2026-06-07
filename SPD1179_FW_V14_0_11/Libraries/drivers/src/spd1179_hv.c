/******************************************************************************
 * @file     spd1179_hv.c
 * @brief    hv firmware functions.
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

#include "spd1179_hv.h"




/********************************************************************************
 * @brief      XIP read High voltage part trim information three times
 *
 * @param[in]  none
 *
 * @return     none
 *
 *******************************************************************************/
uint32_t HV_GetTrimInfo(uint32_t u32Addr)
{
    uint32_t u32Result = 0;
    volatile uint32_t u32ValA = 0;
    volatile uint32_t u32ValB = 0;
    volatile uint32_t u32ValC = 0;
    uint32_t u32Temp = 0;
    
    u32ValA = *((__IO uint32_t *) u32Addr);
    /* Add a temp irrelevant code between two read operations of the same
     * address, prevent the PC from fetching data directly from the XIP cache.
     */
    u32Temp = *((__IO uint32_t *) 0x10000000);
    u32ValB = *((__IO uint32_t *) u32Addr);
    
    u32Result = u32ValA;
    u32Result = u32Result & u32ValB;
    
    /* Add a temp irrelevant code between two read operations of the same
     * address, prevent the PC from fetching data directly from the XIP cache.
     */
    u32Temp = *((__IO uint32_t *) 0x10000000);
    u32ValC = *((__IO uint32_t *) u32Addr);

    u32Temp = u32ValA;
    u32Temp = u32Temp & u32ValC;
    u32Result = u32Result | u32Temp;
    
    u32Temp = u32ValB;
    u32Temp = u32Temp & u32ValC;
    u32Result = u32Result | u32Temp;
    
    return u32Result;
}




/****************************************************************************//**
 * @brief      Initialize High Voltage Module Pin Interface
 *
 * @param[in]  none
 *
 * @return     none
 *
 *******************************************************************************/
void HV_PinInit(void)
{
    /* Pin for High Voltage Module */
    PIN_SetChannel(GPIO_HV_PWM_W_L, PIN_GPIO19_PWM2B);
    PIN_SetChannel(GPIO_HV_PWM_W_H, PIN_GPIO20_PWM2A);

    PIN_SetChannel(GPIO_HV_PWM_V_L, PIN_GPIO21_PWM1B);
    PIN_SetChannel(GPIO_HV_PWM_V_H, PIN_GPIO22_PWM1A);

    PIN_SetChannel(GPIO_HV_PWM_U_L, PIN_GPIO23_PWM0B);
    PIN_SetChannel(GPIO_HV_PWM_U_H, PIN_GPIO24_PWM0A);
}




/********************************************************************************
 * @brief      Initialize High Voltage Module
 *
 * @param[in]  u32Baudrate:  Communication Speed (bps)
 * @param[in]  pu16ID     :  Pointer to the data stored High Voltage Module ID
 *
 * @return     ERROR or SUCCESS
 *
 *******************************************************************************/
ErrorStatus HV_Init(uint16_t *pu16ID)
{
    ErrorStatus Status = SUCCESS;

    /* Init Pin Interface */
    HV_PinInit();

    /* Init Communication */
    if(EPWR_ComSpeedInit(1000000) != SUCCESS)
    {
        Status = ERROR;
    }

    /* Handshake with High Voltage Module */
    if(EPWR_GetID(pu16ID) != SUCCESS)
    {
        Status = ERROR;
    }            

    /* Init High Voltage Module registers */
    if (HV_InitRegister() != SUCCESS)
    {
        Status = ERROR;
    }
    
    if (Status == SUCCESS)
    {
        Status = EPWR_ComSpeedInit(EPWR_COM_SPEED);
    }

    return Status;
}




/********************************************************************************
 * @brief      Init High Voltage Module Registers (Trim)
 *
 * @param[in]  none
 *
 * @return     ERROR or SUCCESS
 *
 *******************************************************************************/
ErrorStatus HV_InitRegister(void)
{
    ErrorStatus Status = SUCCESS;
    uint32_t u32Temp;

    /* Get Trim Flag */
    u32Temp = HV_GetTrimInfo(0x11001000U + 0x180);

    /* Valid Trim Flag */
    if (u32Temp == 0x1ACCE551U)
    {
        /* Enable Write Access */
        if (EPWR_WriteRegister(HV_REG_CTLKEY, KEY_ENGR_REG) != SUCCESS)
        {
            Status = ERROR;
        }

        u32Temp = HV_GetTrimInfo(0x11001000U + 0x188);
        /* Write PMUTRIM0 value */
        if (EPWR_WriteRegister(0x30, u32Temp) != SUCCESS)
        {
            Status = ERROR;
        }

        u32Temp = HV_GetTrimInfo(0x11001000U + 0x18C);
        /* Write PMUTRIM1 value */
        if (EPWR_WriteRegister(0x31, u32Temp) != SUCCESS)
        {
            Status = ERROR;
        }

        u32Temp = HV_GetTrimInfo(0x11001000U + 0x190);
        /* Write PMUTRIM2 value */
        if (EPWR_WriteRegister(0x32, u32Temp) != SUCCESS)
        {
            Status = ERROR;
        }
        
        u32Temp = HV_GetTrimInfo(0x11001000U + 0x194);
        /* Write PMUTRIM3 value */
        if (EPWR_WriteRegister(0x33, u32Temp) != SUCCESS)
        {
            Status = ERROR;
        }

        u32Temp = HV_GetTrimInfo(0x11001000U + 0x198);
        /* Write BODTRIM value */
        if (EPWR_WriteRegister(0x34, u32Temp) != SUCCESS)
        {
            Status = ERROR;
        }

        u32Temp = HV_GetTrimInfo(0x11001000U + 0x19C);
        /* Write LINTRIM value */
        if (EPWR_WriteRegister(0x35, u32Temp) != SUCCESS)
        {
            Status = ERROR;
        }
        
        /* Enable Write Access */
        if (EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG) != SUCCESS)
        {
            Status = ERROR;
        }
        
        /* Write PMUCTL vaule */
        if (EPWR_WriteRegister(HV_REG_PMUCTL, 0xA2B5) != SUCCESS)
        {
            Status = ERROR;
        }
        
        /* Write PDRVCTL1 vaule */
        if (EPWR_WriteRegister(HV_REG_PDRVCTL1, 0x1A7C) != SUCCESS)
        {
            Status = ERROR;
        }

        /* Disable Write Access */
        if (EPWR_WriteRegister(HV_REG_CTLKEY, KEY_LOCK_ALL) != SUCCESS)
        {
            Status = ERROR;
        }
    }

    return Status;
}




/******************************************************************************
 * @brief      HV reset
 *
 * @param[in]  none
 *
 * @return     SUCCESS or ERROR
 *
 * @note       Some critical registers will not reset when executing this command, 
 *             including: SYSEVTFLG, PMUCTL, PMUSTS, CYCSENSECTL, CYCWKUPCTL, MONCTL
 *
 ******************************************************************************/
ErrorStatus HV_Reset(void)
{
    ErrorStatus Status = SUCCESS;

    /* Init Communication */
    if(EPWR_ComSpeedInit(1000000) != SUCCESS)
    {
        Status = ERROR;
    }

     /* Allow to software reset the registers */
    if(EPWR_WriteRegister(HV_REG_CTLKEY, KEY_SRST_REG) != SUCCESS)
    {
        Status = ERROR;
    }

    /* Reset HV Register */
    if(EPWR_ResetRegister() != SUCCESS)
    {
        Status = ERROR;
    }

    return Status;
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
