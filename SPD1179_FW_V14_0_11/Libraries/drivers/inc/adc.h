/******************************************************************************
 * @file     adc.h
 * @brief    ADC driver header file.
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
 *
 * @attention
 * THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION REGARDING
 * THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM. SPINTROL SH0LL NOT BE
 * LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL DOES NOT GUARANTEE THE
 * CORRECTNESS OF THIS SOFTWARE AND RESERVES THE RIGHT TO MODIFY THE SOFTWARE
 * WITHOUT NOTIFICATION.
 *
 ******************************************************************************/


#ifndef ADC_H
#define ADC_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  ADC channel and result related
 */
#define __ADC_CHANNEL_MASK          ((1U << NUM_OF_ADC_CHANNEL) - 1U)
#define __ADC_CODE_MAGNITUDE        (1 << (ADC_RESOLUTION - 1))
#define __ADC_RESULT_MIN            ((int)(- __ADC_CODE_MAGNITUDE))
#define __ADC_RESULT_MAX            ((int)(__ADC_CODE_MAGNITUDE - 1))
#define __ADC_RESULT_MASK           ((1 << ADC_RESOLUTION) - 1)
#define __PPU_RESULT_MIN            ((int)(-(1 << ADC_RESOLUTION)))
#define __PPU_RESULT_MAX            ((int)((1 << ADC_RESOLUTION) - 1))




/**
 *  @brief  ADC default sampling and conversion time
 *          User can adjust with different application
 */
#define ADC_DEFAULT_SAMPLE_TIME_NS          (200U)
#define ADC_DEFAULT_CONVERSION_TIME_NS      (200U)




/**
 *  @brief  ADC default gain and offset value
 *          for each SH (Sampling Holder) and each CH (Channel)
 */
#define ADC_DEFAULT_GAIN        (0x8000U)
#define ADC_DEFAULT_OFFSET      (0)




/**
 *  @brief  ADC default reference value for PPU (Post Process Unit)
 */
#define ADC_PPU_DEFAULT_REF     (0)




/**
 *  @brief  ADC max sample time and conversion time
 */
#define ADC_MAX_SAMPLE_TIME (255U)
#define ADC_MAX_CONVERSION_TIME (63U)




/**
 *  @brief  ADC SH (Sampling Holder) Type Definition
 */
typedef enum
{
    ADC_SH0        =  0U,  /*!< SH 0           */
#if (NUM_OF_ADC_SH > 1)
    ADC_SH1        =  1U,  /*!< SH 1           */
#endif
#if (NUM_OF_ADC_SH > 2)
    ADC_SH2        =  2U,  /*!< SH 2           */
#endif
} ADC_SamplingHolderEnum;




/**
 *  @brief  ADC CH (Channel) Type Definition
 */
typedef enum
{
    ADC_CH0       =  0U,  /*!< ADC channel  0 */
#if (NUM_OF_ADC_CHANNEL > 1)
    ADC_CH1       =  1U,  /*!< ADC channel  1 */
#endif
#if (NUM_OF_ADC_CHANNEL > 2)
    ADC_CH2       =  2U,  /*!< ADC channel  2 */
#endif
#if (NUM_OF_ADC_CHANNEL > 3)
    ADC_CH3       =  3U,  /*!< ADC channel  3 */
#endif
#if (NUM_OF_ADC_CHANNEL > 4)
    ADC_CH4       =  4U,  /*!< ADC channel  4 */
#endif
#if (NUM_OF_ADC_CHANNEL > 5)
    ADC_CH5       =  5U,  /*!< ADC channel  5 */
#endif
#if (NUM_OF_ADC_CHANNEL > 6)
    ADC_CH6       =  6U,  /*!< ADC channel  6 */
#endif
#if (NUM_OF_ADC_CHANNEL > 7)
    ADC_CH7       =  7U,  /*!< ADC channel  7 */
#endif
#if (NUM_OF_ADC_CHANNEL > 8)
    ADC_CH8       =  8U,  /*!< ADC channel  8 */
#endif
#if (NUM_OF_ADC_CHANNEL > 9)
    ADC_CH9       =  9U,  /*!< ADC channel  9 */
#endif
#if (NUM_OF_ADC_CHANNEL > 10)
    ADC_CH10      = 10U,  /*!< ADC channel 10 */
#endif
#if (NUM_OF_ADC_CHANNEL > 11)
    ADC_CH11      = 11U,  /*!< ADC channel 11 */
#endif
#if (NUM_OF_ADC_CHANNEL > 12)
    ADC_CH12      = 12U,  /*!< ADC channel 12 */
#endif
#if (NUM_OF_ADC_CHANNEL > 13)
    ADC_CH13      = 13U,  /*!< ADC channel 13 */
#endif
#if (NUM_OF_ADC_CHANNEL > 14)
    ADC_CH14      = 14U,  /*!< ADC channel 14 */
#endif
#if (NUM_OF_ADC_CHANNEL > 15)
    ADC_CH15      = 15U,  /*!< ADC channel 15 */
#endif
} ADC_ChannelEnum;




/**
 *  @brief  ADC PPU (Post Process Unit) Type Definition
 */
typedef enum
{
#if (NUM_OF_ADC_PPU > 0)
    ADC_PPU0       =  0U,  /*!< ADC PPU 0      */
#endif
#if (NUM_OF_ADC_PPU > 1)
    ADC_PPU1       =  1U,  /*!< ADC PPU 1      */
#endif
#if (NUM_OF_ADC_PPU > 2)
    ADC_PPU2       =  2U,  /*!< ADC PPU 2      */
#endif
#if (NUM_OF_ADC_PPU > 3)
    ADC_PPU3       =  3U,  /*!< ADC PPU 3      */
#endif
#if (NUM_OF_ADC_PPU > 4)
    ADC_PPU4       =  4U,  /*!< ADC PPU 4      */
#endif
#if (NUM_OF_ADC_PPU > 5)
    ADC_PPU5       =  5U,  /*!< ADC PPU 5      */
#endif
#if (NUM_OF_ADC_PPU > 6)
    ADC_PPU6       =  6U,  /*!< ADC PPU 6      */
#endif
#if (NUM_OF_ADC_PPU > 7)
    ADC_PPU7       =  7U,  /*!< ADC PPU 7      */
#endif
} ADC_PostProcessUnitEnum;




/**
 *  @brief  ADC Channel SH (Sampler & Holder) Select Type Definition
 */
typedef enum
{
    ADC_SH_SEL_NONE = 0,  /*!< No SH selected as ADC channel input                  */
    ADC_SH_SEL_0    = 1,  /*!< Select SH_0 sequential sampling mode                 */
#if (NUM_OF_ADC_SH > 1)
    ADC_SH_SEL_1    = 2,  /*!< Select SH_1 sequential sampling mode                 */
#endif
#if (NUM_OF_ADC_SH == 2)
    ADC_SH_SEL_01   = 3,  /*!< Select SH_0,SH_1 simultaneously sampling mode        */
#endif
#if (NUM_OF_ADC_SH > 2)
    ADC_SH_SEL_2    = 3,  /*!< Select SH_2 sequential sampling mode                 */
    ADC_SH_SEL_01   = 4,  /*!< Select SH_0,SH_1 simultaneously sampling mode        */
    ADC_SH_SEL_12   = 5,  /*!< Select SH_1,SH_2 simultaneously sampling mode        */
    ADC_SH_SEL_02   = 6,  /*!< Select SH_0,SH_2 simultaneously sampling mode        */
    ADC_SH_SEL_012  = 7,  /*!< Select SH_0,SH_1,SH_2 simultaneously sampling mode   */
#endif
} ADC_Channel_SHSelectEnum;




/**
 *  @brief  ADC Channel SOC (Start Of Conversion) Type Definition
 */
typedef enum
{
    ADC_CH0_SOC     = (1U << ADC_CH0),  /*!< ADC channel  0 SOC */
#if (NUM_OF_ADC_CHANNEL > 1)
    ADC_CH1_SOC     = (1U << ADC_CH1),  /*!< ADC channel  1 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 2)
    ADC_CH2_SOC     = (1U << ADC_CH2),  /*!< ADC channel  2 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 3)
    ADC_CH3_SOC     = (1U << ADC_CH3),  /*!< ADC channel  3 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 4)
    ADC_CH4_SOC     = (1U << ADC_CH4),  /*!< ADC channel  4 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 5)
    ADC_CH5_SOC     = (1U << ADC_CH5),  /*!< ADC channel  5 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 6)
    ADC_CH6_SOC     = (1U << ADC_CH6),  /*!< ADC channel  6 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 7)
    ADC_CH7_SOC     = (1U << ADC_CH7),  /*!< ADC channel  7 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 8)
    ADC_CH8_SOC     = (1U << ADC_CH8),  /*!< ADC channel  8 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 9)
    ADC_CH9_SOC     = (1U << ADC_CH9),  /*!< ADC channel  9 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 10)
    ADC_CH10_SOC    = (1U << ADC_CH10), /*!< ADC channel 10 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 11)
    ADC_CH11_SOC    = (1U << ADC_CH11), /*!< ADC channel 11 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 12)
    ADC_CH12_SOC    = (1U << ADC_CH12), /*!< ADC channel 12 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 13)
    ADC_CH13_SOC    = (1U << ADC_CH13), /*!< ADC channel 13 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 14)
    ADC_CH14_SOC    = (1U << ADC_CH14), /*!< ADC channel 14 SOC */
#endif
#if (NUM_OF_ADC_CHANNEL > 15)
    ADC_CH15_SOC    = (1U << ADC_CH15), /*!< ADC channel 15 SOC */
#endif
    ADC_CH_ALL_SOC  = ((1U << NUM_OF_ADC_CHANNEL) - 1), /*!<    */
} ADC_Channel_SOCEnum;




/**
 *  @brief  ADC Channel INT (Interrupt) Type Definition
 */
typedef enum
{
    ADC_CH0_INT     = (1U << ADC_CH0),  /*!< ADC channel 0  interrupt   */
#if (NUM_OF_ADC_CHANNEL > 1)
    ADC_CH1_INT     = (1U << ADC_CH1),  /*!< ADC channel 1  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 2)
    ADC_CH2_INT     = (1U << ADC_CH2),  /*!< ADC channel 2  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 3)
    ADC_CH3_INT     = (1U << ADC_CH3),  /*!< ADC channel 3  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 4)
    ADC_CH4_INT     = (1U << ADC_CH4),  /*!< ADC channel 4  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 5)
    ADC_CH5_INT     = (1U << ADC_CH5),  /*!< ADC channel 5  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 6)
    ADC_CH6_INT     = (1U << ADC_CH6),  /*!< ADC channel 6  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 7)
    ADC_CH7_INT     = (1U << ADC_CH7),  /*!< ADC channel 7  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 8)
    ADC_CH8_INT     = (1U << ADC_CH8),  /*!< ADC channel 8  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 9)
    ADC_CH9_INT     = (1U << ADC_CH9),  /*!< ADC channel 9  interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 10)
    ADC_CH10_INT    = (1U << ADC_CH10), /*!< ADC channel 10 interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 11)
    ADC_CH11_INT    = (1U << ADC_CH11), /*!< ADC channel 11 interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 12)
    ADC_CH12_INT    = (1U << ADC_CH12), /*!< ADC channel 12 interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 13)
    ADC_CH13_INT    = (1U << ADC_CH13), /*!< ADC channel 13 interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 14)
    ADC_CH14_INT    = (1U << ADC_CH14), /*!< ADC channel 14 interrupt   */
#endif
#if (NUM_OF_ADC_CHANNEL > 15)
    ADC_CH15_INT    = (1U << ADC_CH15), /*!< ADC channel 15 interrupt   */
#endif
    ADC_CH_ALL_INT  = ((1U << NUM_OF_ADC_CHANNEL) - 1), /*!<    */
} ADC_Channel_IntEnum;




