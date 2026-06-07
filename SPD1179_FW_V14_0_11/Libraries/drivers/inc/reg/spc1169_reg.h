/*************************************************************************
 * @file     spc1169_reg.h
 * @brief    SPC1169 register structure definition.
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

#ifndef SPC1169_REG_H
#define SPC1169_REG_H

#ifdef __cplusplus
extern "C" {
#endif


#include "core_cm4.h"


/** @addtogroup Peripheral_Registers_Structure_Definition
  * @{
  */


/******************************************************************************/
/*                                                                            */
/*      SYSTEM:                                                               */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          SYSTEM
  */
typedef struct
{
    __I  uint32_t   CID0              ;  /*!< Offset: 0x00000000 (RO  ) Chip ID Register 0                                      */
    __I  uint32_t   CID1              ;  /*!< Offset: 0x00000004 (RO  ) Chip ID Register 1                                      */
    __I  uint32_t   UID0              ;  /*!< Offset: 0x00000008 (RO  ) Unique ID Register 0                                    */
    __I  uint32_t   UID1              ;  /*!< Offset: 0x0000000C (RO  ) Unique ID Register 1                                    */
    __I  uint32_t   RND0              ;  /*!< Offset: 0x00000010 (RO  ) Random Number Register 0                                */
    __I  uint32_t   RND1              ;  /*!< Offset: 0x00000014 (RO  ) Random Number Register 1                                */
    __I  uint32_t   REV0              ;  /*!< Offset: 0x00000018 (RO  ) Revision Information Register 0                         */
    __I  uint32_t   REV1              ;  /*!< Offset: 0x0000001C (RO  ) Revision Information Register 1                         */
    __IO uint32_t   SYSMONCTL         ;  /*!< Offset: 0x00000020 (RW  ) System Monitor Control Register                         */
    __IO uint32_t   VBATTH            ;  /*!< Offset: 0x00000024 (RW  ) VBAT Monitor Threshold Register                         */
    __IO uint32_t   VCPTH             ;  /*!< Offset: 0x00000028 (RW  ) VCP Monitor Threshold Register                          */
    __IO uint32_t   VMONTH            ;  /*!< Offset: 0x0000002C (RW  ) VMON Monitor Threshold Register                         */
    __IO uint32_t   VDD5TH            ;  /*!< Offset: 0x00000030 (RW  ) VDD5 Monitor Threshold Register                         */
    __IO uint32_t   VBGTH             ;  /*!< Offset: 0x00000034 (RW  ) Power Bandgap Monitor Threshold Register                */
    __IO uint32_t   TPMUTH            ;  /*!< Offset: 0x00000038 (RW  ) Power Module Temperature Monitor Threshold Register     */
    __IO uint32_t   TLINTH            ;  /*!< Offset: 0x0000003C (RW  ) LIN PHY Temperature Monitor Threshold Register          */
    __IO uint32_t   TMCUTH            ;  /*!< Offset: 0x00000040 (RW  ) Controller Temperature Monitor Threshold Register       */
    __IO uint32_t   VDD33TH           ;  /*!< Offset: 0x00000044 (RW  ) VDD33 Monitor Threshold Register                        */
    __IO uint32_t   VDD12TH           ;  /*!< Offset: 0x00000048 (RW  ) VDD12 Monitor Threshold Register                        */
    __IO uint32_t   VADCREFTH         ;  /*!< Offset: 0x0000004C (RW  ) 13-bit ADC Reference Voltage Monitor Threshold Register */
    __I   int32_t   VBATCODE          ;  /*!< Offset: 0x00000050 (RO  ) VBAT Monitor Code Register                              */
    __I   int32_t   VCPCODE           ;  /*!< Offset: 0x00000054 (RO  ) VCP Monitor Code Register                               */
    __I   int32_t   VMONCODE          ;  /*!< Offset: 0x00000058 (RO  ) VMON Monitor Code Register                              */
    __I   int32_t   VDD5CODE          ;  /*!< Offset: 0x0000005C (RO  ) VDD5 Monitor Code Register                              */
    __I   int32_t   VBGCODE           ;  /*!< Offset: 0x00000060 (RO  ) Power Bandgap Monitor Code Register                     */
    __I   int32_t   TPMUCODE          ;  /*!< Offset: 0x00000064 (RO  ) Power Module Temperature Monitor Code Register          */
    __I   int32_t   TLINCODE          ;  /*!< Offset: 0x00000068 (RO  ) LIN PHY Temperature Monitor Code Register               */
    __I   int32_t   TMCUCODE          ;  /*!< Offset: 0x0000006C (RO  ) Controller Temperature Monitor Code Register            */
    __I   int32_t   VDD33CODE         ;  /*!< Offset: 0x00000070 (RO  ) VDD33 Monitor Code Register                             */
    __I   int32_t   VDD12CODE         ;  /*!< Offset: 0x00000074 (RO  ) VDD12 Monitor Threshold Register                        */
    __I   int32_t   VADCREFCODE       ;  /*!< Offset: 0x00000078 (RO  ) 13-bit ADC Reference Voltage Monitor Code Register      */
    __IO uint32_t   GPIOWKUPCTL       ;  /*!< Offset: 0x0000007C (RW  ) GPIO Wake-Up Control Register                           */
    __IO uint32_t   GPIONMICTL        ;  /*!< Offset: 0x00000080 (RW  ) GPIO Non-Maskable Interrupt Control Register            */
    __I  uint32_t   NMRAWIF           ;  /*!< Offset: 0x00000084 (RO  ) Non-Maskable Interrupt Raw Flag Register                */
    __I  uint32_t   NMIF              ;  /*!< Offset: 0x00000088 (RO  ) Non-Maskable Interrupt Flag Register                    */
    __IO uint32_t   NMIC              ;  /*!< Offset: 0x0000008C (RW  ) Non-Maskable Interrupt Clear Register                   */
    __IO uint32_t   NMIE              ;  /*!< Offset: 0x00000090 (RW  ) Non-Maskable Interrupt Enable Register                  */
    __I  uint32_t   MEMRAWIF          ;  /*!< Offset: 0x00000094 (RO  ) Memory Interrupt Raw Flag Register                      */
    __I  uint32_t   MEMIF             ;  /*!< Offset: 0x00000098 (RO  ) Non-Maskable Interrupt Flag Register                    */
    __IO uint32_t   MEMIC             ;  /*!< Offset: 0x0000009C (RW  ) Memory Interrupt Clear Register                         */
    __IO uint32_t   MEMIE             ;  /*!< Offset: 0x000000A0 (RW  ) Memory Interrupt Enable Register                        */
    __I  uint32_t   RSTEVTFLG         ;  /*!< Offset: 0x000000A4 (RO  ) Reset Event Flag Register                               */
    __IO uint32_t   RSTEVTCLR         ;  /*!< Offset: 0x000000A8 (RW  ) Reset Event Flag Clear Register                         */
    __IO uint32_t   RSTEVTEN          ;  /*!< Offset: 0x000000AC (RW  ) Reset Event Enable Register                             */
    __I  uint32_t   SYSINFO           ;  /*!< Offset: 0x000000B0 (RO  ) System Information Register                             */
    __I  uint32_t   ROMERRADDR        ;  /*!< Offset: 0x000000B4 (RO  ) ROM ECC Error Address                                   */
    __I  uint32_t   FLASHERRADDR      ;  /*!< Offset: 0x000000B8 (RO  ) FLASH ECC Error Address                                 */
    __I  uint32_t   RAM0ERRADDR       ;  /*!< Offset: 0x000000BC (RO  ) RAM0 ECC Error Address                                  */
    __I  uint32_t   RAM1ERRADDR       ;  /*!< Offset: 0x000000C0 (RO  ) RAM1 ECC Error Address                                  */
         uint32_t   RESERVED_0        ;
    __IO uint32_t   DBGIFCTL          ;  /*!< Offset: 0x000000C8 (RW  ) Debug Interface Control Register                        */
    __IO uint32_t   BOOTINFO          ;  /*!< Offset: 0x000000CC (RW  ) Boot Information Register                               */
    __I  uint32_t   AHBMBEFLG         ;  /*!< Offset: 0x000000D0 (RO  ) AHB Multi-Bit ECC Error Event Flag Register             */
    __IO uint32_t   AHBMBECLR         ;  /*!< Offset: 0x000000D4 (RW  ) AHB Multi-bit ECC Error Event Flag Register             */
    __I  uint32_t   AHBSBEFLG         ;  /*!< Offset: 0x000000D8 (RO  ) AHB Single-Bit ECC Error Event Flag Register            */
    __IO uint32_t   AHBSBECLR         ;  /*!< Offset: 0x000000DC (RW  ) AHB Single-bit ECC Error Event Flag Register            */
    __I  uint32_t   PERIRSTFLG        ;  /*!< Offset: 0x000000E0 (RO  ) Peripheral Reset Event Flag Register                    */
    __IO uint32_t   PERIRSTCLR        ;  /*!< Offset: 0x000000E4 (RW  ) Peripheral Reset Event Clear Register                   */
         uint32_t   RESERVED_1[2]     ;
    __IO uint32_t   NVREG0            ;  /*!< Offset: 0x000000F0 (RW  ) Non-Volatile Register 0                                 */
    __IO uint32_t   NVREG1            ;  /*!< Offset: 0x000000F4 (RW  ) Non-Volatile Register 1                                 */
    __IO uint32_t   NVREG2            ;  /*!< Offset: 0x000000F8 (RW  ) Non-Volatile Register 2                                 */
    __IO uint32_t   SYSREGKEY         ;  /*!< Offset: 0x000000FC (RW  ) System Register Write-Allow Key Register                */
} SYSTEM_REGS;


/******************************************************************************/
/*                                                                            */
/*      POWER:                                                                */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          POWER
  */
typedef struct
{
    __IO uint32_t   LDOCTL          ;  /*!< Offset: 0x00000000 (RW  ) Power Control Register                  */
    __IO uint32_t   BOD33CTL        ;  /*!< Offset: 0x00000004 (RW  ) 3.3V BOD Control Register               */
    __IO uint32_t   BOD12CTL        ;  /*!< Offset: 0x00000008 (RW  ) 1.2V BOD Control Register               */
    __O  uint32_t   PWRMODECMD      ;  /*!< Offset: 0x0000000C (W1S ) Power Mode Command Register             */
    __IO uint32_t   PWRREGKEY       ;  /*!< Offset: 0x00000010 (RW  ) Power Register Write-Allow Key Register */
} POWER_REGS;


/******************************************************************************/
/*                                                                            */
/*      CLOCK:                                                                */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          CLOCK
  */
