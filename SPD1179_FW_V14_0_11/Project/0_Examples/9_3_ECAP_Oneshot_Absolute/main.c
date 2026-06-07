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
#define PWM_FREQ                                    10000                                               /* 10kHz PWM */
#define ECAP_PIN                                    PIN_GPIO14                                          /* ECAP PIN */
#define ECAP_PIN_GPIO_FUNC                          PIN_GPIO14_GPIO14                                   /* ECAP PIN act as GPIO function */
#define ECAP_PIN_PWM_FUNC                           PIN_GPIO14_PWM2A                                    /* ECAP PIN act as PWM function */
/*usd the count to calculate the period*/
#define CNTTOFREQ(x)                                 (CLOCK_GetModuleClock(ECAP_MODULE) / (x))


uint32_t TStamp0, TStamp1, TStamp2, TStamp3;
uint32_t u32PWMPeriod;


/*************************************************************************************************************************
 *
 * @brief      In this case, In this case, PIN_GPIO14 used as PWM output and ECAP input, and ECAP work in oneshot absolute
 *             operation mode .
 *
 *            -------                            PIN_GPIO14                       -------
 *           |       |                               -                       |       |
 *           | ECAP  |<-----------------------------| |<---------------------|  PWM  |
 *           |       |  ECAP captured pin           | |    PWM output        |       |
 *           |       |                               -                        -------
 *            -------                               / \
 *                                                   |
 *                                                   |
 *                                                    -------PIN_GPIO14 used as PWM output, also as the ECAP captured pin
 *
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

    printf("Enter the test\n");

    /* Init PWM2, PWM freq will be set as 10kHz in this function */
    PWM_InitSingleChannel(PWM2, PWM_CHA, PWM_FREQ);

    /* Set PWM2A output 50% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM2);
    PWM_SetCMPA(PWM2, u32PWMPeriod / 2);

    /* Start PWM2 */
    PWM_RunCounter(PWM2);

    /* ECAP Init */
    ECAP_CaptureModeInit(ECAP, ECAP_PIN);

    /* Set ECAP as onshot mode */
    ECAP_EnableOneshotMode(ECAP);

    /* Can divide the input signal to observe higher frequency signals */
    ECAP_SetEventDiv(ECAP, 1);

    /* RE-arm ECAP event count register */
    ECAP_OneshotReArm(ECAP);

    /* Set the count reset back to zero when event3 happened */
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT0);
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT1);
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT2);
    ECAP_EnableEventResetCounter(ECAP, ECAP_CEVT3);

    /* Enable global interrupt of EACP */
    NVIC_EnableIRQ(ECAP_IRQn);

    /* Enable EVT3 overflow Interrupt */
    ECAP_EnableInt(ECAP, ECAP_INT_CEVT3);

    /* Select ECAP_PIN as the channel A output of PWM2 */
    PIN_SetChannel(ECAP_PIN, ECAP_PIN_PWM_FUNC);
    PIN_EnableInputChannel(ECAP_PIN, ECAP_PIN_GPIO_FUNC);

    /* Enable Pin input deglitch filter */
    PIN_EnableDeglitch(ECAP_PIN);

    /* The smaller the value, the more accurate the measurement result, but the more susceptible to interference */
    PIN_SetDeglitchWindow(DGCLKCTL_DIV_(0x0));

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
    printf("Fre = %dHz\n", CNTTOFREQ(cnt));

    /* Clear CEVT3 */
    ECAP_ClearInt(ECAP, ECAP_INT_CEVT3);
    ECAP_ClearInt(ECAP, ECAP_INT_GLOBAL);
    ECAP_OneshotReArm(ECAP);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
