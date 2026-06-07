/******************************************************************************
 * @file     gpio.h
 * @brief    GPIO driver header file.
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


#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "spc1169.h"




/**
 *  @brief  GPIO data direction type definition
 */
typedef enum
{
    GPIO_INPUT            = 0,                /*!< Set GPIO port data direction as input  */
    GPIO_OUTPUT           = 1,                /*!< Set GPIO port data direction as output */
} GPIO_DirEnum;




/**
 *  @brief  GPIO pin level definition
 */
typedef enum
{
    GPIO_LEVEL_LOW        = 0,                /*!< GPIO pin is LOW  */
    GPIO_LEVEL_HIGH       = 1,                /*!< GPIO pin is HIGH */
} GPIO_LevelEnum;




/**
 *  @brief  GPIO edge detection type definition
 */
typedef enum
{
    GPIO_EDGE_NONE         = 0,               /*!< Disable edge detection                 */
    GPIO_EDGE_RISING       = 1,               /*!< Rising edge detection                  */
    GPIO_EDGE_FALLING      = 2,               /*!< Falling edge detection                 */
    GPIO_EDGE_BOTH         = 3,               /*!< Rising edge and Falling edge detection */
} GPIO_EdgeEnum;




/******************************************************************************
 * @brief      Get GPIO pin configuration register port and bit position
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define __GPIO_PIN_PORT(ePinName)           ((ePinName) >> (5U)  )
#define __GPIO_PIN_POS(ePinName)            ((ePinName) & (0x1FU))




/******************************************************************************
 * @brief      Set GPIO pin output level
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 * @param[in]  eLvl    :  Value to be written to GPIO pin, should be GPIO_LevelEnum
 *                        - \ref  GPIO_LEVEL_LOW
 *                        - \ref  GPIO_LEVEL_HIGH
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetLevel(ePinName,eLvl)                                           \
    WRITE_U32( GPIO_BASE + (__GPIO_PIN_PORT(ePinName) << 2U) +                 \
    ((eLvl)==GPIO_LEVEL_LOW ? 32U : 16U), (0x1U << __GPIO_PIN_POS(ePinName))  )

#define GPIO_WritePin(ePinName,eLvl)                                           \
    WRITE_U32( GPIO_BASE + (__GPIO_PIN_PORT(ePinName) << 2U) +                 \
    ((eLvl)==GPIO_LEVEL_LOW ? 32U : 16U), (0x1U << __GPIO_PIN_POS(ePinName))  )




/******************************************************************************
 * @brief      Set GPIO pin output HIGH
 *
 * @param[in]  ePinName: Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetHigh(ePinName)              WRITE_REG( GPIO->GSLR[__GPIO_PIN_PORT(ePinName)], ( 0x1U << __GPIO_PIN_POS(ePinName) ) )




/******************************************************************************
 * @brief      Set GPIO pin output LOW
 *
 * @param[in]  ePinName: Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetLow(ePinName)               WRITE_REG( GPIO->GCLR[__GPIO_PIN_PORT(ePinName)], ( 0x1U << __GPIO_PIN_POS(ePinName) ) )




/******************************************************************************
 * @brief      Read GPIO pin input level
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     Value read from GPIO pin
 *             - \ref 0 : GPIO level is LOW
 *             - \ref 1 : GPIO level is HIGH
 *
 ******************************************************************************/
#define GPIO_GetLevel(ePinName)             READ_FIELD( GPIO->GPLR[__GPIO_PIN_PORT(ePinName)], \
        ( 0x1U << __GPIO_PIN_POS(ePinName) ),  \
        __GPIO_PIN_POS(ePinName)               \
                                                      )

#define GPIO_ReadPin(ePinName)              READ_FIELD( GPIO->GPLR[__GPIO_PIN_PORT(ePinName)], \
        ( 0x1U << __GPIO_PIN_POS(ePinName) ),  \
        __GPIO_PIN_POS(ePinName)               \
                                                      )




/******************************************************************************
 * @brief      Toggle GPIO pin output value
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 * @note       The toggle speed is lower than GPIO->GSLR or GPIO->GCLR
 *
 ******************************************************************************/
#define GPIO_Toggle(ePinName)               (GPIO->GPLR[__GPIO_PIN_PORT(ePinName)] ^= (0x01U << __GPIO_PIN_POS(ePinName)))
#define GPIO_TogglePin(ePinName)            (GPIO->GPLR[__GPIO_PIN_PORT(ePinName)] ^= (0x01U << __GPIO_PIN_POS(ePinName)))