typedef struct
{
    __I  uint32_t   CLKSTS          ;  /*!< Offset: 0x00000000 (RO  ) Clock Status Register                      */
    __IO uint32_t   RCOCTL          ;  /*!< Offset: 0x00000004 (RW  ) RCO Control Register                       */
    __IO uint32_t   XOCTL           ;  /*!< Offset: 0x00000008 (RW  ) Crystal Oscillator Control Register        */
    __IO uint32_t   PLLCTL0         ;  /*!< Offset: 0x0000000C (RW  ) PLL Control Register 0                     */
    __IO uint32_t   PLLCTL1         ;  /*!< Offset: 0x00000010 (RW  ) PLL Control Register 1                     */
    __IO uint32_t   CLKDETCTL       ;  /*!< Offset: 0x00000014 (RW  ) Clock Detection Control Register           */
    __IO uint32_t   CLKDETCTH       ;  /*!< Offset: 0x00000018 (RW  ) Clock Detection Counter Threshold Register */
    __I  uint32_t   CLKDETCNT       ;  /*!< Offset: 0x0000001C (RO  ) Clock Detection Counter Register           */
    __IO uint32_t   CLKTZE          ;  /*!< Offset: 0x00000020 (RW  ) Clock Trip-zone Event Enable Register      */
    __IO uint32_t   SYSCLKCTL       ;  /*!< Offset: 0x00000024 (RW  ) System Clock Control Register              */
    __IO uint32_t   DGCLKCTL        ;  /*!< Offset: 0x00000028 (RW  ) Deglitch Clock Control Register            */
    __IO uint32_t   WDT0CLKCTL      ;  /*!< Offset: 0x0000002C (RW  ) WDT0 Clock Control Register                */
    __IO uint32_t   WDT1CLKCTL      ;  /*!< Offset: 0x00000030 (RW  ) WDT1 Clock Control Register                */
    __IO uint32_t   PERICLKEN       ;  /*!< Offset: 0x00000034 (RW  ) Peripheral Clock Enable Register           */
    __I  uint32_t   PERICLKSTS      ;  /*!< Offset: 0x00000038 (RO  ) Peripheral Clock Status Register           */
    __IO uint32_t   CLKREGKEY       ;  /*!< Offset: 0x0000003C (RW  ) Clock Register Write-Allow Key Register    */
} CLOCK_REGS;


/******************************************************************************/
/*                                                                            */
/*      PINMUX:                                                               */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          PINMUX
  */
typedef struct
{
    __IO uint32_t   GPIO0             ;  /*!< Offset: 0x00000000 (RW  ) GPIO0 Pin Control Register                 */
    __IO uint32_t   GPIO1             ;  /*!< Offset: 0x00000004 (RW  ) GPIO1 Pin Control Register                 */
    __IO uint32_t   GPIO2             ;  /*!< Offset: 0x00000008 (RW  ) GPIO2 Pin Control Register                 */
    __IO uint32_t   GPIO3             ;  /*!< Offset: 0x0000000C (RW  ) GPIO3 Pin Control Register                 */
    __IO uint32_t   GPIO4             ;  /*!< Offset: 0x00000010 (RW  ) GPIO4 Pin Control Register                 */
    __IO uint32_t   GPIO5             ;  /*!< Offset: 0x00000014 (RW  ) GPIO5 Pin Control Register                 */
    __IO uint32_t   GPIO6             ;  /*!< Offset: 0x00000018 (RW  ) GPIO6 Pin Control Register                 */
    __IO uint32_t   GPIO7             ;  /*!< Offset: 0x0000001C (RW  ) GPIO7 Pin Control Register                 */
    __IO uint32_t   GPIO8             ;  /*!< Offset: 0x00000020 (RW  ) GPIO8 Pin Control Register                 */
    __IO uint32_t   GPIO9             ;  /*!< Offset: 0x00000024 (RW  ) GPIO9 Pin Control Register                 */
    __IO uint32_t   GPIO10            ;  /*!< Offset: 0x00000028 (RW  ) GPIO10 Pin Control Register                */
    __IO uint32_t   GPIO11            ;  /*!< Offset: 0x0000002C (RW  ) GPIO11 Pin Control Register                */
    __IO uint32_t   GPIO12            ;  /*!< Offset: 0x00000030 (RW  ) GPIO12 Pin Control Register                */
    __IO uint32_t   GPIO13            ;  /*!< Offset: 0x00000034 (RW  ) GPIO13 Pin Control Register                */
    __IO uint32_t   GPIO14            ;  /*!< Offset: 0x00000038 (RW  ) GPIO14 Pin Control Register                */
    __IO uint32_t   GPIO15            ;  /*!< Offset: 0x0000003C (RW  ) GPIO15 Pin Control Register                */
    __IO uint32_t   GPIO16            ;  /*!< Offset: 0x00000040 (RW  ) GPIO16 Pin Control Register                */
    __IO uint32_t   GPIO17            ;  /*!< Offset: 0x00000044 (RW  ) GPIO17 Pin Control Register                */
    __IO uint32_t   GPIO18            ;  /*!< Offset: 0x00000048 (RW  ) GPIO18 Pin Control Register                */
    __IO uint32_t   GPIO19            ;  /*!< Offset: 0x0000004C (RW  ) GPIO19 Pin Control Register                */
    __IO uint32_t   GPIO20            ;  /*!< Offset: 0x00000050 (RW  ) GPIO20 Pin Control Register                */
    __IO uint32_t   GPIO21            ;  /*!< Offset: 0x00000054 (RW  ) GPIO21 Pin Control Register                */
    __IO uint32_t   GPIO22            ;  /*!< Offset: 0x00000058 (RW  ) GPIO22 Pin Control Register                */
    __IO uint32_t   GPIO23            ;  /*!< Offset: 0x0000005C (RW  ) GPIO23 Pin Control Register                */
    __IO uint32_t   GPIO24            ;  /*!< Offset: 0x00000060 (RW  ) GPIO24 Pin Control Register                */
    __IO uint32_t   GPIO25            ;  /*!< Offset: 0x00000064 (RW  ) GPIO25 Pin Control Register                */
    __IO uint32_t   GPIO26            ;  /*!< Offset: 0x00000068 (RW  ) GPIO26 Pin Control Register                */
    __IO uint32_t   GPIO27            ;  /*!< Offset: 0x0000006C (RW  ) GPIO27 Pin Control Register                */
    __IO uint32_t   GPIO28            ;  /*!< Offset: 0x00000070 (RW  ) GPIO28 Pin Control Register                */
    __IO uint32_t   GPIO29            ;  /*!< Offset: 0x00000074 (RW  ) GPIO29 Pin Control Register                */
    __IO uint32_t   GPIO30            ;  /*!< Offset: 0x00000078 (RW  ) GPIO30 Pin Control Register                */
    __IO uint32_t   GPIO31            ;  /*!< Offset: 0x0000007C (RW  ) GPIO31 Pin Control Register                */
    __IO uint32_t   GPIO32            ;  /*!< Offset: 0x00000080 (RW  ) GPIO32 Pin Control Register                */
    __IO uint32_t   GPIO33            ;  /*!< Offset: 0x00000084 (RW  ) GPIO33 Pin Control Register                */
    __IO uint32_t   GPIO34            ;  /*!< Offset: 0x00000088 (RW  ) GPIO34 Pin Control Register                */
    __IO uint32_t   GPIO35            ;  /*!< Offset: 0x0000008C (RW  ) GPIO35 Pin Control Register                */
    __IO uint32_t   GPIO36            ;  /*!< Offset: 0x00000090 (RW  ) GPIO36 Pin Control Register                */
    __IO uint32_t   GPIO37            ;  /*!< Offset: 0x00000094 (RW  ) GPIO37 Pin Control Register                */
    __IO uint32_t   GPIO38            ;  /*!< Offset: 0x00000098 (RW  ) GPIO38 Pin Control Register                */
    __IO uint32_t   GPIO39            ;  /*!< Offset: 0x0000009C (RW  ) GPIO39 Pin Control Register                */
    __IO uint32_t   GPIO40            ;  /*!< Offset: 0x000000A0 (RW  ) GPIO40 Pin Control Register                */
    __IO uint32_t   COMPMONCTL        ;  /*!< Offset: 0x000000A4 (RW  ) Comparator Output Monitor Control Register */
    __IO uint32_t   PINMUXREGKEY      ;  /*!< Offset: 0x000000A8 (RW  ) PINMUX  Register Write-Allow Key Register  */
} PINMUX_REGS;


/******************************************************************************/
/*                                                                            */
/*      EPWR:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          EPWR
  */
typedef struct
{
    __I  uint32_t   EPWRTZFLT       ;  /*!< Offset: 0x00000000 (RO  ) ePower Module Filtered Trip-Zone Event Register     */
    __I  uint32_t   EPWRTZFLG       ;  /*!< Offset: 0x00000004 (RO  ) ePower Module Latched Trip-Zone Flag Register       */
    __IO uint32_t   EPWRTZCLR       ;  /*!< Offset: 0x00000008 (RW  ) ePower Module Latched Trip-Zone Flag Clear Register */
    __IO uint32_t   EPWRTZ0CTL      ;  /*!< Offset: 0x0000000C (RW  ) ePower Module Trip-Zone Event 0 Control Register    */
    __IO uint32_t   EPWRTZ1CTL      ;  /*!< Offset: 0x00000010 (RW  ) ePower Module Trip-Zone Event 1 Control Register    */
    __IO uint32_t   EPWRCTL         ;  /*!< Offset: 0x00000014 (RW  ) ePower Module Control Register                      */
    __IO uint32_t   EPWRSCTL        ;  /*!< Offset: 0x00000018 (RW  ) ePower Module Serial Interface Control Register     */
    __I  uint32_t   EPWRSRDAT       ;  /*!< Offset: 0x0000001C (RO  ) ePower Module Serial Interface Read Data Register   */
    __I  uint32_t   EPWRSSTS        ;  /*!< Offset: 0x00000020 (RO  ) ePower Module Serial Interface Status Register      */
    __IO uint32_t   EPWRREGKEY      ;  /*!< Offset: 0x00000024 (RW  ) ePower Module Register Write-Allow Key Register     */
} EPWR_REGS;


/******************************************************************************/
/*                                                                            */
/*      PHCOMP:                                                               */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          PHCOMP
  */
