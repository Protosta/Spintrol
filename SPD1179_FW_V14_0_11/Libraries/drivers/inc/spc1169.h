/******************************************************************************
 * @file     spc1169.h
 * @brief    SPC1169 device header file.
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


#ifndef SPC1169_H
#define SPC1169_H

#ifdef __cplusplus
extern "C" {
#endif




/**
 *  @brief  Number of modules and resources
 */
#define NUM_OF_WDT_MODULE       (2)  // 2 WDT module for each CPU, total chip have 4 WDT
#define NUM_OF_TIMER_MODULE     (3)
#define NUM_OF_PWM_MODULE       (4)
#define NUM_OF_ECAP_MODULE      (1)
#define NUM_OF_UART_MODULE      (2)
#define NUM_OF_SPI_MODULE       (2)
#define NUM_OF_I2C_MODULE       (1)
#define NUM_OF_CAN_MODULE       (1)
#define NUM_OF_DMAC_MODULE      (1)
#define NUM_OF_CRC_MODULE       (1)
#define NUM_OF_EQEP_MODULE      (1)
#define NUM_OF_ADC_MODULE       (1)
#define NUM_OF_ADC_PPU          (3)
#define NUM_OF_ADC_SH           (1)
#define NUM_OF_ADC_CHANNEL      (16)
#define NUM_OF_DMA_CHANNEL      (8)
#define NUM_OF_GPIO_PIN         (41)




/**
 *  @brief  ADC resolution
 */
#define ADC_RESOLUTION          (13)




/**
 *  @brief  Configuration of the Cortex-M4 Processor and Core Peripherals
 */
#define __CM4_REV                 0x0001    /*!< Core revision r0p1                              */
#define __MPU_PRESENT             1         /*!< MPU present or not                              */
#define __NVIC_PRIO_BITS          4         /*!< Number of Bits used for Priority Levels         */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used    */
#define __FPU_PRESENT             1         /*!< FPU present                                     */




/**
 *  @brief  SPC1169 Interrupt Number Definition
 */