/**
 *  @brief  ADC Channel DMA (Direct Memory Access) Type Definition
 */
typedef enum
{
    ADC_CH0_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH0),   /*!< ADC channel 0  DMA  */
    ADC_CH1_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH1),   /*!< ADC channel 1  DMA  */
    ADC_CH2_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH2),   /*!< ADC channel 2  DMA  */
    ADC_CH3_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH3),   /*!< ADC channel 3  DMA  */
    ADC_CH4_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH4),   /*!< ADC channel 4  DMA  */
    ADC_CH5_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH5),   /*!< ADC channel 5  DMA  */
    ADC_CH6_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH6),   /*!< ADC channel 6  DMA  */
    ADC_CH7_DMA     = (ADCCTL_DMAEN0_Msk << ADC_CH7),   /*!< ADC channel 7  DMA  */
    ADC_CH_ALL_DMA  = ADC_CH0_DMA | ADC_CH1_DMA
                    | ADC_CH2_DMA | ADC_CH3_DMA
                    | ADC_CH4_DMA | ADC_CH5_DMA
                    | ADC_CH6_DMA | ADC_CH7_DMA,        /*!< ADC all channel DMA */
} ADC_Channel_DMAEnum;




/**
 *  @brief  ADC SOC (Start Of Conversion) Priority Type Definition
 *          Specify higher priority other than round robin priority mode
 */
typedef enum
{
    ADC_PRIORITY_HIGHER_AT_SOC0  =  0,  /*!< All SOCs priority follow the rule of round robin mode     */
#if (NUM_OF_ADC_CHANNEL > 1)
    ADC_PRIORITY_HIGHER_AT_SOC1  =  1,  /*!< SOC[0:0] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 2)
    ADC_PRIORITY_HIGHER_AT_SOC2  =  2,  /*!< SOC[0:1] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 3)
    ADC_PRIORITY_HIGHER_AT_SOC3  =  3,  /*!< SOC[0:2] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 4)
    ADC_PRIORITY_HIGHER_AT_SOC4  =  4,  /*!< SOC[0:3] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 5)
    ADC_PRIORITY_HIGHER_AT_SOC5  =  5,  /*!< SOC[0:4] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 6)
    ADC_PRIORITY_HIGHER_AT_SOC6  =  6,  /*!< SOC[0:5] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 7)
    ADC_PRIORITY_HIGHER_AT_SOC7  =  7,  /*!< SOC[0:6] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 8)
    ADC_PRIORITY_HIGHER_AT_SOC8  =  8,  /*!< SOC[0:7] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 9)
    ADC_PRIORITY_HIGHER_AT_SOC9  =  9,  /*!< SOC[0:8] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 10)
    ADC_PRIORITY_HIGHER_AT_SOC10 = 10,  /*!< SOC[0:9] are higher priority, others in round robin mode  */
#endif
#if (NUM_OF_ADC_CHANNEL > 11)
    ADC_PRIORITY_HIGHER_AT_SOC11 = 11,  /*!< SOC[0:10] are higher priority, others in round robin mode */
#endif
#if (NUM_OF_ADC_CHANNEL > 12)
    ADC_PRIORITY_HIGHER_AT_SOC12 = 12,  /*!< SOC[0:11] are higher priority, others in round robin mode */
#endif
#if (NUM_OF_ADC_CHANNEL > 13)
    ADC_PRIORITY_HIGHER_AT_SOC13 = 13,  /*!< SOC[0:12] are higher priority, others in round robin mode */
#endif
#if (NUM_OF_ADC_CHANNEL > 14)
    ADC_PRIORITY_HIGHER_AT_SOC14 = 14,  /*!< SOC[0:13] are higher priority, others in round robin mode */
#endif
#if (NUM_OF_ADC_CHANNEL > 15)
    ADC_PRIORITY_HIGHER_AT_SOC15 = 15,  /*!< SOC[0:14] are higher priority, others in round robin mode */
#endif
} ADC_SOCPriorityEnum;




/**
 *  @brief  ADC Channel SOC (Start Of Conversion) Trigger Source Type Definition
 */
typedef enum
{
    ADC_SOC_TRIGGER_FROM_SOFTWARE   = 0x0000,   /*!< SOC[x] from software force trigger */

    ADC_SOC_TRIGGER_FROM_TIMER0     = 0x0001,   /*!< SOC[x] from TIMER0                 */
    ADC_SOC_TRIGGER_FROM_TIMER1     = 0x0002,   /*!< SOC[x] from TIMER1                 */
    ADC_SOC_TRIGGER_FROM_TIMER2     = 0x0003,   /*!< SOC[x] from TIMER2                 */
    ADC_SOC_TRIGGER_FROM_EXT        = 0x0004,   /*!< SOC[x] from EXTERNAL IO            */
    // Group 0
    ADC_SOC_TRIGGER_FROM_PWM0SOCA   = 0x0005,   /*!< SOC[x] from PWM0 SOCA              */
    ADC_SOC_TRIGGER_FROM_PWM0SOCB   = 0x0006,   /*!< SOC[x] from PWM0 SOCB              */
    ADC_SOC_TRIGGER_FROM_PWM0SOCC   = 0x0007,   /*!< SOC[x] from PWM0 SOCC              */
    ADC_SOC_TRIGGER_FROM_PWM1SOCA   = 0x0008,   /*!< SOC[x] from PWM1 SOCA              */
    ADC_SOC_TRIGGER_FROM_PWM1SOCB   = 0x0009,   /*!< SOC[x] from PWM1 SOCB              */
    ADC_SOC_TRIGGER_FROM_PWM1SOCC   = 0x000A,   /*!< SOC[x] from PWM1 SOCC              */
    ADC_SOC_TRIGGER_FROM_PWM2SOCA   = 0x000B,   /*!< SOC[x] from PWM2 SOCA              */
    ADC_SOC_TRIGGER_FROM_PWM2SOCB   = 0x000C,   /*!< SOC[x] from PWM2 SOCB              */
    ADC_SOC_TRIGGER_FROM_PWM2SOCC   = 0x000D,   /*!< SOC[x] from PWM2 SOCC              */
    ADC_SOC_TRIGGER_FROM_PWM3SOCA   = 0x000E,   /*!< SOC[x] from PWM3 SOCA              */
    ADC_SOC_TRIGGER_FROM_PWM3SOCB   = 0x000F,   /*!< SOC[x] from PWM3 SOCB              */

    // Below options have high priority if SOC from interrupt is enabled
    ADC_SOC_TRIGGER_FROM_INT0       = 0x1000,   /*!< SOC[x] from CH[0] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT1       = 0x1001,   /*!< SOC[x] from CH[1] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT2       = 0x1002,   /*!< SOC[x] from CH[2] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT3       = 0x1003,   /*!< SOC[x] from CH[3] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT4       = 0x1004,   /*!< SOC[x] from CH[4] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT5       = 0x1005,   /*!< SOC[x] from CH[5] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT6       = 0x1006,   /*!< SOC[x] from CH[6] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT7       = 0x1007,   /*!< SOC[x] from CH[7] interrupt       */
#if (NUM_OF_ADC_CHANNEL > 8)
    ADC_SOC_TRIGGER_FROM_INT8       = 0x1008,   /*!< SOC[x] from CH[8] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT9       = 0x1009,   /*!< SOC[x] from CH[9] interrupt       */
    ADC_SOC_TRIGGER_FROM_INT10      = 0x100A,   /*!< SOC[x] from CH[10] interrupt      */
    ADC_SOC_TRIGGER_FROM_INT11      = 0x100B,   /*!< SOC[x] from CH[11] interrupt      */
    ADC_SOC_TRIGGER_FROM_INT12      = 0x100C,   /*!< SOC[x] from CH[12] interrupt      */
    ADC_SOC_TRIGGER_FROM_INT13      = 0x100D,   /*!< SOC[x] from CH[13] interrupt      */
    ADC_SOC_TRIGGER_FROM_INT14      = 0x100E,   /*!< SOC[x] from CH[14] interrupt      */
    ADC_SOC_TRIGGER_FROM_INT15      = 0x100F,   /*!< SOC[x] from CH[15] interrupt      */
#endif
} ADC_Channel_SOCTriggerSourceEnum;




/**
 *  @brief  ADC SH (Sampling Holder) input Selection Type Definition
 *
 * | SEL_CHxP/N | SH0_P      | SH0_P Description    | SH0_N      | SH0_N Description   |
 * | ---------- | ------     | -------------------- | ------     | ------------------- |
 * | 0          | GND        | Analog GND           | GND        | Analog GND          |
 * | 1          | TSENSOR_P  | T-sensor Output 1    | TSENSOR_N  | T-sensor Output 0   |
 * | 2          | DPGAP_OUT  | DPGA positive output | DPGAN_OUT  | PGA negative output |
 * | 3          | ANA_IN0    | ADC Input 0          | ANA_IN1    | ADC Input 1         |
 * | 4          | ANA_IN2    | ADC Input 2          | ANA_IN3    | ADC Input 3         |
 * | 5          | ANA_IN4    | ADC Input 4          | PHV        | PHC from Benz       |
 * | 6          | SPGA       | Single PGA output    | PHW        | PHW from Benz       |
 * | 7          | ATEST      | ATEST output voltage | PHC        | PHV from Benz       |
 * | 8          | DACBUF     | DAC buffer output    | -          | -                   |
 * | 9          | DAC0       | DAC0 output          | -          | -                   |
 * | 10         | VDD12      | Digital 1.2V Power   | -          | -                   |
 * | 11         | VDD33      | Analog 3.3V Power    | -          | -                   |
 * | 12         | PHU        | PHU from Benz        | -          | -                   |
 * | 13         | PHV        | PHC from Benz        | -          | -                   |
 * | 14         | PHW        | PHW from Benz        | -          | -                   |
 * | 15         | PHC        | PHC from Benz        | -          | -                   |
 */