/******************************************************************************
 * @brief      Set GPIO pin direction
 *
 * @param[in]  ePinName: Select the GPIO pin, should be PIN_NameEnum
 * @param[in]  eDir    : GPIO direction, should be GPIO_DirEnum
 *                       - \ref GPIO_INPUT
 *                       - \ref GPIO_OUTPUT
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetDirection(ePinName,eDir)    WRITE_FIELD( GPIO->GPDR[__GPIO_PIN_PORT(ePinName)], \
        ( 0x1U << __GPIO_PIN_POS(ePinName) ),  \
        __GPIO_PIN_POS(ePinName),              \
        (eDir)                                 \
                                                       )

#define GPIO_SetPinDir(ePinName,eDir)       WRITE_FIELD( GPIO->GPDR[__GPIO_PIN_PORT(ePinName)], \
        ( 0x1U << __GPIO_PIN_POS(ePinName) ),  \
        __GPIO_PIN_POS(ePinName),              \
        (eDir)                                 \
                                                       )




/******************************************************************************
 * @brief      Set GPIO pin as output
 *
 * @param[in]  ePinName: Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetAsOutput(ePinName)          WRITE_REG( GPIO->GSDR[__GPIO_PIN_PORT(ePinName)], ( 0x1U << __GPIO_PIN_POS(ePinName) ) )




/******************************************************************************
 * @brief      Set GPIO pin as input
 *
 * @param[in]  ePinName: Select the chip pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetAsInput(ePinName)           WRITE_REG( GPIO->GCDR[__GPIO_PIN_PORT(ePinName)], ( 0x1U << __GPIO_PIN_POS(ePinName) ) )




/******************************************************************************
 * @brief      Get GPIO pin direction
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - GPIO pin is input
 *             1 - GPIO pin is output
 *
 ******************************************************************************/
#define GPIO_GetDirection(ePinName)         READ_FIELD( GPIO->GPDR[__GPIO_PIN_PORT(ePinName)],  \
        ( 0x1U << __GPIO_PIN_POS(ePinName) ),   \
        __GPIO_PIN_POS(ePinName)                \
                                                      )




/******************************************************************************
 * @brief      Enable GPIO rising edge detect
 *
 * @param[in]  pinNum:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_EnableRisingEdgeDetect(ePinName)     (GPIO->GSRE[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Disable GPIO rising edge detect
 *
 * @param[in]  pinNum:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_DisableRisingEdgeDetect(ePinName)    (GPIO->GCRE[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Enable GPIO falling edge detect
 *
 * @param[in]  pinNum:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_EnableFallingEdgeDetect(ePinName)    (GPIO->GSFE[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Disable GPIO falling edge detect
 *
 * @param[in]  pinNum:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_DisableFallingEdgeDetect(ePinName)   (GPIO->GCFE[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Enable GPIO rising edge triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_EnableRisingEdgeInt(ePinName)        (GPIO->GREIE[__GPIO_PIN_PORT(ePinName)] |= (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Disable GPIO rising edge triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_DisableRisingEdgeInt(ePinName)       (GPIO->GREIE[__GPIO_PIN_PORT(ePinName)] &= (~(0x01U << __GPIO_PIN_POS(ePinName))))




/******************************************************************************
 * @brief      Enable GPIO falling edge triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_EnableFallingEdgeInt(ePinName)       (GPIO->GFEIE[__GPIO_PIN_PORT(ePinName)] |= (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Disable GPIO falling edge triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_DisableFallingEdgeInt(ePinName)      (GPIO->GFEIE[__GPIO_PIN_PORT(ePinName)] &= (~(0x01U << __GPIO_PIN_POS(ePinName))))




/******************************************************************************
 * @brief      Get GPIO rising edge triggered event raw flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - No detected rising edge
 *             1 - Rising edge was detected on the selected pin
 *
 ******************************************************************************/
#define GPIO_GetRisingEdgeIntRawFlag(ePinName)    ((GPIO->GRERAWIF[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))




/******************************************************************************
 * @brief      Get GPIO falling edge triggered event raw flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - No detected falling edge
 *             1 - Falling edge was detected on the selected pin
 *
 ******************************************************************************/
#define GPIO_GetFallingEdgeIntRawFlag(ePinName)   ((GPIO->GFERAWIF[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))




/******************************************************************************
 * @brief      Get GPIO rising edge triggered interrupt flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - No interrupt for rising edge on the selected pin
 *             1 - Interrupt was generated for rising edge on the selected pin
 *
 ******************************************************************************/
