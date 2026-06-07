/*******************************************************************************
 * @file     hv.h
 * @brief    High voltage module header file.
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

#ifndef HV_H
#define HV_H

#ifdef __cplusplus
extern "C" {
#endif


#include "epwr.h"
#include "spd1179_hv_bitfield.h"




/**
 *  @brief  High Voltage Module Register Address Definition
 */
typedef enum
{
    HV_REG_SYSEVTFLG              = 0x00,     /*!< System Event Flag Register                             */
    HV_REG_SYSEVTFLGCLR           = 0x01,     /*!< System Event Flag Clear Register                       */
    HV_REG_PMUCTL                 = 0x02,     /*!< PMU Control Register                                   */
    HV_REG_PMUSTS                 = 0x03,     /*!< PMU Status Register                                    */
    HV_REG_CYCSENSECTL            = 0x04,     /*!< Cyclic Sense Control Register                          */
    HV_REG_CYCWKUPCTL             = 0x05,     /*!< Cyclic Wakeup Control Register                         */
    HV_REG_MONCTL                 = 0x06,     /*!< MON Control Register                                   */
    HV_REG_TZEVTSTS0              = 0x07,     /*!< Trip-Zone Event Status Register 0                      */
    HV_REG_TZEVTSTS1              = 0x08,     /*!< Trip-Zone Event Status Register 1                      */
    HV_REG_TZIE0                  = 0x09,     /*!< Trip-Zone Interrupt Enable Register 0                  */
    HV_REG_TZIC0                  = 0x0A,     /*!< Trip-Zone Interrupt Clear Register 0                   */
    HV_REG_TZIF0                  = 0x0B,     /*!< Trip-Zone Interrupt Flag Register 0                    */
    HV_REG_TZIE1                  = 0x0C,     /*!< Trip-Zone Interrupt Enable Register 1                  */
    HV_REG_TZIC1                  = 0x0D,     /*!< Trip-Zone Interrupt Clear Register 1                   */
    HV_REG_TZIF1                  = 0x0E,     /*!< Trip-Zone Interrupt Flag Register 1                    */
    HV_REG_EVTTHCTL0              = 0x0F,     /*!< Event Threshold Control Register 0                     */
    HV_REG_EVTTHCTL1              = 0x10,     /*!< Event Threshold Control Register 1                     */
    HV_REG_PDRVCTL0               = 0x11,     /*!< Pre-Driver Control Register 0                          */
    HV_REG_PDRVCTL1               = 0x12,     /*!< Pre-Driver Control Register 1                          */
    HV_REG_PDRVLSPDSTR0           = 0x14,     /*!< Pre-Driver Low-Side Pull-Down Strength Register 0      */
    HV_REG_PDRVLSPDSTR1           = 0x15,     /*!< Pre-Driver Low-Side Pull-Down Strength Register 1      */
    HV_REG_PDRVLSPUSTR0           = 0x16,     /*!< Pre-Driver Low-Side Pull-Up Strength Register 0        */
    HV_REG_PDRVLSPUSTR1           = 0x17,     /*!< Pre-Driver Low-Side Pull-Up Strength Register 1        */
    HV_REG_PDRVHSPDSTR0           = 0x18,     /*!< Pre-Driver High-Side Pull-Down Strength Register 0     */
    HV_REG_PDRVHSPDSTR1           = 0x19,     /*!< Pre-Driver High-Side Pull-Down Strength Register 1     */
    HV_REG_PDRVHSPUSTR0           = 0x1A,     /*!< Pre-Driver High-Side Pull-Up Strength Register 0       */
    HV_REG_PDRVHSPUSTR1           = 0x1B,     /*!< Pre-Driver High-Side Pull-Up Strength Register 1       */
    HV_REG_PDRVLSPDLEN            = 0x1C,     /*!< Pre-Driver Low-Side Pull-Down Length Register          */
    HV_REG_PDRVLSPULEN            = 0x1D,     /*!< Pre-Driver Low-Side Pull-Up Length Register            */
    HV_REG_PDRVHSPDLEN            = 0x1E,     /*!< Pre-Driver High-Side Pull-Down Length Register         */
    HV_REG_PDRVHSPULEN            = 0x1F,     /*!< Pre-Driver High-Side Pull-Up Length Register           */
    HV_REG_PDRVDLYU               = 0x20,     /*!< Pre-Driver U-Phase Turn-On Delay Register              */
    HV_REG_PDRVDLYV               = 0x21,     /*!< Pre-Driver V-Phase Turn-On Delay Register              */
    HV_REG_PDRVDLYW               = 0x22,     /*!< Pre-Driver W-Phase Turn-On Delay Register              */
    HV_REG_LINCTL                 = 0x23,     /*!< LIN Control Register                                   */
    HV_REG_LINTXPDEVTEN           = 0x24,     /*!< LIN Transmitter Self Power-Down Event Enable Register  */
    HV_REG_CTLKEY                 = 0x2F,     /*!< Control Key Register                                   */

    /* Registers For Engineering Test */
    HV_REG_PMUTRIM0               = 0x30,     /*!< PMU Trimming Register 0                                */
    HV_REG_PMUTRIM1               = 0x31,     /*!< PMU Trimming Register 1                                */
    HV_REG_PMUTRIM2               = 0x32,     /*!< PMU Trimming Register 2                                */
    HV_REG_PMUTRIM3               = 0x33,     /*!< PMU Trimming Register 3                                */
    HV_REG_BODTRIM                = 0x34,     /*!< BOD Trimming Register                                  */
    HV_REG_LINTRIM                = 0x35,     /*!< LIN Trimming Register                                  */
    HV_REG_HVATESTCTL             = 0x36,     /*!< HVATEST Control Register                               */
    HV_REG_MISCENGR               = 0x37,     /*!< Miscellaneous Engineering Register                     */
} HV_REGS;




