/******************************************************************************
 * @file     system.h
 * @brief    SYSTEM driver header file.
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


#ifndef SYSTEM_H
#define SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  SRAM information
 */
#define SRAM0_SIZE                (0x2000U   )      /*!< SRAM0 Size = 8KB                     */
#define SRAM0_BASE_ADDR           (0x1FFFA000U)     /*!< SRAM0 base address                   */

#define SRAM1_SIZE                (0x4000U   )      /*!< SRAM1 Size = 16KB                    */
#define SRAM1_BASE_ADDR           (0x1FFFC000U)     /*!< SRAM1 base address                   */




/**
 *  @brief  System monitor default sampling and conversion time
 *          User can adjust with different application
 */
#define MONITOR_DEFAULT_SAMPLE_OR_CONVERSION_TIME_NS        (500U)




/**
 *  @brief  NMI events definitions
 */
typedef enum
{
    NMI_EVENT_VDD12UV                   = (1U <<  0),     /*!< VDD12 under-voltage                  */
    NMI_EVENT_VDD12OV                   = (1U <<  1),     /*!< VDD12 over-voltage                   */
    NMI_EVENT_VDD33UV                   = (1U <<  2),     /*!< VDD33 under-voltage                  */
    NMI_EVENT_VDD33OV                   = (1U <<  3),     /*!< VDD33 over-voltage                   */
    NMI_EVENT_PLL_UNLOCK                = (1U <<  4),     /*!< PLL unlock                           */
    NMI_EVENT_CLK_DETECT_ERROR          = (1U <<  5),     /*!< Clock detect error                   */
    NMI_EVENT_ROM_MULTI_BIT_ERROR       = (1U <<  6),     /*!< ROM ECC multi-bit error              */
    NMI_EVENT_FLASH_MULTI_BIT_ERROR     = (1U <<  7),     /*!< FLASH ECC multi-bit error            */
    NMI_EVENT_RAM0_MULTI_BIT_ERROR      = (1U <<  8),     /*!< RAM0 ECC multi-bit error             */
    NMI_EVENT_RAM1_MULTI_BIT_ERROR      = (1U <<  9),     /*!< RAM1 ECC multi-bit error             */
    NMI_EVENT_WDT0_TIMEOUT              = (1U << 10),     /*!< Watchdog 0 timeout                   */
    NMI_EVENT_GPIO_EVENT                = (1U << 11),     /*!< GPIO event                           */
    NMI_EVENT_VADCREF_ERROR             = (1U << 12),     /*!< Main ADC reference voltage error     */
    NMI_EVENT_VDD12_ERROR               = (1U << 13),     /*!< VDD12 voltage error                  */
    NMI_EVENT_VDD33_ERROR               = (1U << 14),     /*!< VDD33 voltage error                  */
    NMI_EVENT_LV_TEMPERATURE_ERROR      = (1U << 15),     /*!< LV micro-controller temperature error*/
    NMI_EVENT_HV_LIN_TEMPERATURE_ERROR  = (1U << 16),     /*!< HV block LIN temperature error       */
    NMI_EVENT_HV_PMU_TEMPERATURE_ERROR  = (1U << 17),     /*!< HV block PMU temperature error       */
    NMI_EVENT_HV_VBG_ERROR              = (1U << 18),     /*!< HV block bandgap voltage error       */
    NMI_EVENT_HV_VDD5_ERROR             = (1U << 19),     /*!< HV block VDD5 voltage error          */
    NMI_EVENT_HV_VMON_ERROR             = (1U << 20),     /*!< HV block MON pin voltage error       */
    NMI_EVENT_HV_VCP_ERROR              = (1U << 21),     /*!< HV block VCP voltage error           */
    NMI_EVENT_HV_VBAT_ERROR             = (1U << 22),     /*!< HV block VBAT voltage error          */
    NMI_EVENT_AHB_MULTI_BIT_ERROR       = (1U << 23),     /*!< AHB ECC multi-bit error              */
    NMI_EVENT_DEBUG_MODE_ENTRY          = (1U << 24),     /*!< Debug mode (JTAG/SWD) entry          */
    NMI_EVENT_TEST_MODE_ENTRY           = (1U << 25),     /*!< Production test mode entry           */
    NMI_EVENT_GLOBAL                    = (1U << 26),     /*!< Used in get or clear interrupt flag  */
    NMI_EVENT_ALL                       = (0x7FFFFFFU),   /*!< All NMI events                       */
} SYSTEM_NMIEventEnum;




/**
 *  @brief  Reset events definitions
 */
typedef enum
{
    RESET_EVENT_VDD12UV                 = (1U <<  0),     /*!< Reset on VDD12 under-voltage event           */
    RESET_EVENT_VDD12OV                 = (1U <<  1),     /*!< Reset on VDD12 over-voltage event            */
    RESET_EVENT_VDD33UV                 = (1U <<  2),     /*!< Reset on VDD33 under-voltage event           */
    RESET_EVENT_VDD33OV                 = (1U <<  3),     /*!< Reset on VDD12 over-voltage event            */
    RESET_EVENT_PLL_UNLOCK              = (1U <<  4),     /*!< Reset on PLL unlock event                    */
    RESET_EVENT_CLK_DETECT_ERROR        = (1U <<  5),     /*!< Reset on clock detect error event            */
    RESET_EVENT_ROM_MULTI_BIT_ERROR     = (1U <<  6),     /*!< Reset on multi-bit error during ROM access   */
    RESET_EVENT_FLASH_MULTI_BIT_ERROR   = (1U <<  7),     /*!< Reset on multi-bit error during FLASH access */
    RESET_EVENT_RAM0_MULTI_BIT_ERROR    = (1U <<  8),     /*!< Reset on multi-bit error during RAM0 access  */
    RESET_EVENT_RAM1_MULTI_BIT_ERROR    = (1U <<  9),     /*!< Reset on multi-bit error during RAM1 access  */
    RESET_EVENT_WDT0_RESET              = (1U << 10),     /*!< Reset on watchdog 0 reset request            */
    RESET_EVENT_WDT1_RESET              = (1U << 11),     /*!< Reset on watchdog 1 reset request            */
    RESET_EVENT_SYS_RESET               = (1U << 12),     /*!< Reset on CPU system reset request            */
    RESET_EVENT_PIN_RESET               = (1U << 13),     /*!< Reset on XRSTn pin reset request             */
    RESET_EVENT_ALL                     = (0x3FFFU),      /*!< All reset  events                            */
} SYSTEM_ResetEventEnum;




