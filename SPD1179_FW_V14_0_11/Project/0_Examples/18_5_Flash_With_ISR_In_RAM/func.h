
/******************************************************************************
 * @file     func.h
 * @brief    functions in ISR.
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


#ifndef FUNC_H
#define FUNC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




#if defined ( __ICCARM__ )
    #define         _RAM_FUNC_       __ramfunc
#else
    #define         _RAM_FUNC_       __attribute__ ((section("RAMCODE")))
#endif




/**
 *  @brief Function Declaration
 */
_RAM_FUNC_ int16_t A(int16_t i16Theta);
_RAM_FUNC_ int16_t B_1(int16_t in,int16_t sat);
_RAM_FUNC_ void B(int32_t i32_PWM_Full_Scale,int32_t* pi32_PWM_A,int32_t* pi32_PWM_B,int32_t* pi32_PWM_C);
_RAM_FUNC_ void C(int32_t* pi32_PWM);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* FUNC_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/


