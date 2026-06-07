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
#define              PWM_FREQ                             2000                                /* 2kHz PWM */
#define              PWM_DB_NS                            100                                /* 100ns */


uint32_t             u32PWMPeriod;
int32_t              i32Result;
uint32_t             u32Count                             = 0;


/*************************************************************************************************************************
 *
 * @brief      In this case, PWM1SOCA trigger the ADC0 event
 *
 *        Key_points:
 *                  (1)if you want to observe the trigger signal, do not use the J-LINK download the code, because the
 *        observe PIN_GPIO18 will be occupied by J-LINK SWCK/TCLK
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

    /* Select the channel A/B output of PWM1 respectively */
    PIN_SetChannel(PIN_GPIO12, PIN_GPIO12_PWM1A);
    PIN_SetChannel(PIN_GPIO13, PIN_GPIO13_PWM1B);

    /* set the GPIO to observe the SYNC signal*/
    PIN_SetChannel(PIN_GPIO18, PIN_GPIO18_PWMSOCO);

    /* Initial Basic Complementary PWM */
    PWM_InitComplementaryPairChannel(PWM1, PWM_FREQ, PWM_DB_NS);

    /* Enable PWM1SOCA output to the pin */
    PWMCFG->SOCAOCTL = (PWMCFG->SOCAOCTL & (~SOCAOCTL_SOCA1EN_Msk)) | SOCAOCTL_SOCA1EN_ENABLE;

    /* Set pulse duration of PWMSOCA output to the pin */
    PWMCFG->SOCAOCTL = (PWMCFG->SOCAOCTL & (~SOCAOCTL_DURATION_Msk)) | SOCAOCTL_DURATION_32_PWM_CLK;


    /* Set PWM1A output 25% duty waveform */
    u32PWMPeriod = PWM_GetShadowPRD(PWM1);
    PWM_SetCMPA(PWM1, (u32PWMPeriod * 3) / 4);

    /* Start counting */
    PWM_RunCounter(PWM1);

    /* PWM trigger timing selecting */
    PWM_SetSOCATiming(PWM1, EQU_ZERO);

    /* PWM trigger period selecting */
    PWM_SetSOCAPeriod(PWM1, ON_1ST_EVENT);

    /* Enable PWM SOCA trigger */
    PWM_EnableSOCA(PWM1);

    /* ADC initial */
    ADC_EasyInit1(ADC, ADC_CH0, PIN_GPIO0, ADC_SOC_TRIGGER_FROM_PWM1SOCA);

    /* Enable ADC */
    ADC_Enable(ADC);

    /* SOC0 averaging 4 times */
    ADC_SetChannelResultAverageCount(ADC, ADC_CH0, ADC_AVERAGE_COUNT_4);

    /* INT service routine configuration */
    NVIC_SetPriority(ADCCH0_IRQn, 1);
    NVIC_EnableIRQ(ADCCH0_IRQn);

    /* Enable SOC interrupt */
    ADC_EnableChannelInt(ADC, ADC_CH0);

    while (1)
    {

    }
}


void ADCCH0_IRQHandler(void)
{
    /* The result */
    if (u32Count >= 15)
    {
        printf("CH0 %d\n", ADC_GetChannelResult(ADC, ADC_CH0));
        u32Count = 0;
    }

    u32Count++;

    /* Clear ADC SOC0 INT flag */
    ADC_ClearChannelInt(ADC, ADC_CH0);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
