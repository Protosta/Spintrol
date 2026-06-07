/******************************************************************************
 * @file     epwr.h
 * @brief    ePower driver header file.
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


#ifndef EPWR_H
#define EPWR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




#define EPWR_COMMUNICATION_MAX_RETRY_CNT  3




/**
 *  @brief  EPWR Trip Zone Event
 */
typedef enum
{
    EPWR_TRIP_EVENT_TZ0   = 1,        /*!< TZ0 event      */
    EPWR_TRIP_EVENT_TZ1   = 2,        /*!< TZ1 event      */
} EPWR_TripEventEnum;




/**
 *  @brief  EPWR Trip Zone Event Output selection
 */
typedef enum
{
    EPWR_OUTPUT_ORIGINAL                        = 0,    /*!< Original output                                                    */
    EPWR_OUTPUT_SYNC                            = 1,    /*!< Synchronous output with PWM clock                                  */
    EPWR_OUTPUT_FILTERED                        = 2,    /*!< Digital filter output                                              */
    EPWR_OUTPUT_LATCHED                         = 3,    /*!< Latched digital filter output                                      */
    EPWR_OUTPUT_ORIGINAL_OR_LATCHED             = 4,    /*!< Original output or Latched digital filter output                   */
    EPWR_OUTPUT_SYNC_OR_LATCHED                 = 5,    /*!< Synchronous output with PWM clock or Latched digital filter output */
    EPWR_OUTPUT_FILTERED_OR_LATCHED             = 6,    /*!< Digital filter output or the latched one                           */
    EPWR_OUTPUT_ORIGINAL_OR_FILTERED_OR_LATCHED = 7,    /*!< Original output or Synchronous output with PWM clock or Latched digital filter output */
} EPWR_OutputSelEnum;




/******************************************************************************
 * @brief      Get filtered trip-zone event status
 *
 * @param[in]  eTZEvent: Select the ePower trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     0 - There is now no ePower trip-zone event
 *             not 0 - ePower trip-zone event is happening now
 *
 ******************************************************************************/
#define EPWR_GetFilteredTripEventStatus(eTZEvent)     ((EPWR)->EPWRTZFLT & (eTZEvent))




/******************************************************************************
 * @brief      Get latched trip-zone event flag
 *
 * @param[in]  eTZEvent: Select the ePower trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     0 - ePower trip-zone event never happened
 *             not 0 - ePower trip-zone event happened at least once
 *
 ******************************************************************************/
#define EPWR_GetTripEventFlag(eTZEvent)             ((EPWR)->EPWRTZFLG & (eTZEvent))




/******************************************************************************
 * @brief      Clear trip-zone event flag
 *
 * @param[in]  eTZEvent: Select the ePower trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 ******************************************************************************/
#define EPWR_ClearTripEventFlag(eTZEvent)   (EPWR->EPWRTZCLR = (eTZEvent))




