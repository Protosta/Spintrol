/******************************************************************************
 * @file     i2c.c
 * @brief    I2C firmware functions.
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

#include "i2c.h"


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/******************************************************************************
 * @brief       Initializes I2C standard speed mode
 *
 * @param[in]   I2Cx         : Select the I2C module as defined by I2C_REGS*
 *                             It can be any value below:
 *                               - \ref I2C
 *                           
 * @param[in]   u32Speed     : Speed in bps as defined by uint32_t
 *
 * @param[in]   eMode        : Select the I2C mode as defined by I2C_ModeEnum*
 *                             It can be any value below:
 *                               - \ref I2C_MASTER
 *                               - \ref I2C_SLAVE
 *
 * @return      SUCCESS - Init success
 *              ERROR   - I2C clock too low
 *
 * @note        When is master mode, only low/high/spike/hold count work
 * @note        When is slave mode, only spike/hold/setup count work
 *
 ******************************************************************************/
ErrorStatus I2C_InitStandardSpeed(I2C_REGS *I2Cx, uint32_t u32Speed, I2C_ModeEnum eMode)
{
    uint32_t u32PCnt;
    uint32_t u32HCnt;
    uint32_t u32LCnt;
    float fCntLMin ;
    float fCntHMin ;
    uint32_t u32SpikeLen;
    uint32_t u32ClkFreq;
    uint32_t u32HoldCnt;
    uint32_t u32SetupCnt ;

    u32ClkFreq = CLOCK_GetModuleClock(AHB_MODULE);
    u32PCnt    = u32ClkFreq / u32Speed;
    
    /* Spike suppression : 50ns */
    u32SpikeLen = u32ClkFreq / 20000000;
    if ( u32SpikeLen < 1 )
    {
        u32SpikeLen = 1 ;
    }

    u32LCnt = u32PCnt / 2;
    u32HCnt = u32PCnt - u32LCnt;
    
    /* The SCL Minimum low time : 4.7us*/
    /* The SCL Minimum High time: 5.2us*/
    fCntLMin  = 4.7 * u32ClkFreq / 1000000 + 1.0;
    fCntHMin  = 5.2 * u32ClkFreq / 1000000 + 1.0;
    
    /* If low value too little, use SCL Minimum low time */
    if (u32LCnt < ((uint32_t)fCntLMin))
    {
        u32LCnt = (uint32_t)fCntLMin ;
    }

    /* If high value too little, use SCL Minimum high time */
    if (u32HCnt < ((uint32_t)fCntHMin))
    {
        u32HCnt = (uint32_t)fCntHMin ;
    }

    /* Check whether I2C clock is fast enough to support the speed */
    if((u32LCnt < 12) || (u32HCnt < (u32SpikeLen + 7 + 5)))
    {
        return ERROR;
    }
    
    /* Set SDA Hold time to 1/10 SCL period */
    u32HoldCnt = u32PCnt / 10;
    if (eMode == I2C_MASTER)
    {
        if (u32HoldCnt < 1)
        {
            u32HoldCnt = 1;
        }
        
    }
    else
    {
        if (u32HoldCnt < (u32SpikeLen + 7))
        {
            u32HoldCnt = (u32SpikeLen + 7);
        }
    } 
    I2C_SetSDAHoldCount(I2Cx, u32HoldCnt);
    
    /* Set SDA Setup time to 4/10 SCL period */
    u32SetupCnt = (u32PCnt << 2) / 10 + 1;
    if (u32SetupCnt > 255)
    {
        u32SetupCnt = 255;
    }
    else if (u32SetupCnt < 2 )
    {
        u32SetupCnt = 2 ;
    }
    I2C_SetSDASetupCount(I2Cx, u32SetupCnt);
    
    /* Set I2C operating speed mode */
    MODIFY_REG(I2Cx->I2CCTL, I2CCTL_SPEED_Msk, I2CCTL_SPEED_STANDARD);

    /* Spike suppression */
    I2Cx->I2CFSSPKLEN = u32SpikeLen;

    /* Standard mode SCL hold low time counter */
    I2Cx->I2CSSLCNT = u32LCnt - 1;

    /* Standard mode SCL hold high time counter */
    I2Cx->I2CSSHCNT = u32HCnt - 7 - u32SpikeLen;
    
    return SUCCESS;
}