typedef struct
{
    __I  uint32_t   PHCOMPSTS         ;  /*!< Offset: 0x00000000 (RO  ) Phase Comparison Status Register                   */
    __I  uint32_t   PHCOMPRAWIF       ;  /*!< Offset: 0x00000004 (RO  ) Phase Comparison Raw Interrupt Flag Register       */
    __I  uint32_t   PHCOMPIF          ;  /*!< Offset: 0x00000008 (RO  ) Phase Comparison Interrupt Flag Register           */
    __IO uint32_t   PHCOMPIC          ;  /*!< Offset: 0x0000000C (RW  ) Phase Comparison Interrupt Clear Register          */
    __IO uint32_t   PHCOMPIE          ;  /*!< Offset: 0x00000010 (RW  ) Phase Comparison Interrupt Enable Register         */
    __IO uint32_t   PHCOMPCTL         ;  /*!< Offset: 0x00000014 (RW  ) Phaes Comparison Control Register                  */
    __IO uint32_t   PHCOMPBLANK       ;  /*!< Offset: 0x00000018 (RW  ) Phase Comparison Blanking Control                  */
    __IO uint32_t   PHCOMPFILTER      ;  /*!< Offset: 0x0000001C (RW  ) Phase Comparison Filter Control                    */
    __IO uint32_t   PHCOMPRST         ;  /*!< Offset: 0x00000020 (RW  ) Phase Comparison FSM Reset Register                */
    __IO uint32_t   PHCOMPREGKEY      ;  /*!< Offset: 0x00000024 (RW  ) Phase Comparison Register Write-Allow Key Register */
} PHCOMP_REGS;


/******************************************************************************/
/*                                                                            */
/*      ENGR:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          ENGR
  */
typedef struct
{
         uint32_t   RESERVED_0[5]      ;
    __IO  int32_t   ADC1OFFSET         ;  /*!< Offset: 0x00000014 (RW  ) FuSa ADC Offset Trim Register         */
         uint32_t   RESERVED_1[11]     ;
    __IO uint32_t   MEMECCEN           ;  /*!< Offset: 0x00000044 (RW  ) Memory ECC Enable Register            */
} ENGR_REGS;


/******************************************************************************/
/*                                                                            */
/*      WDT:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          WDT
  */
typedef struct
{
    __IO uint32_t   WDTLOAD        ;  /*!< Offset: 0x00000000 (RW  ) Watchdog Timer Load Register                  */
    __I  uint32_t   WDTCNT         ;  /*!< Offset: 0x00000004 (RO  ) Watchdog Timer Current Value Register         */
    __IO uint32_t   WDTCTL         ;  /*!< Offset: 0x00000008 (RW  ) Watchdog Timer Control Register               */
    __I  uint32_t   WDTRAWIF       ;  /*!< Offset: 0x0000000C (RO  ) Watchdog Timer Raw Interrupt Flag Register    */
    __I  uint32_t   WDTIF          ;  /*!< Offset: 0x00000010 (RO  ) Watchdog Timer Interrupt Flag Register        */
    __IO uint32_t   WDTIC          ;  /*!< Offset: 0x00000014 (RW  ) Watchdog Timer Interrupt Clear Register       */
    __IO uint32_t   WDTIE          ;  /*!< Offset: 0x00000018 (RW  ) Watchdog Timer Interrupt Enable Register      */
    __IO uint32_t   WDTTHL         ;  /*!< Offset: 0x0000001C (RW  ) Watchdog Windowed-Feed Low Threshold Register */
    __IO uint32_t   WDTTHH         ;  /*!< Offset: 0x00000020 (RW  ) Watchdog Windowed-Feed Low Threshold Register */
    __IO uint32_t   WDTREGKEY      ;  /*!< Offset: 0x00000024 (RW  ) Watchdog Register Write-Allow Key Register    */
} WDT_REGS;


/******************************************************************************/
/*                                                                            */
/*      GPIO:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          GPIO
  */
typedef struct
{
    __IO uint32_t   GPLR[2]         ;  /*!< Offset: 0x00000000 (RW  ) GPIO Pin Level Register n ([0:1])                               */
         uint32_t   RESERVED_0[2]   ;
    __O  uint32_t   GSLR[2]         ;  /*!< Offset: 0x00000010 (W1S ) GPIO Pin Output Set Register n ([0:1])                          */
         uint32_t   RESERVED_1[2]   ;
    __O  uint32_t   GCLR[2]         ;  /*!< Offset: 0x00000020 (W1C ) GPIO Group n ([0:1]) Pin Output Clear Register                  */
         uint32_t   RESERVED_2[2]   ;
    __IO uint32_t   GPDR[2]         ;  /*!< Offset: 0x00000030 (RW  ) GPIO Pin Direction Register n ([0:1])                           */
         uint32_t   RESERVED_3[2]   ;
    __O  uint32_t   GSDR[2]         ;  /*!< Offset: 0x00000040 (W1S ) GPIO Pin Bitwise Set Direction Register n ([0:1])               */
         uint32_t   RESERVED_4[2]   ;
    __O  uint32_t   GCDR[2]         ;  /*!< Offset: 0x00000050 (W1C ) GPIO Pin Bitwise Clear Direction Register n ([0:1])             */
         uint32_t   RESERVED_5[2]   ;
    __IO uint32_t   GRER[2]         ;  /*!< Offset: 0x00000060 (RW  ) GPIO Pin Rising Edge Detect Enable Register n ([0:1])           */
         uint32_t   RESERVED_6[2]   ;
    __O  uint32_t   GSRE[2]         ;  /*!< Offset: 0x00000070 (W1S ) GPIO Pin Bitwise Set Rising Edge Detect Enable Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_7[2]   ;
    __O  uint32_t   GCRE[2]         ;  /*!< Offset: 0x00000080 (W1C ) GPIO Pin Bitwise Clear Rising Edge Detect Enable Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_8[2]   ;
    __IO uint32_t   GFER[2]         ;  /*!< Offset: 0x00000090 (RW  ) GPIO Pin Falling Edge Detect Enable Register n ([0:1])          */
         uint32_t   RESERVED_9[2]   ;
    __O  uint32_t   GSFE[2]         ;  /*!< Offset: 0x000000A0 (W1S ) GPIO Pin Bitwise Set Falling Edge Detect Enable Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_10[2]  ;
    __O  uint32_t   GCFE[2]         ;  /*!< Offset: 0x000000B0 (W1C ) GPIO Pin Bitwise Clear Falling Edge Detect Enable Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_11[2]  ;
    __I  uint32_t   GRERAWIF[2]     ;  /*!< Offset: 0x000000C0 (RO  ) GPIO Pin Rising Edge Detect Interrupt Raw Flag Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_12[2]  ;
    __I  uint32_t   GFERAWIF[2]     ;  /*!< Offset: 0x000000D0 (RO  ) GPIO Pin Falling Edge Detect Interrupt Raw Flag Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_13[2]  ;
    __I  uint32_t   GREIF[2]        ;  /*!< Offset: 0x000000E0 (RO  ) GPIO Pin Rising Edge Triggered Interrupt Flag Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_14[2]  ;
    __I  uint32_t   GFEIF[2]        ;  /*!< Offset: 0x000000F0 (RO  ) GPIO Pin Falling Edge Triggerred Interrupt Flag Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_15[2]  ;
    __IO uint32_t   GREIE[2]        ;  /*!< Offset: 0x00000100 (RW  ) GPIO Pin Rising Edge Triggered Interrupt Enable Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_16[2]  ;
    __IO uint32_t   GFEIE[2]        ;  /*!< Offset: 0x00000110 (RW  ) GPIO Pin Falling Edge Triggered Interrupt Enable Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_17[2]  ;
    __O  uint32_t   GREIC[2]        ;  /*!< Offset: 0x00000120 (W1C ) GPIO Group n ([0:1]) Pin Rising Edge Triggered Interrupt Clear
                                                                   Register                                                        */
         uint32_t   RESERVED_18[2]  ;
    __O  uint32_t   GFEIC[2]        ;  /*!< Offset: 0x00000130 (W1C ) GPIO Pin Falling Edge Triggered Interrupt Clear Register n
                                                                   ([0:1])                                                         */
         uint32_t   RESERVED_19[2]  ;
    __O  uint32_t   GREIFRC[2]      ;  /*!< Offset: 0x00000140 (W1S ) GPIO Pin Rising Edge Event Force Register n ([0:1])             */
         uint32_t   RESERVED_20[2]  ;
    __O  uint32_t   GFEIFRC[2]      ;  /*!< Offset: 0x00000150 (W1S ) GPIO Pin Falling Edge Event Force Register n ([0:1])            */
         uint32_t   RESERVED_21[2]  ;
    __IO uint32_t   GLDE[2]         ;  /*!< Offset: 0x00000160 (RW  ) GPIO Pin Level Detect Enable Register n ([0:1])                 */
         uint32_t   RESERVED_22[2]  ;
    __O  uint32_t   GSLDE[2]        ;  /*!< Offset: 0x00000170 (W1S ) GPIO Pin Bitwise Set Level Detect Enable Register n ([0:1])     */
         uint32_t   RESERVED_23[2]  ;
    __O  uint32_t   GCLDE[2]        ;  /*!< Offset: 0x00000180 (W1C ) GPIO Pin Bitwise Clear Level Detect Enable Register n ([0:1])   */
         uint32_t   RESERVED_24[2]  ;
    __IO uint32_t   GLPOL[2]        ;  /*!< Offset: 0x00000190 (RW  ) GPIO Pin Level Detect Polarity Register n ([0:1])               */
         uint32_t   RESERVED_25[2]  ;
    __I  uint32_t   GLRAWIF[2]      ;  /*!< Offset: 0x000001A0 (RO  ) GPIO Pin Level Detect Interrupt Raw Flag Register n ([0:1])     */
         uint32_t   RESERVED_26[2]  ;
    __I  uint32_t   GLIF[2]         ;  /*!< Offset: 0x000001B0 (RO  ) GPIO Pin Level-Triggered Interrupt Flag Register n ([0:1])      */
         uint32_t   RESERVED_27[2]  ;
    __IO uint32_t   GLIE[2]         ;  /*!< Offset: 0x000001C0 (RW  ) GPIO Pin Level-Triggered Interrupt Enable Register n ([0:1])    */
         uint32_t   RESERVED_28[2]  ;
    __O  uint32_t   GLIC[2]         ;  /*!< Offset: 0x000001D0 (W1C ) GPIO Pin Level-Triggered Interrupt Clear Register n ([0:1])     */
         uint32_t   RESERVED_29[2]  ;
    __O  uint32_t   GLIFRC[2]       ;  /*!< Offset: 0x000001E0 (W1S ) GPIO Pin Level-Triggered Event Force Register n ([0:1])         */
         uint32_t   RESERVED_30[2]  ;
    __I  uint32_t   GGRAWIF         ;  /*!< Offset: 0x000001F0 (RO  ) GPIO Global Interrupt Raw Flag Register                         */
    __I  uint32_t   GGIF            ;  /*!< Offset: 0x000001F4 (RO  ) GPIO Global Interrupt Flag Register                             */
    __IO uint32_t   GGIC            ;  /*!< Offset: 0x000001F8 (RW  ) GPIO Global Interrupt Clear Register                            */
    __IO uint32_t   GPIOREGKEY      ;  /*!< Offset: 0x000001FC (RW  ) GPIO Register Write-Allow Key Register                          */
} GPIO_REGS;


