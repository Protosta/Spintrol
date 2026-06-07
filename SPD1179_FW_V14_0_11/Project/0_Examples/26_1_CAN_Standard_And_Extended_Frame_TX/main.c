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
#include <stdlib.h>

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif

#define DEBUG_INFO      1
#define CAN_DATA_LEN    8

uint8_t au8TxBuffer[64];

/* CAN Standard Remote frame message1 */
CAN_MessageTypeDef message1;
/* CAN Standard Data frame message2 */
CAN_MessageTypeDef message2;
/* CAN Extended Remote frame message3 */
CAN_MessageTypeDef message3;
/* CAN Extended Data frame message4 */
CAN_MessageTypeDef message4;

static void CAN_Clk_Enable(void)
{
    /* CAN Clk Enable */
    CLOCK_SetModuleDiv(CAN_MODULE, 1);
    CLOCK_EnableModule(CAN_MODULE);
}


static void CAN_Module_Disable(void)
{
    /* Disable run */
    CAN_Disable(CAN) ;

    /* FIXME add timeout control */
    while (CAN_GetOperationMode(CAN) != CAN_OPERATE_STOP) {}
}

static void CAN_Gpio_Init(void)
{
    #if (defined(SPD1179) || defined(SPD1177))
    PIN_SetChannel(PIN_GPIO8, PIN_GPIO8_CAN_TXD);
    PIN_SetChannel(PIN_GPIO9, PIN_GPIO9_CAN_RXD);
    #else
    PIN_SetChannel(PIN_GPIO38, PIN_GPIO38_CAN_TXD);
    PIN_SetChannel(PIN_GPIO39, PIN_GPIO39_CAN_RXD);
    #endif
}

static void CAN_Config(void)
{
    uint32_t u32Data ;
    uint32_t u32DateSegment1;

    double f64NBps ;
    double f64DBps ;

    uint32_t u32Prescaler;

    /* Set IO swap */
    CAN_DisablePinSwap(CAN) ;

    /* Set FDCAN fromat support */
    CAN_DisableFDFormat(CAN);

    /* Set ISO-CAN frame support */
    CAN_DisableNonIsoMode(CAN);

    /* Set protocol exception mode */
    CAN_EnableProtocolException(CAN);

    /* Set restricted mode */
    CAN_DisableRestrictedMode(CAN);

    /* Set monitor mode */
    CAN_DisableMonitorMode(CAN);

    /* Set transmission pause function */
    CAN_EnableTransmissionPause(CAN);

    /* Set RXD edge filter during integration status */
    CAN_EnableEdgeFilter(CAN);

    /* Enable re-tran message afte lost arbitration or error */
    CAN_EnableAutoRetransmission(CAN);

    /* Enable auto start bus-off recovery sequence after bus-off */
    CAN_EnableAutoBusOn(CAN);

    /* Set nominal bit baud rate
     * 1MHz for 100MHz clock
     **/
    CAN_SetNominalBitRatePrescaler(CAN, 1);
    CAN_SetNominalBitPhaseBufferSegment1(CAN, 79);
    CAN_SetNominalBitPhaseBufferSegment2(CAN, 20); /* sample point: 83% */
    CAN_SetNominalBitResyncJumpWidth(CAN, 8);

    /* Set data bit baud rate */
    if ( CAN_IsEnableFDFormat(CAN))
    {
        u32Prescaler = CAN_GetNominalBitRatePrescaler(CAN);
        /* 5Mbps for 100MHz clock */
        CAN_SetDataBitRatePrescaler(CAN, u32Prescaler);
        CAN_SetDataBitPhaseBufferSegment1(CAN, 17 );
        CAN_SetDataBitPhaseBufferSegment2(CAN, 2 ); /* sample point: 80% */
        CAN_SetDataBitResyncJumpWidth    (CAN, 2 );
    }

    /* Calculate nominal phase baud rate */
    u32Data = CAN_GetNominalBitPhaseBufferSegment1(CAN) + 1;
    u32Data += CAN_GetNominalBitPhaseBufferSegment2(CAN);
    u32Data *= CAN_GetNominalBitRatePrescaler(CAN);
    f64NBps = CLOCK_GetModuleClock(CAN_MODULE) / u32Data;
    
    printf("[CAN]NBps: %f\n", f64NBps ) ;
    
    /* Calculate data phase baud rate */
    if ( CAN_IsEnableFDFormat(CAN))
    {
        u32Data = CAN_GetDataBitPhaseBufferSegment1(CAN) + 1;
        u32Data += CAN_GetDataBitPhaseBufferSegment2(CAN);
        u32Data *= CAN_GetDataBitRatePrescaler(CAN);
        f64DBps = CLOCK_GetModuleClock(CAN_MODULE) / u32Data;
        printf("[CAN]DBps: %f\n", f64DBps ) ;
    }

    /* Set delay befor bus-off recovery, based on nominal bit time */
    /* Set delay 1ms */
    u32Data = (uint32_t)(1.0e6 / ( 1.0e9 / f64NBps));
    if (u32Data > 65535)
    {
        u32Data = 65535;
    }
 
    CAN_SetBusOffRecoveryDelay(CAN, u32Data) ;

    /* Set transmitter delay compensation for FD frame */
    CAN_EnableTransmitterDelayCompensation(CAN);

    /* Set transmitter delay compensation offset and window for FD frame */
    u32DateSegment1 = CAN_GetDataBitPhaseBufferSegment1(CAN);
    CAN_SetTransmitterDelayOffset(CAN, u32DateSegment1 + 1 );
    CAN_SetTransmitterDelayWindow(CAN, u32DateSegment1 + 1 );

    /* Set message RAM parity check */
    CAN_EnableParityCheck(CAN);

    /* Set timestamp */
    CAN_EnableTimestamp(CAN);
}