typedef enum IRQn
{
    /* -------------------  Cortex-M4 Processor Exceptions Numbers  ------------------- */
    NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt          */
    HardFault_IRQn                = -13,      /*!<  3 HardFault Interrupt             */
    MemoryManagement_IRQn         = -12,      /*!<  4 Memory Management Interrupt     */
    BusFault_IRQn                 = -11,      /*!<  5 Bus Fault Interrupt             */
    UsageFault_IRQn               = -10,      /*!<  6 Usage Fault Interrupt           */
    SVCall_IRQn                   =  -5,      /*!< 11 SV Call Interrupt               */
    DebugMonitor_IRQn             =  -4,      /*!< 12 Debug Monitor Interrupt         */
    PendSV_IRQn                   =  -2,      /*!< 14 Pend SV Interrupt               */
    SysTick_IRQn                  =  -1,      /*!< 15 System Tick Interrupt           */

    /******************  SPC1169cific Interrupt Numbers *********************************/
    WDT1_IRQn                     =   0,      /*!< WDT1 Interrupt                     */
    MEM_IRQn                      =   1,      /*!< Memory Interrupt                   */
    EPWRTZ0_IRQn                  =   2,      /*!< ePower Tripzone Interrupt 0        */
    EPWRTZ1_IRQn                  =   3,      /*!< ePower Tripzone Interrupt 1        */
    GPIO_LEVEL_IRQn               =   4,      /*!< GPIO Level Triggered Interrupt     */
    GPIO_EDGE_IRQn                =   5,      /*!< GPIO Edge Triggered Interrupt      */
    UART0_IRQn                    =   6,      /*!< UART0 Interrupt                    */
    SPI0_IRQn                     =   7,      /*!< SPI0 Interrupt                     */
    UART1_IRQn                    =   8,      /*!< UART1 Interrupt                    */
    SPI1_IRQn                     =   9,      /*!< SPI1 Interrupt                     */
    CANTRG0_IRQn                  =  10,      /*!< CAN Transfer Group 0 Interrupt     */
    CANTRG1_IRQn                  =  11,      /*!< CAN Transfer Group 1 Interrupt     */
    CANTRG2_IRQn                  =  12,      /*!< CAN Transfer Group 2 Interrupt     */
    CANTRG3_IRQn                  =  13,      /*!< CAN Transfer Group 3 Interrupt     */
    CANTRG4_IRQn                  =  14,      /*!< CAN Transfer Group 4 Interrupt     */
    CANTRG5_IRQn                  =  15,      /*!< CAN Transfer Group 5 Interrupt     */
    CANTRG6_IRQn                  =  16,      /*!< CAN Transfer Group 6 Interrupt     */
    CANTRG7_IRQn                  =  17,      /*!< CAN Transfer Group 7 Interrupt     */
    CANMISC_IRQn                  =  18,      /*!< CAN Miscellaneous Interrupt        */
    I2C_IRQn                      =  19,      /*!< I2C Interrupt                      */
    ADCCH0_IRQn                   =  20,      /*!< ADC Channel  0 EOC Interrupt       */
    ADCCH1_IRQn                   =  21,      /*!< ADC Channel  1 EOC Interrupt       */
    ADCCH2_IRQn                   =  22,      /*!< ADC Channel  2 EOC Interrupt       */
    ADCCH3_IRQn                   =  23,      /*!< ADC Channel  3 EOC Interrupt       */
    ADCCH4_IRQn                   =  24,      /*!< ADC Channel  4 EOC Interrupt       */
    ADCCH5_IRQn                   =  25,      /*!< ADC Channel  5 EOC Interrupt       */
    ADCCH6_IRQn                   =  26,      /*!< ADC Channel  6 EOC Interrupt       */
    ADCCH7_IRQn                   =  27,      /*!< ADC Channel  7 EOC Interrupt       */
    ADCCH8_IRQn                   =  28,      /*!< ADC Channel  8 EOC Interrupt       */
    ADCCH9_IRQn                   =  29,      /*!< ADC Channel  9 EOC Interrupt       */
    ADCCH10_IRQn                  =  30,      /*!< ADC Channel 10 EOC Interrupt       */
    ADCCH11_IRQn                  =  31,      /*!< ADC Channel 11 EOC Interrupt       */
    ADCCH12_IRQn                  =  32,      /*!< ADC Channel 12 EOC Interrupt       */
    ADCCH13_IRQn                  =  33,      /*!< ADC Channel 13 EOC Interrupt       */
    ADCCH14_IRQn                  =  34,      /*!< ADC Channel 14 EOC Interrupt       */
    ADCCH15_IRQn                  =  35,      /*!< ADC Channel 15 EOC Interrupt       */
    ADCPPU0_IRQn                  =  36,      /*!< ADC PPU0 Interrupt                 */
    ADCPPU1_IRQn                  =  37,      /*!< ADC PPU1 Interrupt                 */
    ADCPPU2_IRQn                  =  38,      /*!< ADC PPU2 Interrupt                 */
    PHCOMP_IRQn                   =  39,      /*!< PHCOMP Interrupt                   */
    PWM0_IRQn                     =  40,      /*!< PWM 0 Interrupt                    */
    PWM1_IRQn                     =  41,      /*!< PWM 1 Interrupt                    */
    PWM2_IRQn                     =  42,      /*!< PWM 2 Interrupt                    */
    PWM3_IRQn                     =  43,      /*!< PWM 3 Interrupt                    */
    PWM0TZ_IRQn                   =  44,      /*!< PWM 0 Tripzone Interrupt           */
    PWM1TZ_IRQn                   =  45,      /*!< PWM 1 Tripzone Interrupt           */
    PWM2TZ_IRQn                   =  46,      /*!< PWM 2 Tripzone Interrupt           */
    PWM3TZ_IRQn                   =  47,      /*!< PWM 3 Tripzone Interrupt           */
    ECAP_IRQn                     =  48,      /*!< ECAP Interrupt                     */
    DMAC_IRQn                     =  49,      /*!< DMAC Interrupt                     */
    TIMER0_IRQn                   =  50,      /*!< TIMER 0 Interrupt                  */
    TIMER1_IRQn                   =  51,      /*!< TIMER 1 Interrupt                  */
    TIMER2_IRQn                   =  52,      /*!< TIMER 2 Interrupt                  */
    CRC_IRQn                      =  53,      /*!< CRC Interrupt                      */
} IRQn_Type;




/**
 *  @brief  GPIO Pin Definition
 */
