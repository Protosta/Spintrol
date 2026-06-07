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
#include "spd1179.h"
#include <stdio.h>

uint16_t              u16PREDRIID;          /* PRE-DRIVER mode ID */
ErrorStatus           eErrorState;
#define               Wake_Up_Mode          0


/******************************************************************************
* @brief      System sleep
*
* @param[in]  None
*
* @return     None
* @note       - System will sleep if no wakeup condition exist 
*             - System will reset if wakeup condition exist 
*
******************************************************************************/
void SYSTEM_Sleep(void)
{
    ErrorStatus (*funcPtr)(void);
    funcPtr = (ErrorStatus (*)(void))(0x2bf5UL);
    
    /* Disable interrupt */
    __disable_irq(); 
    
    /* Disable all NMI interrupt */
    SYSTEM_DisableNonMaskableInt(NMI_EVENT_ALL);
    
    /* 
     * Sleep function:
     * (1) Flash power down
     * (2) Make whole system go to sleep
     * (3) Re-initialize the FLASH if whole system can not go to sleep
     */
    (*funcPtr)(); 
    
    /* Turn off PWM to prevent short-circuit between upper and lower bridges */
    PWM_StopCounter(PWM0);
    PWM_StopCounter(PWM1);
    PWM_StopCounter(PWM2);
    PWM_StopCounter(PWM3);
    
    /* HV register reset */
    HV_Reset();
    
    /* System reset */
    NVIC_SystemReset();
}
     

/*************************************************************************************************************************
 *
 * @brief      In this case, we use signal to wakeup the system from sleep state.
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

    printf("Enter the test\n");

    /* HV reset */
    eErrorState = HV_Reset();
    if (eErrorState == ERROR)
    {
        printf("HV_Reset FAIL\n");
        return 0;
    }
    else
    {
        printf("HV_Reset SUCCESS\n");
    }

    /* HV init */
    eErrorState = HV_Init(&u16PREDRIID);
    if (eErrorState == ERROR)
    {
        printf("Init PRE-DRIVER mode FAIL\n");
        return 0;
    }
    else
    {
        printf("Init PRE-DRIVER mode SUCCESS[ID:%d]\n", u16PREDRIID);
    }

    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
        return 0;
    }

    /* LIN wake up setting */
    #if(Wake_Up_Mode == 0)
    eErrorState = EPWR_WriteRegisterField(HV_REG_PMUCTL, PMUCTL_LINWKUPEN_Msk | 
      PMUCTL_CYCWKUPEN_Msk, PMUCTL_LINWKUPEN_ENABLE | PMUCTL_CYCWKUPEN_DISABLE);
    if (eErrorState == ERROR)
    {
        printf("Write PMUCTL register FAIL\n");
        return 0;
    }

    /* MON asynchronous wake up setting */
    #elif(Wake_Up_Mode == 1)
    eErrorState = EPWR_WriteRegisterField(HV_REG_PMUCTL, PMUCTL_MONWKUPEN_Msk |
                                    PMUCTL_LINWKUPEN_Msk | PMUCTL_CYCWKUPEN_Msk,
                                    PMUCTL_MONWKUPEN_ENABLE | PMUCTL_LINWKUPEN_DISABLE |
                                    PMUCTL_CYCWKUPEN_DISABLE);
    if (eErrorState == ERROR)
    {
        printf("Write PMUCTL register FAIL\n");
        return 0;
    }

    /* Wakeup level is high, MON pin need pull down */
    eErrorState = EPWR_WriteRegisterField(HV_REG_MONCTL, MONCTL_WKUPPOL_Msk |
                               MONCTL_EN_Msk | MONCTL_PULLMODE_Msk,
                               MONCTL_WKUPPOL_ACTIVE_HIGH | MONCTL_EN_ENABLE |
                               MONCTL_PULLMODE_PULL_DOWN);
    if (eErrorState == ERROR)
    {
        printf("Write MONCTL register FAIL\n");
        return 0;
    }
    
    /* Cyclic wake up setting */
    #elif(Wake_Up_Mode == 2)
    eErrorState = EPWR_WriteRegisterField(HV_REG_PMUCTL, PMUCTL_CYCWKUPEN_Msk |
                                          PMUCTL_LINWKUPEN_Msk, PMUCTL_CYCWKUPEN_ENABLE |
                                          PMUCTL_LINWKUPEN_DISABLE);
    if (eErrorState == ERROR)
    {
        printf("Write PMUCTL register FAIL\n");
        return 0;
    }
    
    /* Dead time is (DEADCNT+1) * 2ms */
    eErrorState = EPWR_WriteRegisterField(HV_REG_CYCWKUPCTL, CYCWKUPCTL_DEADCNT_Msk, CYCWKUPCTL_DEADCNT_(5));
    if (eErrorState == ERROR)
    {
        printf("Write CYCWKUPCTL register FAIL\n");
        return 0;
    }
    #endif

    /* Enable sleep/stop command */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_PMU_CMD);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
        return 0;
    }
    
    SYSTEM_Sleep();
    
    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