static void CAN_Printf_Message(CAN_MessageTypeDef *msg)
{
    int i;

    if (msg->eType == CAN_FRAME_DATA)
    {
        printf("    ") ;
        for (i = 0 ; i < msg->u8DataLen; i++)
        {
            printf("0x%02X,", msg->pu8Data[i]);
            if (i % 8 == 7)
            {
                printf("\n    ");
            }
        }
    }

    printf("\n");
}




/***************************************************************************
 *
 * @brief      In this case, the CAN Transmit Standard and Extended frame data.
 *
 *             This demo code is couple with the demo code named 
 *             "CAN_Standard_Frame_RX" "CAN_Extended_Frame_RX".
 *  _____         _____                                 _____           ______
 * |     |       |     |                               |     |         |      |
 * | MCU |--GND--|     |---------GND------x------------|     |---GND---|      |
 * | (TX)|-RX-RX-| CAN |----x---CANH----x-|--------x---| CAN |--RX--RX-| MCU  |
 * |     |-TX-TX-| PHY |----|-CANL-x--x-|-|-x------|---| PHY |--TX--RX-| (RX1)|
 * |     |--5V---|     |    |  __  |  | | | |  __  |   |     |---5V--- |      |
 * |_____|       |_____|    |_|__|_|  | | | |_|__|_|   |_____|         |______|
 *                              120   | | |    120
 *                                    | | |             _____           ______
 *                                    | | |            |     |         |      |
 *                                    | | x------------|     |---GND---|      |
 *                                    | x--------------| CAN |--RX--RX-| MCU  |
 *                                    x----------------| PHY |--TX--RX-| (RX2)|
 *                                                     |     |---5V--- |      |
 *                                                     |_____|         |______|
 *
 *            PHY's RX pin is connected to the RX pin
 *            (See Soc Datasheet for details).
 *            PHY's TX pin is connected to the TX pin
 *            (See Soc Datasheet for details).
 *
 * @KeyPoint   :   Add 120 ohm termination resistor
 *
 * @TestMethod :   Multiple boards to communicate
 * 
 * @TestResult :   Serial display "Transmit CAN Standard Remote frame success" 
 *                 "Transmit CAN Standard Data frame success"
 *                 "Transmit CAN Extended Remote frame success"
 *                 "Transmit CAN Extended Data frame success"
 *                 means data is correct
 *
 ***************************************************************************/