typedef enum
{
    PIN_GPIO0                       =  0U,    /*!< GPIO0  pin define          */
    PIN_GPIO1                       =  1U,    /*!< GPIO1  pin define          */
    PIN_GPIO2                       =  2U,    /*!< GPIO2  pin define          */
    PIN_GPIO3                       =  3U,    /*!< GPIO3  pin define          */
    PIN_GPIO4                       =  4U,    /*!< GPIO4  pin define          */
    PIN_GPIO5                       =  5U,    /*!< GPIO5  pin define          */
    PIN_GPIO6                       =  6U,    /*!< GPIO6  pin define          */
    PIN_GPIO7                       =  7U,    /*!< GPIO7  pin define          */
    PIN_GPIO8                       =  8U,    /*!< GPIO8  pin define          */
    PIN_GPIO9                       =  9U,    /*!< GPIO9  pin define          */
    PIN_GPIO10                      = 10U,    /*!< GPIO10 pin define          */
    PIN_GPIO11                      = 11U,    /*!< GPIO11 pin define          */
    PIN_GPIO12                      = 12U,    /*!< GPIO12 pin define          */
    PIN_GPIO13                      = 13U,    /*!< GPIO13 pin define          */
    PIN_GPIO14                      = 14U,    /*!< GPIO14 pin define          */
    PIN_GPIO15                      = 15U,    /*!< GPIO15 pin define          */
    PIN_GPIO16                      = 16U,    /*!< GPIO16 pin define          */
    PIN_GPIO17                      = 17U,    /*!< GPIO17 pin define          */
    PIN_GPIO18                      = 18U,    /*!< GPIO18 pin define          */
    PIN_GPIO19                      = 19U,    /*!< GPIO19 pin define          */
    PIN_GPIO20                      = 20U,    /*!< GPIO20 pin define          */
    PIN_GPIO21                      = 21U,    /*!< GPIO21 pin define          */
    PIN_GPIO22                      = 22U,    /*!< GPIO22 pin define          */
    PIN_GPIO23                      = 23U,    /*!< GPIO23 pin define          */
    PIN_GPIO24                      = 24U,    /*!< GPIO24 pin define          */
    PIN_GPIO25                      = 25U,    /*!< GPIO25 pin define          */
    PIN_GPIO26                      = 26U,    /*!< GPIO26 pin define          */
    PIN_GPIO27                      = 27U,    /*!< GPIO27 pin define          */
    PIN_GPIO28                      = 28U,    /*!< GPIO28 pin define          */
    PIN_GPIO29                      = 29U,    /*!< GPIO29 pin define          */
    PIN_GPIO30                      = 30U,    /*!< GPIO30 pin define          */
    PIN_GPIO31                      = 31U,    /*!< GPIO31 pin define          */
    PIN_GPIO32                      = 32U,    /*!< GPIO32 pin define          */
    PIN_GPIO33                      = 33U,    /*!< GPIO33 pin define          */
    PIN_GPIO34                      = 34U,    /*!< GPIO34 pin define          */
    PIN_GPIO35                      = 35U,    /*!< GPIO35 pin define          */
    PIN_GPIO36                      = 36U,    /*!< GPIO36 pin define          */
    PIN_GPIO37                      = 37U,    /*!< GPIO37 pin define          */
    PIN_GPIO38                      = 38U,    /*!< GPIO38 pin define          */
    PIN_GPIO39                      = 39U,    /*!< GPIO39 pin define          */
    PIN_GPIO40                      = 40U,    /*!< GPIO40 pin define          */
    PIN_GPIO_LAST                   = 40U,    /*!< GPIO40 pin is the last pin */
} PIN_NameEnum;




/**
 *  @brief  Flag Status Type Definition
 */
typedef enum { RESET = 0, SET = 1 } FlagStatus, IntStatus;


/**
 *  @brief  Functional State Definition
 */
typedef enum { DISABLE = 0, ENABLE = 1 } FunctionalState;


/**
 *  @brief  Status Type Definition
 */
typedef enum { ERROR = 1, SUCCESS = 0 } ErrorStatus;


/**
 *  @brief  Boolean Type Definition
 */
typedef enum { FALSE = 0, TRUE = 1 } BOOL;


/**
 *  @brief  Pin Level Type Definition
 */
typedef enum { LOW = 0, HIGH = 1 } LEVEL;




#include <stdint.h>
#include "core_cm4.h"             /* Processor and core peripherals                       */
#include "system_spc1169.h"       /* System header file                                   */




/**
 *  @brief  SPC1169 Peripheral Memory Map
 */
#define SYSTEM_BASE               ((uint32_t)0x40000000)      /*!< SYSTEM Base Address              */
#define POWER_BASE                ((uint32_t)0x40000100)      /*!< Power Base Address               */
#define CLOCK_BASE                ((uint32_t)0x40000200)      /*!< Clock Base Address               */
#define PINMUX_BASE               ((uint32_t)0x40000300)      /*!< PinMux Base Address              */
#define EPWR_BASE                 ((uint32_t)0x40000400)      /*!< ePower Base Address              */
#define PHCOMP_BASE               ((uint32_t)0x40000500)      /*!< Phase Comparator Base Address    */
#define ENGR_BASE                 ((uint32_t)0x40000F00)      /*!< ENGR Base Address                */
#define WDT0_BASE                 ((uint32_t)0x40001000)      /*!< Watch Dog Timer 0 Base Address   */
#define WDT1_BASE                 ((uint32_t)0x40001100)      /*!< Watch Dog Timer 1 Base Address   */
#define GPIO_BASE                 ((uint32_t)0x40001200)      /*!< GPIO Base Address                */
#define UART0_BASE                ((uint32_t)0x40001400)      /*!< UART0 Base Address               */
#define SPI0_BASE                 ((uint32_t)0x40001500)      /*!< SPI0 Base Address                */
#define UART1_BASE                ((uint32_t)0x40001600)      /*!< UART1 Base Address               */
#define SPI1_BASE                 ((uint32_t)0x40001700)      /*!< SPI1 Base Address                */
#define TIMER0_BASE               ((uint32_t)0x40001800)      /*!< Timer 0 Base Address             */
#define TIMER1_BASE               ((uint32_t)0x40001900)      /*!< Timer 1 Base Address             */
#define TIMER2_BASE               ((uint32_t)0x40001A00)      /*!< Timer 2 Base Address             */
#define FLASHC_BASE               ((uint32_t)0x40001B00)      /*!< FLASHC Base Address              */
#define DMAC_BASE                 ((uint32_t)0x40001C00)      /*!< DMAC Base Address                */
#define DMACH0_BASE               ((uint32_t)0x40001C00)      /*!< DMACH0 Base Address              */
#define DMACH1_BASE               ((uint32_t)0x40001C58)      /*!< DMACH1 Base Address              */
#define DMACH2_BASE               ((uint32_t)0x40001CB0)      /*!< DMACH2 Base Address              */
#define DMACH3_BASE               ((uint32_t)0x40001D08)      /*!< DMACH3 Base Address              */
#define DMACH4_BASE               ((uint32_t)0x40001D60)      /*!< DMACH4 Base Address              */
#define DMACH5_BASE               ((uint32_t)0x40001DB8)      /*!< DMACH5 Base Address              */
#define DMACH6_BASE               ((uint32_t)0x40001E10)      /*!< DMACH6 Base Address              */
#define DMACH7_BASE               ((uint32_t)0x40001E68)      /*!< DMACH7 Base Address              */
#define PWM0_BASE                 ((uint32_t)0x40002000)      /*!< PWM 0 Base Address               */
#define PWM1_BASE                 ((uint32_t)0x40002100)      /*!< PWM 1 Base Address               */
#define PWM2_BASE                 ((uint32_t)0x40002200)      /*!< PWM 2 Base Address               */
#define PWM3_BASE                 ((uint32_t)0x40002300)      /*!< PWM 3 Base Address               */
#define PWMCFG_BASE               ((uint32_t)0x40002F00)      /*!< PWMCFG Base Address              */
#define AFE_BASE                  ((uint32_t)0x40003000)      /*!< AFE Base Address                 */
#define ECAP_BASE                 ((uint32_t)0x40003400)      /*!< ECAP Base Address                */
#define I2C_BASE                  ((uint32_t)0x40003500)      /*!< I2C Base Address                 */
#define CRC_BASE                  ((uint32_t)0x40003600)      /*!< CRC Base Address                 */
#define CAN_BASE                  ((uint32_t)0x40004000)      /*!< CAN Base Address                 */



