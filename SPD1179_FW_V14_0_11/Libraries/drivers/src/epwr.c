/******************************************************************************
 * @file     epwr.c
 * @brief    ePower firmware functions.
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

#include "epwr.h"




/******************************************************************************
 * @brief      Set Trip-zone filter clock dividing ratio
 *
 * @param[in]  eTZEvent : Select the trip-zone event
 *                        Please refer to EPWR_TripEventEnum
 *                        Multiple events can be ORed simultaneously
 * @param[in]  u16ClkDiv: Dividing ratio (1~1024)
 *
 * @return     none
 *
 *******************************************************************************/
void EPWR_SetFilterClockDiv(EPWR_TripEventEnum eTZEvent, uint16_t u16ClkDiv)
{
    if ((u16ClkDiv == 0) || (u16ClkDiv > 1024))
    {
        return;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL = (EPWR->EPWRTZ0CTL & ~EPWRTZ0CTL_FLTDIV_Msk)
                         | ((u16ClkDiv - 1) << EPWRTZ0CTL_FLTDIV_Pos);
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL = (EPWR->EPWRTZ1CTL & ~EPWRTZ1CTL_FLTDIV_Msk)
                         | ((u16ClkDiv - 1) << EPWRTZ1CTL_FLTDIV_Pos);
    }
}




/******************************************************************************
 * @brief      Set Trip-zone filter window size and threshold
 *
 * @param[in]  eTZEvent   : Select the trip-zone event
 *                          Please refer to EPWR_TripEventEnum
 * @param[in]  u8WinSize  : Filter window size (1 ~ 32)
 * @param[in]  u8Threshold: Filter threshold value (1 ~ 32)
 *
 * @return     none
 *
 *******************************************************************************/
void EPWR_SetFilterWindow(EPWR_TripEventEnum eTZEvent, uint8_t u8WinSize, uint8_t u8Threshold)
{
    /* Invalid Window size */
    if ((u8WinSize == 0) || (u8WinSize > 32))
    {
        return;
    }

    /* Invalid Window Threshold */
    if ((u8Threshold == 0) || (u8Threshold > 32))
    {
        return;
    }

    /* Configure Filter Window */
    switch (eTZEvent)
    {
        case EPWR_TRIP_EVENT_TZ0:
            EPWR->EPWRTZ0CTL = (EPWR->EPWRTZ0CTL & ~(EPWRTZ0CTL_FLTWIN_Msk | EPWRTZ0CTL_FLTTH_Msk))
                             | ((u8WinSize   - 1) << EPWRTZ0CTL_FLTWIN_Pos)
                             | ((u8Threshold - 1) << EPWRTZ0CTL_FLTTH_Pos);
            break;

        case EPWR_TRIP_EVENT_TZ1:
            EPWR->EPWRTZ1CTL = (EPWR->EPWRTZ1CTL & ~(EPWRTZ1CTL_FLTWIN_Msk | EPWRTZ1CTL_FLTTH_Msk))
                             | ((u8WinSize   - 1) << EPWRTZ1CTL_FLTWIN_Pos)
                             | ((u8Threshold - 1) << EPWRTZ1CTL_FLTTH_Pos);
            break;
    }
}




/******************************************************************************
 * @brief      Set Trip-zone filter window size and threshold (nano second)
 *
 * @param[in]  eTZEvent          : Select the trip-zone event
 *                                 Please refer to EPWR_TripEventEnum
 * @param[in]  u32SizeTimeNS     : Window Size (Time in ns)
 * @param[in]  u32ThresholdTimeNS: Threshold (Time in ns)
 *
 * @return     none
 *
 *******************************************************************************/
void EPWR_SetFilterWindowTimeNs(EPWR_TripEventEnum eTZEvent, uint32_t u32SizeTimeNS, uint32_t u32ThresholdTimeNS)
{
    uint32_t u32TimeCnt1, u32TimeCnt2;
    uint32_t u32FilterClk, u32FilterDiv;

    /* EPWR clock */
    u32FilterClk = SysInfo.u32SYSCLK;

    switch (eTZEvent)
    {
        case EPWR_TRIP_EVENT_TZ0:
            u32FilterDiv = (EPWR->EPWRTZ0CTL & EPWRTZ0CTL_FLTDIV_Msk) >> EPWRTZ0CTL_FLTDIV_Pos;
            u32FilterClk /= (u32FilterDiv + 1);
            break;

        case EPWR_TRIP_EVENT_TZ1:
            u32FilterDiv = (EPWR->EPWRTZ1CTL & EPWRTZ1CTL_FLTDIV_Msk) >> EPWRTZ1CTL_FLTDIV_Pos;
            u32FilterClk /= (u32FilterDiv + 1);
            break;
    }

    /* Window size */
    u32TimeCnt1 = (((u32SizeTimeNS) * (u32FilterClk / 100000)) / 10000);
    if (u32TimeCnt1 > 32)
    {
        u32TimeCnt1 = 32;
    }

    /* Threshold */
    u32TimeCnt2 = (((u32ThresholdTimeNS) * (u32FilterClk / 100000)) / 10000);
    /* Threshold value must be bigger than WindowSize/2 */
    if ((u32TimeCnt2 * 2) < u32TimeCnt1)
    {
        u32TimeCnt2 = u32TimeCnt1 / 2 + 1;
    }
    if (u32TimeCnt2 > 32)
    {
        u32TimeCnt2 = 32;
    }

    EPWR_SetFilterWindow(eTZEvent, u32TimeCnt1, u32TimeCnt2);
}




