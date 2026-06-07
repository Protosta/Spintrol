/******************************************************************************
 * @file     pin.h
 * @brief    PINMUX driver header file.
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


#ifndef PIN_H
#define PIN_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  Pin Control Register Bit-field Mask and Position Definition
 */
#define PIN_OCHSEL_Msk          (GPIO0_OCHSEL_Msk   )
#define PIN_OCHSEL_Pos          (GPIO0_OCHSEL_Pos   )
#define PIN_DEGLITCH_Msk        (GPIO0_DEGLITCH_Msk )
#define PIN_DEGLITCH_Pos        (GPIO0_DEGLITCH_Pos )
#define PIN_STRENGTH_Msk        (GPIO0_STRENGTH_Msk )
#define PIN_STRENGTH_Pos        (GPIO0_STRENGTH_Pos )
#define PIN_ICHEN_Msk           (GPIO0_ICHEN_Msk    )
#define PIN_ICHEN_Pos           (GPIO0_ICHEN_Pos    )
#define PIN_PD_Msk              (GPIO0_PD_Msk       )
#define PIN_PD_Pos              (GPIO0_PD_Pos       )
#define PIN_PU_Msk              (GPIO0_PU_Msk       )
#define PIN_PU_Pos              (GPIO0_PU_Pos       )




/**
 *  @brief  Pin channel definition
 */
typedef enum
{
    PIN_CH0                     = 0U,   /*!< Pin channel 0 definition       */
    PIN_CH1                     = 1U,   /*!< Pin channel 1 definition       */
    PIN_CH2                     = 2U,   /*!< Pin channel 2 definition       */
    PIN_CH3                     = 3U,   /*!< Pin channel 3 definition       */
} PIN_ChannelEnum;




/**
 *  @brief  Pin output driving strength definition
 *  @note   For 3.3V pin the following value is valid:
 *            - \ref PIN_OUT_STRENGTH_5MA
 *            - \ref PIN_OUT_STRENGTH_10MA
 *            - \ref PIN_OUT_STRENGTH_15MA
 *            - \ref PIN_OUT_STRENGTH_20MA
 *          For 5V pin the following value is valid:
 *            - \ref PIN_OUT_STRENGTH_1MA
 *            - \ref PIN_OUT_STRENGTH_20MA
 */
typedef enum
{
    PIN_OUT_STRENGTH_1MA        = 0U,   /*!< Output strength is 1  mA       */
    PIN_OUT_STRENGTH_5MA        = 0U,   /*!< Output strength is 5  mA       */
    PIN_OUT_STRENGTH_10MA       = 1U,   /*!< Output strength is 10 mA       */
    PIN_OUT_STRENGTH_15MA       = 2U,   /*!< Output strength is 15 mA       */
    PIN_OUT_STRENGTH_20MA       = 3U,   /*!< Output strength is 20 mA       */
} PIN_OutStrengthEnum;




/**
 *  @brief  Pin comparator monitor output channel definitions
 */
typedef enum
{
    PIN_COMP_MONITOR_CH0        = 0U,   /*!< Comparator monitor output 0    */
    PIN_COMP_MONITOR_CH1        = 1U,   /*!< Comparator monitor output 1    */
    PIN_COMP_MONITOR_CH2        = 2U,   /*!< Comparator monitor output 2    */
    PIN_COMP_MONITOR_CH3        = 3U,   /*!< Comparator monitor output 3    */
    PIN_COMP_MONITOR_CH4        = 4U,   /*!< Comparator monitor output 4    */
    PIN_COMP_MONITOR_CH5        = 5U,   /*!< Comparator monitor output 5    */
    PIN_COMP_MONITOR_CH6        = 6U,   /*!< Comparator monitor output 6    */
    PIN_COMP_MONITOR_CH7        = 7U,   /*!< Comparator monitor output 7    */
} PIN_ComparatorMonitorChannelEnum;




/**
 *  @brief  Pin comparator monitor source definitions
 */