/******************************************************************************
 * @brief       Initializes I2C fast speed mode
 *
 * @param[in]   I2Cx         : Select the I2C module as defined by I2C_REGS*
 *                             It can be any value below:
 *                               - \ref I2C
 *                           
 * @param[in]   u32Speed     : Speed in bps as defined by uint32_t
 *                           
 * @param[in]   eMode        : Select the I2C mode as defined by I2C_ModeEnum*
 *                             It can be any value below:
 *                               - \ref I2C_MASTER
 *                               - \ref I2C_SLAVE
 *
 * @return      SUCCESS - Init success
 *              ERROR   - I2C clock too low
 *
 * @note        When is master mode, only low/high/spike/hold count work
 * @note        When is slave mode, only spike/hold/setup count work
 *
 ******************************************************************************/
ErrorStatus I2C_InitFastSpeed(I2C_REGS *I2Cx, uint32_t u32Speed, I2C_ModeEnum eMode)
{
    uint32_t u32PCnt;
    uint32_t u32HCnt;
    uint32_t u32LCnt;
    float fCntLMin ;
    float fCntHMin ;
    uint32_t u32SpikeLen;
    uint32_t u32ClkFreq;
    uint32_t u32HoldCnt;
    uint32_t u32SetupCnt ;

    u32ClkFreq = CLOCK_GetModuleClock(AHB_MODULE);
    u32PCnt    = u32ClkFreq / u32Speed;
    
    /* Spike suppression : 50ns */
    u32SpikeLen = u32ClkFreq / 20000000;
    if ( u32SpikeLen < 1 )
    {
        u32SpikeLen = 1 ;
    }
    
    u32LCnt = u32PCnt / 2 ;
    u32HCnt = u32PCnt - u32LCnt ;

    if ( u32Speed > 400000 )
    {
        /* The SCL Minimum low time : 0.5us*/
        /* The SCL Minimum High time: 0.5us*/
        fCntLMin  = 0.5 * u32ClkFreq / 1000000 + 1.0;
        fCntHMin  = 0.5 * u32ClkFreq / 1000000 + 1.0;
    }
    else
    {
        /* The SCL Minimum low time : 1.33us*/
        /* The SCL Minimum High time: 1.16us*/
        fCntLMin  = 1.33 * u32ClkFreq / 1000000 + 1.0;
        fCntHMin  = 1.16 * u32ClkFreq / 1000000 + 1.0;
    }

    /* If low value too little, use SCL Minimum low time */
    if (u32LCnt < ((uint32_t)fCntLMin))
    {
        u32LCnt = (uint32_t)fCntLMin ;
    }

    /* If high value too little, use SCL Minimum high time */
    if (u32HCnt < ((uint32_t)fCntHMin))
    {
        u32HCnt = (uint32_t)fCntHMin ;
    }

    /* Check whether I2C clock is fast enough to support the speed */
    if((u32LCnt < 13) || (u32HCnt < (u32SpikeLen + 7 + 5)))
    {
        return ERROR;
    }
    
    /* Set SDA Hold time to 1/10 SCL period */
    u32HoldCnt = u32PCnt / 10;
    if (eMode == I2C_MASTER)
    {
        if (u32HoldCnt < 1)
        {
            u32HoldCnt = 1;
        }
        
    }
    else
    {
        if (u32HoldCnt < (u32SpikeLen + 7))
        {
            u32HoldCnt = (u32SpikeLen + 7);
        }
    } 
    I2C_SetSDAHoldCount(I2Cx, u32HoldCnt);
    
    /* Set SDA Setup time to 4/10 SCL period */
    u32SetupCnt = (u32PCnt << 2) / 10 + 1;
    if (u32SetupCnt > 255)
    {
        u32SetupCnt = 255;
    }
    else if (u32SetupCnt < 2 )
    {
        u32SetupCnt = 2 ;
    }
    I2C_SetSDASetupCount(I2Cx, u32SetupCnt);

    /* Set I2C operating speed mode */
    MODIFY_REG(I2Cx->I2CCTL, I2CCTL_SPEED_Msk, I2CCTL_SPEED_FAST);

    /* Spike suppresion */
    I2Cx->I2CFSSPKLEN = u32SpikeLen;

    /* Fast mode SCL hold low time counter */
    I2Cx->I2CFSLCNT = u32LCnt - 1;

    /* Fast mode SCL hold high time counter */
    I2Cx->I2CFSHCNT = u32HCnt - 7 - u32SpikeLen;
    
    return SUCCESS;
}




