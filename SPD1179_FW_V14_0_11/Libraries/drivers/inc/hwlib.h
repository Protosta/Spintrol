/******************************************************************************
 * @file     hwlib.h
 * @brief    System library header file.
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


#ifndef HWLIB_H
#define HWLIB_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  EEPROM status definitions
 */
#define EEPROM_STATUS_OK                ((uint32_t)0x00000000U)    /* Operation success                                                  */
#define EEPROM_STATUS_WRITE_ERROR       ((uint32_t)0x00000001U)    /* Flash program error                                                */
#define EEPROM_STATUS_ERASE_ERROR       ((uint32_t)0x00000002U)    /* Flash erase error                                                  */
#define EEPROM_STATUS_INVALID_ADDR      ((uint32_t)0x00000004U)    /* Invalid variable address                                           */
#define EEPROM_STATUS_WRITE_CHECK_FAIL  ((uint32_t)0x00000008U)    /* Write check fail                                                   */
#define EEPROM_STATUS_NO_DATA           ((uint32_t)0x00000010U)    /* Not find variable when reading                                     */
#define EEPROM_STATUS_INVALID_ENTRY     ((uint32_t)0x00000020U)    /* The entry address value is invalid                                 */
#define EEPROM_STATUS_ELEMENT_NOT_EMPTY ((uint32_t)0x00000040U)    /* The element content is not empty                                   */
#define EEPROM_STATUS_ADDR_MISMATCH     ((uint32_t)0x00000080U)    /* The variable address is not equal with the address in EEPROM element */
#define EEPROM_STATUS_PARITY_ERROR      ((uint32_t)0x00000100U)    /* The element content parity check error                             */
#define EEPROM_STATUS_PAGE_FULL         ((uint32_t)0x00000200U)    /* Page full                                                          */
#define EEPROM_STATUS_NO_PAGE_FOUND     ((uint32_t)0x00000400U)    /* No suitable page found                                             */
#define EEPROM_STATUS_PAGE_HEADER_ERROR ((uint32_t)0x00000800U)    /* Page header set error                                              */
#define EEPROM_STATUS_INVALID_CB        ((uint32_t)0x00001000U)    /* Invalid MEEPROM control block                                      */
#define EEPROM_STATUS_TRANSFER_ERROR    ((uint32_t)0x40000000U)    /* Transfer page error, ORed with other status                        */
#define EEPROM_STATUS_INVALID_HEADER    ((uint32_t)0x80000000U)    /* Invalid page header state, ORed with other status                  */




/**
 *  @brief SYSTEM status definitions
 */
#define SYSTEM_STATUS_OK                (0x00U)
#define SYSTEM_STATUS_ADDR_UNALIGN      (0x01U)
#define SYSTEM_STATUS_REG_CHECK_FAIL    (0x06U)




/**
 *  @brief  Structure type to access the MEEPROM Control Block
 */
typedef struct
{
    uint32_t    BASE_ADDR;                  /* MEEPROM Base address in main Flash        */
    uint32_t    u32SectorNumOfPage;         /* Flash sector number of a EEPROM page      */
    uint32_t    u32MaxVarNum;               /* Maximum variable number                   */
    uint32_t*   pEntryTable;                /* Pointer to the start of the entry table
                                               the table item number must > u32MaxVarNum */
    uint32_t    u32Next;                    /* Next address for variable written         */
} MEEPROM_CB;




struct SVPWM_T
{
    int32_t    i32Amp;
	int32_t    i32AmpLimit;
	int32_t    i32AmpFilter;
    float      f32DutyShrink;   // (0~1.0)  --> (1~100%)
};




struct Bubble_T{
	int32_t     ai32Array[3][2];
	int32_t     ai32ArrayLast[3][2];
	#define     GET_VALUE 1
	#define     GET_INDEX 0
};




struct CurrentReconstruct_T
{
	int8_t       i8ReconstructEnable;
	int16_t      i16UVW_Flag;
	int16_t      i16UVW_FlagLast;
	int16_t      i16UVW_FlagLast2;
	int16_t      i16CurrentAngle;
	int16_t      i16CurrentAnglePredict;
	int32_t      i32InvSine,i32Amplitude;
	struct       Bubble_T sMyUVW_Bubble;
	uint16_t     au8TrustArray[4];

