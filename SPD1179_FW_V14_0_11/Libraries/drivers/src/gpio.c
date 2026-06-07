/******************************************************************************
 * @file     gpio.c
 * @brief    GPIO firmware functions.
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

#include "gpio.h"


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
 * @brief      Configure GPIO edge detection type
 *
 * @param[in]  ePinName :  Select the pin, should be PIN_NameEnum
 * @param[in]  eEdgeType:  Edge detection type, should be GPIO_EdgeIntEnum
 *                         - \ref GPIO_EDGE_RISING  -> Rising edge
 *                         - \ref GPIO_EDGE_FALLING -> Falling edge
 *                         - \ref GPIO_EDGE_BOTH    -> Rising and Falling edge
 *                         - \ref GPIO_EDGE_NONE    -> Disable edge detection
 *
 * @return     none
 *
 ******************************************************************************/
void GPIO_SetEdgeIntMode(PIN_NameEnum ePinName, GPIO_EdgeEnum eEdgeType)
{
    /* Enable/Disabe GPIO Rising/Falling interrupt function */
    switch (eEdgeType)
    {
        case GPIO_EDGE_RISING:
            GPIO_EnableRisingEdgeDetect(ePinName);
            GPIO_EnableRisingEdgeInt(ePinName);

            GPIO_DisableFallingEdgeDetect(ePinName);
            GPIO_DisableFallingEdgeInt(ePinName);
            break;

        case GPIO_EDGE_FALLING:
            GPIO_DisableRisingEdgeDetect(ePinName);
            GPIO_DisableRisingEdgeInt(ePinName);

            GPIO_EnableFallingEdgeDetect(ePinName);
            GPIO_EnableFallingEdgeInt(ePinName);
            break;

        case GPIO_EDGE_BOTH:
            GPIO_EnableRisingEdgeDetect(ePinName);
            GPIO_EnableRisingEdgeInt(ePinName);

            GPIO_EnableFallingEdgeDetect(ePinName);
            GPIO_EnableFallingEdgeInt(ePinName);
            break;

        case GPIO_EDGE_NONE:
            GPIO_DisableRisingEdgeDetect(ePinName);
            GPIO_DisableRisingEdgeInt(ePinName);

            GPIO_DisableFallingEdgeDetect(ePinName);
            GPIO_DisableFallingEdgeInt(ePinName);
            break;

        default:
            break;
    }
}




/******************************************************************************
 * @brief       Set GPIO Open drain output high
 *
 * @param[in]   ePinName :  Select the pin, should be PIN_NameEnum
 *
 * @note        The high open-drain output requires the external level 
 *              to be pulled up
 *
 * @return      None
 *
 ******************************************************************************/
void GPIO_SetOpenDrainOutputHigh(PIN_NameEnum ePinName)
{
    /* Set GPIO channal */
    PIN_SetChannel(ePinName, PIN_CH0);

    /* Set GPIO Intput function */
    GPIO_SetDirection(ePinName, GPIO_INPUT);
}




/******************************************************************************
 * @brief       Set GPIO Open drain output low
 *
 * @param[in]   ePinName :  Select the pin, should be PIN_NameEnum
 *
 * @return      None
 *
 ******************************************************************************/
void GPIO_SetOpenDrainOutputLow(PIN_NameEnum ePinName)
{
    /* Set GPIO channal */
    PIN_SetChannel(ePinName, PIN_CH0);

    /* Set GPIO Output low */
    GPIO_SetLow(ePinName);

    /* Set GPIO Output function */
    GPIO_SetDirection(ePinName, GPIO_OUTPUT);
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