/******************************************************************************
 * @brief       Initializes I2C high speed mode
 *
 * @param[in]   I2Cx         : Select the I2C module as defined by I2C_REGS*
 *                             It can be any value below:
 *                               - \ref I2C
 *
 * @param[in]   u8MasterCode : Master code in High speed mode as defined by 
 *                             uint8_t
 *
 * @param[in]   u32Speed0    : Master code speed in bps as defined by uint32_t
 *                           
 * @param[in]   u32Speed1    : Data speed in bps as defined by uint32_t
 *
 * @param[in]   eMode        : Select the I2C mode as defined by I2C_ModeEnum*
 *                             It can be any value below:
 *                               - \ref I2C_MASTER
 *                               - \ref I2C_SLAVE
 *
 * @return      SUCCESS - Init success
 *              ERROR   - I2C clock too low
 *
 * @note        When is master mode, only low/high/spike/hold count work
 * @note        When is slave mode, only spike/hold/setup count work
 *
 ******************************************************************************/
ErrorStatus I2C_InitHighSpeed(I2C_REGS *I2Cx, uint8_t u8MasterCode, 
                     uint32_t u32Speed0, uint32_t u32Speed1, I2C_ModeEnum eMode)
{
    uint32_t u32PCnt;
    uint32_t u32HCnt;
    uint32_t u32LCnt;
    float fCntLMin ;
    float fCntHMin ;
    uint32_t u32SpikeLen;
    uint32_t u32ClkFreq;
    uint32_t u32HoldCnt;
    uint32_t u32SetupCnt ;

    u32ClkFreq = CLOCK_GetModuleClock(AHB_MODULE);
    
    u32PCnt    = u32ClkFreq / u32Speed0;
    
    /* Spike suppression : 50ns */
    u32SpikeLen = u32ClkFreq / 20000000;
    if ( u32SpikeLen < 1 )
    {
        u32SpikeLen = 1 ;
    }
    
    u32LCnt = u32PCnt / 2 ;
    u32HCnt = u32PCnt - u32LCnt ;

    if ( u32Speed0 > 400000 )
    {
        /* The SCL Minimum low time : 0.5us*/
        /* The SCL Minimum High time: 0.5us*/
        fCntLMin  = 0.5 * u32ClkFreq / 1000000 + 1.0;
        fCntHMin  = 0.5 * u32ClkFreq / 1000000 + 1.0;
    }
    else
    {
        /* The SCL Minimum low time : 1.33us*/
        /* The SCL Minimum High time: 1.16us*/
        fCntLMin  = 1.33 * u32ClkFreq / 1000000 + 1.0;
        fCntHMin  = 1.16 * u32ClkFreq / 1000000 + 1.0;
    }
    
    /* If low value too little, use SCL Minimum low time */
    if (u32LCnt < ((uint32_t)fCntLMin))
    {
        u32LCnt = (uint32_t)fCntLMin ;
    }

    /* If high value too little, use SCL Minimum high time */
    if (u32HCnt < ((uint32_t)fCntHMin))
    {
        u32HCnt = (uint32_t)fCntHMin ;
    }

    /* Check whether I2C clock is fast enough to support the speed */
    if((u32LCnt < 13) || (u32HCnt < (u32SpikeLen + 7 + 5)))
    {
        return ERROR;
    }

    /* Spike suppresion */
    I2Cx->I2CFSSPKLEN = u32SpikeLen;

    /* Fast mode SCL hold low time counter */
    I2Cx->I2CFSLCNT = u32LCnt - 1;

    /* Fast mode SCL hold high time counter */
    I2Cx->I2CFSHCNT = u32HCnt - 7 - u32SpikeLen;
     
    u32PCnt    = u32ClkFreq / u32Speed1;
    
    /* Spike suppression : 10ns */
    u32SpikeLen = u32ClkFreq / 100000000;
    if ( u32SpikeLen < 1 )
    {
        u32SpikeLen = 1 ;
    }

    u32HCnt = u32PCnt / 3 ;
    u32LCnt = u32PCnt - u32HCnt ;
    
    /* The SCL Minimum low time : 0.161us*/
    /* The SCL Minimum High time: 0.132us*/
    fCntLMin  = 0.161 * u32ClkFreq / 1000000 + 1.0;
    fCntHMin  = 0.132 * u32ClkFreq / 1000000 + 1.0;
   
    /* If low value too little, use SCL Minimum low time */
    if (u32LCnt < ((uint32_t)fCntLMin))
    {
        u32LCnt = (uint32_t)fCntLMin ;
    }

    /* If high value too little, use SCL Minimum high time */
    if (u32HCnt < ((uint32_t)fCntHMin))
    {
        u32HCnt = (uint32_t)fCntHMin ;
    }
    
    /* Check whether I2C clock is fast enough to support the speed */
    if((u32LCnt < 11) || (u32HCnt < (u32SpikeLen + 7 + 1)))
    {
        return ERROR;
    }

    /* Set SDA Hold time to 1/10 SCL period */
    u32HoldCnt = u32PCnt / 10;
    if (eMode == I2C_MASTER)
    {
        if (u32HoldCnt < 1)
        {
            u32HoldCnt = 1;
        }
        
    }
    else
    {
        if (u32HoldCnt < (u32SpikeLen + 7))
        {
            u32HoldCnt = (u32SpikeLen + 7);
        }
    }
    I2C_SetSDAHoldCount(I2Cx, u32HoldCnt);
    
    /* Set SDA Setup time to 6/10 SCL period */
    u32SetupCnt = (u32PCnt * 6) / 10 + 1;
    if (u32SetupCnt > 255)
    {
        u32SetupCnt = 255;
    }
    else if (u32SetupCnt < 2 )
    {
        u32SetupCnt = 2 ;
    }
    I2C_SetSDASetupCount(I2Cx, u32SetupCnt);
    
    /* Set I2C operating speed mode */
    MODIFY_REG(I2Cx->I2CCTL, I2CCTL_SPEED_Msk, I2CCTL_SPEED_HIGH);
    
    /* Spike suppresion */
    I2Cx->I2CHSSPKLEN = u32SpikeLen;

    /* High mode SCL hold low time counter */
    I2Cx->I2CHSLCNT = u32LCnt - 1;

    /* High mode SCL hold high time counter */
    I2Cx->I2CHSHCNT = u32HCnt - 7 - u32SpikeLen;
    
    I2C_SetHighSpeedCode(I2Cx, u8MasterCode);
    
    return SUCCESS;
}




