/******************************************************************************
 * @file     isr.c
 * @brief    Interrupt service routine functions.
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
#include "isr.h"




//---------------------------------------------------------------------------
// Cortex-M4 Processor Exceptions Handlers
//---------------------------------------------------------------------------

/*******************************************************************************
 * @brief      This function handles NMI exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void NMI_Handler(void)
{
    printf("NMI_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles Hard Fault exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void HardFault_Handler(void)
{
    printf("HardFault_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles Memory Manage exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void MemManage_Handler(void)
{
    printf("MemManage_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles Bus Fault exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void BusFault_Handler(void)
{
    printf("BusFault_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles Usage Fault exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void UsageFault_Handler(void)
{
    printf("UsageFault_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles SVCall exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void SVC_Handler(void)
{
    printf("SVC_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles Debug Monitor exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void DebugMon_Handler(void)
{
    printf("DebugMon_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles PendSVC exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void PendSV_Handler(void)
{
    printf("PendSV_Handler\n");
}




/*******************************************************************************
 * @brief      This function handles SysTick interrupt request
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void SysTick_Handler(void)
{
    printf("SysTick_Handler\n");
}




/******************************************************************************/
/*                 SOC Peripherals Interrupt Handlers                         */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_spc1169.s).                                                 */
/******************************************************************************/

/*******************************************************************************
 * @brief      This function handles Memory Manage exception
 *
 * @param[in]  none
 *
 * @return     none
 *
 ******************************************************************************/
void EPWRTZ0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles EPWRTZ1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void EPWRTZ1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles WDT1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void WDT1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles GPIO Level triggered interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void GPIO_LEVEL_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles GPIO Edge triggered interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void GPIO_EDGE_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles UART0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void UART0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles SPI0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void SPI0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles UART1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void UART1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles SPI1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void SPI1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC2 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH2_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC3 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH3_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC4 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH4_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC5 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH5_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC6 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH6_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC EOC7 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH7_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC PPU0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCPPU0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC PPU1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCPPU1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC PPU2 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCPPU2_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PWM0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PWM1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PWM2 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM2_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PWM0 Trip-zone interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM0TZ_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PWM1 Trip-zone interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM1TZ_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PWM2 Trip-zone interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM2TZ_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles PHCOMP interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PHCOMP_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ECAP interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
//void ECAP_IRQHandler(void)
//{

//}




/*******************************************************************************
 * @brief  This function handles TIMER0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void TIMER0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles TIMER1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void TIMER1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles TIMER2 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void TIMER2_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles DMAC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void DMAC_IRQHandler(void)
{

}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
