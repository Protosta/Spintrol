/******************************************************************************
 * @file     lin_lld_UART.c
 * @brief    UART for LIN network
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


#include "lin_lld_uart.h"
#include "lin_common_proto.h"


#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#endif


/***** Globle variable data *****/


typedef struct
{
    uint16_t cnt_10ms;
    uint16_t cnt_100ms;
}loop_t;

loop_t loop; 
/**
* @var static l_u8          ifc
*/
l_u8          ifc = 0xFF;


volatile l_u8          step = 0;

/**
* @var static lin_status    l_status
*/
static lin_status    l_status;

/**
* @var static l_u8          cnt_byte
*/
static l_u8          cnt_byte = 0;

/**
* @var static l_u8         *ptr
*/
static l_u8          *ptr = 0;

/**
* @var static l_u8          current_id
*/
static l_u8          current_id = 0x00;

/**
* @var static l_u8         *response_buffer
*/
static l_u8          *response_buffer = 0;

/**
* @var static l_u8          pid
*/
static l_u8          pid = 0x80;

extern l_u8 lin_lld_response_buffer[10];


l_u8 lin_configuration_ID_and_NAD[LIN_SIZE_OF_CFG + 8 ]= {0xFF};

void lin_revert_default_baud
(
)
{
    UART_InitSpeed(UART1, LIN_BAUD_RATE);
    UART_EnableAutoBaud(UART1);
}

#ifdef LOAD_ID_NAD_FROM_FLASH 
void lin_init_id_or_nad_from_flash()
{
    uint32_t i;
    
    /* Get data from Flash */
    pHWLIB->FLASHC_Read((uint32_t *)lin_configuration_ID_and_NAD, OPERATION_ADDR, (((LIN_SIZE_OF_CFG + 1)/8 + 1) *2));
    /* If data format is right, use the data */    
    if ((lin_configuration_ID_and_NAD[0] == 0x00) &&  (lin_configuration_ID_and_NAD[LIN_SIZE_OF_CFG - 1] == 0xFF))
    {
        for (i =0; i < LIN_SIZE_OF_CFG; i++)
        {
           lin_configuration_RAM[i] = lin_configuration_ID_and_NAD[i];
           printf("%x\n", lin_configuration_RAM[i]);
        }

        lin_configured_NAD = lin_configuration_ID_and_NAD[LIN_SIZE_OF_CFG];
        printf("%x\n", lin_configured_NAD);          
    }
    /* If data format is not right, init Flash, do not change data in lin_configuration_RAM and lin_configured_NAD */   
    else
    {
        for (i =0; i < LIN_SIZE_OF_CFG; i++)
        {
            lin_configuration_ID_and_NAD[i] = lin_configuration_ROM[i];
        }
        lin_configuration_ID_and_NAD[LIN_SIZE_OF_CFG] = lin_initial_NAD;
        
        pHWLIB->FLASHC_EraseSector(OPERATION_ADDR);
        pHWLIB->FLASHC_Program((uint32_t *)lin_configuration_ID_and_NAD, OPERATION_ADDR, (((LIN_SIZE_OF_CFG + 1)/8 + 1) *2));
        
        printf("Program\n");

        for (i =0; i < LIN_SIZE_OF_CFG; i++)
        {
           printf("%x\n", lin_configuration_RAM[i]);
        }

        printf("%x\n", lin_configured_NAD);         
    }   
}

void lin_save_configuration()
{
    uint32_t i;
    if (lin_save_configuration_flg == 1)
    {
        for (i =0; i < LIN_SIZE_OF_CFG; i++)
        {
            lin_configuration_ID_and_NAD[i] = lin_configuration_RAM[i];
        }
        lin_configuration_ID_and_NAD[LIN_SIZE_OF_CFG] = lin_configured_NAD;
        
        pHWLIB->FLASHC_EraseSector(OPERATION_ADDR);
        pHWLIB->FLASHC_Program((uint32_t *)lin_configuration_ID_and_NAD, OPERATION_ADDR, (((LIN_SIZE_OF_CFG + 1)/8 + 1) *2));
            
        lin_save_configuration_flg = 0;
    }
}
#else

#endif