/******************************************************************************
 * @brief      Reset Trip-zone filters
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_ResetFilter(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL |= EPWRTZ0CTL_FLTRST_RESET;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL |= EPWRTZ1CTL_FLTRST_RESET;
    }
}




/******************************************************************************
 * @brief      Enable PWMSYNC clear Trip-zone event latched flag
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_EnablePWMSyncClearTripEventFlag(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL |= EPWRTZ0CTL_SYNCCLREN_ENABLE;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL |= EPWRTZ1CTL_SYNCCLREN_ENABLE;
    }
}




/******************************************************************************
 * @brief      Disable PWMSYNC clear Trip-zone event latched flag
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_DisablePWMSyncClearTripEventStatus(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL &= ~EPWRTZ0CTL_SYNCCLREN_ENABLE;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL &= ~EPWRTZ1CTL_SYNCCLREN_ENABLE;
    }
}




/******************************************************************************
 * @brief      Set EPWR Trip-zone event input as active high
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SetTripEventInputActiveHigh(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL |= EPWRTZ0CTL_INPOL_ACTIVE_HIGH;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL |= EPWRTZ1CTL_INPOL_ACTIVE_HIGH;
    }
}




/******************************************************************************
 * @brief      Set EPWR Trip-zone event input as active low
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SetTripEventInputActiveLow(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL &= ~EPWRTZ0CTL_INPOL_ACTIVE_HIGH;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL &= ~EPWRTZ1CTL_INPOL_ACTIVE_HIGH;
    }
}




/******************************************************************************
 * @brief      Enable Trip-zone event input
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_EnableTripEvent(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL |= EPWRTZ0CTL_IE_ENABLE;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL |= EPWRTZ1CTL_IE_ENABLE;
    }
}




/******************************************************************************
 * @brief      Disable Trip-zone event input
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_DisableTripEvent(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL &= ~EPWRTZ0CTL_IE_ENABLE;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL &= ~EPWRTZ1CTL_IE_ENABLE;
    }
}




/******************************************************************************
 * @brief      Set EPWR Trip-zone event output as active high
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SetTripEventOutputActiveHigh(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL |= EPWRTZ0CTL_POL4PWM_ACTIVE_HIGH;
        EPWR->EPWRTZ0CTL |= EPWRTZ0CTL_POL4GPIO_ACTIVE_HIGH;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL |= EPWRTZ1CTL_POL4PWM_ACTIVE_HIGH;
        EPWR->EPWRTZ1CTL |= EPWRTZ1CTL_POL4GPIO_ACTIVE_HIGH;
    }
}




/******************************************************************************
 * @brief      Set EPWR Trip-zone event output as active low
 *
 * @param[in]  eTZEvent: Select the trip-zone event
 *                       Please refer to EPWR_TripEventEnum
 *                       Multiple events can be ORed simultaneously
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SetTripEventOutputActiveLow(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL &= ~EPWRTZ0CTL_POL4PWM_ACTIVE_HIGH;
        EPWR->EPWRTZ0CTL &= ~EPWRTZ0CTL_POL4GPIO_ACTIVE_HIGH;
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL &= ~EPWRTZ1CTL_POL4PWM_ACTIVE_HIGH;
        EPWR->EPWRTZ1CTL &= ~EPWRTZ1CTL_POL4GPIO_ACTIVE_HIGH;
    }
}




/******************************************************************************
 * @brief      Set Trip-zone event output type
 *
 * @param[in]  eTZEvent  : Select the trip-zone event
 *                         Please refer to EPWR_TripEventEnum
 *                         Multiple events can be ORed simultaneously
 * @param[in]  eOutputSel: Select the trip-zone output
 *                         Please refer to EPWR_OutputSelEnum
 *
 * @return     None
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SetTripEventOutputType(EPWR_TripEventEnum eTZEvent, EPWR_OutputSelEnum eOutputSel)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRTZ0CTL = (EPWR->EPWRTZ0CTL & ~(EPWRTZ0CTL_SEL4PWM_Msk | EPWRTZ0CTL_SEL4GPIO_Msk)) |
                           (eOutputSel << EPWRTZ0CTL_SEL4PWM_Pos) |
                           (eOutputSel << EPWRTZ0CTL_SEL4GPIO_Pos);
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRTZ1CTL = (EPWR->EPWRTZ1CTL & ~(EPWRTZ1CTL_SEL4PWM_Msk | EPWRTZ1CTL_SEL4GPIO_Msk)) |
                           (eOutputSel << EPWRTZ1CTL_SEL4PWM_Pos) |
                           (eOutputSel << EPWRTZ1CTL_SEL4GPIO_Pos);
    }
}




/******************************************************************************
 * @brief      Select PWM Synchronization signal to clear Trip-zone event latched flag
 *
 * @param[in]  eTZEvent : Select the trip-zone event
 *                        Please refer to EPWR_TripEventEnum
 *                        Multiple events can be ORed simultaneously
 * @param[in]  ePWMIndex: PWM module index
 *                        Please refer to PWM_IncEnum
 *
 * @return     None
 *
 * @example    EPWR_SetSyncEvent(EPWR_TRIP_EVENT_TZ0, INC_PWM0 | INC_PWM1);
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SetSyncEvent(EPWR_TripEventEnum eTZEvent, uint8_t ePWMIndex)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        EPWR->EPWRCTL = (EPWR->EPWRCTL & 0xff00ffffU) | ((ePWMIndex) << 16U);
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        EPWR->EPWRCTL = (EPWR->EPWRCTL & 0x00ffffffU) | ((ePWMIndex) << 24U);
    }
}




/******************************************************************************
 * @brief      Select which TZ signal is to output to GPIO
 *
 * @param[in]  eTZEvent : Select the trip-zone event
 *                        Please refer to EPWR_TripEventEnum
 *
 * @return     None
 *
 * @example    EPWR_SelectTZEventOutputToGPIO(EPWR_TRIP_EVENT_TZ0);
 *
 *******************************************************************************/