/**
 *  @brief  System monitor item definitions
 */
typedef enum
{
    MONITOR_ADCREF                  = (1U << 16),       /*!< Monitor 13-bit ADC reference         */
    MONITOR_VDD12                   = (1U << 17),       /*!< Monitor VDD12 voltage                */
    MONITOR_VDD33                   = (1U << 18),       /*!< Monitor VDD13 voltage                */
    MONITOR_MCU_TEMPERATURE         = (1U << 19),       /*!< Monitor LV MCU temperature           */
    MONITOR_HV_LIN_TEMPERATURE      = (1U << 20),       /*!< Monitor HV block LIN PHY temperature */
    MONITOR_HV_PMU_TEMPERATURE      = (1U << 21),       /*!< Monitor HV block PMU temperature     */
    MONITOR_HV_VBG                  = (1U << 22),       /*!< Monitor HV block bandgap voltage     */
    MONITOR_HV_VDD5                 = (1U << 23),       /*!< Monitor HV block VDD5 voltage        */
    MONITOR_HV_VMON                 = (1U << 24),       /*!< Monitor HV block VMON pin voltage    */
    MONITOR_HV_VCP                  = (1U << 25),       /*!< Monitor HV block VCP voltage         */
    MONITOR_HV_VBAT                 = (1U << 26),       /*!< Monitor HV block VBAT voltage        */
    MONITOR_ALL                     = 0x7FF0000U,
} SYSTEM_MonitorItemEnum;




/**
 *  @brief  System option definitions
 */
typedef enum
{
    ROM_BASIC_SUPPORT               = 0,
    ROM_FULL_SUPPORT                = 1,

    FLASH_SIZE_32KB                 = 0,
    FLASH_SIZE_64KB                 = 1,
    FLASH_SIZE_96KB                 = 2,
    FLASH_SIZE_128KB                = 3,

    RAM_SIZE_4KB                    = 0,
    RAM_SIZE_8KB                    = 1,
    RAM_SIZE_12KB                   = 2,
    RAM_SIZE_16KB                   = 3,

    CLOCK_MAX_50MHz_NO_XO           = 0,
    CLOCK_MAX_100MHZ_NO_XO          = 1,
    CLOCK_MAX_50MHZ_WITH_XO         = 2,
    CLOCK_MAX_100MHZ_WITH_XO        = 3,

    ADC_RESOLUTION_10_BIT           = 0,
    ADC_RESOLUTION_11_BIT           = 1,
    ADC_RESOLUTION_12_BIT           = 2,
    ADC_RESOLUTION_13_BIT           = 3,
} SYSTEM_OptionEnum;



/**
 *  @brief  System memory interrupt definitions
 */
typedef enum
{
    MEM_INT_ROM_SINGLE_BIT_ERROR    = (1U << 0),    /* ROM ECC single-bit error             */
    MEM_INT_FLASH_SINGLE_BIT_ERROR  = (1U << 1),    /* FLASH ECC single-bit error           */
    MEM_INT_RAM0_SINGLE_BIT_ERROR   = (1U << 2),    /* RAM0 ECC single-bit error            */
    MEM_INT_RAM1_SINGLE_BIT_ERROR   = (1U << 3),    /* RAM1 ECC single-bit error            */
    MEM_INT_GLOBAL                  = (1U << 4),    /* Used to get or clear interrupt flag  */
    MEM_INT_ALL                     = (0x1FU),      /* All memory interrupt                 */
} SYSTEM_MemoryIntEnum;




/**
 *  @brief  System memory definitions
 */
typedef enum
{
    MEM_ROM                     = 0xB4U,        /* Storage ROM ECC Error Address    */
    MEM_FLASH                   = 0xB8U,        /* Storage FLASH ECC Error Address  */
    MEM_RAM0                    = 0xBCU,        /* Storage RAM0 ECC Error Address   */
    MEM_RAM1                    = 0xC0U,        /* Storage RAM1 ECC Error Address   */
} SYSTEM_MemoryEnum;




/******************************************************************************
 * @brief      Get Chip name ID
 *
 * @param[in]  None
 *
 * @return     64-bit chip name ID
 *
 ******************************************************************************/
#define SYSTEM_GetCID()                     (*((uint64_t*)(SYSTEM_BASE)))




/******************************************************************************
 * @brief      Get Chip Unique ID
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_GetUID()                     (*((uint64_t*)(SYSTEM_BASE + 0x8U)))




/******************************************************************************
 * @brief      Get Chip Random number
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_GetRandomNum()               (*((uint64_t*)(SYSTEM_BASE + 0x10U)))




/******************************************************************************
 * @brief      Get Chip version
 *
 * @param[in]  None
 *
 * @return     64-bit chip version
 *
 ******************************************************************************/
#define SYSTEM_GetVersion()                 (*((uint64_t*)(SYSTEM_BASE + 0x18U)))
#define SYSTEM_GetESDVersion()              ((SYSTEM->REV1 >> 4U) & 0x3U)