typedef enum
{
    ADC_SH0_P_GND                =  0U,  /*!< Analog GND                         */
    ADC_SH0_P_TSENSOR_P          =  1U,  /*!< T-sensor positive                  */
    ADC_SH0_P_DPGAP_OUT          =  2U,  /*!< PGA positive output                */
    ADC_SH0_P_ANA_IN0            =  3U,  /*!< Analog input 0                     */
    ADC_SH0_P_ANA_IN2            =  4U,  /*!< Analog input 2                     */
    ADC_SH0_P_ANA_IN4            =  5U,  /*!< Aanlog input 4                     */
    ADC_SH0_P_SPGA_OUT           =  6U,  /*!< Single-ended PGA output            */
    ADC_SH0_P_ATEST              =  7U,  /*!< ATEST output voltage               */
    ADC_SH0_P_DACBUF             =  8U,  /*!< DAC buffer output                  */
    ADC_SH0_P_DAC0               =  9U,  /*!< DAC0 output                        */
    ADC_SH0_P_VDD12              = 10U,  /*!< Digital 1.2V power                 */
    ADC_SH0_P_VDD33              = 11U,  /*!< Analog 3.3V ower                   */
    ADC_SH0_P_ANA_IN9_PHU        = 12U,  /*!< Analog input 9 or PHU from HV      */
    ADC_SH0_P_ANA_IN10_PHV       = 13U,  /*!< Analog input 10 or PHV from HV     */
    ADC_SH0_P_ANA_IN11_PHW       = 14U,  /*!< Analog input 11 or PHW from HV     */
    ADC_SH0_P_ANA_IN13_VBATM_DIV = 15U,  /*!< Analog input 13 or divided VBATM from HV   */
} ADC_SH_PositiveInputEnum;

typedef enum
{
    ADC_SH0_N_GND               =  0U,  /*!< Analog GND                         */
    ADC_SH0_N_TSENSOR_N         =  1U,  /*!< T-sensor output 0                  */
    ADC_SH0_N_DPGAN_OUT         =  2U,  /*!< PGA negative output                */
    ADC_SH0_N_ANA_IN1           =  3U,  /*!< Analog input 1                     */
    ADC_SH0_N_ANA_IN3           =  4U,  /*!< Analog input 3                     */
    ADC_SH0_N_ANA_IN5           =  5U,  /*!< Analog input 5                     */
    ADC_SH0_N_ANA_IN6           =  6U,  /*!< Analog input 6                     */
    ADC_SH0_N_ANA_IN7           =  7U,  /*!< Analog input 7                     */
    ADC_SH0_N_ANA_IN8           =  8U,  /*!< Analog input 8                     */
    ADC_SH0_N_DAC1              =  9U,  /*!< DAC1 output                        */
    ADC_SH0_N_DAC2              =  10U, /*!< DAC2 output                        */
    ADC_SH0_N_ANA_IN12_PHC      =  11U, /*!< Analog input 12 or PHC from HV     */
} ADC_SH_NegativeInputEnum;




/**
 *  @brief  ADC Channel Result Average Count Type Definition
 */
typedef enum
{
    ADC_AVERAGE_COUNT_1    =  0U,  /*!< No average, result is the sample value               */
    ADC_AVERAGE_COUNT_2    =  1U,  /*!< Result is average of 2   samples caused by onece SOC */
    ADC_AVERAGE_COUNT_4    =  2U,  /*!< Result is average of 4   samples caused by onece SOC */
    ADC_AVERAGE_COUNT_8    =  3U,  /*!< Result is average of 8   samples caused by onece SOC */
    ADC_AVERAGE_COUNT_16   =  4U,  /*!< Result is average of 16  samples caused by onece SOC */
    ADC_AVERAGE_COUNT_32   =  5U,  /*!< Result is average of 32  samples caused by onece SOC */
    ADC_AVERAGE_COUNT_64   =  6U,  /*!< Result is average of 64  samples caused by onece SOC */
    ADC_AVERAGE_COUNT_128  =  7U,  /*!< Result is average of 128 samples caused by onece SOC */
} ADC_ResultAverageCountEnum;




/**
 *  @brief  ADC SH (Sampling Holder) Force Input Type Definition
 */
typedef enum
{
    ADC_SH_FORCE_DISABLE   = 0U,  /*!< Disable                                    */
    ADC_SH_FORCE_GND       = 2U,  /*!< Force SH positive/negative input tied low  */
    ADC_SH_FORCE_VDD33     = 3U,  /*!< Force SH positive/negative input tied high */
} ADC_SH_ForceInputEnum;




/**
 *  @brief  ADC PPU (Post Process Unit) Interrupt Type Definition
 */
typedef enum
{
    ADC_PPU_INT_TOO_LOW     = 1 << 0U,  /*!< PPU_RESULT < PPU_LOW_THRESHOLD     */
    ADC_PPU_INT_TOO_HIGH    = 1 << 1U,  /*!< PPU_RESULT > PPU_HIGH_THRESHOLD    */
    ADC_PPU_INT_CROSS_ZERO  = 1 << 2U,  /*!< PPU_RESULT cross ZERO              */
    ADC_PPU_INT_GLOBAL      = 1 << 3U,  /*!< Global interrupt                   */
    ADC_PPU_INT_ALL         = 0xFU      /*!< Used for all interrupts            */
} ADC_PPU_IntEnum;




/**
 *  @brief  ADC PPU (Post Process Unit) Event Type Definition
 */
typedef enum
{
    ADC_PPU_EVENT_TOO_LOW     = 1 << 0U,  /*!< PPU_RESULT < PPU_LOW_THRESHOLD   */
    ADC_PPU_EVENT_TOO_HIGH    = 1 << 1U,  /*!< PPU_RESULT > PPU_HIGH_THRESHOLD  */
    ADC_PPU_EVENT_CROSS_ZERO  = 1 << 2U,  /*!< PPU_RESULT cross ZERO            */
    ADC_PPU_EVENT_ALL         = 0x7U      /*!< Used for all events              */
} ADC_PPU_EventEnum;




/**
 *  @brief  ADC PPU (Post Process Unit) Data Process Type Definition
 */
typedef enum
{
    REFERENCE_MINUS_ADCRESULT = 0U, /*!< PPU_RESULT = PPU_REF    - CH_RESULT   */
    ADCRESULT_MINUS_REFERENCE = 1U, /*!< PPU_RESULT = CH_RESULT - PPU_REF      */
} ADC_PPU_DataProcessEnum;




/**
 *  @brief  ADC Input Pin Selection Table
 *          Encode logic for Non-GPIO pin:
 *            ( ( Sampler(4-bit) << 4 ) + SHInputSelect(4-bit) )
 *          Sampler
 *            - \ref 8  SH Positive
 *            - \ref 9  SH Negative
 */
typedef enum
{
    ADC_IN_TSENSOR_P        = (0x80U | ADC_SH0_P_TSENSOR_P),    /*!< SH positive terminal: T-sensor output 1       */
    ADC_IN_DPGAP_OUT        = (0x80U | ADC_SH0_P_DPGAP_OUT),    /*!< SH positive terminal: Positive output of DPGA */
    ADC_IN_GPIO0            = PIN_GPIO0,                        /*!< SH positive terminal: GPIO0                   */
    ADC_IN_GPIO2            = PIN_GPIO2,                        /*!< SH positive terminal: GPIO2                   */
    ADC_IN_GPIO4            = PIN_GPIO4,                        /*!< SH positive terminal: GPIO4                   */
    ADC_IN_SPGA_OUT         = (0x80U | ADC_SH0_P_SPGA_OUT),     /*!< SH positive terminal: Positive output of SPGA */
    ADC_IN_ATEST            = (0x80U | ADC_SH0_P_ATEST),        /*!< SH positive terminal: ATEST                   */
    ADC_IN_DACBUF           = (0x80U | ADC_SH0_P_DACBUF),       /*!< SH positive terminal: DAC BUF                 */
    ADC_IN_DAC0             = (0x80U | ADC_SH0_P_DAC0),         /*!< SH positive terminal: DAC0                    */
    ADC_IN_VDD12            = (0x80U | ADC_SH0_P_VDD12),        /*!< SH positive terminal: VDD12                   */
    ADC_IN_VDD33            = (0x80U | ADC_SH0_P_VDD33),        /*!< SH positive terminal: VDD33                   */
    ADC_IN_GPIO36_PHU       = PIN_GPIO36,                       /*!< SH positive terminal: GPIO36(PHU)             */
    ADC_IN_GPIO37_PHV       = PIN_GPIO37,                       /*!< SH both     terminal: GPIO37(PHV)             */
    ADC_IN_GPIO38_PHW       = PIN_GPIO38,                       /*!< SH both     terminal: GPIO38(PHW)             */
    ADC_IN_GPIO40_VBATM_DIV = PIN_GPIO40,                       /*!< SH both     terminal: GPIO40(VBATMDIV)        */
    
    ADC_IN_TSENSOR_N        = (0x90U | ADC_SH0_N_TSENSOR_N),    /*!< SH negative terminal: T-sensor output 0       */
    ADC_IN_DPGAN_OUT        = (0x90U | ADC_SH0_N_DPGAN_OUT),    /*!< SH negative terminal: Negative output of DPGA */
    ADC_IN_GPIO1            = PIN_GPIO1,                        /*!< SH negative terminal: GPIO1                   */
    ADC_IN_GPIO3            = PIN_GPIO3,                        /*!< SH negative terminal: GPIO3                   */
    ADC_IN_GPIO28           = PIN_GPIO28,                       /*!< SH negative terminal: GPIO28                  */
    ADC_IN_GPIO29           = PIN_GPIO29,                       /*!< SH negative terminal: GPIO29                  */
    ADC_IN_GPIO30           = PIN_GPIO30,                       /*!< SH negative terminal: GPIO30                  */
    ADC_IN_GPIO31           = PIN_GPIO31,                       /*!< SH negative terminal: GPIO31                  */
    ADC_IN_DAC1             = (0x90U | ADC_SH0_N_DAC1),         /*!< SH negative terminal: DAC1                    */
    ADC_IN_DAC2             = (0x90U | ADC_SH0_N_DAC2),         /*!< SH negative terminal: DAC2                    */
    ADC_IN_GPIO39_PHC       = PIN_GPIO39,                       /*!< SH negative terminal: GPIO39(PHC)             */
} ADC_InputSelectEnum;




/******************************************************************************
 * @brief      Force ADC FSM (Finite State Machine) control reset
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_Reset(ADCx)                                                         \
    SET_BITS( (ADCx)->ADCCTL, ADCCTL_RST_Msk )




/******************************************************************************
 * @brief      Disable ADCx module
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_Disable(ADCx)                                                       \
    CLEAR_BITS( (ADCx)->ADCCTL, ADCCTL_REFEN_Msk | ADCCTL_EN_Msk )




/******************************************************************************
 * @brief      Disable ADCx Reference
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_DisableReference(ADCx) \
    CLEAR_BITS( (ADCx)->ADCCTL, ADCCTL_REFEN_Msk )




/******************************************************************************
 * @brief      Get ADCx enable setting
 *
 * @param[in]  None
 *
 * @return     0     - ADC is not enable;
 *             not 0 - ADC is enable.
 *
 ******************************************************************************/
#define ADC_IsEnable(ADCx)                                                     \
    ( (ADCx)->ADCCTL & ADCCTL_EN_Msk )