/******************************************************************************
 * @brief      Set ePower communication interface speed
 *
 * @param[in]  u32Speed: Bit rate during communication
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus EPWR_ComSpeedInit(uint32_t u32Speed)
{
    uint32_t    u32Div;
    ErrorStatus Status = SUCCESS;

    /* ePower communication interface speed must < 2.6M */
    if (u32Speed > 2600000)
    {
        u32Speed = 2600000;
        Status = ERROR;
    }

    /* Calculate EPWR serial interface divider */
    u32Div = SysInfo.u32SYSCLK / u32Speed;

    /* Check divider */
    if (u32Div == 0UL)
    {
        u32Div = 1UL;
    }

    if (u32Div > 255UL)
    {
        u32Div = 255;
        Status = ERROR;
    }

    EPWR->EPWRCTL = (EPWR->EPWRCTL & (~EPWRCTL_SCLKDIV_Msk)) | (u32Div << EPWRCTL_SCLKDIV_Pos);

    return Status;
}




/******************************************************************************
 * @brief      ePower get chip ID
 *
 * @param[in]  pu16ID: Pointer to the address to store the ID
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus EPWR_GetID(uint16_t *pu16ID)
{
    volatile uint32_t  u32Timeout;
    uint32_t  i, u32RetyCnt;
    ErrorStatus Status = ERROR;

    for(u32RetyCnt = 0; u32RetyCnt < EPWR_COMMUNICATION_MAX_RETRY_CNT; u32RetyCnt++)
    {
        /* Issue GET_ID command */
        EPWR->EPWRSCTL = 0xfe000000;

        /* Calculate timeout threshold */
        u32Timeout = (EPWR->EPWRCTL & EPWRCTL_SCLKDIV_Msk) << 8UL;

        /* Wait for communication finish or timeout */
        i = 0;
        while ((i < u32Timeout) && (EPWR_IsComBusy() == 1UL))
        {
            i = i + 1;
        }

        /* Check error and update the result */
        if ((i < u32Timeout) && (EPWR_IsComError() == 0UL))
        {
            Status = SUCCESS;
            break;
        }
    }

    *pu16ID = (uint16_t)(EPWR->EPWRSRDAT);

    return Status;
}




/******************************************************************************
 * @brief      ePower write register
 *
 * @param[in]  u8Addr      : Register address within from 0x00 to 0x3F
 * @param[in]  u16WriteData: 2-byte data to write to the register
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus EPWR_WriteRegister(uint8_t u8Addr, uint16_t u16WriteData)
{
    volatile uint32_t  u32Timeout;
    uint32_t  i, u32RetyCnt;
    ErrorStatus Status = ERROR;

    if (u8Addr <= 63UL)
    {
        for(u32RetyCnt = 0; u32RetyCnt < EPWR_COMMUNICATION_MAX_RETRY_CNT * 2; u32RetyCnt++)
        {
            /* WRITE_SHADOW command */
            EPWR->EPWRSCTL = 0xfe400000 | ((uint32_t)u8Addr << 16) | (uint32_t)u16WriteData;

            /* Calculate timeout threshold */
            u32Timeout = (EPWR->EPWRCTL & EPWRCTL_SCLKDIV_Msk) << 8;

            /* Wait communication finish or timeout */
            i = 0;
            while ((i < u32Timeout) && (EPWR_IsComBusy() == 1UL))
            {
                i = i + 1;
            }

            if ((i < u32Timeout) && (EPWR_IsComError() == 0UL))
            {
                /* WRITE_ACTIVE command */
                EPWR->EPWRSCTL = 0xfe800000;

                i = 0;
                while ((i < u32Timeout) && (EPWR_IsComBusy() == 1UL))
                {
                    i = i + 1;
                }

                if ((i < u32Timeout) && (EPWR_IsComError() == 0UL))
                {
                    Status = SUCCESS;
                    break;
                }
            }
        }
    }
    return Status;
}