/******************************************************************************
 * @brief      Set GPIO NMI input source and polarity
 *
 * @param[in]  ePinName :  Select the pin for external input
 *                         Please refer to PIN_NameEnum
 * @param[in]  ePinLevel:  Select the pin level for active external input
 *                         Please refer to GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetGPIONMIInput(ePinName, ePinLevel)                              \
    MODIFY_REG( SYSTEM->GPIONMICTL ,                                              \
                ( GPIONMICTL_IOSEL_Msk | GPIONMICTL_POL_Msk ),                    \
                ( ((ePinName) << GPIONMICTL_IOSEL_Pos)                             \
                  |((ePinLevel) << GPIONMICTL_POL_Pos)                             \
                )                                                                 \
              )




/******************************************************************************
 * @brief      Get GPIO NMI input source
 *
 * @return     Get the GPIO number for external input
 *             Please refer to PIN_NameEnum
 *
 ******************************************************************************/
#define SYSTEM_GetGPIONMIInputSource()                                          \
    READ_FIELD( SYSTEM->GPIONMICTL, GPIONMICTL_IOSEL_Msk, GPIONMICTL_IOSEL_Pos )




/******************************************************************************
 * @brief      Get GPIO NMI input source polarity
 *
 * @return     Get the GPIO pin level for active external input
 *             Please refer to GPIO_LevelEnum
 *
 ******************************************************************************/
#define SYSTEM_GetGPIONMIInputSourcePolarity()                                  \
    READ_FIELD( SYSTEM->GPIONMICTL, GPIONMICTL_POL_Msk, GPIONMICTL_POL_Pos )




/******************************************************************************
 * @brief      Enable system monitor item
 *
 * @param[in]  eItem: System monitor item defined by SYSTEM_MonitorItemEnum
 *                    ORed of the following values are valid:
 *                      - \ref MONITOR_ALL
 *                      - \ref MONITOR_VADCREF
 *                      - \ref MONITOR_VDD12
 *                      - \ref MONITOR_VDD33
 *                      - \ref MONITOR_MCU_TEMPERATURE
 *                      - \ref MONITOR_HV_LIN_TEMPERATURE
 *                      - \ref MONITOR_HV_PMU_TEMPERATURE
 *                      - \ref MONITOR_HV_VBG
 *                      - \ref MONITOR_HV_VDD5
 *                      - \ref MONITOR_HV_VMON
 *                      - \ref MONITOR_HV_VCP
 *                      - \ref MONITOR_HV_VBAT
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_EnableMonitorItem(eItem)                                         \
    SET_BITS(SYSTEM->SYSMONCTL, (eItem))

#define SYSTEM_DisableMonitorItem(eItem)                                        \
    CLEAR_BITS(SYSTEM->SYSMONCTL, (eItem))




/******************************************************************************
 * @brief      Get system monitor item
 *
 * @param[in]  eItem: System monitor item defined by SYSTEM_MonitorItemEnum
 *                    ORed of the following values are valid:
 *                      - \ref MONITOR_ALL
 *                      - \ref MONITOR_VADCREF
 *                      - \ref MONITOR_VDD12
 *                      - \ref MONITOR_VDD33
 *                      - \ref MONITOR_MCU_TEMPERATURE
 *                      - \ref MONITOR_HV_LIN_TEMPERATURE
 *                      - \ref MONITOR_HV_PMU_TEMPERATURE
 *                      - \ref MONITOR_HV_VBG
 *                      - \ref MONITOR_HV_VDD5
 *                      - \ref MONITOR_HV_VMON
 *                      - \ref MONITOR_HV_VCP
 *                      - \ref MONITOR_HV_VBAT
 *
 * @return     0     - None of the queried items is set;
 *             not 0 - Corresponding items for non-zero bit is set.
 *
 ******************************************************************************/
#define SYSTEM_GetMonitorItem(eItem)                                            \
    (SYSTEM->SYSMONCTL & (eItem))




/******************************************************************************
 * @brief      Set 8-bits ADC of monitor convert interval count
 *
 * @param[in]  u16Cnt : Interval count value
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetMonitorIntervalCount(u16Cnt)                                  \
    WRITE_FIELD(SYSTEM->SYSMONCTL, SYSMONCTL_MONPRD_Msk, SYSMONCTL_MONPRD_Pos,  \
                (u16Cnt)                                                        \
               )




/******************************************************************************
 * @brief      Get 8-bits ADC of monitor convert interval count
 *
 * @return     Interval count value
 *
 ******************************************************************************/
#define SYSTEM_GetMonitorIntervalCount()                                        \
    READ_FIELD(SYSTEM->SYSMONCTL, SYSMONCTL_MONPRD_Msk, SYSMONCTL_MONPRD_Pos)