#define GPIO_GetRisingEdgeIntFlag(ePinName)   ((GPIO->GREIF[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))



/******************************************************************************
 * @brief      Get GPIO falling edge triggered interrupt flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - No interrupt for falling edge on the selected pin
 *             1 - Interrupt was generated for falling edge on the selected pin
 *
 ******************************************************************************/
#define GPIO_GetFallingEdgeIntFlag(ePinName)  ((GPIO->GFEIF[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))




/******************************************************************************
 * @brief      Clear GPIO rising edge triggered interrupt flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ClearRisingEdgeInt(ePinName)   (GPIO->GREIC[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Clear GPIO falling edge triggered interrupt flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ClearFallingEdgeInt(ePinName)  (GPIO->GFEIC[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Force GPIO rising edge triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ForceRisingEdgeInt(ePinName)   (GPIO->GREIFRC[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Force GPIO falling edge triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ForceFallingEdgeInt(ePinName)  (GPIO->GFEIFRC[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Enable GPIO level detect
 *
 * @param[in]  pinNum:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_EnableLevelDetect(ePinName)    (GPIO->GSLDE[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Disable GPIO level detect
 *
 * @param[in]  pinNum:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_DisableLevelDetect(ePinName)   (GPIO->GCLDE[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Enable GPIO level triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_EnableLevelInt(ePinName)       (GPIO->GLIE[__GPIO_PIN_PORT(ePinName)] |= (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Disable GPIO level triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_DisableLevelInt(ePinName)      (GPIO->GLIE[__GPIO_PIN_PORT(ePinName)] &= (~(0x01U << __GPIO_PIN_POS(ePinName))))




/******************************************************************************
 * @brief      Get GPIO level triggered event raw flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - No specified level was detected on the selected pin
 *             1 - Specified level was detected on the selected pin
 *
 ******************************************************************************/
#define GPIO_GetLevelIntRawFlag(ePinName)   ((GPIO->GLRAWIF[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))




/******************************************************************************
 * @brief      Get GPIO level triggered interrupt flag
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - No interrupt for the specified level on the selected pin
 *             1 - Interrupt was generated for the specified level on the
 *                 selected pin
 *
 ******************************************************************************/
#define GPIO_GetLevelIntFlag(ePinName)       ((GPIO->GLIF[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))




/******************************************************************************
 * @brief      Clear GPIO level triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ClearLevelInt(ePinName)         (GPIO->GLIC[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Force level triggered interrupt
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ForceLevelInt(ePinName)         (GPIO->GLIFRC[__GPIO_PIN_PORT(ePinName)] = (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Set GPIO level detect polarity to trigger the interrupt
 *
 * @param[in]  ePinName : Select the GPIO pin, should be PIN_NameEnum
 *             ePinLevel: Select the GPIO pin level, should be GPIO_LevelEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetLevelIntPolarity(ePinName, ePinLevel)   { GPIO->GLPOL[__GPIO_PIN_PORT(ePinName)] &= (~(0x01U << __GPIO_PIN_POS(ePinName))); \
        GPIO->GLPOL[__GPIO_PIN_PORT(ePinName)] |= ((ePinLevel) << __GPIO_PIN_POS(ePinName)); }




/******************************************************************************
 * @brief      Set GPIO level detect target as GPIO input is high
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetLevelIntActiveHigh(ePinName) (GPIO->GLPOL[__GPIO_PIN_PORT(ePinName)] |= (0x01U << __GPIO_PIN_POS(ePinName)))




/******************************************************************************
 * @brief      Set GPIO level detect target as GPIO input is low
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_SetLevelIntActiveLow(ePinName)  (GPIO->GLPOL[__GPIO_PIN_PORT(ePinName)] &= (~(0x01U << __GPIO_PIN_POS(ePinName))))




/******************************************************************************
 * @brief      Get level triggered interrupt polarity
 *
 * @param[in]  ePinName:  Select the GPIO pin, should be PIN_NameEnum
 *
 * @return     0 - Interrupt triggered when GPIO level is HIGH
 *             1 - Interrupt triggered when GPIO level is LOW
 *
 ******************************************************************************/
#define GPIO_GetLevelIntPolarity(ePinName)  ((GPIO->GLPOL[__GPIO_PIN_PORT(ePinName)] & (0x01U << __GPIO_PIN_POS(ePinName))) >> __GPIO_PIN_POS(ePinName))