/******************************************************************************
 * @brief      Initializes the I2C master
 *
 * @param[in]  I2Cx    :  Select the I2C module
 * @param[in]  u32Speed:  Operation speed (bps)
 *
 * @return     None
 *
 ******************************************************************************/
void I2C_MasterInit(I2C_REGS *I2Cx)
{
    /* Enable I2C Module Clock */
    CLOCK_EnableModule(I2C_MODULE);
    
    /* Disable I2C and interrupt */
    I2C_Disable(I2Cx) ;
    I2C_DisableInt(I2Cx, I2C_INT_ALL);

    /* Master mode */
    I2C_SetMode(I2Cx, I2C_MASTER);

    /* Restart enable */
    I2C_EnableRestart(I2Cx);
    
    /* Clear interrupt */
    I2C_ClearInt(I2Cx, I2C_INT_ALL);
}




/******************************************************************************
 * @brief      Initializes the I2C slave
 *
 * @param[in]  I2Cx      :  Select the I2C module
 *
 * @param[in]  eAddrMode :  Address mode
 *                          Please refer to I2C_AddrModeEnum
 *                           - \ref I2C_ADDR_7BIT
 *                           - \ref I2C_ADDR_10BIT
 *
 * @param[in]  u16SlvAddr:  Slave address
 *
 * @return     None
 *
 ******************************************************************************/
void I2C_SlaveInit(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode, uint16_t u16SlvAddr)
{
    CLOCK_EnableModule(I2C_MODULE);

    /* Disable I2C and interrupt */
    I2C_Disable(I2Cx) ;
    I2C_DisableInt(I2Cx, I2C_INT_ALL);

    /* Slave mode */
    I2C_SetMode(I2Cx, I2C_SLAVE);

    /* Restart enable */
    I2C_EnableRestart(I2Cx);

    /* Set address mode */
    I2C_SetAddressMode(I2Cx, eAddrMode);

    /* Slave address */
    I2C_SetSlaveAddress(I2Cx, u16SlvAddr);
    
    /* Clear interrupt */
    I2C_ClearInt(I2Cx, I2C_INT_ALL);
}