void lin_Cr_or_As_timeout()
{
    #if (_TL_FRAME_SUPPORT_ ==  _TL_MULTI_FRAME_)
    if (LD_CHECK_N_CR_TIMEOUT == tl_check_timeout_type)
    {
        if(0 == --tl_check_timeout)
        {
            printf("LD_CHECK_N_CR_TIMEOUT\n");
            /* update status of transport layer */
            tl_service_status = LD_SERVICE_ERROR;
            tl_receive_msg_status = LD_N_CR_TIMEOUT;
            tl_rx_msg_status = LD_N_CR_TIMEOUT;
            tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
            tl_diag_state = LD_DIAG_IDLE;
        }
    }

    if (LD_CHECK_N_AS_TIMEOUT == tl_check_timeout_type)
    {
        if(0 == --tl_check_timeout)
        {
            printf("LD_CHECK_N_AS_TIMEOUT\n");
            /* update status of transport layer */
            tl_service_status = LD_SERVICE_ERROR;
            tl_tx_msg_status = LD_N_AS_TIMEOUT;
            tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
            tl_diag_state = LD_DIAG_IDLE;
        }
    } 
    #else
    /* Single Frame */
    if (LD_CHECK_N_AS_TIMEOUT == tl_check_timeout_type)
    {
        if(0 == --tl_check_timeout)
        {   /* update status of transport layer */
            tl_service_status = LD_SERVICE_ERROR;
            tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
        }
    }
    #endif
}

void lin_lld_uart()
{
    #ifdef LOAD_ID_NAD_FROM_FLASH      
        lin_init_id_or_nad_from_flash();
    #else
    
    #endif
    
    while(1)
    {   

        if( loop.cnt_10ms >= 1 )//10ms
        {
            loop.cnt_10ms = 0;
            
            #ifdef LOAD_ID_NAD_FROM_FLASH   
                lin_save_configuration();
            #else

            #endif 
        }
 
        if( loop.cnt_100ms >= 10)//100ms
        {
            loop.cnt_100ms = 0;
            
            lin_Cr_or_As_timeout();
        }
    }
}

void TIMER2_IRQHandler()
{
    loop.cnt_10ms++;
    loop.cnt_100ms++;
    /* Clear the INT */
    TIMER_ClearInt(TIMER2);
}

        
void TIMER1_IRQHandler()
{
    if (UART_GetIntFlag(UART1, UART_INT_LIN_BIT_ERROR) == 0)
    {
        /* TX transfer complete */
        l_status.byte |= LIN_STA_SUCC_TRANSFER;

        /* trigger CALLBACK */
        CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_TX_COMPLETED, current_id);
    }
    else
    {       
        UART_ClearInt(UART1, UART_INT_LIN_BIT_ERROR);
    }
    
    lin_goto_idle_state();
    
    TIMER_Disable(TIMER1);
    /* Clear the INT */
    TIMER_ClearInt(TIMER1);
}