/******************************************************************************
 * @brief      Get ADCx reference enable setting
 *
 * @param[in]  None
 *
 * @return     0     - ADC refeerence is not enable;
 *             not 0 - ADC refeerence is enable.
 *
 ******************************************************************************/
#define ADC_IsEnableReference(ADCx)                                            \
    ( (ADCx)->ADCCTL & ADCCTL_REFEN_Msk )




/******************************************************************************
 * @brief      Enable PPU[x]
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnablePPU(ADCx,ePPUx)                                               \
    SET_BITS( (ADCx)->PPUCTL[(ePPUx)], PPUCTL_EN_Msk )

#define ADC_DisablePPU(ADCx,ePPUx)                                              \
    CLEAR_BITS( (ADCx)->PPUCTL[(ePPUx)], PPUCTL_EN_Msk )





/******************************************************************************
 * @brief      Get PPU[x] enable setting
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnablePPU(ADCx,ePPUx)                                             \
    ( (ADCx)->PPUCTL[(ePPUx)] & (PPUCTL_EN_Msk) )




/******************************************************************************
 * @brief      ADC Enable T-Sensor
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableTSensor(ADCx)                                                 \
    SET_BITS( (ADCx)->TSENSCTL, TSENSCTL_EN_Msk )




/******************************************************************************
 * @brief      ADC Disable T-Sensor
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_DisableTSensor(ADCx)                                                \
    CLEAR_BITS( (ADCx)->TSENSCTL, TSENSCTL_EN_Msk )




/******************************************************************************
 * @brief      Get T-Sensor state
 *
 * @param[in]  None
 *
 * @return     0     - ADC TSensor is Disable
 *             1     - ADC TSensor is Enable
 *
 ******************************************************************************/
#define ADC_IsEnableTSensor(ADCx)                                               \
    ( (ADCx)->TSENSCTL & TSENSCTL_EN_Msk )




/******************************************************************************
 * @brief      Force SH[x] positive input
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 * @param[in]  eFrc  : Sampling Holder force input type defined by ADC_SH_ForceInputEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH_FORCE_DISABLE
 *                       - \ref ADC_SH_FORCE_GND
 *                       - \ref ADC_SH_FORCE_VCC
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_ForceSHPositiveInput(ADCx,eSHx,eFrc)                                \
    WRITE_FIELD( (ADCx)->ADCCTL,                                                  \
                 ADCCTL_SHFRCP0_Msk << ( (eSHx) << 2 ),                                      \
                 ADCCTL_SHFRCP0_Pos +  ( (eSHx) << 2 ),                                      \
                 (eFrc)                                                                      \
               )




/******************************************************************************
 * @brief      Get SH[x] force positive input setting
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     Sampling Holder force input type defined by ADC_SH_ForceInputEnum
 *
 ******************************************************************************/
#define ADC_GetSHPositiveForceInput(ADCx,eSHx)                                  \
    READ_FIELD( (ADCx)->ADCCTL,                                                   \
                ADCCTL_SHFRCP0_Msk << ( (eSHx) << 2 ),                                      \
                ADCCTL_SHFRCP0_Pos +  ( (eSHx) << 2 )                                       \
              )




/******************************************************************************
 * @brief      Force SH[x] negetive input
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 * @param[in]  eFrc  : Sampling Holder force input type defined by ADC_SH_ForceInputEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH_FORCE_DISABLE
 *                       - \ref ADC_SH_FORCE_GND
 *                       - \ref ADC_SH_FORCE_VCC
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_ForceSHNegativeInput(ADCx,eSHx,eFrc)                                \
    WRITE_FIELD( (ADCx)->ADCCTL,                                                  \
                 ADCCTL_SHFRCN0_Msk << ( (eSHx) << 2 ),                                      \
                 ADCCTL_SHFRCN0_Pos +  ( (eSHx) << 2 ),                                      \
                 (eFrc)                                                                      \
               )




/******************************************************************************
 * @brief      Get SH[x] force negetive input setting
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     Sampling Holder force input type defined by ADC_SH_ForceInputEnum
 *
 ******************************************************************************/
#define ADC_GetSHNegativeForceInput(ADCx,eSHx)                                  \
    READ_FIELD( (ADCx)->ADCCTL,                                                   \
                ADCCTL_SHFRCN0_Msk << ( (eSHx) << 2 ),                                      \
                ADCCTL_SHFRCN0_Pos +  ( (eSHx) << 2 )                                       \
              )




/******************************************************************************
 * @brief      Set SH[x] offset value
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 * @param[in]  i32Val: Signed value.
 *                     Valid range:
 *                       [   -4096
 *                         :  4095
 *                       ]
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetSHOffset(ADCx,eSHx,i32Val)                                       \
    WRITE_REG( (ADCx)->SHOFFSET[eSHx], i32Val )




/******************************************************************************
 * @brief      Get SH[x] offset value
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     Signed value.
 *             Range:
 *               [   -4096
 *                 :  4095
 *               ]
 *
 ******************************************************************************/
#define ADC_GetSHOffset(ADCx,eSHx)                                              \
    ( (int32_t)READ_REG( (ADCx)->SHOFFSET[eSHx] ) )




/******************************************************************************
 * @brief      Set SH[x] gain value
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 * @param[in]  u16Val: Unsigned value.
 *                     Valid range: [0:65536)
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetSHGain(ADCx,eSHx,u16Val)                                         \
    WRITE_REG( (ADCx)->SHGAIN[eSHx], u16Val )




/******************************************************************************
 * @brief      Get SH[x] gain value
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     Unsigned value.
 *             Range: [0:65536)
 *
 ******************************************************************************/
#define ADC_GetSHGain(ADCx,eSHx)                                                \
    READ_REG( (ADCx)->SHGAIN[eSHx] )




/******************************************************************************
 * @brief      Get SH[x] EOC (End Of Convertion) flag
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetSHEOCFlag(ADCx,eSHx)                                             \
    ( (ADCx)->SHFLG & (1U << (eSHx)) )




/******************************************************************************
 * @brief      Clear SH[x] EOC (End Of Convertion) flag
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearSHEOCFlag(ADCx,eSHx)                                           \
    WRITE_REG( (ADCx)->SHFLGCLR, (1U << (eSHx)) )




/******************************************************************************
 * @brief      Get SH[x] result after EOC (End Of Convertion)
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     Signed value.
 *             Range:
 *               [   -4096
 *                 :  4095
 *               ]
 *
 ******************************************************************************/
#define ADC_GetSHResult(ADCx,eSHx)                                              \
    ( (int32_t)READ_REG( (ADCx)->SHRAWCODE[eSHx] ) )




/******************************************************************************
 * @brief      Get SH[x] raw result after EOC (End Of Convertion)
 *
 * @param[in]  eSHx  : Sampling Holder x defined by ADC_SamplingHolderEnum
 *                     Following values are valid:
 *                       - \ref ADC_SH0
 *
 * @return     Unsigned value.
 *             Range: [ 0 : 8191 ]
 *
 ******************************************************************************/
#define ADC_GetSHRawResult(ADCx,eSHx)                                           \
    ( (uint32_t)( ADC_GetSHResult(ADCx, eSHx) + 4096 ) )




/******************************************************************************
 * @brief      Enable ADCx channels interrupt
 *
 * @param[in]  u32Ints: Channels interrupts defined by ADC_Channel_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_INT
 *                        - \ref ADC_CH0_INT ~ ADC_CH15_INT
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableMultiChannelInt(ADCx,u32Ints)                                 \
    SET_BITS( (ADCx)->ADCIE, (u32Ints) )

#define ADC_DisableMultiChannelInt(ADCx,u32Ints)                                \
    CLEAR_BITS( (ADCx)->ADCIE, (u32Ints) )




/******************************************************************************
 * @brief      Enable ADCx CH[x] interrupt
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableChannelInt(ADCx,eCHx)                                         \
    SET_BITS( (ADCx)->ADCIE, ( 1U << (eCHx) ) )

#define ADC_DisableChannelInt(ADCx,eCHx)                                        \
    CLEAR_BITS( (ADCx)->ADCIE, ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Get ADCx channels interrput setting
 *
 * @param[in]  u32Ints: Channels interrupt defined by ADC_Channel_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_INT
 *                        - \ref ADC_CH0_INT ~ ADC_CH15_INT
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnableMultiChannelInt(ADCx,u32Ints)                               \
    ( (ADCx)->ADCIE & (u32Ints) )




/******************************************************************************
 * @brief      Get ADCx CH[x] interrput setting
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnableChannelInt(ADCx,eCHx)                                       \
    ( (ADCx)->ADCIE & ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Get ADCx channels interrput flag
 *
 * @param[in]  u32Ints: Channels interrupt defined by ADC_Channel_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_INT
 *                        - \ref ADC_CH0_INT ~ ADC_CH15_INT
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetMultiChannelIntFlag(ADCx,u32Ints)                                \
    ( (ADCx)->ADCIF & (u32Ints) )




/******************************************************************************
 * @brief      Get ADCx CH[x] interrput flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetChannelIntFlag(ADCx,eCHx)                                        \
    ( (ADCx)->ADCIF & ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Clear ADCx channels interrupt flag
 *
 * @param[in]  u32Ints: Channels interrupt defined by ADC_Channel_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_INT
 *                        - \ref ADC_CH0_INT ~ ADC_CH15_INT
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearMultiChannelInt(ADCx,u32Ints)                                  \
    WRITE_REG( (ADCx)->ADCIC, (u32Ints) )




/******************************************************************************
 * @brief      Clear ADCx CH[x] interrput flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearChannelInt(ADCx,eCHx)                                          \
    WRITE_REG( (ADCx)->ADCIC, ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Get ADCx channels interrput overflow flag
 *
 * @param[in]  u32Ints: Channels interrupt defined by ADC_Channel_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_INT
 *                        - \ref ADC_CH0_INT ~ ADC_CH15_INT
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetMultiChannelIntOverflowFlag(ADCx,u32Ints)                        \
    ( (ADCx)->ADCIOVF & (u32Ints) )




/******************************************************************************
 * @brief      Get ADCx CH[x] interrput overflow flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetChannelIntOverflowFlag(ADCx,eCHx)                                \
    ( (ADCx)->ADCIOVF & ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Clear ADCx channels interrupt overflow flag
 *
 * @param[in]  u32Ints: Channels interrupt defined by ADC_Channel_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_INT
 *                        - \ref ADC_CH0_INT ~ ADC_CH15_INT
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearMultiChannelIntOverflowFlag(ADCx,u32Ints)                      \
    WRITE_REG( (ADCx)->ADCIOVFC, (u32Ints) )




/******************************************************************************
 * @brief      Clear ADCx CH[x] interrput overflow flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearChannelIntOverflowFlag(ADCx,eCHx)                              \
    WRITE_REG( (ADCx)->ADCIOVFC, ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Enable ADCx channels DMA
 *
 * @param[in]  u32DMAs: Channels DMA defined by ADC_Channel_DMAEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_DMA
 *                        - \ref ADC_CH0_DMA ~ ADC_CH7_DMA
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableMultiChannelDMA(ADCx,u32DMAs)                                 \
    SET_BITS( (ADCx)->ADCCTL, (u32DMAs) )

#define ADC_DisableMultiChannelDMA(ADCx,u32DMAs)                                \
    CLEAR_BITS( (ADCx)->ADCCTL, (u32DMAs) )




/******************************************************************************
 * @brief      Enable ADCx CH[x] DMA
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableChannelDMA(ADCx,eCHx)                                         \
    SET_BITS( (ADCx)->ADCCTL, ADCCTL_DMAEN0_Msk << (eCHx) )

#define ADC_DisableChannelDMA(ADCx,eCHx)                                        \
    CLEAR_BITS( (ADCx)->ADCCTL, ADCCTL_DMAEN0_Msk << (eCHx) )




/******************************************************************************
 * @brief      Get ADCx channels DMA setting
 *
 * @param[in]  u32DMAs: Channels DMA defined by ADC_Channel_DMAEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_DMA
 *                        - \ref ADC_CH0_DMA ~ ADC_CH7_DMA
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnableMultiChannelDMA(ADCx,u32DMAs)                               \
    ( (ADCx)->ADCCTL & (u32DMAs) )




/******************************************************************************
 * @brief      Get ADCx CH[x] DMA setting
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnableChannelDMA(ADCx,eCHx)                                       \
    ( (ADCx)->ADCCTL & ( ADCCTL_DMAEN0_Msk << (eCHx) ) )




/******************************************************************************
 * @brief      Set ADCx channels SOC priority
 *
 * @param[in]  ePriority: SOC priority defined by ADC_SOCPriorityEnum
 *                        Only the following values are valid:
 *                          - \ref ADC_PRIORITY_HIGHER_AT_SOC0 ~ ADC_PRIORITY_HIGHER_AT_SOC15
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetSOCPriority(ADCx,ePriority)                                      \
    WRITE_FIELD( (ADCx)->ADCSOCPRICTL,                                          \
                 ADCSOCPRICTL_PRIORITY_Msk,                                     \
                 ADCSOCPRICTL_PRIORITY_Pos,                                     \
                 (ePriority)                                                    \
               )




/******************************************************************************
 * @brief      Get ADCx channels SOC priority setting
 *
 * @param[in]  None
 *
 * @return     SOC priority defined by ADC_SOCPriorityEnum
 *
 ******************************************************************************/