/**
 *  @brief  High Voltage Register Key Definition
 */
typedef enum
{
    KEY_LOCK_ALL                  = 0x0000,   /*!< Lock all register access               */
    KEY_SRST_REG                  = 0x6666,   /*!< Allow to software reset the registers  */
    KEY_USER_REG                  = 0x7777,   /*!< Allow to write user registers          */
    KEY_ENGR_REG                  = 0x8888,   /*!< Allow to write engineer registers      */
    KEY_PMU_CMD                   = 0x9999,   /*!< Allow to accept PMU stop/sleep command */
} HV_KEYEnum;




/**
 *  @brief  High Voltage Module Pin Interface Definition
 */
#define GPIO_HV_PWM_U_H           (PIN_GPIO24)   /*!< GPIO for PWM_U_H           */
#define GPIO_HV_PWM_U_L           (PIN_GPIO23)   /*!< GPIO for PWM_U_L           */
#define GPIO_HV_PWM_V_H           (PIN_GPIO22)   /*!< GPIO for PWM_V_H           */
#define GPIO_HV_PWM_V_L           (PIN_GPIO21)   /*!< GPIO for PWM_V_L           */
#define GPIO_HV_PWM_W_H           (PIN_GPIO20)   /*!< GPIO for PWM_W_H           */
#define GPIO_HV_PWM_W_L           (PIN_GPIO19)   /*!< GPIO for PWM_W_L           */




/**
 *  @brief  LIN Module Pin Interface Definition
 */
#define GPIO_LIN_TXD              (PIN_GPIO25)   /*!< GPIO for LIN TXD           */
#define GPIO_LIN_RXD              (PIN_GPIO26)   /*!< GPIO for LIN RXD           */




/**
 *  @brief  LIN Module Pin Interface Definition
 */
#define GPIO_HV_MON               (PIN_GPIO27)   /*!< GPIO for HV monitor        */




/**
 *  @brief  ePower communication interface speed
 */
#define EPWR_COM_SPEED            (2600000) /*!< 2.6Mbps */




/**
 *  @brief  High Voltage Module Register Address Check
 */
#define IS_HV_REG(u8Addr)         (((u8Addr) <= 0x24) || (((u8Addr) >= 0x2F) && ((u8Addr) <= 0x37)))




/**
 *  @brief  High Voltage Module Public Function Declaration
 */
ErrorStatus HV_Init(uint16_t *pu16ID);
ErrorStatus HV_InitRegister(void);
ErrorStatus HV_Reset(void);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* HV_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
