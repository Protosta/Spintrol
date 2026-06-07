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
#include <stdio.h>

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif
#include "func.h"



/*************************************************************************************************************************
 *
 * @brief      This demo if gaven for how to write a function interface defined by user, which can used by main thread in
 *             "Flash_Call_User_Func" folder, this code give a example of how to load the right function into specific address.
 *
 *************************************************************************************************************************/


#if defined ( __CC_ARM )
#define         _PRE_Define
#define         _FUNC_Absolute_Addr_            __attribute__((section(".ARM.__at_0x1000F000")))
#else
#define         _PRE_Define                     __root
#define         _FUNC_Absolute_Addr_            @ (0x1000F000)
#endif

uint32_t gu32Number;

/* Put the function into 0x1000F000 */
_PRE_Define const FUNCLIB ThirdFuncLib _FUNC_Absolute_Addr_ =
{
    UserFunc,
    GetMotorStatus,
    TestFunc,
};

uint32_t TestFunc(void)
{
    gu32Number = 10;
    return gu32Number;
}
  
uint32_t UserFunc(uint8_t a, uint8_t b, int vtor, int* c, int d)
{
    d = a + b;
    vtor += d;
    c = &d;
    gu32Number++;
    return *c + vtor + gu32Number;
}

PHBs* GetMotorStatus(uint32_t *PHA, PHBs * PHB, int *PHC, uint32_t **Key, uint32_t Count)
{
    PHB->voltage = *PHA + *PHC;
    *Key = &Count;
    PHB->phase = **Key;
    return PHB;
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
