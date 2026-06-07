/******************************************************************************
 * @file     engr.h
 * @brief    Engineering driver header file.
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


#ifndef ENGR_H
#define ENGR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




#ifndef SPC1169
    #define SPC1169
#endif




/**
 *  @brief  Analog test module definition
 */
typedef enum
{
    ATEST_SYSBG         = 1U << 5,      /*!< System bandgap         */
    ATEST_FLASHREF      = 1U << 6,      /*!< Flash reference        */
    ATEST_BOD           = 1U << 7,      /*!< Brown-out detector     */
    ATEST_RCO           = 1U << 8,      /*!< RCO                    */
    ATEST_XO            = 1U << 9,      /*!< XO                     */
    ATEST_PLL           = 1U << 10,     /*!< PLL                    */
    ATEST_ADCBG         = 1U << 11,     /*!< ADC bandgap            */
    ATEST_AREF1         = 1U << 12,     /*!< FuSa ADC reference     */
    ATEST_ADC1          = 1U << 13,     /*!< FuSa ADC               */
    ATEST_AREF0         = 1U << 14,     /*!< Main ADC reference     */
    ATEST_ADC0          = 1U << 15,     /*!< Main ADC               */
    ATEST_COMPL         = 1U << 16,     /*!< COMPL                  */
    ATEST_COMPH         = 1U << 17,     /*!< COMPH                  */
    ATEST_DAC0          = 1U << 18,     /*!< DAC0                   */
    ATEST_DAC1          = 1U << 19,     /*!< DAC1                   */
    ATEST_DAC2          = 1U << 20,     /*!< DAC2                   */
    ATEST_DACBUF        = 1U << 21,     /*!< DAC buffer             */
    ATEST_D2SBUF        = 1U << 22,     /*!< D2S buffer             */
    ATEST_SPGA          = 1U << 23,     /*!< Single-ended PGA       */
    ATEST_DPGA          = 1U << 24,     /*!< Differential PGA       */
    ATEST_TSENS         = 1U << 25,     /*!< Temperature sensor     */
    ATEST_PHCOMPU       = 1U << 26,     /*!< U phase comparator     */
    ATEST_PHCOMPV       = 1U << 27,     /*!< V phase comparator     */
    ATEST_PHCOMPW       = 1U << 28,     /*!< W phase comparator     */
    ATEST_EPWR          = 1U << 29,     /*!< ePower ATEST input     */
} ENGR_AnalogTestModuleEnum;



/**
 *  @brief  FuSa ADC SH Positive Input Selection Definition
 */
typedef enum
{
    ADC1_SH_P_GND       = 0U,       /*!< VDD33                      */
    ADC1_SH_P_ANA_IN0   = 1U,       /*!< ANA_IN0 pin                */
    ADC1_SH_P_TSENSOR_P = 2U,       /*!< T-sensor positive output   */
    ADC1_SH_P_DAC2      = 3U,       /*!< DAC2                       */
    ADC1_SH_P_VDD33     = 4U,       /*!< VDD33                      */
    ADC1_SH_P_VAREF0    = 5U,       /*!< Main ADC reference         */
    ADC1_SH_P_VDD12     = 6U,       /*!< VDD12                      */
    ADC1_SH_P_ATEST     = 7U,       /*!< ATEST                      */
} ADC1_SH_PositiveInputEnum;




/**
 *  @brief  FuSa ADC SH Negative Input Selection Definition
 */
typedef enum
{
    ADC1_SH_N_GND       = 0U,       /*!< Ground                     */
    ADC1_SH_N_ANA_IN1   = 1U,       /*!< ANA_IN1 pin                */
    ADC1_SH_N_TSENSOR_N = 2U,       /*!< T-sensor negative output   */
    ADC1_SH_N_DAC1      = 3U,       /*!< DAC1                       */
} ADC1_SH_NegativeInputEnum;




/**
 *  @brief  Power Monitor Selection Definition
 */