/******************************************************************************
 * @brief      Set threshold for VBAT monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVBATThreshold(u8Low,u8High)                                   \
    (SYSTEM->VBATTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVBATLowThreshold()                                            \
    (SYSTEM->VBATTH & 0xFFFFU)

#define SYSTEM_GetVBATHighThreshold()                                           \
    (SYSTEM->VBATTH >> 16U)

#define SYSTEM_GetVBATMonitorValue()                                            \
    (SYSTEM->VBATCODE)




/******************************************************************************
 * @brief      Set threshold for VCP monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVCPThreshold(u8Low,u8High)                                    \
    (SYSTEM->VCPTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVCPLowThreshold()                                             \
    (SYSTEM->VCPTH & 0xFFFFU)

#define SYSTEM_GetVCPHighThreshold()                                            \
    (SYSTEM->VCPTH >> 16U)

#define SYSTEM_GetVCPMonitorValue()                                             \
    (SYSTEM->VCPCODE)




/******************************************************************************
 * @brief      Set threshold for VMON monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVMONThreshold(u8Low,u8High)                                   \
    (SYSTEM->VMONTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVMONLowThreshold()                                            \
    (SYSTEM->VMONTH & 0xFFFFU)

#define SYSTEM_GetVMONHighThreshold()                                           \
    (SYSTEM->VMONTH >> 16U)

#define SYSTEM_GetVMONMonitorValue()                                            \
    (SYSTEM->VMONCODE)




/******************************************************************************
 * @brief      Set threshold for VDD5 monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVDD5Threshold(u8Low,u8High)                                   \
    (SYSTEM->VDD5TH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVDD5LowThreshold()                                            \
    (SYSTEM->VDD5TH & 0xFFFFU)

#define SYSTEM_GetVDD5HighThreshold()                                           \
    (SYSTEM->VDD5TH >> 16U)

#define SYSTEM_GetVDD5MonitorValue()                                            \
    (SYSTEM->VDD5CODE)




/******************************************************************************
 * @brief      Set threshold for VBG monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVBGThreshold(u8Low,u8High)                                    \
    (SYSTEM->VBGTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVBGLowThreshold()                                             \
    (SYSTEM->VBGTH & 0xFFFFU)

#define SYSTEM_GetVBGHighThreshold()                                            \
    (SYSTEM->VBGTH >> 16U)

#define SYSTEM_GetVBGMonitorValue()                                             \
    (SYSTEM->VBGCODE)




/******************************************************************************
 * @brief      Set threshold for PMU temperature monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetTPMUThreshold(u8Low,u8High)                                   \
    (SYSTEM->TPMUTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetTPMULowThreshold()                                            \
    (SYSTEM->TPMUTH & 0xFFFFU)

#define SYSTEM_GetTPMUHighThreshold()                                           \
    (SYSTEM->TPMUTH >> 16U)

#define SYSTEM_GetTPMUMonitorValue()                                            \
    (SYSTEM->TPMUCODE)




/******************************************************************************
 * @brief      Set threshold for LIN temperature monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetTLINThreshold(u8Low,u8High)                                   \
    (SYSTEM->TLINTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetTLINLowThreshold()                                            \
    (SYSTEM->TLINTH & 0xFFFFU)

#define SYSTEM_GetTLINHighThreshold()                                           \
    (SYSTEM->TLINTH >> 16U)

#define SYSTEM_GetTLINMonitorValue()                                            \
    (SYSTEM->TLINCODE)




/******************************************************************************
 * @brief      Set threshold for MCU temperature monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetTMCUThreshold(u8Low,u8High)                                   \
    (SYSTEM->TMCUTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetTMCULowThreshold()                                            \
    (SYSTEM->TMCUTH & 0xFFFFU)

#define SYSTEM_GetTMCUHighThreshold()                                           \
    (SYSTEM->TMCUTH >> 16U)

#define SYSTEM_GetTMCUMonitorValue()                                            \
    (SYSTEM->TMCUCODE)




/******************************************************************************
 * @brief      Set threshold for VDD33 monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVDD33Threshold(u8Low,u8High)                                  \
    (SYSTEM->VDD33TH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVDD33LowThreshold()                                           \
    (SYSTEM->VDD33TH & 0xFFFFU)

#define SYSTEM_GetVDD33HighThreshold()                                          \
    (SYSTEM->VDD33TH >> 16U)

#define SYSTEM_GetVDD33MonitorValue()                                           \
    (SYSTEM->VDD33CODE)




/******************************************************************************
 * @brief      Set threshold for VDD12 monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetVDD12Threshold(u8Low,u8High)                                  \
    (SYSTEM->VDD12TH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetVDD12LowThreshold()                                           \
    (SYSTEM->VDD12TH & 0xFFFFU)

#define SYSTEM_GetVDD12HighThreshold()                                          \
    (SYSTEM->VDD12TH >> 16U)

#define SYSTEM_GetVDD12MonitorValue()                                           \
    (SYSTEM->VDD12CODE)




/******************************************************************************
 * @brief      Set threshold for 13-bit ADC reference voltage monitor
 *
 * @param[in]  u8Low : Low threshold
 * @param[in]  u8High: High threshold
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetADCREFThreshold(u8Low,u8High)                                 \
    (SYSTEM->VADCREFTH = (u8Low) | ((u8High) << 16U))

#define SYSTEM_GetADCREFLowThreshold()                                          \
    (SYSTEM->VADCREFTH & 0xFFFFU)

#define SYSTEM_GetADCREFHighThreshold()                                         \
    (SYSTEM->VADCREFTH >> 16U)

#define SYSTEM_GetADCREFMonitorValue()                                          \
    (SYSTEM->VADCREFCODE)




/******************************************************************************
 * @brief      Enable non-maskalbe interrupt
 *
 * @param[in]  eNMIEvt:  NMI event defined by SYSTEM_NMIEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref NMI_EVENT_ALL
 *                         - \ref NMI_EVENT_VDD12UV
 *                         - \ref NMI_EVENT_VDD12OV
 *                         - \ref NMI_EVENT_VDD33UV
 *                         - \ref NMI_EVENT_VDD33OV
 *                         - \ref NMI_EVENT_PLL_UNLOCK
 *                         - \ref NMI_EVENT_CLK_DETECT_ERROR
 *                         - \ref NMI_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_WDT0_TIMEOUT
 *                         - \ref NMI_EVENT_GPIO_EVENT
 *                         - \ref NMI_EVENT_VADCREF_ERROR
 *                         - \ref NMI_EVENT_VDD12_ERROR
 *                         - \ref NMI_EVENT_VDD33_ERROR
 *                         - \ref NMI_EVENT_LV_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_LIN_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_PMU_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_VBG_ERROR
 *                         - \ref NMI_EVENT_HV_VDD5_ERROR
 *                         - \ref NMI_EVENT_HV_VMON_ERROR
 *                         - \ref NMI_EVENT_HV_VCP_ERROR
 *                         - \ref NMI_EVENT_HV_VBAT_ERROR
 *                         - \ref NMI_EVENT_AHB_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_TEST_MODE_ENTRY
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_EnableNonMaskableInt(eNMIEvt)                                    \
    SET_BITS(SYSTEM->NMIE, (eNMIEvt))

#define SYSTEM_DisableNonMaskableInt(eNMIEvt)                                   \
    CLEAR_BITS(SYSTEM->NMIE, (eNMIEvt))




/******************************************************************************
 * @brief      Get non-maskalbe interrupt enabled status
 *
 * @param[in]  eNMIEvt:  NMI event defined by SYSTEM_NMIEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref NMI_EVENT_ALL
 *                         - \ref NMI_EVENT_VDD12UV
 *                         - \ref NMI_EVENT_VDD12OV
 *                         - \ref NMI_EVENT_VDD33UV
 *                         - \ref NMI_EVENT_VDD33OV
 *                         - \ref NMI_EVENT_PLL_UNLOCK
 *                         - \ref NMI_EVENT_CLK_DETECT_ERROR
 *                         - \ref NMI_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_WDT0_TIMEOUT
 *                         - \ref NMI_EVENT_GPIO_EVENT
 *                         - \ref NMI_EVENT_VADCREF_ERROR
 *                         - \ref NMI_EVENT_VDD12_ERROR
 *                         - \ref NMI_EVENT_VDD33_ERROR
 *                         - \ref NMI_EVENT_LV_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_LIN_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_PMU_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_VBG_ERROR
 *                         - \ref NMI_EVENT_HV_VDD5_ERROR
 *                         - \ref NMI_EVENT_HV_VMON_ERROR
 *                         - \ref NMI_EVENT_HV_VCP_ERROR
 *                         - \ref NMI_EVENT_HV_VBAT_ERROR
 *                         - \ref NMI_EVENT_AHB_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_TEST_MODE_ENTRY
 *
 * @return     0     - None of the queried interrupts is enabled
 *             not 0 - Corresponding interrupts for non-zero bit is enabled
 *
 ******************************************************************************/