int main(void)
{
    int i;
    ErrorStatus status;

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

    printf("CAN: Transmit Message\n");

    /* CAN Clk Enable */
    CAN_Clk_Enable();

    /* CAN Disable */
    CAN_Module_Disable();
    
    /* CAN Gpio Init */
    CAN_Gpio_Init();

    /* CAN config */
    CAN_Config();

    /* Init message RAM contents before enable CAN module */
    CAN_InitMessageRAM(CAN);

    /* CAN run */
    CAN_Enable(CAN);

    /* Init mailbox for transmit CAN Standard Remote frame message1 */
    message1.eDataDir    = CAN_MSG_DATA_TX;
    message1.eRmtRspEn   = DISABLE;
    message1.eIntEn      = ENABLE;
    message1.eEobEn      = DISABLE;
    message1.eBrs        = DISABLE;
    message1.eEsiCtlEn   = ENABLE;
    message1.eEsi        = DISABLE;

    message1.u32Id       = 0x11;
    message1.u8MBoxId    = 0;
    message1.eFormat     = CAN_FORMAT_STD;
    message1.eType       = CAN_FRAME_REMOTE;

    /* Remote frame no DATA FIELD */
    message1.u8DataLen = 0;
    message1.pu8Data     = NULL;

    status = CAN_SetMessage(CAN, &message1);
    if (status == ERROR)
    {
        printf("[CAN][u8MBoxId:%2d] Set MBOX failed", message1.u8MBoxId);
        return -1;
    }

    CAN_EnableMailbox(CAN, message1.u8MBoxId);

    /* Wait CAN Standard Remote frame message1 txed */
    while (CAN_GetMailboxControlInfo(CAN, message1.u8MBoxId, CAN_MBOX_SET_MSG_NEW | CAN_MBOX_REQUEST_TX)) {}

    printf("\nTransmit CAN Standard Remote frame success\n");

    /* Init mailbox for transmit CAN Standard Data frame message2 */
    message2.eDataDir    = CAN_MSG_DATA_TX;
    message2.eRmtRspEn   = DISABLE;
    message2.eIntEn      = ENABLE;
    message2.eEobEn      = DISABLE;
    message2.eBrs        = DISABLE;
    message2.eEsiCtlEn   = ENABLE;
    message2.eEsi        = DISABLE;

    message2.u32Id       = 0x22;
    message2.u8MBoxId    = 1;
    message2.eFormat     = CAN_FORMAT_STD;
    message2.eType       = CAN_FRAME_DATA;

    /* DATA FIELD */
    message2.u8DataLen   = CAN_DATA_LEN;
    message2.pu8Data     = au8TxBuffer;

    for (i = 0; i < message2.u8DataLen; i++)
    {
        message2.pu8Data[i] = i;
    }

    #if DEBUG_INFO
    printf("CAN Standard Frame Data:\n") ;
    CAN_Printf_Message(&message2);
    #endif

    status = CAN_SetMessage(CAN, &message2);
    if (status == ERROR)
    {
        printf("[CAN][u8MBoxId:%2d] Set MBOX failed", message2.u8MBoxId);
        return -1;
    }

    CAN_EnableMailbox(CAN, message2.u8MBoxId);

    /* Wait CAN Standard Data frame message2 txed */
    while (CAN_GetMailboxControlInfo(CAN, message2.u8MBoxId, CAN_MBOX_SET_MSG_NEW | CAN_MBOX_REQUEST_TX)) {}

    printf("\nTransmit CAN Standard Data frame success\n");


    /* Init mailbox for transmit CAN Extended Remote frame message3 */
    message3.eDataDir    = CAN_MSG_DATA_TX;
    message3.eRmtRspEn   = DISABLE;
    message3.eIntEn      = ENABLE;
    message3.eEobEn      = DISABLE;
    message3.eBrs        = DISABLE;
    message3.eEsiCtlEn   = ENABLE;
    message3.eEsi        = DISABLE;

    message3.u32Id       = 0x33;
    message3.u8MBoxId    = 3;
    message3.eFormat     = CAN_FORMAT_EXT;
    message3.u8DataLen   = CAN_DATA_LEN;
    message3.eType       = CAN_FRAME_REMOTE;

    /* Remote frame no DATA FIELD */
    message3.u8DataLen   = 0;
    message3.pu8Data     = NULL;

    status = CAN_SetMessage(CAN, &message3);
    if (status == ERROR)
    {
        printf("[CAN][u8MBoxId:%2d] Set MBOX failed", message2.u8MBoxId);
        return -1;
    }

    CAN_EnableMailbox(CAN, message3.u8MBoxId);

    /* Wait CAN Extended Remote frame message3 txed */
    while (CAN_GetMailboxControlInfo(CAN, message3.u8MBoxId, CAN_MBOX_SET_MSG_NEW | CAN_MBOX_REQUEST_TX)) {}

    printf("\nTransmit CAN Extended Remote frame success\n");


    /* Init mailbox for transmit CAN Extended Data frame message4 */
    message4.eDataDir    = CAN_MSG_DATA_TX;
    message4.eRmtRspEn   = DISABLE;
    message4.eIntEn      = ENABLE;
    message4.eEobEn      = DISABLE;
    message4.eBrs        = DISABLE;
    message4.eEsiCtlEn   = ENABLE;
    message4.eEsi        = DISABLE;

    message4.u32Id       = 0x44;
    message4.u8MBoxId    = 4;
    message4.eFormat     = CAN_FORMAT_EXT;
    message4.eType       = CAN_FRAME_DATA;

    /* DATA FIELD */
    message4.u8DataLen   = CAN_DATA_LEN;
    message4.pu8Data     = au8TxBuffer;

    for (i = 0; i < message4.u8DataLen; i++)
    {
        message4.pu8Data[i] = i;
    }

    #if DEBUG_INFO
    printf("CAN Extended Frame Data:\n") ;
    CAN_Printf_Message(&message4);
    #endif

    status = CAN_SetMessage(CAN, &message4);
    if (status == ERROR)
    {
        printf("[CAN][u8MBoxId:%2d] Set MBOX failed", message4.u8MBoxId);
        return -1;
    }

    CAN_EnableMailbox(CAN, message4.u8MBoxId);

    /* Wait CAN Extended Data frame message4 txed */
    while (CAN_GetMailboxControlInfo(CAN, message4.u8MBoxId, CAN_MBOX_SET_MSG_NEW | CAN_MBOX_REQUEST_TX)) {}

    printf("\nTransmit CAN Extended Data frame success\n");

    while(1)
    {

    }
}

/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
