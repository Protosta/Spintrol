/******************************************************************************
 * @file     pga.h
 * @brief    PGA driver header file.
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


#ifndef PGA_H
#define PGA_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  PGA Input selection
 */
typedef enum
{
    SPGA_FROM_ANA_IN0     = 0U,               /*!< ANA_IN0                 */
    SPGA_FROM_ANA_IN1     = 1U,               /*!< ANA_IN1                 */
    SPGA_FROM_ANA_IN2     = 2U,               /*!< ANA_IN2                 */
    SPGA_FROM_ANA_IN3     = 3U,               /*!< ANA_IN3                 */
    SPGA_FROM_ANA_IN4     = 4U,               /*!< ANA_IN4                 */
    SPGA_FROM_TSENS_N     = 5U,               /*!< TSENS_N                 */
    SPGA_FROM_TSENS_P     = 6U,               /*!< TSENS_P                 */
    SPGA_FROM_ATEST       = 7U,               /*!< ATEST                   */
} PGA_InputSelEnum;




/**
 *  @brief  PGA Gain
 */
typedef enum
{
    SPGA_GAIN_1X          = 0U,               /*!< 1x  for SPGA         */
    SPGA_GAIN_2X          = 1U,               /*!< 2x  for SPGA         */
    SPGA_GAIN_4X          = 2U,               /*!< 4x  for SPGA         */
    SPGA_GAIN_8X          = 3U,               /*!< 8x  for SPGA         */
    SPGA_GAIN_16X         = 4U,               /*!< 16x for SPGA         */
    SPGA_GAIN_32X         = 5U,               /*!< 32x for SPGA         */
    SPGA_GAIN_48X         = 6U,               /*!< 48x for SPGA         */
    SPGA_GAIN_64X         = 7U,               /*!< 64x for SPGA         */

    DPGA_GAIN_2X          = 0U,               /*!< 2x  for DPGA         */
    DPGA_GAIN_4X          = 1U,               /*!< 4x  for DPGA         */
    DPGA_GAIN_8X          = 2U,               /*!< 8x  for DPGA         */
    DPGA_GAIN_16X         = 3U,               /*!< 16x for DPGA         */
    DPGA_GAIN_24X         = 4U,               /*!< 24x for DPGA         */
    DPGA_GAIN_32X         = 5U,               /*!< 32x for DPGA         */
    DPGA_GAIN_48X         = 6U,               /*!< 48x for DPGA         */
    DPGA_GAIN_64X         = 7U,               /*!< 64x for DPGA         */
} PGA_GainEnum;




/******************************************************************************
 * @brief      Enable DPGA
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_EnableDPGA()                    (PGA->DPGACTL |= DPGACTL_EN_ENABLE)




/******************************************************************************
 * @brief      Disable SPGA
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_DisableDPGA()                   (PGA->DPGACTL &= ~DPGACTL_EN_ENABLE)




/******************************************************************************
 * @brief      Enable DPGA bypass
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_EnableDPGABypass()              (PGA->DPGACTL |= DPGACTL_BYP_ENABLE)




/******************************************************************************
 * @brief      Disable DPGA bypass
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_DisableDPGABypass()             (PGA->DPGACTL &= ~DPGACTL_BYP_ENABLE)




/******************************************************************************
 * @brief      Set DPGA gain
 *
 * @param[in]  eGain:  Gain selection, defined by PGA_GainEnum
 *                     \ref - DPGA_GAIN_2X ~ DPGA_GAIN_64X
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_SetDPGAGain(eGain)              WRITE_FIELD( PGA->DPGACTL, DPGACTL_GAIN_Msk, DPGACTL_GAIN_Pos, eGain )




/******************************************************************************
 * @brief      Enable DPGA positive input pull-up
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_EnablePositiveInputPullup()     (PGA->DPGACTL |= DPGACTL_PUIP_ENABLE)




/******************************************************************************
 * @brief      Disable DPGA positive input pull-up
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_DisablePositiveInputPullup()    (PGA->DPGACTL &= ~DPGACTL_PUIP_ENABLE)




/******************************************************************************
 * @brief      Enable DPGA negative input pull-up
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_EnableNegativeInputPullup()     (PGA->DPGACTL |= DPGACTL_PUIN_ENABLE)




/******************************************************************************
 * @brief      Disable DPGA positive input pull-up
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_DisableNegativeInputPullup()    (PGA->DPGACTL &= ~DPGACTL_PUIN_ENABLE)




/******************************************************************************
 * @brief      Enable SPGA
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_EnableSPGA()                    (PGA->SPGACTL |= SPGACTL_EN_ENABLE)




/******************************************************************************
 * @brief      Disable SPGA
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_DisableSPGA()                   (PGA->SPGACTL &= ~SPGACTL_EN_ENABLE)




/******************************************************************************
 * @brief      Set SPGA input
 *
 * @param[in]  eInput:  Input selection, defined by PGA_InputSelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_SetSPGAInput(eInput)            WRITE_FIELD( PGA->SPGACTL, SPGACTL_INSEL_Msk, SPGACTL_INSEL_Pos, eInput )




/******************************************************************************
 * @brief      Set SPGA gain
 *
 * @param[in]  eGain:  Gain option, defined by PGA_GainEnum
 *                     \ref - SPGA_GAIN_1X ~ DPGA_GAIN_64X
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_SetSPGAGain(eGain)              WRITE_FIELD( PGA->SPGACTL, SPGACTL_GAIN_Msk, SPGACTL_GAIN_Pos, eGain )




/********************************************************************************
 * @brief      Enable Differential to Single-ended Buffer
 *
 * @param[in]  None
 *
 * @return     None
 *
 *******************************************************************************/
#define D2S_Enable()                        (PGA->DPGACTL |= DPGACTL_D2SBUFEN_Msk)




/********************************************************************************
 * @brief      Disable Differential to Single-ended Buffer
 *
 * @param[in]  None
 *
 * @return     None
 *
 *******************************************************************************/
#define D2S_Disable()                       (PGA->DPGACTL &= ~DPGACTL_D2SBUFEN_Msk)




/******************************************************************************
 * @brief      Enable write access to the protected PGA registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_WALLOW()                        (PGA->PGAREGKEY = 0x1ACCE551U)




/******************************************************************************
 * @brief      Disable write access to the protected PGA registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define PGA_WDIS()                          (PGA->PGAREGKEY = 0x0U)




/**
 *  @brief  PGA Public Function Declaration
 */
void PGA_InitDPGA(PGA_GainEnum eGain);
void PGA_InitSPGA(PGA_InputSelEnum eInput, PGA_GainEnum eGain);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* PGA_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
