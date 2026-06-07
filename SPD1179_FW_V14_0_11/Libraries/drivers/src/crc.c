/******************************************************************************
 * @file     crc.c
 * @brief    CRC firmware functions.
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

#include "crc.h"


#if defined(__IAR_SYSTEMS_ICC__)
    #pragma optimize=low
#elif defined(__GNUC__)
    #pragma GCC push_options
    #pragma GCC optimize ("O1")
#elif defined(__CC_ARM)
    #pragma push
    #pragma O1
#endif


/****************************************************************************//**
 * @brief      CRC Initial
 *
 * @param[in]  CRCx  :  Select the CRC module
 * @param[in]  eMode :  CRC mode defined by CRC_ModeEnum
 *
 * @return     none
 *
 *******************************************************************************/
void CRC_Init(CRC_REGS *CRCx, CRC_ModeEnum eMode)
{
    /* Disable CRC and interrupt */
    CLEAR_REG((CRCx)->CRCCTL);
    CRC_DisableInt(CRCx, CRC_INT_ALL);
    /*
     *  Algorithm             Poly      
     *  CRC-8/AUTOSAR_2F      0x2F      
     *  CRC-16/CCITT          0x1021    
     *  CRC-16/IBM            0x8005    
     *  CRC-16/T10-DIF        0x8BB7    
     *  CRC-16/DNP            0x3D65    
     *  CRC-32/IEEE802P3      0x04C11DB7
     */  
    CRC_SetMode(CRCx, eMode);
    
    /*
     *  Algorithm             RefIn    RefOut   XorOut 
     *  CRC-16/DNP            true     true     0xFFFF
     *  CRC-32/IEEE802P3      true     true     0xFFFFFFFF
     */       
    if ((eMode == CRC_MODE_32_IEEE802P3) || (eMode == CRC_MODE_16_DNP))
    {
        CRC_ReverseData(CRC, CRC_DATA_REVERSE);
        CRC_XorOutputData(CRC, CRC_OUTPUTDATA_XOR_ALL_1);
    }
    /*
     *  Algorithm             RefIn    RefOut   XorOut 
     *  CRC-8/AUTOSAR_2F      false    false    0xFF 
     */    
    else if (eMode == CRC_MODE_8_AUTOSAR_2F)
    {
        CRC_ReverseData(CRC, CRC_DATA_NOT_REVERSE);
        CRC_XorOutputData(CRC, CRC_OUTPUTDATA_XOR_ALL_1);  
    }
    /*
     *  Algorithm             RefIn    RefOut   XorOut 
     *  CRC-16/T10-DIF        false    false    0x0000
     */    
    else if (eMode == CRC_MODE_16_T10_DIF)
    {
        CRC_ReverseData(CRC, CRC_DATA_NOT_REVERSE);
        CRC_XorOutputData(CRC, CRC_OUTPUTDATA_XOR_ALL_0);
    }
    /*
     *  Algorithm             RefIn    RefOut   XorOut 
     *  CRC-16/CCITT          true     true     0x0000
     *  CRC-16/IBM            true     true     0x0000
     */    
    else if ((eMode == CRC_MODE_16_CCITT) || (eMode == CRC_MODE_16_IBM))
    {
        CRC_ReverseData(CRC, CRC_DATA_REVERSE);
        CRC_XorOutputData(CRC, CRC_OUTPUTDATA_XOR_ALL_0);
    }
    else
    {
        CRC_ReverseData(CRC, CRC_DATA_REVERSE);
        CRC_XorOutputData(CRC, CRC_OUTPUTDATA_XOR_ALL_0);
    }

    /*
     * Internal register will be cleared when CRCCTL.EN=0 
     * so next frame calculation is a fresh new start 
     */
    CRC_DisableContinuousFrame(CRCx);

    /* CRCSTRIN is written per word (4 bytes) */
    CRC_SetFeedFormat(CRCx, CRC_FEED_PER_WORD);
    
    /* Clear Int */
    CRC_ClearInt(CRCx, CRC_INT_ALL);
}




/****************************************************************************//**
 * @brief      When Init Value is not 0, 
 *             make input data stream and feed data in CRC,
 *             must first feed u32FrameHead to generate special Init Value
 *
 * @param[in]  CRCx         :  Select the CRC module
 * @param[in]  pu8DataStr   :  input data stream
 * @param[in]  u32DataLen   :  data length in byte
 * @param[in]  u32FrameHead :  Feed u32FrameHead first to generate special Init Value
 *                             For CRC8,  low 3 bytes of u32FrameHead is always 0x00, 
 *                             like 0xXX000000
 *                             For CRC16, low 2 bytes of u32FrameHead is always 0x00,
 *                             like 0xXXXX0000
 *                             CRC32, none byte of u32FrameHead is always 0x00,
 *                             like 0xXXXXXXXX
 * @return     CRC result
 *
 *******************************************************************************/