#define SYSTEM_IsEnableNonMaskableInt(eNMIEvt)                                  \
    (SYSTEM->NMIE & (eNMIEvt))




/******************************************************************************
 * @brief      Get non-maskable event raw flag
 *
 * @param[in]  eNMIEvt:  NMI event defined by SYSTEM_NMIEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref NMI_EVENT_ALL
 *                         - \ref NMI_EVENT_VDD12UV
 *                         - \ref NMI_EVENT_VDD12OV
 *                         - \ref NMI_EVENT_VDD33UV
 *                         - \ref NMI_EVENT_VDD33OV
 *                         - \ref NMI_EVENT_PLL_UNLOCK
 *                         - \ref NMI_EVENT_CLK_DETECT_ERROR
 *                         - \ref NMI_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_WDT0_TIMEOUT
 *                         - \ref NMI_EVENT_GPIO_EVENT
 *                         - \ref NMI_EVENT_VADCREF_ERROR
 *                         - \ref NMI_EVENT_VDD12_ERROR
 *                         - \ref NMI_EVENT_VDD33_ERROR
 *                         - \ref NMI_EVENT_LV_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_LIN_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_PMU_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_VBG_ERROR
 *                         - \ref NMI_EVENT_HV_VDD5_ERROR
 *                         - \ref NMI_EVENT_HV_VMON_ERROR
 *                         - \ref NMI_EVENT_HV_VCP_ERROR
 *                         - \ref NMI_EVENT_HV_VBAT_ERROR
 *                         - \ref NMI_EVENT_AHB_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_TEST_MODE_ENTRY
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define SYSTEM_GetNonMaskableIntRawFlag(eNMIEvt)  (SYSTEM->NMRAWIF & (eNMIEvt))




/******************************************************************************
 * @brief      Get non-maskable interrupt flag
 *
 * @param[in]  eNMIEvt:  NMI event defined by SYSTEM_NMIEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref NMI_EVENT_ALL
 *                         - \ref NMI_EVENT_GLOBAL
 *                         - \ref NMI_EVENT_VDD12UV
 *                         - \ref NMI_EVENT_VDD12OV
 *                         - \ref NMI_EVENT_VDD33UV
 *                         - \ref NMI_EVENT_VDD33OV
 *                         - \ref NMI_EVENT_PLL_UNLOCK
 *                         - \ref NMI_EVENT_CLK_DETECT_ERROR
 *                         - \ref NMI_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_WDT0_TIMEOUT
 *                         - \ref NMI_EVENT_GPIO_EVENT
 *                         - \ref NMI_EVENT_VADCREF_ERROR
 *                         - \ref NMI_EVENT_VDD12_ERROR
 *                         - \ref NMI_EVENT_VDD33_ERROR
 *                         - \ref NMI_EVENT_LV_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_LIN_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_PMU_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_VBG_ERROR
 *                         - \ref NMI_EVENT_HV_VDD5_ERROR
 *                         - \ref NMI_EVENT_HV_VMON_ERROR
 *                         - \ref NMI_EVENT_HV_VCP_ERROR
 *                         - \ref NMI_EVENT_HV_VBAT_ERROR
 *                         - \ref NMI_EVENT_AHB_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_TEST_MODE_ENTRY
 *
 * @return     0     - None of the queried interrupts occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define SYSTEM_GetNonMaskableIntFlag(eNMIEvt)     (SYSTEM->NMIF & (eNMIEvt))




/******************************************************************************
 * @brief      Clear non-maskable interrupt flag
 *
 * @param[in]  eNMIEvt:  NMI event defined by SYSTEM_NMIEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref NMI_EVENT_ALL
 *                         - \ref NMI_EVENT_GLOBAL
 *                         - \ref NMI_EVENT_VDD12UV
 *                         - \ref NMI_EVENT_VDD12OV
 *                         - \ref NMI_EVENT_VDD33UV
 *                         - \ref NMI_EVENT_VDD33OV
 *                         - \ref NMI_EVENT_PLL_UNLOCK
 *                         - \ref NMI_EVENT_CLK_DETECT_ERROR
 *                         - \ref NMI_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_WDT0_TIMEOUT
 *                         - \ref NMI_EVENT_GPIO_EVENT
 *                         - \ref NMI_EVENT_VADCREF_ERROR
 *                         - \ref NMI_EVENT_VDD12_ERROR
 *                         - \ref NMI_EVENT_VDD33_ERROR
 *                         - \ref NMI_EVENT_LV_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_LIN_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_PMU_TEMPERATURE_ERROR
 *                         - \ref NMI_EVENT_HV_VBG_ERROR
 *                         - \ref NMI_EVENT_HV_VDD5_ERROR
 *                         - \ref NMI_EVENT_HV_VMON_ERROR
 *                         - \ref NMI_EVENT_HV_VCP_ERROR
 *                         - \ref NMI_EVENT_HV_VBAT_ERROR
 *                         - \ref NMI_EVENT_AHB_MULTI_BIT_ERROR
 *                         - \ref NMI_EVENT_TEST_MODE_ENTRY
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_ClearNonMaskableInt(eNMIEvt)       (SYSTEM->NMIC = (eNMIEvt))




/******************************************************************************
 * @brief      Enable/disable memory interrupt
 *
 * @param[in]  eMemEvt:  Memory interrupt event defined by SYSTEM_MemoryIntEnum
 *                       ORed of the following values are valid:
 *                         - \ref MEM_INT_ALL
 *                         - \ref MEM_INT_ROM_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_FLASH_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM0_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM1_SINGLE_BIT_ERROR
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_EnableMemoryInt(eMemEvt)                                         \
    SET_BITS(SYSTEM->MEMIE, (eMemEvt))

#define SYSTEM_DisableMemoryInt(eMemEvt)                                        \
    CLEAR_BITS(SYSTEM->MEMIE, (eMemEvt))




/******************************************************************************
 * @brief      Get memory interrupt enabled status
 *
 * @param[in]  eMemEvt:  Memory interrupt event defined by SYSTEM_MemoryIntEnum
 *                       ORed of the following values are valid:
 *                         - \ref MEM_INT_ALL
 *                         - \ref MEM_INT_ROM_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_FLASH_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM0_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM1_SINGLE_BIT_ERROR
 *
 * @return     0     - None of the queried interrupts is enabled
 *             not 0 - Corresponding interrupts for non-zero bit is enabled
 *
 ******************************************************************************/
