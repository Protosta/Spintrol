/******************************************************************************
 * @file     system_spc1169.h
 * @brief    CMSIS Device System Header File for SPCxxxx Device Series
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


#ifndef SYSTEM_SPC1169_H
#define SYSTEM_SPC1169_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


///**
// *  @brief  System Clock Frequency (Core Clock)
// */
//extern uint32_t SystemCoreClock;




/**
 *  @brief  System Information Structure Declaration
 */
typedef struct
{
  uint32_t u32SRCCLK[4];        /*!< Source clock       */
  uint32_t u32SYSCLK;           /*!< SYSCLK Frequeny    */
  int32_t  i32SHOffset;
  int32_t  i32SHGain;
} SysInfoStruct;




/**
 *  @brief  System information data
 */
extern SysInfoStruct SysInfo;




/******************************************************************************
 * @brief      Initialize the system
 *             Setup the microcontroller system
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
extern void SystemInit(void);




///******************************************************************************
// * @brief      Updates the SystemCoreClock with current core Clock
// *             retrieved from cpu registers.
// *
// * @param[in]  None
// *
// * @return     None
// *
// ******************************************************************************/
//extern void SystemCoreClockUpdate(void);


#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_ARMCM4_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