/******************************************************************************
 * @brief      Get Global GPIO rising edge triggered event raw flag
 *
 * @param[in]  None
 *
 * @return     0 - No rising edge triggered event occurred
 *             1 - Rising edge triggered event occurred
 *
 ******************************************************************************/
#define GPIO_GetGlobalRisingEdgeIntRawFlag()    ((GPIO->GGRAWIF & GGRAWIF_REDGE_Msk) >> GGRAWIF_REDGE_Pos)




/******************************************************************************
 * @brief      Get Global GPIO falling edge triggered event raw flag
 *
 * @param[in]  None
 *
 * @return     0 - No falling edge triggered event occurred
 *             1 - Falling edge triggered event occurred
 *
 ******************************************************************************/
#define GPIO_GetGlobalFallingEdgeIntRawFlag()   ((GPIO->GGRAWIF & GGRAWIF_FEDGE_Msk) >> GGRAWIF_FEDGE_Pos)




/******************************************************************************
 * @brief      Get Global GPIO edge-triggered event raw flag
 *
 * @param[in]  None
 *
 * @return     0 - No edge-triggered event occurred
 *             1 - Edge-triggered event occurred
 *
 ******************************************************************************/
#define GPIO_GetGlobalEdgeIntRawFlag()      ((GPIO->GGRAWIF & GGRAWIF_EDGE_Msk) >> GGRAWIF_EDGE_Pos)




/******************************************************************************
 * @brief      Get GPIO level-triggered event raw flag
 *
 * @param[in]  None
 *
 * @return     0 - No level-triggered event occurred
 *             1 - Level-triggered event occurred
 *
 ******************************************************************************/
#define GPIO_GetGlobalLevelIntRawFlag()     ((GPIO->GGRAWIF & GGRAWIF_LEVEL_Msk) >> GGRAWIF_LEVEL_Pos)




/******************************************************************************
 * @brief      Get GPIO all global event raw flag
 *
 * @param[in]  None
 *
 * @return     Full global event raw flag register value
 *
 *
 ******************************************************************************/
#define GPIO_GetAllGlobalIntRawFlag()       (GPIO->GGRAWIF)




/******************************************************************************
 * @brief      Get Global GPIO edge-triggered interrupt flag
 *
 * @param[in]  None
 *
 * @return     0 - No edge-triggered interrupt was generated
 *             1 - Edge-triggered interrupt was generated
 *
 ******************************************************************************/
#define GPIO_GetGlobalEdgeIntFlag()         ((GPIO->GGIF & GGIF_EDGE_Msk) >> GGIF_EDGE_Pos)




/******************************************************************************
 * @brief      Get GPIO level-triggered interrupt flag
 *
 * @param[in]  None
 *
 * @return     0 - No level-triggered interrupt was generated
 *             1 - Level-triggered interrupt was generated
 *
 ******************************************************************************/
#define GPIO_GetGlobalLevelIntFlag()        ((GPIO->GGIF & GGIF_LEVEL_Msk) >> GGIF_LEVEL_Pos)




/******************************************************************************
 * @brief      Clear GPIO edge-triggered interrupt flag
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ClearGlobalEdgeInt()           (GPIO->GGIC = GGIC_EDGE_CLEAR)




/******************************************************************************
 * @brief      Clear GPIO level-triggered interrupt flag
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_ClearGlobalLevelInt()          (GPIO->GGIC = GGIC_LEVEL_CLEAR)




/******************************************************************************
 * @brief      Get GPIO all global interrupt flag
 *
 * @param[in]  None
 *
 * @return     Full global interrupt flag register value
 *
 *
 ******************************************************************************/
#define GPIO_GetAllGlobalIntFlag()          (GPIO->GGIF)




/******************************************************************************
 * @brief      Enable write access to the protected GPIO registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_WALLOW()                       (GPIO->GPIOREGKEY = 0x1ACCE551U)




/******************************************************************************
 * @brief      Disable write access to the protected GPIO registers
 *
 * @param[in]  None
 *
 * @return     None
 *
 ******************************************************************************/
#define GPIO_WDIS()                         (GPIO->GPIOREGKEY = 0x0U)




/**
 *  @brief GPIO Public Function Declaration
 */
void GPIO_SetEdgeIntMode(PIN_NameEnum ePinName, GPIO_EdgeEnum eEdgeType);
void GPIO_SetOpenDrainOutputHigh(PIN_NameEnum ePinName);
void GPIO_SetOpenDrainOutputLow(PIN_NameEnum ePinName);




#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* GPIO_H */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