typedef enum
{
    PIN_MONITOR_COMP_L          = 0U,   /*!< Monitor COMP_L                 */
    PIN_MONITOR_COMP_H          = 1U,   /*!< Monitor COMP_H                 */
    PIN_MONITOR_PHCOMP_U        = 2U,   /*!< Monitor PHCOMP_U               */
    PIN_MONITOR_PHCOMP_V        = 3U,   /*!< Monitor PHCOMP_V               */
    PIN_MONITOR_PHCOMP_W        = 4U,   /*!< Monitor PHCOMP_W               */
    PIN_MONITOR_PHCOMP_U_FILTER = 5U,   /*!< Monitor filtered PHCOMP_U      */
    PIN_MONITOR_PHCOMP_V_FILTER = 6U,   /*!< Monitor filtered PHCOMP_V      */
    PIN_MONITOR_PHCOMP_W_FILTER = 7U,   /*!< Monitor filtered PHCOMP_W      */
} PIN_ComparatorMonitorSourceEnum;




/**
 *  @brief  PIN_GPIO0 channel function define
 */
#define PIN_GPIO0_GPIO0           PIN_CH0
#define PIN_GPIO0_ANA_IN0         PIN_CH1
#define PIN_GPIO0_PWMSOCAO        PIN_CH2
#define PIN_GPIO0_PWMSOCCO        PIN_CH3




/**
 *  @brief  PIN_GPIO1 channel function define
 */
#define PIN_GPIO1_GPIO1           PIN_CH0
#define PIN_GPIO1_ANA_IN1         PIN_CH1
#define PIN_GPIO1_PWMSOCBO        PIN_CH2
#define PIN_GPIO1_ECAP_APWMO      PIN_CH3




/**
 *  @brief  PIN_GPIO2 channel function define
 */
#define PIN_GPIO2_GPIO2           PIN_CH0
#define PIN_GPIO2_ANA_IN2         PIN_CH1
#define PIN_GPIO2_DCLK            PIN_CH2
#define PIN_GPIO2_EPWRTZO         PIN_CH3




/**
 *  @brief  PIN_GPIO3 channel function define
 */
#define PIN_GPIO3_GPIO3           PIN_CH0
#define PIN_GPIO3_ANA_IN3         PIN_CH1
#define PIN_GPIO3_XIN             PIN_CH2
#define PIN_GPIO3_COMP_MON0       PIN_CH3




/**
 *  @brief  PIN_GPIO4 channel function define
 */
#define PIN_GPIO4_GPIO4           PIN_CH0
#define PIN_GPIO4_ANA_IN4         PIN_CH1
#define PIN_GPIO4_XOUT            PIN_CH2
#define PIN_GPIO4_COMP_MON1       PIN_CH3




/**
 *  @brief  PIN_GPIO5 channel function define
 */
#define PIN_GPIO5_GPIO5           PIN_CH0
#define PIN_GPIO5_EPWRTZO         PIN_CH1
#define PIN_GPIO5_PWMSOCO         PIN_CH2
#define PIN_GPIO5_ECAP_APWMO      PIN_CH3




/**
 *  @brief  PIN_GPIO6 channel function define
 */
#define PIN_GPIO6_GPIO6           PIN_CH0
#define PIN_GPIO6_SPI0_SCLK       PIN_CH1
#define PIN_GPIO6_UART1_TXD       PIN_CH2
#define PIN_GPIO6_COMP_MON2       PIN_CH3




/**
 *  @brief  PIN_GPIO7 channel function define
 */
#define PIN_GPIO7_GPIO7           PIN_CH0
#define PIN_GPIO7_SPI0_SFRM       PIN_CH1
#define PIN_GPIO7_UART1_RXD       PIN_CH2
#define PIN_GPIO7_COMP_MON3       PIN_CH3




/**
 *  @brief  PIN_GPIO8 channel function define
 */
#define PIN_GPIO8_GPIO8           PIN_CH0
#define PIN_GPIO8_SPI0_MOSI       PIN_CH1
#define PIN_GPIO8_CAN_TXD         PIN_CH2
#define PIN_GPIO8_COMP_MON4       PIN_CH3




/**
 *  @brief  PIN_GPIO9 channel function define
 */
#define PIN_GPIO9_GPIO9           PIN_CH0
#define PIN_GPIO9_SPI0_MISO       PIN_CH1
#define PIN_GPIO9_CAN_RXD         PIN_CH2
#define PIN_GPIO9_COMP_MON5       PIN_CH3




