 /******************************************************************************
 * @file     main.c
 * @brief    Main program body
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

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif

#include "func.h"


#define         VectorTableLoadAddr                     0x10000000
#define         TimerPeridCount                         1 //1ms
#define         OperationADDR                           0x1000F000

#define         VECTOR_NUM                              79

/* Save interrupt vector table */
uint32_t u32aRAMVector[VECTOR_NUM] __attribute__((aligned(0x400))) = {0};

uint32_t u32VectorCnt = 0;
int16_t i16Result;
int32_t i32_PWM_A = 90;
int32_t i32_PWM_B = 100;
int32_t i32_PWM_C = 110;
int32_t i32_PWM   = 0;

/*************************************************************************************************************************
 *
 * @brief      This demo may be useful when you want to wrote/erase flash, which may be break-in by interrupt.
 *
 *************************************************************************************************************************/


int main(void)
{
    CLOCK_InitWithRCO(100000000);

    Delay_Init();

    /*
     * Init the UART
     */
    PIN_SetChannel(PIN_GPIO10, PIN_GPIO10_UART0_TXD);
    PIN_SetChannel(PIN_GPIO11, PIN_GPIO11_UART0_RXD);
    UART_Init(UART0, 38400);
    UART_EnableTx(UART0);
    UART_EnableRx(UART0);

    pHWLIB->FLASHC_Init();
    
    /* Copy vector table to RAM */
    for(u32VectorCnt = 0; u32VectorCnt < VECTOR_NUM; u32VectorCnt++)
    {
        u32aRAMVector[u32VectorCnt] = 
               *((volatile uint32_t *)(VectorTableLoadAddr + u32VectorCnt * 4));
    }

    /* Redirection the Vector Address */
    SCB->VTOR = (uint32_t)u32aRAMVector;
    printf("Exception vector table Addr is : %x\n", SCB->VTOR);

    /* Flash operation allow */
    FLASHC_WALLOW();

    /* Init Timer1 */
    TIMER_Init(TIMER1, TimerPeridCount);

    /* Open Global INT for TIMER1 */
    NVIC_EnableIRQ(TIMER1_IRQn);

    /* Enable Timer interrupt */
    TIMER_EnableInt(TIMER1);

    TIMER_Enable(TIMER1);

    while (1)
    {
        printf("Flash XIP will be closed...\n");
        pHWLIB->FLASHC_EraseSector(OperationADDR);
        printf("Flash XIP has been opened...\n");
        
        printf("i16Result %d, i32_PWM_A %d, i32_PWM_B %d, i32_PWM_C %d, i32_PWM %d\n", i16Result, i32_PWM_A, i32_PWM_B, i32_PWM_C, i32_PWM);
    }

}



/* When Erase Flash, XIP Will be Closed, At that moment, If TIMER1 Interrupt 
      Happend, CPU will go to Fetch TIMER1 Driver Code,So we Must Put TIMER1 Driver 
      Code and sub functions into RAM */
_RAM_FUNC_ void TIMER1_IRQHandler(void)
{
    i16Result = A(-16384);
    
    B(100, &i32_PWM_A, &i32_PWM_B, &i32_PWM_C);
    
    C(&i32_PWM);

    /* Clear the INT */
    TIMER_ClearInt(TIMER1);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