/******************************************************************************/
/*                                                                            */
/*      UART:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          UART
  */
typedef struct
{
    __IO uint32_t   UARTDAT         ;  /*!< Offset: 0x00000000 (RW  ) UART Data Register                     */
    __IO uint32_t   UARTCTL         ;  /*!< Offset: 0x00000004 (RW  ) UART Control Register                  */
    __IO uint32_t   LINCTL          ;  /*!< Offset: 0x00000008 (RW  ) LIN Control Register                   */
    __IO uint32_t   LINID           ;  /*!< Offset: 0x0000000C (RW  ) LIN ID Register                        */
    __IO uint32_t   LINIDFILT       ;  /*!< Offset: 0x00000010 (RW  ) LIN ID Filter Register                 */
    __IO uint32_t   BUSIDLETH       ;  /*!< Offset: 0x00000014 (RW  ) Bus Idle Threshold Register            */
    __IO uint32_t   UARTBDCNT       ;  /*!< Offset: 0x00000018 (RW  ) UART Baud Count Register               */
    __I  uint32_t   UARTABCNT       ;  /*!< Offset: 0x0000001C (RO  ) UART Auto-Baud Count Register          */
    __IO uint32_t   UARTTOTH        ;  /*!< Offset: 0x00000020 (RW  ) UART Timeout Threshold Register        */
    __I  uint32_t   UARTRXLVL       ;  /*!< Offset: 0x00000024 (RO  ) UART Receive FIFO Level Register       */
    __I  uint32_t   UARTTXLVL       ;  /*!< Offset: 0x00000028 (RO  ) UART Transmit FIFO Level Register      */
    __IO uint32_t   UARTRXTH        ;  /*!< Offset: 0x0000002C (RW  ) UART Receive FIFO Threshold Register   */
    __IO uint32_t   UARTTXTH        ;  /*!< Offset: 0x00000030 (RW  ) UART Transmit FIFO Threshold Register  */
    __IO uint32_t   UARTSIRCTL      ;  /*!< Offset: 0x00000034 (RW  ) UART Infrared Control Register         */
         uint32_t   RESERVED_0[2]   ;
    __I  uint32_t   UARTSTS         ;  /*!< Offset: 0x00000040 (RO  ) UART Status Register                   */
    __I  uint32_t   UARTRAWIF       ;  /*!< Offset: 0x00000044 (RO  ) UART Raw Interrupt Flag Register       */
    __I  uint32_t   UARTIF          ;  /*!< Offset: 0x00000048 (RO  ) UART Interrupt Flag Register           */
    __IO uint32_t   UARTIC          ;  /*!< Offset: 0x0000004C (RW  ) UART Interrupt Clear Register          */
    __IO uint32_t   UARTIE          ;  /*!< Offset: 0x00000050 (RW  ) UART Interrupt Enable Register         */
    __IO uint32_t   UARTDGCTL       ;  /*!< Offset: 0x00000054 (RW  ) UART RXD Deglitch Control              */
    __IO uint32_t   UARTREGKEY      ;  /*!< Offset: 0x00000058 (RW  ) Uart Register Write-Allow Key Register */
} UART_REGS;


/******************************************************************************/
/*                                                                            */
/*      SPI:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          SPI
  */
typedef struct
{
    __IO uint32_t   SPIDATA         ;  /*!< Offset: 0x00000000 (RW  ) SPI Data Register                         */
    __IO uint32_t   SPICTL0         ;  /*!< Offset: 0x00000004 (RW  ) SPI Control Register 0                    */
    __IO uint32_t   SPICTL1         ;  /*!< Offset: 0x00000008 (RW  ) SPI Control Register 1                    */
    __I  uint32_t   SPISTS          ;  /*!< Offset: 0x0000000C (RO  ) SPI Status Register                       */
    __I  uint32_t   SPIRFLVL        ;  /*!< Offset: 0x00000010 (RO  ) SPI Receive FIFO Level Register           */
    __I  uint32_t   SPITFLVL        ;  /*!< Offset: 0x00000014 (RO  ) SPI Transmit FIFO Level Register          */
    __IO uint32_t   SPIRFTH         ;  /*!< Offset: 0x00000018 (RW  ) SPI Receive FIFO Threshold Register       */
    __IO uint32_t   SPITFTH         ;  /*!< Offset: 0x0000001C (RW  ) SPI Transmit FIFO Threshold Register      */
    __I  uint32_t   SPIRAWIF        ;  /*!< Offset: 0x00000020 (RO  ) SPI Raw Interrupt Flag Register           */
    __I  uint32_t   SPIIF           ;  /*!< Offset: 0x00000024 (RO  ) SPI Interrupt Flag Register               */
    __IO uint32_t   SPIIC           ;  /*!< Offset: 0x00000028 (RW  ) SPI Interrupt Clear Register              */
    __IO uint32_t   SPIIE           ;  /*!< Offset: 0x0000002C (RW  ) SPI Interrupt Enable Register             */
    __IO uint32_t   SPITO           ;  /*!< Offset: 0x00000030 (RW  ) SPI Time Out Register                     */
    __IO uint32_t   SPIPSP          ;  /*!< Offset: 0x00000034 (RW  ) SPI Programmable Serial Protocol Register */
         uint32_t   RESERVED_0[2]   ;
    __IO uint32_t   SPITCTL         ;  /*!< Offset: 0x00000040 (RW  ) SPI Test Control Register                 */
    __IO uint32_t   SPIBDCNT        ;  /*!< Offset: 0x00000044 (RW  ) SPI Baud Count Register                   */
    __IO uint32_t   SPIREGKEY       ;  /*!< Offset: 0x00000048 (RW  ) SPI Register Write-Allow Key Register     */
} SPI_REGS;


/******************************************************************************/
/*                                                                            */
/*      TIMER:                                                                */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          TIMER
  */
typedef struct
{
    __IO uint32_t   TMRLOAD        ;  /*!< Offset: 0x00000000 (RW  ) Timer Load Register                     */
    __IO uint32_t   TMRCNT         ;  /*!< Offset: 0x00000004 (RW  ) Timer Counter Value Register            */
    __IO uint32_t   TMRCTL         ;  /*!< Offset: 0x00000008 (RW  ) Timer Control Register                  */
    __I  uint32_t   TMRRAWIF       ;  /*!< Offset: 0x0000000C (RO  ) Timer Raw Interrupt Flag Register       */
    __I  uint32_t   TMRIF          ;  /*!< Offset: 0x00000010 (RO  ) Timer Interrupt Flag Register           */
    __IO uint32_t   TMRIC          ;  /*!< Offset: 0x00000014 (RW  ) Timer Interrupt Clear Register          */
    __IO uint32_t   TMRIE          ;  /*!< Offset: 0x00000018 (RW  ) Timer Interrupt Enable Register         */
    __IO uint32_t   TMRREGKEY      ;  /*!< Offset: 0x0000001C (RW  ) Timer Register Write-Allow Key Register */
} TIMER_REGS;


/******************************************************************************/
/*                                                                            */
/*      FLASHC:                                                               */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          FLASHC
  */
typedef struct
{
    __IO uint32_t   FLASHCTL          ;  /*!< Offset: 0x00000000 (RW  ) Flash Control Register                             */
         uint32_t   RESERVED_0        ;
    __IO uint32_t   FLASHADDR         ;  /*!< Offset: 0x00000008 (RW  ) Flash Address Register                             */
         uint32_t   RESERVED_1        ;
    __IO uint32_t   FLASHDINL         ;  /*!< Offset: 0x00000010 (RW  ) Flash Data Input Low Word Register                 */
    __IO uint32_t   FLASHDINH         ;  /*!< Offset: 0x00000014 (RW  ) Flash Data Input High Word Register                */
    __IO uint32_t   FLASHDINE         ;  /*!< Offset: 0x00000018 (RW  ) Flash Data Input ECC Byte Register                 */
    __IO uint32_t   FLASHDINP         ;  /*!< Offset: 0x0000001C (RW  ) Flash Data Input Pattern Register                  */
    __I  uint32_t   FLASHDOUTL        ;  /*!< Offset: 0x00000020 (RO  ) Flash Data Output Low Word Register                */
    __I  uint32_t   FLASHDOUTH        ;  /*!< Offset: 0x00000024 (RO  ) Flash Data Output High Word Register               */
    __I  uint32_t   FLASHDOUTE        ;  /*!< Offset: 0x00000028 (RO  ) Flash Data Output ECC Byte Register                */
    __I  uint32_t   FLASHDOUTP        ;  /*!< Offset: 0x0000002C (RO  ) Flash Data Output Pattern Register                 */
         uint32_t   RESERVED_2[4]     ;
    __IO uint32_t   FLASHTIMING0      ;  /*!< Offset: 0x00000040 (RW  ) Flash Timing Register 0                            */
    __IO uint32_t   FLASHTIMING1      ;  /*!< Offset: 0x00000044 (RW  ) Flash Timing Register 1                            */
    __IO uint32_t   FLASHTIMING2      ;  /*!< Offset: 0x00000048 (RW  ) Flash Timing Register 2                            */
    __IO uint32_t   FLASHTIMING3      ;  /*!< Offset: 0x0000004C (RW  ) Flash Timing Register 3                            */
    __IO uint32_t   FLASHTIMING4      ;  /*!< Offset: 0x00000050 (RW  ) Flash Timing Register 4                            */
    __IO uint32_t   FLASHTIMING5      ;  /*!< Offset: 0x00000054 (RW  ) Flash Timing Register 5                            */
    __IO uint32_t   FLASHWP           ;  /*!< Offset: 0x00000058 (RW  ) Flash Write Protect Register                       */
         uint32_t   RESERVED_3        ;
    __IO uint32_t   FLASHCREGKEY      ;  /*!< Offset: 0x00000060 (RW  ) Flash Controller Register Write-Allow Key Register */
} FLASHC_REGS;


/******************************************************************************/
/*                                                                            */
/*      DMAC:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          DMAC
  */