uint32_t CRC_CalculateWithInitValueIsNotZero(CRC_REGS *CRCx, const uint8_t *pu8DataStr, 
    uint32_t u32DataLen, uint32_t u32FrameHead)
{
    uint32_t i = 0, u32HeadCnt, u32TailCnt;
    uint32_t u32AddressTail;
    uint32_t *p;
    volatile uint32_t u32Timeout = 0xffffffffU;
    
    /* Clear internal register */
    CRC_DisableContinuousFrame(CRCx);
    CRC_Disable(CRCx);
    
    /* If u32DataLen > 3, use word word word ... byte mode to accelerate feed speed */
    if ( u32DataLen > 3 )
    {
        /* Use word word word ... byte mode to feed data */
        CRC_EnableContinuousFrame(CRCx);

        /* Set word feed mode */
        CRC_SetFeedFormat(CRCx, CRC_FEED_PER_WORD);

        /* Get address tail(0x0, 0x1, 0x2, 0x3) */ 
        u32AddressTail    = (uint32_t)pu8DataStr & 0x3;
        
        switch(u32AddressTail)
        {
            case 1:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 5) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 5) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);
            
                CRC_FeedData(CRCx, (u32FrameHead << 8));
                CRC_FeedData(CRCx, ((u32FrameHead >> 24)  |
                                      (((uint32_t)pu8DataStr[0]) << 8) |
                                      (((uint32_t)pu8DataStr[1]) << 16) |
                                      (((uint32_t)pu8DataStr[2]) << 24)));
                u32HeadCnt -= 8;
            
                /* p point to pu8DataStr[3] */
                p = (uint32_t *)&pu8DataStr[3];
                break;

            case 2:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 6) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 6) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);
            
                CRC_FeedData(CRCx, (u32FrameHead << 16));
                CRC_FeedData(CRCx, ((u32FrameHead >> 16)  |
                                      (((uint32_t)pu8DataStr[0]) << 16) |
                                      (((uint32_t)pu8DataStr[1]) << 24)));
                u32HeadCnt -= 8;
            
                /* p point to pu8DataStr[2] */
                p = (uint32_t *)&pu8DataStr[2];
                break;

            case 3:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 7) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 7) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);

                /* Feed redundant data to generate 0xffffffff in Init Value */
                CRC_FeedData(CRCx, (u32FrameHead << 24));
                CRC_FeedData(CRCx, ((u32FrameHead >> 8)  |
                                      (((uint32_t)pu8DataStr[0]) << 24)));
                u32HeadCnt -= 8;
            
                /* p point to pu8DataStr[1] */
                p = (uint32_t *)&pu8DataStr[1];
                break;

            default:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 4) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 4) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);

                /* Feed redundant data to generate 0xffffffff in Init Value */
                CRC_FeedData(CRCx, u32FrameHead);
                u32HeadCnt -= 4;
            
                /* p point to pu8DataStr[0] */
                p = (uint32_t *)&pu8DataStr[0];
                break;
        }
        
        /* Use word to feed head data */
        while(u32HeadCnt > 0)
        {
            CRC_FeedData(CRCx, *p);
            p++;
            u32HeadCnt -= 4;
        }
        
        if (u32TailCnt > 0)
        {   
            /* Enable parameter change */            
            CRC_Disable(CRCx);
            
            /* Set byte mode */
            CRC_SetFeedFormat(CRCx, CRC_FEED_PER_BYTE);
            
            /* Set byte length */
            CRC_SetStreamLen(CRCx, u32TailCnt);
         
            CRC_Enable(CRCx);
            
            /* Use byte to feed data */
            while(u32TailCnt > 0)
            {
                CRC_FeedData(CRCx, pu8DataStr[u32DataLen - u32TailCnt]);
                u32TailCnt--;
            }
        }
    }
    else
    {
        /* Feed redundant data to generate 0xffffffff in Init Value */
        CRC_SetStreamLen(CRCx, u32DataLen + 4);
        CRC_SetFeedFormat(CRCx, CRC_FEED_PER_BYTE);
        CRC_Enable(CRCx);
        CRC_FeedData(CRCx, (u32FrameHead & 0xFF));
        CRC_FeedData(CRCx, ((u32FrameHead >> 8) & 0xFF));
        CRC_FeedData(CRCx, ((u32FrameHead >> 16) & 0xFF));
        CRC_FeedData(CRCx, ((u32FrameHead >> 24) & 0xFF));
        
        /* Feed data */
        while(i < u32DataLen)
        {
            CRC_FeedData(CRCx, pu8DataStr[i]);
            i++;
        }
    }

    /* Wait for the result */
    for (u32Timeout = 0xffffffffU; u32Timeout > 0U; u32Timeout--)
    {
        if (CRC_GetIntRawFlag(CRCx, CRC_INT_OPERATION_DONE) != 0U)
        {
            break;
        }
    }

    /* Clear interrupt flag */
    CRC_ClearInt(CRCx, CRC_INT_ALL);

    /* Return the result */
    return CRC_GetResult(CRCx);
}