#define ADC_GetSOCPriority(ADCx)                                                \
    READ_FIELD( (ADCx)->ADCSOCPRICTL,                                           \
                ADCSOCPRICTL_PRIORITY_Msk,                                      \
                ADCSOCPRICTL_PRIORITY_Pos                                       \
              )




/******************************************************************************
 * @brief      Get Round Ring Pointer of ADCx channels SOC trigger
 *
 * @param[in]  None
 *
 * @return     Channel defined by ADC_ChannelEnum
 *
 ******************************************************************************/
#define ADC_GetRoundRingPointer(ADCx)                                           \
    READ_FIELD( (ADCx)->ADCSOCPRICTL,                                           \
                ADCSOCPRICTL_RRPOINTER_Msk,                                     \
                ADCSOCPRICTL_RRPOINTER_Pos                                      \
              )




/******************************************************************************
 * @brief      Enable channels SOC trigger from other channel interrupt
 *
 * @param[in]  u32SOCs: SOC masks defined by ADC_Channel_SOCEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_SOC
 *                        - \ref ADC_CH0_SOC ~ ADC_CH15_SOC
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableMultiChannelIntTriggerSOC(ADCx,u32SOCs)                       \
    SET_BITS( (ADCx)->ADCINTSOCEN, (u32SOCs) )

#define ADC_DisableMultiChannelIntTriggerSOC(ADCx,u32SOCs)                      \
    CLEAR_BITS( (ADCx)->ADCINTSOCEN, (u32SOCs) )




/******************************************************************************
 * @brief      Enable CH[x] SOC trigger from CH[y] interrupt
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableChannelIntTriggerSOC(ADCx,eCHx)                               \
    SET_BITS( (ADCx)->ADCINTSOCEN, 1U << (eCHx) )

#define ADC_DisableChannelIntTriggerSOC(ADCx,eCHx)                              \
    CLEAR_BITS( (ADCx)->ADCINTSOCEN, 1U << (eCHx) )




/******************************************************************************
 * @brief      Get channels SOC trigger from other channel interrupt setting
 *
 * @param[in]  u32SOCs: SOCs mask defined by ADC_Channel_SOCEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_SOC
 *                        - \ref ADC_CH0_SOC ~ ADC_CH15_SOC
 *
 * @return     0     - None of the queried SOCs is enabled;
 *             not 0 - Corresponding SOCs for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnableMultiChannelIntTriggerSOC(ADCx,u32SOCs)                     \
    ( (ADCx)->ADCINTSOCEN & (u32SOCs) )




/******************************************************************************
 * @brief      Get CH[x] SOC trigger from CH[y] interrupt setting
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried SOCs is enabled;
 *             not 0 - Corresponding SOCs for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnableChannelIntTriggerSOC(ADCx,eCHx)                             \
    ( (ADCx)->ADCINTSOCEN & ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Set CH[x] SOC triggered from which CH[y] interrupt
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eCHy:  Channel y defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 ******************************************************************************/
__STATIC_INLINE void ADC_SetChannelIntTriggerSOC(ADC_REGS *ADCx, ADC_ChannelEnum  eCHx, ADC_ChannelEnum  eCHy)                           \
    {                                                                           
        if ( eCHx < ADC_CH8 )                                                   
        {                                                                       
            WRITE_FIELD( (ADCx)->ADCINTSOCSEL[0],                               
                         ADCINTSOCSEL_CH0_Msk << ( (eCHx) << 2 ),               
                         ADCINTSOCSEL_CH0_Pos +  ( (eCHx) << 2 ),               
                         (eCHy)                                                 
                       );                                                       
        }                                                                       
        else                                                                    
        {                                                                       
            WRITE_FIELD( (ADCx)->ADCINTSOCSEL[1],                               
                         ADCINTSOCSEL_CH0_Msk << ( ((eCHx) - ADC_CH8) << 2 ),   
                         ADCINTSOCSEL_CH0_Pos +  ( ((eCHx) - ADC_CH8) << 2 ),   
                         (eCHy)                                                 
                       );                                                       
        }                                                                       
    }




/******************************************************************************
 * @brief      Get CH[x] SOC triggered from which channel interrupt
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Channel defined by ADC_ChannelEnum
 *
 ******************************************************************************/
__STATIC_INLINE ADC_ChannelEnum ADC_GetChannelIntTriggerSOC(ADC_REGS *ADCx, ADC_ChannelEnum eCHx)
{
    if(eCHx < ADC_CH8)
    {
        return (ADC_ChannelEnum)(
                   READ_FIELD((ADCx)->ADCINTSOCSEL[0],
                              ADCINTSOCSEL_CH0_Msk << ((eCHx) << 2),
                              ADCINTSOCSEL_CH0_Pos + ((eCHx) << 2)
                             )
               );
    }
    else
    {
        return (ADC_ChannelEnum)(
                   READ_FIELD((ADCx)->ADCINTSOCSEL[1],
                              ADCINTSOCSEL_CH0_Msk << (((eCHx) - ADC_CH8) << 2),
                              ADCINTSOCSEL_CH0_Pos + (((eCHx) - ADC_CH8) << 2)
                             )
               );
    }
}




/******************************************************************************
 * @brief      Set external SOC IO input source and polarity
 *
 * @param[in]  ePin: Select the GPIO pin for external input
 *                   Please refer to PIN_NameEnum
 * @param[in]  eLvl: Select the GPIO pin level for active external input
 *                   Please refer to LEVEL
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetExternalSOCInput(ADCx,ePin,eLvl)                                 \
    MODIFY_REG( (ADCx)->ADCEXTSOCCTL,                                             \
                ( ADCEXTSOCCTL_IOSEL_Msk | ADCEXTSOCCTL_POL_Msk ),                          \
                (   ( (ePin) << ADCEXTSOCCTL_IOSEL_Pos )                                    \
                    | ( (eLvl) << ADCEXTSOCCTL_POL_Pos   )                                    \
                )                                                                           \
              )




/******************************************************************************
 * @brief      Get external SOC IO input source
 *
 * @return     Get the GPIO number for external input
 *             Please refer to PIN_NameEnum
 *
 ******************************************************************************/
#define ADC_GetExternalSOCInputSource(ADCx)                                     \
    READ_FIELD( (ADCx)->ADCEXTSOCCTL, ADCEXTSOCCTL_IOSEL_Msk, ADCEXTSOCCTL_IOSEL_Pos )




/******************************************************************************
 * @brief      Get external SOC IO input polarity
 *
 * @return     Get the GPIO pin level for active external input
 *             Please refer to GPIO_LevelEnum
 *
 ******************************************************************************/
#define ADC_GetExternalSOCInputPolarity(ADCx)                                   \
    READ_FIELD( (ADCx)->ADCEXTSOCCTL, ADCEXTSOCCTL_POL_Msk, ADCEXTSOCCTL_POL_Pos )




/******************************************************************************
 * @brief      Set CH[x] Sampling Holder mode
 *
 * @param[in]  eCHx : Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eSel: Sampling Holder select defined by ADC_Channel_SHSelectEnum
 *                    If (NUM_OF_ADC_SH == 0 ) :
 *                      Only support sequential sampling mode,
                        following values are valid:
 *                          - \ref ADC_SH_SEL_NONE
 *                          - \ref ADC_SH_SEL_0
 *                    If (NUM_OF_ADC_SH == 3 ) :
 *                      If ( eCHx % 3 == 0 ), following values are valid:
 *                          - \ref ADC_SH_SEL_NONE
 *                          - \ref ADC_SH_SEL_0     -> Sequential sampling mode
 *                          - \ref ADC_SH_SEL_1     -> Sequential sampling mode
 *                          - \ref ADC_SH_SEL_2     -> Sequential sampling mode
 *                          - \ref ADC_SH_SEL_01    -> Simultaneous sampling mode
 *                          - \ref ADC_SH_SEL_12    -> Simultaneous sampling mode, SH0 will be disabled
 *                          - \ref ADC_SH_SEL_02    -> Simultaneous sampling mode
 *                          - \ref ADC_SH_SEL_012   -> Simultaneous sampling mode
 *                      If ( eCHx % 3 != 0 ) and eCHx isn't used in simultaneous
 *                      sampling mode, following values are valid:
 *                          - \ref ADC_SH_SEL_NONE
 *                          - \ref ADC_SH_SEL_0
 *                          - \ref ADC_SH_SEL_1
 *                          - \ref ADC_SH_SEL_2
 *
 * @return     None
 *
 * @note       If ( eCHx % 3 != 0 ) and eCHx is used in simultaneous sampling
 *             mode, its SOC controlled by CH[floor(eCHx/3)]
 *
 ******************************************************************************/