typedef enum
{
  PMON_VBAT                   = 0x0U,      /*!< VBAT               */
  PMON_VCP                    = 0x1U,      /*!< VCP                */
  PMON_VMON                   = 0x2U,      /*!< MON pin voltage    */
  PMON_VDD5                   = 0x3U,      /*!< VDD5               */
  PMON_VBG                    = 0x4U,      /*!< HV chip bandgap    */
  PMON_TPMU                   = 0x5U,      /*!< PMU temperature sensor voltage */
  PMON_TLIN                   = 0x6U,      /*!< LIN temperature sensor voltage */
} EPWR_MonitorItemEnum;




/**
 *  @brief  Software forced memory access error options
 */
typedef enum
{
    READ_ROM_ERROR          = (1U << 0 ),   /* Error when read ROM              */
    READ_FLASH_ERROR        = (1U << 1 ),   /* Error when read FLASH            */
    READ_RAM0_ERROR         = (1U << 2 ),   /* Error when read RAM0             */
    READ_RAM1_ERROR         = (1U << 3 ),   /* Error when read RAM1             */
    READ_CAN_ERROR          = (1U << 4 ),   /* Error when read CAN              */

    WRITE_FLASH_ERROR       = (1U << 17),   /* Error when write FLASH           */
    WRITE_RAM0_ERROR        = (1U << 18),   /* Error when write RAM0            */
    WRITE_RAM1_ERROR        = (1U << 19),   /* Error when write RAM1            */
    WRITE_CAN_ERROR         = (1U << 20),   /* Error when write CAN             */

    MEMORY_ACCESS_ERROR_ALL = 0x001E001FU   /* All memory access error          */
} ENGR_MemoryAccessErrorEnum;




/******************************************************************************
 * @brief      Set LDO trim code
 *
 * @param[in]  u8Code: LDO output voltage trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetLDOTrimCode(u8Code)         (ENGR->PWRTRIM = (u8Code) | PWRTRIM_LDOWE_ENABLE)




/******************************************************************************
 * @brief      Get LDO trim code
 *
 * @param[in]  None
 *
 * @return     LDO output voltage trim code
 *
 ******************************************************************************/
#define ENGR_GetLDOTrimCode()               (ENGR->PWRTRIM & PWRTRIM_LDO_Msk)




/******************************************************************************
 * @brief      Set BOD reference trim Code
 *
 * @param[in]  u8Code: BOD reference voltage trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetBODRefTrimCode(u8Code)      (ENGR->PWRTRIM = ((u8Code) << PWRTRIM_BOD_Pos) | PWRTRIM_BODWE_ENABLE)




/******************************************************************************
 * @brief      Get BOD reference trim code
 *
 * @param[in]  None
 *
 * @return     BOD reference trim code
 *
 ******************************************************************************/
#define ENGR_GetBODRefTrimCode()            ((ENGR->PWRTRIM & PWRTRIM_BOD_Msk) >> PWRTRIM_BOD_Pos)




/******************************************************************************
 * @brief      Set Flash reference trim Code
 *
 * @param[in]  u8Code: Flash reference voltage trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetFlashRefTrimCode(u8Code)    (ENGR->PWRTRIM = ((u8Code) << PWRTRIM_FVREF_Pos) | PWRTRIM_FVREFWE_ENABLE)




/******************************************************************************
 * @brief      Get Flash reference trim code
 *
 * @param[in]  None
 *
 * @return     Flash reference trim code
 *
 ******************************************************************************/
#define ENGR_GetFlashRefTrimCode()          ((ENGR->PWRTRIM & PWRTRIM_FVREF_Msk) >> PWRTRIM_FVREF_Pos)




/******************************************************************************
 * @brief      Set LPLDO output voltage trim code
 *
 * @param[in]  u8CodeLo: Select the LPLDO output voltage lower boundry
 * @param[in]  u8CodeHi: Select the LPLDO output voltage upper boundry
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetLPLDOTrimCode(u8CodeLo, u8CodeHi)   (ENGR->LPLDOTRIM = (u8CodeLo) | ((u8CodeHi) << LPLDOTRIM_VOUTHI_Pos) | 0x8080U)




/******************************************************************************
 * @brief      Get LPLDO output voltage lower boundry trim code
 *
 * @param[in]  None
 *
 * @return     LPLDO output voltage lower boundry trim code
 *
 ******************************************************************************/