#include "spc1169_reg.h"          /*!< SPC1169 Register Structure Definition Header File  */
#include "spc1169_bitfield.h"     /*!< SPC1169 Register Bit Field Definition Header File  */




/**
 *  @brief  SPC1169 Peripheral Declaration
 */
#define SYSTEM          ((SYSTEM_REGS *) SYSTEM_BASE )        /*!< SYSTEM Declaration               */
#define POWER           ((POWER_REGS  *) POWER_BASE  )        /*!< Power Declaration                */
#define CLOCK           ((CLOCK_REGS  *) CLOCK_BASE  )        /*!< Clock Declaration                */
#define PINMUX          ((PINMUX_REGS *) PINMUX_BASE )        /*!< PinMux Declaration               */
#define EPWR            ((EPWR_REGS   *) EPWR_BASE   )        /*!< ePower Declaration               */
#define PHCOMP          ((PHCOMP_REGS *) PHCOMP_BASE )        /*!< Phase Comparator Declaration     */
#define ENGR            ((ENGR_REGS   *) ENGR_BASE   )        /*!< ENGR Declaration                 */
#define WDT0            ((WDT_REGS    *) WDT0_BASE   )        /*!< Watch Dog Timer 0 Declaration    */
#define WDT1            ((WDT_REGS    *) WDT1_BASE   )        /*!< Watch Dog Timer 1 Declaration    */
#define GPIO            ((GPIO_REGS   *) GPIO_BASE   )        /*!< GPIO Declaration                 */
#define UART0           ((UART_REGS   *) UART0_BASE  )        /*!< UART0 Declaration                */
#define SPI0            ((SPI_REGS    *) SPI0_BASE   )        /*!< SPI0 Declaration                 */
#define UART1           ((UART_REGS   *) UART1_BASE  )        /*!< UART1 Declaration                */
#define SPI1            ((SPI_REGS    *) SPI1_BASE   )        /*!< SPI1 Declaration                 */
#define TIMER0          ((TIMER_REGS  *) TIMER0_BASE )        /*!< Timer 0 Declaration              */
#define TIMER1          ((TIMER_REGS  *) TIMER1_BASE )        /*!< Timer 1 Declaration              */
#define TIMER2          ((TIMER_REGS  *) TIMER2_BASE )        /*!< Timer 2 Declaration              */
#define FLASHC          ((FLASHC_REGS *) FLASHC_BASE )        /*!< FLASHC Declaration               */
#define DMAC            ((DMAC_REGS   *) DMAC_BASE   )        /*!< DMAC Declaration                 */
#define DMACH0          ((DMACH_REGS  *) DMACH0_BASE )        /*!< DMACH0 Declaration               */
#define DMACH1          ((DMACH_REGS  *) DMACH1_BASE )        /*!< DMACH1 Declaration               */
#define DMACH2          ((DMACH_REGS  *) DMACH2_BASE )        /*!< DMACH2 Declaration               */
#define DMACH3          ((DMACH_REGS  *) DMACH3_BASE )        /*!< DMACH3 Declaration               */
#define DMACH4          ((DMACH_REGS  *) DMACH4_BASE )        /*!< DMACH4 Declaration               */
#define DMACH5          ((DMACH_REGS  *) DMACH5_BASE )        /*!< DMACH5 Declaration               */
#define DMACH6          ((DMACH_REGS  *) DMACH6_BASE )        /*!< DMACH6 Declaration               */
#define DMACH7          ((DMACH_REGS  *) DMACH7_BASE )        /*!< DMACH7 Declaration               */
#define PWM0            ((PWM_REGS    *) PWM0_BASE   )        /*!< PWM 0 Declaration                */
#define PWM1            ((PWM_REGS    *) PWM1_BASE   )        /*!< PWM 1 Declaration                */
#define PWM2            ((PWM_REGS    *) PWM2_BASE   )        /*!< PWM 2 Declaration                */
#define PWM3            ((PWM_REGS    *) PWM3_BASE   )        /*!< PWM 3 Declaration                */
#define PWMCFG          ((PWMCFG_REGS *) PWMCFG_BASE )        /*!< PWM CFG Declaration              */
#define ADC             ((ADC_REGS    *) AFE_BASE    )        /*!< ADC Declaration                  */
#define PGA             ((PGA_REGS    *) AFE_BASE    )        /*!< PGA Declaration                  */
#define COMP            ((COMP_REGS   *) AFE_BASE    )        /*!< COMP Declaration                 */
#define ECAP            ((ECAP_REGS   *) ECAP_BASE   )        /*!< ECAP Declaration                 */
#define I2C             ((I2C_REGS    *) I2C_BASE    )        /*!< I2C Declaration                  */
#define CRC             ((CRC_REGS    *) CRC_BASE    )        /*!< CRC Declaration                  */
#define CAN             ((CAN_REGS    *) CAN_BASE    )        /*!< CAN Declaration                  */




