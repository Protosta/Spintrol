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

#define             DEBUG_INFO              1               /* the controlling flag of printf info*/
#define             MASTER_TRANSMIT         1               /* 1: master transmit 0: master receive */
#define             T_BUFFER_SIZE           128
#define             I2C_SPEED               400000
#define             I2C_Slave_ADDR          0x9             /* IIC Slave ADDR */

uint32_t            gu32BuffSize            = T_BUFFER_SIZE;
uint8_t             gau8TxBuf[T_BUFFER_SIZE];
uint8_t             gau8RxBuf[T_BUFFER_SIZE];
uint32_t            gu32_cnt_i2c_stop_isr;
ErrorStatus         estatus;

static void Check_Receive_Data(void)
{
    int i;
    uint8_t u8Data = 0;

    /*To check the datum sent and recieved are the same*/
    for(i = 0; i < gu32BuffSize; i++)
    {
        if (gau8RxBuf[i] != u8Data)
        {
            printf("[Error]@%4d: TX(0x%02X) != RX(0x%02X)\n", __LINE__, u8Data, gau8RxBuf[i] );
        }
        else
        {
            #if DEBUG_INFO
            printf("%3d: TX(0x%02X) == RX(0x%02X)\n", i, u8Data, gau8RxBuf[i] );
            #endif
        }

        u8Data++;
    }
}

void Master_TxRX_data(I2C_REGS* I2Cx)
{
    int i;
    uint8_t u8Data = 0;
    uint32_t u32IsrCnt = 0;                                   /*Interrupt Check variable*/

    if (MASTER_TRANSMIT)
    {
        /* Generate random datum to transmit */
        for(i=0; i < gu32BuffSize; i++)
        {
            gau8TxBuf[i] = u8Data++;
            printf("gau8TxBuf[%d] = 0x%x\n", i, gau8TxBuf[i]);
        }

        printf("Master Tx data...\n");
        I2C_MasterWrite(I2Cx, I2C_ADDR_7BIT, I2C_Slave_ADDR, gau8TxBuf, gu32BuffSize);
    }
    else
    {
        printf("Master Rx data...\n");

        /*Read the data had sent to the slave back and put them in 'gau8RxBuf'*/
        I2C_MasterRead(I2Cx, I2C_ADDR_7BIT, I2C_Slave_ADDR, gau8RxBuf, gu32BuffSize);

        /*To check the datum sent and recieved are the same*/
        Check_Receive_Data();
    }

    u32IsrCnt = 1;

    /* Wait for I2C INT done */
    Delay_Us(300);

    /*
    * Check interrupt counter, if the INT count is not equal the bytes we has sent, there
    * must be something wrong had happened.
    */
    if( gu32_cnt_i2c_stop_isr != u32IsrCnt)
    {
        printf("[Error]@%4d: I2C ISR counter not right. expect %d, but is %d", __LINE__,
                                  u32IsrCnt, gu32_cnt_i2c_stop_isr);
    }
    else
    {
        printf("Success\n");
    }
}


/*************************************************************************************************************************
 *
 * @brief      This demo code is couple with the slave demo code named "I2C_Slave_Polling_TxRx".
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

    #if (defined(SPD1179) || defined(SPD1177))
    /* Initial the I2C PIN */
    PIN_SetChannel(PIN_GPIO14, PIN_GPIO14_I2C_SCL);
    PIN_SetChannel(PIN_GPIO15, PIN_GPIO15_I2C_SDA);

    /*
    * Set Output Strength as 20mA, in case of many more
    * slaves are linking to the master.
    */
    PIN_SetOutStrength(PIN_GPIO14, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO15, PIN_OUT_STRENGTH_20MA);
    #else
    /* Initial the I2C PIN */
    PIN_SetChannel(PIN_GPIO32, PIN_GPIO32_I2C_SCL);
    PIN_SetChannel(PIN_GPIO33, PIN_GPIO33_I2C_SDA);

    /*
    * Set Output Strength as 20mA, in case of many more
    * slaves are linking to the master.
    */
    PIN_SetOutStrength(PIN_GPIO32, PIN_OUT_STRENGTH_20MA);
    PIN_SetOutStrength(PIN_GPIO33, PIN_OUT_STRENGTH_20MA);
    #endif

    /* Disable All INT */
    I2C_DisableInt(I2C,I2C_INT_ALL);

    /* Clear All INT */
    I2C_ClearInt(I2C, I2C_INT_ALL);

    /* Initial I2C as Master */
    I2C_MasterInit(I2C);
    
    I2C_InitFastSpeed(I2C, I2C_SPEED, I2C_MASTER);
    
    /* Enable MCU INT Request */
    NVIC_EnableIRQ(I2C_IRQn);

    /* Enable the INT of detecting the STOP of I2C */
    I2C_EnableInt(I2C,I2C_INT_STOP_DETECT);

    /* Enable I2C */
    I2C_Enable(I2C);

    /* Master start to transmit and receive data */
    Master_TxRX_data(I2C);

    while(1)
    {

    }
}


void I2C_IRQHandler(void)
{
    if(I2C_GetIntFlag(I2C,I2C_INT_STOP_DETECT))
    {
        gu32_cnt_i2c_stop_isr ++ ;

        I2C_ClearInt(I2C, I2C_INT_STOP_DETECT|I2C_INT_GLOBAL);
    }
    else
    {
        printf("[%s Error] Stop detect interrupt error\n", __func__);
    }
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