#define ENGR_GetLPLDOTrimCodeLow()          ((ENGR->LPLDOTRIM & LPLDOTRIM_VOUTLO_Msk) >> LPLDOTRIM_VOUTLO_Pos)




/******************************************************************************
 * @brief      Get LPLDO output voltage upper boundry trim code
 *
 * @param[in]  None
 *
 * @return     LPLDO output voltage upper boundry trim code
 *
 ******************************************************************************/
#define ENGR_GetLPLDOTrimCodeHigh()         ((ENGR->LPLDOTRIM & LPLDOTRIM_VOUTHI_Msk) >> LPLDOTRIM_VOUTHI_Pos)




/******************************************************************************
 * @brief      Set RCO trim Code
 *
 * @param[in]  u16Code: RCO frequency trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetRCOTrimCode(u16Code)        (ENGR->CLKTRIM = (u16Code) | CLKTRIM_RCOWE_ENABLE)




/******************************************************************************
 * @brief      Get RCO trim code
 *
 * @param[in]  None
 *
 * @return     RCO frequency trim code
 *
 ******************************************************************************/
#define ENGR_GetRCOTrimCode()               ((ENGR->CLKTRIM & CLKTRIM_RCO_Msk) >> CLKTRIM_RCO_Pos)




/******************************************************************************
 * @brief      Set ROSC trim Code
 *
 * @param[in]  u8Code: ROSC frequency trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetROSCTrimCode(u8Code)        (ENGR->CLKTRIM = ((u8Code) << CLKTRIM_ROSC_Pos) | CLKTRIM_ROSCWE_ENABLE)




/******************************************************************************
 * @brief      Get ROSC trim code
 *
 * @param[in]  None
 *
 * @return     ROSC frequency trim code
 *
 ******************************************************************************/
#define ENGR_GetROSCTrimCode()              ((ENGR->CLKTRIM & CLKTRIM_ROSC_Msk) >> CLKTRIM_ROSC_Pos)




/******************************************************************************
 * @brief      Set VCO trim Code
 *
 * @param[in]  u8Code: VCO frequency trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetVCOTrimCode(u8Code)         (ENGR->CLKTRIM = ((u8Code) << CLKTRIM_VCO_Pos) | CLKTRIM_VCOWE_ENABLE)




/******************************************************************************
 * @brief      Get VCO trim code
 *
 * @param[in]  None
 *
 * @return     VCO frequency trim code
 *
 ******************************************************************************/
#define ENGR_GetVCOTrimCode()               ((ENGR->CLKTRIM & CLKTRIM_VCO_Msk) >> CLKTRIM_VCO_Pos)