__STATIC_INLINE void EPWR_SelectTZEventOutputToGPIO(EPWR_TripEventEnum eTZEvent)
{
    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ0) != 0UL)
    {
        CLEAR_BITS(EPWR->EPWRCTL, EPWRCTL_TZSEL4GPIO_Msk);
    }

    if (((eTZEvent) & EPWR_TRIP_EVENT_TZ1) != 0UL)
    {
        SET_BITS(EPWR->EPWRCTL, EPWRCTL_TZSEL4GPIO_Msk);
    }
}




/******************************************************************************
 * @brief      Is communiation interface busy
 *
 * @param[in]  None
 *
 * @return     0 - Communication interface is idle
 *             1 - Communication interface is busy
 *
 *******************************************************************************/
#define EPWR_IsComBusy()                    ((EPWR->EPWRSSTS & EPWRSSTS_BUSY_Msk) >> EPWRSSTS_BUSY_Pos)




/******************************************************************************
 * @brief      Is communiation interface error
 *
 * @param[in]  None
 *
 * @return     0 - Communication is succesfully
 *             1 - Communication is error
 *
 *******************************************************************************/
#define EPWR_IsComError()                   ((EPWR->EPWRSSTS & EPWRSSTS_ERROR_Msk) >> EPWRSSTS_ERROR_Pos)




/******************************************************************************
 * @brief      Enable write access to the protected EPWR registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define EPWR_WALLOW()                       (EPWR->EPWRREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected EPWR registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define EPWR_WDIS()                         (EPWR->EPWRREGKEY = 0x0)




/**
 *  @brief EPWR Public Function Declaration
 */
void EPWR_SetFilterClockDiv(EPWR_TripEventEnum eTZEvent, uint16_t u16ClkDiv);
void EPWR_SetFilterWindow(EPWR_TripEventEnum eTZEvent, uint8_t u8WinSize, uint8_t u8Threshold);
void EPWR_SetFilterWindowTimeNs(EPWR_TripEventEnum eTZEvent, uint32_t u32SizeTimeNS, uint32_t u32ThresholdTimeNS);

ErrorStatus EPWR_ComSpeedInit(uint32_t u32Speed);
ErrorStatus EPWR_GetID(uint16_t *pu16ID);
ErrorStatus EPWR_WriteRegister(uint8_t u8Addr, uint16_t u16WriteData);
ErrorStatus EPWR_WriteRegisterField(uint8_t u8Addr, uint16_t u16Mask, uint16_t u16FieldData);
ErrorStatus EPWR_ReadRegister(uint8_t u8Addr, uint16_t *u16ReadData);
ErrorStatus EPWR_ResetRegister(void);
ErrorStatus EPWR_FeedWatchdog(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* EPWR_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