/**
 *  @brief  Define Data Type
 */
typedef volatile unsigned char  vu8;        /*!< Define 8-bit unsigned volatile data type           */
typedef volatile unsigned short vu16;       /*!< Define 16-bit unsigned volatile data type          */
typedef volatile unsigned int   vu32;       /*!< Define 32-bit unsigned volatile data type          */




/******************************************************************************
 * @brief      Get a 8-bit unsigned value from specified address
 *
 * @param[in]  addr: Address to get 8-bit data from
 *
 * @return     8-bit unsigned value stored in specified address
 *
 ******************************************************************************/
#define M8(addr)                  (*((vu8  *) (addr)))




/******************************************************************************
 * @brief      Get a 16-bit unsigned value from specified address
 *
 * @param[in]  addr: Address to get 16-bit data from
 *
 * @return     16-bit unsigned value stored in specified address
 *
 * @note       The input address must be 16-bit aligned
 *
 ******************************************************************************/
#define M16(addr)                 (*((vu16 *) (addr)))




/******************************************************************************
 * @brief      Get a 32-bit unsigned value from specified address
 *
 * @param[in]  addr: Address to get 32-bit data from
 *
 * @return     32-bit unsigned value stored in specified address
 *
 * @note       The input address must be 32-bit aligned
 *
 ******************************************************************************/
#define M32(addr)                 (*((vu32 *) (addr)))




/******************************************************************************
 * @brief      Set a 32-bit unsigned value to specified I/O port
 *
 * @param[in]  port : Port address to set 32-bit data
 * @param[in]  value: Value to write to I/O port
 *
 * @return     None
 *
 * @note       The output port must be 32-bit aligned
 *
 ******************************************************************************/
#define outpw(port,value)         (*((volatile unsigned int *)(port)) = (value))




/******************************************************************************
 * @brief      Get a 32-bit unsigned value from specified I/O port
 *
 * @param[in]  port: Port address to get 32-bit data from
 *
 * @return     32-bit unsigned value stored in specified I/O port
 *
 * @note       The input port must be 32-bit aligned
 *
 ******************************************************************************/
#define inpw(port)                (*((volatile unsigned int *)(port)))




/******************************************************************************
 * @brief      Set a 16-bit unsigned value to specified I/O port
 *
 * @param[in]  port : Port address to set 16-bit data
 * @param[in]  value: Value to write to I/O port
 *
 * @return     None
 *
 * @note       The output port must be 16-bit aligned
 *
 ******************************************************************************/
#define outps(port,value)         (*((volatile unsigned short *)(port)) = (value))




/******************************************************************************
 * @brief      Get a 16-bit unsigned value from specified I/O port
 *
 * @param[in]  port: Port address to get 16-bit data from
 *
 * @return     16-bit unsigned value stored in specified I/O port
 *
 * @note       The input port must be 16-bit aligned
 *
 ******************************************************************************/
#define inps(port)                (*((volatile unsigned short *)(port)))




/******************************************************************************
 * @brief      Set a 8-bit unsigned value to specified I/O port
 *
 * @param[in]  port : Port address to set 8-bit data
 * @param[in]  value: Value to write to I/O port
 *
 * @return     None
 *
 ******************************************************************************/
#define outpb(port,value)         (*((volatile unsigned char *)(port)) = (value))