typedef struct
{
         uint32_t   RESERVED_0[176]  ;
    __I  uint32_t   DMATCRAWIF       ;  /*!< Offset: 0x000002C0 (RO  ) DMA Transfer Complete Raw Interrupt Flag Register             */
         uint32_t   RESERVED_1       ;
    __I  uint32_t   DMABTCRAWIF      ;  /*!< Offset: 0x000002C8 (RO  ) DMA Block Transfer Complete Raw Interrupt Flag Register       */
         uint32_t   RESERVED_2       ;
    __I  uint32_t   DMASTCRAWIF      ;  /*!< Offset: 0x000002D0 (RO  ) DMA Source Transfer Complete Raw Interrupt Flag Register      */
         uint32_t   RESERVED_3       ;
    __I  uint32_t   DMADTCRAWIF      ;  /*!< Offset: 0x000002D8 (RO  ) DMA Destination Transfer Complete Raw Interrupt Flag Register */
         uint32_t   RESERVED_4       ;
    __I  uint32_t   DMAERRRAWIF      ;  /*!< Offset: 0x000002E0 (RO  ) DMA Error Raw Interrupt Flag Register                         */
         uint32_t   RESERVED_5       ;
    __I  uint32_t   DMATCIF          ;  /*!< Offset: 0x000002E8 (RO  ) DMA Transfer Complete Interrupt Flag Register                 */
         uint32_t   RESERVED_6       ;
    __I  uint32_t   DMABTCIF         ;  /*!< Offset: 0x000002F0 (RO  ) DMA Block Transfer Complete Interrupt Flag Register           */
         uint32_t   RESERVED_7       ;
    __I  uint32_t   DMASTCIF         ;  /*!< Offset: 0x000002F8 (RO  ) DMA Source Transfer Complete Interrupt Flag Register          */
         uint32_t   RESERVED_8       ;
    __I  uint32_t   DMADTCIF         ;  /*!< Offset: 0x00000300 (RO  ) DMA Destination Transfer Complete Interrupt Flag Register     */
         uint32_t   RESERVED_9       ;
    __I  uint32_t   DMAERRIF         ;  /*!< Offset: 0x00000308 (RO  ) DMA Error Interrupt Flag Register                             */
         uint32_t   RESERVED_10      ;
    __IO uint32_t   DMATCIE          ;  /*!< Offset: 0x00000310 (RW  ) DMA Transfer Complete Interrupt Enable Register               */
         uint32_t   RESERVED_11      ;
    __IO uint32_t   DMABTCIE         ;  /*!< Offset: 0x00000318 (RW  ) DMA Block Transfer Complete Interrupt Enable Register         */
         uint32_t   RESERVED_12      ;
    __IO uint32_t   DMASTCIE         ;  /*!< Offset: 0x00000320 (RW  ) DMA Source Transfer Complete Interrupt Enable Register        */
         uint32_t   RESERVED_13      ;
    __IO uint32_t   DMADTCIE         ;  /*!< Offset: 0x00000328 (RW  ) DMA Destination Transfer Complete Interrupt Enable Register   */
         uint32_t   RESERVED_14      ;
    __IO uint32_t   DMAERRIE         ;  /*!< Offset: 0x00000330 (RW  ) DMA Error Interrupt Enable Register                           */
         uint32_t   RESERVED_15      ;
    __IO uint32_t   DMATCIC          ;  /*!< Offset: 0x00000338 (RW  ) DMA Transfer Complete Interrupt Clear Register                */
         uint32_t   RESERVED_16      ;
    __IO uint32_t   DMABTCIC         ;  /*!< Offset: 0x00000340 (RW  ) DMA Block Transfer Complete Interrupt Clear Register          */
         uint32_t   RESERVED_17      ;
    __IO uint32_t   DMASTCIC         ;  /*!< Offset: 0x00000348 (RW  ) DMA Source Transfer Complete Interrupt Clear Register         */
         uint32_t   RESERVED_18      ;
    __IO uint32_t   DMADTCIC         ;  /*!< Offset: 0x00000350 (RW  ) DMA Destination Transfer Complete Interrupt Clear Register    */
         uint32_t   RESERVED_19      ;
    __IO uint32_t   DMAERRIC         ;  /*!< Offset: 0x00000358 (RW  ) DMA Error Interrupt Clear Register                            */
         uint32_t   RESERVED_20      ;
    __I  uint32_t   DMAIF            ;  /*!< Offset: 0x00000360 (RO  ) DMA Combined Interrupt Flag Register                          */
         uint32_t   RESERVED_21      ;
    __IO uint32_t   DMASSREQ         ;  /*!< Offset: 0x00000368 (RW  ) DMA Source Software Transaction Request Register              */
         uint32_t   RESERVED_22      ;
    __IO uint32_t   DMADSREQ         ;  /*!< Offset: 0x00000370 (RW  ) DMA Destination Software Transaction Request Register         */
         uint32_t   RESERVED_23      ;
    __IO uint32_t   DMASSSREQ        ;  /*!< Offset: 0x00000378 (RW  ) DMA Source Software Transaction Single Request Register       */
         uint32_t   RESERVED_24      ;
    __IO uint32_t   DMADSSREQ        ;  /*!< Offset: 0x00000380 (RW  ) DMA Destination Software Transaction Single Request Register  */
         uint32_t   RESERVED_25      ;
    __IO uint32_t   DMASSLREQ        ;  /*!< Offset: 0x00000388 (RW  ) DMA Source Software Transaction Last Request Register         */
         uint32_t   RESERVED_26      ;
    __IO uint32_t   DMADSLREQ        ;  /*!< Offset: 0x00000390 (RW  ) DMA Destination Software Transaction Last Request Register    */
         uint32_t   RESERVED_27      ;
    __IO uint32_t   DMAEN            ;  /*!< Offset: 0x00000398 (RW  ) DMA Enable Register                                           */
         uint32_t   RESERVED_28      ;
    __IO uint32_t   DMACHEN          ;  /*!< Offset: 0x000003A0 (RW  ) DMA Channel Enable Register                                   */
} DMAC_REGS;


/******************************************************************************/
/*                                                                            */
/*      DMACH:                                                                */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          DMACH
  */
typedef struct
{
    __IO uint32_t   DMACHSA           ;  /*!< Offset: 0x00000000 (RW  ) DMA Channel Source Address Register                         */
         uint32_t   RESERVED_0        ;
    __IO uint32_t   DMACHDA           ;  /*!< Offset: 0x00000008 (RW  ) DMA Channel Destination Address Register                    */
         uint32_t   RESERVED_1[3]     ;
    __IO uint32_t   DMACHCTL0         ;  /*!< Offset: 0x00000018 (RW  ) DMA Channel Control Register 0                              */
    __IO uint32_t   DMACHCTL1         ;  /*!< Offset: 0x0000001C (RW  ) DMA Channel Control Register 1                              */
         uint32_t   RESERVED_2[8]     ;
    __IO uint32_t   DMACHCFG0         ;  /*!< Offset: 0x00000040 (RW  ) DMA Channel Configure Register 0                            */
    __IO uint32_t   DMACHCFG1         ;  /*!< Offset: 0x00000044 (RW  ) DMA Channel Configure Register 1                            */
} DMACH_REGS;


/******************************************************************************/
/*                                                                            */
/*      PWM:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          PWM
  */