/******************************************************************************
 * @brief      Set ADC VREF trim Code
 *
 * @param[in]  u8Code: Reference voltage trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetADCReferenceTrimCode(u8Code)    (ENGR->AREF13TRIM = ((u8Code) << AREF13TRIM_VREF_Pos) | AREF13TRIM_VREFWE_ENABLE)




/******************************************************************************
 * @brief      Set ADC VDIG trim Code
 *
 * @param[in]  u8Code: Slave digital regulator trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetADCDigitalSlaveRegulatorTrimCode(u8Code)    (ENGR->AREF13TRIM = ((u8Code) << AREF13TRIM_VDIG_Pos) | AREF13TRIM_VDIGWE_ENABLE)




/******************************************************************************
 * @brief      Set ADC VANA trim Code
 *
 * @param[in]  u8Code: Slave analog regulator trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetADCAnalogSlaveRegulatorTrimCode(u8Code)     (ENGR->AREF13TRIM = ((u8Code) << AREF13TRIM_VANA_Pos) | AREF13TRIM_VANAWE_ENABLE)




/******************************************************************************
 * @brief      Set ADC VMST trim Code
 *
 * @param[in]  u8Code: Master regulator trim code
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetADCMasterRegulatorTrimCode(u8Code)          (ENGR->AREF13TRIM = ((u8Code) << AREF13TRIM_VMST_Pos) | AREF13TRIM_VMSTWE_ENABLE)




/******************************************************************************
 * @brief      Select analog test point
 *
 * @param[in]  u8Sel: Select test point from 0 to 15
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SelectAnalogTestPoint(u8Sel)   (ENGR->ATESTCTL = (ENGR->ATESTCTL & ~ATESTCTL_TPSEL_Msk) | (u8Sel & 0xf))




/******************************************************************************
 * @brief      Enable BOD
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableBOD()            SET_BITS(ENGR->PWRENGR, PWRENGR_BODEN_Msk)
#define ENGR_DisableBOD()           CLEAR_BITS(ENGR->PWRENGR, PWRENGR_BODEN_Msk)
#define ENGR_IsEnableBOD()          (ENGR->PWRENGR & PWRENGR_BODEN_Msk)




/******************************************************************************
 * @brief      Enable analog test output
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableAnalogTestOutput()                                           \
  SET_BITS(ENGR->ATESTCTL, ATESTCTL_OE_Msk)

#define ENGR_DisableAnalogTestOutput()                                          \
  CLEAR_BITS(ENGR->ATESTCTL, ATESTCTL_OE_Msk)

#define ENGR_IsEnableAnalogTestOutput()                                         \
  (ENGR->ATESTCTL & ATESTCTL_OE_Msk)




/******************************************************************************
 * @brief      Enable analog test module
 *
 * @param[in]  eModule: Select the module for analog test from ENGR_AnalogTestModuleEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetAnalogTestModule(eModules)                                      \
  MODIFY_REG(ENGR->ATESTCTL, ~0x0000001F, ~0x0000001F & (eModules) )

#define ENGR_EnableAnalogTestModule(eModules)                                   \
  SET_BITS(ENGR->ATESTCTL, ~0x0000001F & (eModules) )

#define ENGR_DisableAnalogTestModule(eModules)                                  \
  CLEAR_BITS(ENGR->ATESTCTL, ~0x0000001F & (eModules) )

#define ENGR_IsEnableAnalogTestModule(eModules)                                 \
  (ENGR->ATESTCTL & (eModule))



/******************************************************************************
 * @brief      Enable system monitor
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableSystemMonitor()          (ENGR->SYSMONSTOPKEY = 0U)




/******************************************************************************
 * @brief      Disable system monitor
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableSystemMonitor()         (ENGR->SYSMONSTOPKEY = 0x1acce551U)




/******************************************************************************
 * @brief      Enable ADC bandgap
 *
 * @param[in]  None
 *
 * @return     None
 *
 * @note       Bandgap shared by FuSa ADC and main ADC
 *
 ******************************************************************************/
#define ENGR_EnableADCBandgap()                                                 \
  SET_BITS(ENGR->AFEENGR1, AFEENGR1_ADCBGEN_Msk)

#define ENGR_DisableADCBandgap()                                                \
  CLEAR_BITS(ENGR->AFEENGR1, AFEENGR1_ADCBGEN_Msk)




/******************************************************************************
 * @brief      Get ADC bandgap setting
 *
 * @param[in]  None
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ENGR_IsEnableADCBandgap()                                               \
  (ENGR->AFEENGR1 & AFEENGR1_ADCBGEN_Msk)




/******************************************************************************
 * @brief      Enable/disable FuSa ADC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC1_Enable()                       (ENGR->AFEENGR1 |= 6U)
#define ADC1_Disable()                      (ENGR->AFEENGR1 &= 0xfffffff9U)




/******************************************************************************
 * @brief      Get FuSa ADC enable setting
 *
 * @param[in]  None
 *
 * @return     0     - None of the queried settings is enabled;
 *             not 0 - Corresponding settings for non-zero bit is enabled.
 *
 ******************************************************************************/
