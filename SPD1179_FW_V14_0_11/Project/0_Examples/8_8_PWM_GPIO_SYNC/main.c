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


/* This macro is used to get the PWM period with a specified frequency */
#define                PWM_FREQ                          20000        /* 20kHz PWM */
#define                PWM_DB_NS                         1000         /* 1000ns */


uint32_t              u32PWMPeriod;                                                               /* PWM Period*/

#if (defined(SPD1179) || defined(SPD1177) || defined(SPD1179B))
uint16_t              u16PREDRIID;                                                                /* PRE-DRIVER mode ID */
uint16_t              u16PREDRIDATA                      = 0;                                     /* Data read from PRE-DRIVER */
ErrorStatus           eErrorState;                                                                /* Function State */
#endif

/*************************************************************************************************************************
 *
 * @brief      In this case, GPIO is used as SYNC signal and will trigger SYNC on all PWMs(PWM0/PWM1/PWM2) synchronously
 *
 *             Key point : the SYNC GPIO must be keep low level before test begin, and switch to high level when you want
 *             to trigger the sync signal.
 *
 *************************************************************************************************************************/


int main(void)
{
    #if (defined(SPD1179) || defined(SPD1177) || defined(SPD1179B))
        uint32_t u32Timeout;
    #endif
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

    #if (defined(SPD1179) || defined(SPD1177) || defined(SPD1179B))

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

    /* Power up PRE-DRIVER mode*/
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
    #else
    /* Cofig PWM0/1/2 GPIO Function */
    PIN_SetChannel(PIN_GPIO19, PIN_GPIO19_PWM2B);
    PIN_SetChannel(PIN_GPIO20, PIN_GPIO20_PWM2A);
    PIN_SetChannel(PIN_GPIO21, PIN_GPIO21_PWM1B);
    PIN_SetChannel(PIN_GPIO22, PIN_GPIO22_PWM1A);
    PIN_SetChannel(PIN_GPIO23, PIN_GPIO23_PWM0B);
    PIN_SetChannel(PIN_GPIO24, PIN_GPIO24_PWM0A);
    #endif

    /* Init PWM0/PWM1/PWM2 and output 20kHz waveform on both channel A and channel B */
    PWM_InitComplementaryPairChannel(PWM0, PWM_FREQ, PWM_DB_NS);
    PWM_InitComplementaryPairChannel(PWM1, PWM_FREQ, PWM_DB_NS);
    PWM_InitComplementaryPairChannel(PWM2, PWM_FREQ, PWM_DB_NS); 
    PWM2->AQCTLA = AQCTLA_CAU_SET_LOW | AQCTLA_CAD_SET_HIGH;
    
    /* Enable receive sync */
    PWM_EnableSync(PWM0);
    PWM_EnableSync(PWM1);
    PWM_EnableSync(PWM2);

    /* If we want to use GPIO as the SYNC signal, TBCNT SYNC out signal when TBCNT=0 must be close */
    PWM_SetSyncOutEvent(PWM0, SYNCO_DISABLE);
    PWM_SetSyncOutEvent(PWM1, SYNCO_DISABLE);
    PWM_SetSyncOutEvent(PWM2, SYNCO_DISABLE);

    /* Set PWM0A output duty */
    u32PWMPeriod = PWM_GetShadowPRD(PWM0);
    PWM_SetCMPA(PWM0, (u32PWMPeriod * 2) / 3);
    PWM_SetCMPA(PWM1, (u32PWMPeriod * 2) / 3);
    PWM_SetCMPA(PWM2, (u32PWMPeriod * 1) / 3);

    /* Start counting */
    PWM_RunCounter(PWM0);
    PWM_RunCounter(PWM1);
    PWM_RunCounter(PWM2);

    /* Enable GPIO SYNC on PWM */
    PWM_EnableSyncFromGPIO(INC_PWM0 | INC_PWM1 | INC_PWM2);

    /* Set the PWMs work at counting up mode after SYNC */
    PWM_SetCounterDirAfterSync(PWM0, COUNT_UP);
    PWM_SetCounterDirAfterSync(PWM1, COUNT_UP);
    PWM_SetCounterDirAfterSync(PWM2, COUNT_UP);

    /*
     * Set the value will be loaded to TBCNT after SYNC signal.
     */
    PWM_SetSyncReloadValue(PWM0, (PWM0->CMPA));
    PWM_SetSyncReloadValue(PWM1, 0);
    PWM_SetSyncReloadValue(PWM2, (PWM2->CMPA));

    /* Synchronize when PIN_GPIO0 is high, This interface will set GPIO as input */
    PWM_SetSyncFromGPIO(PIN_GPIO0, GPIO_LEVEL_HIGH);

    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
