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
#define             SLAVE_TRANSMIT          0               /* 1: slave transmit 0: slave receive */
#define             RX_INT_TH               0xf             /* Rx thresgold as 16 entry */
#define             TX_INT_TH               0x0             /* Tx thresgold as 1 entry */
#define             TxRx_DATA_LEN           16              /* Send receive 16 Byte */
#define             T_BUFFER_SIZE           128
#define             I2C_SPEED               400000
#define             I2C_Slave_ADDR          0x9             /* IIC Slave ADDR */


uint32_t            gu32BuffSize            = T_BUFFER_SIZE;
uint8_t             gau8TxBuf[T_BUFFER_SIZE];
uint8_t             gau8RxBuf[T_BUFFER_SIZE];
uint32_t            num                     = 0;
uint32_t            u32IsrCnt               = 0;

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


void Slave_TxRX_data(I2C_REGS* I2Cx)
{
    int i;
    uint8_t u8Data = 0;

    if (SLAVE_TRANSMIT)
    {
        /* Generate random datum to transmit */
        for(i = 0; i < gu32BuffSize; i++)
        {
            gau8TxBuf[i] = u8Data++;
            printf("gau8TxBuf[%d] = 0x%x\n", i, gau8TxBuf[i]);
        }

        printf("Slave Tx data...\n");

        I2C_SetTxFIFOThreshold(I2C, TX_INT_TH);

        I2C_EnableInt(I2C, I2C_INT_TX_REQ);
    }
    else
    {
        printf("Slave Rx data...\n");

        I2C_SetRxFIFOThreshold(I2C, RX_INT_TH);

        I2C_EnableInt(I2C, I2C_INT_RX_REQ);
    }
}


/*************************************************************************************************************************
 *
 * @brief      In this case, the IIC controller is used as master and sent datum to the slave and read these datum back to
 *             compare, if there is a item not equal with each other, the test FAIL.
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

    #if (defined(SPD1179) || defined(SPD1177) || defined(SPD1179B))
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

    /* Initial I2C as Slave and set the speed as 400K */
    I2C_SlaveInit(I2C, I2C_ADDR_7BIT, I2C_Slave_ADDR);
    
    I2C_InitFastSpeed(I2C, I2C_SPEED, I2C_SLAVE);

    /* Enable MCU INT Request */
    NVIC_EnableIRQ(I2C_IRQn);

    /* Enable I2C */
    I2C_Enable(I2C);

    /* Slave start to transmit and receive data */
    Slave_TxRX_data(I2C);

    while(1)
    {
    }
}

void I2C_IRQHandler(void)
{
    int i;

    if (SLAVE_TRANSMIT && (u32IsrCnt < T_BUFFER_SIZE))
    {
        if (I2C_GetStatus(I2C, I2C_STS_TX_EMPTY))
        {
            for (i = 0; i < TxRx_DATA_LEN; i++)
            {
                /* Wait Until Detect Read Request */
                while(!I2C_GetIntRawFlag(I2C, I2C_INT_READ_REQ)) { }

                /* Clear Event Flag */
                I2C_ClearInt(I2C, I2C_INT_READ_REQ);

                /* Write TxFIFO, Send Data */
                I2C_WriteByte(I2C, gau8TxBuf[u32IsrCnt++]);
            }
        }

    }
    else if (!SLAVE_TRANSMIT && (u32IsrCnt < T_BUFFER_SIZE))
    {
        while (I2C_GetStatus(I2C, I2C_STS_RX_NOT_EMPTY))
        {
            gau8RxBuf[u32IsrCnt++] = I2C_ReadByte(I2C);
        }
    }


    if (u32IsrCnt == T_BUFFER_SIZE)
    {
        if (SLAVE_TRANSMIT)
        {
            I2C_DisableInt(I2C,I2C_INT_TX_REQ);
        }
        else
        {
            I2C_DisableInt(I2C,I2C_INT_RX_REQ);
            Check_Receive_Data();
        }

        printf("Success\n");
    }
    
    I2C_ClearInt(I2C, I2C_INT_ALL);
}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