#define ADC_SetChannelSH(ADCx,eCHx,eSel)                                        \
    WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                        \
                 ADCCHCTL_SHSEL_Msk,                                            \
                 ADCCHCTL_SHSEL_Pos,                                            \
                 (eSel)                                                         \
               )




/******************************************************************************
 * @brief      Get CH[x] Sampling Holder mode
 *
 * @param[in]  eCHx : Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Sampling Holder selected defined by ADC_Channel_SHSelectEnum
 *
 ******************************************************************************/
#define ADC_GetChannelSH(ADCx,eCHx)                                             \
    READ_FIELD( (ADCx)->ADCCHCTL[eCHx],                                         \
                ADCCHCTL_SHSEL_Msk,                                             \
                ADCCHCTL_SHSEL_Pos                                              \
              )




/******************************************************************************
 * @brief      Set CH[x] SOC trigger source
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eSrc:  SOC source defined by ADC_Channel_SOCTriggerSourceEnum
 *                    Following values are valid:
 *                        - \ref ADC_SOC_TRIGGER_FROM_SOFTWARE
 *                        - \ref ADC_SOC_TRIGGER_FROM_TIMER0
 *                        - \ref ADC_SOC_TRIGGER_FROM_TIMER1
 *                        - \ref ADC_SOC_TRIGGER_FROM_TIMER2
 *                        - \ref ADC_SOC_TRIGGER_FROM_EXT
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM0SOCA
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM0SOCB
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM0SOCC
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM1SOCA
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM1SOCB
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM1SOCC
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM2SOCA
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM2SOCB
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM2SOCC
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM3SOCA
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM3SOCB
 *                        - \ref ADC_SOC_TRIGGER_FROM_PWM3SOCC
 *                        - \ref ADC_SOC_TRIGGER_FROM_INT0 ~ ADC_SOC_TRIGGER_FROM_INT15
 *
 * @return     None
 *
 * @note       If ( eCHx % 3 != 0 ) and eCHx is used in simultaneous sampling
 *             mode, its SOC controlled by CH[floor(eCHx/3)]
 *
 ******************************************************************************/
#define ADC_SetChannelSOCTriggerSource(ADCx,eCHx,eSrc)                          \
    {                                                                           \
        if ( eSrc >= ADC_SOC_TRIGGER_FROM_INT0 )                                \
        {                                                                       \
            ADC_SetChannelIntTriggerSOC(ADCx, eCHx, (ADC_ChannelEnum)((eSrc) & 0xFF));            \
            ADC_EnableChannelIntTriggerSOC(ADCx, eCHx);                         \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            ADC_DisableChannelIntTriggerSOC(ADCx, eCHx);                        \
            WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                \
                         ADCCHCTL_TRIGSEL_Msk,                                  \
                         ADCCHCTL_TRIGSEL_Pos,                                  \
                         (eSrc)                                                 \
                       );                                                       \
        }                                                                       \
    }




/******************************************************************************
 * @brief      Get CH[x] SOC trigger source
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     SOC source defined by ADC_Channel_SOCTriggerSourceEnum
 *
 ******************************************************************************/
__STATIC_INLINE ADC_Channel_SOCTriggerSourceEnum
ADC_GetChannelSOCTriggerSource(ADC_REGS *ADCx, ADC_ChannelEnum eCHx)
{
    if (ADC_IsEnableChannelIntTriggerSOC(ADCx, eCHx) != 0U)
    {
        return (ADC_Channel_SOCTriggerSourceEnum)(
                   ADC_GetChannelIntTriggerSOC(ADCx, eCHx) | 0x1000U);
    }
    else
    {
        return (ADC_Channel_SOCTriggerSourceEnum)(
                   READ_FIELD((ADCx)->ADCCHCTL[eCHx],
                              ADCCHCTL_TRIGSEL_Msk,
                              ADCCHCTL_TRIGSEL_Pos
                             )
               );
    }
}




/******************************************************************************
 * @brief      Set CH[x] Sampling Holder positive channel input
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eSrc:  Sampling Holder positive channel input source
 *                    defined by ADC_SH_PositiveInputEnum.
 *                    Following values are valid:
 *                      - \ref ADC_SH0_P_GND
 *                      - \ref ADC_SH0_P_TSENSOR_P
 *                      - \ref ADC_SH0_P_DPGAP_OUT
 *                      - \ref ADC_SH0_P_ANA_IN0
 *                      - \ref ADC_SH0_P_ANA_IN2
 *                      - \ref ADC_SH0_P_ANA_IN4
 *                      - \ref ADC_SH0_P_SPGA_OUT
 *                      - \ref ADC_SH0_P_ATEST
 *                      - \ref ADC_SH0_P_DACBUF
 *                      - \ref ADC_SH0_P_DAC0
 *                      - \ref ADC_SH0_P_VDD12
 *                      - \ref ADC_SH0_P_VDD33
 *                      - \ref ADC_SH0_P_PHU
 *                      - \ref ADC_SH0_P_PHV
 *                      - \ref ADC_SH0_P_PHW
 *                      - \ref ADC_SH0_P_VBAT_DIV
 *
 * @return     None
 *
 * @note       If ( eCHx % 3 != 0 ) and eCHx is used in simultaneous sampling
 *             mode, its SOC controlled by CH[floor(eCHx/3)], and:
 *             - if SH0 used in simultaneous sampling mode,
 *                 SH0 channel selection controlled by CH[floor(eCHx/3)+0]
 *             - if SH1 used in simultaneous sampling mode,
 *                 SH1 channel selection controlled by CH[floor(eCHx/3)+1]
 *             - if SH2 used in simultaneous sampling mode,
 *                 SH2 channel selection controlled by CH[floor(eCHx/3)+2]
 *
 ******************************************************************************/
#define ADC_SetChannelSHPositiveInput(ADCx,eCHx,eSrc)                           \
    WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                        \
                 ADCCHCTL_SHINSELP_Msk,                                         \
                 ADCCHCTL_SHINSELP_Pos,                                         \
                 (eSrc)                                                         \
               )




/******************************************************************************
 * @brief      Get CH[x] Sampling Holder positive channel input
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Sampling Holder positive channel input source
 *             defined by ADC_SH_PositiveInputEnum.
 *
 ******************************************************************************/
#define ADC_GetChannelSHPositiveInput(ADCx,eCHx)                                \
    READ_FIELD( (ADCx)->ADCCHCTL[eCHx],                                         \
                ADCCHCTL_SHINSELP_Msk,                                          \
                ADCCHCTL_SHINSELP_Pos                                           \
              )




/******************************************************************************
 * @brief      Set CH[x] Sampling Holder negative channel input
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eSrc:  Sampling Holder negative channel input source
 *                    defined by ADC_SH_NegativeInputEnum.
 *                    Following values are valid:
 *                      - \ref ADC_SH0_N_GND
 *                      - \ref ADC_SH0_N_TSENSOR_N
 *                      - \ref ADC_SH0_N_DPGAN_OUT
 *                      - \ref ADC_SH0_N_ANA_IN1
 *                      - \ref ADC_SH0_N_ANA_IN3
 *                      - \ref ADC_SH0_N_PHV
 *                      - \ref ADC_SH0_N_PHW
 *                      - \ref ADC_SH0_N_PHC
 *
 * @return     None
 *
 * @note       If ( eCHx % 3 != 0 ) and eCHx is used in simultaneous sampling
 *             mode, its SOC controlled by CH[floor(eCHx/3)], and:
 *             - if SH0 used in simultaneous sampling mode,
 *                 SH0 channel selection controlled by CH[floor(eCHx/3)+0]
 *             - if SH1 used in simultaneous sampling mode,
 *                 SH1 channel selection controlled by CH[floor(eCHx/3)+1]
 *             - if SH2 used in simultaneous sampling mode,
 *                 SH2 channel selection controlled by CH[floor(eCHx/3)+2]
 *
 ******************************************************************************/
#define ADC_SetChannelSHNegativeInput(ADCx,eCHx,eSrc)                           \
    WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                        \
                 ADCCHCTL_SHINSELN_Msk,                                         \
                 ADCCHCTL_SHINSELN_Pos,                                         \
                 (eSrc)                                                         \
               )




/******************************************************************************
 * @brief      Get CH[x] Sampling Holder negative channel input
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Sampling Holder negative channel input source
 *             defined by ADC_SH_NegativeInputEnum.
 *
 ******************************************************************************/
#define ADC_GetChannelSHNegativeInput(ADCx,eCHx)                                \
    READ_FIELD( (ADCx)->ADCCHCTL[eCHx],                                         \
                ADCCHCTL_SHINSELN_Msk,                                          \
                ADCCHCTL_SHINSELN_Pos                                           \
              )




/******************************************************************************
 * @brief      Set CH[x] result oversample type
 *             ADCx result is the average value of oversample.
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eType: Oversample type defined by ADC_ResultAverageCountEnum.
 *                    Following values are valid:
 *                      - \ref ADC_AVERAGE_COUNT_1
 *                      - \ref ADC_AVERAGE_COUNT_2
 *                      - \ref ADC_AVERAGE_COUNT_4
 *                      - \ref ADC_AVERAGE_COUNT_8
 *                      - \ref ADC_AVERAGE_COUNT_16
 *                      - \ref ADC_AVERAGE_COUNT_32
 *                      - \ref ADC_AVERAGE_COUNT_64
 *                      - \ref ADC_AVERAGE_COUNT_128
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetChannelResultAverageCount(ADCx,eCHx,eType)                       \
    WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                        \
                 ADCCHCTL_AVGCNT_Msk,                                           \
                 ADCCHCTL_AVGCNT_Pos,                                           \
                 (eType)                                                        \
               )




/******************************************************************************
 * @brief      Get CH[x] result oversample setting
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Oversample type defined by ADC_ResultAverageCountEnum.
 *
 ******************************************************************************/
#define ADC_GetChannelResultAverageCount(ADCx,eCHx)                             \
    READ_FIELD( (ADCx)->ADCCHCTL[eCHx],                                         \
                ADCCHCTL_AVGCNT_Msk,                                            \
                ADCCHCTL_AVGCNT_Pos                                             \
              )




/******************************************************************************
 * @brief      Enable CH[x] to have 20-bit result, where
 *             the 7 LSBs are the fractional part
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnableChannelFractionalResult(ADCx,eCHx)                            \
    SET_BITS( (ADCx)->ADCCHCTL[eCHx], ADCCHCTL_FRACBIT_Msk)




/******************************************************************************
 * @brief      Set CH[x] to have only the 13-bit result
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_DisableChannelFractionalResult(ADCx,eCHx)                            \
    CLEAR_BITS( (ADCx)->ADCCHCTL[eCHx], ADCCHCTL_FRACBIT_Msk)




/******************************************************************************
 * @brief      Get CH[x] fractional result bit setting
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0    :  ADCRESULT[x] is 13-bit integer number
 *             Not 0:  ADCRESULT[x] is 20-bit and the 7 LSBs are the fractional part
 *
 ******************************************************************************/
#define ADC_IsEnableChannelFractionalResult(ADCx,eCHx)                          \
    ( (ADCx)->ADCCHCTL[eCHx] & ADCCHCTL_FRACBIT_Msk )




