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
#define PWM_FREQ                                             10000                                         /* 10kHz PWM */
/*usd the count to calculate the period*/
#define CNTTOFREQ(x)                                        (CLOCK_GetModuleClock(ECAP_MODULE) / (x))


uint32_t TStamp0, TStamp1, TStamp2, TStamp3;
uint32_t u32PWMPeriod;


/*************************************************************************************************************************
 *
 * @brief      In this case, In this case, PIN_GPIO14 used as PWM output and ECAP input, and ECAP work in continue absolute
 *             operation mode .
 *
 *            -------                            PIN_GPIO14                   -------
 *           |       |                               -                       |       |
 *           | ECAP  |<-----------------------------| |<---------------------|  PWM  |
 *           |       |  ECAP captured pin           | |    PWM output        |       |
 *            -------                                -                        -------
 *                                                  / \
 *                                                   |
 *                                                   |
 *                                                    -------PIN_GPIO14 used as PWM output, also as the ECAP captured pin
 *
 *             Please keep in mind that don't do to much in the Int function, which can cause captured value over-write.
 *             Key Point:
 *                     <1>:For Continue mode, user do not care about exactly each incoming event, so we do not add extra 4
 *                         event cycle to initialize the divider.
 *
 *                     <2>:As showed below:
 *                           -------          --------          --------
 *                          |       |        |        |        |        |        |
 *                          |       |        |        |        |        |        |
 *                                   --------          --------          --------
 *                         / \     / \      / \      / \      / \      / \      / \
 *                          |       |        |        |        |        |        |
 *                          1       2        3        4        5        6        7
 *
 *             If there are 7 Int had happened, there will be 7 count value need to store into ECAP->CAP0~3.
 *
 *             Take a scenarios into account, 3 INT had happened, then ECAP->CAP0/ECAP->CAP1/ECAP->CAP2 store the value
 *             captured, but you do too much work in INT of 3 before reading ECAP->CAP0~2, then there are other 2 INT
 *             happened, then the 2 new value will store in ECAP->CAPA3 and ECAP->CAP0,which cause ECAP->CAP0 over written,
 *             as a result, ECAP->CAP0 is bigger than ECAP->CAP1~3, this is fatal in a sys.
 *
 *************************************************************************************************************************/


int main(void)
{
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

    /* Init PWM2, PWM freq will be set as 10kHz in this function */
    PWM_InitSingleChannel(PWM2, PWM_CHA, PWM_FREQ);

    /* Set PWM2A output 50% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM2);
    PWM_SetCMPA(PWM2, u32PWMPeriod / 2);

    /* Start PWM2 */
    PWM_RunCounter(PWM2);

    /* ECAP Init */
    ECAP_CaptureModeInit(ECAP, PIN_GPIO14);

    /* Select PIN_GPIO14 as the channel A output of PWM2 */
    PIN_SetChannel(PIN_GPIO14, PIN_GPIO14_PWM2A);
    PIN_EnableInputChannel(PIN_GPIO14, PIN_GPIO14_GPIO14);

    /* Enable Pin input deglitch filter */
    PIN_EnableDeglitch(PIN_GPIO14);

    /* The smaller the value, the more accurate the measurement result, but the more susceptible to interference */
    PIN_SetDeglitchWindow(DGCLKCTL_DIV_(0x0));

    /* Set the count reset back to zero when event3 happened */
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT0);
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT1);
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT2);
    ECAP_EnableEventResetCounter(ECAP, ECAP_CEVT3);

    /* Enable global interrupt of EACP */
    NVIC_EnableIRQ(ECAP_IRQn);

    /* Enable EVT3 overflow Interrupt */
    ECAP_EnableInt(ECAP, ECAP_INT_CEVT3);

    /* Start ECAP */
    ECAP_RunCounter(ECAP);

    while (1)
    {

    }
}


void ECAP_IRQHandler(void)
{
    uint32_t cnt;

    TStamp0 = ECAP->CAP0;
    TStamp1 = ECAP->CAP1;
    TStamp2 = ECAP->CAP2;
    TStamp3 = ECAP->CAP3;

    cnt = ((TStamp2 - TStamp0) + (TStamp3 - TStamp1)) / 2;
    printf("Fre %d\n", CNTTOFREQ(cnt));

    /* Clear CEVT3 */
    ECAP_ClearInt(ECAP, ECAP_INT_CEVT3);
    ECAP_ClearInt(ECAP, ECAP_INT_GLOBAL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
