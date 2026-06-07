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


uint32_t              u32PWMPeriod;         /* PWM Period*/
uint16_t              u16PREDRIID;          /* PRE-DRIVER mode ID */
ErrorStatus           eErrorState;
#define               Wake_Up_Mode          0


/******************************************************************************
* @brief      System stop
*
* @param[in]  None
*
* @return     None
* @note       - System will stop if no wakeup condition exist 
*             - System will not stop if wakeup condition exist 
*
******************************************************************************/
void SYSTEM_Stop(void)
{
    ErrorStatus eStatus;
    uint32_t i;
    uint32_t u32Temp;
    ErrorStatus (*funcPtr)(void);
    funcPtr = (ErrorStatus (*)(void))(0x2c39UL);
    
    /* Disable interrupt */
    __disable_irq(); 
    
    /* Save NMIE setting */
    u32Temp = READ_REG(SYSTEM->NMIE);    
    
    /* Disable all NMI interrupt */
    SYSTEM_DisableNonMaskableInt(NMI_EVENT_ALL);
    
    /* Stop function:
     * (1) Flash power down
     * (2) Make whole system go to stop
     * (3) Re-initialize the FLASH after stop exit
     * (4) Resume FLASH timing
     * note: 
     * (1) If any error occured, try 3 times     
     */
    for (i = 0U; i < 3U; i++)
    {
        /* If stop communication(between LV and HV) is wrong, then return error */
        eStatus = (*funcPtr)();
        if (eStatus == SUCCESS)
        {
            break;
        }    
    }
    
    /* 
     * (1) Write 1 to NMIC.PLLUNLOCK to clear the possible alarm of clock lock loss 
     *     during setup process 
     * (2) Write 1 to other NMIC bits to keep NMI events clean
     */
    SYSTEM_ClearNonMaskableInt(NMI_EVENT_ALL);
    
    /* Restore NMIE setting */
    WRITE_REG(SYSTEM->NMIE, u32Temp);  
    
    /* Enable interrupt */
    __enable_irq(); 
}


/*************************************************************************************************************************
 *
 * @brief      In this case, we use signal to wakeup the system from stop state.
 * @note       1, If MCU over temperature 105 degrees Celsius, can not enter SYSTEM_Stop(), this operation has been showed 
 *             in the code.
 *
 *************************************************************************************************************************/
int main(void)
{
    int32_t * pi32TrimValue;
    int32_t i32Temperature;
    
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
    
    /* Cyclic sense wake up setting */
    #elif(Wake_Up_Mode == 3)
    /* Use GPIO9 as the wake up source */
    /* Config pin as GPIO input */
    PIN_SetPinAsGPIO((PIN_NameEnum)PIN_GPIO9);
    GPIO_SetPinDir((PIN_NameEnum)PIN_GPIO9, GPIO_INPUT);

    /* Set GPIO number and active level */
    SYSTEM->GPIOWKUPCTL = (LOW << GPIOWKUPCTL_STOPWKUPPOL_Pos) |
                          (PIN_GPIO9  << GPIOWKUPCTL_STOPWKUPIO_Pos) |
                          GPIOWKUPCTL_STOPWKUPWE_ENABLE;
    
    printf("LIN or MON must be enabled, otherwise cyclic wake up can not be disabled\n");
    eErrorState = EPWR_WriteRegisterField(HV_REG_PMUCTL, 
                                         PMUCTL_LINWKUPEN_Msk | PMUCTL_MONWKUPEN_Msk , 
                                         PMUCTL_LINWKUPEN_DISABLE | PMUCTL_MONWKUPEN_ENABLE );
    if (eErrorState == ERROR)
    {
        printf("Write PMUCTL register FAIL\n");
        return 0;
    }
    
    printf("Enable cyclic sense wake up and disable cyclic wake up\n");
    eErrorState = EPWR_WriteRegisterField(HV_REG_PMUCTL, 
                                         PMUCTL_CYCSENWKUPEN_Msk | PMUCTL_CYCWKUPEN_Msk, 
                                         PMUCTL_CYCSENWKUPEN_ENABLE | PMUCTL_CYCWKUPEN_DISABLE);
    if (eErrorState == ERROR)
    {
        printf("Write PMUCTL register FAIL\n");
        return 0;
    }
     
    /* Dead time is (DEADCNT+1) * 2ms, sense window is (SENSECNT+1) * 10us */
    eErrorState = EPWR_WriteRegisterField(HV_REG_CYCSENSECTL, CYCSENSECTL_DEADCNT_Msk | \
            CYCSENSECTL_SENSECNT_Msk, CYCSENSECTL_DEADCNT_(10) | CYCSENSECTL_SENSECNT_(15));
    if (eErrorState == ERROR)
    {
        printf("Write CYCSENSECTL register FAIL\n");
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

    /* Enable monitor MCU */
    SYSTEM_EnableMonitorItem(MONITOR_MCU_TEMPERATURE);
    ADC_EnableTSensor(ADC);
    /* Wait for sampling to end */
    Delay_Ms(500);
    
    /* TPMUOFFSET
     * TPMUGAIN
     * TLINOFFSET
     * TLINGAIN
     * TMCUOFFSET
     * TMCUGAIN   
     */
    pi32TrimValue = (int32_t *)0x11001168;
    
    /* The if branch is equivalent to the else branch, and the if branch is more accurate */
    if (pi32TrimValue[4] != 0xffffffff)
    {
        i32Temperature = ((pi32TrimValue[4] + pi32TrimValue[5] * SYSTEM->TMCUCODE )/65536);
    }
    else
    {
        i32Temperature = ((4096 * SYSTEM->TMCUCODE - 305657)/1081);    
    }
    
    /* If MCU over temperature 105 degrees Celsius, can not enter SYSTEM_Stop() */
    if (i32Temperature > 105)
    {
        printf("the MCU temperature is %d\n", i32Temperature);  
        return 0;
    }

    SYSTEM_Stop();

    printf("total test passed\n");
    
    while (1)
    {

    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/