#define ADC1_IsEnable()                     (ENGR->AFEENGR1 & 6U)




/******************************************************************************
 * @brief      Set FuSa ADC input
 *
 * @param[in]  ePosIn:  ADC positive input channel selection as defined
 *                      by ADC1_PositiveInputEnum
 * @param[in]  eNegIn:  ADC negative input channel selection as defined
 *                      by ADC1_NegativeInputEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC1_SetInputChannel(ePosIn, eNegIn)    (ENGR->AFEENGR1 = (ENGR->AFEENGR1 & ~(AFEENGR1_ADC1CHSELP_Msk | AFEENGR1_ADC1CHSELN_Msk)) | ((ePosIn) << AFEENGR1_ADC1CHSELP_Pos) | ((eNegIn) << AFEENGR1_ADC1CHSELN_Pos))
#define ADC1_GetPositiveInputChannel()          ((ENGR->AFEENGR1 & AFEENGR1_ADC1CHSELP_Msk) >> AFEENGR1_ADC1CHSELP_Pos)
#define ADC1_GetNegativeInputChannel()          ((ENGR->AFEENGR1 & AFEENGR1_ADC1CHSELN_Msk) >> AFEENGR1_ADC1CHSELN_Pos)



/******************************************************************************
 * @brief      Set ePower monitor channel
 *
 * @param[in]  eCh: ePower monitor channel as define by EPWR_MonitorItemEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetEPWRMonitorChannel(eCh)     (ENGR->HVMONCTL = (eCh))
#define ENGR_GetEPWRMonitorChannel()        (ENGR->HVMONCTL)




/******************************************************************************
 * @brief      Software trigger FuSa ADC conversion
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC1_SoftwareTrigger()              (ENGR->AFEENGR1 |= AFEENGR1_ADC1SOC_RUN)




/******************************************************************************
 * @brief      Is FuSa ADC conversion busy running
 *
 * @param[in]  None
 *
 * @return     0 - Conversion is done
 *             1 - Conversion is busy running
 *
 ******************************************************************************/
#define ADC1_IsBusy()                       ((ENGR->AFEENGR1 >> AFEENGR1_ADC1SOC_Pos) & 1U)




/******************************************************************************
 * @brief      Get FuSa ADC conversion result
 *
 * @param[in]  None
 *
 * @return     FuSa ADC code
 *
 ******************************************************************************/
#define ADC1_GetResult()                    (ENGR->ADC1CODE)




/******************************************************************************
 * @brief      Set FuSa ADC offset
 *
 * @param[in]  i32Offset: Offset
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC1_SetOffset(i32Offset)           (ENGR->ADC1OFFSET = (i32Offset))
#define ADC1_GetOffset()                    (ENGR->ADC1OFFSET)




/******************************************************************************
 * @brief      Set FuSa ADC gain
 *
 * @param[in]  u32Gain: gain scaled by 32768
 *
 * @return     None
 *
 ******************************************************************************/
#define ADC1_SetGain(u32Gain)               (ENGR->ADC1GAIN = (u32Gain))
#define ADC1_GetGain()                      (ENGR->ADC1GAIN)




