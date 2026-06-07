/******************************************************************************
 * @file     delay.c
 * @brief    Time-Delay firmware functions.
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

#include "delay.h"


/**
 *  @brief  Clock cycles per micro-second for software delay
 */
volatile uint32_t u32DelayLoopPerUs;
volatile uint32_t u32DelayClockPerUs;


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/******************************************************************************
 * @brief      Initialize the time-delay module
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void Delay_Init(void)
{
#if defined   ( DELAY_BY_SW_SRAM )
    u32DelayLoopPerUs  = (SysInfo.u32SYSCLK / 1000000) >> 2;  /* Each loop will cost 4 cycles */
    if (u32DelayLoopPerUs < 1)
    {
        u32DelayLoopPerUs = 1;
    }
#elif defined ( DELAY_BY_SW_FLASH )
	if (SysInfo.u32SYSCLK <= 25000000)
	{
		u32DelayLoopPerUs = 4U;
	}
	else if (SysInfo.u32SYSCLK <= 32000000)
	{
		u32DelayLoopPerUs = 5U;
	}
	else
	{
		u32DelayLoopPerUs = 6U;
	}
#else
    u32DelayClockPerUs = (SysInfo.u32SYSCLK / 1000000);
    #if   defined ( DELAY_BY_HW_TIMER0 )
        CLOCK_EnableModule(TIMER0_MODULE);
    #elif defined ( DELAY_BY_HW_TIMER1 )
        CLOCK_EnableModule(TIMER1_MODULE);
    #elif defined ( DELAY_BY_HW_TIMER2 )
        CLOCK_EnableModule(TIMER2_MODULE);
    #endif

    TIMER_EnableInt(DELAY_TIMER);
#endif
}




/******************************************************************************
 * @brief      Delay the specified milliseconds
 *
 * @param[in]  u32DelayMs:  The milliseconds to delay
 *
 * @return     none
 *
 * @others     If require high-precision delay, Use the timer.
 *
 ******************************************************************************/
void Delay_Ms(uint32_t u32DelayMs)
{
    Delay_Us(u32DelayMs * 1000);
}




/******************************************************************************
 * @brief      Delay the specified microseconds
 *
 * @param[in]  u32DelayUs:  The microseconds to delay
 *
 * @return     none
 *
 * @others     When using a TIMER delay, even if the program is running in RAM, 
 *             the additional instruction time is close to 700us at 100M clock.
 *             Such as Delay_Us(1), Actual time is 1.7us.
 *
 ******************************************************************************/
void Delay_Us(uint32_t u32DelayUs)
{
#if   defined ( DELAY_BY_SW_SRAM ) || defined ( DELAY_BY_SW_FLASH )
    /* Delay by software */
    u32DelayUs = (u32DelayUs * u32DelayLoopPerUs);    /* There is 4 cycle during for in O0~O3  */
    while (u32DelayUs)
    {
        u32DelayUs--;
    }
#else
    TIMER_Stop(DELAY_TIMER);                                              /* Stop timer                            */
    TIMER_SetReloadValue(DELAY_TIMER, u32DelayUs * u32DelayClockPerUs);   /* Set timer reload value                */
    TIMER_ClearInt(DELAY_TIMER);                                          /* Clear timer interrupt flag            */
    TIMER_Run(DELAY_TIMER);                                               /* Timer run                             */
    while (TIMER_GetIntFlag(DELAY_TIMER) == 0U)                              /* Wait until Timer flag enable          */
    {
    }
#endif
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