/******************************************************************************
 * @brief      Get a 8-bit unsigned value from specified I/O port
 *
 * @param[in]  port : Port address to get 8-bit data from
 *
 * @return     8-bit unsigned value stored in specified I/O port
 *
 ******************************************************************************/
#define inpb(port)                (*((volatile unsigned char *)(port)))




/******************************************************************************
 * @brief      Set a 32-bit unsigned value to specified I/O port
 *
 * @param[in]  port : Port address to set 32-bit data
 * @param[in]  value: Value to write to I/O port
 *
 * @return     None
 *
 * @note       The output port must be 32-bit aligned
 *
 ******************************************************************************/
#define outp32(port,value)        (*((volatile unsigned int *)(port)) = (value))




/******************************************************************************
 * @brief      Get a 32-bit unsigned value from specified I/O port
 *
 * @param[in]  port: Port address to get 32-bit data from
 *
 * @return     32-bit unsigned value stored in specified I/O port
 *
 * @note       The input port must be 32-bit aligned
 *
 ******************************************************************************/
#define inp32(port)               (*((volatile unsigned int *)(port)))




/******************************************************************************
 * @brief      Set a 16-bit unsigned value to specified I/O port
 *
 * @param[in]  port : Port address to set 16-bit data
 * @param[in]  value: Value to write to I/O port
 *
 * @return     None
 *
 * @note       The output port must be 16-bit aligned
 *
 ******************************************************************************/
#define outp16(port,value)        (*((volatile unsigned short *)(port)) = (value))




/******************************************************************************
 * @brief      Get a 16-bit unsigned value from specified I/O port
 *
 * @param[in]  port: Port address to get 16-bit data from
 *
 * @return     16-bit unsigned value stored in specified I/O port
 *
 * @note       The input port must be 16-bit aligned
 *
 ******************************************************************************/
#define inp16(port)               (*((volatile unsigned short *)(port)))




/******************************************************************************
 * @brief      Set a 8-bit unsigned value to specified I/O port
 *
 * @param[in]  port : Port address to set 8-bit data
 * @param[in]  value: Value to write to I/O port
 *
 * @return     None
 *
 ******************************************************************************/
#define outp8(port,value)         (*((volatile unsigned char *)(port)) = (value))




/******************************************************************************
 * @brief      Get a 8-bit unsigned value from specified I/O port
 *
 * @param[in]  port: Port address to get 8-bit data from
 *
 * @return     8-bit unsigned value stored in specified I/O port
 *
 ******************************************************************************/
#define inp8(port)                (*((volatile unsigned char *)(port)))




/**
 *  @brief  Null Type definition
 */
#ifndef NULL
#define NULL            (0)                 /*!< Null Pointer                                       */
#endif




/**
 *  @brief  Define one bit mask
 */
#define BIT0            (0x00000001)        /*!< Bit  0 mask of an 32 bit integer                   */
#define BIT1            (0x00000002)        /*!< Bit  1 mask of an 32 bit integer                   */
#define BIT2            (0x00000004)        /*!< Bit  2 mask of an 32 bit integer                   */
#define BIT3            (0x00000008)        /*!< Bit  3 mask of an 32 bit integer                   */
#define BIT4            (0x00000010)        /*!< Bit  4 mask of an 32 bit integer                   */
#define BIT5            (0x00000020)        /*!< Bit  5 mask of an 32 bit integer                   */
#define BIT6            (0x00000040)        /*!< Bit  6 mask of an 32 bit integer                   */
#define BIT7            (0x00000080)        /*!< Bit  7 mask of an 32 bit integer                   */
#define BIT8            (0x00000100)        /*!< Bit  8 mask of an 32 bit integer                   */
#define BIT9            (0x00000200)        /*!< Bit  9 mask of an 32 bit integer                   */
#define BIT10           (0x00000400)        /*!< Bit 10 mask of an 32 bit integer                   */
#define BIT11           (0x00000800)        /*!< Bit 11 mask of an 32 bit integer                   */
#define BIT12           (0x00001000)        /*!< Bit 12 mask of an 32 bit integer                   */
#define BIT13           (0x00002000)        /*!< Bit 13 mask of an 32 bit integer                   */
#define BIT14           (0x00004000)        /*!< Bit 14 mask of an 32 bit integer                   */
#define BIT15           (0x00008000)        /*!< Bit 15 mask of an 32 bit integer                   */
#define BIT16           (0x00010000)        /*!< Bit 16 mask of an 32 bit integer                   */
#define BIT17           (0x00020000)        /*!< Bit 17 mask of an 32 bit integer                   */
#define BIT18           (0x00040000)        /*!< Bit 18 mask of an 32 bit integer                   */
#define BIT19           (0x00080000)        /*!< Bit 19 mask of an 32 bit integer                   */
#define BIT20           (0x00100000)        /*!< Bit 20 mask of an 32 bit integer                   */
#define BIT21           (0x00200000)        /*!< Bit 21 mask of an 32 bit integer                   */
#define BIT22           (0x00400000)        /*!< Bit 22 mask of an 32 bit integer                   */
#define BIT23           (0x00800000)        /*!< Bit 23 mask of an 32 bit integer                   */
#define BIT24           (0x01000000)        /*!< Bit 24 mask of an 32 bit integer                   */
#define BIT25           (0x02000000)        /*!< Bit 25 mask of an 32 bit integer                   */
#define BIT26           (0x04000000)        /*!< Bit 26 mask of an 32 bit integer                   */
#define BIT27           (0x08000000)        /*!< Bit 27 mask of an 32 bit integer                   */
#define BIT28           (0x10000000)        /*!< Bit 28 mask of an 32 bit integer                   */
#define BIT29           (0x20000000)        /*!< Bit 29 mask of an 32 bit integer                   */
#define BIT30           (0x40000000)        /*!< Bit 30 mask of an 32 bit integer                   */
#define BIT31           (0x80000000)        /*!< Bit 31 mask of an 32 bit integer                   */