/******************************************************************************
 * @brief      Set ROM option
 *
 * @param[in]  eOpt: Select the ROM option
 *                   Please refer to SYSTEM_OptionEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetROMOption(eOpt)             (ENGR->SYSOPT = (ENGR->SYSOPT & ~SYSOPT_ROMSIZE_Msk) | (eOpt))




/******************************************************************************
 * @brief      Set RAM option
 *
 * @param[in]  eOpt: Select the RAM option
 *                   Please refer to SYSTEM_OptionEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetRAMOption(eOpt)             (ENGR->SYSOPT = (ENGR->SYSOPT & ~SYSOPT_RAMSIZE_Msk) | ((eOpt) << SYSOPT_RAMSIZE_Pos))




/******************************************************************************
 * @brief      Set Flash option
 *
 * @param[in]  eOpt: Select the Flash option
 *                   Please refer to SYSTEM_OptionEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetFlashOption(eOpt)           (ENGR->SYSOPT = (ENGR->SYSOPT & ~SYSOPT_FLASHSIZE_Msk) | ((eOpt) << SYSOPT_FLASHSIZE_Pos))




/******************************************************************************
 * @brief      Set Clock option
 *
 * @param[in]  eOpt: Select the clock option
 *                   Please refer to SYSTEM_OptionEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetClockOption(eOpt)           (ENGR->SYSOPT = (ENGR->SYSOPT & ~SYSOPT_CKOPT_Msk) | ((eOpt) << SYSOPT_CLKOPT_Pos))




/******************************************************************************
 * @brief      Set ADC resolution option
 *
 * @param[in]  eOpt: Select the ADC resolution option
 *                   Please refer to SYSTEM_OptionEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetADCOption(eOpt)             (ENGR->SYSOPT = (ENGR->SYSOPT & ~SYSOPT_ADCBIT_Msk) | ((eOpt) << SYSOPT_ADCBIT_Pos))




/******************************************************************************
 * @brief      Set full system option
 *
 * @param[in]  u32Opt: Full option control word
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetFullOption(u32Opt)          (ENGR->SYSOPT = (u32Opt))




/******************************************************************************
 * @brief      Enable ROM ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableROMECC()                 SET_BIT(ENGR->MEMECCEN, MEMECCEN_ROMECC_Pos)




/******************************************************************************
 * @brief      Disable ROM ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableROMECC()                CLEAR_BIT(ENGR->MEMECCEN, MEMECCEN_ROMECC_Pos)




/******************************************************************************
 * @brief      Enable Flash ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableFlashECC()               SET_BIT(ENGR->MEMECCEN, MEMECCEN_FLASHECC_Pos)




/******************************************************************************
 * @brief      Disable Flash ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableFlashECC()              CLEAR_BIT(ENGR->MEMECCEN, MEMECCEN_FLASHECC_Pos)




/******************************************************************************
 * @brief      Enable RAM0 ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableRAM0ECC()                 SET_BIT(ENGR->MEMECCEN, MEMECCEN_RAM0ECC_Pos)




/******************************************************************************
 * @brief      Disable RAM0 ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableRAM0ECC()                CLEAR_BIT(ENGR->MEMECCEN, MEMECCEN_RAM0ECC_Pos)




/******************************************************************************
 * @brief      Enable RAM1 ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableRAM1ECC()                 SET_BIT(ENGR->MEMECCEN, MEMECCEN_RAM1ECC_Pos)




/******************************************************************************
 * @brief      Disable RAM1 ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableRAM1ECC()                CLEAR_BIT(ENGR->MEMECCEN, MEMECCEN_RAM1ECC_Pos)




/******************************************************************************
 * @brief      Enable CAN ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableCANECC()                 SET_BIT(ENGR->MEMECCEN, MEMECCEN_CANECC_Pos)




/******************************************************************************
 * @brief      Disable CAN ECC
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableCANECC()                CLEAR_BIT(ENGR->MEMECCEN, MEMECCEN_CANECC_Pos)




/******************************************************************************
 * @brief      Lock Flash NVR
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_LockFlashNVR()                 (ENGR->MEMLOCK |= MEMLOCK_FLASHNVR_Msk)




/******************************************************************************
 * @brief      Lock Flash pin
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_LockFlashPin()                 (ENGR->MEMLOCK |= MEMLOCK_FLASHPIN_Msk)




/******************************************************************************
 * @brief      Lock security
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_LockSecurity()                 (ENGR->MEMLOCK |= MEMLOCK_SECURITY_Msk)




/******************************************************************************
 * @brief      Is Flash NVR locked
 *
 * @param[in]  None
 *
 * @return     0 - Flash NVR is not locked
 *             1 - Flash NVR is locked
 *
 ******************************************************************************/