/**
 *  @brief  PIN_GPIO10 channel function define
 */
#define PIN_GPIO10_GPIO10         PIN_CH0
#define PIN_GPIO10_UART0_TXD      PIN_CH1
#define PIN_GPIO10_PWM0A          PIN_CH2
#define PIN_GPIO10_I2C_SCL        PIN_CH3




/**
 *  @brief  PIN_GPIO11 channel function define
 */
#define PIN_GPIO11_GPIO11         PIN_CH0
#define PIN_GPIO11_UART0_RXD      PIN_CH1
#define PIN_GPIO11_PWM0B          PIN_CH2
#define PIN_GPIO11_I2C_SDA        PIN_CH3




/**
 *  @brief  PIN_GPIO12 channel function define
 */
#define PIN_GPIO12_GPIO12         PIN_CH0
#define PIN_GPIO12_SPI1_SCLK      PIN_CH1
#define PIN_GPIO12_PWM1A          PIN_CH2
#define PIN_GPIO12_PWM3A          PIN_CH3




/**
 *  @brief  PIN_GPIO13 channel function define
 */
#define PIN_GPIO13_GPIO13         PIN_CH0
#define PIN_GPIO13_SPI1_SFRM      PIN_CH1
#define PIN_GPIO13_PWM1B          PIN_CH2
#define PIN_GPIO13_PWM3B          PIN_CH3




/**
 *  @brief  PIN_GPIO14 channel function define
 */
#define PIN_GPIO14_GPIO14         PIN_CH0
#define PIN_GPIO14_SPI1_MOSI      PIN_CH1
#define PIN_GPIO14_PWM2A          PIN_CH2
#define PIN_GPIO14_I2C_SCL        PIN_CH3




/**
 *  @brief  PIN_GPIO15 channel function define
 */
#define PIN_GPIO15_GPIO15         PIN_CH0
#define PIN_GPIO15_SPI1_MISO      PIN_CH1
#define PIN_GPIO15_PWM2B          PIN_CH2
#define PIN_GPIO15_I2C_SDA        PIN_CH3




/**
 *  @brief  PIN_GPIO16 channel function define
 */
#define PIN_GPIO16_GPIO16         PIN_CH0
#define PIN_GPIO16_UART1_TXD      PIN_CH1
#define PIN_GPIO16_CAN_TXD        PIN_CH2
#define PIN_GPIO16_SPI1_SFRM      PIN_CH3




/**
 *  @brief  PIN_GPIO17 channel function define
 */
#define PIN_GPIO17_GPIO17         PIN_CH0
#define PIN_GPIO17_UART1_RXD      PIN_CH1
#define PIN_GPIO17_CAN_RXD        PIN_CH2
#define PIN_GPIO17_SPI1_SCLK      PIN_CH3




/**
 *  @brief  PIN_GPIO18 channel function define
 */
#define PIN_GPIO18_GPIO18         PIN_CH0
#define PIN_GPIO18_PWMSOCO        PIN_CH1
#define PIN_GPIO18_PWMSYNCO       PIN_CH2
#define PIN_GPIO18_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO19 channel function define
 */
#define PIN_GPIO19_GPIO19         PIN_CH0
#define PIN_GPIO19_PWM2B          PIN_CH1
#define PIN_GPIO19_PWM0A          PIN_CH2
#define PIN_GPIO19_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO20 channel function define
 */
#define PIN_GPIO20_GPIO20         PIN_CH0
#define PIN_GPIO20_PWM2A          PIN_CH1
#define PIN_GPIO20_PWM1A          PIN_CH2
#define PIN_GPIO20_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO21 channel function define
 */
#define PIN_GPIO21_GPIO21         PIN_CH0
#define PIN_GPIO21_PWM1B          PIN_CH1
#define PIN_GPIO21_PWM2A          PIN_CH2
#define PIN_GPIO21_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO22 channel function define
 */
#define PIN_GPIO22_GPIO22         PIN_CH0
#define PIN_GPIO22_PWM1A          PIN_CH1
#define PIN_GPIO22_PWM0B          PIN_CH2
#define PIN_GPIO22_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO23 channel function define
 */