/**
 *  @brief  Byte Mask Definitions
 */
#define BYTE0_Msk       (0x000000FF)        /*!< Mask to get bit 0~bit 7 from a 32 bit integer      */
#define BYTE1_Msk       (0x0000FF00)        /*!< Mask to get bit 8~bit15 from a 32 bit integer      */
#define BYTE2_Msk       (0x00FF0000)        /*!< Mask to get bit16~bit23 from a 32 bit integer      */
#define BYTE3_Msk       (0xFF000000)        /*!< Mask to get bit24~bit31 from a 32 bit integer      */




/******************************************************************************
 * @brief      Extract byte 0 from specified 32-bit unsigned value
 *
 * @param[in]  u32Param: 32-bit unsigned value
 *
 * @return     Byte 0 value
 *
 ******************************************************************************/
#define GET_BYTE0(u32Param)       (((u32Param) & BYTE0_Msk)      )




/******************************************************************************
 * @brief      Extract byte 1 from specified 32-bit unsigned value
 *
 * @param[in]  u32Param: 32-bit unsigned value
 *
 * @return     Byte 1 value
 *
 ******************************************************************************/
#define GET_BYTE1(u32Param)       (((u32Param) & BYTE1_Msk) >>  8)




/******************************************************************************
 * @brief      Extract byte 2 from specified 32-bit unsigned value
 *
 * @param[in]  u32Param: 32-bit unsigned value
 *
 * @return     Byte 2 value
 *
 ******************************************************************************/
#define GET_BYTE2(u32Param)       (((u32Param) & BYTE2_Msk) >> 16)




/******************************************************************************
 * @brief      Extract byte 3 from specified 32-bit unsigned value
 *
 * @param[in]  u32Param: 32-bit unsigned value
 *
 * @return     Byte 3 value
 *
 ******************************************************************************/
#define GET_BYTE3(u32Param)       (((u32Param) & BYTE3_Msk) >> 24)




/******************************************************************************
 * @brief      Calculate the absolute value of x
 *
 * @param[in]  x: Integer value
 *
 * @return     The absolute value of x
 *
 ******************************************************************************/
#define ABS(x)                    (((x)<0)? (-(x)):(x))




/******************************************************************************
 * @brief      Convert bit band address and bit number into bit band alias address
 *
 * @param[in]  addr: Peripheral register address
 * @param[in]  addr: Register bit number
 *
 * @return     Bit band alias address
 *
 ******************************************************************************/
#define BITBAND(addr,bitnum)      (((addr) & 0xF0000000) + 0x2000000 + (((addr) & 0xFFFFF)<<5) + ((bitnum)<<2))




/******************************************************************************
 * @brief      Convert the address as a pointer and get its value
 *
 * @param[in]  addr: Memory address
 *
 * @return     Value in the memory address
 *
 ******************************************************************************/
#define MEM_ADDR(addr)            (*((volatile unsigned int *)(addr)))




/******************************************************************************
 * @brief      Get register bit value with bit-band feature
 *
 * @param[in]  addr  : Peripheral register address
 * @param[in]  bitnum: Register bit number
 *
 * @return     Bit value
 *
 ******************************************************************************/
#define REG_BIT(addr,bitnum)      MEM_ADDR(BITBAND((addr), (bitnum)))




/******************************************************************************
 * @brief      Set register bits
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bits mask
 *
 * @return     None
 *
 ******************************************************************************/
#define SET_BITS(REG, MASK)       ((REG) |= (MASK))




/******************************************************************************
 * @brief      XOR register bits
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bits mask
 *
 * @return     None
 *
 ******************************************************************************/
#define XOR_BITS(REG, MASK)       ((REG) ^= (MASK))




/******************************************************************************
 * @brief      Read register bits
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bits mask
 *
 * @return     Register bit value (masked value)
 *
 ******************************************************************************/
#define READ_BITS(REG, MASK)      ((REG) & (MASK))




/******************************************************************************
 * @brief      Clear register bits
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bits mask
 *
 * @return     None
 *
 ******************************************************************************/
#define CLEAR_BITS(REG, MASK)     ((REG) &= ~(MASK))