#define SYSTEM_IsEnableMemoryInt(eMemEvt)                                       \
    (SYSTEM->MEMIE & (eMemEvt))




/******************************************************************************
 * @brief      Get memory event raw flag
 *
 * @param[in]  eMemEvt:  Memory interrupt event defined by SYSTEM_MemoryIntEnum
 *                       ORed of the following values are valid:
 *                         - \ref MEM_INT_ALL
 *                         - \ref MEM_INT_ROM_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_FLASH_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM0_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM1_SINGLE_BIT_ERROR
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define SYSTEM_GetMemoryIntRawFlag(eMemEvt)     (SYSTEM->MEMRAWIF & (eMemEvt))




/******************************************************************************
 * @brief      Get memory interrupt flag
 *
 * @param[in]  eMemEvt:  Memory interrupt event defined by SYSTEM_MemoryIntEnum
 *                       ORed of the following values are valid:
 *                         - \ref MEM_INT_ALL
 *                         - \ref MEM_INT_GLOBAL
 *                         - \ref MEM_INT_ROM_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_FLASH_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM0_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM1_SINGLE_BIT_ERROR
 *
 * @return     0     - None of the queried interrupts occurred;
 *             not 0 - Corresponding interrupts for non-zero bit occurred.
 *
 ******************************************************************************/
#define SYSTEM_GetMemoryIntFlag(eMemEvt)        (SYSTEM->MEMIF & (eMemEvt))




