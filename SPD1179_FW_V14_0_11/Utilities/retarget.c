/******************************************************************************
 * @file     retarget.c
 * @brief    'Retarget' layer for target-dependent low level functions
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

#include <stdio.h>
#include "spc1169.h"




#ifndef __GNUC__
    /* Arm and IAR setting in this branch */
    /**
     *  @brief  These must be defined to avoid linking in stdio.o from the C Library
     */
    struct __FILE
    {
        int handle;   /* Add whatever you need here */
    };
    FILE __stdout;
    FILE __stdin;
    FILE __stderr;




    /******************************************************************************
     * @brief      Get character from UART
     *
     * @param[in]  f:  Pointer to a FILE object that identifies the stream on which
     *                 the operation is to be performed
     *
     * @return     The character read from UART
     *
     ******************************************************************************/
    int fgetc(FILE *f)
    {
        /* Wait until data is available in RBR or the FIFO */
        while ((UART0->UARTSTS & UARTSTS_RXNE_Msk) == UARTSTS_RXNE_EMPTY)
        {
        }

        return (int)UART_ReadByte(UART0);
    }




    /******************************************************************************
     * @brief      Write character to stream
     *
     * @param[in]  ch:  Character to be written
     * @param[in]  f :  Pointer to a FILE object that identifies the stream on which
     *                  the operation is to be written
     *
     * @return     The same character that has been written
     *
     ******************************************************************************/
    int fputc(int ch, FILE *f)
    {
        volatile uint32_t u32Timeout;
        
        if (ch == '\n')
        {
            UART_WriteByte(UART0, (uint8_t)'\r');
            
            for ( u32Timeout = 0xffffffffU ; u32Timeout > 0U ; u32Timeout-- )
            {
                if ( 0U != UART_GetStatus(UART0, UART_STS_TX_EMPTY) )
                {
                    break ;
                }
            }
        }

        UART_WriteByte(UART0, (uint8_t) ch);
        
        for ( u32Timeout = 0xffffffffU ; u32Timeout > 0U ; u32Timeout-- )
        {
            if ( 0U != UART_GetStatus(UART0, UART_STS_TX_EMPTY) )
            {
                break ;
            }
        }

        return ch;
    }




    void _ttywrch(int ch)
    {
        UART_WriteByte(UART0, (uint8_t) ch);
        while ((UART0->UARTSTS & UARTSTS_TXEMPTY_Msk) == UARTSTS_TXEMPTY_NOT_EMPTY)
        {
        }
    }




    int __backspace(FILE *f)
    {
        return 0;
    }




    int ferror(FILE *f)
    {
        /* Your implementation of ferror */
        return EOF;
    }




    void _sys_exit(int return_code)
    {
        /* Endless loop */
        while (1);
    }
  
#else
    __attribute__((weak)) void _close(){}
    __attribute__((weak)) void _fstat(){}
    __attribute__((weak)) void  _getpid(){}
    __attribute__((weak)) void _isatty(){}
    __attribute__((weak)) void _kill(){}
    __attribute__((weak)) void _lseek(){}
    __attribute__((weak)) void _read(){}

    int _write(int file, char *ptr, int len)
    {
        int DataIdx;
        for (DataIdx = 0; DataIdx < len;DataIdx++)
        {
            if (ptr[DataIdx] == '\n')
            {
                UART_WriteByte(UART0, (uint8_t)'\r');
                while ((UART0->UARTSTS & UARTSTS_TXEMPTY_Msk) == UARTSTS_TXEMPTY_NOT_EMPTY)
                {
                }
            }

            UART_WriteByte(UART0, (uint8_t) ptr[DataIdx] );
            while ((UART0->UARTSTS & UARTSTS_TXEMPTY_Msk) == UARTSTS_TXEMPTY_NOT_EMPTY)
            {
            }
        }
        
        return len;
    }

#endif  

