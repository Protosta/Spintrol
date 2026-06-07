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


#define REF3V3_CODE      15502147584  // Ideal code for 3.3V input related to +-3.657143V range. 3696(ideal_code)*32768*128

int32_t               old_adc_sha_offset     = 0;             /* sampler A offset */
int32_t               old_adc_sha_gain       = 0;             /* sampler A Gain */

int32_t               adc_sha_offset         = 0;             /* sampler A offset */
int32_t               adc_sha_gain           = 0;             /* sampler A Gain */


/*************************************************************************************************************************
 *
 * @brief      ADC Calibration Function to get ADC calibration parameter
 *             method for sampler ADC A : (1) the two channel of sampler connect to AGND, and save the measure result as
 *                                            'adc_sha_offset'
 *                                        (2) connect the two channel of sampler to ANA_IN0(3.3V) and ANA_IN1(0V), the measure result
 *                                            is 'VDD_CODE'
 *                                        (3) use 'adc_sha_offset' and 'VDD_CODE' to calculate 'adc_sha_gain'
 *                                        (4) from now on, we get the gain and offset calibration value : 'adc_sha_gain' and
 *                                            'adc_sha_offset'
 *
 *
 *************************************************************************************************************************/


int main(void)
{
    CLOCK_InitWithRCO(100000000);

    Delay_Init();

    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    printf("Enter the test\n");
    
    old_adc_sha_offset = ADC_GetSHOffset(ADC,ADC_SH0);
    old_adc_sha_gain = ADC_GetSHGain(ADC,ADC_SH0);
    
    printf("old_adc_sha_offset %d\n", old_adc_sha_offset);
    printf("old_adc_sha_gain %d\n", old_adc_sha_gain);

    printf("\n************** ADC Calibration Test Start ******************\n");

    /* Enable ADC Module Clock */
    CLOCK_EnableModule(ADC_MODULE);
    
    ADC_Enable(ADC);

    /* Div ADC clk, the more lower clock the more accurate the sample result ,now the clock frequency = systemclk / 2*/
    CLOCK_SetModuleDiv(ADC_MODULE, 2);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    /* Enable ADC Interrupt Flag */
    ADC_EnableChannelInt(ADC, ADC_CH0);
    ADC_EnableChannelInt(ADC, ADC_CH1);

    Delay_Us(100);
    
    ADC_EnableChannelFractionalResult(ADC, ADC_CH0);
    
    /* CH0, Set sample time and conversion time */
    ADC_SetSampleAndConvertTime(ADC, ADC_CH0, ADC_DEFAULT_SAMPLE_TIME_NS, ADC_DEFAULT_CONVERSION_TIME_NS);

    /* trigger source selection */
    ADC_SetChannelSOCTriggerSource(ADC, ADC_CH0, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Set averaging 16 times */
    ADC_SetChannelResultAverageCount(ADC, ADC_CH0, ADC_AVERAGE_COUNT_16);

    /* positive terminal select AGND, negative terminal select AGND */
    ADC_SetChannelSHPositiveInput(ADC, ADC_CH0, ADC_SH0_P_GND);
    ADC_SetChannelSHNegativeInput(ADC, ADC_CH0, ADC_SH0_N_GND);

    /* sampler enable */
    ADC_SetChannelSH(ADC, ADC_CH0, ADC_SH_SEL_0);

    /* clear INT0 */
    ADC_ClearChannelInt(ADC, ADC_CH0);

    /* Software trigger CH0 */
    ADC_ForceChannelSOC(ADC, ADC_CH0);

    /* wait for ADC conversion done */
    while (ADC_GetChannelIntFlag(ADC, ADC_CH0) == 0);
    
    ADC_EnableChannelFractionalResult(ADC, ADC_CH1);

    /* CH1, Set sample time and conversion time */
    ADC_SetSampleAndConvertTime(ADC, ADC_CH1, ADC_DEFAULT_SAMPLE_TIME_NS, ADC_DEFAULT_CONVERSION_TIME_NS);

    /* trigger source selection */
    ADC_SetChannelSOCTriggerSource(ADC, ADC_CH1, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Set averaging 16 times */
    ADC_SetChannelResultAverageCount(ADC, ADC_CH1, ADC_AVERAGE_COUNT_16);

    /* positive terminal select ANA_IN0(3.3V), negative terminal select ANA_IN1(0V) */
    ADC_SetChannelSHPositiveInput(ADC, ADC_CH1, ADC_SH0_P_ANA_IN0);
    ADC_SetChannelSHNegativeInput(ADC, ADC_CH1, ADC_SH0_N_ANA_IN1);

    /* sampler enable */
    ADC_SetChannelSH(ADC, ADC_CH1, ADC_SH_SEL_0);

    /* clear INT1 */
    ADC_ClearChannelInt(ADC, ADC_CH1);

    /* Software trigger CH1 */
    ADC_ForceChannelSOC(ADC, ADC_CH1);

    /* wait for ADC conversion done */
    while (ADC_GetChannelIntFlag(ADC, ADC_CH1) == 0);

    printf("Measure AGND  Code is %d \n", ADC->ADCRESULT[0]);
    printf("Measure VDD33 Code is %d \n", ADC->ADCRESULT[1]);

    adc_sha_offset = ADC->ADCRESULT[0];

    adc_sha_gain = ADC->ADCRESULT[1];
    adc_sha_gain = adc_sha_gain - ADC->ADCRESULT[0];
    adc_sha_gain = REF3V3_CODE / adc_sha_gain;

    printf("ADC Offset: %d \n", adc_sha_offset);
    printf("ADC Gain:   %d \n", adc_sha_gain);

    printf("\n************** ADC Calibration Test End ******************\n");

    printf("offset change percent %f %%\n", (float)(adc_sha_offset - old_adc_sha_offset)/old_adc_sha_offset*100);
    printf("gain change percent %f %%\n", (float)(adc_sha_gain - old_adc_sha_gain)/old_adc_sha_gain*100);
    while (1)
    {
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