/******************************************************************************
 * @brief      Clear memory interrupt flag
 *
 * @param[in]  eMemEvt:  Memory interrupt event defined by SYSTEM_MemoryIntEnum
 *                       ORed of the following values are valid:
 *                         - \ref MEM_INT_ALL
 *                         - \ref MEM_INT_GLOBAL
 *                         - \ref MEM_INT_ROM_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_FLASH_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM0_SINGLE_BIT_ERROR
 *                         - \ref MEM_INT_RAM1_SINGLE_BIT_ERROR
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_ClearMemoryInt(eMemEvt)          (SYSTEM->MEMIC = (eMemEvt))




/******************************************************************************
 * @brief      Enable reset event
 *
 * @param[in]  eRSTEvt:  Reset event defined by SYSTEM_ResetEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref RESET_EVENT_ALL
 *                         - \ref RESET_EVENT_VDD12UV
 *                         - \ref RESET_EVENT_VDD12OV
 *                         - \ref RESET_EVENT_VDD33UV
 *                         - \ref RESET_EVENT_VDD33OV
 *                         - \ref RESET_EVENT_PLL_UNLOCK
 *                         - \ref RESET_EVENT_CLK_DETECT_ERROR
 *                         - \ref RESET_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_WDT0_RESET
 *                         - \ref RESET_EVENT_WDT1_RESET
 *                         - \ref RESET_EVENT_SYS_RESET
 *                         - \ref RESET_EVENT_PIN_RESET
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_EnableResetEvent(eRSTEvt)                                        \
    SET_BITS(SYSTEM->RSTEVTEN, (eRSTEvt))

#define SYSTEM_DisableResetEvent(eRSTEvt)                                       \
    CLEAR_BITS(SYSTEM->RSTEVTEN, (eRSTEvt))




/******************************************************************************
 * @brief      Get reset event
 *
 * @param[in]  eRSTEvt:  Reset event defined by SYSTEM_ResetEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref RESET_EVENT_ALL
 *                         - \ref RESET_EVENT_VDD12UV
 *                         - \ref RESET_EVENT_VDD12OV
 *                         - \ref RESET_EVENT_VDD33UV
 *                         - \ref RESET_EVENT_VDD33OV
 *                         - \ref RESET_EVENT_PLL_UNLOCK
 *                         - \ref RESET_EVENT_CLK_DETECT_ERROR
 *                         - \ref RESET_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_WDT0_RESET
 *                         - \ref RESET_EVENT_WDT1_RESET
 *                         - \ref RESET_EVENT_SYS_RESET
 *                         - \ref RESET_EVENT_PIN_RESET
 *
 * @return     0     - None of the queried events is enabled;
 *             not 0 - Corresponding events for non-zero bit is enabled.
 *
 ******************************************************************************/
#define SYSTEM_IsEnableResetEvent(eRSTEvt)                                      \
    (SYSTEM->RSTEVTEN & (eRSTEvt))




/******************************************************************************
 * @brief      Get reset event flag
 *
 * @param[in]  eRSTEvt:  Reset event defined by SYSTEM_ResetEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref RESET_EVENT_ALL
 *                         - \ref RESET_EVENT_VDD12UV
 *                         - \ref RESET_EVENT_VDD12OV
 *                         - \ref RESET_EVENT_VDD33UV
 *                         - \ref RESET_EVENT_VDD33OV
 *                         - \ref RESET_EVENT_PLL_UNLOCK
 *                         - \ref RESET_EVENT_CLK_DETECT_ERROR
 *                         - \ref RESET_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_WDT0_RESET
 *                         - \ref RESET_EVENT_WDT1_RESET
 *                         - \ref RESET_EVENT_SYS_RESET
 *                         - \ref RESET_EVENT_PIN_RESET
 *
 * @return     0     - None of the queried events occurred;
 *             not 0 - Corresponding events for non-zero bit occurred.
 *
 ******************************************************************************/
#define SYSTEM_GetResetEventFlag(eRSTEvt)   (SYSTEM->RSTEVTFLG & (eRSTEvt))




/******************************************************************************
 * @brief      Clear reset event flag
 *
 * @param[in]  eRSTEvt:  Reset event defined by SYSTEM_ResetEventEnum
 *                       ORed of the following values are valid:
 *                         - \ref RESET_EVENT_ALL
 *                         - \ref RESET_EVENT_VDD12UV
 *                         - \ref RESET_EVENT_VDD12OV
 *                         - \ref RESET_EVENT_VDD33UV
 *                         - \ref RESET_EVENT_VDD33OV
 *                         - \ref RESET_EVENT_PLL_UNLOCK
 *                         - \ref RESET_EVENT_CLK_DETECT_ERROR
 *                         - \ref RESET_EVENT_ROM_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_FLASH_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM0_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_RAM1_MULTI_BIT_ERROR
 *                         - \ref RESET_EVENT_WDT0_RESET
 *                         - \ref RESET_EVENT_WDT1_RESET
 *                         - \ref RESET_EVENT_SYS_RESET
 *                         - \ref RESET_EVENT_PIN_RESET
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_ClearResetEventFlag(eRSTEvt)       (SYSTEM->RSTEVTCLR = (eRSTEvt))




/******************************************************************************
 * @brief      Get AHB multi-bit ECC error event flag
 *
 * @param[in]  eECCEvt:  Multi-bit ECC error event
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for none-0 bit occurred
 *
 ******************************************************************************/
#define SYSTEM_GetAHBMultiBitErrorEventFlag(ePort)      (SYSTEM->AHBMBEFLG & (ePort))




/******************************************************************************
 * @brief      Clear AHB multi-bit ECC error event flag
 *
 * @param[in]  eECCEvt:  Multi-bit ECC error event
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for none-0 bit occurred
 *
 ******************************************************************************/
#define SYSTEM_ClearAHBMultiBitErrorEventFlag(ePort)    (SYSTEM->AHBMBECLR = (ePort))




/******************************************************************************
 * @brief      Get AHB sing-bit ECC error event flag
 *
 * @param[in]  eECCEvt:  Single-bit ECC error event
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for none-0 bit occurred
 *
 ******************************************************************************/
#define SYSTEM_GetAHBSingleBitErrorEventFlag(ePort)     (SYSTEM->AHBSBEFLG & (ePort))




/******************************************************************************
 * @brief      Clear AHB single-bit ECC error event flag
 *
 * @param[in]  eECCEvt:  Single-bit ECC error event
 *
 * @return     0     - None of the queried events occurred
 *             not 0 - Corresponding events for none-0 bit occurred
 *
 ******************************************************************************/
#define SYSTEM_ClearAHBSingleBitErrorEventFlag(ePort)   (SYSTEM->AHBSBECLR = (ePort))