/******************************************************************************
 * @brief      Enable I2C
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     none
 *
 ******************************************************************************/
void I2C_Enable(I2C_REGS *I2Cx)
{
    volatile uint32_t u32Timeout = 0U;

    /* Enable I2C */
    SET_BITS(I2Cx->I2CCTL, I2CCTL_EN_Msk);

    /* Wait I2C enabled */
    for (u32Timeout = 0U; u32Timeout < 5000U; u32Timeout++)
    {
        if (I2C_GetStatus(I2Cx, I2C_STS_ENABLE) != 0U)
        {
            break;
        }
    }
}




/******************************************************************************
 * @brief      Disable I2C
 *
 * @param[in]  I2Cx:  Select the I2C module
 *
 * @return     none
 *
 ******************************************************************************/
void I2C_Disable(I2C_REGS *I2Cx)
{
    volatile uint32_t u32Timeout = 0U;
    
    /* Disable I2C */
    CLEAR_BITS(I2Cx->I2CCTL, I2CCTL_EN_Msk);

    /* Wait I2C disabled */
    for (u32Timeout = 0U; u32Timeout < 5000U; u32Timeout++)
    {
        if (I2C_GetStatus(I2Cx, I2C_STS_ENABLE) == 0U)
        {
            break;
        }
    }
}




/******************************************************************************
 * @brief      I2C Master Mode  Send Data function
 *
 * @param[in]  I2Cx          :  Select the I2C module
 * @param[in]  eAddrMode     :  Address mode
 *                              Please refer to I2C_AddrModeEnum
 *                               - \ref I2C_ADDR_7BIT
 *                               - \ref I2C_ADDR_10BIT
 * @param[in]  u16TargetAddr :  Target Slave address
 * @param[in]  pu8WriteBuf   :  Pointer to the buffer that stored the data to be sent
 * @param[in]  u32Count      :  Number of data to be sent or received
 *
 * @return     SUCCESS - Write success
 *             ERROR   - Timeout or Transmission abort
 *
 ******************************************************************************/
ErrorStatus I2C_MasterWrite(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode,
                         uint16_t u16TargetAddr, uint8_t *pu8WriteBuf, uint32_t u32Count)
{
    uint32_t i;
    volatile uint32_t u32Timeout ;
    
    /* Set Address Mode */
    I2C_SetAddressMode(I2Cx, eAddrMode);

    /* Set Target Slave Address*/
    I2C_SetTargetAddress(I2Cx, u16TargetAddr);

    /* TxFIFO Can Not Empty During  Transmit */
    for(i = 0; i < u32Count; i++)
    {
        /* Wait Until TxFIFO not Full */
        for ( u32Timeout = 0xffffffff ; 
        (u32Timeout > 0) && (!I2C_GetStatus(I2Cx, I2C_STS_TX_NOT_FULL)) ; 
        u32Timeout-- )
        {
            /* Must wait not busy when abort ouccr */
            if ( 0U != I2C_GetIntRawFlag(I2Cx, I2C_INT_TX_ABORT) )
            {
                for ( u32Timeout = 0xffffffff ; u32Timeout > 0UL ; u32Timeout-- )
                {
                    if ( 0U == I2C_GetStatus(I2Cx, I2C_STS_ACTIVITY) )
                    {
                        break ;
                    }
                }
                return ERROR ;
            }
        }

        if ( u32Timeout == 0 )
        {
            return ERROR ;
        }

        /* Write TxFIFO, Send Data If Master Get ACK */
        I2C_WriteByte(I2Cx, pu8WriteBuf[i]);
    }

    /* Wait Slave Receive Data And Send ACK Again,
    * Until Master Stop Bus Because of TxFIFO Empty
    */

    /* Wait Until TxFIFO Empty */
    for ( u32Timeout = 0xffffffff ; u32Timeout > 0UL ; u32Timeout-- )
    {
        if ( 0U != I2C_GetStatus(I2Cx, I2C_STS_TX_EMPTY) )
        {
            break ;
        }
    }

    if ( u32Timeout == 0 )
    {
        return ERROR ;
    }

    /* Wait I2C Bus Idle */  
    for ( u32Timeout = 0xffffffff ; u32Timeout > 0U ; u32Timeout-- )
    {
        if ( 0U == I2C_GetStatus(I2Cx, I2C_STS_ACTIVITY) )
        {
            break ;
        }
    }

    if ( u32Timeout == 0 )
    {
        return ERROR ;
    }

    /* Do Not Get ACK, Master Abort Send Data, Flush TxFIFO, Send Stop Signal */
    if ( 0U != I2C_GetIntRawFlag(I2Cx, I2C_INT_TX_ABORT) )
    {
        for ( u32Timeout = 0xffffffff ; u32Timeout > 0UL ; u32Timeout-- )
        {
            if ( 0U == I2C_GetStatus(I2Cx, I2C_STS_ACTIVITY) )
            {
                break ;
            }
        }
        return ERROR ;
    }
    return SUCCESS ;
}