/******************************************************************************
 * @brief      Set CH[x] sample timer count value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  u8Cnt: Sample timer count value which worked on CLK_ADC.
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetChannelSampleTimeCount(ADCx,eCHx, u8Cnt)                         \
    WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                        \
                 ADCCHCTL_SAMPCNT_Msk,                                          \
                 ADCCHCTL_SAMPCNT_Pos,                                          \
                 (u8Cnt)                                                        \
               )




/******************************************************************************
 * @brief      Get CH[x] sample timer count value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Sample timer count value which worked on CLK_ADC.
 *
 ******************************************************************************/
#define ADC_GetChannelSampleTimeCount(ADCx,eCHx)                                \
    READ_FIELD( (ADCx)->ADCCHCTL[eCHx],                                         \
                ADCCHCTL_SAMPCNT_Msk,                                           \
                ADCCHCTL_SAMPCNT_Pos                                            \
              )




/******************************************************************************
 * @brief      Set CH[x] convert timer count value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  u8Cnt: Convert timer count value which worked on CLK_ADC.
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetChannelConvertTimeCount(ADCx,eCHx,u8Cnt)                         \
    WRITE_FIELD( (ADCx)->ADCCHCTL[eCHx],                                        \
                 ADCCHCTL_CONVCNT_Msk,                                          \
                 ADCCHCTL_CONVCNT_Pos,                                          \
                 (u8Cnt)                                                        \
               )




/******************************************************************************
 * @brief      Get CH[x] convert timer count value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Convert timer count value which worked on CLK_ADC.
 *
 ******************************************************************************/
#define ADC_GetChannelConvertTimeCount(ADCx,eCHx)                               \
    READ_FIELD( (ADCx)->ADCCHCTL[eCHx],                                         \
                ADCCHCTL_CONVCNT_Msk,                                           \
                ADCCHCTL_CONVCNT_Pos                                            \
              )




/******************************************************************************
 * @brief      Set CH[x] offset value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  i32Val: Signed value.
 *                     Valid range:
 *                       [   -4096
 *                         :  4095
 *                       ]
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetChannelOffset(ADCx,eCHx,i32Val)                                  \
    WRITE_REG( (ADCx)->ADCOFFSET[eCHx], i32Val )




/******************************************************************************
 * @brief      Get CH[x] offset value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Signed value.
 *             Range:
 *               [   -4096
 *                 :  4095
 *               ]
 *
 ******************************************************************************/
#define ADC_GetChannelOffset(ADCx,eCHx)                                         \
    ( (int32_t)READ_REG( (ADCx)->ADCOFFSET[eCHx] ) )




/******************************************************************************
 * @brief      Set CH[x] gain value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  u16Val: Unsigned value.
 *                     Valid range: [0:65536)
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetChannelGain(ADCx,eCHx,u16Val)                                    \
    WRITE_REG( (ADCx)->ADCGAIN[eCHx], u16Val )




/******************************************************************************
 * @brief      Get CH[x] gain value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Unsigned value.
 *             Range: [0:65536)
 *
 ******************************************************************************/
#define ADC_GetChannelGain(ADCx,eCHx)                                           \
    READ_REG( (ADCx)->ADCGAIN[eCHx] )




/******************************************************************************
 * @brief      Force trigger ADCx channels SOC
 *
 * @param[in]  u32SOCs: SOC masks defined by ADC_Channel_SOCEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_SOC
 *                        - \ref ADC_CH0_SOC ~ ADC_CH15_SOC
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ForceMultiChannelSOC(ADCx,u32SOCs)                                  \
    WRITE_REG( (ADCx)->ADCSOCFRC, (u32SOCs) )

#define ADC_TriggerMultiChannelSOC(ADCx,u32SOCs)                                \
    ADC_ForceMultiChannelSOC(ADCx,u32SOCs)




/******************************************************************************
 * @brief      Force trigger ADCx CH[x] SOC
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ForceChannelSOC(ADCx,eCHx)                                          \
    WRITE_REG( (ADCx)->ADCSOCFRC, 1U << (eCHx) )

#define ADC_TriggerChannelSOC(ADCx,eCHx)                                        \
    ADC_ForceChannelSOC(ADCx,eCHx)




/******************************************************************************
 * @brief      Get ADCx channels SOC trigger flag
 *
 * @param[in]  u32SOCs: SOC masks defined by ADC_Channel_SOCEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_SOC
 *                        - \ref ADC_CH0_SOC ~ ADC_CH15_SOC
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 * @note       These flags are self-cleared.
 *
 ******************************************************************************/
#define ADC_GetMultiChannelSOCFlag(ADCx,u32SOCs)                                \
    ( (ADCx)->ADCSOCFLG & (u32SOCs) )




/******************************************************************************
 * @brief      Get ADCx CH[x] SOC trigger flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 * @note       These flags are self-cleared.
 *
 ******************************************************************************/