typedef struct
{
    __I  uint32_t   SHADOWSTS         ;  /*!< Offset: 0x00000000 (RO  ) Shadow Status Register                                     */
    __IO uint32_t   GLDCTL0           ;  /*!< Offset: 0x00000004 (RW  ) Global Shadow to Active Load Control Register 0            */
    __IO uint32_t   GLDCTL1           ;  /*!< Offset: 0x00000008 (RW  ) Global Shadow to Active Load Control Register 1            */
    __IO uint32_t   GLDSEL            ;  /*!< Offset: 0x0000000C (RW  ) Global Shadow to Active Load Select Register               */
    __IO uint32_t   PWMLINK           ;  /*!< Offset: 0x00000010 (RW  ) PWM Link Control Register                                  */
    __IO uint32_t   TBCTL             ;  /*!< Offset: 0x00000014 (RW  ) Time-Base Control Register                                 */
    __IO uint32_t   TBPRD             ;  /*!< Offset: 0x00000018 (RW  ) Time-Base Period Register                                  */
    __I  uint32_t   TBPRDA            ;  /*!< Offset: 0x0000001C (RO  ) Time-Base Period Active Register                           */
    __IO uint32_t   TBPHS             ;  /*!< Offset: 0x00000020 (RW  ) Time-Base Phase Register                                   */
    __IO uint32_t   TBCNT             ;  /*!< Offset: 0x00000024 (RW  ) Time-Base Counter Register                                 */
    __I  uint32_t   TBFLG             ;  /*!< Offset: 0x00000028 (RO  ) Time-Base Status Register                                  */
    __IO uint32_t   TBFLGCLR          ;  /*!< Offset: 0x0000002C (RW  ) Time-Base Status Clear Register                            */
    __IO uint32_t   CMPCTL            ;  /*!< Offset: 0x00000030 (RW  ) Counter-Compare Control Register                           */
    __IO uint32_t   CMPA              ;  /*!< Offset: 0x00000034 (RW  ) Counter-Compare A Threshold Register                       */
    __I  uint32_t   CMPAA             ;  /*!< Offset: 0x00000038 (RO  ) Counter-Compare A Threshold Active Register                */
    __IO uint32_t   CMPB              ;  /*!< Offset: 0x0000003C (RW  ) Counter-Compare B Threshold Register                       */
    __I  uint32_t   CMPBA             ;  /*!< Offset: 0x00000040 (RO  ) Counter-Compare B Threshold Active Register                */
    __IO uint32_t   CMPC              ;  /*!< Offset: 0x00000044 (RW  ) Counter-Compare C Threshold Register                       */
    __I  uint32_t   CMPCA             ;  /*!< Offset: 0x00000048 (RO  ) Counter-Compare C Threshold Active Register                */
    __IO uint32_t   CMPD              ;  /*!< Offset: 0x0000004C (RW  ) Counter-Compare D Threshold Register                       */
    __I  uint32_t   CMPDA             ;  /*!< Offset: 0x00000050 (RO  ) Counter-Compare D Threshold Active Register                */
    __IO uint32_t   AQCTL             ;  /*!< Offset: 0x00000054 (RW  ) Action-Qualifier Control Register                          */
    __IO uint32_t   AQCTLA            ;  /*!< Offset: 0x00000058 (RW  ) Action-Qualifier Output A Control Register                 */
    __I  uint32_t   AQCTLAA           ;  /*!< Offset: 0x0000005C (RO  ) Action-Qualifier Output A Control Active Register          */
    __IO uint32_t   AQCTLB            ;  /*!< Offset: 0x00000060 (RW  ) Action-Qualifier Output B Control Register                 */
    __I  uint32_t   AQCTLBA           ;  /*!< Offset: 0x00000064 (RO  ) Action-Qualifier Output B Control Active Register          */
    __IO uint32_t   AQSFRC            ;  /*!< Offset: 0x00000068 (RW  ) Action-Qualifier Software Force Register                   */
    __IO uint32_t   AQCSFRC           ;  /*!< Offset: 0x0000006C (RW  ) Action-Qualifier Continuous Software Force Register        */
    __I  uint32_t   AQCSFRCA          ;  /*!< Offset: 0x00000070 (RO  ) Action-Qualifier Continuous Software Force Active Register */
    __IO uint32_t   DBCTL             ;  /*!< Offset: 0x00000074 (RW  ) Dead-Band Generator Control Register                       */
    __I  uint32_t   DBCTLA            ;  /*!< Offset: 0x00000078 (RO  ) Dead-Band Generator Control Active Register                */
    __IO uint32_t   DBRED             ;  /*!< Offset: 0x0000007C (RW  ) Dead-Band Generator Rising Edge Delay Register             */
    __I  uint32_t   DBREDA            ;  /*!< Offset: 0x00000080 (RO  ) Dead-Band Generator Rising Edge Delay Active Register      */
    __IO uint32_t   DBFED             ;  /*!< Offset: 0x00000084 (RW  ) Dead-Band Generator Falling Edge Delay Register            */
    __I  uint32_t   DBFEDA            ;  /*!< Offset: 0x00000088 (RO  ) Dead-Band Generator Falling Edge Delay Active Register     */
    __IO uint32_t   TZSEL             ;  /*!< Offset: 0x0000008C (RW  ) Trip-Zone Event Select Register                            */
    __I  uint32_t   TZFLG             ;  /*!< Offset: 0x00000090 (RO  ) Trip-Zone Flag Register                                    */
    __IO uint32_t   TZFLGCLR          ;  /*!< Offset: 0x00000094 (RW  ) Trip-Zone Flag Clear Register                              */
    __IO uint32_t   TZDCSEL           ;  /*!< Offset: 0x00000098 (RW  ) Trip-Zone Digital Compare Event Select Register            */
    __IO uint32_t   TZACTL            ;  /*!< Offset: 0x0000009C (RW  ) Trip-Zone Output A Control Register                        */
    __IO uint32_t   TZBCTL            ;  /*!< Offset: 0x000000A0 (RW  ) Trip-Zone Ouput B Control Register                         */
    __I  uint32_t   TZIF              ;  /*!< Offset: 0x000000A4 (RO  ) Trip-Zone Interrupt Flag Register                          */
    __IO uint32_t   TZIC              ;  /*!< Offset: 0x000000A8 (RW  ) Trip-Zone Clear Register                                   */
    __IO uint32_t   TZIE              ;  /*!< Offset: 0x000000AC (RW  ) Trip-Zone Interrupt Enable Register                        */
    __IO uint32_t   TZFRC             ;  /*!< Offset: 0x000000B0 (RW  ) Trip-Zone Force Register                                   */
    __IO uint32_t   DCALTRIPSEL       ;  /*!< Offset: 0x000000B4 (RW  ) Digital Compare AL Trip Select Register                    */
    __IO uint32_t   DCAHTRIPSEL       ;  /*!< Offset: 0x000000B8 (RW  ) Digital Compare AH Trip Select Register                    */
    __IO uint32_t   DCBLTRIPSEL       ;  /*!< Offset: 0x000000BC (RW  ) Digital Compare BL Trip Select Register                    */
    __IO uint32_t   DCBHTRIPSEL       ;  /*!< Offset: 0x000000C0 (RW  ) Digital Compare BH Trip Select Register                    */
    __IO uint32_t   DCACTL            ;  /*!< Offset: 0x000000C4 (RW  ) Digital Compare A Control Register                         */
    __IO uint32_t   DCBCTL            ;  /*!< Offset: 0x000000C8 (RW  ) Digital Compare B Control Register                         */
    __IO uint32_t   DCFCTL            ;  /*!< Offset: 0x000000CC (RW  ) Digital Compare Filter Register                            */
    __IO uint32_t   DCFOFFSET         ;  /*!< Offset: 0x000000D0 (RW  ) Digital Compare Filter Offset Register                     */
    __I  uint32_t   DCFOFFSETCNT      ;  /*!< Offset: 0x000000D4 (RO  ) Digital Compare Filter Offset Counter Register             */
    __IO uint32_t   DCFWINDOW         ;  /*!< Offset: 0x000000D8 (RW  ) Digital Compare Filter Window Register                     */
    __I  uint32_t   DCFWINDOWCNT      ;  /*!< Offset: 0x000000DC (RO  ) Digital Compare Filter Window Counter Register             */
    __IO uint32_t   DCCAPCTL          ;  /*!< Offset: 0x000000E0 (RW  ) Digital Compare Capture Control Register                   */
    __I  uint32_t   DCCAP             ;  /*!< Offset: 0x000000E4 (RO  ) Digital Compare Counter Capture Register                   */
    __IO uint32_t   ETCTL             ;  /*!< Offset: 0x000000E8 (RW  ) Event-Trigger Control Register                             */
    __IO uint32_t   ETPS              ;  /*!< Offset: 0x000000EC (RW  ) Event-Trigger Prescale Register                            */
    __I  uint32_t   ETFLG             ;  /*!< Offset: 0x000000F0 (RO  ) Event-Trigger Flag Register                                */
    __IO uint32_t   ETCLR             ;  /*!< Offset: 0x000000F4 (RW  ) Event-Trigger Clear Register                               */
    __IO uint32_t   ETFRC             ;  /*!< Offset: 0x000000F8 (RW  ) Event-Trigger Force Register                               */
    __IO uint32_t   PWMREGKEY         ;  /*!< Offset: 0x000000FC (RW  ) PWM Register Write-Allow Key Register                      */
} PWM_REGS;


/******************************************************************************/
/*                                                                            */
/*      PWMCFG:                                                               */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          PWMCFG
  */
typedef struct
{
    __IO uint32_t   TZ0SRCCTL         ;  /*!< Offset: 0x00000000 (RW  ) TZ0 Source Control Register               */
    __IO uint32_t   TZ1SRCCTL         ;  /*!< Offset: 0x00000004 (RW  ) TZ1 Source Control Register               */
    __IO uint32_t   TZ2SRCCTL         ;  /*!< Offset: 0x00000008 (RW  ) TZ2 Source Control Register               */
    __IO uint32_t   TZ3SRCCTL         ;  /*!< Offset: 0x0000000C (RW  ) TZ3 Source Control Register               */
    __IO uint32_t   TZ4SRCCTL         ;  /*!< Offset: 0x00000010 (RW  ) TZ4 Source Control Register               */
    __O  uint32_t   FRCSYNC           ;  /*!< Offset: 0x00000014 (W1S ) Global PWM Force Synchronization Register */
    __IO uint32_t   GPIOSYNCICTL      ;  /*!< Offset: 0x00000018 (RW  ) GPIO PWMSYNCI Control Register            */
    __IO uint32_t   GPIOSYNCIEN       ;  /*!< Offset: 0x0000001C (RW  ) GPIO Force PWMSYNCI Enable Register       */
    __IO uint32_t   TMR0SYNCIEN       ;  /*!< Offset: 0x00000020 (RW  ) Timer 0 Force PWMSYNCI Enable Register    */
    __IO uint32_t   TMR1SYNCIEN       ;  /*!< Offset: 0x00000024 (RW  ) Timer 1 Force PWMSYNCI Enable Register    */
    __IO uint32_t   TMR2SYNCIEN       ;  /*!< Offset: 0x00000028 (RW  ) Timer 2 Force PWMSYNCI Enable Register    */
    __IO uint32_t   SYNCOCTL          ;  /*!< Offset: 0x0000002C (RW  ) PWMSYNCO Control Register                 */
    __IO uint32_t   SOCAOCTL          ;  /*!< Offset: 0x00000030 (RW  ) PWMSOCA Output Control Register           */
    __IO uint32_t   SOCBOCTL          ;  /*!< Offset: 0x00000034 (RW  ) PWMSOCB Output Control Register           */
    __IO uint32_t   SOCCOCTL          ;  /*!< Offset: 0x00000038 (RW  ) PWMSOCC Output Control Register           */
    __IO uint32_t   PWMCFGREGKEY      ;  /*!< Offset: 0x0000003C (RW  ) PWMCFG Register Write-Allow Key Register  */
} PWMCFG_REGS;


/******************************************************************************/
/*                                                                            */
/*      ADC:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          ADC
  */
