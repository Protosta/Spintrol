/******************************************************************************
 * @file     power.h
 * @brief    POWER driver header file.
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


#ifndef POWER_H
#define POWER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  BOD VDD33 over-voltage threshold definitions
 */
typedef enum
{
    BOD_VDD33OV_3dot66_V      = 3,    /*!< 3.66V     */
    BOD_VDD33OV_3dot79_V      = 4,    /*!< 3.79V     */
    BOD_VDD33OV_3dot93_V      = 5,    /*!< 3.93V     */
    BOD_VDD33OV_4dot08_V      = 6,    /*!< 4.08V     */
    BOD_VDD33OV_4dot24_V      = 7,    /*!< 4.24V     */
} POWER_VDD33OVEnum;




/**
 *  @brief  BOD VDD33 under-voltage threshold definitions
 */
typedef enum
{
    BOD_VDD33UV_2dot86_V      = 4,    /*!< 2.86V     */
    BOD_VDD33UV_2dot94_V      = 5,    /*!< 2.94V     */
    BOD_VDD33UV_3dot03_V      = 6,    /*!< 3.03V     */
} POWER_VDD33UVEnum;




/**
 *  @brief  BOD VDD12 over-voltage threshold definitions
 */
typedef enum
{
    BOD_VDD12OV_1dot36_V      = 2,    /*!< 1.36V     */
    BOD_VDD12OV_1dot38_V      = 3,    /*!< 1.38V     */
    BOD_VDD12OV_1dot41_V      = 4,    /*!< 1.41V     */
    BOD_VDD12OV_1dot43_V      = 5,    /*!< 1.43V     */
    BOD_VDD12OV_1dot46_V      = 6,    /*!< 1.46V     */
    BOD_VDD12OV_1dot49_V      = 7,    /*!< 1.49V     */
} POWER_VDD12OVEnum;




/**
 *  @brief  BOD VDD12 under-voltage threshold definitions
 */
typedef enum
{
    BOD_VDD12UV_0dot94_V      = 0,    /*!< 0.94V     */
    BOD_VDD12UV_0dot97_V      = 1,    /*!< 0.97V     */
    BOD_VDD12UV_0dot99_V      = 2,    /*!< 0.99V     */
    BOD_VDD12UV_1dot02_V      = 3,    /*!< 1.02V     */
    BOD_VDD12UV_1dot04_V      = 4,    /*!< 1.04V     */
    BOD_VDD12UV_1dot07_V      = 5,    /*!< 1.07V     */
} POWER_VDD12UVEnum;




/******************************************************************************
 * @brief      Enable write access to the protected POWER registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define POWER_WALLOW()                      (POWER->PWRREGKEY = 0x1ACCE551)




/******************************************************************************
 * @brief      Disable write access to the protected POWER registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define POWER_WDIS()                        (POWER->PWRREGKEY = 0x0)




/**
 *  @brief Power Public Function Declaration
 */
void POWER_SetVDD12UVThreshold(POWER_VDD12UVEnum eAssert, POWER_VDD12UVEnum eDeassert);
void POWER_SetVDD12OVThreshold(POWER_VDD12OVEnum eAssert, POWER_VDD12OVEnum eDeassert);

void POWER_SetVDD33UVThreshold(POWER_VDD33UVEnum eAssert, POWER_VDD33UVEnum eDeassert);
void POWER_SetVDD33OVThreshold(POWER_VDD33OVEnum eAssert, POWER_VDD33OVEnum eDeassert);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* POWER_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