void UART1_IRQHandler
(
)
{
    uint8_t i;
    if (UART_GetIntFlag(UART1, UART_INT_LIN_ID_MATCH) != 0)
    {
        /* reset lin status */
        l_status.byte = LIN_STA_BUS_ACTIVITY;

        /******************************
        *** 4.3 SLAVE: Receiving PID
        *******************************/
        /* Keep the PID */
        pid = LIN_GetRxID(UART1);

        /* checkparity and extrait PID */
        current_id = lin_process_parity(pid, CHECK_PARITY);

        if (current_id != 0xFF)
        {

            /*****************************************/
            /*** ID received correctly - parity OK ***/
            /*****************************************/
            /* trigger callback */
            CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_PID_OK, current_id);
        }
        else
        {
            /*****************************************/
            /*** ID Parity Error                   ***/
            /*****************************************/
            /* set lin status: parity_error */
            l_status.byte |= LIN_STA_PARITY_ERR;
            /* trigger callback */
            CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_PID_ERR, 0xFF);
            lin_goto_idle_state();
        }
        
        UART_ClearInt(UART1, UART_INT_LIN_ID_MATCH);
    }
    else if (UART_GetIntFlag(UART1, UART_INT_RX_REQ) != 0)
    {
        ptr++;
        for (i = 0; i < (response_buffer[0] + 1); i++)
        {
            *(ptr) = UART_ReadByte(UART1);
            ptr++;
            cnt_byte++;
        }
        
        /* Check bytes received fully */
        if (cnt_byte == (response_buffer[0] + 1))
        {
            /* checksum checking */
            if (lin_checksum(response_buffer, pid) == response_buffer[(response_buffer[0]+1)])
            {
                /*******************************************/
                /***  RX Buffer Full - Checksum OK       ***/
                /*******************************************/
                /* set lin status: successful_transfer */
                l_status.byte |= LIN_STA_SUCC_TRANSFER;

                /* trigger callback */
                CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_RX_COMPLETED, current_id);
            }
            else
            {
                /*******************************************/
                /***  RX Buffer Full - Checksum ERROR    ***/
                /*******************************************/
                /* set lin status: error_in_response, checksum_error */
                l_status.byte |= (LIN_STA_ERROR_RESP|LIN_STA_CHECKSUM_ERR);
                /* trigger callback */
                CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_CHECKSUM_ERR, current_id);
            }
        }
        lin_goto_idle_state();
    }
    else if (UART_GetIntFlag(UART1, UART_INT_RX_TIMEOUT) != 0)
    {
        if (UART_GetRxFIFOLevel(UART1) > 0)
        {
            CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_NODATA_TIMEOUT, current_id);
        }
        
        lin_goto_idle_state();
        
        UART_ClearInt(UART1, UART_INT_RX_TIMEOUT);
    }
    else if (UART_GetIntFlag(UART1, UART_INT_RX_FRAME_ERROR) != 0)
    {
        if (READ_FIELD((UART1)->LINCTL, LINCTL_RESP_Msk, LINCTL_RESP_Pos) ==  LIN_RESPONSE_RX)
        {
            UART_DisableInt(UART1, UART_INT_RX_REQ);
            LIN_SetResponse(UART1, LIN_RESPONSE_NONE);
            
            CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_FRAME_ERR, current_id);
        }
        
        lin_goto_idle_state();
        
        UART_ClearInt(UART1, UART_INT_RX_FRAME_ERROR);
    }
    else if (UART_GetIntFlag(UART1, UART_INT_LIN_BIT_ERROR) != 0)
    {
        LIN_SetResponse(UART1, LIN_RESPONSE_NONE);
        CALLBACK_HANDLER((l_ifc_handle)ifc, LIN_LLD_READBACK_ERR, current_id);
        
        lin_goto_idle_state();
    }
    else if (UART_GetIntFlag(UART1, UART_INT_LIN_BUS_IDLE) != 0)
    {
        printf("BUS_IDLE\n");
        lin_lld_uart_set_low_power_mode();

        UART_ClearInt(UART1, UART_INT_LIN_BUS_IDLE);
    }
    /* GetAutobaudlockFlag */
    if (UART_GetIntFlag(UART1, UART_INT_AUTOBAUD_LOCK) != 0)
    {
        /* The BaudCount must be set once again */
        UART_SetBaudCount(UART1, UART_GetBaudCount(UART1));
        
        UART_ClearInt(UART1, UART_INT_AUTOBAUD_LOCK);
    }

    UART_ClearInt(UART1, UART_INT_GLOBAL);
} /* End function lin_lld_UART_rx_isr() */



/***** LOW-LEVEL API *****/

