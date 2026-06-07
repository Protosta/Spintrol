/******************************************************************************
 * @file     dma.c
 * @brief    DMA firmware functions.
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

#include "dma.h"




///******************************************************************************
// * @brief      Set handshake with SPI0 Tx (Memory to Peripheral)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithSPI0Tx(DMACH_REGS *DMACHx)
//{
//    /* Set destination address */
//    DMA_SetDestinationAddr(DMACHx, SPI0_BASE);
//
//    /* Set destination peripheral */
//    DMA_SetDestinationPeripheral(DMACHx, DMA_DPER_SPI0_TX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_MEMORY_TO_PERIPHERAL);
//
//    /* Set destination Address mode */
//    DMA_SetDestinationAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set destination handshaking */
//    DMA_SetDestinationHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with SPI1 Tx (Memory to Peripheral)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithSPI1Tx(DMACH_REGS *DMACHx)
//{
//    /* Set destination address */
//    DMA_SetDestinationAddr(DMACHx, SPI1_BASE);
//
//    /* Set destination peripheral */
//    DMA_SetDestinationPeripheral(DMACHx, DMA_DPER_SPI1_TX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_MEMORY_TO_PERIPHERAL);
//
//    /* Set destination Address mode */
//    DMA_SetDestinationAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set destination handshaking */
//    DMA_SetDestinationHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with SPI0 Rx (Peripheral to Memory)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithSPI0Rx(DMACH_REGS *DMACHx)
//{
//    /* Set source address */
//    DMA_SetSourceAddr(DMACHx, SPI0_BASE);
//
//    /* Set source peripheral */
//    DMA_SetSourcePeripheral(DMACHx, DMA_SPER_SPI0_RX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_PERIPHERAL_TO_MEMORY);
//
//    /* Set source Address mode */
//    DMA_SetSourceAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set source handshaking */
//    DMA_SetSourceHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with SPI1 Rx (Peripheral to Memory)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithSPI1Rx(DMACH_REGS *DMACHx)
//{
//    /* Set source address */
//    DMA_SetSourceAddr(DMACHx, SPI1_BASE);
//
//    /* Set source peripheral */
//    DMA_SetSourcePeripheral(DMACHx, DMA_SPER_SPI1_RX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_PERIPHERAL_TO_MEMORY);
//
//    /* Set source Address mode */
//    DMA_SetSourceAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set source handshaking */
//    DMA_SetSourceHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with UART0 Tx (Memory to Peripheral)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithUART0Tx(DMACH_REGS *DMACHx)
//{
//    /* Set destination address */
//    DMA_SetDestinationAddr(DMACHx, UART0_BASE);
//
//    /* Set destination peripheral */
//    DMA_SetDestinationPeripheral(DMACHx, DMA_DPER_UART0_TX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_MEMORY_TO_PERIPHERAL);
//
//    /* Set destination Address mode */
//    DMA_SetDestinationAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set destination handshaking */
//    DMA_SetDestinationHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with UART1 Tx (Memory to Peripheral)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithUART1Tx(DMACH_REGS *DMACHx)
//{
//    /* Set destination address */
//    DMA_SetDestinationAddr(DMACHx, UART1_BASE);
//
//    /* Set destination peripheral */
//    DMA_SetDestinationPeripheral(DMACHx, DMA_DPER_UART1_TX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_MEMORY_TO_PERIPHERAL);
//
//    /* Set destination Address mode */
//    DMA_SetDestinationAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set destination handshaking */
//    DMA_SetDestinationHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with UART0 Rx (Peripheral to Memory)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithUART0Rx(DMACH_REGS *DMACHx)
//{
//    /* Set source address */
//    DMA_SetSourceAddr(DMACHx, UART0_BASE);
//
//    /* Set source peripheral */
//    DMA_SetSourcePeripheral(DMACHx, DMA_SPER_UART0_RX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_PERIPHERAL_TO_MEMORY);
//
//    /* Set source Address mode */
//    DMA_SetSourceAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set source handshaking */
//    DMA_SetSourceHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with UART1 Rx (Peripheral to Memory)
// *
// * @param[in]  DMACHx:  Select the DMA channel (DMACH0 ~ DMACH7)
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithUART1Rx(DMACH_REGS *DMACHx)
//{
//    /* Set source address */
//    DMA_SetSourceAddr(DMACHx, UART1_BASE);
//
//    /* Set source peripheral */
//    DMA_SetSourcePeripheral(DMACHx, DMA_SPER_UART1_RX);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_PERIPHERAL_TO_MEMORY);
//
//    /* Set source Address mode */
//    DMA_SetSourceAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set source handshaking */
//    DMA_SetSourceHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with ADC Result Register (Peripheral to Memory)
// *
// * @param[in]  DMACHx     :  Select the DMA channel (DMACH0 ~ DMACH7)
// * @param[in]  ePeripheral:  Select the peripheral define in DMA_PeripheralEnum
// *                           \ref DMA_SPER_ADCRESULT0 ~ DMA_SPER_ADCRESULT7
// *
// * @return     none
// *
// ******************************************************************************/
//void __DMA_SetHandShakeWithADC(DMACH_REGS *DMACHx, DMA_PeripheralEnum ePeripheral)
//{
//    if (ePeripheral < DMA_SPER_ADCRESULT0)
//    {
//        return;
//    }
//
//    /* Set source address */
//    DMA_SetSourceAddr(DMACHx, AFE_BASE + 0x128U + (ePeripheral - DMA_SPER_ADCRESULT0) * 4U);
//
//    /* Set source peripheral */
//    DMA_SetSourcePeripheral(DMACHx, ePeripheral);
//
//    /* Set Transfer type */
//    DMA_SetTransferType(DMACHx, DMA_PERIPHERAL_TO_MEMORY);
//
//    /* Set source Address mode */
//    DMA_SetSourceAddrMode(DMACHx, DMA_ADDRESS_NO_CHANGE);
//
//    /* Set source handshaking */
//    DMA_SetSourceHandShake(DMACHx, DMA_HANDSHAKE_BY_HARDWARE, DMA_HANDSHAKE_POL_ACTIVE_HIGH);
//}
//
//
//
//
///******************************************************************************
// * @brief      Set handshake with Peripheral
// *
// * @param[in]  DMACHx     : Select the DMA channel (DMACH0 ~ DMACH7)
// * @param[in]  ePeripheral: Select the peripheral define in DMA_PeripheralEnum
// *
// * @return     none
// *
// ******************************************************************************/
//void DMA_SetHandShakeWithPeripheral(DMACH_REGS *DMACHx, DMA_PeripheralEnum ePeripheral)
//{
//    switch (ePeripheral)
//    {
//        case DMA_SPER_UART0_RX:
//            __DMA_SetHandShakeWithUART0Rx(DMACHx);
//            break;
//
//        case DMA_DPER_UART0_TX:
//            __DMA_SetHandShakeWithUART0Tx(DMACHx);
//            break;
//
//        case DMA_SPER_UART1_RX:
//            __DMA_SetHandShakeWithUART1Rx(DMACHx);
//            break;
//
//        case DMA_DPER_UART1_TX:
//            __DMA_SetHandShakeWithUART1Tx(DMACHx);
//            break;
//
//        case DMA_SPER_SPI0_RX:
//            __DMA_SetHandShakeWithSPI0Rx(DMACHx);
//            break;
//
//        case DMA_DPER_SPI0_TX:
//            __DMA_SetHandShakeWithSPI0Tx(DMACHx);
//            break;
//
//        case DMA_SPER_SPI1_RX:
//            __DMA_SetHandShakeWithSPI1Rx(DMACHx);
//            break;
//
//        case DMA_DPER_SPI1_TX:
//            __DMA_SetHandShakeWithSPI1Tx(DMACHx);
//            break;
//
//        case DMA_SPER_ADCRESULT0:
//        case DMA_SPER_ADCRESULT1:
//        case DMA_SPER_ADCRESULT2:
//        case DMA_SPER_ADCRESULT3:
//        case DMA_SPER_ADCRESULT4:
//        case DMA_SPER_ADCRESULT5:
//        case DMA_SPER_ADCRESULT6:
//        case DMA_SPER_ADCRESULT7:
//            __DMA_SetHandShakeWithADC(DMACHx, ePeripheral);
//            break;
//
//        default:
//            break;
//    }
//}


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
