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
#define PWM_FREQ                            10000 /* 10kHz PWM */
#define PWM_DeadTimeNs                      400   /* 400 ns */

/*usd the count to calculate the period*/
#define CNTTOFREQ(x)                        (CLOCK_GetModuleClock(ECAP_MODULE) / (x))

uint32_t TStamp0, TStamp1, TStamp2, TStamp3;
uint32_t u32PWMPeriod;


/*************************************************************************************************************************
 *
 * @brief      In this case, In this case, PIN_GPIO12 and PIN_GPIO13 used as PWM output and ECAP input, and ECAP work in 
 *             ECAP Dual pin operation mode .
 *
 *            -------                            PIN_GPIO12                   -------
 *           |       |                               -                       |       |
 *           |       |<-----------------------------| |<---------------------|  PWM  |
 *           |       |  ECAP captured pin           | |    PWM output        |       |
 *           |       |                               -                        -------
 *           |       |                              / \
 *           |       |                               |
 *           |  ECAP |                               |
 *           |       |                                -------PIN_GPIO12 used as PWM output, also as the ECAP captured pin
 *           |       |
 *           |       |                           PIN_GPIO13                   -------
 *           |       |                               -                       |       |
 *           |       |<-----------------------------| |<---------------------|  PWM  |
 *           |       |  ECAP captured pin           | |    PWM output        |       |
 *            -------                                -                        -------
 *                                                  / \
 *                                                   |
 *                                                   |
 *                                                    -------PIN_GPIO13 used as PWM output, also as the ECAP captured pin
 *
 *
 *            showed below:
 *                           -------          -------           ------
 *                          |       |        |      |          |      |          |
 *                          |       |        |      |          |      |          |
 *                                   --------        ----------        ----------             CHA
 *                                          / \                      / \
 *                                           |                        |
 *                                           0                        2
 *
 *                                   -------          --------          --------
 *                          |       |       |        |        |        |        |
 *                          |       |       |        |        |        |        |
 *                           -------         --------          --------          --------     CHB
 *                                                  / \                        / \
 *                                                   |                          |
 *                                                   1                          3
 *
 *************************************************************************************************************************/

void ECAP_CaptureModeDualPinInit(ECAP_REGS *ECAPx, PIN_NameEnum ePinName1,  PIN_NameEnum ePinName2)
{
    /* Open ECAP clock */
    CLOCK_EnableModule(ECAP_MODULE);

    /* ECAP Init */
    ECAP->CAPSRCCTL |= CAPSRCCTL_POL1_(GPIO_LEVEL_HIGH);
    ECAP->CAPSRCCTL |= CAPSRCCTL_IOSEL1_(ePinName2);

    /* Configure IO Pin for capture */
    ECAP_SetInput(ECAPx, ePinName1, GPIO_LEVEL_HIGH);

    ECAPx->CAPCTL =   CAPCTL_APWMMODE_CAPTURE_MODE        /* Configure ECAP as Capture mode             */
                      | CAPCTL_CAPLDEN_ENABLE               /* Enable Cap Register loading on a capture event */
                      | CAPCTL_STOPWRAP_ON_CAPTURE_EVENT3   /* Stop/Wrap after Capture Event 3            */
                      | CAPCTL_ONESHOT_DISABLE              /* Operate in Continous mode                  */
                      | CAPCTL_CAP0POL_TRIG_ON_RISING_EDGE  /* Event 0 occurs on pulse rising edge        */
                      | CAPCTL_CAP1POL_TRIG_ON_RISING_EDGE  /* Event 1 occurs on pulse rising edge       */
                      | CAPCTL_CAP2POL_TRIG_ON_FALLING_EDGE /* Event 2 occurs on pulse falling edge        */
                      | CAPCTL_CAP3POL_TRIG_ON_FALLING_EDGE /* Event 3 occurs on pulse falling edge       */
                      | CAPCTL_CNTRST0_ENABLE               /* Reset capture counter when Event 0 occurs  */
                      | CAPCTL_CNTRST1_ENABLE               /* Reset capture counter when Event 1 occurs  */
                      | CAPCTL_CNTRST2_ENABLE               /* Reset capture counter when Event 2 occurs  */
                      | CAPCTL_CNTRST3_ENABLE               /* Reset capture counter when Event 3 occurs  */
                      | CAPCTL_TSCNTRUN_STOP_COUNTER;       /* Disable ECAP counter                       */

    /* Enable Dual pin capture mode */
    ECAP->CAPCTL |= CAPCTL_DUALPIN_ENABLE;

    /* Disable Capture event interrupt */
    ECAPx->CAPIE = 0U;
}


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

    /* Init PWM1, PWM freq will be set as 10kHz in this function */
    PWM_InitComplementaryPairChannel(PWM1, PWM_FREQ, PWM_DeadTimeNs);

    /* Select PIN as the channel A/B output of PWM1 */
    PIN_SetChannel(PIN_GPIO12, PIN_GPIO12_PWM1A);
    PIN_SetChannel(PIN_GPIO13, PIN_GPIO13_PWM1B);

    /* Start PWM1 */
    PWM_RunCounter(PWM1);

    /* ECAP Dual Pin Init */
    ECAP_CaptureModeDualPinInit(ECAP, PIN_GPIO12, PIN_GPIO13);

    PIN_EnableInputChannel(PIN_GPIO12, PIN_GPIO12_GPIO12);
    PIN_EnableInputChannel(PIN_GPIO13, PIN_GPIO13_GPIO13);

    /* The smaller the value, the more accurate the measurement result, but the more susceptible to interference */
    PIN_SetDeglitchWindow(DGCLKCTL_DIV_(0x0));

    /* Set the count reset back to zero when event3 happened */
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT0);
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT1);
    ECAP_DisableEventResetCounter(ECAP, ECAP_CEVT2);
    ECAP_EnableEventResetCounter(ECAP, ECAP_CEVT3);

    /* Can divide the input signal to observe higher frequency signals */
    ECAP_SetEventDiv(ECAP, 1);

    /* Enable global interrupt of EACP */
    NVIC_EnableIRQ(ECAP_IRQn);

    /* Enable EVT3 overflow Interrupt */
    ECAP_DisableInt(ECAP, ECAP_INT_CEVT0);
    ECAP_DisableInt(ECAP, ECAP_INT_CEVT1);
    ECAP_DisableInt(ECAP, ECAP_INT_CEVT2);
    ECAP_EnableInt(ECAP, ECAP_INT_CEVT3);

    /* Start ECAP */
    ECAP_RunCounter(ECAP);

    while (1)
    {

    }
}


void ECAP_IRQHandler(void)
{
    uint32_t cnt1, cnt2;

    TStamp0 = ECAP->CAP0;
    TStamp1 = ECAP->CAP1;
    TStamp2 = ECAP->CAP2;
    TStamp3 = ECAP->CAP3;

    printf("ECAP->CAP0 = %d\n", TStamp0);
    printf("ECAP->CAP1 = %d\n", TStamp1);
    printf("ECAP->CAP2 = %d\n", TStamp2);
    printf("ECAP->CAP3 = %d\n", TStamp3);

    cnt1 = TStamp1 - TStamp0;
    cnt2 = TStamp3 - TStamp2;

    printf("Fre = %dHz\n", CNTTOFREQ(cnt1 + cnt2));
    printf("Duty = %d%%\n",  cnt1 * 100 / ((cnt1 + cnt2)));

    /* Clear CEVT3 */
    ECAP_ClearInt(ECAP, ECAP_INT_CEVT3);
    ECAP_ClearInt(ECAP, ECAP_INT_GLOBAL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
