/******************************************************************************
 * @file     system.c
 * @brief    POWER firmware functions.
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

#include "power.h"


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/******************************************************************************
 * @brief      Set VDD12UV threshold voltage
 *
 * @param[in]  eAssert  :  Select the threshold to assert the VDD12UV event
 *             eDeassert:  Select the threshold to de-assert the VDD12UV event
 *                         Please refer to POWER_VDD12UVEnum
 *
 * @return     none
 *
 ******************************************************************************/
void POWER_SetVDD12UVThreshold(POWER_VDD12UVEnum eAssert, POWER_VDD12UVEnum eDeassert)
{
    /* It should be merged into one assignment as below */
    POWER->BOD12CTL = (POWER->BOD12CTL & ~(BOD12CTL_UVASVTH_Msk | BOD12CTL_UVDEVTH_Msk))
                    | ((eAssert) << BOD12CTL_UVASVTH_Pos)
                    | ((eDeassert) << BOD12CTL_UVDEVTH_Pos);
}




/******************************************************************************
 * @brief      Set VDD12OV threshold voltage
 *
 * @param[in]  eAssert  :  Select the threshold to assert the VDD12OV event
 *             eDeassert:  Select the threshold to de-assert the VDD12OV event
 *                         Please refer to POWER_VDD12OVEnum
 *
 * @return     none
 *
 ******************************************************************************/
void POWER_SetVDD12OVThreshold(POWER_VDD12OVEnum eAssert, POWER_VDD12OVEnum eDeassert)
{
    /* It should be merged into one assignment as below */
    POWER->BOD12CTL = (POWER->BOD12CTL & ~(BOD12CTL_OVASVTH_Msk | BOD12CTL_OVDEVTH_Msk))
                    | ((eAssert) << BOD12CTL_OVASVTH_Pos)
                    | ((eDeassert) << BOD12CTL_OVDEVTH_Pos);
}




/******************************************************************************
 * @brief      Set VDD33UV threshold voltage
 *
 * @param[in]  eAssert  :  Select the threshold to assert the VDD33UV event
 *             eDeassert:  Select the threshold to de-assert the VDD33UV event
 *                         Please refer to POWER_VDD33UVEnum
 *
 * @return     none
 *
 ******************************************************************************/
void POWER_SetVDD33UVThreshold(POWER_VDD33UVEnum eAssert, POWER_VDD33UVEnum eDeassert)
{
    /* It should be merged into one assignment as below */
    POWER->BOD33CTL = (POWER->BOD33CTL & ~(BOD33CTL_UVASVTH_Msk | BOD33CTL_UVDEVTH_Msk))
                    | ((eAssert) << BOD33CTL_UVASVTH_Pos)
                    | ((eDeassert) << BOD33CTL_UVDEVTH_Pos);
}




/******************************************************************************
 * @brief      Set VDD33OV threshold voltage
 *
 * @param[in]  eAssert  :  Select the threshold to assert the VDD33OV event
 *             eDeassert:  Select the threshold to de-assert the VDD33OV event
 *                         Please refer to POWER_VDD33OVEnum
 *
 * @return     none
 *
 ******************************************************************************/
void POWER_SetVDD33OVThreshold(POWER_VDD33OVEnum eAssert, POWER_VDD33OVEnum eDeassert)
{
    /* It should be merged into one assignment as below */
    POWER->BOD33CTL = (POWER->BOD33CTL & ~(BOD33CTL_OVASVTH_Msk | BOD33CTL_OVDEVTH_Msk))
                    | ((eAssert) << BOD33CTL_OVASVTH_Pos)
                    | ((eDeassert) << BOD33CTL_OVDEVTH_Pos);
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