/****************************************************************************//**
 * @brief      When Init Value is 0, 
 *             make input data stream and feed data in CRC
 *
 * @param[in]  CRCx       :  Select the CRC module
 * @param[in]  pu8DataStr :  input data stream
 * @param[in]  u32DataLen :  data length in byte
 *
 * @return     CRC result
 *
 *******************************************************************************/
uint32_t CRC_CalculateWithInitValueIsZero(CRC_REGS *CRCx, const uint8_t *pu8DataStr, 
    uint32_t u32DataLen)
{
    uint32_t i = 0, u32HeadCnt, u32TailCnt;
    uint32_t u32AddressTail;
    uint32_t *p;
    volatile uint32_t u32Timeout = 0xffffffffU;
    
    /* Clear internal register */
    CRC_DisableContinuousFrame(CRCx);
    CRC_Disable(CRCx);
    
    /* If u32DataLen > 3, use word word word ... byte mode to accelerate feed speed */
    if ( u32DataLen > 3 )
    {
        /* Use word word word ... byte mode to feed data */
        CRC_EnableContinuousFrame(CRCx);

        /* Set word feed mode */
        CRC_SetFeedFormat(CRCx, CRC_FEED_PER_WORD);

        /* Get address tail(0x0, 0x1, 0x2, 0x3) */ 
        u32AddressTail    = (uint32_t)pu8DataStr & 0x3;
        
        switch(u32AddressTail)
        {
            case 1:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 1) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 1) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);
            
                CRC_FeedData(CRCx, (0x00000000  |
                                      (((uint32_t)pu8DataStr[0]) << 8) |
                                      (((uint32_t)pu8DataStr[1]) << 16) |
                                      (((uint32_t)pu8DataStr[2]) << 24)));
                u32HeadCnt -= 4;
            
                /* p point to pu8DataStr[3] */
                p = (uint32_t *)&pu8DataStr[3];
                break;

            case 2:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 2) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 2) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);

                CRC_FeedData(CRCx, (0x00000000  |
                                      (((uint32_t)pu8DataStr[0]) << 16) |
                                      (((uint32_t)pu8DataStr[1]) << 24)));
                u32HeadCnt -= 4;
            
                /* p point to pu8DataStr[2] */
                p = (uint32_t *)&pu8DataStr[2];
                break;

            case 3:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 3) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 3) & 0x3;
            
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);

                CRC_FeedData(CRCx, (0x00000000  |
                                      (((uint32_t)pu8DataStr[0]) << 24)));
                u32HeadCnt -= 4;
            
                /* p point to pu8DataStr[1] */
                p = (uint32_t *)&pu8DataStr[1];
                break;

            default:
                /* Obtain HeadCnt(4x) */
                u32HeadCnt = (u32DataLen + 0) & (~0x3);
            
                /* Obtain TailCnt */
                u32TailCnt = (u32DataLen + 0) & 0x3;
                   
                /* Set Head length */
                CRC_SetStreamLen(CRCx, u32HeadCnt);
            
                CRC_Enable(CRCx);

                /* p point to pu8DataStr[0] */
                p = (uint32_t *)&pu8DataStr[0];
                break;
        }
           
        /* Use word to feed head data */
        while(u32HeadCnt > 0)
        {
            CRC_FeedData(CRCx, *p);
            p++;
            u32HeadCnt -= 4;
        }
        
        if (u32TailCnt > 0)
        {     
            CRC_Disable(CRCx);
            
            /* Set byte mode */
            CRC_SetFeedFormat(CRCx, CRC_FEED_PER_BYTE);
            
            /* Set byte length */
            CRC_SetStreamLen(CRCx, u32TailCnt);
         
            CRC_Enable(CRCx);
            
            /* Use byte to feed data */
            while(u32TailCnt > 0)
            {
                CRC_FeedData(CRCx, pu8DataStr[u32DataLen - u32TailCnt]);
                u32TailCnt--;
            }
        }
    }
    else
    {       
        /* Feed redundant data to generate 0xffffffff in Init Value */
        CRC_SetStreamLen(CRCx, u32DataLen);
        CRC_SetFeedFormat(CRCx, CRC_FEED_PER_BYTE);
        CRC_Enable(CRCx);
        
        /* Feed data */
        while(i < u32DataLen)
        {
            CRC_FeedData(CRCx, pu8DataStr[i]);
            i++;
        }
    }
    /* Wait for the result */
    for (u32Timeout = 0xffffffffU; u32Timeout > 0U; u32Timeout--)
    {
        if (CRC_GetIntRawFlag(CRCx, CRC_INT_OPERATION_DONE) != 0U)
        {
            break;
        }
    }
    
    /* Clear interrupt flag */
    CRC_ClearInt(CRCx, CRC_INT_ALL);

    /* Return the result */
    return CRC_GetResult(CRCx);
}


#if defined(__IAR_SYSTEMS_ICC__)
#elif defined(__GNUC__)
    #pragma GCC pop_options
#elif defined(__CC_ARM)
    #pragma pop
#endif


/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/