/******************************************************************************
 * @brief      Get ROM support option
 *
 * @param[in]  None
 *
 * @return     ROM support option
 *             Please refer to SYSTEM_OptionEnum
 *
 ******************************************************************************/
#define SYSTEM_GetROMOption()               ((SYSTEM->SYSINFO & SYSINFO_ROMSIZE_Msk) >> SYSINFO_ROMSIZE_Pos)




/******************************************************************************
 * @brief      Get RAM size option
 *
 * @param[in]  None
 *
 * @return     RAM size option
 *             Please refer to SYSTEM_OptionEnum
 *
 ******************************************************************************/
#define SYSTEM_GetRAMOption()               ((SYSTEM->SYSINFO & SYSINFO_RAMSIZE_Msk) >> SYSINFO_RAMSIZE_Pos)




/******************************************************************************
 * @brief      Get clock option
 *
 * @param[in]  None
 *
 * @return     Clock option
 *             Please refer to SYSTEM_OptionEnum
 *
 ******************************************************************************/
#define SYSTEM_GetClockOption()             ((SYSTEM->SYSINFO & SYSINFO_CLKOPT_Msk) >> SYSINFO_CLKOPT_Pos)




/******************************************************************************
 * @brief      Get ADC resolution option
 *
 * @param[in]  None
 *
 * @return     ADC resolution option
 *             Please refer to SYSTEM_OptionEnum
 *
 ******************************************************************************/
#define SYSTEM_GetADCOption()               ((SYSTEM->SYSINFO & SYSINFO_ADCBIT_Msk) >> SYSINFO_ADCBIT_Pos)




/******************************************************************************
 * @brief      Get all system option
 *
 * @param[in]  None
 *
 * @return     Full 32-bit system option
 *
 ******************************************************************************/
#define SYSTEM_GetAllOption()               (SYSTEM->SYSINFO)




/******************************************************************************
 * @brief      Get address where memory access error is detected
 *
 * @param[in]  eMem:  Memory types
 *                    Please refer to SYSTEM_MemoryEnum
 *
 * @return     The address where memory access error is detected
 *
 ******************************************************************************/
#define SYSTEM_GetMemErrorAddress(eMem)     (*((__IO uint32_t*)(SYSTEM_BASE + (eMem))))




/******************************************************************************
 * @brief      Get boot count
 *
 * @param[in]  None
 *
 * @return     Boot count
 *             i.e. How many times the boot code is executed after power-up
 *
 ******************************************************************************/
#define SYSTEM_GetBootCount()               (SYSTEM->BOOTINFO & 0xFFFFU)




/******************************************************************************
 * @brief      Get module reset flag
 *
 * @param[in]  eModule: The peripheral module as defined by CLOCK_ModuleEnum
 *
 * @return     0:     All modules have not been reset
 *             not 0: Module with coresponding bit to be 1 has been reset
 *
 ******************************************************************************/
#define SYSTEM_GetModuleResetFlag(eModule)  (SYSTEM->PERIRSTFLG & (eModule))




/******************************************************************************
 * @brief      Clear module reset flag
 *
 * @param[in]  eModule: The peripheral module as defined by CLOCK_ModuleEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_ClearModuleResetFlag(eModule)  (SYSTEM->PERIRSTCLR = (eModule))




/******************************************************************************
 * @brief      Set NVREG0 register value
 *
 * @param[in]  u32Val: Value to be written to the NVREG0 register
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetNVREG0(u32Val)            (SYSTEM->NVREG0 = (u32Val))




/******************************************************************************
 * @brief      Get NVREG0 register value
 *
 * @param[in]  None
 *
 * @return     Current value of NVREG0 register
 *
 ******************************************************************************/
#define SYSTEM_GetNVREG0()                  (SYSTEM->NVREG0)




/******************************************************************************
 * @brief      Set NVREG1 register value
 *
 * @param[in]  u32Val: Value to be written to the NVREG1 register
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetNVREG1(u32Val)            (SYSTEM->NVREG1 = (u32Val))




/******************************************************************************
 * @brief      Get NVREG1 register value
 *
 * @param[in]  None
 *
 * @return     Current value of NVREG1 register
 *
 ******************************************************************************/
#define SYSTEM_GetNVREG1()                  (SYSTEM->NVREG1)




/******************************************************************************
 * @brief      Set NVREG2 register value
 *
 * @param[in]  u32Val: Value to be written to the NVREG2 register
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_SetNVREG2(u32Val)            (SYSTEM->NVREG2 = (u32Val))




/******************************************************************************
 * @brief      Get NVREG2 register value
 *
 * @param[in]  None
 *
 * @return     Current value of NVREG2 register
 *
 ******************************************************************************/
#define SYSTEM_GetNVREG2()                  (SYSTEM->NVREG2)




/******************************************************************************
 * @brief      Enable write access to the protected SYSTEM registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_WALLOW()                     (SYSTEM->SYSREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected SYSTEM registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define SYSTEM_WDIS()                       (SYSTEM->SYSREGKEY = 0x0)




/**
 *  @brief System Public Function Declaration
 */
ErrorStatus SYSTEM_SetMonitorInterval(uint32_t u32IntervalUs);
ErrorStatus SYSTEM_SetMonitorSampleAndConvertTime(uint32_t u32TimeNs);
ErrorStatus SYSTEM_SetMonitorThreshold(SYSTEM_MonitorItemEnum eItem, uint32_t u32MinVal, uint32_t u32MaxVal);
#if (defined(SPC1169))
ErrorStatus SYSTEM_SetStopWakeUpByGPIO(PIN_NameEnum ePinName, LEVEL ePinLevel);
ErrorStatus SYSTEM_SetSleepWakeUpByGPIO(PIN_NameEnum ePinName, LEVEL ePinLevel);
#endif


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SYSTEM_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