    int16_t      i16_DutyU;
    int16_t      i16_DutyV;
    int16_t      i16_DutyW;
	int16_t      i16OffsetU;
	int16_t      i16OffsetV;
	int16_t      i16OffsetW;
	int16_t      i16Ia;
	int16_t      i16Ib;
	int16_t      i16Ia0, i16Ia1, i16Ia2, i16Ia3;
	int16_t      i16Ib0, i16Ib1, i16Ib2, i16Ib3;
    int16_t      i16IaZero;
    int16_t      i16IbZero;
	int16_t      u8SampleMode;
	int16_t      u8SampleModeLast;
	int16_t      i16T1Cycle, i16T2Cycle, i16T3Cycle, i16T4Cycle, i16T5Cycle, i16T6Cycle, i16T7Cycle;

    float      f32IaA,  f32IbA;
    float      fDeadT, fTSys, fVibrationT, fSampleT, fDelayT;

    uint32_t   gu32PWMPeriod;

    int16_t    i16_I_U, i16_I_V, i16_I_W;
    int16_t    i16_I_U_Last, i16_I_V_Last, i16_I_W_Last;

    int16_t    i16TriggerPoint, i16TriggerPoint2;
};




/**
 *  @brief  Function Pointers of Hardware Library
 */
typedef struct
{
    /* 0x1000 */
    /******************************************************************************
    * @brief      Initialize Flash module configurations
    *
    * @param[in]  None
    *
    * @return     FLASH_OP_SUCCESS :  Success
    *             FLASH_OP_TIMEOUT :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_Init)(void);
    /* 0x1004 */
    /******************************************************************************
    * @brief      Read word
    *
    * @param[in]  pu32Buf    :  Pointer to the array stored data to be readed
    * @param[in]  u32Addr    :  The start address to be readed
    * @param[in]  u32NumWords:  Number of words to be readed
    *
    * @return     FLASH_OP_SUCCESS              :  Success
    *             FLASH_OP_INVALID_READ_ADDRESS :  Invalid address range to read
    *             FLASH_OP_INVALID_PARAMETER    :  Invalid array address to store data
    *             FLASH_OP_TIMEOUT              :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_Read)(uint32_t *pu32Buf, uint32_t u32Addr, uint32_t u32NumWords);
    /* 0x1008 */
    /******************************************************************************
    * @brief      Verify Read word
    *             Because of the stricter threshold, 
    *             it is easier to read wrong data than FLASHC_Read().
    *
    * @param[in]  pu32Buf    :  Pointer to the array stored data to be readed
    * @param[in]  u32Addr    :  The start address to be readed
    * @param[in]  u32NumWords:  Number of words to be readed
    *
    * @return     FLASH_OP_SUCCESS              :  Success
    *             FLASH_OP_INVALID_READ_ADDRESS :  Invalid address range to read
    *             FLASH_OP_INVALID_PARAMETER    :  Invalid array address to store data
    *             FLASH_OP_TIMEOUT              :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_VerifyRead)(uint32_t *pu32Buf, uint32_t u32Addr, uint32_t u32NumWords);
    /* 0x100C */
    /******************************************************************************
    * @brief      Program a double word data
    *
    * @param[in]  u32Addr    :  The address to be written (Double word aligned)
    * @param[in]  u32LowWord :  Low word of the 64-bit data to be written
    * @param[in]  u32HighWord:  High word of the 64-bit data to be written
    *
    * @return     FLASH_OP_SUCCESS               : Success
    *             FLASH_OP_INVALID_WRITE_ADDRESS : Invalid address to program
    *             FLASH_OP_NO_PERMISSION         : No permission to program
    *             FLASH_OP_TIMEOUT               : Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_ProgramDWord)(uint32_t u32Addr, uint32_t u32LowWord, uint32_t u32HighWord);
    /* 0x1010 */
    /******************************************************************************
    * @brief      Program word data
    *
    * @param[in]  pu32Buf    :  Pointer to the array stored data to be written
    * @param[in]  u32Addr    :  The start address to be written
    *                           It should be double-word aligned
    * @param[in]  u32NumWords:  Number of words to be written
    *                           It should be an even number
    *
    * @return     FLASH_OP_SUCCESS               :  Success
    *             FLASH_OP_INVALID_WRITE_ADDRESS :  Invalid write address range
    *             FLASH_OP_INVALID_PARAMETER     :  Invalid number of words to be written
    *             FLASH_OP_NO_PERMISSION         :  No permission to program
    *             FLASH_OP_TIMEOUT               :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_Program)(uint32_t *pu32Buf, uint32_t u32Addr, uint32_t u32NumWords);
    /* 0x1014 */
    /******************************************************************************
    * @brief      Erase flash sector
    *
    * @param[in]  u32SectorAddr:  Sector address, align in 4096 bytes
    *
    * @return     FLASH_OP_SUCCESS               :  Success
    *             FLASH_OP_INVALID_WRITE_ADDRESS :  Invalid address for erase
    *             FLASH_OP_NO_PERMISSION         :  No permission to erase
    *             FLASH_OP_TIMEOUT               :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_EraseSector)(uint32_t u32SectorAddr);
    /* 0x1018 */
    /******************************************************************************
    * @brief      Erase flash chip
    *
    * @param[in]  None
    *
    * @return     FLASH_OP_SUCCESS :  Success
    *             FLASH_OP_TIMEOUT :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_EraseChip)(void);
    /* 0x101C */
    /******************************************************************************
    * @brief      Verify erase
    *             Because of the stricter threshold, 
    *             it is easier to read wrong data to compare with All 1,
    *             so it is easier to get FLASH_OP_VERIFY_ERASE_FAIL
    *
    * @param[in]  u32StartAddr:  The start address to be verified
    * @param[in]  u32Size     :  The memeory size to be verified (in bytes)
    *
    * @return     FLASH_OP_SUCCESS              :  Success
    *             FLASH_OP_INVALID_READ_ADDRESS :  Invalid address range to check
    *             FLASH_OP_TIMEOUT              :  Operation timeout
    *             FLASH_OP_VERIFY_ERASE_FAIL    :  Flash content is not erased
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_VerifyErase)(uint32_t u32StartAddr, uint32_t u32Size);
    /* 0x1020 */
    /******************************************************************************
    * @brief      Power up the Flash
    *
    * @param[in]  None
    *
    * @return     FLASH_OP_SUCCESS :  Success
    *             FLASH_OP_TIMEOUT :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_PowerUp)(void);
    /* 0x1024 */
    /******************************************************************************
    * @brief      Power down the Flash
    *
    * @param[in]  None
    *
    * @return     FLASH_OP_SUCCESS :  Success
    *             FLASH_OP_TIMEOUT :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_PowerDown)(void);
    /* 0x1028 */
    /******************************************************************************
    * @brief      Enable write protect for the specified area
    *
    * @param[in]  u32StartAddr:  Flash protect start address
    * @param[in]  u32Size     :  Flash protect size in bytes
    *
    * @return     FLASH_OP_SUCCESS           :  Success
    *             FLASH_OP_INVALID_PARAMETER :  Invalid start address or end address
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_WriteProtect)(uint32_t u32StartAddr, uint32_t u32Size);
    /* 0x102C */
    /******************************************************************************
    * @brief      Disable write protect for the specified area
    *
    * @param[in]  u32StartAddr:  Flash protect start address
    * @param[in]  u32EndAddr  :  Flash protect size in bytes
    *
    * @return     FLASH_OP_SUCCESS           :  Success
    *             FLASH_OP_INVALID_PARAMETER :  Invalid start address or end address
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_WriteUnProtect)(uint32_t u32StartAddr, uint32_t u32Size);
    /* 0x1030 */
    /******************************************************************************
    * @brief      Enable double word cache for Flash XIP
    *
    * @param[in]  None
    *
    * @return     None
    *
    ******************************************************************************/
    void (*FLASHC_EnableCache)(void);
    /* 0x1034 */
    /******************************************************************************
    * @brief      Disable double word cache for Flash XIP
    *
    * @param[in]  None
    *
    * @return     None
    *
    ******************************************************************************/
    void (*FLASHC_DisableCache)(void);
    /* 0x1038 */
    /******************************************************************************
    * @brief      Set Flash timing parameters
    *
    * @param[in]  u32ClkFreq:  System clock frequency (Hz)
    *
    * @return     FLASH_OP_SUCCESS         :  Success
    *             FLASH_OP_SET_TIMING_FAIL :  Fail to set timing parameter
    *             FLASH_OP_TIMEOUT         :  Operation timeout
    *
    ******************************************************************************/
    FlashOperationStatus(*FLASHC_SetTiming)(uint32_t u32ClkFreq);
    /* 0x103C */
    void (*FLASHC_Reserved0)(void);

    /* 0x1040 */
    void (*EEPROM_Reserved0)(void);
    /* 0x1044 */
    void (*EEPROM_Reserved1)(void);
    /* 0x1048 */
    void (*EEPROM_Reserved2)(void);
    /* 0x104C */
    void (*EEPROM_Reserved3)(void);

    /* 0x1050 */
    void (*EEPROM_Reserved4)(void);
    /* 0x1054 */
    void (*EEPROM_Reserved5)(void);
    /* 0x1058 */
    void (*EEPROM_Reserved6)(void);
    /* 0x105C */
    void (*EEPROM_Reserved7)(void);

    /* 0x1060 */
    void (*SYSTEM_Reserved0)(void);

    /* 0x1064 */
    void (*SYSTEM_Reserved1)(void);

    /* 0x1068 */
    void (*SYSTEM_Reserved2)(void);

    /* 0x106C */
    void (*SYSTEM_Reserved3)(void);

    /* 0x1070 */
    /******************************************************************************
    * @brief      Calculate the CRC value of the specified memory area
    *
    * @param[in]  u32StartAddr: The memory area start address
    * @param[in]  u32NumWords : The memory area size in words
    * @param[out] pu32CrcVal  : The calculated CRC value
    *
    * @return     - SYSTEM_STATUS_OK           : if success
    *             - SYSTEM_STATUS_ADDR_UNALIGN : if start address not 4-byte aligned
    *
    ******************************************************************************/
    uint32_t (*SYSTEM_CalculateMemCRC)(uint32_t u32StartAddr, uint32_t u32Size, uint32_t *pu32CrcVal);

    /* 0x1074 */
    void (*SYSTEM_Reserved4)(void);

    /* 0x1078 */
    void (*SYSTEM_Reserved5)(void);

    /* 0x107C */
    /******************************************************************************
    * @brief      Fast Trigonometric sine function
    *
    * @param[in]  i16Theta:  Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    * 
    * @return     Sine value(Q15 format)
    * 
    ******************************************************************************/
    int16_t (*Sin)(int16_t i16Theta);
    /* 0x1080 */
    /******************************************************************************
    * @brief      Fast Trigonometric cosine function
    * 
    * @param[in]  i16Theta:  Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    * 
    * @return     Cosine value(Q15 format)
    * 
    ******************************************************************************/
    int16_t (*Cos)(int16_t i16Theta);
    /* 0x1084 */
    /******************************************************************************
    * @brief      Fast Trigonometric sine function
    * 
    * @param[in]  i16Theta:  Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    * 
    * @return     Sine value(Q15 format)
    *
    * @note       Use the interpolation method.
    * 
    ******************************************************************************/
    int16_t (*Sin2)(int16_t i16Theta);
    /* 0x1088 */
    /******************************************************************************
    * @brief      Fast Trigonometric Cosine function
    * 
    * @param[in]  i16Theta:  Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    * 
    * @return     Cosine value(Q15 format)
    * 
    * @note       Use the interpolation method.
    * 
    ******************************************************************************/
    int16_t (*Cos2)(int16_t i16Theta);
    /* 0x108C */
    /******************************************************************************
    * @brief      Fast Inverse tangent function
    *
    * @param[in]  y: sine value(Qn format)
    *             in range [-2^n, 2^n - 1] and is mapped to [-1, +1]
    * @param[in]  x: cosine value(Qn format)
    *             in range [-2^n, 2^n - 1] and is mapped to [-1, +1]
    * 
    * @return     Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    *
    * @note       "n" is recommended as 15 for the accuracy.
    * 
    ******************************************************************************/
    int16_t (*Atan2)(int16_t y, int16_t x);
    /* 0x1090 */
    /******************************************************************************
    * @brief      Fast Inverse tangent function
    *
    * @param[in]  f32Sin: sine value
    *
    * @param[in]  f32Cos: cosine value
    * 
    * @return     Angle value(unit:rad)
    * 
    ******************************************************************************/
    float (*AtanF32)(float f32Sin, float f32Cos);
    /* 0x1094 */
    /******************************************************************************
    * @brief      Fast square root function
    *
    * @param[in]  x: input data(u32)
    * 
    * @return     sqrt(x) value range[0 +65535]
    * 
    ******************************************************************************/
    uint32_t (*FastSqrt)(uint32_t x);

    /* 0x1098 */
    /******************************************************************************
    * @brief      Fast Trigonometric sine function
    * 
    * @param[in]  i16Theta: Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    * 
    * @return     Sine value(Q15 format)
    * 
    ******************************************************************************/
    int16_t (*Sin512)(int16_t i16_Theta);
    /* 0x109C */
    /******************************************************************************
    * @brief      Fast Trigonometric Cosine function
    * 
    * @param[in]  i16Theta: Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    * 
    * @return     Cosine value(Q15 format)
    * 
    ******************************************************************************/
    int16_t (*Cos512)(int16_t i16_Theta);
    /* 0x10A0 */
    /******************************************************************************
    * @brief      Fast Inverse tangent function
    *
    * @param[in]  y: sine value(Qn format)
    *             in range [-2^n, 2^n - 1] and is mapped to [-1, +1]
    * @param[in]  x: cosine value(Qn format)
    *             in range [-2^n, 2^n - 1] and is mapped to [-1, +1]
    * 
    * @return     Scaled Angle value(Q15 format)
    *             in the range [-32768 +32767] and is mapped to [-pi +pi].
    *
    * @note       "n" is recommended as 15 for the accuracy.
    * 
    ******************************************************************************/
    int16_t (*Atan512)(int16_t y, int16_t x);

    /* 0x10A4 */
    /******************************************************************************
    * @brief      Theta wrap from [-pi +pi].
    *
    * @param[in]  f32ThetaRad: Angle value(unit:rad)  
    * 
    * @return     Angle value(unit:rad)
    *             in range range[-pi +pi]
    * 
    * @note       Adjustment the range for A round period.
    * 
    ******************************************************************************/
    float (*ThetaRadWrap)(float f32ThetaRad);

    /* 0x10A8 */
    /******************************************************************************
    * @brief      saturation function
    *
    * @param[in]  in:  Data input
    * 
    * @param[in]  sat: Max value
    *
    * @return     The saturation value range[0,sat]  
    *
    ******************************************************************************/
    int16_t (*SAT0)(int16_t in,int16_t sat);

    /* 0x10AC */
    void (*Motor_Reserved0)(void);

    /* 0x10B0 */
    /******************************************************************************
    * @brief      Clarke transform function(Equal-amplitude)
    *
    * @param[in]  f32IU:  Axies U value 
    * @param[in]  f32IV:  Axies V value 
    * @param[in]  f32IW:  Axies W value
    *
    * @return     f32UAlfa:  Axies Alpha value
    * @return     f32UBeta:  Axies Beta  value
    *
    ******************************************************************************/ 
    void  (*ClarkeF32)(float f32IU, float f32IV, float f32IW, float *f32UAlfa, float *f32UBeta);

    /* 0x10B4 */
    /******************************************************************************
    * @brief      Invers Park transform function 
    *
    * @param[in]  f32UD:  Axies D value 
    * @param[in]  f32UQ:  Axies Q value 
    * @param[in]  f32Theta:  Angle between Axies D and Axies Alpha range[-pi +pi] 
    *
    * @return     f32UAlfa:  Axies Alpha value
    * @return     f32UBeta:  Axies Beta  value
    *
    ******************************************************************************/ 
    void  (*InvParkF32)(float f32UD, float f32UQ, float f32Theta, float *f32UAlfa, float *f32UBeta);

    /* 0x10B8 */
    /******************************************************************************
    * @brief      Park transform function 
    *
    * @param[in]  f32UAlfa:  Axies Alpha value 
    * @param[in]  f32UBeta:  Axies Beta  value 
    * @param[in]  f32Theta:  Angle between Axies D and Axies Alpha range[-pi +pi]  
    *
    * @return     f32UD:  Axies D value 
    * @return     f32UQ:  Axies Q value 
    *
    ******************************************************************************/ 
    void  (*ParkF32)(float f32UAlfa, float f32UBeta, float f32Theta, float *f32UD, float *f32UQ);

    /* 0x10BC */
    void (*Motor_Reserved1)(void);

    /* 0x10C0 */
    void (*Motor_Reserved2)(void);

    /* 0x10C4 */
    void (*Motor_Reserved3)(void);

    /* 0x10C8 */
    void (*Motor_Reserved4)(void);
} HW_LIB_TypeDef;




/**
 *  @brief  Export Hardware Library Pointer
 */
extern const HW_LIB_TypeDef *pHWLIB;




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* HW_LIB_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