/******************************************************************************
 * @brief      I2C Slave Mode  Receive Data function
 *
 * @param[in]  I2Cx      :  Select the I2C module
 * @param[in]  pu8ReadBuf:  Pointer to the buffer that stored the received data
 * @param[in]  u32Count  :  Number of data to be sent or received
 *
 * @return     SUCCESS - Read success
 *
 ******************************************************************************/
ErrorStatus I2C_SlaveRead(I2C_REGS *I2Cx, uint8_t *pu8ReadBuf, uint32_t u32Count)
{
    uint32_t i;

    for(i = 0; i < u32Count; i++)
    {
        /* Slave Receive Data, And Send ACK
         */

        /* Wait Until RxFIFO Not Empty */
        while(!I2C_GetStatus(I2Cx, I2C_STS_RX_NOT_EMPTY)) { }

        /* Read RxFIFO, Read Data */
        pu8ReadBuf[i] = I2C_ReadByte(I2Cx);
    }
    
    return SUCCESS;
}




/******************************************************************************
 * @brief      I2C Master Mode  Receive Data function
 *
 * @param[in]  I2Cx         :  Select the I2C module
 * @param[in]  eAddrMode    :  Address mode
 *                             Please refer to I2C_AddrModeEnum
 *                              - \ref I2C_ADDR_7BIT
 *                              - \ref I2C_ADDR_10BIT
 * @param[in]  u16TargetAddr:  Target Slave address
 * @param[in]  pu8ReadBuf   :  Pointer to the buffer that stored the received data
 * @param[in]  u32Count     :  Number of data to be sent or received
 *
 * @return     SUCCESS - Read success
 *             ERROR   - Timeout or Transmission abort
 *
 ******************************************************************************/