#define PIN_GPIO23_GPIO23         PIN_CH0
#define PIN_GPIO23_PWM0B          PIN_CH1
#define PIN_GPIO23_PWM1B          PIN_CH2
#define PIN_GPIO23_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO24 channel function define
 */
#define PIN_GPIO24_GPIO24         PIN_CH0
#define PIN_GPIO24_PWM0A          PIN_CH1
#define PIN_GPIO24_PWM2B          PIN_CH2
#define PIN_GPIO24_ECAP_APWMO     PIN_CH3




/**
 *  @brief  PIN_GPIO25 channel function define
 */
#define PIN_GPIO25_GPIO25         PIN_CH0
#define PIN_GPIO25_UART1_TXD      PIN_CH1
#define PIN_GPIO25_CAN_TXD        PIN_CH2
#define PIN_GPIO25_I2C_SCL        PIN_CH3




/**
 *  @brief  PIN_GPIO26 channel function define
 */
#define PIN_GPIO26_GPIO26         PIN_CH0
#define PIN_GPIO26_UART1_RXD      PIN_CH1
#define PIN_GPIO26_CAN_RXD        PIN_CH2
#define PIN_GPIO26_I2C_SDA        PIN_CH3




/**
 *  @brief  PIN_GPIO27 channel function define
 */
#define PIN_GPIO27_GPIO27         PIN_CH0




/**
 *  @brief  PIN_GPIO28 channel function define
 */
#define PIN_GPIO28_GPIO28         PIN_CH0
#define PIN_GPIO28_ANA_IN5        PIN_CH1
#define PIN_GPIO28_SPI1_SCLK      PIN_CH2
#define PIN_GPIO28_PWMSOCAO       PIN_CH3




/**
 *  @brief  PIN_GPIO29 channel function define
 */
#define PIN_GPIO29_GPIO29         PIN_CH0
#define PIN_GPIO29_ANA_IN6        PIN_CH1
#define PIN_GPIO29_SPI1_SFRM      PIN_CH2
#define PIN_GPIO29_PWMSOCBO       PIN_CH3




/**
 *  @brief  PIN_GPIO30 channel function define
 */
#define PIN_GPIO30_GPIO30         PIN_CH0
#define PIN_GPIO30_ANA_IN7        PIN_CH1
#define PIN_GPIO30_SPI1_MOSI      PIN_CH2
#define PIN_GPIO30_PWMSOCCO       PIN_CH3




/**
 *  @brief  PIN_GPIO31 channel function define
 */
#define PIN_GPIO31_GPIO31         PIN_CH0
#define PIN_GPIO31_ANA_IN8        PIN_CH1
#define PIN_GPIO31_SPI1_MISO      PIN_CH2
#define PIN_GPIO31_PWMSYNCO       PIN_CH3




/**
 *  @brief  PIN_GPIO32 channel function define
 */
#define PIN_GPIO32_GPIO32         PIN_CH0
#define PIN_GPIO32_UART1_TXD      PIN_CH1
#define PIN_GPIO32_I2C_SCL        PIN_CH2
#define PIN_GPIO32_COMP_MON6      PIN_CH3




/**
 *  @brief  PIN_GPIO33 channel function define
 */
#define PIN_GPIO33_GPIO33         PIN_CH0
#define PIN_GPIO33_UART1_RXD      PIN_CH1
#define PIN_GPIO33_I2C_SDA        PIN_CH2
#define PIN_GPIO33_COMP_MON7      PIN_CH3




/**
 *  @brief  PIN_GPIO34 channel function define
 */
#define PIN_GPIO34_GPIO34         PIN_CH0
#define PIN_GPIO34_CAN_TXD        PIN_CH1
#define PIN_GPIO34_I2C_SCL        PIN_CH2
#define PIN_GPIO34_EPWRTZ0O       PIN_CH3




/**
 *  @brief  PIN_GPIO35 channel function define
 */
#define PIN_GPIO35_GPIO35         PIN_CH0
#define PIN_GPIO35_CAN_RXD        PIN_CH1
#define PIN_GPIO35_I2C_SDA        PIN_CH2
#define PIN_GPIO35_EPWRTZ1O       PIN_CH3




