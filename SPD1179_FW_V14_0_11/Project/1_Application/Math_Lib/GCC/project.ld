/******************************************************************************
 * @file     project.ld
 * @brief    Link file
 * @version  VXX.XX.XX
 * @date     XX-XXX-XXXX
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

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0x400;;      /* required amount of heap  */
_Min_Stack_Size = 0x400;; /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
FLASH (rx)      : ORIGIN = 0x10000000, LENGTH = 0x0000F000
RAM (rw)       : ORIGIN = 0x1FFFC000, LENGTH = 0x00003000
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    /*
     * After build, for peripherals, the name can be find in map:
     *  ....../clock.c.obj
     *  ....../uart.c.obj
     *  ......
     *
     * For example, if you want to exclude uart and libarm_cortexM4lf_math.a text
     *  EXCLUDE_FILE(*uart.c.obj *cortexM4lf_math.a)*(.text)
     *  EXCLUDE_FILE(*uart.c.obj *cortexM4lf_math.a)*(.text*)
     */
    EXCLUDE_FILE(*cortexM4lf_math.a)*(.text)
    EXCLUDE_FILE(*cortexM4lf_math.a)*(.text*)
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    /*
     * After build, for peripherals, the name can be find in map:
     *  ....../clock.c.obj
     *  ....../uart.c.obj
     *  ......
     *
     * For example, if you want to exclude uart and libarm_cortexM4lf_math.a rodata
     *  EXCLUDE_FILE(*uart.c.obj *cortexM4lf_math.a)*(.rodata)
     *  EXCLUDE_FILE(*uart.c.obj *cortexM4lf_math.a)*(.rodata*)
     */
    EXCLUDE_FILE(*cortexM4lf_math.a)*(.rodata)
    EXCLUDE_FILE(*cortexM4lf_math.a)*(.rodata*)
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    /*
     * After build, the name can be find in map, for example:
     *  ../libarm_cortexM4lf_math.a(arm_cos_f32.o)
     *          arm_cos_f32
     *  ../libarm_cortexM4lf_math.a(arm_common_tables.o)
     *          sinTable_f32
     * 
     * If you want libarm_cortexM4lf_math.a run in RAM:
     *  1, exclude libarm_cortexM4lf_math.a in >FLASH;
     *  2, add following code to >RAM AT> FLASH:
     *    *arm_cos_f32.o(.text)
     *    *arm_cos_f32.o(.text*)
     *    *arm_common_tables.o(.rodata)
     *    *arm_common_tables.o(.rodata*)
     *
     * If you want uart code run in RAM:
     *  1, exclude uart in >FLASH;
     *  2, add following code to >RAM AT> FLASH:
     *    *uart.c.obj(.text)
     *    *uart.c.obj(.text*)
     *    *uart.c.obj(.rodata)
     *    *uart.c.obj(.rodata*)
     */
    *arm_cos_f32.o(.text)
    *arm_cos_f32.o(.text*)
    *arm_common_tables.o(.rodata)
    *arm_common_tables.o(.rodata*)
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}