ErrorStatus I2C_MasterRead(I2C_REGS *I2Cx, I2C_AddrModeEnum eAddrMode,
                        uint16_t u16TargetAddr, uint8_t *pu8ReadBuf, uint32_t u32Count)
{
    uint32_t u32RxCnt = 0;
    uint32_t u32TxCnt = 0;
    volatile uint32_t u32Timeout ;

    /* Set Address Mode */
    I2C_SetAddressMode(I2Cx, eAddrMode);

    /* Set Target Slave Address*/
    I2C_SetTargetAddress(I2Cx, u16TargetAddr);

    /* Master Send Address, Wait Slave Send Data If Master Get ACK;
    * Then Master Receive Data and Send ACK;
    * Send NACK and Stop Bus When TxFIFO Empty;
    */

    /* TxFIFO Can Not Empty During  Transmit */
    while(u32TxCnt < u32Count)
    {
        /* TxFIFO not Full */
        if(I2C_GetStatus(I2Cx, I2C_STS_TX_NOT_FULL))
        {
            /* Write TxFIFO, Send Read Command */
            I2C_MasterReadCmd(I2Cx);
            u32TxCnt++;
        }

        /* RxFIFO Not Empty */
        if(I2C_GetStatus(I2Cx, I2C_STS_RX_NOT_EMPTY))
        {
            /* Read RxFIFO, Read Data */
            *pu8ReadBuf++ = I2C_ReadByte(I2Cx);
            u32RxCnt++;
        }

        /* Must wait not busy when abort ouccr */
        if ( 0U != I2C_GetIntRawFlag(I2Cx, I2C_INT_TX_ABORT) )
        {
            for ( u32Timeout = 0xffffffff ; u32Timeout > 0UL ; u32Timeout-- )
            {
                if ( 0U == I2C_GetStatus(I2Cx, I2C_STS_ACTIVITY) )
                {
                    break ;
                }
            }
            return ERROR ;
        }
    }

    u32Timeout = 0xffffffffU;
    
    /* Read the Rest of Data */
    while(u32RxCnt < u32Count)
    {
        /* RxFIFO Not Empty */
        if(I2C_GetStatus(I2Cx, I2C_STS_RX_NOT_EMPTY))
        {
            /* Read RxFIFO, Read Data */
            *pu8ReadBuf++ = I2C_ReadByte(I2Cx);
            u32RxCnt++;
            u32Timeout = 0xffffffffU;
        }
        
        u32Timeout--;
        if (u32Timeout == 0U)
        {
            return ERROR ;
        }
    }

    /* Wait Until TxFIFO Empty */
    for ( u32Timeout = 0xffffffff ; u32Timeout > 0UL ; u32Timeout-- )
    {
        if ( 0U != I2C_GetStatus(I2Cx, I2C_STS_TX_EMPTY) )
        {
            break ;
        }
    }

    if ( u32Timeout == 0 )
    {
        return ERROR ;
    }
    
    /* Wait I2C Bus Idle */
    for ( u32Timeout = 0xffffffff ; u32Timeout > 0U ; u32Timeout-- )
    {
        if ( 0U == I2C_GetStatus(I2Cx, I2C_STS_ACTIVITY) )
        {
            break ;
        }
    }

    if ( u32Timeout == 0 )
    {
        return ERROR ;
    }
    
    return SUCCESS ;
}




/******************************************************************************
 * @brief      I2C Slave Mode  Send Data function
 *
 * @param[in]  I2Cx       :  Select the I2C module
 * @param[in]  pu8WriteBuf:  Pointer to the buffer that stored the data to be sent
 * @param[in]  u32Count   :  Number of data to be sent or received
 *
 * @return     SUCCESS - Write success
 *             ERROR   - Timeout or Transmission abort
 *
 ******************************************************************************/
ErrorStatus I2C_SlaveWrite(I2C_REGS *I2Cx, uint8_t *pu8WriteBuf, uint32_t u32Count)
{
    uint32_t i = 0;
    volatile uint32_t u32Timeout;

    /* Slave Send ACK If Master Request Address Matched
    */

    /* Wait Until Detect Read Request */
    while(!I2C_GetIntRawFlag(I2Cx, I2C_INT_READ_REQ)) { }

    /* Clear Event Flag */
    I2C_ClearInt(I2Cx, I2C_INT_READ_REQ);

    while(i < u32Count)
    {
        /* Must wait not busy when abort ouccr */
        if ( 0U != I2C_GetIntRawFlag(I2Cx, I2C_INT_TX_ABORT) )
        {
            for ( u32Timeout = 0xffffffff ; u32Timeout > 0UL ; u32Timeout-- )
            {
                if ( 0U == I2C_GetStatus(I2Cx, I2C_STS_ACTIVITY) )
                {
                    break ;
                }
            }
            return ERROR ;
        }
        /* TxFIFO not Full */
        if(I2C_GetStatus(I2Cx, I2C_STS_TX_NOT_FULL))
        {
            /* Write TxFIFO, Send Data */
            I2C_WriteByte(I2Cx, pu8WriteBuf[i]);
            i++;
        }
    }
    
    u32Timeout = 0xffffffff;
    
    /* Wait Until Master Receiver Done, Slave Get NACK */
    while ( 0U == I2C_GetIntRawFlag(I2Cx, I2C_INT_RX_DONE) )
    { 
        if (u32Timeout-- == 0)
        {
            return ERROR;
        }
    }

    /* Clear Event Flag */
    I2C_ClearInt(I2Cx, I2C_INT_RX_DONE);

    /* Clear Event Flag */
    I2C_ClearInt(I2Cx, I2C_INT_READ_REQ);
    
    return SUCCESS ;
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