/**
 *  @brief  PIN_GPIO36 channel function define
 */
#define PIN_GPIO36_GPIO36         PIN_CH0
#define PIN_GPIO36_ANA_PHU        PIN_CH1
#define PIN_GPIO36_SPI1_SCLK      PIN_CH2
#define PIN_GPIO36_UART1_TXD      PIN_CH3




/**
 *  @brief  PIN_GPIO37 channel function define
 */
#define PIN_GPIO37_GPIO37         PIN_CH0
#define PIN_GPIO37_ANA_PHV        PIN_CH1
#define PIN_GPIO37_SPI1_SFRM      PIN_CH2
#define PIN_GPIO37_UART1_RXD      PIN_CH3




/**
 *  @brief  PIN_GPIO38 channel function define
 */
#define PIN_GPIO38_GPIO38         PIN_CH0
#define PIN_GPIO38_ANA_PHW        PIN_CH1
#define PIN_GPIO38_SPI1_MOSI      PIN_CH2
#define PIN_GPIO38_CAN_TXD        PIN_CH3




/**
 *  @brief  PIN_GPIO39 channel function define
 */
#define PIN_GPIO39_GPIO39         PIN_CH0
#define PIN_GPIO39_ANA_PHC        PIN_CH1
#define PIN_GPIO39_SPI1_MISO      PIN_CH2
#define PIN_GPIO39_CAN_RXD        PIN_CH3




/**
 *  @brief  PIN_GPIO40 channel function define
 */
#define PIN_GPIO40_GPIO40         PIN_CH0
#define PIN_GPIO40_ANA_IN9        PIN_CH1
#define PIN_GPIO40_ANA_VBATDIV    PIN_CH1




/******************************************************************************
 * @brief      Pin Configuration Register define
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define __PINMUX_REG(ePinName)              (*((__IO uint32_t*)(PINMUX_BASE + ((ePinName) * 4))))




/******************************************************************************
 * @brief      Set/Get Pin channel
 *
 * @param[in]  ePinName:  Select the pin, should be PIN_NameEnum
 * @param[in]  eChannel:  GPIO pin channel, should be PIN_ChannelEnum
 *
 * @return     None
 * @return     Pin channel
 *
 ******************************************************************************/
#define PIN_SetChannel(ePinName,eChannel)   MODIFY_REG( __PINMUX_REG(ePinName), (PIN_OCHSEL_Msk | PIN_ICHEN_Msk), (((eChannel) << PIN_OCHSEL_Pos) | ((1U << (eChannel)) << PIN_ICHEN_Pos)) )
#define PIN_GetChannel(ePinName)            READ_FIELD( __PINMUX_REG(ePinName), PIN_OCHSEL_Msk, PIN_OCHSEL_Pos )