void lin_lld_uart_init
(
    /* [IN] LIN interface name */
    l_ifc_handle iii
)
{
    uint16_t             u16PREDRIID;                            /* PRE-DRIVER mode ID */
    ErrorStatus          eErrorState;                            /* Function State */
    /* Config */
    ifc = (l_u8)iii;
    response_buffer = lin_lld_response_buffer;
    
    /* HV reset */
    eErrorState = HV_Reset();
    if (eErrorState == ERROR)
    {
        printf("HV_Reset FAIL\n");
        return;
    }
    else
    {
        printf("HV_Reset SUCCESS\n");
    }

    /* HV init */
    eErrorState = HV_Init(&u16PREDRIID);
    if (eErrorState == ERROR)
    {
        printf("Init HV mode FAIL\n");
    }
    else
    {
        ;
    }

    /* HV parameter write enable */
    eErrorState = EPWR_WriteRegister(HV_REG_CTLKEY, KEY_USER_REG);
    if (eErrorState == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
    }
    
    eErrorState = EPWR_WriteRegisterField(HV_REG_PMUCTL, PMUCTL_LINWKUPEN_Msk | 
      PMUCTL_CYCWKUPEN_Msk, PMUCTL_LINWKUPEN_ENABLE | PMUCTL_CYCWKUPEN_DISABLE);
    if (eErrorState == ERROR)
    {
        printf("Write PMUCTL register FAIL\n");
    }

#if (defined(SPD1177) || defined(SPD1179B))
    /*
    Init LIN parameter
    */
    eErrorState = EPWR_WriteRegisterField(HV_REG_LINCTL, LINCTL_RLOAD_Msk | LINCTL_TXEN_Msk | LINCTL_EN_Msk, LINCTL_RLOAD_938_OHM | LINCTL_TXEN_ENABLE | LINCTL_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegisterField FAIL\n");
    }

    eErrorState = EPWR_WriteRegisterField(HV_REG_LINTXSCTL, LINTXSCTL_ISTEP_Msk , ((LIN_BAUD_RATE << 1) / 1000) << LINTXSCTL_ISTEP_Pos);
    if (eErrorState == ERROR)
    {
        printf("EPWR_WriteRegisterField FAIL\n");
    }
#elif defined(SPD1179)
    /*
    Init LIN parameter
    when Baud rate 9600, LINCTL_TXSLOPE_19P0US
    when Baud rate 19200, LINCTL_TXSLOPE_7PUS
    */
    eErrorState = EPWR_WriteRegisterField(HV_REG_LINCTL, LINCTL_TXSLOPE_Msk | LINCTL_STRENGTH_Msk | LINCTL_TXEN_Msk | LINCTL_EN_Msk, LINCTL_TXSLOPE_7PUS | LINCTL_STRENGTH_47P2MA | LINCTL_TXEN_ENABLE | LINCTL_EN_ENABLE);
    if (eErrorState == ERROR)
    {
        printf("LINCTL_WriteRegisterField FAIL\n");
    }
#endif

    LIN_Init(UART1, LIN_SLAVE, LIN_BAUD_RATE);
    UART_EnableTx(UART1);
    UART_EnableRx(UART1);
    
    LIN_SetIDFilter(UART1, 0x00, 0x00);
    
    UART_SetBusIdleThreshold(UART1, (4*SysInfo.u32SYSCLK));
    UART_RunBusIdleCounter(UART1);

    /* Enable UART1_IRQn trigger INT in MCU side */
    NVIC_EnableIRQ(UART1_IRQn);

    UART_EnableInt(UART1, UART_INT_LIN_ID_MATCH | UART_INT_AUTOBAUD_LOCK);

    /* Set the default u32Th, enable the interrupt when FIFO level > u32Th */
    UART_SetRxFIFOThreshold(UART1, 8);
    UART_EnableInt(UART1, UART_INT_RX_TIMEOUT);
    UART_EnableInt(UART1, UART_INT_RX_FRAME_ERROR);
    UART_EnableInt(UART1, UART_INT_LIN_BIT_ERROR);
    
    #ifdef BUS_IDLE_AUTO_SLEEP
        UART_EnableInt(UART1, UART_INT_LIN_BUS_IDLE);
    #else
    
    #endif

    lin_goto_idle_state();

    PIN_SetChannel(PIN_GPIO25, PIN_GPIO25_UART1_TXD);
    PIN_SetChannel(PIN_GPIO26, PIN_GPIO26_UART1_RXD);
} /* End of function lin_lld_uart_init( l_ifc_handle iii ) */
/*--------------------------------------------------------------------*/

void timer_init()
{
    /* Enable and Get Timer module clock */
    CLOCK_EnableModule(TIMER2_MODULE);

    /* Set Timer mode */
    TIMER_SetMode(TIMER2, TIMER_GENERAL_TIMER);

    /* Set reload Timer while Timer reaches 0 */
    TIMER_SetReloadValue(TIMER2, CLOCK_MsToCounter((10), CLOCK_GetModuleClock(TIMER2_MODULE)));

    /* Open Global INT for Timer */
    NVIC_EnableIRQ(TIMER2_IRQn);

    /* Enable Timer interrupt */
    TIMER_EnableInt(TIMER2);

    TIMER_Enable(TIMER2);
    
    
    
    /* Enable and Get Timer module clock */
    CLOCK_EnableModule(TIMER1_MODULE);

    /* Set Timer mode */
    TIMER_SetMode(TIMER1, TIMER_GENERAL_TIMER);

    /* Set reload Timer while Timer reaches 0 */
    TIMER_SetReloadValue(TIMER1, CLOCK_UsToCounter(((80 + 20) * 1000000 / LIN_BAUD_RATE ), CLOCK_GetModuleClock(TIMER1_MODULE)));

    /* Open Global INT for Timer */
    NVIC_EnableIRQ(TIMER1_IRQn);

    /* Enable Timer interrupt */
    TIMER_EnableInt(TIMER1);
} /* End of function lin_lld_uart_init( l_ifc_handle iii ) */






void lin_lld_uart_deinit
(
)
{
    lin_lld_uart_int_disable();
}


void lin_lld_uart_tx_wake_up
(
)
{

} /* End function lin_lld_UART_tx_wake_up() */
/*--------------------------------------------------------------------*/

