/******************************************************************************
 * @file     engr.c
 * @brief    ENGR firmware functions.
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

#include "engr.h"




///******************************************************************************
// * @brief      Set 8-bit ADC timing
// *
// * @param[in]  u32SampNs: Sample time in ns
// * @param[in]  u32ConvNs: Convert time in ns
// *
// * @return     SUCCESS or ERROR
// *
// ******************************************************************************/
//ErrorStatus ENGR_Set8BitADCTiming(uint32_t u32SampNs, uint32_t u32ConvNs)
//{
//  uint32_t    u32SampCnt;
//  uint32_t    u32ConvCnt;
//  uint32_t    u32Key0;
//  uint32_t    u32Key1;
//  ErrorStatus Status = SUCCESS;
//
//  u32SampCnt = SysInfo.u32SYSCLK / 1000 * u32SampNs / 1000000 ;
//  u32ConvCnt = SysInfo.u32SYSCLK / 1000 * u32ConvNs / 1000000 ;
//
//  if (u32SampCnt>0)
//  {
//    u32SampCnt--;
//  }
//
//  if (u32ConvCnt>0)
//  {
//    u32ConvCnt--;
//  }
//
//  if ((u32SampCnt > 255) || (u32ConvCnt > 127))
//  {
//    /* Overflow error */
//    Status = ERROR;
//  }
//  else
//  {
//    u32Key0             = ENGR->ENGRREGKEY;
//    u32Key1             = ENGR->SYSMONSTOPKEY;
//    ENGR->ENGRREGKEY    = 0x1acce551;
//    ENGR->SYSMONSTOPKEY = 0x1acce551;
//    ENGR->AFEENGR1      = (ENGR->AFEENGR1 & 0xff8000ff)         |
//                          (u32SampCnt << AFEENGR1_SAMPCNT_Pos)  |
//                          (u32ConvCnt << AFEENGR1_CONVCNT_Pos);
//    ENGR->SYSMONSTOPKEY = u32Key1;
//    ENGR->ENGRREGKEY    = u32Key0;
//  }
//  return Status;
//}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
