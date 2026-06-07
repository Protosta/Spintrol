/******************************************************************************
 * @file     lin.c
 * @brief    LIN low level functions
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


#include "lin.h"





#include "lin_lld_uart.h"

/* Globle variable */
#if (LIN_MODE == _SLAVE_MODE_)
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME__)
lin_message_timeout_type tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;    /**< timeout type */
l_u16 tl_check_timeout = N_MAX_TIMEOUT_CNT;                            /**< timeout counter*/
lin_service_status tl_service_status = LD_SERVICE_IDLE;              /**< Status of the last configuration service */
#endif
#endif

#if (LIN_MODE == _MASTER_MODE_)
l_u8        etf_collision_flag[LIN_NUM_OF_IFCS] = {0};
/* Extern globle variable */
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME__)
lin_message_timeout_type tl_check_timeout_type_array[LIN_NUM_OF_IFCS] = {LD_NO_CHECK_TIMEOUT};
l_u16 tl_check_timeout_array[LIN_NUM_OF_IFCS] = {N_MAX_TIMEOUT_CNT};
#endif

l_u8 lin_lld_init
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */
    l_u8 ret = 0;

    /* Check for valid interface */
    if (iii > LIN_NUM_OF_IFCS)
    {
        ret = LIN_LLD_INVALID_IFC;
    }
    else
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_init(lin_hw, iii);
        ret = LIN_LLD_OK;
    }
    return ret;
}

l_u8 lin_lld_deinit
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */
    l_u8 ret = 0;

    /* Check for valid interface */
    if (iii > LIN_NUM_OF_IFCS)
    {
        ret = LIN_LLD_INVALID_IFC;
    }
    else
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_deinit(lin_hw);
        ret = LIN_LLD_OK;
    }

    return ret;
}

l_u8 lin_lld_get_state
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */
    l_u8 ret = 0;

    /* Check for valid interface */
    if (iii > LIN_NUM_OF_IFCS)
    {
        ret = LIN_LLD_INVALID_IFC;
    }
    else
    {
        lin_hw = lin_virtual_ifc[iii];
        ret = lin_lld_uart_get_state(lin_hw);
    }

    return ret;
}

void lin_lld_tx_header
(
    /* [IN] interface identifier */
    l_ifc_handle iii,
    /* [IN] ID of the header to be sent */
    l_u8 pid
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */

    /* Check for valid interface */
    if (iii <= LIN_NUM_OF_IFCS)
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_tx_header(lin_hw, pid);
    }

    return;
}

void lin_lld_tx_wake_up
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw;

    /* Check for valid interface */
    if (iii <= LIN_NUM_OF_IFCS)
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_tx_wake_up(lin_hw);
    }

    return;
}

void lin_lld_int_enable
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw;

    /* Check for valid interface */
    if (iii <= LIN_NUM_OF_IFCS)
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_int_enable(lin_hw);
    }

    return;
}

l_u8 lin_lld_int_disable
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw;
    l_u8 ret = 0;

    /* Check for valid interface */
    if (iii > LIN_NUM_OF_IFCS)
    {
        ret = LIN_LLD_INVALID_IFC;
    }
    else
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_int_disable(lin_hw);
        ret = LIN_LLD_OK;
    }

    return ret;
}

void lin_lld_ignore_response
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */

    /* Check for valid interface */
    if (iii <= LIN_NUM_OF_IFCS)
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_ignore_response(lin_hw);
    }

    return;
}

void lin_lld_set_low_power_mode
(
    /* [IN] interface identifier */
    l_ifc_handle iii
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */

    /* Check for valid interface */
    if (iii <= LIN_NUM_OF_IFCS)
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_set_low_power_mode(lin_hw);
    }

    return;
}

l_u8 lin_lld_set_response
(
    /* [IN] interface identifier */
    l_ifc_handle iii,
    /* [IN] response length */
    l_u8 response_length
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */
    l_u8 ret = 0;

    /* Check for valid interface */
    if (iii > LIN_NUM_OF_IFCS)
    {
        ret = LIN_LLD_INVALID_IFC;
    }
    else
    {
        /* Check for valid response length */
        if (response_length > 8)
        {
            ret = LIN_LLD_INVALID_PARA;
        }
        else
        {
            /* Put response length into buffer */
            *(lin_ifc_configuration[iii].response_buffer) = response_length;

            /* Find LIN HW interface which is mounted to interface */
            lin_hw = lin_virtual_ifc[iii];
            lin_lld_uart_tx_response(lin_hw);
            ret = LIN_LLD_OK;
        }
    }

    return ret;
}

