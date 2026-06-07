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


int32_t                 i32result_out;                                              /* Output Value */


/**************************************************************************
 *
 * @brief      PGA-ADC Calibration Function to get PGA-ADC system calibration parameter
 *              (1) Enable Channel Fractional Result;
 *              (2) First DPGA_P DPGA_N connect to AGND, result is Vadc_out1;                                         
 *              (3) In 4x amplification factor, DPGA_P connect to 0.6V, 
 *               DPGA_N connect to AGND, result is Vadc_out2;                                    
 *              (4) ADCOFFSET=Vadc_out1;
 *              (5) ADCGAIN=32768*  (4*(0.6V/3.657143*4096)*2^7)/(Vadc_out2-Vadc_out1);
 *
 *        Key_points:
 *              (1) Can only use ADC_SetChannelOffset() and ADC_SetChannelGain() 
 *              to set ADCOFFSET and ADCGAIN in PGA-ADC Channel, other Channel
 *              is prohibit.
 *              (2) When PGA-ADC Channel is trim, can not use this Channel
 *              to measure ADC alone, because the PGA-ADC trim parameter is 
 *              not suitable to ADC alone
 *
 **************************************************************************/


int main(void)
{
    uint32_t j;
    
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

    printf("\n\n************** DPGA Calibration Test Start ******************\n");
    
    ADC_EnableChannelFractionalResult(ADC, ADC_CH1);
    ADC_EnableChannelFractionalResult(ADC, ADC_CH0);

    /* Init DPGA mode */
    PGA_InitDPGA(DPGA_GAIN_4X);

    /* Enable PGA */
    PGA_EnableDPGA();
    
    /* Differential ADC Init, collect the signal from DPGAP and DPGAN */
    ADC_EasyInit2(ADC, ADC_CH1, ADC_IN_DPGAP_OUT, ADC_IN_DPGAN_OUT, ADC_SOC_TRIGGER_FROM_SOFTWARE);

    /* Enable ADC */
    ADC_Enable(ADC);
    
    ADC_EnableChannelInt(ADC, ADC_CH1);
    
    ADC_SetChannelOffset(ADC, ADC_CH1, 0);
    ADC_SetChannelGain(ADC, ADC_CH1, 32768);
    
    printf("ChannelOffset %d\n", ADC_GetChannelOffset(ADC, ADC_CH1));
    printf("ChannelOffset %d\n", ADC_GetChannelGain(ADC, ADC_CH1));
    
    /* Set sample and convert time */
    ADC_SetSampleAndConvertTime(
        ADC,
        ADC_CH1,
        8000U,
        ADC_DEFAULT_CONVERSION_TIME_NS
    );
    
    ADC_SetChannelResultAverageCount(ADC,ADC_CH1,ADC_AVERAGE_COUNT_128);
    
    for(j = 0; j < 5; j ++)
    {
        PGA_DisableDPGABypass(); 
        Delay_Ms(10);
          
        /* Use software to trigger ADC CH1 to work */
        ADC_ForceChannelSOC(ADC, ADC_CH1);

        /* Wait until ADC conversion finished (Interrupt flag is set) */
        while (ADC_GetChannelIntFlag(ADC, ADC_CH1) == 0);

        /* Get the ADC CH result */
        i32result_out = ((int32_t)(READ_REG( (ADC)->ADCRESULT[ADC_CH1] )));

        /* Clear channel Int */
        ADC_ClearChannelInt(ADC, ADC_CH1);

        
        printf("The out is %d\n", i32result_out);
    }    
    
    while (1)
    {
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