/******************************************************************************
 * @brief      Enable/Disable Pin input deglitch filter
 *
 * @param[in]  ePinName:  Select the pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_EnableDeglitch(ePinName)        SET_BITS( __PINMUX_REG(ePinName), PIN_DEGLITCH_Msk )
#define PIN_DisableDeglitch(ePinName)       CLEAR_BITS( __PINMUX_REG(ePinName), PIN_DEGLITCH_Msk )




/******************************************************************************
 * @brief      Set Pin output strength
 *
 * @param[in]  ePinName :  Select the pin, should be PIN_NameEnum
 * @param[in]  eStrength:  Pin output strength, should be PIN_OutStrengthEnum
 *                         For 3.3V pin the following value is valid:
 *                          - \ref PIN_OUT_STRENGTH_5MA
 *                          - \ref PIN_OUT_STRENGTH_10MA
 *                          - \ref PIN_OUT_STRENGTH_15MA
 *                          - \ref PIN_OUT_STRENGTH_20MA
 *                         For 5V pin the following value is valid:
 *                          - \ref PIN_OUT_STRENGTH_1MA
 *                          - \ref PIN_OUT_STRENGTH_20MA
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_SetOutStrength(ePinName,eStrength)                                  \
    WRITE_FIELD(                                                                \
                  __PINMUX_REG(ePinName),                                       \
                  PIN_STRENGTH_Msk,                                             \
                  PIN_STRENGTH_Pos,                                             \
                  (eStrength)                                                   \
               )




/******************************************************************************
 * @brief      Enable/Disable input channel
 *
 * @param[in]  ePinName : Select the chip pin, should be PIN_NameEnum
 * @param[in]  eChannel : Chip pin channel, should be PIN_ChannelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_EnableInputChannel(ePinName,eChannel)   SET_BITS( __PINMUX_REG(ePinName), ((0x1UL) << (PIN_ICHEN_Pos + (eChannel))) )
#define PIN_DisableInputChannel(ePinName,eChannel)  CLEAR_BITS( __PINMUX_REG(ePinName), ((0x1UL) << (PIN_ICHEN_Pos + (eChannel))) )




/******************************************************************************
 * @brief      Enable Pin pull-down
 *
 * @param[in]  ePinName:  Select the pin, should be PIN_NameEnum
 * @param[in]  eChannel:  Pin channel, should be PIN_ChannelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_EnablePullDown(ePinName,eChannel)                                   \
    MODIFY_REG(                                                                 \
                __PINMUX_REG(ePinName),                                         \
                ((0x01U << (eChannel)) << PIN_PU_Pos),                          \
                ((0x01U << (eChannel)) << PIN_PD_Pos)                           \
              )




/******************************************************************************
 * @brief      Disable Pin pull-down
 *
 * @param[in]  ePinName:  Select the pin, should be PIN_NameEnum
 * @param[in]  eChannel:  Pin channel, should be PIN_ChannelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_DisablePullDown(ePinName,eChannel)  CLEAR_BITS( __PINMUX_REG(ePinName), ((0x01U << (eChannel)) << PIN_PD_Pos) )




/******************************************************************************
 * @brief      Enable Pin pull-up
 *
 * @param[in]  ePinName:  Select the pin, should be PIN_NameEnum
 * @param[in]  eChannel:  Pin channel, should be PIN_ChannelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_EnablePullUp(ePinName,eChannel)                                     \
    MODIFY_REG(                                                                 \
                __PINMUX_REG(ePinName),                                         \
                ((0x01U << (eChannel)) << PIN_PD_Pos),                          \
                ((0x01U << (eChannel)) << PIN_PU_Pos)                           \
              )




/******************************************************************************
 * @brief      Disable Pin pull-up
 *
 * @param[in]  ePinName:  Select the pin, should be PIN_NameEnum
 * @param[in]  eChannel:  Pin channel, should be PIN_ChannelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_DisablePullUp(ePinName,eChannel)    CLEAR_BITS( __PINMUX_REG(ePinName), ((0x01U << (eChannel)) << PIN_PU_Pos) )




/******************************************************************************
 * @brief      Set Pin deglitch window size
 *
 * @param[in]  u32DIV:  Deglitch clock divider
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_SetDeglitchWindow(u32DIV)       (CLOCK->DGCLKCTL = (u32DIV))




/******************************************************************************
 * @brief      Set comparator monitor source
 *
 * @param[in]  eCH :  Comparator monitor channel as defined by PIN_ComparatorMonitorChannelEnum
 * @param[in]  eSrc:  Comparator monitor source as defined by PIN_ComparatorMonitorSourceEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PIN_SetComparatorMonitorSource(eCH, eSrc)                               \
    (PINMUX->COMPMONCTL = (PINMUX->COMPMONCTL & ~(0xFU << ((eCH) << 2U)))       \
                        | ((eSrc) << ((eCH) << 2U)))




/******************************************************************************
 * @brief      Enable write access to the protected PINMUX registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PINMUX_WALLOW()                     (PINMUX->PINMUXREGKEY = 0x1ACCE551U)




/******************************************************************************
 * @brief      Disable write access to the protected PINMUX registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PINMUX_WDIS()                       (PINMUX->PINMUXREGKEY = 0x0U)




/**
 *  @brief PINMUX Public Function Declaration
 */
void PIN_ResetAllPin(void);
void PIN_SetPinAsGPIO(PIN_NameEnum ePinName);
void PIN_SetPinAsECAPO(PIN_NameEnum ePinName);
void PIN_SetPinAsAnalog(PIN_NameEnum ePinName);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* PIN_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