l_u8 lin_lld_rx_response
(
    /* [IN] interface identifier */
    l_ifc_handle iii,
    /* [IN] response length */
    l_u8 response_length
)
{
    lin_hardware_name lin_hw; /* Indicator of LIN HW */
    l_u8 ret = 0;

    /* Check for valid interface */
    if (iii > LIN_NUM_OF_IFCS)
    {
        ret = LIN_LLD_INVALID_IFC;
    }
    else
    {
        /* Find LIN HW interface which is mounted to interface */
        lin_hw = lin_virtual_ifc[iii];
        lin_lld_uart_rx_response(lin_hw, response_length);
        ret = LIN_LLD_OK;
    }

    return ret;
}

void lin_lld_set_etf_collision_flag(
    /* [IN] interface identifier */
    l_ifc_handle iii)
{
    /* Set flag in case of occurring collision in event trigger frame */
    etf_collision_flag[iii] = 1;
}

void lin_lld_clear_etf_collision_flag(
    /* [IN] interface identifier */
    l_ifc_handle iii)
{
    /* Clear flag in case of occurring collision in event trigger frame */
    etf_collision_flag[iii] = 0;
}

#endif /* end of LIN_MODE == _MASTER_MODE_ */


#if LIN_MODE == _SLAVE_MODE_
/* Extern globle variable */

l_u8 lin_lld_init
(
)
{
    lin_lld_uart_init((l_ifc_handle)0);

    return LIN_LLD_OK;
}

l_u8 lin_lld_deinit
(
)
{
    lin_lld_uart_deinit();

    return LIN_LLD_OK;
}

l_u8 lin_lld_get_status
(
)
{
    l_u8 ret = 0;

    lin_lld_uart_get_status();

    return ret;
}

l_u8 lin_lld_get_state()
{
    l_u8 ret = 0;

    ret = lin_lld_uart_get_state();

    return ret;
}

void lin_lld_tx_wake_up ()
{
    lin_lld_uart_tx_wake_up();

    return;
}

void lin_lld_int_enable ()
{
    lin_lld_uart_int_enable();

    return;
}

l_u8 lin_lld_int_disable ()
{
    lin_lld_uart_int_disable();

    return LIN_LLD_OK;
}

void lin_lld_ignore_response
(
)
{
    lin_lld_uart_ignore_response();

    return;
}

void lin_lld_set_low_power_mode ()
{

    lin_lld_uart_set_low_power_mode();

    return;
}

l_u8 lin_lld_set_response
(
    /* [IN] response length */
    l_u8 response_length
)
{
    l_u8 ret = 0;

    /* Check for valid response length */
    if (response_length > 8)
    {
        ret = LIN_LLD_INVALID_PARA;
    }
    else
    {
        /* Put response length into buffer */
        lin_lld_response_buffer[0] = response_length;

        lin_lld_uart_tx_response();

        ret = LIN_LLD_OK;
    }

    return ret;
}

l_u8 lin_lld_rx_response
(
    /* [IN] response length */
    l_u8 response_length
)
{
    lin_lld_uart_rx_response(response_length);

    return LIN_LLD_OK;
}

#endif /* End of LIN_MODE == _SLAVE_MODE_ */

/*** Common function used to all low-level driver ***/

l_u8 lin_process_parity
(
    /* [IN] PID need to be send */
    l_u8 pid,
    /* [IN] Check or Make parity */
    l_u8 type
)
{
    l_u8 parity;
    l_u8 ret;

    parity = (((BIT(pid, 0)^BIT(pid, 1)^BIT(pid, 2)^BIT(pid, 4)) << 6)|
              ((~(BIT(pid, 1)^BIT(pid, 3)^BIT(pid, 4)^BIT(pid, 5))) << 7));
    if (CHECK_PARITY == type)
    {
        if ((pid&0xC0) != parity)
        {
            ret = 0xFF;
        }
        else
        {
            ret = (l_u8)(pid&0x3F);
        }
    }
    else
    {
        ret = (l_u8)(pid|parity);
    }

    return (ret);
}

l_u8 lin_checksum
(
    /* [IN] pointer to buffer */
    l_u8 *buffer,
    /* [IN] pid */
    l_u8 raw_pid
)
{
    l_u8 length;
    l_u16 check_sum;

    /* 1. PID correspond to Master request and Slave response, their checksum cal is classic
    the non-diagnostic frame is calculated in Enhanced */
    if ((0x3C != raw_pid) && (0x7D != raw_pid))
    {
        check_sum = raw_pid;
    }
    else
    {
        check_sum = 0;
    }

    for (length = *buffer; 0 < length; length--)
    {
        buffer++;
        check_sum += *(buffer);
        /* 2. to deal with the carry */
        if (check_sum > 0xFF)
        {
            check_sum -= 0xFF;
        }
    }

    /* 3. to reverse */
    return (l_u8)(~check_sum);
}

void lin_lld_timer_init
(
    void
)
{
}


#if (LIN_MODE == _SLAVE_MODE_)
void lin_lld_mcu_reset()
{



}

#endif /* End (LIN_MODE == _SLAVE_MODE_) */


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
