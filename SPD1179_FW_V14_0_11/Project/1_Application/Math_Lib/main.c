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

/* If the FPU is not enabled, the compilation is terminated */
# if __FPU_USED == 0
    # error "__FPU_USED == 0"
# endif 


#include <stdio.h>
#include "arm_math.h"


/* exact-width signed integer types */
typedef   signed           int i32;
/* exact-width unsigned integer types */
typedef unsigned           int u32;


float fa = 0.0;
/******************************************************************************
 * @brief      GccPrint10xFloat
 *
 * @param[in]  f32Value  :  Float precision is 7 to 8 decimal places
 *                          Integer of Value from -2147483648 to 2147483647
 *
 * @return     none
 *
 ******************************************************************************/
void GccPrint10xFloat(float f32Value) 
{
    i32 i32Integer;

    i32Integer = (int32_t)(10 * f32Value);
    
    printf("10xFloat %d\n", i32Integer);
} 




int main(void)
{
    CLOCK_InitWithRCO(100000000);
    Delay_Init();

    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);  

    /* Function in arm_math.h */
    fa = arm_cos_f32(1.047);
    #if defined ( __GNUC__ )
        GccPrint10xFloat(fa);
    #else
        printf("###\n");
        printf("Just a Sample....%f\n", fa);
    #endif

    arm_sqrt_f32(2.56, &fa);
    #if defined ( __GNUC__ )
        GccPrint10xFloat(fa);
    #else
        printf("Just a Sample....%f\n", fa);
    #endif

    /* Function in math.h */
    fa = sqrt(2.25);
    #if defined ( __GNUC__ )
        GccPrint10xFloat(fa);
    #else
        printf("Just a Sample....%f\n", fa);
    #endif

    while (1)
    {
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