/******************************************************************************
 * @brief      ePower write register
 *
 * @param[in]  u8Addr      : Register address within from 0x00 to 0x3F
 * @param[in]  u16Mask     : Bit-field mask
 * @param[in]  u16FieldData: Register bit-field value (shifted according to its position)
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus EPWR_WriteRegisterField(uint8_t u8Addr, uint16_t u16Mask, uint16_t u16FieldData)
{
    ErrorStatus Status = ERROR;
    uint16_t u16RxData;

    Status = EPWR_ReadRegister(u8Addr, &u16RxData);

    if (Status == SUCCESS)
    {
        u16RxData &= ~u16Mask;
        u16RxData |= (u16FieldData);

        Status = EPWR_WriteRegister(u8Addr, u16RxData);
    }

    return Status;
}




/******************************************************************************
 * @brief      ePower read register
 *
 * @param[in]  u8Addr      : Register address within from 0x00 to 0x3F
 * @param[in]  pu16ReadData: Pointer to store the data read from the register
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus EPWR_ReadRegister(uint8_t u8Addr, uint16_t *pu16ReadData)
{
    volatile uint32_t  u32Timeout;
    uint32_t  i, u32RetyCnt;
    ErrorStatus Status = ERROR;

    if (u8Addr <= 63UL)
    {
        for(u32RetyCnt = 0; u32RetyCnt < EPWR_COMMUNICATION_MAX_RETRY_CNT; u32RetyCnt++)
        {
            /* READ_ACTIVE command */
            EPWR->EPWRSCTL = 0xfec00000 | ((uint32_t)u8Addr << 16);

            /* Calculate timeout threshold */
            u32Timeout = (EPWR->EPWRCTL & EPWRCTL_SCLKDIV_Msk) << 8;

            /* Wait communication finish or timeout */
            i = 0;
            while ((i < u32Timeout) && (EPWR_IsComBusy() == 1UL))
            {
                i = i + 1;
            }

            if ((i < u32Timeout) && (EPWR_IsComError() == 0UL))
            {
                Status = SUCCESS;
                break;
            }
        }
    }
    
    *pu16ReadData = (uint16_t)(EPWR->EPWRSRDAT);
    
    return Status;
}




/******************************************************************************
 * @brief      ePower reset register
 *
 * @param[in]  none
 *
 * @return     SUCCESS or ERROR
 *
 * @note       Some critical registers will not reset when executing this command, 
 *             including: SYSEVTFLG, PMUCTL, PMUSTS, CYCSENSECTL, CYCWKUPCTL, MONCTL
 *
 ******************************************************************************/
ErrorStatus EPWR_ResetRegister(void)
{
    volatile uint32_t  u32Timeout;
    uint32_t  i, u32RetyCnt;
    ErrorStatus Status = ERROR;

    for(u32RetyCnt = 0; u32RetyCnt < EPWR_COMMUNICATION_MAX_RETRY_CNT; u32RetyCnt++)
    {
        /* Issue reset register command */
        EPWR->EPWRSCTL = 0xff000000;

        /* Calculate timeout threshold */
        u32Timeout = (EPWR->EPWRCTL & EPWRCTL_SCLKDIV_Msk) << 8;

        /* Wait communication finish or timeout */
        i = 0;
        while ((i < u32Timeout) && (EPWR_IsComBusy() == 1UL))
        {
            i = i + 1;
        }

        if ((i < u32Timeout) && (EPWR_IsComError() == 0UL))
        {
            Status = SUCCESS;
            break;
        }
    }

    return Status;
}




/******************************************************************************
 * @brief      ePower feed watchdog
 *
 * @param[in]  none
 *
 * @return     SUCCESS or ERROR
 *
 ******************************************************************************/
ErrorStatus EPWR_FeedWatchdog(void)
{
    volatile uint32_t  u32Timeout;
    uint32_t  i, u32RetyCnt;
    ErrorStatus Status = ERROR;

    for(u32RetyCnt = 0; u32RetyCnt < EPWR_COMMUNICATION_MAX_RETRY_CNT; u32RetyCnt++)
    {
        /* Issue feed watchdog command */
        EPWR->EPWRSCTL = 0xff400000;

        /* Calculate timeout threshold */
        u32Timeout = (EPWR->EPWRCTL & EPWRCTL_SCLKDIV_Msk) << 8;

        /* Wait communication finish or timeout */
        i = 0;
        while ((i < u32Timeout) && (EPWR_IsComBusy() == 1UL))
        {
            i = i + 1;
        }

        if ((i < u32Timeout) && (EPWR_IsComError() == 0UL))
        {
            Status = SUCCESS;
            break;
        }
    }

    return Status;
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