#define ENGR_IsFlashNVRLocked()             ((ENGR->MEMLOCK & MEMLOCK_FLASHNVR_Msk ) >> MEMLOCK_FLASHNVR_Pos)




/******************************************************************************
 * @brief      Is FLASHPIN register locked
 *
 * @param[in]  None
 *
 * @return     0 - FLASHPIN register is not locked
 *             1 - FLASHPIN register is locked
 *
 ******************************************************************************/
#define ENGR_IsFlashPinLocked()             ((ENGR->MEMLOCK & MEMLOCK_FLASHPIN_Msk) >> MEMLOCK_FLASHPIN_Pos)




/******************************************************************************
 * @brief      Is SECURITY register locked
 *
 * @param[in]  None
 *
 * @return     0 - SECURITY register is not locked
 *             1 - SECURITY register is locked
 *
 ******************************************************************************/
#define ENGR_IsSecurityLocked()             ((ENGR->MEMLOCK & MEMLOCK_SECURITY_Msk) >> MEMLOCK_SECURITY_Pos)




/******************************************************************************
 * @brief      Enable bus fault
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableBusFault()               (ENGR->SYSENGR &= ~SYSENGR_HRESPERREN_Msk)




/******************************************************************************
 * @brief      Disable bus fault
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableBusFault()              (ENGR->SYSENGR = (ENGR->SYSENGR & ~SYSENGR_HRESPERREN_Msk) | 0x5A)




/******************************************************************************
 * @brief      Enable debug interface
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_EnableDebugInterface()         (ENGR->DBGIFKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable debug interface
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_DisableDebugInterface()        (ENGR->DBGIFKEY = 0x0)




/******************************************************************************
 * @brief      Force bit error pattern
 *
 * @param[in]  u8Idx  :  Bit range selection to force the memory error
 *                       0 - Bit [31: 0]
 *                       1 - Bit [63:32]
 *                       2 - Bit [95:64]
 * @param[in]  u32Pat :  Bit error pattern for the selected 32-bit
 *                       0 - Do not force errror on the bit
 *                       1 - Force error on the bit
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_ForceMemoryErrorPattern(u8Idx, u32Pat)  (ENGR->BITERRPAT[(u8Idx)] = (u32Pat))
#define ENGR_ForceAHBBitErrorPattern(u8Idx, u32Pat)  (ENGR->BITERRPAT[(u8Idx)] = (u32Pat))




/******************************************************************************
 * @brief      Force memory access error
 *
 * @param[in]  eErr: Select the memory access type to force the error
 *                   Please refer to ENGR_MemoryAccessErrorEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_ForceMemoryAccessError(eErr)   SET_BITS(ENGR->MEMERRFRC, (eErr))
#define ENGR_IsForceMemoryAccessError(eErr)   READ_BITS(ENGR->MEMERRFRC, (eErr))




/******************************************************************************
 * @brief      Force Bus access error
 *
 * @param[in]  eErr: Select the memory access type to force the error
 *                   Please refer to ENGR_MemoryAccessErrorEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_ForceAHBAccessError(eErr)      (ENGR->AHBERRFRC[(eErr)/32] = (1 << (eErr % 32)))




/******************************************************************************
 * @brief      Set value of Test Information register
 *
 * @param[in]  u32Idx : Index of TESTINFO[] register
 * @param[in]  u32Info: Value to be written to the register
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_SetTestInfo(u32Idx, u32Info)   WRITE_REG(ENGR->TESTINFO[(u32Idx)], (u32Info))
#define ENGR_GetTestInfo(u32Idx)            READ_REG(ENGR->TESTINFO[(u32Idx)])




/******************************************************************************
 * @brief      Enable write access to the protected ENGR registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_WALLOW()                       (ENGR->ENGRREGKEY = 0x1ACCE551U)




/******************************************************************************
 * @brief      Disable write access to the protected ENGR registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define ENGR_WDIS()                         (ENGR->ENGRREGKEY = 0x0U)




/**
 *  @brief ENGR Public Function Declaration
 */




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* ENGR_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
