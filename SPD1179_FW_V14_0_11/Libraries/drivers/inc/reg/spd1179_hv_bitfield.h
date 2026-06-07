/*************************************************************************
 * @file     hv_bitfield.h
 * @brief    High voltage module register bit-field definition
 * @version  V14.0.11
 * @date     30-March-2026
 *
 * @note
 * Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd.. All rights reserved.
 *
 * @attention
 * THIS SOFTWARE JUST PROVIDES CUSTOMERS WITH CODING INFORMATION
 * REGARDING THEIR PRODUCTS, WHICH AIMS AT SAVING TIME FOR THEM.
 * SPINTROL SHALL NOT BE LIABLE FOR THE USE OF THE SOFTWARE. SPINTROL
 * DOES NOT GUARANTEE THE CORRECTNESS OF THIS SOFTWARE AND RESERVES THE
 * RIGHT TO MODIFY THE SOFTWARE WITHOUT NOTIFICATION.
 *
 ************************************************************************/


#ifndef HV_BITFIELD_H
#define HV_BITFIELD_H

#ifdef __cplusplus
extern "C" {
#endif



/********************************************************************************
*
* Module Name     HV
*
*
********************************************************************************/



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PINPMURST
 *  @access     HV->SYSEVTFLG
 *  @brief      XRSTn pin triggered PMU reset event flag
 */
#define SYSEVTFLG_PINPMURST_Pos (0UL)
#define SYSEVTFLG_PINPMURST_Msk (0x1UL << SYSEVTFLG_PINPMURST_Pos)

#define SYSEVTFLG_PINPMURST_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PINPMURST_Pos)
#define SYSEVTFLG_PINPMURST_OCCUR             ((0x1UL) << SYSEVTFLG_PINPMURST_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PINFUNCRST
 *  @access     HV->SYSEVTFLG
 *  @brief      XRSTn pin triggered function reset event flag
 */
#define SYSEVTFLG_PINFUNCRST_Pos (1UL)
#define SYSEVTFLG_PINFUNCRST_Msk (0x1UL << SYSEVTFLG_PINFUNCRST_Pos)

#define SYSEVTFLG_PINFUNCRST_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PINFUNCRST_Pos)
#define SYSEVTFLG_PINFUNCRST_OCCUR             ((0x1UL) << SYSEVTFLG_PINFUNCRST_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PMUWDTRST
 *  @access     HV->SYSEVTFLG
 *  @brief      PMU watchdog reset event flag
 */
#define SYSEVTFLG_PMUWDTRST_Pos (2UL)
#define SYSEVTFLG_PMUWDTRST_Msk (0x1UL << SYSEVTFLG_PMUWDTRST_Pos)

#define SYSEVTFLG_PMUWDTRST_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PMUWDTRST_Pos)
#define SYSEVTFLG_PMUWDTRST_OCCUR             ((0x1UL) << SYSEVTFLG_PMUWDTRST_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PMUTIMEOUT
 *  @access     HV->SYSEVTFLG
 *  @brief      PMU timeout evet flag
 *              It is asserted if the VDD5/VDD3 failed to be fully established within the predefined
 *              time  (typical 2ms)
 */
#define SYSEVTFLG_PMUTIMEOUT_Pos (3UL)
#define SYSEVTFLG_PMUTIMEOUT_Msk (0x1UL << SYSEVTFLG_PMUTIMEOUT_Pos)

#define SYSEVTFLG_PMUTIMEOUT_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PMUTIMEOUT_Pos)
#define SYSEVTFLG_PMUTIMEOUT_OCCUR             ((0x1UL) << SYSEVTFLG_PMUTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       VDD5EXTOCFAIL
 *  @access     HV->SYSEVTFLG
 *  @brief      VDD5EXT over-current failure event flag
 *              It is asserted if the condition is detected during power-up or last for more than
 *              320us and make the VDD5EXT self-shutdown
 */
#define SYSEVTFLG_VDD5EXTOCFAIL_Pos (4UL)
#define SYSEVTFLG_VDD5EXTOCFAIL_Msk (0x1UL << SYSEVTFLG_VDD5EXTOCFAIL_Pos)

#define SYSEVTFLG_VDD5EXTOCFAIL_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_VDD5EXTOCFAIL_Pos)
#define SYSEVTFLG_VDD5EXTOCFAIL_OCCUR             ((0x1UL) << SYSEVTFLG_VDD5EXTOCFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       VDD5OCFAIL
 *  @access     HV->SYSEVTFLG
 *  @brief      VDD5 over-current failure event flag
 *              It is asserted if the condition is detected during power-up or last for more than
 *              320us in active state and make the system go to sleep
 */
#define SYSEVTFLG_VDD5OCFAIL_Pos (5UL)
#define SYSEVTFLG_VDD5OCFAIL_Msk (0x1UL << SYSEVTFLG_VDD5OCFAIL_Pos)

#define SYSEVTFLG_VDD5OCFAIL_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_VDD5OCFAIL_Pos)
#define SYSEVTFLG_VDD5OCFAIL_OCCUR             ((0x1UL) << SYSEVTFLG_VDD5OCFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       VDD3OCFAIL
 *  @access     HV->SYSEVTFLG
 *  @brief      VDD3 over-current failure event flag
 *              It is asserted if the condition last for more than 320us and make the system go to
 *              sleep
 */
#define SYSEVTFLG_VDD3OCFAIL_Pos (6UL)
#define SYSEVTFLG_VDD3OCFAIL_Msk (0x1UL << SYSEVTFLG_VDD3OCFAIL_Pos)

#define SYSEVTFLG_VDD3OCFAIL_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_VDD3OCFAIL_Pos)
#define SYSEVTFLG_VDD3OCFAIL_OCCUR             ((0x1UL) << SYSEVTFLG_VDD3OCFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PMUONFAIL
 *  @access     HV->SYSEVTFLG
 *  @brief      PMU power on failure event flag
 *              It is asserted if VDD5/VDD3 over-current or timeout for 5 times and make the system
 *              go to sleep
 */
#define SYSEVTFLG_PMUONFAIL_Pos (7UL)
#define SYSEVTFLG_PMUONFAIL_Msk (0x1UL << SYSEVTFLG_PMUONFAIL_Pos)

#define SYSEVTFLG_PMUONFAIL_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PMUONFAIL_Pos)
#define SYSEVTFLG_PMUONFAIL_OCCUR             ((0x1UL) << SYSEVTFLG_PMUONFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PMUWDTFAIL
 *  @access     HV->SYSEVTFLG
 *  @brief      PMU WDT failure event flag
 *              It is asserted if PMU watchdog reset happnes for 5 times and make the system go to
 *              sleep
 */
#define SYSEVTFLG_PMUWDTFAIL_Pos (8UL)
#define SYSEVTFLG_PMUWDTFAIL_Msk (0x1UL << SYSEVTFLG_PMUWDTFAIL_Pos)

#define SYSEVTFLG_PMUWDTFAIL_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PMUWDTFAIL_Pos)
#define SYSEVTFLG_PMUWDTFAIL_OCCUR             ((0x1UL) << SYSEVTFLG_PMUWDTFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       PMUOTFAIL
 *  @access     HV->SYSEVTFLG
 *  @brief      PMU over-temperature fatal failure event flag
 */
#define SYSEVTFLG_PMUOTFAIL_Pos (9UL)
#define SYSEVTFLG_PMUOTFAIL_Msk (0x1UL << SYSEVTFLG_PMUOTFAIL_Pos)

#define SYSEVTFLG_PMUOTFAIL_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_PMUOTFAIL_Pos)
#define SYSEVTFLG_PMUOTFAIL_OCCUR             ((0x1UL) << SYSEVTFLG_PMUOTFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       SLEEPCMD
 *  @access     HV->SYSEVTFLG
 *  @brief      Sleep command received event flag
 */
#define SYSEVTFLG_SLEEPCMD_Pos (10UL)
#define SYSEVTFLG_SLEEPCMD_Msk (0x1UL << SYSEVTFLG_SLEEPCMD_Pos)

#define SYSEVTFLG_SLEEPCMD_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_SLEEPCMD_Pos)
#define SYSEVTFLG_SLEEPCMD_OCCUR             ((0x1UL) << SYSEVTFLG_SLEEPCMD_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       STOPCMD
 *  @access     HV->SYSEVTFLG
 *  @brief      Stop command received event flag
 */
#define SYSEVTFLG_STOPCMD_Pos (11UL)
#define SYSEVTFLG_STOPCMD_Msk (0x1UL << SYSEVTFLG_STOPCMD_Pos)

#define SYSEVTFLG_STOPCMD_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_STOPCMD_Pos)
#define SYSEVTFLG_STOPCMD_OCCUR             ((0x1UL) << SYSEVTFLG_STOPCMD_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       CYCSENWKUP
 *  @access     HV->SYSEVTFLG
 *  @brief      Cyclic sense GPIO wakeup event flag
 */
#define SYSEVTFLG_CYCSENWKUP_Pos (12UL)
#define SYSEVTFLG_CYCSENWKUP_Msk (0x1UL << SYSEVTFLG_CYCSENWKUP_Pos)

#define SYSEVTFLG_CYCSENWKUP_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_CYCSENWKUP_Pos)
#define SYSEVTFLG_CYCSENWKUP_OCCUR             ((0x1UL) << SYSEVTFLG_CYCSENWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       CYCWKUP
 *  @access     HV->SYSEVTFLG
 *  @brief      Cyclic wakeup event flag
 */
#define SYSEVTFLG_CYCWKUP_Pos (13UL)
#define SYSEVTFLG_CYCWKUP_Msk (0x1UL << SYSEVTFLG_CYCWKUP_Pos)

#define SYSEVTFLG_CYCWKUP_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_CYCWKUP_Pos)
#define SYSEVTFLG_CYCWKUP_OCCUR             ((0x1UL) << SYSEVTFLG_CYCWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       MONWKUP
 *  @access     HV->SYSEVTFLG
 *  @brief      MON wake up event flag
 */
#define SYSEVTFLG_MONWKUP_Pos (14UL)
#define SYSEVTFLG_MONWKUP_Msk (0x1UL << SYSEVTFLG_MONWKUP_Pos)

#define SYSEVTFLG_MONWKUP_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_MONWKUP_Pos)
#define SYSEVTFLG_MONWKUP_OCCUR             ((0x1UL) << SYSEVTFLG_MONWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLG       LINWKUP
 *  @access     HV->SYSEVTFLG
 *  @brief      Lin wake up event flag
 */
#define SYSEVTFLG_LINWKUP_Pos (15UL)
#define SYSEVTFLG_LINWKUP_Msk (0x1UL << SYSEVTFLG_LINWKUP_Pos)

#define SYSEVTFLG_LINWKUP_NOT_OCCUR         ((0x0UL) << SYSEVTFLG_LINWKUP_Pos)
#define SYSEVTFLG_LINWKUP_OCCUR             ((0x1UL) << SYSEVTFLG_LINWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PINPMURST
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      XRSTn pin triggered PMU reset event flag clear
 */
#define SYSEVTFLGCLR_PINPMURST_Pos (0UL)
#define SYSEVTFLGCLR_PINPMURST_Msk (0x1UL << SYSEVTFLGCLR_PINPMURST_Pos)

#define SYSEVTFLGCLR_PINPMURST_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PINPMURST_Pos)
#define SYSEVTFLGCLR_PINPMURST_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PINPMURST_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PINFUNCRST
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      XRSTn pin triggered function reset event flag clear
 */
#define SYSEVTFLGCLR_PINFUNCRST_Pos (1UL)
#define SYSEVTFLGCLR_PINFUNCRST_Msk (0x1UL << SYSEVTFLGCLR_PINFUNCRST_Pos)

#define SYSEVTFLGCLR_PINFUNCRST_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PINFUNCRST_Pos)
#define SYSEVTFLGCLR_PINFUNCRST_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PINFUNCRST_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PMUWDTRST
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      PMU watchdog reset event flag clear
 */
#define SYSEVTFLGCLR_PMUWDTRST_Pos (2UL)
#define SYSEVTFLGCLR_PMUWDTRST_Msk (0x1UL << SYSEVTFLGCLR_PMUWDTRST_Pos)

#define SYSEVTFLGCLR_PMUWDTRST_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PMUWDTRST_Pos)
#define SYSEVTFLGCLR_PMUWDTRST_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PMUWDTRST_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PMUTIMEOUT
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      PMU timeout evet flag clear
 */
#define SYSEVTFLGCLR_PMUTIMEOUT_Pos (3UL)
#define SYSEVTFLGCLR_PMUTIMEOUT_Msk (0x1UL << SYSEVTFLGCLR_PMUTIMEOUT_Pos)

#define SYSEVTFLGCLR_PMUTIMEOUT_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PMUTIMEOUT_Pos)
#define SYSEVTFLGCLR_PMUTIMEOUT_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PMUTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    VDD5EXTOCFAIL
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      VDD5EXT over-current event flag clear
 */
#define SYSEVTFLGCLR_VDD5EXTOCFAIL_Pos (4UL)
#define SYSEVTFLGCLR_VDD5EXTOCFAIL_Msk (0x1UL << SYSEVTFLGCLR_VDD5EXTOCFAIL_Pos)

#define SYSEVTFLGCLR_VDD5EXTOCFAIL_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_VDD5EXTOCFAIL_Pos)
#define SYSEVTFLGCLR_VDD5EXTOCFAIL_CLEAR             ((0x1UL) << SYSEVTFLGCLR_VDD5EXTOCFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    VDD5OCFAIL
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      VDD5 over-current event flag clear
 */
#define SYSEVTFLGCLR_VDD5OCFAIL_Pos (5UL)
#define SYSEVTFLGCLR_VDD5OCFAIL_Msk (0x1UL << SYSEVTFLGCLR_VDD5OCFAIL_Pos)

#define SYSEVTFLGCLR_VDD5OCFAIL_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_VDD5OCFAIL_Pos)
#define SYSEVTFLGCLR_VDD5OCFAIL_CLEAR             ((0x1UL) << SYSEVTFLGCLR_VDD5OCFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    VDD3OCFAIL
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      VDD3 over-current event flag clear
 */
#define SYSEVTFLGCLR_VDD3OCFAIL_Pos (6UL)
#define SYSEVTFLGCLR_VDD3OCFAIL_Msk (0x1UL << SYSEVTFLGCLR_VDD3OCFAIL_Pos)

#define SYSEVTFLGCLR_VDD3OCFAIL_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_VDD3OCFAIL_Pos)
#define SYSEVTFLGCLR_VDD3OCFAIL_CLEAR             ((0x1UL) << SYSEVTFLGCLR_VDD3OCFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PMULDOFAIL
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      PMU LDO failure event flag clear
 */
#define SYSEVTFLGCLR_PMULDOFAIL_Pos (7UL)
#define SYSEVTFLGCLR_PMULDOFAIL_Msk (0x1UL << SYSEVTFLGCLR_PMULDOFAIL_Pos)

#define SYSEVTFLGCLR_PMULDOFAIL_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PMULDOFAIL_Pos)
#define SYSEVTFLGCLR_PMULDOFAIL_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PMULDOFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PMUWDTFAIL
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      PMU WDT failure event flag clear
 */
#define SYSEVTFLGCLR_PMUWDTFAIL_Pos (8UL)
#define SYSEVTFLGCLR_PMUWDTFAIL_Msk (0x1UL << SYSEVTFLGCLR_PMUWDTFAIL_Pos)

#define SYSEVTFLGCLR_PMUWDTFAIL_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PMUWDTFAIL_Pos)
#define SYSEVTFLGCLR_PMUWDTFAIL_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PMUWDTFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    PMUOTFAIL
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      PMU over-temperature fatal failure event flag clear
 */
#define SYSEVTFLGCLR_PMUOTFAIL_Pos (9UL)
#define SYSEVTFLGCLR_PMUOTFAIL_Msk (0x1UL << SYSEVTFLGCLR_PMUOTFAIL_Pos)

#define SYSEVTFLGCLR_PMUOTFAIL_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_PMUOTFAIL_Pos)
#define SYSEVTFLGCLR_PMUOTFAIL_CLEAR             ((0x1UL) << SYSEVTFLGCLR_PMUOTFAIL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    SLEEPCMD
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      Sleep command received event flag clear
 */
#define SYSEVTFLGCLR_SLEEPCMD_Pos (10UL)
#define SYSEVTFLGCLR_SLEEPCMD_Msk (0x1UL << SYSEVTFLGCLR_SLEEPCMD_Pos)

#define SYSEVTFLGCLR_SLEEPCMD_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_SLEEPCMD_Pos)
#define SYSEVTFLGCLR_SLEEPCMD_CLEAR             ((0x1UL) << SYSEVTFLGCLR_SLEEPCMD_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    STOPCMD
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      Stop command received event flag clear
 */
#define SYSEVTFLGCLR_STOPCMD_Pos (11UL)
#define SYSEVTFLGCLR_STOPCMD_Msk (0x1UL << SYSEVTFLGCLR_STOPCMD_Pos)

#define SYSEVTFLGCLR_STOPCMD_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_STOPCMD_Pos)
#define SYSEVTFLGCLR_STOPCMD_CLEAR             ((0x1UL) << SYSEVTFLGCLR_STOPCMD_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    CYCSENWKUP
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      Cyclic sense GPIO wakeup event flag clear
 */
#define SYSEVTFLGCLR_CYCSENWKUP_Pos (12UL)
#define SYSEVTFLGCLR_CYCSENWKUP_Msk (0x1UL << SYSEVTFLGCLR_CYCSENWKUP_Pos)

#define SYSEVTFLGCLR_CYCSENWKUP_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_CYCSENWKUP_Pos)
#define SYSEVTFLGCLR_CYCSENWKUP_CLEAR             ((0x1UL) << SYSEVTFLGCLR_CYCSENWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    CYCWKUP
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      Cyclic wakeup event flag clear
 */
#define SYSEVTFLGCLR_CYCWKUP_Pos (13UL)
#define SYSEVTFLGCLR_CYCWKUP_Msk (0x1UL << SYSEVTFLGCLR_CYCWKUP_Pos)

#define SYSEVTFLGCLR_CYCWKUP_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_CYCWKUP_Pos)
#define SYSEVTFLGCLR_CYCWKUP_CLEAR             ((0x1UL) << SYSEVTFLGCLR_CYCWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    MONWKUP
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      MON wake up event flag clear
 */
#define SYSEVTFLGCLR_MONWKUP_Pos (14UL)
#define SYSEVTFLGCLR_MONWKUP_Msk (0x1UL << SYSEVTFLGCLR_MONWKUP_Pos)

#define SYSEVTFLGCLR_MONWKUP_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_MONWKUP_Pos)
#define SYSEVTFLGCLR_MONWKUP_CLEAR             ((0x1UL) << SYSEVTFLGCLR_MONWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              SYSEVTFLGCLR    LINWKUP
 *  @access     HV->SYSEVTFLGCLR
 *  @brief      Lin wake up event flag clear
 */
#define SYSEVTFLGCLR_LINWKUP_Pos (15UL)
#define SYSEVTFLGCLR_LINWKUP_Msk (0x1UL << SYSEVTFLGCLR_LINWKUP_Pos)

#define SYSEVTFLGCLR_LINWKUP_NO_EFFECT         ((0x0UL) << SYSEVTFLGCLR_LINWKUP_Pos)
#define SYSEVTFLGCLR_LINWKUP_CLEAR             ((0x1UL) << SYSEVTFLGCLR_LINWKUP_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          VDD5LPLVL
 *  @access     HV->PMUCTL
 *  @brief      VDD5 level in low-power stop mode
 */
#define PMUCTL_VDD5LPLVL_Pos (0UL)
#define PMUCTL_VDD5LPLVL_Msk (0x3UL << PMUCTL_VDD5LPLVL_Pos)

#define PMUCTL_VDD5LPLVL_4P24V         ((0x0UL) << PMUCTL_VDD5LPLVL_Pos)
#define PMUCTL_VDD5LPLVL_4P45V         ((0x1UL) << PMUCTL_VDD5LPLVL_Pos)
#define PMUCTL_VDD5LPLVL_4P70V         ((0x2UL) << PMUCTL_VDD5LPLVL_Pos)
#define PMUCTL_VDD5LPLVL_5P00V         ((0x3UL) << PMUCTL_VDD5LPLVL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          VDD3LPLVL
 *  @access     HV->PMUCTL
 *  @brief      VDD3 level in low-power stop mode
 */
#define PMUCTL_VDD3LPLVL_Pos (2UL)
#define PMUCTL_VDD3LPLVL_Msk (0x3UL << PMUCTL_VDD3LPLVL_Pos)

#define PMUCTL_VDD3LPLVL_2P77V         ((0x0UL) << PMUCTL_VDD3LPLVL_Pos)
#define PMUCTL_VDD3LPLVL_2P88V         ((0x1UL) << PMUCTL_VDD3LPLVL_Pos)
#define PMUCTL_VDD3LPLVL_3P00V         ((0x2UL) << PMUCTL_VDD3LPLVL_Pos)
#define PMUCTL_VDD3LPLVL_3P30V         ((0x3UL) << PMUCTL_VDD3LPLVL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          XRSTDGWIN
 *  @access     HV->PMUCTL
 *  @brief      XRSTn pin deglitch filtering window
 */
#define PMUCTL_XRSTDGWIN_Pos (4UL)
#define PMUCTL_XRSTDGWIN_Msk (0x7UL << PMUCTL_XRSTDGWIN_Pos)

#define PMUCTL_XRSTDGWIN_4P2US           ((0x0UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_97US            ((0x1UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_394US           ((0x2UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_1P58MS          ((0x3UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_3P17MS          ((0x4UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_6P34MS          ((0x5UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_25P68MS         ((0x6UL) << PMUCTL_XRSTDGWIN_Pos)
#define PMUCTL_XRSTDGWIN_102P7MS         ((0x7UL) << PMUCTL_XRSTDGWIN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          LPRCOAON
 *  @access     HV->PMUCTL
 *  @brief      Force LPRCO to be always-on even in stop and sleep mode
 */
#define PMUCTL_LPRCOAON_Pos (7UL)
#define PMUCTL_LPRCOAON_Msk (0x1UL << PMUCTL_LPRCOAON_Pos)

#define PMUCTL_LPRCOAON_DISABLE         ((0x0UL) << PMUCTL_LPRCOAON_Pos)
#define PMUCTL_LPRCOAON_ENABLE          ((0x1UL) << PMUCTL_LPRCOAON_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          VDD5EXTEN
 *  @access     HV->PMUCTL
 *  @brief      VDD5EXT enable
 */
#define PMUCTL_VDD5EXTEN_Pos (8UL)
#define PMUCTL_VDD5EXTEN_Msk (0x1UL << PMUCTL_VDD5EXTEN_Pos)

#define PMUCTL_VDD5EXTEN_DISABLE         ((0x0UL) << PMUCTL_VDD5EXTEN_Pos)
#define PMUCTL_VDD5EXTEN_ENABLE          ((0x1UL) << PMUCTL_VDD5EXTEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          VDD5EXTPROTEN
 *  @access     HV->PMUCTL
 *  @brief      VDD5EXT protect enable to shut down VDD5EXT upon over-current for more than 320us
 *              or under-voltage (regarded as short)
 */
#define PMUCTL_VDD5EXTPROTEN_Pos (9UL)
#define PMUCTL_VDD5EXTPROTEN_Msk (0x1UL << PMUCTL_VDD5EXTPROTEN_Pos)

#define PMUCTL_VDD5EXTPROTEN_DISABLE         ((0x0UL) << PMUCTL_VDD5EXTPROTEN_Pos)
#define PMUCTL_VDD5EXTPROTEN_ENABLE          ((0x1UL) << PMUCTL_VDD5EXTPROTEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          PMUWDTEN
 *  @access     HV->PMUCTL
 *  @brief      PMU watchdog enable
 */
#define PMUCTL_PMUWDTEN_Pos (10UL)
#define PMUCTL_PMUWDTEN_Msk (0x1UL << PMUCTL_PMUWDTEN_Pos)

#define PMUCTL_PMUWDTEN_DISABLE         ((0x0UL) << PMUCTL_PMUWDTEN_Pos)
#define PMUCTL_PMUWDTEN_ENABLE          ((0x1UL) << PMUCTL_PMUWDTEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          CYCSENWKUPEN
 *  @access     HV->PMUCTL
 *  @brief      Cyclic sense GPIO (including MON) wakeup enable
 *              Note: Once MONWKUPEN=1, MON pin cannot be used for cyclic sense wakeup, but only
 *              for asynchronous MON wakeup
 */
#define PMUCTL_CYCSENWKUPEN_Pos (12UL)
#define PMUCTL_CYCSENWKUPEN_Msk (0x1UL << PMUCTL_CYCSENWKUPEN_Pos)

#define PMUCTL_CYCSENWKUPEN_DISABLE         ((0x0UL) << PMUCTL_CYCSENWKUPEN_Pos)
#define PMUCTL_CYCSENWKUPEN_ENABLE          ((0x1UL) << PMUCTL_CYCSENWKUPEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          CYCWKUPEN
 *  @access     HV->PMUCTL
 *  @brief      Cyclic wakeup enable
 *              This bit is automatically set to 1 if both LINWKUPEN & MONWKUPEN bits are 0
 */
#define PMUCTL_CYCWKUPEN_Pos (13UL)
#define PMUCTL_CYCWKUPEN_Msk (0x1UL << PMUCTL_CYCWKUPEN_Pos)

#define PMUCTL_CYCWKUPEN_DISABLE         ((0x0UL) << PMUCTL_CYCWKUPEN_Pos)
#define PMUCTL_CYCWKUPEN_ENABLE          ((0x1UL) << PMUCTL_CYCWKUPEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          MONWKUPEN
 *  @access     HV->PMUCTL
 *  @brief      MON wakeup enable
 *              Note: Write 1 to this bit will also write 1 to EN bit in MONCTL
 */
#define PMUCTL_MONWKUPEN_Pos (14UL)
#define PMUCTL_MONWKUPEN_Msk (0x1UL << PMUCTL_MONWKUPEN_Pos)

#define PMUCTL_MONWKUPEN_DISABLE         ((0x0UL) << PMUCTL_MONWKUPEN_Pos)
#define PMUCTL_MONWKUPEN_ENABLE          ((0x1UL) << PMUCTL_MONWKUPEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUCTL          LINWKUPEN
 *  @access     HV->PMUCTL
 *  @brief      LIN wakeup enable
 */
#define PMUCTL_LINWKUPEN_Pos (15UL)
#define PMUCTL_LINWKUPEN_Msk (0x1UL << PMUCTL_LINWKUPEN_Pos)

#define PMUCTL_LINWKUPEN_DISABLE         ((0x0UL) << PMUCTL_LINWKUPEN_Pos)
#define PMUCTL_LINWKUPEN_ENABLE          ((0x1UL) << PMUCTL_LINWKUPEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          CURSTATE
 *  @access     HV->PMUSTS
 *  @brief      Current state
 */
#define PMUSTS_CURSTATE_Pos (0UL)
#define PMUSTS_CURSTATE_Msk (0x3UL << PMUSTS_CURSTATE_Pos)

#define PMUSTS_CURSTATE_STARTUP         ((0x0UL) << PMUSTS_CURSTATE_Pos)
#define PMUSTS_CURSTATE_SLEEP           ((0x1UL) << PMUSTS_CURSTATE_Pos)
#define PMUSTS_CURSTATE_STOP            ((0x2UL) << PMUSTS_CURSTATE_Pos)
#define PMUSTS_CURSTATE_ACTIVE          ((0x3UL) << PMUSTS_CURSTATE_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          PRESTATE1
 *  @access     HV->PMUSTS
 *  @brief      Last state
 */
#define PMUSTS_PRESTATE1_Pos (2UL)
#define PMUSTS_PRESTATE1_Msk (0x3UL << PMUSTS_PRESTATE1_Pos)

#define PMUSTS_PRESTATE1_STARTUP         ((0x0UL) << PMUSTS_PRESTATE1_Pos)
#define PMUSTS_PRESTATE1_SLEEP           ((0x1UL) << PMUSTS_PRESTATE1_Pos)
#define PMUSTS_PRESTATE1_STOP            ((0x2UL) << PMUSTS_PRESTATE1_Pos)
#define PMUSTS_PRESTATE1_ACTIVE          ((0x3UL) << PMUSTS_PRESTATE1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          PRESTATE2
 *  @access     HV->PMUSTS
 *  @brief      The state before the last
 */
#define PMUSTS_PRESTATE2_Pos (4UL)
#define PMUSTS_PRESTATE2_Msk (0x3UL << PMUSTS_PRESTATE2_Pos)

#define PMUSTS_PRESTATE2_STARTUP         ((0x0UL) << PMUSTS_PRESTATE2_Pos)
#define PMUSTS_PRESTATE2_SLEEP           ((0x1UL) << PMUSTS_PRESTATE2_Pos)
#define PMUSTS_PRESTATE2_STOP            ((0x2UL) << PMUSTS_PRESTATE2_Pos)
#define PMUSTS_PRESTATE2_ACTIVE          ((0x3UL) << PMUSTS_PRESTATE2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          LPPMURDY
 *  @access     HV->PMUSTS
 *  @brief      Low-power PMU ready
 */
#define PMUSTS_LPPMURDY_Pos (6UL)
#define PMUSTS_LPPMURDY_Msk (0x1UL << PMUSTS_LPPMURDY_Pos)

#define PMUSTS_LPPMURDY_NOT_READY         ((0x0UL) << PMUSTS_LPPMURDY_Pos)
#define PMUSTS_LPPMURDY_READY             ((0x1UL) << PMUSTS_LPPMURDY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          HPPMURDY
 *  @access     HV->PMUSTS
 *  @brief      High-power PMU ready
 */
#define PMUSTS_HPPMURDY_Pos (7UL)
#define PMUSTS_HPPMURDY_Msk (0x1UL << PMUSTS_HPPMURDY_Pos)

#define PMUSTS_HPPMURDY_NOT_READY         ((0x0UL) << PMUSTS_HPPMURDY_Pos)
#define PMUSTS_HPPMURDY_READY             ((0x1UL) << PMUSTS_HPPMURDY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          VDD5EXTRDY
 *  @access     HV->PMUSTS
 *  @brief      VDD5EXT ready
 */
#define PMUSTS_VDD5EXTRDY_Pos (8UL)
#define PMUSTS_VDD5EXTRDY_Msk (0x1UL << PMUSTS_VDD5EXTRDY_Pos)

#define PMUSTS_VDD5EXTRDY_NOT_READY         ((0x0UL) << PMUSTS_VDD5EXTRDY_Pos)
#define PMUSTS_VDD5EXTRDY_READY             ((0x1UL) << PMUSTS_VDD5EXTRDY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PMUSTS          CPRDY
 *  @access     HV->PMUSTS
 *  @brief      Pre-driver charge-pump ready
 */
#define PMUSTS_CPRDY_Pos (9UL)
#define PMUSTS_CPRDY_Msk (0x1UL << PMUSTS_CPRDY_Pos)

#define PMUSTS_CPRDY_NOT_READY         ((0x0UL) << PMUSTS_CPRDY_Pos)
#define PMUSTS_CPRDY_READY             ((0x1UL) << PMUSTS_CPRDY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              CYCSENSECTL     DEADCNT
 *  @access     HV->CYCSENSECTL
 *  @brief      Dead time is (DEADCNT+1) * 2ms
 */
#define CYCSENSECTL_DEADCNT_Pos (0UL)
#define CYCSENSECTL_DEADCNT_Msk (0x3FFUL << CYCSENSECTL_DEADCNT_Pos)

#define CYCSENSECTL_DEADCNT_(x) ((x) << CYCSENSECTL_DEADCNT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              CYCSENSECTL     RAMPCNT
 *  @access     HV->CYCSENSECTL
 *  @brief      VDD5EXT power on time after the dead time and before the sense window,  which is
 *              (RAMPCNT+1) * 2ms
 *              This feature is enabled only when the VDD5EXTEN bit in PMUCTL is set as 1 during
 *              stop entry
 */
#define CYCSENSECTL_RAMPCNT_Pos (10UL)
#define CYCSENSECTL_RAMPCNT_Msk (0x3UL << CYCSENSECTL_RAMPCNT_Pos)

#define CYCSENSECTL_RAMPCNT_(x) ((x) << CYCSENSECTL_RAMPCNT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              CYCSENSECTL     SENSECNT
 *  @access     HV->CYCSENSECTL
 *  @brief      Sense window is (SENSECNT+1) * 10us
 */
#define CYCSENSECTL_SENSECNT_Pos (12UL)
#define CYCSENSECTL_SENSECNT_Msk (0xFUL << CYCSENSECTL_SENSECNT_Pos)

#define CYCSENSECTL_SENSECNT_(x) ((x) << CYCSENSECTL_SENSECNT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              CYCWKUPCTL      DEADCNT
 *  @access     HV->CYCWKUPCTL
 *  @brief      Dead time is (DEADCNT+1) * 2ms
 */
#define CYCWKUPCTL_DEADCNT_Pos (0UL)
#define CYCWKUPCTL_DEADCNT_Msk (0x3FFUL << CYCWKUPCTL_DEADCNT_Pos)

#define CYCWKUPCTL_DEADCNT_(x) ((x) << CYCWKUPCTL_DEADCNT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              MONCTL          EN
 *  @access     HV->MONCTL
 *  @brief      MON enable
 *              In sleep mode, this bit is masked as 0 if MON wakeup is disabled.
 *              In stop mode, this bit is masked as 0 if both MON wakeup and cyclic sense wakeup
 *              are disabled.
 */
#define MONCTL_EN_Pos (0UL)
#define MONCTL_EN_Msk (0x1UL << MONCTL_EN_Pos)

#define MONCTL_EN_DISABLE         ((0x0UL) << MONCTL_EN_Pos)
#define MONCTL_EN_ENABLE          ((0x1UL) << MONCTL_EN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              MONCTL          PULLMODE
 *  @access     HV->MONCTL
 *  @brief      MON pin pull mode
 */
#define MONCTL_PULLMODE_Pos (1UL)
#define MONCTL_PULLMODE_Msk (0x3UL << MONCTL_PULLMODE_Pos)

#define MONCTL_PULLMODE_PULL_DISABLE          ((0x0UL) << MONCTL_PULLMODE_Pos)
#define MONCTL_PULLMODE_PULL_DOWN             ((0x1UL) << MONCTL_PULLMODE_Pos)
#define MONCTL_PULLMODE_PULL_UP               ((0x2UL) << MONCTL_PULLMODE_Pos)
#define MONCTL_PULLMODE_PULL_ADAPTIVE         ((0x3UL) << MONCTL_PULLMODE_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              MONCTL          WKUPPOL
 *  @access     HV->MONCTL
 *  @brief      MON pin polarity to trigger the asynchronous MON wakeup
 *              It does not affect the polarity when MON is used for cyclic sense wakeup
 */
#define MONCTL_WKUPPOL_Pos (3UL)
#define MONCTL_WKUPPOL_Msk (0x1UL << MONCTL_WKUPPOL_Pos)

#define MONCTL_WKUPPOL_ACTIVE_LOW          ((0x0UL) << MONCTL_WKUPPOL_Pos)
#define MONCTL_WKUPPOL_ACTIVE_HIGH         ((0x1UL) << MONCTL_WKUPPOL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VBATUV
 *  @access     HV->TZEVTSTS0
 *  @brief      VBAT under-voltage event status (without latch)
 */
#define TZEVTSTS0_VBATUV_Pos (0UL)
#define TZEVTSTS0_VBATUV_Msk (0x1UL << TZEVTSTS0_VBATUV_Pos)

#define TZEVTSTS0_VBATUV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VBATUV_Pos)
#define TZEVTSTS0_VBATUV_OCCUR             ((0x1UL) << TZEVTSTS0_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VBATOV
 *  @access     HV->TZEVTSTS0
 *  @brief      VBAT over-voltage event status (without latch)
 */
#define TZEVTSTS0_VBATOV_Pos (1UL)
#define TZEVTSTS0_VBATOV_Msk (0x1UL << TZEVTSTS0_VBATOV_Pos)

#define TZEVTSTS0_VBATOV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VBATOV_Pos)
#define TZEVTSTS0_VBATOV_OCCUR             ((0x1UL) << TZEVTSTS0_VBATOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD5UV
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD5 under-voltage event status (without latch)
 */
#define TZEVTSTS0_VDD5UV_Pos (2UL)
#define TZEVTSTS0_VDD5UV_Msk (0x1UL << TZEVTSTS0_VDD5UV_Pos)

#define TZEVTSTS0_VDD5UV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD5UV_Pos)
#define TZEVTSTS0_VDD5UV_OCCUR             ((0x1UL) << TZEVTSTS0_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD5OV
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD5 over-voltage event status (without latch)
 */
#define TZEVTSTS0_VDD5OV_Pos (3UL)
#define TZEVTSTS0_VDD5OV_Msk (0x1UL << TZEVTSTS0_VDD5OV_Pos)

#define TZEVTSTS0_VDD5OV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD5OV_Pos)
#define TZEVTSTS0_VDD5OV_OCCUR             ((0x1UL) << TZEVTSTS0_VDD5OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD5EXTUV
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD5EXT under-voltage event status (without latch)
 */
#define TZEVTSTS0_VDD5EXTUV_Pos (4UL)
#define TZEVTSTS0_VDD5EXTUV_Msk (0x1UL << TZEVTSTS0_VDD5EXTUV_Pos)

#define TZEVTSTS0_VDD5EXTUV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD5EXTUV_Pos)
#define TZEVTSTS0_VDD5EXTUV_OCCUR             ((0x1UL) << TZEVTSTS0_VDD5EXTUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD5EXTOV
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD5EXT over-voltage event status (without latch)
 */
#define TZEVTSTS0_VDD5EXTOV_Pos (5UL)
#define TZEVTSTS0_VDD5EXTOV_Msk (0x1UL << TZEVTSTS0_VDD5EXTOV_Pos)

#define TZEVTSTS0_VDD5EXTOV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD5EXTOV_Pos)
#define TZEVTSTS0_VDD5EXTOV_OCCUR             ((0x1UL) << TZEVTSTS0_VDD5EXTOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD3UV
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD3 under-voltage event status (without latch)
 */
#define TZEVTSTS0_VDD3UV_Pos (6UL)
#define TZEVTSTS0_VDD3UV_Msk (0x1UL << TZEVTSTS0_VDD3UV_Pos)

#define TZEVTSTS0_VDD3UV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD3UV_Pos)
#define TZEVTSTS0_VDD3UV_OCCUR             ((0x1UL) << TZEVTSTS0_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD3OV
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD3 over-voltage event status (without latch)
 */
#define TZEVTSTS0_VDD3OV_Pos (7UL)
#define TZEVTSTS0_VDD3OV_Msk (0x1UL << TZEVTSTS0_VDD3OV_Pos)

#define TZEVTSTS0_VDD3OV_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD3OV_Pos)
#define TZEVTSTS0_VDD3OV_OCCUR             ((0x1UL) << TZEVTSTS0_VDD3OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       PMUOTWARN
 *  @access     HV->TZEVTSTS0
 *  @brief      PMU over-temperature warning event status (without latch)
 */
#define TZEVTSTS0_PMUOTWARN_Pos (8UL)
#define TZEVTSTS0_PMUOTWARN_Msk (0x1UL << TZEVTSTS0_PMUOTWARN_Pos)

#define TZEVTSTS0_PMUOTWARN_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_PMUOTWARN_Pos)
#define TZEVTSTS0_PMUOTWARN_OCCUR             ((0x1UL) << TZEVTSTS0_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD5EXTOC
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD5EXT over-current event status (without latch)
 */
#define TZEVTSTS0_VDD5EXTOC_Pos (9UL)
#define TZEVTSTS0_VDD5EXTOC_Msk (0x1UL << TZEVTSTS0_VDD5EXTOC_Pos)

#define TZEVTSTS0_VDD5EXTOC_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD5EXTOC_Pos)
#define TZEVTSTS0_VDD5EXTOC_OCCUR             ((0x1UL) << TZEVTSTS0_VDD5EXTOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD5OC
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD5 over-current event status (without latch)
 */
#define TZEVTSTS0_VDD5OC_Pos (10UL)
#define TZEVTSTS0_VDD5OC_Msk (0x1UL << TZEVTSTS0_VDD5OC_Pos)

#define TZEVTSTS0_VDD5OC_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD5OC_Pos)
#define TZEVTSTS0_VDD5OC_OCCUR             ((0x1UL) << TZEVTSTS0_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       VDD3OC
 *  @access     HV->TZEVTSTS0
 *  @brief      VDD3 over-current event status (without latch)
 */
#define TZEVTSTS0_VDD3OC_Pos (11UL)
#define TZEVTSTS0_VDD3OC_Msk (0x1UL << TZEVTSTS0_VDD3OC_Pos)

#define TZEVTSTS0_VDD3OC_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_VDD3OC_Pos)
#define TZEVTSTS0_VDD3OC_OCCUR             ((0x1UL) << TZEVTSTS0_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       CLKERR
 *  @access     HV->TZEVTSTS0
 *  @brief      Clock error event status (without latch)
 *              This bit is the logic OR of LPRCOERR and RCOERR bits in TZEVTSTS1
 */
#define TZEVTSTS0_CLKERR_Pos (12UL)
#define TZEVTSTS0_CLKERR_Msk (0x1UL << TZEVTSTS0_CLKERR_Pos)

#define TZEVTSTS0_CLKERR_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_CLKERR_Pos)
#define TZEVTSTS0_CLKERR_OCCUR             ((0x1UL) << TZEVTSTS0_CLKERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       LINTXDTIMEOUT
 *  @access     HV->TZEVTSTS0
 *  @brief      LIN TXD timeout event status (without latch)
 *              It is asserted when TXD holds dominant state for over 12ms
 */
#define TZEVTSTS0_LINTXDTIMEOUT_Pos (13UL)
#define TZEVTSTS0_LINTXDTIMEOUT_Msk (0x1UL << TZEVTSTS0_LINTXDTIMEOUT_Pos)

#define TZEVTSTS0_LINTXDTIMEOUT_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_LINTXDTIMEOUT_Pos)
#define TZEVTSTS0_LINTXDTIMEOUT_OCCUR             ((0x1UL) << TZEVTSTS0_LINTXDTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       LINOC
 *  @access     HV->TZEVTSTS0
 *  @brief      LIN transceiver over-current event status (without latch)
 */
#define TZEVTSTS0_LINOC_Pos (14UL)
#define TZEVTSTS0_LINOC_Msk (0x1UL << TZEVTSTS0_LINOC_Pos)

#define TZEVTSTS0_LINOC_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_LINOC_Pos)
#define TZEVTSTS0_LINOC_OCCUR             ((0x1UL) << TZEVTSTS0_LINOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS0       LINOT
 *  @access     HV->TZEVTSTS0
 *  @brief      LIN transceiver over-temperature event status (without latch)
 */
#define TZEVTSTS0_LINOT_Pos (15UL)
#define TZEVTSTS0_LINOT_Msk (0x1UL << TZEVTSTS0_LINOT_Pos)

#define TZEVTSTS0_LINOT_NOT_OCCUR         ((0x0UL) << TZEVTSTS0_LINOT_Pos)
#define TZEVTSTS0_LINOT_OCCUR             ((0x1UL) << TZEVTSTS0_LINOT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       PDRVOCLU
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver U-phase low-side over-current event status (without latch)
 *              It is detected by Vds over-voltage of the external FET
 */
#define TZEVTSTS1_PDRVOCLU_Pos (0UL)
#define TZEVTSTS1_PDRVOCLU_Msk (0x1UL << TZEVTSTS1_PDRVOCLU_Pos)

#define TZEVTSTS1_PDRVOCLU_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_PDRVOCLU_Pos)
#define TZEVTSTS1_PDRVOCLU_OCCUR             ((0x1UL) << TZEVTSTS1_PDRVOCLU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       PDRVOCLV
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver V-phase low-side over-current event status (without latch)
 *              It is detected by Vds over-voltage of the external FET
 */
#define TZEVTSTS1_PDRVOCLV_Pos (1UL)
#define TZEVTSTS1_PDRVOCLV_Msk (0x1UL << TZEVTSTS1_PDRVOCLV_Pos)

#define TZEVTSTS1_PDRVOCLV_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_PDRVOCLV_Pos)
#define TZEVTSTS1_PDRVOCLV_OCCUR             ((0x1UL) << TZEVTSTS1_PDRVOCLV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       PDRVOCLW
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver W-phase low-side over-current event status (without latch)
 *              It is detected by Vds over-voltage of the external FET
 */
#define TZEVTSTS1_PDRVOCLW_Pos (2UL)
#define TZEVTSTS1_PDRVOCLW_Msk (0x1UL << TZEVTSTS1_PDRVOCLW_Pos)

#define TZEVTSTS1_PDRVOCLW_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_PDRVOCLW_Pos)
#define TZEVTSTS1_PDRVOCLW_OCCUR             ((0x1UL) << TZEVTSTS1_PDRVOCLW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       PDRVOCHU
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver U-phase high-side over-current event status (without latch)
 *              It is detected by Vds over-voltage of the external FET
 */
#define TZEVTSTS1_PDRVOCHU_Pos (3UL)
#define TZEVTSTS1_PDRVOCHU_Msk (0x1UL << TZEVTSTS1_PDRVOCHU_Pos)

#define TZEVTSTS1_PDRVOCHU_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_PDRVOCHU_Pos)
#define TZEVTSTS1_PDRVOCHU_OCCUR             ((0x1UL) << TZEVTSTS1_PDRVOCHU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       PDRVOCHV
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver V-phase high-side over-current event status (without latch)
 *              It is detected by Vds over-voltage of the external FET
 */
#define TZEVTSTS1_PDRVOCHV_Pos (4UL)
#define TZEVTSTS1_PDRVOCHV_Msk (0x1UL << TZEVTSTS1_PDRVOCHV_Pos)

#define TZEVTSTS1_PDRVOCHV_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_PDRVOCHV_Pos)
#define TZEVTSTS1_PDRVOCHV_OCCUR             ((0x1UL) << TZEVTSTS1_PDRVOCHV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       PDRVOCHW
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver W-phase high-side over-current event status (without latch)
 *              It is detected by Vds over-voltage of the external FET
 */
#define TZEVTSTS1_PDRVOCHW_Pos (5UL)
#define TZEVTSTS1_PDRVOCHW_Msk (0x1UL << TZEVTSTS1_PDRVOCHW_Pos)

#define TZEVTSTS1_PDRVOCHW_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_PDRVOCHW_Pos)
#define TZEVTSTS1_PDRVOCHW_OCCUR             ((0x1UL) << TZEVTSTS1_PDRVOCHW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       VCPUV
 *  @access     HV->TZEVTSTS1
 *  @brief      Pre-driver VCP under-voltage event status (without latch)
 */
#define TZEVTSTS1_VCPUV_Pos (6UL)
#define TZEVTSTS1_VCPUV_Msk (0x1UL << TZEVTSTS1_VCPUV_Pos)

#define TZEVTSTS1_VCPUV_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_VCPUV_Pos)
#define TZEVTSTS1_VCPUV_OCCUR             ((0x1UL) << TZEVTSTS1_VCPUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       LPRCOERR
 *  @access     HV->TZEVTSTS1
 *  @brief      40MHz RCO error event status (without latch)
 */
#define TZEVTSTS1_LPRCOERR_Pos (8UL)
#define TZEVTSTS1_LPRCOERR_Msk (0x1UL << TZEVTSTS1_LPRCOERR_Pos)

#define TZEVTSTS1_LPRCOERR_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_LPRCOERR_Pos)
#define TZEVTSTS1_LPRCOERR_OCCUR             ((0x1UL) << TZEVTSTS1_LPRCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZEVTSTS1       RCOERR
 *  @access     HV->TZEVTSTS1
 *  @brief      100kHz LPRCO error event status (without latch)
 */
#define TZEVTSTS1_RCOERR_Pos (9UL)
#define TZEVTSTS1_RCOERR_Msk (0x1UL << TZEVTSTS1_RCOERR_Pos)

#define TZEVTSTS1_RCOERR_NOT_OCCUR         ((0x0UL) << TZEVTSTS1_RCOERR_Pos)
#define TZEVTSTS1_RCOERR_OCCUR             ((0x1UL) << TZEVTSTS1_RCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VBATUV
 *  @access     HV->TZIE0
 *  @brief      VBAT under-voltage event interrupt enable
 */
#define TZIE0_VBATUV_Pos (0UL)
#define TZIE0_VBATUV_Msk (0x1UL << TZIE0_VBATUV_Pos)

#define TZIE0_VBATUV_DISABLE         ((0x0UL) << TZIE0_VBATUV_Pos)
#define TZIE0_VBATUV_ENABLE          ((0x1UL) << TZIE0_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VBATOV
 *  @access     HV->TZIE0
 *  @brief      VBAT over-voltage event interrupt enable
 */
#define TZIE0_VBATOV_Pos (1UL)
#define TZIE0_VBATOV_Msk (0x1UL << TZIE0_VBATOV_Pos)

#define TZIE0_VBATOV_DISABLE         ((0x0UL) << TZIE0_VBATOV_Pos)
#define TZIE0_VBATOV_ENABLE          ((0x1UL) << TZIE0_VBATOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD5UV
 *  @access     HV->TZIE0
 *  @brief      VDD5 under-voltage event interrupt enable
 */
#define TZIE0_VDD5UV_Pos (2UL)
#define TZIE0_VDD5UV_Msk (0x1UL << TZIE0_VDD5UV_Pos)

#define TZIE0_VDD5UV_DISABLE         ((0x0UL) << TZIE0_VDD5UV_Pos)
#define TZIE0_VDD5UV_ENABLE          ((0x1UL) << TZIE0_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD5OV
 *  @access     HV->TZIE0
 *  @brief      VDD5 over-voltage event interrupt enable
 */
#define TZIE0_VDD5OV_Pos (3UL)
#define TZIE0_VDD5OV_Msk (0x1UL << TZIE0_VDD5OV_Pos)

#define TZIE0_VDD5OV_DISABLE         ((0x0UL) << TZIE0_VDD5OV_Pos)
#define TZIE0_VDD5OV_ENABLE          ((0x1UL) << TZIE0_VDD5OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD5EXTUV
 *  @access     HV->TZIE0
 *  @brief      VDD5EXT under-voltage event interrupt enable
 */
#define TZIE0_VDD5EXTUV_Pos (4UL)
#define TZIE0_VDD5EXTUV_Msk (0x1UL << TZIE0_VDD5EXTUV_Pos)

#define TZIE0_VDD5EXTUV_DISABLE         ((0x0UL) << TZIE0_VDD5EXTUV_Pos)
#define TZIE0_VDD5EXTUV_ENABLE          ((0x1UL) << TZIE0_VDD5EXTUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD5EXTOV
 *  @access     HV->TZIE0
 *  @brief      VDD5EXT over-voltage event interrupt enable
 */
#define TZIE0_VDD5EXTOV_Pos (5UL)
#define TZIE0_VDD5EXTOV_Msk (0x1UL << TZIE0_VDD5EXTOV_Pos)

#define TZIE0_VDD5EXTOV_DISABLE         ((0x0UL) << TZIE0_VDD5EXTOV_Pos)
#define TZIE0_VDD5EXTOV_ENABLE          ((0x1UL) << TZIE0_VDD5EXTOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD3UV
 *  @access     HV->TZIE0
 *  @brief      VDD3 under-voltage event interrupt enable
 */
#define TZIE0_VDD3UV_Pos (6UL)
#define TZIE0_VDD3UV_Msk (0x1UL << TZIE0_VDD3UV_Pos)

#define TZIE0_VDD3UV_DISABLE         ((0x0UL) << TZIE0_VDD3UV_Pos)
#define TZIE0_VDD3UV_ENABLE          ((0x1UL) << TZIE0_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD3OV
 *  @access     HV->TZIE0
 *  @brief      VDD3 over-voltage event interrupt enable
 */
#define TZIE0_VDD3OV_Pos (7UL)
#define TZIE0_VDD3OV_Msk (0x1UL << TZIE0_VDD3OV_Pos)

#define TZIE0_VDD3OV_DISABLE         ((0x0UL) << TZIE0_VDD3OV_Pos)
#define TZIE0_VDD3OV_ENABLE          ((0x1UL) << TZIE0_VDD3OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           PMUOTWARN
 *  @access     HV->TZIE0
 *  @brief      PMU over-temperature warning event interrupt enable
 */
#define TZIE0_PMUOTWARN_Pos (8UL)
#define TZIE0_PMUOTWARN_Msk (0x1UL << TZIE0_PMUOTWARN_Pos)

#define TZIE0_PMUOTWARN_DISABLE         ((0x0UL) << TZIE0_PMUOTWARN_Pos)
#define TZIE0_PMUOTWARN_ENABLE          ((0x1UL) << TZIE0_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD5EXTOC
 *  @access     HV->TZIE0
 *  @brief      VDD5EXT over-current event flag
 */
#define TZIE0_VDD5EXTOC_Pos (9UL)
#define TZIE0_VDD5EXTOC_Msk (0x1UL << TZIE0_VDD5EXTOC_Pos)

#define TZIE0_VDD5EXTOC_DISABLE         ((0x0UL) << TZIE0_VDD5EXTOC_Pos)
#define TZIE0_VDD5EXTOC_ENABLE          ((0x1UL) << TZIE0_VDD5EXTOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD5OC
 *  @access     HV->TZIE0
 *  @brief      VDD5 over-current event interrupt enable
 */
#define TZIE0_VDD5OC_Pos (10UL)
#define TZIE0_VDD5OC_Msk (0x1UL << TZIE0_VDD5OC_Pos)

#define TZIE0_VDD5OC_DISABLE         ((0x0UL) << TZIE0_VDD5OC_Pos)
#define TZIE0_VDD5OC_ENABLE          ((0x1UL) << TZIE0_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           VDD3OC
 *  @access     HV->TZIE0
 *  @brief      VDD3 over-current event interrupt enable
 */
#define TZIE0_VDD3OC_Pos (11UL)
#define TZIE0_VDD3OC_Msk (0x1UL << TZIE0_VDD3OC_Pos)

#define TZIE0_VDD3OC_DISABLE         ((0x0UL) << TZIE0_VDD3OC_Pos)
#define TZIE0_VDD3OC_ENABLE          ((0x1UL) << TZIE0_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           CLKERR
 *  @access     HV->TZIE0
 *  @brief      Clock error event interrupt enable
 */
#define TZIE0_CLKERR_Pos (12UL)
#define TZIE0_CLKERR_Msk (0x1UL << TZIE0_CLKERR_Pos)

#define TZIE0_CLKERR_DISABLE         ((0x0UL) << TZIE0_CLKERR_Pos)
#define TZIE0_CLKERR_ENABLE          ((0x1UL) << TZIE0_CLKERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           LINTXDTIMEOUT
 *  @access     HV->TZIE0
 *  @brief      LIN TXD timeout event interrupt enable
 */
#define TZIE0_LINTXDTIMEOUT_Pos (13UL)
#define TZIE0_LINTXDTIMEOUT_Msk (0x1UL << TZIE0_LINTXDTIMEOUT_Pos)

#define TZIE0_LINTXDTIMEOUT_DISABLE         ((0x0UL) << TZIE0_LINTXDTIMEOUT_Pos)
#define TZIE0_LINTXDTIMEOUT_ENABLE          ((0x1UL) << TZIE0_LINTXDTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           LINOC
 *  @access     HV->TZIE0
 *  @brief      LIN transceiver over-current event interrupt enable
 */
#define TZIE0_LINOC_Pos (14UL)
#define TZIE0_LINOC_Msk (0x1UL << TZIE0_LINOC_Pos)

#define TZIE0_LINOC_DISABLE         ((0x0UL) << TZIE0_LINOC_Pos)
#define TZIE0_LINOC_ENABLE          ((0x1UL) << TZIE0_LINOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE0           LINOT
 *  @access     HV->TZIE0
 *  @brief      LIN transceiver over-temperature event interrupt enable
 */
#define TZIE0_LINOT_Pos (15UL)
#define TZIE0_LINOT_Msk (0x1UL << TZIE0_LINOT_Pos)

#define TZIE0_LINOT_DISABLE         ((0x0UL) << TZIE0_LINOT_Pos)
#define TZIE0_LINOT_ENABLE          ((0x1UL) << TZIE0_LINOT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VBATUV
 *  @access     HV->TZIC0
 *  @brief      VBAT under-voltage event interrupt clear
 */
#define TZIC0_VBATUV_Pos (0UL)
#define TZIC0_VBATUV_Msk (0x1UL << TZIC0_VBATUV_Pos)

#define TZIC0_VBATUV_NO_EFFECT         ((0x0UL) << TZIC0_VBATUV_Pos)
#define TZIC0_VBATUV_CLEAR             ((0x1UL) << TZIC0_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VBATOV
 *  @access     HV->TZIC0
 *  @brief      VBAT over-voltage event interrupt clear
 */
#define TZIC0_VBATOV_Pos (1UL)
#define TZIC0_VBATOV_Msk (0x1UL << TZIC0_VBATOV_Pos)

#define TZIC0_VBATOV_NO_EFFECT         ((0x0UL) << TZIC0_VBATOV_Pos)
#define TZIC0_VBATOV_CLEAR             ((0x1UL) << TZIC0_VBATOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD5UV
 *  @access     HV->TZIC0
 *  @brief      VDD5 under-voltage event interrupt clear
 */
#define TZIC0_VDD5UV_Pos (2UL)
#define TZIC0_VDD5UV_Msk (0x1UL << TZIC0_VDD5UV_Pos)

#define TZIC0_VDD5UV_NO_EFFECT         ((0x0UL) << TZIC0_VDD5UV_Pos)
#define TZIC0_VDD5UV_CLEAR             ((0x1UL) << TZIC0_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD5OV
 *  @access     HV->TZIC0
 *  @brief      VDD5 over-voltage event interrupt clear
 */
#define TZIC0_VDD5OV_Pos (3UL)
#define TZIC0_VDD5OV_Msk (0x1UL << TZIC0_VDD5OV_Pos)

#define TZIC0_VDD5OV_NO_EFFECT         ((0x0UL) << TZIC0_VDD5OV_Pos)
#define TZIC0_VDD5OV_CLEAR             ((0x1UL) << TZIC0_VDD5OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD5EXTUV
 *  @access     HV->TZIC0
 *  @brief      VDD5EXT under-voltage event interrupt clear
 */
#define TZIC0_VDD5EXTUV_Pos (4UL)
#define TZIC0_VDD5EXTUV_Msk (0x1UL << TZIC0_VDD5EXTUV_Pos)

#define TZIC0_VDD5EXTUV_NO_EFFECT         ((0x0UL) << TZIC0_VDD5EXTUV_Pos)
#define TZIC0_VDD5EXTUV_CLEAR             ((0x1UL) << TZIC0_VDD5EXTUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD5EXTOV
 *  @access     HV->TZIC0
 *  @brief      VDD5EXT over-voltage event interrupt clear
 */
#define TZIC0_VDD5EXTOV_Pos (5UL)
#define TZIC0_VDD5EXTOV_Msk (0x1UL << TZIC0_VDD5EXTOV_Pos)

#define TZIC0_VDD5EXTOV_NO_EFFECT         ((0x0UL) << TZIC0_VDD5EXTOV_Pos)
#define TZIC0_VDD5EXTOV_CLEAR             ((0x1UL) << TZIC0_VDD5EXTOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD3UV
 *  @access     HV->TZIC0
 *  @brief      VDD3 under-voltage event interrupt clear
 */
#define TZIC0_VDD3UV_Pos (6UL)
#define TZIC0_VDD3UV_Msk (0x1UL << TZIC0_VDD3UV_Pos)

#define TZIC0_VDD3UV_NO_EFFECT         ((0x0UL) << TZIC0_VDD3UV_Pos)
#define TZIC0_VDD3UV_CLEAR             ((0x1UL) << TZIC0_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD3OV
 *  @access     HV->TZIC0
 *  @brief      VDD3 over-voltage event interrupt clear
 */
#define TZIC0_VDD3OV_Pos (7UL)
#define TZIC0_VDD3OV_Msk (0x1UL << TZIC0_VDD3OV_Pos)

#define TZIC0_VDD3OV_NO_EFFECT         ((0x0UL) << TZIC0_VDD3OV_Pos)
#define TZIC0_VDD3OV_CLEAR             ((0x1UL) << TZIC0_VDD3OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           PMUOTWARN
 *  @access     HV->TZIC0
 *  @brief      Over-temperature warning event interrupt clear
 */
#define TZIC0_PMUOTWARN_Pos (8UL)
#define TZIC0_PMUOTWARN_Msk (0x1UL << TZIC0_PMUOTWARN_Pos)

#define TZIC0_PMUOTWARN_NO_EFFECT         ((0x0UL) << TZIC0_PMUOTWARN_Pos)
#define TZIC0_PMUOTWARN_CLEAR             ((0x1UL) << TZIC0_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD5EXTOC
 *  @access     HV->TZIC0
 *  @brief      VDD5EXT over-current event interrupt clear
 */
#define TZIC0_VDD5EXTOC_Pos (9UL)
#define TZIC0_VDD5EXTOC_Msk (0x1UL << TZIC0_VDD5EXTOC_Pos)

#define TZIC0_VDD5EXTOC_NO_EFFECT         ((0x0UL) << TZIC0_VDD5EXTOC_Pos)
#define TZIC0_VDD5EXTOC_CLEAR             ((0x1UL) << TZIC0_VDD5EXTOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD5OC
 *  @access     HV->TZIC0
 *  @brief      VDD5 over-current event interrupt clear
 */
#define TZIC0_VDD5OC_Pos (10UL)
#define TZIC0_VDD5OC_Msk (0x1UL << TZIC0_VDD5OC_Pos)

#define TZIC0_VDD5OC_NO_EFFECT         ((0x0UL) << TZIC0_VDD5OC_Pos)
#define TZIC0_VDD5OC_CLEAR             ((0x1UL) << TZIC0_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           VDD3OC
 *  @access     HV->TZIC0
 *  @brief      VDD3 over-current event interrupt clear
 */
#define TZIC0_VDD3OC_Pos (11UL)
#define TZIC0_VDD3OC_Msk (0x1UL << TZIC0_VDD3OC_Pos)

#define TZIC0_VDD3OC_NO_EFFECT         ((0x0UL) << TZIC0_VDD3OC_Pos)
#define TZIC0_VDD3OC_CLEAR             ((0x1UL) << TZIC0_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           CLKERR
 *  @access     HV->TZIC0
 *  @brief      Clock error event interrupt clear
 */
#define TZIC0_CLKERR_Pos (12UL)
#define TZIC0_CLKERR_Msk (0x1UL << TZIC0_CLKERR_Pos)

#define TZIC0_CLKERR_NO_EFFECT         ((0x0UL) << TZIC0_CLKERR_Pos)
#define TZIC0_CLKERR_CLEAR             ((0x1UL) << TZIC0_CLKERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           LINTXDTIMEOUT
 *  @access     HV->TZIC0
 *  @brief      LIN TXD timeout event interrupt clear
 */
#define TZIC0_LINTXDTIMEOUT_Pos (13UL)
#define TZIC0_LINTXDTIMEOUT_Msk (0x1UL << TZIC0_LINTXDTIMEOUT_Pos)

#define TZIC0_LINTXDTIMEOUT_NO_EFFECT         ((0x0UL) << TZIC0_LINTXDTIMEOUT_Pos)
#define TZIC0_LINTXDTIMEOUT_CLEAR             ((0x1UL) << TZIC0_LINTXDTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           LINOC
 *  @access     HV->TZIC0
 *  @brief      LIN transceiver over-current event interrupt clear
 */
#define TZIC0_LINOC_Pos (14UL)
#define TZIC0_LINOC_Msk (0x1UL << TZIC0_LINOC_Pos)

#define TZIC0_LINOC_NO_EFFECT         ((0x0UL) << TZIC0_LINOC_Pos)
#define TZIC0_LINOC_CLEAR             ((0x1UL) << TZIC0_LINOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC0           LINOT
 *  @access     HV->TZIC0
 *  @brief      LIN transceiver over-temperature event interrupt clear
 */
#define TZIC0_LINOT_Pos (15UL)
#define TZIC0_LINOT_Msk (0x1UL << TZIC0_LINOT_Pos)

#define TZIC0_LINOT_NO_EFFECT         ((0x0UL) << TZIC0_LINOT_Pos)
#define TZIC0_LINOT_CLEAR             ((0x1UL) << TZIC0_LINOT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VBATUV
 *  @access     HV->TZIF0
 *  @brief      Latched VBAT under-voltage event interrupt flag
 */
#define TZIF0_VBATUV_Pos (0UL)
#define TZIF0_VBATUV_Msk (0x1UL << TZIF0_VBATUV_Pos)

#define TZIF0_VBATUV_NOT_OCCUR         ((0x0UL) << TZIF0_VBATUV_Pos)
#define TZIF0_VBATUV_OCCUR             ((0x1UL) << TZIF0_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VBATOV
 *  @access     HV->TZIF0
 *  @brief      Latched VBAT over-voltage event interrupt flag
 */
#define TZIF0_VBATOV_Pos (1UL)
#define TZIF0_VBATOV_Msk (0x1UL << TZIF0_VBATOV_Pos)

#define TZIF0_VBATOV_NOT_OCCUR         ((0x0UL) << TZIF0_VBATOV_Pos)
#define TZIF0_VBATOV_OCCUR             ((0x1UL) << TZIF0_VBATOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD5UV
 *  @access     HV->TZIF0
 *  @brief      Latched VDD5 under-voltage event interrupt flag
 */
#define TZIF0_VDD5UV_Pos (2UL)
#define TZIF0_VDD5UV_Msk (0x1UL << TZIF0_VDD5UV_Pos)

#define TZIF0_VDD5UV_NOT_OCCUR         ((0x0UL) << TZIF0_VDD5UV_Pos)
#define TZIF0_VDD5UV_OCCUR             ((0x1UL) << TZIF0_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD5OV
 *  @access     HV->TZIF0
 *  @brief      Latched VDD5 over-voltage event interrupt flag
 */
#define TZIF0_VDD5OV_Pos (3UL)
#define TZIF0_VDD5OV_Msk (0x1UL << TZIF0_VDD5OV_Pos)

#define TZIF0_VDD5OV_NOT_OCCUR         ((0x0UL) << TZIF0_VDD5OV_Pos)
#define TZIF0_VDD5OV_OCCUR             ((0x1UL) << TZIF0_VDD5OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD5EXTUV
 *  @access     HV->TZIF0
 *  @brief      Latched VDD5EXT under-voltage event interrupt flag
 */
#define TZIF0_VDD5EXTUV_Pos (4UL)
#define TZIF0_VDD5EXTUV_Msk (0x1UL << TZIF0_VDD5EXTUV_Pos)

#define TZIF0_VDD5EXTUV_NOT_OCCUR         ((0x0UL) << TZIF0_VDD5EXTUV_Pos)
#define TZIF0_VDD5EXTUV_OCCUR             ((0x1UL) << TZIF0_VDD5EXTUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD5EXTOV
 *  @access     HV->TZIF0
 *  @brief      Latched VDD5EXT over-voltage event interrupt flag
 */
#define TZIF0_VDD5EXTOV_Pos (5UL)
#define TZIF0_VDD5EXTOV_Msk (0x1UL << TZIF0_VDD5EXTOV_Pos)

#define TZIF0_VDD5EXTOV_NOT_OCCUR         ((0x0UL) << TZIF0_VDD5EXTOV_Pos)
#define TZIF0_VDD5EXTOV_OCCUR             ((0x1UL) << TZIF0_VDD5EXTOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD3UV
 *  @access     HV->TZIF0
 *  @brief      Latched VDD3 under-voltage event interrupt flag
 */
#define TZIF0_VDD3UV_Pos (6UL)
#define TZIF0_VDD3UV_Msk (0x1UL << TZIF0_VDD3UV_Pos)

#define TZIF0_VDD3UV_NOT_OCCUR         ((0x0UL) << TZIF0_VDD3UV_Pos)
#define TZIF0_VDD3UV_OCCUR             ((0x1UL) << TZIF0_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD3OV
 *  @access     HV->TZIF0
 *  @brief      Latched VDD3 over-voltage event interrupt flag
 */
#define TZIF0_VDD3OV_Pos (7UL)
#define TZIF0_VDD3OV_Msk (0x1UL << TZIF0_VDD3OV_Pos)

#define TZIF0_VDD3OV_NOT_OCCUR         ((0x0UL) << TZIF0_VDD3OV_Pos)
#define TZIF0_VDD3OV_OCCUR             ((0x1UL) << TZIF0_VDD3OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           PMUOTWARN
 *  @access     HV->TZIF0
 *  @brief      Latched PMU over-temperature warning event interrupt flag
 */
#define TZIF0_PMUOTWARN_Pos (8UL)
#define TZIF0_PMUOTWARN_Msk (0x1UL << TZIF0_PMUOTWARN_Pos)

#define TZIF0_PMUOTWARN_NOT_OCCUR         ((0x0UL) << TZIF0_PMUOTWARN_Pos)
#define TZIF0_PMUOTWARN_OCCUR             ((0x1UL) << TZIF0_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD5EXTOC
 *  @access     HV->TZIF0
 *  @brief      Latched VDD5EXT over-current event interrupt flag
 */
#define TZIF0_VDD5EXTOC_Pos (9UL)
#define TZIF0_VDD5EXTOC_Msk (0x1UL << TZIF0_VDD5EXTOC_Pos)

#define TZIF0_VDD5EXTOC_NOT_OCCUR         ((0x0UL) << TZIF0_VDD5EXTOC_Pos)
#define TZIF0_VDD5EXTOC_OCCUR             ((0x1UL) << TZIF0_VDD5EXTOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD5OC
 *  @access     HV->TZIF0
 *  @brief      Latched VDD5 over-current event interrupt flag
 */
#define TZIF0_VDD5OC_Pos (10UL)
#define TZIF0_VDD5OC_Msk (0x1UL << TZIF0_VDD5OC_Pos)

#define TZIF0_VDD5OC_NOT_OCCUR         ((0x0UL) << TZIF0_VDD5OC_Pos)
#define TZIF0_VDD5OC_OCCUR             ((0x1UL) << TZIF0_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           VDD3OC
 *  @access     HV->TZIF0
 *  @brief      Latched VDD3 over-current event interrupt flag
 */
#define TZIF0_VDD3OC_Pos (11UL)
#define TZIF0_VDD3OC_Msk (0x1UL << TZIF0_VDD3OC_Pos)

#define TZIF0_VDD3OC_NOT_OCCUR         ((0x0UL) << TZIF0_VDD3OC_Pos)
#define TZIF0_VDD3OC_OCCUR             ((0x1UL) << TZIF0_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           CLKERR
 *  @access     HV->TZIF0
 *  @brief      Latched clock error event interrupt flag
 */
#define TZIF0_CLKERR_Pos (12UL)
#define TZIF0_CLKERR_Msk (0x1UL << TZIF0_CLKERR_Pos)

#define TZIF0_CLKERR_NOT_OCCUR         ((0x0UL) << TZIF0_CLKERR_Pos)
#define TZIF0_CLKERR_OCCUR             ((0x1UL) << TZIF0_CLKERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           LINTXTIMEOUT
 *  @access     HV->TZIF0
 *  @brief      Latched LIN TXD timeout event interrupt flag
 */
#define TZIF0_LINTXTIMEOUT_Pos (13UL)
#define TZIF0_LINTXTIMEOUT_Msk (0x1UL << TZIF0_LINTXTIMEOUT_Pos)

#define TZIF0_LINTXTIMEOUT_NOT_OCCUR         ((0x0UL) << TZIF0_LINTXTIMEOUT_Pos)
#define TZIF0_LINTXTIMEOUT_OCCUR             ((0x1UL) << TZIF0_LINTXTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           LINOC
 *  @access     HV->TZIF0
 *  @brief      Latched LIN transceiver over-current event interrupt flag
 */
#define TZIF0_LINOC_Pos (14UL)
#define TZIF0_LINOC_Msk (0x1UL << TZIF0_LINOC_Pos)

#define TZIF0_LINOC_NOT_OCCUR         ((0x0UL) << TZIF0_LINOC_Pos)
#define TZIF0_LINOC_OCCUR             ((0x1UL) << TZIF0_LINOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF0           LINOT
 *  @access     HV->TZIF0
 *  @brief      Latched LIN transceiver over-temperature event interrupt flag
 */
#define TZIF0_LINOT_Pos (15UL)
#define TZIF0_LINOT_Msk (0x1UL << TZIF0_LINOT_Pos)

#define TZIF0_LINOT_NOT_OCCUR         ((0x0UL) << TZIF0_LINOT_Pos)
#define TZIF0_LINOT_OCCUR             ((0x1UL) << TZIF0_LINOT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PDRVOCLU
 *  @access     HV->TZIE1
 *  @brief      Pre-driver U-phase low-side over-current event interrupt enable
 */
#define TZIE1_PDRVOCLU_Pos (0UL)
#define TZIE1_PDRVOCLU_Msk (0x1UL << TZIE1_PDRVOCLU_Pos)

#define TZIE1_PDRVOCLU_DISABLE         ((0x0UL) << TZIE1_PDRVOCLU_Pos)
#define TZIE1_PDRVOCLU_ENABLE          ((0x1UL) << TZIE1_PDRVOCLU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PDRVOCLV
 *  @access     HV->TZIE1
 *  @brief      Pre-driver V-phase low-side over-current event interrupt enable
 */
#define TZIE1_PDRVOCLV_Pos (1UL)
#define TZIE1_PDRVOCLV_Msk (0x1UL << TZIE1_PDRVOCLV_Pos)

#define TZIE1_PDRVOCLV_DISABLE         ((0x0UL) << TZIE1_PDRVOCLV_Pos)
#define TZIE1_PDRVOCLV_ENABLE          ((0x1UL) << TZIE1_PDRVOCLV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PDRVOCLW
 *  @access     HV->TZIE1
 *  @brief      Pre-driver W-phase low-side over-current event interrupt enable
 */
#define TZIE1_PDRVOCLW_Pos (2UL)
#define TZIE1_PDRVOCLW_Msk (0x1UL << TZIE1_PDRVOCLW_Pos)

#define TZIE1_PDRVOCLW_DISABLE         ((0x0UL) << TZIE1_PDRVOCLW_Pos)
#define TZIE1_PDRVOCLW_ENABLE          ((0x1UL) << TZIE1_PDRVOCLW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PDRVOCHU
 *  @access     HV->TZIE1
 *  @brief      Pre-driver U-phase high-side over-current event interrupt enable
 */
#define TZIE1_PDRVOCHU_Pos (3UL)
#define TZIE1_PDRVOCHU_Msk (0x1UL << TZIE1_PDRVOCHU_Pos)

#define TZIE1_PDRVOCHU_DISABLE         ((0x0UL) << TZIE1_PDRVOCHU_Pos)
#define TZIE1_PDRVOCHU_ENABLE          ((0x1UL) << TZIE1_PDRVOCHU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PDRVOCHV
 *  @access     HV->TZIE1
 *  @brief      Pre-driver V-phase high-side over-current event interrupt enable
 */
#define TZIE1_PDRVOCHV_Pos (4UL)
#define TZIE1_PDRVOCHV_Msk (0x1UL << TZIE1_PDRVOCHV_Pos)

#define TZIE1_PDRVOCHV_DISABLE         ((0x0UL) << TZIE1_PDRVOCHV_Pos)
#define TZIE1_PDRVOCHV_ENABLE          ((0x1UL) << TZIE1_PDRVOCHV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PDRVOCHW
 *  @access     HV->TZIE1
 *  @brief      Pre-driver W-phase high-side over-current event interrupt enable
 */
#define TZIE1_PDRVOCHW_Pos (5UL)
#define TZIE1_PDRVOCHW_Msk (0x1UL << TZIE1_PDRVOCHW_Pos)

#define TZIE1_PDRVOCHW_DISABLE         ((0x0UL) << TZIE1_PDRVOCHW_Pos)
#define TZIE1_PDRVOCHW_ENABLE          ((0x1UL) << TZIE1_PDRVOCHW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           VCPUV
 *  @access     HV->TZIE1
 *  @brief      Pre-driver VCP over-voltage event interrupt enable
 */
#define TZIE1_VCPUV_Pos (6UL)
#define TZIE1_VCPUV_Msk (0x1UL << TZIE1_VCPUV_Pos)

#define TZIE1_VCPUV_DISABLE         ((0x0UL) << TZIE1_VCPUV_Pos)
#define TZIE1_VCPUV_ENABLE          ((0x1UL) << TZIE1_VCPUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           VBATUV
 *  @access     HV->TZIE1
 *  @brief      VBAT under-voltage event interrupt enable
 */
#define TZIE1_VBATUV_Pos (8UL)
#define TZIE1_VBATUV_Msk (0x1UL << TZIE1_VBATUV_Pos)

#define TZIE1_VBATUV_DISABLE         ((0x0UL) << TZIE1_VBATUV_Pos)
#define TZIE1_VBATUV_ENABLE          ((0x1UL) << TZIE1_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           VDD5UV
 *  @access     HV->TZIE1
 *  @brief      VDD5 under-voltage event interrupt enable
 */
#define TZIE1_VDD5UV_Pos (9UL)
#define TZIE1_VDD5UV_Msk (0x1UL << TZIE1_VDD5UV_Pos)

#define TZIE1_VDD5UV_DISABLE         ((0x0UL) << TZIE1_VDD5UV_Pos)
#define TZIE1_VDD5UV_ENABLE          ((0x1UL) << TZIE1_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           VDD3UV
 *  @access     HV->TZIE1
 *  @brief      VDD3 under-voltage event interrupt enable
 */
#define TZIE1_VDD3UV_Pos (10UL)
#define TZIE1_VDD3UV_Msk (0x1UL << TZIE1_VDD3UV_Pos)

#define TZIE1_VDD3UV_DISABLE         ((0x0UL) << TZIE1_VDD3UV_Pos)
#define TZIE1_VDD3UV_ENABLE          ((0x1UL) << TZIE1_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           PMUOTWARN
 *  @access     HV->TZIE1
 *  @brief      Over-temperature warning event interrupt enable
 */
#define TZIE1_PMUOTWARN_Pos (11UL)
#define TZIE1_PMUOTWARN_Msk (0x1UL << TZIE1_PMUOTWARN_Pos)

#define TZIE1_PMUOTWARN_DISABLE         ((0x0UL) << TZIE1_PMUOTWARN_Pos)
#define TZIE1_PMUOTWARN_ENABLE          ((0x1UL) << TZIE1_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           VDD5OC
 *  @access     HV->TZIE1
 *  @brief      VDD5 over-current event interrupt enable
 */
#define TZIE1_VDD5OC_Pos (12UL)
#define TZIE1_VDD5OC_Msk (0x1UL << TZIE1_VDD5OC_Pos)

#define TZIE1_VDD5OC_DISABLE         ((0x0UL) << TZIE1_VDD5OC_Pos)
#define TZIE1_VDD5OC_ENABLE          ((0x1UL) << TZIE1_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           VDD3OC
 *  @access     HV->TZIE1
 *  @brief      VDD3 over-current event interrupt enable
 */
#define TZIE1_VDD3OC_Pos (13UL)
#define TZIE1_VDD3OC_Msk (0x1UL << TZIE1_VDD3OC_Pos)

#define TZIE1_VDD3OC_DISABLE         ((0x0UL) << TZIE1_VDD3OC_Pos)
#define TZIE1_VDD3OC_ENABLE          ((0x1UL) << TZIE1_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           LPRCOERR
 *  @access     HV->TZIE1
 *  @brief      LPRCO error event interrupt enable
 */
#define TZIE1_LPRCOERR_Pos (14UL)
#define TZIE1_LPRCOERR_Msk (0x1UL << TZIE1_LPRCOERR_Pos)

#define TZIE1_LPRCOERR_DISABLE         ((0x0UL) << TZIE1_LPRCOERR_Pos)
#define TZIE1_LPRCOERR_ENABLE          ((0x1UL) << TZIE1_LPRCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIE1           RCOERR
 *  @access     HV->TZIE1
 *  @brief      RCO error event interrupt enable
 */
#define TZIE1_RCOERR_Pos (15UL)
#define TZIE1_RCOERR_Msk (0x1UL << TZIE1_RCOERR_Pos)

#define TZIE1_RCOERR_DISABLE         ((0x0UL) << TZIE1_RCOERR_Pos)
#define TZIE1_RCOERR_ENABLE          ((0x1UL) << TZIE1_RCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PDRVOCLU
 *  @access     HV->TZIC1
 *  @brief      Pre-driver U-phase low-side over-current event interrupt clear
 */
#define TZIC1_PDRVOCLU_Pos (0UL)
#define TZIC1_PDRVOCLU_Msk (0x1UL << TZIC1_PDRVOCLU_Pos)

#define TZIC1_PDRVOCLU_NO_EFFECT         ((0x0UL) << TZIC1_PDRVOCLU_Pos)
#define TZIC1_PDRVOCLU_CLEAR             ((0x1UL) << TZIC1_PDRVOCLU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PDRVOCLV
 *  @access     HV->TZIC1
 *  @brief      Pre-driver V-phase low-side over-current event interrupt clear
 */
#define TZIC1_PDRVOCLV_Pos (1UL)
#define TZIC1_PDRVOCLV_Msk (0x1UL << TZIC1_PDRVOCLV_Pos)

#define TZIC1_PDRVOCLV_NO_EFFECT         ((0x0UL) << TZIC1_PDRVOCLV_Pos)
#define TZIC1_PDRVOCLV_CLEAR             ((0x1UL) << TZIC1_PDRVOCLV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PDRVOCLW
 *  @access     HV->TZIC1
 *  @brief      Pre-driver W-phase low-side over-current event interrupt clear
 */
#define TZIC1_PDRVOCLW_Pos (2UL)
#define TZIC1_PDRVOCLW_Msk (0x1UL << TZIC1_PDRVOCLW_Pos)

#define TZIC1_PDRVOCLW_NO_EFFECT         ((0x0UL) << TZIC1_PDRVOCLW_Pos)
#define TZIC1_PDRVOCLW_CLEAR             ((0x1UL) << TZIC1_PDRVOCLW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PDRVOCHU
 *  @access     HV->TZIC1
 *  @brief      Pre-driver U-phase high-side over-current event interrupt clear
 */
#define TZIC1_PDRVOCHU_Pos (3UL)
#define TZIC1_PDRVOCHU_Msk (0x1UL << TZIC1_PDRVOCHU_Pos)

#define TZIC1_PDRVOCHU_NO_EFFECT         ((0x0UL) << TZIC1_PDRVOCHU_Pos)
#define TZIC1_PDRVOCHU_CLEAR             ((0x1UL) << TZIC1_PDRVOCHU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PDRVOCHV
 *  @access     HV->TZIC1
 *  @brief      Pre-driver V-phase high-side over-current event interrupt clear
 */
#define TZIC1_PDRVOCHV_Pos (4UL)
#define TZIC1_PDRVOCHV_Msk (0x1UL << TZIC1_PDRVOCHV_Pos)

#define TZIC1_PDRVOCHV_NO_EFFECT         ((0x0UL) << TZIC1_PDRVOCHV_Pos)
#define TZIC1_PDRVOCHV_CLEAR             ((0x1UL) << TZIC1_PDRVOCHV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PDRVOCHW
 *  @access     HV->TZIC1
 *  @brief      Pre-driver W-phase high-side over-current event interrupt clear
 */
#define TZIC1_PDRVOCHW_Pos (5UL)
#define TZIC1_PDRVOCHW_Msk (0x1UL << TZIC1_PDRVOCHW_Pos)

#define TZIC1_PDRVOCHW_NO_EFFECT         ((0x0UL) << TZIC1_PDRVOCHW_Pos)
#define TZIC1_PDRVOCHW_CLEAR             ((0x1UL) << TZIC1_PDRVOCHW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           VCPUV
 *  @access     HV->TZIC1
 *  @brief      Pre-driver VCP over-voltage event interrupt clear
 */
#define TZIC1_VCPUV_Pos (6UL)
#define TZIC1_VCPUV_Msk (0x1UL << TZIC1_VCPUV_Pos)

#define TZIC1_VCPUV_NO_EFFECT         ((0x0UL) << TZIC1_VCPUV_Pos)
#define TZIC1_VCPUV_CLEAR             ((0x1UL) << TZIC1_VCPUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           VBATUV
 *  @access     HV->TZIC1
 *  @brief      VBAT under-voltage event interrupt clear
 */
#define TZIC1_VBATUV_Pos (8UL)
#define TZIC1_VBATUV_Msk (0x1UL << TZIC1_VBATUV_Pos)

#define TZIC1_VBATUV_NO_EFFECT         ((0x0UL) << TZIC1_VBATUV_Pos)
#define TZIC1_VBATUV_CLEAR             ((0x1UL) << TZIC1_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           VDD5UV
 *  @access     HV->TZIC1
 *  @brief      VDD5 under-voltage event interrupt clear
 */
#define TZIC1_VDD5UV_Pos (9UL)
#define TZIC1_VDD5UV_Msk (0x1UL << TZIC1_VDD5UV_Pos)

#define TZIC1_VDD5UV_NO_EFFECT         ((0x0UL) << TZIC1_VDD5UV_Pos)
#define TZIC1_VDD5UV_CLEAR             ((0x1UL) << TZIC1_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           VDD3UV
 *  @access     HV->TZIC1
 *  @brief      VDD3 under-voltage event interrupt clear
 */
#define TZIC1_VDD3UV_Pos (10UL)
#define TZIC1_VDD3UV_Msk (0x1UL << TZIC1_VDD3UV_Pos)

#define TZIC1_VDD3UV_NO_EFFECT         ((0x0UL) << TZIC1_VDD3UV_Pos)
#define TZIC1_VDD3UV_CLEAR             ((0x1UL) << TZIC1_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           PMUOTWARN
 *  @access     HV->TZIC1
 *  @brief      Over-temperature warning event interrupt clear
 */
#define TZIC1_PMUOTWARN_Pos (11UL)
#define TZIC1_PMUOTWARN_Msk (0x1UL << TZIC1_PMUOTWARN_Pos)

#define TZIC1_PMUOTWARN_NO_EFFECT         ((0x0UL) << TZIC1_PMUOTWARN_Pos)
#define TZIC1_PMUOTWARN_CLEAR             ((0x1UL) << TZIC1_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           VDD5OC
 *  @access     HV->TZIC1
 *  @brief      VDD5 over-current event interrupt clear
 */
#define TZIC1_VDD5OC_Pos (12UL)
#define TZIC1_VDD5OC_Msk (0x1UL << TZIC1_VDD5OC_Pos)

#define TZIC1_VDD5OC_NO_EFFECT         ((0x0UL) << TZIC1_VDD5OC_Pos)
#define TZIC1_VDD5OC_CLEAR             ((0x1UL) << TZIC1_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           VDD3OC
 *  @access     HV->TZIC1
 *  @brief      VDD3 over-current event interrupt clear
 */
#define TZIC1_VDD3OC_Pos (13UL)
#define TZIC1_VDD3OC_Msk (0x1UL << TZIC1_VDD3OC_Pos)

#define TZIC1_VDD3OC_NO_EFFECT         ((0x0UL) << TZIC1_VDD3OC_Pos)
#define TZIC1_VDD3OC_CLEAR             ((0x1UL) << TZIC1_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           LPRCOERR
 *  @access     HV->TZIC1
 *  @brief      LPRCO error event interrupt clear
 */
#define TZIC1_LPRCOERR_Pos (14UL)
#define TZIC1_LPRCOERR_Msk (0x1UL << TZIC1_LPRCOERR_Pos)

#define TZIC1_LPRCOERR_NO_EFFECT         ((0x0UL) << TZIC1_LPRCOERR_Pos)
#define TZIC1_LPRCOERR_CLEAR             ((0x1UL) << TZIC1_LPRCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIC1           RCOERR
 *  @access     HV->TZIC1
 *  @brief      RCO error event interrupt clear
 */
#define TZIC1_RCOERR_Pos (15UL)
#define TZIC1_RCOERR_Msk (0x1UL << TZIC1_RCOERR_Pos)

#define TZIC1_RCOERR_NO_EFFECT         ((0x0UL) << TZIC1_RCOERR_Pos)
#define TZIC1_RCOERR_CLEAR             ((0x1UL) << TZIC1_RCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PDRVOCLU
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver U-phase low-side over-current event interrupt flag
 */
#define TZIF1_PDRVOCLU_Pos (0UL)
#define TZIF1_PDRVOCLU_Msk (0x1UL << TZIF1_PDRVOCLU_Pos)

#define TZIF1_PDRVOCLU_NOT_OCCUR         ((0x0UL) << TZIF1_PDRVOCLU_Pos)
#define TZIF1_PDRVOCLU_OCCUR             ((0x1UL) << TZIF1_PDRVOCLU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PDRVOCLV
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver V-phase low-side over-current event interrupt flag
 */
#define TZIF1_PDRVOCLV_Pos (1UL)
#define TZIF1_PDRVOCLV_Msk (0x1UL << TZIF1_PDRVOCLV_Pos)

#define TZIF1_PDRVOCLV_NOT_OCCUR         ((0x0UL) << TZIF1_PDRVOCLV_Pos)
#define TZIF1_PDRVOCLV_OCCUR             ((0x1UL) << TZIF1_PDRVOCLV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PDRVOCLW
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver W-phase low-side over-current event interrupt flag
 */
#define TZIF1_PDRVOCLW_Pos (2UL)
#define TZIF1_PDRVOCLW_Msk (0x1UL << TZIF1_PDRVOCLW_Pos)

#define TZIF1_PDRVOCLW_NOT_OCCUR         ((0x0UL) << TZIF1_PDRVOCLW_Pos)
#define TZIF1_PDRVOCLW_OCCUR             ((0x1UL) << TZIF1_PDRVOCLW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PDRVOCHU
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver U-phase high-side over-current event interrupt flag
 */
#define TZIF1_PDRVOCHU_Pos (3UL)
#define TZIF1_PDRVOCHU_Msk (0x1UL << TZIF1_PDRVOCHU_Pos)

#define TZIF1_PDRVOCHU_NOT_OCCUR         ((0x0UL) << TZIF1_PDRVOCHU_Pos)
#define TZIF1_PDRVOCHU_OCCUR             ((0x1UL) << TZIF1_PDRVOCHU_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PDRVOCHV
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver V-phase high-side over-current event interrupt flag
 */
#define TZIF1_PDRVOCHV_Pos (4UL)
#define TZIF1_PDRVOCHV_Msk (0x1UL << TZIF1_PDRVOCHV_Pos)

#define TZIF1_PDRVOCHV_NOT_OCCUR         ((0x0UL) << TZIF1_PDRVOCHV_Pos)
#define TZIF1_PDRVOCHV_OCCUR             ((0x1UL) << TZIF1_PDRVOCHV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PDRVOCHW
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver W-phase high-side over-current event interrupt flag
 */
#define TZIF1_PDRVOCHW_Pos (5UL)
#define TZIF1_PDRVOCHW_Msk (0x1UL << TZIF1_PDRVOCHW_Pos)

#define TZIF1_PDRVOCHW_NOT_OCCUR         ((0x0UL) << TZIF1_PDRVOCHW_Pos)
#define TZIF1_PDRVOCHW_OCCUR             ((0x1UL) << TZIF1_PDRVOCHW_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           VCPUV
 *  @access     HV->TZIF1
 *  @brief      Latched pre-driver VCP over-voltage event interrupt flag
 */
#define TZIF1_VCPUV_Pos (6UL)
#define TZIF1_VCPUV_Msk (0x1UL << TZIF1_VCPUV_Pos)

#define TZIF1_VCPUV_NOT_OCCUR         ((0x0UL) << TZIF1_VCPUV_Pos)
#define TZIF1_VCPUV_OCCUR             ((0x1UL) << TZIF1_VCPUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           VBATUV
 *  @access     HV->TZIF1
 *  @brief      Latched VBAT under-voltage event interrupt flag
 */
#define TZIF1_VBATUV_Pos (8UL)
#define TZIF1_VBATUV_Msk (0x1UL << TZIF1_VBATUV_Pos)

#define TZIF1_VBATUV_NOT_OCCUR         ((0x0UL) << TZIF1_VBATUV_Pos)
#define TZIF1_VBATUV_OCCUR             ((0x1UL) << TZIF1_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           VDD5UV
 *  @access     HV->TZIF1
 *  @brief      Latched VDD5 under-voltage event interrupt flag
 */
#define TZIF1_VDD5UV_Pos (9UL)
#define TZIF1_VDD5UV_Msk (0x1UL << TZIF1_VDD5UV_Pos)

#define TZIF1_VDD5UV_NOT_OCCUR         ((0x0UL) << TZIF1_VDD5UV_Pos)
#define TZIF1_VDD5UV_OCCUR             ((0x1UL) << TZIF1_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           VDD3UV
 *  @access     HV->TZIF1
 *  @brief      Latched VDD3 under-voltage event interrupt flag
 */
#define TZIF1_VDD3UV_Pos (10UL)
#define TZIF1_VDD3UV_Msk (0x1UL << TZIF1_VDD3UV_Pos)

#define TZIF1_VDD3UV_NOT_OCCUR         ((0x0UL) << TZIF1_VDD3UV_Pos)
#define TZIF1_VDD3UV_OCCUR             ((0x1UL) << TZIF1_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           PMUOTWARN
 *  @access     HV->TZIF1
 *  @brief      Latched over-temperature warning event interrupt flag
 */
#define TZIF1_PMUOTWARN_Pos (11UL)
#define TZIF1_PMUOTWARN_Msk (0x1UL << TZIF1_PMUOTWARN_Pos)

#define TZIF1_PMUOTWARN_NOT_OCCUR         ((0x0UL) << TZIF1_PMUOTWARN_Pos)
#define TZIF1_PMUOTWARN_OCCUR             ((0x1UL) << TZIF1_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           VDD5OC
 *  @access     HV->TZIF1
 *  @brief      Latched VDD5 over-current event interrupt flag
 */
#define TZIF1_VDD5OC_Pos (12UL)
#define TZIF1_VDD5OC_Msk (0x1UL << TZIF1_VDD5OC_Pos)

#define TZIF1_VDD5OC_NOT_OCCUR         ((0x0UL) << TZIF1_VDD5OC_Pos)
#define TZIF1_VDD5OC_OCCUR             ((0x1UL) << TZIF1_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           VDD3OC
 *  @access     HV->TZIF1
 *  @brief      Latched VDD3 over-current event interrupt flag
 */
#define TZIF1_VDD3OC_Pos (13UL)
#define TZIF1_VDD3OC_Msk (0x1UL << TZIF1_VDD3OC_Pos)

#define TZIF1_VDD3OC_NOT_OCCUR         ((0x0UL) << TZIF1_VDD3OC_Pos)
#define TZIF1_VDD3OC_OCCUR             ((0x1UL) << TZIF1_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           LPRCOERR
 *  @access     HV->TZIF1
 *  @brief      Latched LPRCO error event interrupt flag
 */
#define TZIF1_LPRCOERR_Pos (14UL)
#define TZIF1_LPRCOERR_Msk (0x1UL << TZIF1_LPRCOERR_Pos)

#define TZIF1_LPRCOERR_NOT_OCCUR         ((0x0UL) << TZIF1_LPRCOERR_Pos)
#define TZIF1_LPRCOERR_OCCUR             ((0x1UL) << TZIF1_LPRCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              TZIF1           RCOERR
 *  @access     HV->TZIF1
 *  @brief      Latched RCO error event interrupt flag
 */
#define TZIF1_RCOERR_Pos (15UL)
#define TZIF1_RCOERR_Msk (0x1UL << TZIF1_RCOERR_Pos)

#define TZIF1_RCOERR_NOT_OCCUR         ((0x0UL) << TZIF1_RCOERR_Pos)
#define TZIF1_RCOERR_OCCUR             ((0x1UL) << TZIF1_RCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL0       PMUOTFATAL
 *  @access     HV->EVTTHCTL0
 *  @brief      PMU over-temperature fatal event threshold
 */
#define EVTTHCTL0_PMUOTFATAL_Pos (0UL)
#define EVTTHCTL0_PMUOTFATAL_Msk (0x7UL << EVTTHCTL0_PMUOTFATAL_Pos)

#define EVTTHCTL0_PMUOTFATAL_129C         ((0x0UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_137C         ((0x1UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_146C         ((0x2UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_154C         ((0x3UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_163C         ((0x4UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_171C         ((0x5UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_180C         ((0x6UL) << EVTTHCTL0_PMUOTFATAL_Pos)
#define EVTTHCTL0_PMUOTFATAL_189C         ((0x7UL) << EVTTHCTL0_PMUOTFATAL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL0       PMUOTWARN
 *  @access     HV->EVTTHCTL0
 *  @brief      PMU over-temperature warning event threshold
 */
#define EVTTHCTL0_PMUOTWARN_Pos (3UL)
#define EVTTHCTL0_PMUOTWARN_Msk (0x7UL << EVTTHCTL0_PMUOTWARN_Pos)

#define EVTTHCTL0_PMUOTWARN_129C         ((0x0UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_137C         ((0x1UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_146C         ((0x2UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_154C         ((0x3UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_163C         ((0x4UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_171C         ((0x5UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_180C         ((0x6UL) << EVTTHCTL0_PMUOTWARN_Pos)
#define EVTTHCTL0_PMUOTWARN_189C         ((0x7UL) << EVTTHCTL0_PMUOTWARN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL0       VBATUV
 *  @access     HV->EVTTHCTL0
 *  @brief      VBAT under-voltage event threshold
 */
#define EVTTHCTL0_VBATUV_Pos (6UL)
#define EVTTHCTL0_VBATUV_Msk (0x7UL << EVTTHCTL0_VBATUV_Pos)

#define EVTTHCTL0_VBATUV_5P0V          ((0x0UL) << EVTTHCTL0_VBATUV_Pos)
#define EVTTHCTL0_VBATUV_5P5V          ((0x1UL) << EVTTHCTL0_VBATUV_Pos)
#define EVTTHCTL0_VBATUV_6P0V          ((0x2UL) << EVTTHCTL0_VBATUV_Pos)
#define EVTTHCTL0_VBATUV_7P4V          ((0x3UL) << EVTTHCTL0_VBATUV_Pos)
#define EVTTHCTL0_VBATUV_9P6V          ((0x4UL) << EVTTHCTL0_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL0       VBATOV
 *  @access     HV->EVTTHCTL0
 *  @brief      VBAT over-voltage event threshold
 */
#define EVTTHCTL0_VBATOV_Pos (9UL)
#define EVTTHCTL0_VBATOV_Msk (0x7UL << EVTTHCTL0_VBATOV_Pos)

#define EVTTHCTL0_VBATOV_14P2V         ((0x0UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_16P6V         ((0x1UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_20P0V         ((0x2UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_23P2V         ((0x3UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_27P5V         ((0x4UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_30P4V         ((0x5UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_33P9V         ((0x6UL) << EVTTHCTL0_VBATOV_Pos)
#define EVTTHCTL0_VBATOV_44P0V         ((0x7UL) << EVTTHCTL0_VBATOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL0       VDD5UV
 *  @access     HV->EVTTHCTL0
 *  @brief      VDD5 under-voltage event threshold
 */
#define EVTTHCTL0_VDD5UV_Pos (12UL)
#define EVTTHCTL0_VDD5UV_Msk (0x3UL << EVTTHCTL0_VDD5UV_Pos)

#define EVTTHCTL0_VDD5UV_4P4V         ((0x0UL) << EVTTHCTL0_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL0       VDD5OV
 *  @access     HV->EVTTHCTL0
 *  @brief      VDD5 over-voltage event threshold
 */
#define EVTTHCTL0_VDD5OV_Pos (14UL)
#define EVTTHCTL0_VDD5OV_Msk (0x3UL << EVTTHCTL0_VDD5OV_Pos)

#define EVTTHCTL0_VDD5OV_5P68V         ((0x2UL) << EVTTHCTL0_VDD5OV_Pos)
#define EVTTHCTL0_VDD5OV_5P90V         ((0x3UL) << EVTTHCTL0_VDD5OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL1       VDD5EXTUV
 *  @access     HV->EVTTHCTL1
 *  @brief      VDD5EXT under-voltage threshold
 */
#define EVTTHCTL1_VDD5EXTUV_Pos (0UL)
#define EVTTHCTL1_VDD5EXTUV_Msk (0x3UL << EVTTHCTL1_VDD5EXTUV_Pos)

#define EVTTHCTL1_VDD5EXTUV_4P4V         ((0x3UL) << EVTTHCTL1_VDD5EXTUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL1       VDD5EXTOV
 *  @access     HV->EVTTHCTL1
 *  @brief      VDD5EXT over-voltage threshold
 */
#define EVTTHCTL1_VDD5EXTOV_Pos (2UL)
#define EVTTHCTL1_VDD5EXTOV_Msk (0x3UL << EVTTHCTL1_VDD5EXTOV_Pos)

#define EVTTHCTL1_VDD5EXTOV_5P68V         ((0x2UL) << EVTTHCTL1_VDD5EXTOV_Pos)
#define EVTTHCTL1_VDD5EXTOV_5P90V         ((0x3UL) << EVTTHCTL1_VDD5EXTOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL1       VDD3UV
 *  @access     HV->EVTTHCTL1
 *  @brief      VDD3 under-voltage threshold
 */
#define EVTTHCTL1_VDD3UV_Pos (4UL)
#define EVTTHCTL1_VDD3UV_Msk (0x3UL << EVTTHCTL1_VDD3UV_Pos)

#define EVTTHCTL1_VDD3UV_2P85V         ((0x2UL) << EVTTHCTL1_VDD3UV_Pos)
#define EVTTHCTL1_VDD3UV_3P00V         ((0x3UL) << EVTTHCTL1_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL1       VDD3OV
 *  @access     HV->EVTTHCTL1
 *  @brief      VDD3 over-voltage threshold
 */
#define EVTTHCTL1_VDD3OV_Pos (6UL)
#define EVTTHCTL1_VDD3OV_Msk (0x3UL << EVTTHCTL1_VDD3OV_Pos)

#define EVTTHCTL1_VDD3OV_3P64V         ((0x1UL) << EVTTHCTL1_VDD3OV_Pos)
#define EVTTHCTL1_VDD3OV_3P90V         ((0x2UL) << EVTTHCTL1_VDD3OV_Pos)
#define EVTTHCTL1_VDD3OV_4P22V         ((0x3UL) << EVTTHCTL1_VDD3OV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              EVTTHCTL1       VCPUV
 *  @access     HV->EVTTHCTL1
 *  @brief      VCP under-voltage event threshold
 */
#define EVTTHCTL1_VCPUV_Pos (8UL)
#define EVTTHCTL1_VCPUV_Msk (0xFUL << EVTTHCTL1_VCPUV_Pos)

#define EVTTHCTL1_VCPUV_VBAT_ADD_6dot097_V         ((0x00UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_6dot333_V         ((0x01UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_6dot568_V         ((0x02UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_6dot802_V         ((0x03UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_7dot039_V         ((0x04UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_7dot295_V         ((0x05UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_7dot509_V         ((0x06UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_7dot745_V         ((0x07UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_7dot982_V         ((0x08UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_8dot217_V         ((0x09UL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_8dot452_V         ((0x0AUL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_8dot687_V         ((0x0BUL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_8dot922_V         ((0x0CUL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_9dot158_V         ((0x0DUL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_9dot393_V         ((0x0EUL) << EVTTHCTL1_VCPUV_Pos)
#define EVTTHCTL1_VCPUV_VBAT_ADD_9dot629_V         ((0x0FUL) << EVTTHCTL1_VCPUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        EN
 *  @access     HV->PDRVCTL0
 *  @brief      Pre-driver enable
 */
#define PDRVCTL0_EN_Pos (0UL)
#define PDRVCTL0_EN_Msk (0x1UL << PDRVCTL0_EN_Pos)

#define PDRVCTL0_EN_DISABLE         ((0x0UL) << PDRVCTL0_EN_Pos)
#define PDRVCTL0_EN_ENABLE          ((0x1UL) << PDRVCTL0_EN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        MAXHOLDEN
 *  @access     HV->PDRVCTL0
 *  @brief      Enable maximum hold during pre-driver switch
 */
#define PDRVCTL0_MAXHOLDEN_Pos (1UL)
#define PDRVCTL0_MAXHOLDEN_Msk (0x1UL << PDRVCTL0_MAXHOLDEN_Pos)

#define PDRVCTL0_MAXHOLDEN_DISABLE         ((0x0UL) << PDRVCTL0_MAXHOLDEN_Pos)
#define PDRVCTL0_MAXHOLDEN_ENABLE          ((0x1UL) << PDRVCTL0_MAXHOLDEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        MINNOV
 *  @access     HV->PDRVCTL0
 *  @brief      Minimal non-overlap timing window
 */
#define PDRVCTL0_MINNOV_Pos (2UL)
#define PDRVCTL0_MINNOV_Msk (0x3UL << PDRVCTL0_MINNOV_Pos)

#define PDRVCTL0_MINNOV_350NS          ((0x0UL) << PDRVCTL0_MINNOV_Pos)
#define PDRVCTL0_MINNOV_750NS          ((0x1UL) << PDRVCTL0_MINNOV_Pos)
#define PDRVCTL0_MINNOV_1550NS         ((0x2UL) << PDRVCTL0_MINNOV_Pos)
#define PDRVCTL0_MINNOV_3150NS         ((0x3UL) << PDRVCTL0_MINNOV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        OCTH
 *  @access     HV->PDRVCTL0
 *  @brief      Over current detection threshold.
 *              It is via monitoring the Vds of external FET, and the threshold is Vds/Rdson, where
 *              Rdson is the on resistance of the external FET.
 */
#define PDRVCTL0_OCTH_Pos (4UL)
#define PDRVCTL0_OCTH_Msk (0xFUL << PDRVCTL0_OCTH_Pos)

#define PDRVCTL0_OCTH_0P15V_DIV_RDSON         ((0x00UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_0P30V_DIV_RDSON         ((0x01UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_0P45V_DIV_RDSON         ((0x02UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_0P60V_DIV_RDSON         ((0x03UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_0P75V_DIV_RDSON         ((0x04UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_0P90V_DIV_RDSON         ((0x05UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P05V_DIV_RDSON         ((0x06UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P20V_DIV_RDSON         ((0x07UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P35V_DIV_RDSON         ((0x08UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P50V_DIV_RDSON         ((0x09UL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P65V_DIV_RDSON         ((0x0AUL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P80V_DIV_RDSON         ((0x0BUL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_1P95V_DIV_RDSON         ((0x0CUL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_2P10V_DIV_RDSON         ((0x0DUL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_2P25V_DIV_RDSON         ((0x0EUL) << PDRVCTL0_OCTH_Pos)
#define PDRVCTL0_OCTH_2P40V_DIV_RDSON         ((0x0FUL) << PDRVCTL0_OCTH_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        DGCLKDIV
 *  @access     HV->PDRVCTL0
 *  @brief      Vds monitor deglitch clock dividing ratio.
 *              The blanking and filtering windows are scaled up accordingly
 */
#define PDRVCTL0_DGCLKDIV_Pos (8UL)
#define PDRVCTL0_DGCLKDIV_Msk (0x3UL << PDRVCTL0_DGCLKDIV_Pos)

#define PDRVCTL0_DGCLKDIV_1         ((0x0UL) << PDRVCTL0_DGCLKDIV_Pos)
#define PDRVCTL0_DGCLKDIV_2         ((0x1UL) << PDRVCTL0_DGCLKDIV_Pos)
#define PDRVCTL0_DGCLKDIV_4         ((0x2UL) << PDRVCTL0_DGCLKDIV_Pos)
#define PDRVCTL0_DGCLKDIV_8         ((0x3UL) << PDRVCTL0_DGCLKDIV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        BLANKWIN
 *  @access     HV->PDRVCTL0
 *  @brief      Vds monitor blanking window size
 */
#define PDRVCTL0_BLANKWIN_Pos (10UL)
#define PDRVCTL0_BLANKWIN_Msk (0x3UL << PDRVCTL0_BLANKWIN_Pos)

#define PDRVCTL0_BLANKWIN_800NS          ((0x0UL) << PDRVCTL0_BLANKWIN_Pos)
#define PDRVCTL0_BLANKWIN_1600NS         ((0x1UL) << PDRVCTL0_BLANKWIN_Pos)
#define PDRVCTL0_BLANKWIN_3200NS         ((0x2UL) << PDRVCTL0_BLANKWIN_Pos)
#define PDRVCTL0_BLANKWIN_6400NS         ((0x3UL) << PDRVCTL0_BLANKWIN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL0        FILTERWIN
 *  @access     HV->PDRVCTL0
 *  @brief      Vds monitor deglitch filter window size
 */
#define PDRVCTL0_FILTERWIN_Pos (12UL)
#define PDRVCTL0_FILTERWIN_Msk (0x3UL << PDRVCTL0_FILTERWIN_Pos)

#define PDRVCTL0_FILTERWIN_800NS          ((0x0UL) << PDRVCTL0_FILTERWIN_Pos)
#define PDRVCTL0_FILTERWIN_1600NS         ((0x1UL) << PDRVCTL0_FILTERWIN_Pos)
#define PDRVCTL0_FILTERWIN_3200NS         ((0x2UL) << PDRVCTL0_FILTERWIN_Pos)
#define PDRVCTL0_FILTERWIN_6400NS         ((0x3UL) << PDRVCTL0_FILTERWIN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        VCPLVL
 *  @access     HV->PDRVCTL1
 *  @brief      VCP level above VBAT
 */
#define PDRVCTL1_VCPLVL_Pos (0UL)
#define PDRVCTL1_VCPLVL_Msk (0x7UL << PDRVCTL1_VCPLVL_Pos)

#define PDRVCTL1_VCPLVL_9P7V          ((0x0UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_10P1V         ((0x1UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_10P7V         ((0x2UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_11P4V         ((0x3UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_12P0V         ((0x4UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_12P8V         ((0x5UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_13P5V         ((0x6UL) << PDRVCTL1_VCPLVL_Pos)
#define PDRVCTL1_VCPLVL_14P4V         ((0x7UL) << PDRVCTL1_VCPLVL_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        LSVGS
 *  @access     HV->PDRVCTL1
 *  @brief      Pre-driver low-side Vgs select
 */
#define PDRVCTL1_LSVGS_Pos (3UL)
#define PDRVCTL1_LSVGS_Msk (0x7UL << PDRVCTL1_LSVGS_Pos)

#define PDRVCTL1_LSVGS_8P15V         ((0x0UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_8P5V          ((0x1UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_8P9V          ((0x2UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_9P3V          ((0x3UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_9P6V          ((0x4UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_10P0V         ((0x5UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_10P4V         ((0x6UL) << PDRVCTL1_LSVGS_Pos)
#define PDRVCTL1_LSVGS_11P4V         ((0x7UL) << PDRVCTL1_LSVGS_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        STATICSTR
 *  @access     HV->PDRVCTL1
 *  @brief      Static pull-up and pull-down strength when not switch
 */
#define PDRVCTL1_STATICSTR_Pos (6UL)
#define PDRVCTL1_STATICSTR_Msk (0x1FUL << PDRVCTL1_STATICSTR_Pos)

#define PDRVCTL1_STATICSTR_(x) ((x) << PDRVCTL1_STATICSTR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        SSMODE
 *  @access     HV->PDRVCTL1
 *  @brief      Dithering mode on charge-pump clock for spread spectrum
 */
#define PDRVCTL1_SSMODE_Pos (11UL)
#define PDRVCTL1_SSMODE_Msk (0x3UL << PDRVCTL1_SSMODE_Pos)

#define PDRVCTL1_SSMODE_FIXED_DIV              ((0x0UL) << PDRVCTL1_SSMODE_Pos)
#define PDRVCTL1_SSMODE_DIV8_OR_DIV16          ((0x1UL) << PDRVCTL1_SSMODE_Pos)
#define PDRVCTL1_SSMODE_DIV16_OR_DIV32         ((0x2UL) << PDRVCTL1_SSMODE_Pos)
#define PDRVCTL1_SSMODE_DIV32_OR_DIV64         ((0x3UL) << PDRVCTL1_SSMODE_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        SSPRD
 *  @access     HV->PDRVCTL1
 *  @brief      Dithering period on charge-pump clock for spread spectrum
 */
#define PDRVCTL1_SSPRD_Pos (13UL)
#define PDRVCTL1_SSPRD_Msk (0x1UL << PDRVCTL1_SSPRD_Pos)

#define PDRVCTL1_SSPRD_256X         ((0x0UL) << PDRVCTL1_SSPRD_Pos)
#define PDRVCTL1_SSPRD_512X         ((0x1UL) << PDRVCTL1_SSPRD_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        MEADLYMODE
 *  @access     HV->PDRVCTL1
 *  @brief      Pre-driver path delay measurement end point mode
 */
#define PDRVCTL1_MEADLYMODE_Pos (14UL)
#define PDRVCTL1_MEADLYMODE_Msk (0x1UL << PDRVCTL1_MEADLYMODE_Pos)

#define PDRVCTL1_MEADLYMODE_OTHER_SIDE_OC_RISE         ((0x0UL) << PDRVCTL1_MEADLYMODE_Pos)
#define PDRVCTL1_MEADLYMODE_SAME_SIDE_OC_FALL          ((0x1UL) << PDRVCTL1_MEADLYMODE_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVCTL1        MEADLYEN
 *  @access     HV->PDRVCTL1
 *  @brief      Pre-driver path delay measurement enable
 */
#define PDRVCTL1_MEADLYEN_Pos (15UL)
#define PDRVCTL1_MEADLYEN_Msk (0x1UL << PDRVCTL1_MEADLYEN_Pos)

#define PDRVCTL1_MEADLYEN_DISABLE         ((0x0UL) << PDRVCTL1_MEADLYEN_Pos)
#define PDRVCTL1_MEADLYEN_ENABLE          ((0x1UL) << PDRVCTL1_MEADLYEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDSTR0    STRENTH0
 *  @access     HV->PDRVLSPDSTR0
 *  @brief      Pull-down strength for time segment 0, which is 10mA*(code+1)
 */
#define PDRVLSPDSTR0_STRENTH0_Pos (0UL)
#define PDRVLSPDSTR0_STRENTH0_Msk (0x1FUL << PDRVLSPDSTR0_STRENTH0_Pos)

#define PDRVLSPDSTR0_STRENTH0_(x) ((x) << PDRVLSPDSTR0_STRENTH0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDSTR0    STRENTH1
 *  @access     HV->PDRVLSPDSTR0
 *  @brief      Pull-down strength for time segment 1, which is 10mA*(code+1)
 */
#define PDRVLSPDSTR0_STRENTH1_Pos (8UL)
#define PDRVLSPDSTR0_STRENTH1_Msk (0x1FUL << PDRVLSPDSTR0_STRENTH1_Pos)

#define PDRVLSPDSTR0_STRENTH1_(x) ((x) << PDRVLSPDSTR0_STRENTH1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDSTR1    STRENTH2
 *  @access     HV->PDRVLSPDSTR1
 *  @brief      Pull-down strength for time segment 2, which is 10mA*(code+1)
 */
#define PDRVLSPDSTR1_STRENTH2_Pos (0UL)
#define PDRVLSPDSTR1_STRENTH2_Msk (0x1FUL << PDRVLSPDSTR1_STRENTH2_Pos)

#define PDRVLSPDSTR1_STRENTH2_(x) ((x) << PDRVLSPDSTR1_STRENTH2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDSTR1    STRENTH3
 *  @access     HV->PDRVLSPDSTR1
 *  @brief      Pull-down strength for time segment 3, which is 10mA*(code+1)
 */
#define PDRVLSPDSTR1_STRENTH3_Pos (8UL)
#define PDRVLSPDSTR1_STRENTH3_Msk (0x1FUL << PDRVLSPDSTR1_STRENTH3_Pos)

#define PDRVLSPDSTR1_STRENTH3_(x) ((x) << PDRVLSPDSTR1_STRENTH3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPUSTR0    STRENTH0
 *  @access     HV->PDRVLSPUSTR0
 *  @brief      Pull-up strength for time segment 0, which is 10mA*(code+1)
 */
#define PDRVLSPUSTR0_STRENTH0_Pos (0UL)
#define PDRVLSPUSTR0_STRENTH0_Msk (0x1FUL << PDRVLSPUSTR0_STRENTH0_Pos)

#define PDRVLSPUSTR0_STRENTH0_(x) ((x) << PDRVLSPUSTR0_STRENTH0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPUSTR0    STRENTH1
 *  @access     HV->PDRVLSPUSTR0
 *  @brief      Pull-up strength for time segment 1, which is 10mA*(code+1)
 */
#define PDRVLSPUSTR0_STRENTH1_Pos (8UL)
#define PDRVLSPUSTR0_STRENTH1_Msk (0x1FUL << PDRVLSPUSTR0_STRENTH1_Pos)

#define PDRVLSPUSTR0_STRENTH1_(x) ((x) << PDRVLSPUSTR0_STRENTH1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPUSTR1    STRENTH2
 *  @access     HV->PDRVLSPUSTR1
 *  @brief      Pull-up strength for time segment 2, which is 10mA*(code+1)
 */
#define PDRVLSPUSTR1_STRENTH2_Pos (0UL)
#define PDRVLSPUSTR1_STRENTH2_Msk (0x1FUL << PDRVLSPUSTR1_STRENTH2_Pos)

#define PDRVLSPUSTR1_STRENTH2_(x) ((x) << PDRVLSPUSTR1_STRENTH2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPUSTR1    STRENTH3
 *  @access     HV->PDRVLSPUSTR1
 *  @brief      Pull-up strength for time segment 3, which is 10mA*(code+1)
 */
#define PDRVLSPUSTR1_STRENTH3_Pos (8UL)
#define PDRVLSPUSTR1_STRENTH3_Msk (0x1FUL << PDRVLSPUSTR1_STRENTH3_Pos)

#define PDRVLSPUSTR1_STRENTH3_(x) ((x) << PDRVLSPUSTR1_STRENTH3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDSTR0    STRENTH0
 *  @access     HV->PDRVHSPDSTR0
 *  @brief      Pull-down strength for time segment 0, which is 10mA*(code+1)
 */
#define PDRVHSPDSTR0_STRENTH0_Pos (0UL)
#define PDRVHSPDSTR0_STRENTH0_Msk (0x1FUL << PDRVHSPDSTR0_STRENTH0_Pos)

#define PDRVHSPDSTR0_STRENTH0_(x) ((x) << PDRVHSPDSTR0_STRENTH0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDSTR0    STRENTH1
 *  @access     HV->PDRVHSPDSTR0
 *  @brief      Pull-down strength for time segment 1, which is 10mA*(code+1)
 */
#define PDRVHSPDSTR0_STRENTH1_Pos (8UL)
#define PDRVHSPDSTR0_STRENTH1_Msk (0x1FUL << PDRVHSPDSTR0_STRENTH1_Pos)

#define PDRVHSPDSTR0_STRENTH1_(x) ((x) << PDRVHSPDSTR0_STRENTH1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDSTR1    STRENTH2
 *  @access     HV->PDRVHSPDSTR1
 *  @brief      Pull-down strength for time segment 2, which is 10mA*(code+1)
 */
#define PDRVHSPDSTR1_STRENTH2_Pos (0UL)
#define PDRVHSPDSTR1_STRENTH2_Msk (0x1FUL << PDRVHSPDSTR1_STRENTH2_Pos)

#define PDRVHSPDSTR1_STRENTH2_(x) ((x) << PDRVHSPDSTR1_STRENTH2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDSTR1    STRENTH3
 *  @access     HV->PDRVHSPDSTR1
 *  @brief      Pull-down strength for time segment 3, which is 10mA*(code+1)
 */
#define PDRVHSPDSTR1_STRENTH3_Pos (8UL)
#define PDRVHSPDSTR1_STRENTH3_Msk (0x1FUL << PDRVHSPDSTR1_STRENTH3_Pos)

#define PDRVHSPDSTR1_STRENTH3_(x) ((x) << PDRVHSPDSTR1_STRENTH3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPUSTR0    STRENTH0
 *  @access     HV->PDRVHSPUSTR0
 *  @brief      Pull-up strength for time segment 0, which is 10mA*(code+1)
 */
#define PDRVHSPUSTR0_STRENTH0_Pos (0UL)
#define PDRVHSPUSTR0_STRENTH0_Msk (0x1FUL << PDRVHSPUSTR0_STRENTH0_Pos)

#define PDRVHSPUSTR0_STRENTH0_(x) ((x) << PDRVHSPUSTR0_STRENTH0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPUSTR0    STRENTH1
 *  @access     HV->PDRVHSPUSTR0
 *  @brief      Pull-up strength for time segment 1, which is 10mA*(code+1)
 */
#define PDRVHSPUSTR0_STRENTH1_Pos (8UL)
#define PDRVHSPUSTR0_STRENTH1_Msk (0x1FUL << PDRVHSPUSTR0_STRENTH1_Pos)

#define PDRVHSPUSTR0_STRENTH1_(x) ((x) << PDRVHSPUSTR0_STRENTH1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPUSTR1    STRENTH2
 *  @access     HV->PDRVHSPUSTR1
 *  @brief      Pull-up strength for time segment 2, which is 10mA*(code+1)
 */
#define PDRVHSPUSTR1_STRENTH2_Pos (0UL)
#define PDRVHSPUSTR1_STRENTH2_Msk (0x1FUL << PDRVHSPUSTR1_STRENTH2_Pos)

#define PDRVHSPUSTR1_STRENTH2_(x) ((x) << PDRVHSPUSTR1_STRENTH2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPUSTR1    STRENTH3
 *  @access     HV->PDRVHSPUSTR1
 *  @brief      Pull-up strength for time segment 3, which is 10mA*(code+1)
 */
#define PDRVHSPUSTR1_STRENTH3_Pos (8UL)
#define PDRVHSPUSTR1_STRENTH3_Msk (0x1FUL << PDRVHSPUSTR1_STRENTH3_Pos)

#define PDRVHSPUSTR1_STRENTH3_(x) ((x) << PDRVHSPUSTR1_STRENTH3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDLEN     LEN0
 *  @access     HV->PDRVLSPDLEN
 *  @brief      Pull-down time segment 0 length, which is 25ns*code
 */
#define PDRVLSPDLEN_LEN0_Pos (0UL)
#define PDRVLSPDLEN_LEN0_Msk (0xFUL << PDRVLSPDLEN_LEN0_Pos)

#define PDRVLSPDLEN_LEN0_(x) ((x) << PDRVLSPDLEN_LEN0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDLEN     LEN1
 *  @access     HV->PDRVLSPDLEN
 *  @brief      Pull-down time segment 1 length, which is 25ns*code
 */
#define PDRVLSPDLEN_LEN1_Pos (4UL)
#define PDRVLSPDLEN_LEN1_Msk (0xFUL << PDRVLSPDLEN_LEN1_Pos)

#define PDRVLSPDLEN_LEN1_(x) ((x) << PDRVLSPDLEN_LEN1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDLEN     LEN2
 *  @access     HV->PDRVLSPDLEN
 *  @brief      Pull-down time segment 2 length, which is 25ns*code
 */
#define PDRVLSPDLEN_LEN2_Pos (8UL)
#define PDRVLSPDLEN_LEN2_Msk (0xFUL << PDRVLSPDLEN_LEN2_Pos)

#define PDRVLSPDLEN_LEN2_(x) ((x) << PDRVLSPDLEN_LEN2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPDLEN     LEN3
 *  @access     HV->PDRVLSPDLEN
 *  @brief      Pull-down time segment 3 length, which is 25ns*code
 */
#define PDRVLSPDLEN_LEN3_Pos (12UL)
#define PDRVLSPDLEN_LEN3_Msk (0xFUL << PDRVLSPDLEN_LEN3_Pos)

#define PDRVLSPDLEN_LEN3_(x) ((x) << PDRVLSPDLEN_LEN3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPULEN     LEN0
 *  @access     HV->PDRVLSPULEN
 *  @brief      Pull-up time segment 0 length, which is 25ns*code
 */
#define PDRVLSPULEN_LEN0_Pos (0UL)
#define PDRVLSPULEN_LEN0_Msk (0xFUL << PDRVLSPULEN_LEN0_Pos)

#define PDRVLSPULEN_LEN0_(x) ((x) << PDRVLSPULEN_LEN0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPULEN     LEN1
 *  @access     HV->PDRVLSPULEN
 *  @brief      Pull-up time segment 1 length, which is 25ns*code
 */
#define PDRVLSPULEN_LEN1_Pos (4UL)
#define PDRVLSPULEN_LEN1_Msk (0xFUL << PDRVLSPULEN_LEN1_Pos)

#define PDRVLSPULEN_LEN1_(x) ((x) << PDRVLSPULEN_LEN1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPULEN     LEN2
 *  @access     HV->PDRVLSPULEN
 *  @brief      Pull-up time segment 2 length, which is 25ns*code
 */
#define PDRVLSPULEN_LEN2_Pos (8UL)
#define PDRVLSPULEN_LEN2_Msk (0xFUL << PDRVLSPULEN_LEN2_Pos)

#define PDRVLSPULEN_LEN2_(x) ((x) << PDRVLSPULEN_LEN2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVLSPULEN     LEN3
 *  @access     HV->PDRVLSPULEN
 *  @brief      Pull-up time segment 3 length, which is 25ns*code
 */
#define PDRVLSPULEN_LEN3_Pos (12UL)
#define PDRVLSPULEN_LEN3_Msk (0xFUL << PDRVLSPULEN_LEN3_Pos)

#define PDRVLSPULEN_LEN3_(x) ((x) << PDRVLSPULEN_LEN3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDLEN     LEN0
 *  @access     HV->PDRVHSPDLEN
 *  @brief      Pull-down time segment 0 length, which is 25ns*code
 */
#define PDRVHSPDLEN_LEN0_Pos (0UL)
#define PDRVHSPDLEN_LEN0_Msk (0xFUL << PDRVHSPDLEN_LEN0_Pos)

#define PDRVHSPDLEN_LEN0_(x) ((x) << PDRVHSPDLEN_LEN0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDLEN     LEN1
 *  @access     HV->PDRVHSPDLEN
 *  @brief      Pull-down time segment 1 length, which is 25ns*code
 */
#define PDRVHSPDLEN_LEN1_Pos (4UL)
#define PDRVHSPDLEN_LEN1_Msk (0xFUL << PDRVHSPDLEN_LEN1_Pos)

#define PDRVHSPDLEN_LEN1_(x) ((x) << PDRVHSPDLEN_LEN1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDLEN     LEN2
 *  @access     HV->PDRVHSPDLEN
 *  @brief      Pull-down time segment 2 length, which is 25ns*code
 */
#define PDRVHSPDLEN_LEN2_Pos (8UL)
#define PDRVHSPDLEN_LEN2_Msk (0xFUL << PDRVHSPDLEN_LEN2_Pos)

#define PDRVHSPDLEN_LEN2_(x) ((x) << PDRVHSPDLEN_LEN2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPDLEN     LEN3
 *  @access     HV->PDRVHSPDLEN
 *  @brief      Pull-down time segment 3 length, which is 25ns*code
 */
#define PDRVHSPDLEN_LEN3_Pos (12UL)
#define PDRVHSPDLEN_LEN3_Msk (0xFUL << PDRVHSPDLEN_LEN3_Pos)

#define PDRVHSPDLEN_LEN3_(x) ((x) << PDRVHSPDLEN_LEN3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPULEN     LEN0
 *  @access     HV->PDRVHSPULEN
 *  @brief      Pull-up time segment 0 length, which is 25ns*code
 */
#define PDRVHSPULEN_LEN0_Pos (0UL)
#define PDRVHSPULEN_LEN0_Msk (0xFUL << PDRVHSPULEN_LEN0_Pos)

#define PDRVHSPULEN_LEN0_(x) ((x) << PDRVHSPULEN_LEN0_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPULEN     LEN1
 *  @access     HV->PDRVHSPULEN
 *  @brief      Pull-up time segment 1 length, which is 25ns*code
 */
#define PDRVHSPULEN_LEN1_Pos (4UL)
#define PDRVHSPULEN_LEN1_Msk (0xFUL << PDRVHSPULEN_LEN1_Pos)

#define PDRVHSPULEN_LEN1_(x) ((x) << PDRVHSPULEN_LEN1_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPULEN     LEN2
 *  @access     HV->PDRVHSPULEN
 *  @brief      Pull-up time segment 2 length, which is 25ns*code
 */
#define PDRVHSPULEN_LEN2_Pos (8UL)
#define PDRVHSPULEN_LEN2_Msk (0xFUL << PDRVHSPULEN_LEN2_Pos)

#define PDRVHSPULEN_LEN2_(x) ((x) << PDRVHSPULEN_LEN2_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVHSPULEN     LEN3
 *  @access     HV->PDRVHSPULEN
 *  @brief      Pull-up time segment 3 length, which is 25ns*code
 */
#define PDRVHSPULEN_LEN3_Pos (12UL)
#define PDRVHSPULEN_LEN3_Msk (0xFUL << PDRVHSPULEN_LEN3_Pos)

#define PDRVHSPULEN_LEN3_(x) ((x) << PDRVHSPULEN_LEN3_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVDLYU        LSDLY
 *  @access     HV->PDRVDLYU
 *  @brief      Low-side measured turn-on delay, which is LSDLY*25ns
 */
#define PDRVDLYU_LSDLY_Pos (0UL)
#define PDRVDLYU_LSDLY_Msk (0xFFUL << PDRVDLYU_LSDLY_Pos)

#define PDRVDLYU_LSDLY_(x) ((x) << PDRVDLYU_LSDLY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVDLYU        HSDLY
 *  @access     HV->PDRVDLYU
 *  @brief      High-side measured turn-on delay, which is HSDLY*25ns
 */
#define PDRVDLYU_HSDLY_Pos (8UL)
#define PDRVDLYU_HSDLY_Msk (0xFFUL << PDRVDLYU_HSDLY_Pos)

#define PDRVDLYU_HSDLY_(x) ((x) << PDRVDLYU_HSDLY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVDLYV        LSDLY
 *  @access     HV->PDRVDLYV
 *  @brief      Low-side measured turn-on delay, which is LSDLY*25ns
 */
#define PDRVDLYV_LSDLY_Pos (0UL)
#define PDRVDLYV_LSDLY_Msk (0xFFUL << PDRVDLYV_LSDLY_Pos)

#define PDRVDLYV_LSDLY_(x) ((x) << PDRVDLYV_LSDLY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVDLYV        HSDLY
 *  @access     HV->PDRVDLYV
 *  @brief      High-side measured turn-on delay, which is HSDLY*25ns
 */
#define PDRVDLYV_HSDLY_Pos (8UL)
#define PDRVDLYV_HSDLY_Msk (0xFFUL << PDRVDLYV_HSDLY_Pos)

#define PDRVDLYV_HSDLY_(x) ((x) << PDRVDLYV_HSDLY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVDLYW        LSDLY
 *  @access     HV->PDRVDLYW
 *  @brief      Low-side measured turn-on delay, which is LSDLY*25ns
 */
#define PDRVDLYW_LSDLY_Pos (0UL)
#define PDRVDLYW_LSDLY_Msk (0xFFUL << PDRVDLYW_LSDLY_Pos)

#define PDRVDLYW_LSDLY_(x) ((x) << PDRVDLYW_LSDLY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              PDRVDLYW        HSDLY
 *  @access     HV->PDRVDLYW
 *  @brief      High-side measured turn-on delay, which is HSDLY*25ns
 */
#define PDRVDLYW_HSDLY_Pos (8UL)
#define PDRVDLYW_HSDLY_Msk (0xFFUL << PDRVDLYW_HSDLY_Pos)

#define PDRVDLYW_HSDLY_(x) ((x) << PDRVDLYW_HSDLY_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINCTL          EN
 *  @access     HV->LINCTL
 *  @brief      LIN enable
 *              This bit should be written as 1 when enable transmitter and over-temperature detect
 *              function
 */
#define LINCTL_EN_Pos (0UL)
#define LINCTL_EN_Msk (0x1UL << LINCTL_EN_Pos)

#define LINCTL_EN_DISABLE         ((0x0UL) << LINCTL_EN_Pos)
#define LINCTL_EN_ENABLE          ((0x1UL) << LINCTL_EN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINCTL          TXEN
 *  @access     HV->LINCTL
 *  @brief      LIN transmmiter enable
 *              This bit will be automatically cleared as 0 if EN bit is written as 0 or the events
 *              as selected in LINTXPDEVTEN register happens
 */
#define LINCTL_TXEN_Pos (1UL)
#define LINCTL_TXEN_Msk (0x1UL << LINCTL_TXEN_Pos)

#define LINCTL_TXEN_DISABLE         ((0x0UL) << LINCTL_TXEN_Pos)
#define LINCTL_TXEN_ENABLE          ((0x1UL) << LINCTL_TXEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINCTL          OTEN
 *  @access     HV->LINCTL
 *  @brief      LIN over-temperature detect enable
 *              This bit will be automatically cleared as 0 if EN bit is written as 0
 */
#define LINCTL_OTEN_Pos (2UL)
#define LINCTL_OTEN_Msk (0x1UL << LINCTL_OTEN_Pos)

#define LINCTL_OTEN_DISABLE         ((0x0UL) << LINCTL_OTEN_Pos)
#define LINCTL_OTEN_ENABLE          ((0x1UL) << LINCTL_OTEN_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINCTL          OTTH
 *  @access     HV->LINCTL
 *  @brief      LIN over-temperature threshold
 */
#define LINCTL_OTTH_Pos (3UL)
#define LINCTL_OTTH_Msk (0x7UL << LINCTL_OTTH_Pos)

#define LINCTL_OTTH_129C         ((0x0UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_137C         ((0x1UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_145C         ((0x2UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_153C         ((0x3UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_161C         ((0x4UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_170C         ((0x5UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_178C         ((0x6UL) << LINCTL_OTTH_Pos)
#define LINCTL_OTTH_186C         ((0x7UL) << LINCTL_OTTH_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINCTL          TXSLOPE
 *  @access     HV->LINCTL
 *  @brief      LIN tranmitter output slope control.
 *              This bit determines the transient time between VBAT and ground for the LIN bus during
 *              transmission.
 */
#define LINCTL_TXSLOPE_Pos (6UL)
#define LINCTL_TXSLOPE_Msk (0xFUL << LINCTL_TXSLOPE_Pos)

#define LINCTL_TXSLOPE_25P0US         ((0x00UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_23P5US         ((0x01UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_22P0US         ((0x02UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_20P5US         ((0x03UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_19P0US         ((0x04UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_17P5US         ((0x05UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_16P0US         ((0x06UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_14P5US         ((0x07UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_13P0US         ((0x08UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_11P5US         ((0x09UL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_10P0US         ((0x0AUL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_8P5US          ((0x0BUL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_7PUS           ((0x0CUL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_5P5US          ((0x0DUL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_4P0US          ((0x0EUL) << LINCTL_TXSLOPE_Pos)
#define LINCTL_TXSLOPE_2P5US          ((0x0FUL) << LINCTL_TXSLOPE_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINCTL          STRENGTH
 *  @access     HV->LINCTL
 *  @brief      LIN transmitter pull-down driving strength for VBAT=12V
 */
#define LINCTL_STRENGTH_Pos (10UL)
#define LINCTL_STRENGTH_Msk (0x3UL << LINCTL_STRENGTH_Pos)

#define LINCTL_STRENGTH_39P8MA         ((0x0UL) << LINCTL_STRENGTH_Pos)
#define LINCTL_STRENGTH_47P2MA         ((0x1UL) << LINCTL_STRENGTH_Pos)
#define LINCTL_STRENGTH_58P1MA         ((0x2UL) << LINCTL_STRENGTH_Pos)
#define LINCTL_STRENGTH_75P3MA         ((0x3UL) << LINCTL_STRENGTH_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    VBATUV
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon VBAT under-voltage event
 */
#define LINTXPDEVTEN_VBATUV_Pos (0UL)
#define LINTXPDEVTEN_VBATUV_Msk (0x1UL << LINTXPDEVTEN_VBATUV_Pos)

#define LINTXPDEVTEN_VBATUV_DISABLE         ((0x0UL) << LINTXPDEVTEN_VBATUV_Pos)
#define LINTXPDEVTEN_VBATUV_ENABLE          ((0x1UL) << LINTXPDEVTEN_VBATUV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    VDD5UV
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon VDD5 under-voltage event
 */
#define LINTXPDEVTEN_VDD5UV_Pos (1UL)
#define LINTXPDEVTEN_VDD5UV_Msk (0x1UL << LINTXPDEVTEN_VDD5UV_Pos)

#define LINTXPDEVTEN_VDD5UV_DISABLE         ((0x0UL) << LINTXPDEVTEN_VDD5UV_Pos)
#define LINTXPDEVTEN_VDD5UV_ENABLE          ((0x1UL) << LINTXPDEVTEN_VDD5UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    VDD3UV
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon VDD3 under-voltage event
 */
#define LINTXPDEVTEN_VDD3UV_Pos (2UL)
#define LINTXPDEVTEN_VDD3UV_Msk (0x1UL << LINTXPDEVTEN_VDD3UV_Pos)

#define LINTXPDEVTEN_VDD3UV_DISABLE         ((0x0UL) << LINTXPDEVTEN_VDD3UV_Pos)
#define LINTXPDEVTEN_VDD3UV_ENABLE          ((0x1UL) << LINTXPDEVTEN_VDD3UV_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    VDD5OC
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon VDD5 over-current event
 */
#define LINTXPDEVTEN_VDD5OC_Pos (3UL)
#define LINTXPDEVTEN_VDD5OC_Msk (0x1UL << LINTXPDEVTEN_VDD5OC_Pos)

#define LINTXPDEVTEN_VDD5OC_DISABLE         ((0x0UL) << LINTXPDEVTEN_VDD5OC_Pos)
#define LINTXPDEVTEN_VDD5OC_ENABLE          ((0x1UL) << LINTXPDEVTEN_VDD5OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    VDD3OC
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon VDD3 over-current event
 */
#define LINTXPDEVTEN_VDD3OC_Pos (4UL)
#define LINTXPDEVTEN_VDD3OC_Msk (0x1UL << LINTXPDEVTEN_VDD3OC_Pos)

#define LINTXPDEVTEN_VDD3OC_DISABLE         ((0x0UL) << LINTXPDEVTEN_VDD3OC_Pos)
#define LINTXPDEVTEN_VDD3OC_ENABLE          ((0x1UL) << LINTXPDEVTEN_VDD3OC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    LPRCOERR
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon LPRCO error event
 */
#define LINTXPDEVTEN_LPRCOERR_Pos (5UL)
#define LINTXPDEVTEN_LPRCOERR_Msk (0x1UL << LINTXPDEVTEN_LPRCOERR_Pos)

#define LINTXPDEVTEN_LPRCOERR_DISABLE         ((0x0UL) << LINTXPDEVTEN_LPRCOERR_Pos)
#define LINTXPDEVTEN_LPRCOERR_ENABLE          ((0x1UL) << LINTXPDEVTEN_LPRCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    RCOERR
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon RCO error event
 */
#define LINTXPDEVTEN_RCOERR_Pos (6UL)
#define LINTXPDEVTEN_RCOERR_Msk (0x1UL << LINTXPDEVTEN_RCOERR_Pos)

#define LINTXPDEVTEN_RCOERR_DISABLE         ((0x0UL) << LINTXPDEVTEN_RCOERR_Pos)
#define LINTXPDEVTEN_RCOERR_ENABLE          ((0x1UL) << LINTXPDEVTEN_RCOERR_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    LINTXDTIMEOUT
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon LIN TXD timeout event
 */
#define LINTXPDEVTEN_LINTXDTIMEOUT_Pos (7UL)
#define LINTXPDEVTEN_LINTXDTIMEOUT_Msk (0x1UL << LINTXPDEVTEN_LINTXDTIMEOUT_Pos)

#define LINTXPDEVTEN_LINTXDTIMEOUT_DISABLE         ((0x0UL) << LINTXPDEVTEN_LINTXDTIMEOUT_Pos)
#define LINTXPDEVTEN_LINTXDTIMEOUT_ENABLE          ((0x1UL) << LINTXPDEVTEN_LINTXDTIMEOUT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    LINOC
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon LIN over-current event
 */
#define LINTXPDEVTEN_LINOC_Pos (8UL)
#define LINTXPDEVTEN_LINOC_Msk (0x1UL << LINTXPDEVTEN_LINOC_Pos)

#define LINTXPDEVTEN_LINOC_DISABLE         ((0x0UL) << LINTXPDEVTEN_LINOC_Pos)
#define LINTXPDEVTEN_LINOC_ENABLE          ((0x1UL) << LINTXPDEVTEN_LINOC_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              LINTXPDEVTEN    LINOT
 *  @access     HV->LINTXPDEVTEN
 *  @brief      Shut down LIN transmitter upon LIN over-temperature event
 */
#define LINTXPDEVTEN_LINOT_Pos (9UL)
#define LINTXPDEVTEN_LINOT_Msk (0x1UL << LINTXPDEVTEN_LINOT_Pos)

#define LINTXPDEVTEN_LINOT_DISABLE         ((0x0UL) << LINTXPDEVTEN_LINOT_Pos)
#define LINTXPDEVTEN_LINOT_ENABLE          ((0x1UL) << LINTXPDEVTEN_LINOT_Pos)



/**
 *  @hierarchy       Module          Register        Bitfield
 *                   HV              CTLKEY          KEY
 *  @access     HV->CTLKEY
 *  @brief      Control Key
 *              Write as 0x6666 to enable sotware reset command
 *              Write as 0x7777 to enable write on registers highlighted in red
 *              Write as 0x8888 to enable write on registers highlighted in blue
 *              Write as 0x9999 to enable sleep/stop command
 */
#define CTLKEY_KEY_Pos (0UL)
#define CTLKEY_KEY_Msk (0xFFFFUL << CTLKEY_KEY_Pos)

#define CTLKEY_KEY_(x) ((x) << CTLKEY_KEY_Pos)



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* HV_BITFIELD_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