typedef struct
{
    __I  uint32_t   ADCIF             ;  /*!< Offset: 0x00000000 (RO  ) ADC Interrupt Flag Register                       */
    __IO uint32_t   ADCIC             ;  /*!< Offset: 0x00000004 (RW  ) ADC Interrupt Flag Clear Register                 */
    __I  uint32_t   ADCIOVF           ;  /*!< Offset: 0x00000008 (RO  ) ADC Interrupt Overflow Flag Register              */
    __IO uint32_t   ADCIOVFC          ;  /*!< Offset: 0x0000000C (RW  ) ADC Interrupt Overflow Flag Clear Register        */
    __IO uint32_t   ADCIE             ;  /*!< Offset: 0x00000010 (RW  ) ADC Interrupt Enable Register                     */
    __IO uint32_t   ADCSOCPRICTL      ;  /*!< Offset: 0x00000014 (RW  ) ADC Start of Conversion Priority Control Register */
    __I  uint32_t   ADCSOCFLG         ;  /*!< Offset: 0x00000018 (RO  ) ADC SOC Flag Register                             */
    __IO uint32_t   ADCSOCFRC         ;  /*!< Offset: 0x0000001C (RW  ) ADC SOC Force Register                            */
    __I  uint32_t   ADCSOCOVF         ;  /*!< Offset: 0x00000020 (RO  ) ADC SOC Overflow Register                         */
    __IO uint32_t   ADCSOCOVFC        ;  /*!< Offset: 0x00000024 (RW  ) ADC SOC Overflow Clear Register                   */
    __IO uint32_t   ADCINTSOCEN       ;  /*!< Offset: 0x00000028 (RW  ) ADC Interrupt Trigger SOC Enable Register         */
    __IO uint32_t   ADCINTSOCSEL[2]   ;  /*!< Offset: 0x0000002C (RW  ) ADC Interrupt Trigger SOC Select Register 0       */
    __IO uint32_t   ADCEXTSOCCTL      ;  /*!< Offset: 0x00000034 (RW  ) ADC External SOC Input Control Register           */
    __IO uint32_t   ADCCHCTL[16]      ;  /*!< Offset: 0x00000038 (RW  ) ADC Channel n ([0:15]) Control Register           */
    __IO  int32_t   ADCOFFSET[16]     ;  /*!< Offset: 0x00000078 (RW  ) ADC Offset Trim Register n ([0:15])               */
    __IO uint32_t   ADCGAIN[16]       ;  /*!< Offset: 0x000000B8 (RW  ) ADC Gain Trim Register n ([0:15])                 */
    __IO  int32_t   SHOFFSET[1]       ;  /*!< Offset: 0x000000F8 (RW  ) ADC SH0 Offset Trim Register                      */
         uint32_t   RESERVED_0[2]     ;
    __IO uint32_t   SHGAIN[1]         ;  /*!< Offset: 0x00000104 (RW  ) ADC SH0 Gain Trim Register                        */
         uint32_t   RESERVED_1[2]     ;
    __I  uint32_t   SHFLG             ;  /*!< Offset: 0x00000110 (RO  ) ADC Sample Hold Channel EOC Flag Register         */
    __IO uint32_t   SHFLGCLR          ;  /*!< Offset: 0x00000114 (RW  ) ADC Sample Hold Channel EOC Flag Clear Register   */
    __IO uint32_t   ADCCTL            ;  /*!< Offset: 0x00000118 (RW  ) ADC Control Register                              */
    __I   int32_t   SHRAWCODE[1]      ;  /*!< Offset: 0x0000011C (RO  ) ADC SH0 Raw Code Register                         */
         uint32_t   RESERVED_2[2]     ;
    __I   int32_t   ADCRESULT[16]     ;  /*!< Offset: 0x00000128 (RO  ) ADC Result Register n ([0:15])                    */
    __I   int32_t   PPURESULT[3]      ;  /*!< Offset: 0x00000168 (RO  ) PPU Comparison Result Register n ([0:2])          */
         uint32_t   RESERVED_3[5]     ;
    __I  uint32_t   PPUSOCDLY[3]      ;  /*!< Offset: 0x00000188 (RO  ) PPU SOC Delay Register n ([0:2])                  */
         uint32_t   RESERVED_4[5]     ;
    __I  uint32_t   PPURAWIF[3]       ;  /*!< Offset: 0x000001A8 (RO  ) PPU Raw Interrupt Flag Register n ([0:2])         */
         uint32_t   RESERVED_5[5]     ;
    __I  uint32_t   PPUIF[3]          ;  /*!< Offset: 0x000001C8 (RO  ) PPU Interrupt Flag Register n ([0:2])             */
         uint32_t   RESERVED_6[5]     ;
    __IO uint32_t   PPUIC[3]          ;  /*!< Offset: 0x000001E8 (RW  ) PPU Interrupt Clear Register n ([0:2])            */
         uint32_t   RESERVED_7[5]     ;
    __IO uint32_t   PPUIE[3]          ;  /*!< Offset: 0x00000208 (RW  ) PPU Interrupt Enable Register n ([0:2])           */
         uint32_t   RESERVED_8[5]     ;
    __IO uint32_t   PPUTZE[3]         ;  /*!< Offset: 0x00000228 (RW  ) PPU Trip-Zone Event Enable Register n ([0:2])     */
         uint32_t   RESERVED_9[5]     ;
    __IO uint32_t   PPUCTL[3]         ;  /*!< Offset: 0x00000248 (RW  ) PPU Control Register n ([0:2])                    */
         uint32_t   RESERVED_10[5]    ;
    __IO  int32_t   PPUREF[3]         ;  /*!< Offset: 0x00000268 (RW  ) PPU Reference Register n ([0:2])                  */
         uint32_t   RESERVED_11[5]    ;
    __IO  int32_t   PPUTHL[3]         ;  /*!< Offset: 0x00000288 (RW  ) PPU Trip-Zone Low-Side Threshold Register n
                                                                       ([0:2])                                           */
         uint32_t   RESERVED_12[5]    ;
    __IO  int32_t   PPUTHH[3]         ;  /*!< Offset: 0x000002A8 (RW  ) PPU Trip-Zone High-Side Threshold Register n
                                                                       ([0:2])                                           */
         uint32_t   RESERVED_13[5]    ;
    __IO uint32_t   TSENSCTL          ;  /*!< Offset: 0x000002C8 (RW  ) Temperature Sensor Control Register               */
    __IO uint32_t   ADCREGKEY         ;  /*!< Offset: 0x000002CC (RW  ) ADC Register Write-Allow Key Register             */
} ADC_REGS;


/******************************************************************************/
/*                                                                            */
/*      COMP:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          COMP
  */
typedef struct
{
         uint32_t   RESERVED_0[189] ;
    __I  uint32_t   COMPFLTOUT      ;  /*!< Offset: 0x000002F4 (RO  ) Comparator Filter Output Register      */
    __I  uint32_t   COMPFLG         ;  /*!< Offset: 0x000002F8 (RO  ) Comparator Flag Register               */
    __IO uint32_t   COMPFLGCLR      ;  /*!< Offset: 0x000002FC (RW  ) Comparator Flag Clear Register         */
    __IO uint32_t   COMPCTL         ;  /*!< Offset: 0x00000300 (RW  ) Comparator 0 Control Register          */
    __IO uint32_t   COMPLCTL        ;  /*!< Offset: 0x00000304 (RW  ) COMP0L Control Register                */
    __IO uint32_t   COMPHCTL        ;  /*!< Offset: 0x00000308 (RW  ) COMP0H Control Register                */
         uint32_t   RESERVED_1[21]  ;
    __IO uint32_t   DAC0CTL         ;  /*!< Offset: 0x00000360 (RW  ) DAC0 Control Register                  */
    __IO uint32_t   DAC0CODE        ;  /*!< Offset: 0x00000364 (RW  ) DAC0 Code Register                     */
    __I  uint32_t   DAC0CODEA       ;  /*!< Offset: 0x00000368 (RO  ) DAC0 Active Code Register              */
    __IO uint32_t   RAMP0DLY        ;  /*!< Offset: 0x0000036C (RW  ) RAMP0 Delay Shadow Register            */
    __I  uint32_t   RAMP0DLYA       ;  /*!< Offset: 0x00000370 (RO  ) RAMP0 Delay Active Register            */
    __IO uint32_t   RAMP0DEC        ;  /*!< Offset: 0x00000374 (RW  ) RAMP0 Decrement Shadow Register        */
    __I  uint32_t   RAMP0DECA       ;  /*!< Offset: 0x00000378 (RO  ) RAMP0 Decrement Active Register        */
    __IO uint32_t   RAMP0MAX        ;  /*!< Offset: 0x0000037C (RW  ) RAMP0 Reload Value Shadow Register     */
    __I  uint32_t   RAMP0MAXA       ;  /*!< Offset: 0x00000380 (RO  ) RAMP0 Reload Value Active Register     */
    __I  uint32_t   RAMP0CNT        ;  /*!< Offset: 0x00000384 (RO  ) RAMP0 Count Register                   */
    __IO uint32_t   DAC1CTL         ;  /*!< Offset: 0x00000388 (RW  ) DAC1 Control Register                  */
    __IO uint32_t   DAC1CODE        ;  /*!< Offset: 0x0000038C (RW  ) DAC1 Code Register                     */
    __I  uint32_t   DAC1CODEA       ;  /*!< Offset: 0x00000390 (RO  ) DAC1 Active Code Register              */
    __IO uint32_t   RAMP1DLY        ;  /*!< Offset: 0x00000394 (RW  ) RAMP1 Delay Shadow Register            */
    __I  uint32_t   RAMP1DLYA       ;  /*!< Offset: 0x00000398 (RO  ) RAMP1 Delay Active Register            */
    __IO uint32_t   RAMP1DEC        ;  /*!< Offset: 0x0000039C (RW  ) RAMP1 Decrement Shadow Register        */
    __I  uint32_t   RAMP1DECA       ;  /*!< Offset: 0x000003A0 (RO  ) RAMP1 Decrement Active Register        */
    __IO uint32_t   RAMP1MAX        ;  /*!< Offset: 0x000003A4 (RW  ) RAMP1 Reload Value Shadow Register     */
    __I  uint32_t   RAMP1MAXA       ;  /*!< Offset: 0x000003A8 (RO  ) RAMP1 Reload Value Active Register     */
    __I  uint32_t   RAMP1CNT        ;  /*!< Offset: 0x000003AC (RO  ) RAMP1 Count Register                   */
    __IO uint32_t   DAC2CTL         ;  /*!< Offset: 0x000003B0 (RW  ) DAC2 Control Register                  */
    __IO uint32_t   DAC2CODE        ;  /*!< Offset: 0x000003B4 (RW  ) DAC2 Code Register                     */
    __I  uint32_t   DAC2CODEA       ;  /*!< Offset: 0x000003B8 (RO  ) DAC2 Active Code Register              */
         uint32_t   RESERVED_2[15]  ;
    __IO uint32_t   DACBUFCTL       ;  /*!< Offset: 0x000003F8 (RW  ) DAC Buffer Control Register            */
    __IO uint32_t   COMPREGKEY      ;  /*!< Offset: 0x000003FC (RW  ) COMP Register Write-Allow Key Register */
} COMP_REGS;


/******************************************************************************/
/*                                                                            */
/*      PGA:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          PGA
  */
typedef struct
{
         uint32_t   RESERVED_0[180] ;
    __IO uint32_t   DPGACTL        ;  /*!< Offset: 0x000002D0 (RW  ) Differential PGA Control Register     */
    __IO uint32_t   SPGACTL        ;  /*!< Offset: 0x000002D4 (RW  ) Single-ended PGA Control Register     */
         uint32_t   RESERVED_1[6]  ;
    __IO uint32_t   PGAREGKEY      ;  /*!< Offset: 0x000002F0 (RW  ) PGA Register Write-Allow Key Register */
} PGA_REGS;


/******************************************************************************/
/*                                                                            */
/*      ECAP:                                                                 */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          ECAP
  */
typedef struct
{
    __IO uint32_t   CAPSRCCTL        ;  /*!< Offset: 0x00000000 (RW  ) Capture Source Input Control Register                 */
    __IO uint32_t   CAPSYNCICTL      ;  /*!< Offset: 0x00000004 (RW  ) Capture Synchronization Source Input Control Register */
    __IO uint32_t   CAPTSCNT         ;  /*!< Offset: 0x00000008 (RW  ) Time-Stamp Counter Register                           */
    __IO uint32_t   CAPCNTPHS        ;  /*!< Offset: 0x0000000C (RW  ) Counter Phase Offset Value Register                   */
    __IO uint32_t   CAP0             ;  /*!< Offset: 0x00000010 (RW  ) Capture Register 0                                    */
    __IO uint32_t   CAP1             ;  /*!< Offset: 0x00000014 (RW  ) Capture Register 1                                    */
    __IO uint32_t   CAP2             ;  /*!< Offset: 0x00000018 (RW  ) Capture Register 2                                    */
    __IO uint32_t   CAP3             ;  /*!< Offset: 0x0000001C (RW  ) Capture Register 3                                    */
    __IO uint32_t   CAPCTL           ;  /*!< Offset: 0x00000020 (RW  ) Capture Control Register                              */
    __I  uint32_t   CAPRAWIF         ;  /*!< Offset: 0x00000024 (RO  ) Capture Interrupt Raw Flag Register                   */
    __I  uint32_t   CAPIF            ;  /*!< Offset: 0x00000028 (RO  ) Capture Interrupt Flag Register                       */
    __IO uint32_t   CAPIE            ;  /*!< Offset: 0x0000002C (RW  ) Capture Interrupt Enable Register                     */
    __IO uint32_t   CAPIC            ;  /*!< Offset: 0x00000030 (RW  ) Capture Interrupt Clear Register                      */
    __IO uint32_t   CAPIFRC          ;  /*!< Offset: 0x00000034 (RW  ) Capture Interrupt Event Force Register                */
    __IO uint32_t   CAPREGKEY        ;  /*!< Offset: 0x00000038 (RW  ) Capture Register Write-Allow Key Register             */
} ECAP_REGS;