void lin_lld_uart_int_enable
(
)
{
    /* Can't enable in interrupt context */

    NVIC_EnableIRQ(UART1_IRQn);
} /* End function lin_lld_UART_int_enable() */
/*--------------------------------------------------------------------*/

void lin_lld_uart_int_disable
(
)
{
    /*--------------------------------------------------------------------*/
    /* Can't disable in interrupt context */
    /* Disable UART Channel */
    NVIC_DisableIRQ(UART1_IRQn);
} /* End function lin_lld_UART_int_disable() */


void lin_lld_uart_ignore_response
(
)
{
    LIN_SetResponse(UART1, LIN_RESPONSE_NONE);

    lin_goto_idle_state();
}


void lin_lld_uart_set_low_power_mode
(
)
{
    ErrorStatus (*funcPtr)(void);
    funcPtr = (ErrorStatus (*)(void))(0x2bf5UL);
    
    /* Enable sleep/stop command */
    if (EPWR_WriteRegister(HV_REG_CTLKEY, KEY_PMU_CMD) == ERROR)
    {
        printf("Write CTLKEY register FAIL\n");
    }

    /* System sleep */
    /* Disable interrupt */
    __disable_irq(); 
    
    /* Disable all NMI interrupt */
    SYSTEM_DisableNonMaskableInt(NMI_EVENT_ALL);
    
    /* 
     * Sleep
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
void lin_lld_uart_rx_response
(
    /* [IN] Length of response data expect to wait */
    l_u8  msg_length
)
{
    LIN_SetResponse(UART1, LIN_RESPONSE_RX);

    /* Set the respond lenth */
    LIN_SetResponseLen(UART1, msg_length);

    if ((0x3C != pid) && (0x7D != pid))
    {
        LIN_SetCheckSumMode(UART1, LIN_ENHANCED_CHECKSUM);
    }
    else
    {
        LIN_SetCheckSumMode(UART1, LIN_CLASSIC_CHECKSUM) ;
    }

    /* Put response length and pointer of response buffer into descriptor */
    *(response_buffer) = msg_length;
    cnt_byte = 0;
    ptr = response_buffer;

    UART_SetRxFIFOThreshold(UART1, msg_length);
    
    UART_EnableInt(UART1, UART_INT_RX_REQ);
}

void lin_lld_uart_tx_response
(
)
{
    LIN_SetResponse(UART1, LIN_RESPONSE_TX);

    LIN_SetResponseLen(UART1, response_buffer[0]);

    /* 1. PID correspond to Master request and Slave response, their checksum cal is classic
    the non-diagnostic frame is calculated in Enhanced */
    if ((0x3C != pid) && (0x7D != pid))
    {
        LIN_SetCheckSumMode(UART1, LIN_ENHANCED_CHECKSUM);
    }
    else
    {
        LIN_SetCheckSumMode(UART1, LIN_CLASSIC_CHECKSUM) ;
    }
    
    TIMER_SetReloadValue(TIMER1, 
    CLOCK_UsToCounter(((10 * response_buffer[0] + 20) * 1000000 / (CLOCK_GetModuleClock(UART1_MODULE) / UART_GetBaudCount(UART1))), CLOCK_GetModuleClock(TIMER1_MODULE)));
    TIMER_Enable(TIMER1);

    /* Set LIN Status */
    for (cnt_byte = 1; cnt_byte < (response_buffer[0] + 1); cnt_byte++)
    {
        UART_WriteByte(UART1, response_buffer[cnt_byte]);
    }

    UART1->LINCTL |= LINCTL_TXCHKSUM_TRANSMIT;    
/*--------------------------------------------------------------------*/
} /* End function lin_lld_UART_tx_response() */

l_u8 lin_lld_uart_get_status
(
)
{
    return l_status.byte;
}


l_u8 lin_lld_uart_get_state()
{
    return 0;
}










/*** INTERNAL FUNTIONS ***/
void lin_goto_idle_state
(
)
{
    LIN_SetResponse(UART1, LIN_RESPONSE_NONE);
    UART_ClearRxFIFO(UART1);
    UART_ClearTxFIFO(UART1);
    
    lin_revert_default_baud();
    
    /* set lin status: ~bus_activity */
    l_status.byte &= ~LIN_STA_BUS_ACTIVITY;

    UART_ClearInt(UART1, UART_INT_LIN_ID_MATCH);
} /* End function lin_goto_idle_state() */
