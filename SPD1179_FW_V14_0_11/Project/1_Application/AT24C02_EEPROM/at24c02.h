/******************************************************************************
 * @file     at24c02.h
 * @brief    at24c02 driver header file.
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


#ifndef AT24C02_H
#define AT24C02_H

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(SPD1177) || defined(SPD1179B))
    #include "spd1177.h"
#elif defined(SPD1179)
    #include "spd1179.h"
#else
    #include "spc1169.h"
#endif

#include <stdio.h>

/* I2C Interface */
#if (defined(SPD1179) || defined(SPD1177))
#define GPIOx_SCL_PIN                   PIN_GPIO14
#define I2C_SCL_FUNC                    PIN_GPIO14_I2C_SCL

#define GPIOx_SDA_PIN                   PIN_GPIO15
#define I2C_SDA_FUNC                    PIN_GPIO15_I2C_SDA
#else
#define GPIOx_SCL_PIN                   PIN_GPIO32
#define I2C_SCL_FUNC                    PIN_GPIO32_I2C_SCL

#define GPIOx_SDA_PIN                   PIN_GPIO33
#define I2C_SDA_FUNC                    PIN_GPIO33_I2C_SDA
#endif

/* Debug Message Output */
#define EEPROM_DEBUG_ON                 (1)

#define EEPROM_INFO(fmt,arg...)         printf("<<-EEPROM-INFO->> "fmt"\n",##arg)
#define EEPROM_ERROR(fmt,arg...)        printf("<<-EEPROM-ERROR->> "fmt"\n",##arg)
#define EEPROM_DEBUG(fmt,arg...)        do{\
                                        if(EEPROM_DEBUG_ON)\
                                        printf("<<-EEPROM-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                        }while(0)


/* 
 * AT24C02 2kb = 2048bit = 256 Byte
 * 32 pages of 8 bytes each
 *
 * Device Address (7bit)
 * 1 0 1 0 A2 A1 A0 
 */

#define EEPROM_DEVICE_ADDR_A0           (0U)
#define EEPROM_DEVICE_ADDR_A1           (0U)
#define EEPROM_DEVICE_ADDR_A2           (0U)

#define EEPROM_DEVICE_ADDR              (0x50U | (EEPROM_DEVICE_ADDR_A2 << 2) \
                                               | (EEPROM_DEVICE_ADDR_A1 << 1) \
                                               | (EEPROM_DEVICE_ADDR_A0 << 0))

#define EEPROM_PAGE_SIZE                (8U)            /* AT24C02 EEPROM Page Size */
#define EEPROM_SPEED                    (100000U)       /* AT24C02 EEPROM Communication Speed = 100kbps */


#define EEPROM_TIMEOUT                  (0xFFFFFFFFU)


/*
 *  @brief  24C02 Public Function Declaration
 */
ErrorStatus AT24C02_Init(void);

ErrorStatus AT24C02_WriteByte(uint8_t u8Addr, uint8_t u8Data);
ErrorStatus AT24C02_ReadByte(uint8_t u8Addr, uint8_t* pu8Data);

ErrorStatus AT24C02_WritePage(uint8_t* pu8Data, uint8_t u8Addr, uint8_t u8Size);

ErrorStatus AT24C02_Write(uint8_t* pu8Data, uint8_t u8Addr, uint16_t u16Size);
ErrorStatus AT24C02_Read(uint8_t* pu8Data, uint8_t u8Addr, uint16_t u16Size);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* AT24C02_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