/******************************************************************************/
/*                                                                            */
/*      I2C:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          I2C
  */
typedef struct
{
    __IO uint32_t   I2CCTL            ;  /*!< Offset: 0x00000000 (RW  ) I2C Control Register                             */
    __IO uint32_t   I2CMADDR          ;  /*!< Offset: 0x00000004 (RW  ) I2C Master Address Register                      */
    __IO uint32_t   I2CSADDR          ;  /*!< Offset: 0x00000008 (RW  ) I2C Slave Address Register                       */
    __IO uint32_t   I2CDATACMD        ;  /*!< Offset: 0x0000000C (RW  ) I2C Data and Command Register                    */
    __IO uint32_t   I2CSSLCNT         ;  /*!< Offset: 0x00000010 (RW  ) Standard Speed I2C Clock SCL Low Count Register  */
    __IO uint32_t   I2CSSHCNT         ;  /*!< Offset: 0x00000014 (RW  ) Standard Speed I2C Clock SCL High Count Register */
    __IO uint32_t   I2CFSLCNT         ;  /*!< Offset: 0x00000018 (RW  ) Fast Speed I2C Clock SCL Low Count Register      */
    __IO uint32_t   I2CFSHCNT         ;  /*!< Offset: 0x0000001C (RW  ) Fast Speed I2C Clock SCL High Count Register     */
    __IO uint32_t   I2CHSLCNT         ;  /*!< Offset: 0x00000020 (RW  ) High Speed I2C Clock SCL Low Count Register      */
    __IO uint32_t   I2CHSHCNT         ;  /*!< Offset: 0x00000024 (RW  ) High Speed I2C Clock SCL High Count Register     */
    __IO uint32_t   I2CFSSPKLEN       ;  /*!< Offset: 0x00000028 (RW  ) Fast Speed I2C Spike Suppresion Limit Register   */
    __IO uint32_t   I2CHSSPKLEN       ;  /*!< Offset: 0x0000002C (RW  ) High Speed I2C Spike Suppresion Limit Register   */
    __IO uint32_t   I2CSDASETUP       ;  /*!< Offset: 0x00000030 (RW  ) I2C SDA Setup Time Register                      */
    __IO uint32_t   I2CSDAHOLD        ;  /*!< Offset: 0x00000034 (RW  ) I2C SDA Hold Time Register                       */
    __I  uint32_t   I2CTXLVL          ;  /*!< Offset: 0x00000038 (RO  ) I2C Transmit FIFO Level Register                 */
    __I  uint32_t   I2CRXLVL          ;  /*!< Offset: 0x0000003C (RO  ) I2C Receive FIFO Level Register                  */
    __IO uint32_t   I2CTXTH           ;  /*!< Offset: 0x00000040 (RW  ) I2C Transmit FIFO Threshold Register             */
    __IO uint32_t   I2CRXTH           ;  /*!< Offset: 0x00000044 (RW  ) I2C Receive FIFO Threshold Register              */
         uint32_t   RESERVED_0[3]     ;
    __I  uint32_t   I2CSTS            ;  /*!< Offset: 0x00000054 (RO  ) I2C Status Register                              */
    __I  uint32_t   I2CTXABRTSRC      ;  /*!< Offset: 0x00000058 (RO  ) I2C Transmit Abort Source Register               */
    __I  uint32_t   I2CRAWIF          ;  /*!< Offset: 0x0000005C (RO  ) I2C Raw Interrupt Flag Register                  */
    __I  uint32_t   I2CIF             ;  /*!< Offset: 0x00000060 (RO  ) I2C Interrupt Flag Register                      */
    __IO uint32_t   I2CIE             ;  /*!< Offset: 0x00000064 (RW  ) I2C Interrupt Enable Register                    */
    __IO uint32_t   I2CIC             ;  /*!< Offset: 0x00000068 (RW  ) I2C Interrupt Enable Register                    */
    __IO uint32_t   I2CREGKEY         ;  /*!< Offset: 0x0000006C (RW  ) I2C Register Write-Allow Key Register            */
} I2C_REGS;


/******************************************************************************/
/*                                                                            */
/*      CRC:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          CRC
  */
typedef struct
{
    __IO uint32_t   CRCCTL         ;  /*!< Offset: 0x00000000 (RW  ) CRC Control Register                  */
    __IO uint32_t   CRCSTRLEN      ;  /*!< Offset: 0x00000004 (RW  ) CRC Stream Length Register            */
    __IO uint32_t   CRCSEED        ;  /*!< Offset: 0x00000008 (RW  ) CRC Seed Register                     */
    __IO uint32_t   CRCSTRIN       ;  /*!< Offset: 0x0000000C (RW  ) CRC Stream Input Register             */
    __I  uint32_t   CRCRESULT      ;  /*!< Offset: 0x00000010 (RO  ) CRC Result Register                   */
    __I  uint32_t   CRCRAWIF       ;  /*!< Offset: 0x00000014 (RO  ) CRC Raw Interrupt Flag Register       */
    __I  uint32_t   CRCIF          ;  /*!< Offset: 0x00000018 (RO  ) CRC Interrupt Flag Register           */
    __IO uint32_t   CRCIC          ;  /*!< Offset: 0x0000001C (RW  ) CRC Interrupt Clear Register          */
    __IO uint32_t   CRCIE          ;  /*!< Offset: 0x00000020 (RW  ) CRC Interrupt Enable Register         */
    __IO uint32_t   CRCREGKEY      ;  /*!< Offset: 0x00000024 (RW  ) CRC Register Write-Allow Key Register */
} CRC_REGS;


/******************************************************************************/
/*                                                                            */
/*      CANMBOX:                                                              */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          CANMBOX
  */
typedef struct
{
    __IO uint32_t   CANMBOXFDW[16]   ;  /*!< Offset: 0x00000000 (RW  ) Mailbox Data Word n ([0:15])
                                                                     Register                           */
    __IO uint32_t   CANMBOXFMSK      ;  /*!< Offset: 0x00000040 (RW  ) Mailbox Frame Mask Register        */
    __IO uint32_t   CANMBOXFID       ;  /*!< Offset: 0x00000044 (RW  ) Mailbox Frame Identifier Register  */
    __IO uint32_t   CANMBOXMTS       ;  /*!< Offset: 0x00000048 (RW  ) Mailbox Message Timestamp Register
                                                                     Note: Read only.                   */
    __IO uint32_t   CANMBOXMCTL      ;  /*!< Offset: 0x0000004C (RW  ) Mailbox Message Control Register   */
} CANMBOX_REGS;


/******************************************************************************/
/*                                                                            */
/*      CAN:                                                                  */
/*                                                                            */
/******************************************************************************/


/**
  *  @brief  Structure type to access the .
  *          CAN
  */
typedef struct
{
    CANMBOX_REGS    CANMBOX[64]        ;
    __IO uint32_t   CANCTL             ;  /*!< Offset: 0x00000000 (RW  ) Control Register                              */
    __IO uint32_t   CANNBTQ            ;  /*!< Offset: 0x00000004 (RW  ) Nominal Bit Timing Quatum Register            */
    __IO uint32_t   CANDBTQ            ;  /*!< Offset: 0x00000008 (RW  ) Data Bit Timing Quatum Register               */
    __IO uint32_t   CANTDC             ;  /*!< Offset: 0x0000000C (RW  ) Transmitter Delay Compensation Register       */
    __IO uint32_t   CANBRDLY           ;  /*!< Offset: 0x00000010 (RW  ) Bus-Off Recovery Delay Register               */
    __I  uint32_t   CANSTS             ;  /*!< Offset: 0x00000014 (RO  ) Status Register                               */
    __I  uint32_t   CANLEC             ;  /*!< Offset: 0x00000018 (RO  ) Last Error Code Register                      */
    __IO uint32_t   CANMIE             ;  /*!< Offset: 0x0000001C (RW  ) Misc Interrupt Enable Register                */
    __I  uint32_t   CANMRAWIF          ;  /*!< Offset: 0x00000020 (RO  ) Misc Raw Interrupt Flag Register              */
    __I  uint32_t   CANMIF             ;  /*!< Offset: 0x00000024 (RO  ) Misc Interrupt Flag Register                  */
    __O  uint32_t   CANMIC             ;  /*!< Offset: 0x00000028 (W1C ) Misc Interrupt Flag Clear Register            */
    __I  uint32_t   CANTGIF            ;  /*!< Offset: 0x0000002C (RO  ) Transfer Group Interrupt Flag Register        */
    __IO uint32_t   CANTGIC            ;  /*!< Offset: 0x00000030 (RW  ) Transfer Group Interrupt Flag Clear Register  */
    __I  uint32_t   CANMEMERRADDR      ;  /*!< Offset: 0x00000034 (RO  ) Memory Error Address Register                 */
    __IO uint32_t   CANTEST            ;  /*!< Offset: 0x00000038 (RW  ) Test Control Register                         */
    __IO uint32_t   CANECCTL           ;  /*!< Offset: 0x0000003C (RW  ) Error Counter Control Register                */
    __I  uint32_t   CANTXREQ[2]        ;  /*!< Offset: 0x00000040 (RO  ) Transmission Request Register                 */
         uint32_t   RESERVED_0[2]      ;
    __I  uint32_t   CANMSGNEW[2]       ;  /*!< Offset: 0x00000050 (RO  ) New Message Register                          */
         uint32_t   RESERVED_1[2]      ;
    __I  uint32_t   CANMSGIF[2]        ;  /*!< Offset: 0x00000060 (RO  ) Message Transfer Done Interrupt Flag Register */
         uint32_t   RESERVED_2[2]      ;
    __I  uint32_t   CANMBEN[2]         ;  /*!< Offset: 0x00000070 (RO  ) Mailbox Enable Register                       */
         uint32_t   RESERVED_3[2]      ;
    __IO uint32_t   CANTSCTL           ;  /*!< Offset: 0x00000080 (RW  ) Timestamp Control Register                    */
    __IO uint32_t   CANTSCNT           ;  /*!< Offset: 0x00000084 (RW  ) Timestamp Counter Register                    */
         uint32_t   RESERVED_4         ;
    __IO uint32_t   CANREGKEY          ;  /*!< Offset: 0x0000008C (RW  ) Register write-allow key register             */
} CAN_REGS;


/**
  * @}
  */


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* SPC1169_REG_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
