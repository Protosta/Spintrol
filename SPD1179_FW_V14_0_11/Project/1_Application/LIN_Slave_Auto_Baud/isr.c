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
 * @brief  This function handles MEM interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void MEM_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles EPWRTZ0 interrupt request
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
// void UART0_IRQHandler(void)
// {

// }




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
//void UART1_IRQHandler(void)
//{

//}




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
 * @brief  This function handles CANTRG0 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG0_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG1 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG1_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG2 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG2_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG3 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG3_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG4 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG4_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG5 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG5_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG6 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG6_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANTRG7 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANTRG7_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles CANMISC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CANMISC_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles I2C interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void I2C_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 0 EOC interrupt request
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
 * @brief  This function handles ADC channel 1 EOC interrupt request
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
 * @brief  This function handles ADC channel 2 EOC interrupt request
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
 * @brief  This function handles ADC channel 3 EOC interrupt request
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
 * @brief  This function handles ADC channel 4 EOC interrupt request
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
 * @brief  This function handles ADC channel 5 EOC interrupt request
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
 * @brief  This function handles ADC channel 6 EOC interrupt request
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
 * @brief  This function handles ADC channel 7 EOC interrupt request
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
 * @brief  This function handles ADC channel 8 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH8_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 9 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH9_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 10 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH10_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 11 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH11_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 12 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH12_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 13 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH13_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 14 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH14_IRQHandler(void)
{

}




/*******************************************************************************
 * @brief  This function handles ADC channel 15 EOC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void ADCCH15_IRQHandler(void)
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
 * @brief  This function handles PWM3 interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM3_IRQHandler(void)
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
 * @brief  This function handles PWM3 Trip-zone interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void PWM3TZ_IRQHandler(void)
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
void ECAP_IRQHandler(void)
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
//void TIMER1_IRQHandler(void)
//{

//}




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
 * @brief  This function handles CRC interrupt request
 *
 * @param  None
 *
 * @return None
 *
 ******************************************************************************/
void CRC_IRQHandler(void)
{

}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