/******************************************************************************
 * @brief      Write value to register bit-field
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bit-field mask
 * @param[in]  POS : Register bit-field position
 * @param[in]  VAL : Register bit-field value
 *
 * @return     None
 *
 ******************************************************************************/
#define WRITE_FIELD(REG, MASK, POS, VAL)    ((REG) = (((REG) & (~(MASK))) | (((uint32_t)(VAL)) << (POS))))




/******************************************************************************
 * @brief      Read register bit-field value
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bit-field mask
 * @param[in]  POS : Register bit-field position
 *
 * @return     Register bit-field value
 *
 ******************************************************************************/
#define READ_FIELD(REG, MASK, POS)          (((REG) & (MASK)) >> (POS))




/******************************************************************************
 * @brief      Clear register bit-field
 *
 * @param[in]  REG : Peripheral register
 * @param[in]  MASK: Register bit-field mask
 *
 * @return     None
 *
 ******************************************************************************/
#define CLEAR_FIELD(REG, MASK)    ((REG) &= ~(MASK))




/******************************************************************************
 * @brief      Clear register
 *
 * @param[in]  REG: Peripheral register
 *
 * @return     None
 *
 ******************************************************************************/
#define CLEAR_REG(REG)            ((REG) = (0x0))




/******************************************************************************
 * @brief      Write value to register
 *
 * @param[in]  REG: Peripheral register
 * @param[in]  VAL: Value to be written
 *
 * @return     None
 *
 ******************************************************************************/
#define WRITE_REG(REG, VAL)       ((REG) = (VAL))




/******************************************************************************
 * @brief      Read register value
 *
 * @param[in]  REG: Peripheral register
 *
 * @return     Register value
 *
 ******************************************************************************/
#define READ_REG(REG)             ((REG))




/******************************************************************************
 * @brief      Modify register bits value
 *
 * @param[in]  REG      : Peripheral register
 * @param[in]  CLEARMASK: Register bits value clear mask
 * @param[in]  SETMASK  : Register bits value set mask
 *
 * @return     None
 *
 ******************************************************************************/
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))




/******************************************************************************
 * @brief      Get the position of first '1' in data 'VAL'
 *
 * @param[in]  VAL: Data value, usually mask value
 *
 * @return     None
 *
 ******************************************************************************/
#define POSITION_VAL(VAL)         (__CLZ(__RBIT(VAL)))




/******************************************************************************
 * @brief      Declare un-used variable to avoid warning reported by Compiler
 *
 * @param[in]  x: Variable name
 *
 * @return     None
 *
 ******************************************************************************/
#define UNUSED(x)                 ((void)(x))




/******************************************************************************
 * @brief      Rounding-off for integer division
 *
 * @param[in]  A: Dividend
 * @param[in]  B: Divisor
 *
 * @return     The value of Quotient
 *
 ******************************************************************************/
#define U32DIV(A,B) ( ( (uint32_t)(A)*1000 + (uint32_t)(B)*500 ) / (uint32_t)(B) / 1000 )




/******************************************************************************
 * @brief      Calculate the Quotient of (A - 1) / B + 1
 *
 * @param[in]  A: Dividend
 * @param[in]  B: Divisor
 *
 * @return     The value of Quotient
 *
 ******************************************************************************/
#define CEIL_DIV(A,B) ( ( (A) - 1 ) / (B) + 1 )




/******************************************************************************
 * @brief      Calculate the Quotient of A / B
 *
 * @param[in]  A: Dividend
 * @param[in]  B: Divisor
 *
 * @return     The value of Quotient
 *
 ******************************************************************************/
#define FLOOR_DIV(A,B) ( (A) / (B) )




/******************************************************************************
 * @brief       Write 8/16/32/64-bit data to the specified address
 *
 * @param[in]   ADDR: Address to be written to
 * @param[in]   VAL : Value to be written
 *
 * @return      None
 *
 ******************************************************************************/
#define WRITE_U8(ADDR, VAL)         (*(__IO uint8_t*)(ADDR) = (VAL))
#define WRITE_U16(ADDR, VAL)        (*(__IO uint16_t*)(ADDR) = (VAL))
#define WRITE_U32(ADDR, VAL)        (*(__IO uint32_t*)(ADDR) = (VAL))
#define WRITE_U64(ADDR, VAL)        (*(__IO uint64_t*)(ADDR) = (VAL))




/**
 *  @brief  SPC1169 Peripheral Header Files
 */
#include "adc.h"
#include "clock.h"
#include "comp.h"
#include "crc.h"
#include "delay.h"
#include "dma.h"
#include "ecap.h"
#if defined(ENGINEERING)
    #include "engr.h"
#endif
#include "flashc.h"
#include "gpio.h"
#include "hwlib.h"
#include "i2c.h"
#include "pga.h"
#include "phcomp.h"
#include "pin.h"
#include "power.h"
#include "pwm.h"
#include "spi.h"
#include "system.h"
#include "timer.h"
#include "wdt.h"
#include "uart.h"
#include "can.h"


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* end of SPC1169_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