#define ADC_GetChannelSOCFlag(ADCx,eCHx)                                        \
    ( (ADCx)->ADCSOCFLG & ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Get ADCx channels SOC trigger overflow flag
 *
 * @param[in]  u32SOCs: SOC masks defined by ADC_Channel_SOCEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_SOC
 *                        - \ref ADC_CH0_SOC ~ ADC_CH15_SOC
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetMultiChannelSOCOverflowFlag(ADCx,u32SOCs)                        \
    ( (ADCx)->ADCSOCOVF & (u32SOCs) )




/******************************************************************************
 * @brief      Get ADCx CH[x] SOC trigger overflow flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetChannelSOCOverflowFlag(ADCx,eCHx)                                \
    ( (ADCx)->ADCSOCOVF & ( 1U << (eCHx) ) )




/******************************************************************************
 * @brief      Clear ADCx channels SOC trigger overflow flag
 *
 * @param[in]  u32SOCs: SOC masks defined by ADC_Channel_SOCEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_CH_ALL_SOC
 *                        - \ref ADC_CH0_SOC ~ ADC_CH15_SOC
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearMultiChannelSOCOverflowFlag(ADCx,u32SOCs)                      \
    WRITE_REG( (ADCx)->ADCSOCOVFC, (u32SOCs) )




/******************************************************************************
 * @brief      Clear ADCx CH[x] SOC trigger overflow flag
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                        - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearChannelSOCOverflowFlag(ADCx,eCHx)                              \
    WRITE_REG( (ADCx)->ADCSOCOVFC, 1U << (eCHx) )




/******************************************************************************
 * @brief      Get CH[x] result value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Signed value.
 *             Range:
 *               [   -4096
 *                 :  4095
 *               ]
 *
 ******************************************************************************/
#define ADC_GetChannelResult(ADCx,eCHx)                                         \
    ( (int32_t)READ_REG( (ADCx)->ADCRESULT[eCHx] ) )




/******************************************************************************
 * @brief      Get CH[x] raw result value
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Unsigned value.
 *             Range: [ 0 : 8191 ]
 *
 ******************************************************************************/
#define ADC_GetChannelRawResult(ADCx,eCHx)                                      \
    ( (uint32_t)( ADC_GetChannelResult(ADCx, eCHx) + 4096 ) )




/******************************************************************************
 * @brief      For Single End Mode Only (One terminal is GND)
 *             Get Trim result(code) from ADCx result register
 *
 * @param[in]  eCHx:  Channel x defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 *
 * @return     Signed value.
 *             Range: [ 0 : 8191 ]
 *
 ******************************************************************************/
#define ADC_GetChannelAbsoluteResult(ADCx,eCHx)                                 \
    ( ABS( ADC_GetChannelResult(ADCx, eCHx) ) )




/******************************************************************************
 * @brief      Set PPU[x] input data and trigger source
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  eDSrc: Data source (channel x) defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  eTSrc: Delay source (channel x) defined by ADC_ChannelEnum
 *                    Following values are valid:
 *                      - \ref ADC_CH0 ~ ADC_CH15
 * @param[in]  ePType:  PPU data process type defined by ADC_PPU_DataProcessEnum
 *                      Following values are valid:
 *                        - \ref REFERENCE_MINUS_ADCRESULT
 *                        - \ref ADCRESULT_MINUS_REFERENCE
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetPPUInput(ADCx,ePPUx,eDSrc,eTSrc,ePType)                          \
    MODIFY_REG( (ADCx)->PPUCTL[(ePPUx)],                                        \
                (   PPUCTL_DATASEL_Msk                                          \
                    | PPUCTL_SOCSEL_Msk                                         \
                    | PPUCTL_POL_Msk                                            \
                ),                                                              \
                (                                                               \
                        ( (eDSrc) << PPUCTL_DATASEL_Pos )                       \
                        | ( (eTSrc) << PPUCTL_SOCSEL_Pos )                      \
                        | ( (ePType)<< PPUCTL_POL_Pos )                         \
                )                                                               \
              )




/******************************************************************************
 * @brief      Get PPU[x] input data source
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Data source (channel x) defined by ADC_ChannelEnum
 *
 ******************************************************************************/
#define ADC_GetPPUDataSource(ADCx,ePPUx)                                        \
    READ_FIELD(                                                                 \
            (ADCx)->PPUCTL[(ePPUx)],                                            \
            PPUCTL_DATASEL_Msk,                                                 \
            PPUCTL_DATASEL_Pos                                                  \
              )




/******************************************************************************
 * @brief      Get PPU[x] input trigger source
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Trigger source (SOC from channel x) defined by ADC_ChannelEnum
 *
 ******************************************************************************/
#define ADC_GetPPUTriggerSource(ADCx,ePPUx)                                     \
    READ_FIELD(                                                                 \
            (ADCx)->PPUCTL[(ePPUx)],                                            \
            PPUCTL_SOCSEL_Msk,                                                  \
            PPUCTL_SOCSEL_Pos                                                   \
              )




/******************************************************************************
 * @brief      Get PPU[x] data process type
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     PPU data process type defined by ADC_PPU_DataProcessEnum
 *
 ******************************************************************************/
#define ADC_GetPPUProcessType(ADCx,ePPUx)                                       \
    READ_FIELD(                                                                 \
            (ADCx)->PPUCTL[(ePPUx)],                                            \
            PPUCTL_POL_Msk,                                                     \
            PPUCTL_POL_Pos                                                      \
              )




/******************************************************************************
 * @brief      Enable PPU[x] result cycle-by-cycle clear
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnablePPUCycleClear(ADCx,ePPUx)                                     \
    SET_BITS( (ADCx)->PPUCTL[(ePPUx)], PPUCTL_CBCEN_Msk )

#define ADC_DisablePPUCycleClear(ADCx,ePPUx)                                    \
    CLEAR_BITS( (ADCx)->PPUCTL[(ePPUx)], PPUCTL_CBCEN_Msk )




/******************************************************************************
 * @brief      Get PPU[x] result cycle-by-cycle clear setting
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnablePPUCycleClear(ADCx,ePPUx)                                   \
    ( (ADCx)->PPUCTL[(ePPUx)] & PPUCTL_CBCEN_Msk )




/******************************************************************************
 * @brief      Set PPU[x] result high threshold
 *
 * @param[in]  ePPUx : PPU x defined by ADC_PostProcessUnitEnum
 *                     Following values are valid:
 *                       - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  i32Val: Signed value.
 *                     Valid range:
 *                       [   -8192
 *                         :  8191
 *                       ]
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetPPUHighThreshold(ADCx,ePPUx,i32Val)                              \
    WRITE_REG( (ADCx)->PPUTHH[(ePPUx)], (i32Val) )




/******************************************************************************
 * @brief      Get PPU[x] result high threshold
 *
 * @param[in]  ePPUx : PPU x defined by ADC_PostProcessUnitEnum
 *                     Following values are valid:
 *                       - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Signed value.
 *             Range:
 *               [   -8192
 *                 :  8191
 *               ]
 *
 ******************************************************************************/
#define ADC_GetPPUHighThreshold(ADCx,ePPUx)                                     \
    ( (int32_t)READ_REG( (ADCx)->PPUTHH[(ePPUx)]) )




/******************************************************************************
 * @brief      Set PPU[x] result low threshold
 *
 * @param[in]  ePPUx : PPU x defined by ADC_PostProcessUnitEnum
 *                     Following values are valid:
 *                       - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  i32Val: Signed value.
 *                     Valid range:
 *                       [   -8192
 *                         :  8191
 *                       ]
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetPPULowThreshold(ADCx,ePPUx,i32Val)                               \
    WRITE_REG( (ADCx)->PPUTHL[(ePPUx)], (i32Val) )




/******************************************************************************
 * @brief      Get PPU[x] result low threshold
 *
 * @param[in]  ePPUx : PPU x defined by ADC_PostProcessUnitEnum
 *                     Following values are valid:
 *                       - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Signed value.
 *             Range:
 *               [   -8192
 *                 :  8191
 *               ]
 *
 ******************************************************************************/
#define ADC_GetPPULowThreshold(ADCx,ePPUx)                                      \
    ( (int32_t)READ_REG( (ADCx)->PPUTHL[(ePPUx)]) )




/******************************************************************************
 * @brief      Set PPU[x] reference value
 *
 * @param[in]  ePPUx : PPU x defined by ADC_PostProcessUnitEnum
 *                     Following values are valid:
 *                       - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  i32Val: Signed value.
 *                     Valid range:
 *                       [   -4096
 *                         :  4095
 *                       ]
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_SetPPUReference(ADCx,ePPUx,i32Val)                                  \
    WRITE_REG( (ADCx)->PPUREF[ePPUx], i32Val )




/******************************************************************************
 * @brief      Get PPU[x] reference value
 *
 * @param[in]  ePPUx : PPU x defined by ADC_PostProcessUnitEnum
 *                     Following values are valid:
 *                       - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Signed value.
 *             Range:
 *               [   -4096
 *                 :  4095
 *               ]
 *
 ******************************************************************************/
#define ADC_GetPPUReference(ADCx,ePPUx)                                         \
    ( (int32_t)READ_REG( (ADCx)->PPUREF[ePPUx] ) )




/******************************************************************************
 * @brief      Get PPU[x] result value
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Signed value.
 *             Range:
 *               [   -8192
 *                 :  8191
 *               ]
 *
 ******************************************************************************/
#define ADC_GetPPUResult(ADCx,ePPUx)                                            \
    ( (int32_t)READ_REG( (ADCx)->PPURESULT[ePPUx] ) )




/******************************************************************************
 * @brief      Get PPU[x] raw result value
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Unsigned value.
 *             Range: [ 0 : 16383 ]
 *
 ******************************************************************************/
#define ADC_GetPPURawResult(ADCx,ePPUx)                                         \
    ( (uint32_t)( ADC_GetPPUResult(ADCx, ePPUx) + 8192 ) )




/******************************************************************************
 * @brief      Get PPU[x] delay from selected SOC trigger to begin sample
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 *
 * @return     Unsigned delay time count, which worked on CLK_ADC.
 *
 ******************************************************************************/
#define ADC_GetPPUTriggerDelay(ADCx,ePPUx)                                      \
    READ_REG( (ADCx)->PPUSOCDLY[ePPUx] )




/******************************************************************************
 * @brief      Enable PPU[x] interrupts
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Ints: Interrupts defined by ADC_PPU_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_INT_ALL
 *                        - \ref ADC_PPU_INT_TOO_LOW
 *                        - \ref ADC_PPU_INT_TOO_HIGH
 *                        - \ref ADC_PPU_INT_CROSS_ZERO
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnablePPUInt(ADCx,ePPUx,u32Ints)                                    \
    SET_BITS( (ADCx)->PPUIE[ePPUx], (u32Ints) )

#define ADC_DisablePPUInt(ADCx,ePPUx,u32Ints)                                   \
    CLEAR_BITS( (ADCx)->PPUIE[ePPUx], (u32Ints) )




/******************************************************************************
 * @brief      Get PPU[x] interrupts setting
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Ints: Interrupts defined by ADC_PPU_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_INT_ALL
 *                        - \ref ADC_PPU_INT_TOO_LOW
 *                        - \ref ADC_PPU_INT_TOO_HIGH
 *                        - \ref ADC_PPU_INT_CROSS_ZERO
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnablePPUInt(ADCx,ePPUx,u32Ints)                                  \
    ( (ADCx)->PPUIE[ePPUx] & (u32Ints) )




/******************************************************************************
 * @brief      Get PPU[x] events raw flag
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Ints: Interrupts defined by ADC_PPU_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_INT_ALL
 *                        - \ref ADC_PPU_INT_TOO_LOW
 *                        - \ref ADC_PPU_INT_TOO_HIGH
 *                        - \ref ADC_PPU_INT_CROSS_ZERO
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetPPUIntRawFlag(ADCx,ePPUx,u32Ints)                                \
    ( (ADCx)->PPURAWIF[ePPUx] & (u32Ints) )




/******************************************************************************
 * @brief      Get PPU[x] interrupts flag
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Ints: Interrupts defined by ADC_PPU_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_INT_ALL
 *                        - \ref ADC_PPU_INT_GLOBAL
 *                        - \ref ADC_PPU_INT_TOO_LOW
 *                        - \ref ADC_PPU_INT_TOO_HIGH
 *                        - \ref ADC_PPU_INT_CROSS_ZERO
 *
 * @return     0     - None of the queried flags occurred;
 *             not 0 - Corresponding flags for non-zero bit occurred.
 *
 ******************************************************************************/
#define ADC_GetPPUIntFlag(ADCx,ePPUx,u32Ints)                                   \
    ( (ADCx)->PPUIF[ePPUx] & (u32Ints) )




/******************************************************************************
 * @brief      Clear PPU[x] interrupts flag
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Ints: Interrupts defined by ADC_PPU_IntEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_INT_ALL
 *                        - \ref ADC_PPU_INT_GLOBAL
 *                        - \ref ADC_PPU_INT_TOO_LOW
 *                        - \ref ADC_PPU_INT_TOO_HIGH
 *                        - \ref ADC_PPU_INT_CROSS_ZERO
 *
 * @return     None
 *
 * @note       These fields are self-cleared.
 *
 ******************************************************************************/
#define ADC_ClearPPUInt(ADCx,ePPUx,u32Ints)                                     \
    WRITE_REG( (ADCx)->PPUIC[ePPUx], u32Ints )




/******************************************************************************
 * @brief      Enable PPU[x] trip-zone events
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Evts: Events defined by ADC_PPU_EventEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_EVENT_ALL
 *                        - \ref ADC_PPU_EVENT_TOO_LOW
 *                        - \ref ADC_PPU_EVENT_TOO_HIGH
 *                        - \ref ADC_PPU_EVENT_CROSS_ZERO
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_EnablePPUTripEvent(ADCx,ePPUx,u32Evts)                              \
    SET_BITS( (ADCx)->PPUTZE[ePPUx], u32Evts )

#define ADC_DisablePPUTripEvent(ADCx,ePPUx,u32Evts)                             \
    CLEAR_BITS( (ADCx)->PPUTZE[ePPUx], u32Evts )




/******************************************************************************
 * @brief      Get PPU[x] trip-zone events setting
 *
 * @param[in]  ePPUx: PPU x defined by ADC_PostProcessUnitEnum
 *                    Following values are valid:
 *                      - \ref ADC_PPU0 ~ ADC_PPU2
 * @param[in]  u32Evts: Events defined by ADC_PPU_EventEnum
 *                      ORed of the following values are valid:
 *                        - \ref ADC_PPU_EVENT_ALL
 *                        - \ref ADC_PPU_EVENT_TOO_LOW
 *                        - \ref ADC_PPU_EVENT_TOO_HIGH
 *                        - \ref ADC_PPU_EVENT_CROSS_ZERO
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC_IsEnablePPUTripEvent(ADCx,ePPUx,u32Evts)                            \
    ( (ADCx)->PPUTZE[ePPUx] & (u32Evts) )




/******************************************************************************
 * @brief      Enable write access to the protected ADCx registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_WALLOW(ADCx)                                                        \
    WRITE_REG( (ADCx)->ADCREGKEY, 0x1ACCE551U )




/******************************************************************************
 * @brief      Disable write access to the protected ADCx registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC_WDIS(ADCx)                                                          \
    WRITE_REG( (ADCx)->ADCREGKEY, 0x0U )





/** @defgroup ADC ENGR
  * @brief ADC Engineering Test Functions
  * @{
  */




/**
  * @}
  */






/**
 *  @brief  ADC Public Function Declaration
 */
void ADC_SetSampleAndConvertTime(ADC_REGS *ADCx, ADC_ChannelEnum eCHx, uint32_t u32SampleTimeNs, uint32_t u32ConvTimeNs);

ErrorStatus ADC_SelectPinSingleEnd(ADC_REGS *ADCx, ADC_ChannelEnum eCHx, uint8_t u8PinSel, ADC_Channel_SOCTriggerSourceEnum eTrigSrc);
ErrorStatus ADC_SelectPinDifferetial(ADC_REGS *ADCx, ADC_ChannelEnum eCHx, uint8_t u8PinSel_1, uint8_t u8PinSel_2, ADC_Channel_SOCTriggerSourceEnum eTrigSrc);

ErrorStatus ADC_EasyInit1(ADC_REGS *ADCx, ADC_ChannelEnum eCHx, uint8_t u8PinSel, ADC_Channel_SOCTriggerSourceEnum eTrigSrc);
ErrorStatus ADC_EasyInit2(ADC_REGS *ADCx, ADC_ChannelEnum eCHx, uint8_t u8PinSel_1, uint8_t u8PinSel_2, ADC_Channel_SOCTriggerSourceEnum eTrigSrc);

void ADC_Init(ADC_REGS *ADCx, ADC_ChannelEnum eCHx, ADC_SH_PositiveInputEnum ePosIn, ADC_SH_NegativeInputEnum eNegIn, ADC_Channel_SOCTriggerSourceEnum eTrigSrc);
void ADC_Enable(ADC_REGS *ADCx);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ADC_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
