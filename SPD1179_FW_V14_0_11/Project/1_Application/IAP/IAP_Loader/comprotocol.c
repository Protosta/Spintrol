#include "comprotocol.h"
#include <string.h>


#define SPACE_BETWEEN_FF_MAX_COUNT (0xFCu)
/* FFFE Unicode Escape Sequence State */
#define FIND_FIRST_FF     0x00U
#define FIND_SECOND_FF    0x01U
#define NO_FF_TIME        0x02U
#define WAIT_FF_POS       0x03U
#define UN_TRANSFER_FAIL  0x04U

/* FFFE Data Reception State */
#define COM_WAIT_START_FF 0x00U
#define COM_WAIT_START_FE 0x01U
#define COM_WAIT_STOP_FF  0x02U
#define COM_WAIT_STOP_FD  0x03U

/* Local Static Function Declaration Area */
uint16_t FFInBufferTransfer(const uint8_t p_p8SrcBuffer[], uint8_t p_p8DestBuffer[],uint16_t p_u16SrcLen);
uint16_t UnTransferFFInBuffer(const uint8_t p_p8SrcBuffer[],uint8_t p_p8DestBuffer[],uint16_t t_u16SrcLen);


/*********************************************************************************************************
 *  @fn             FFInBufferTransfer
 *  @brief          FF Escape Function
 *  @detail         The function is called to escape FF data in the data source, 
 *                  recording the distance between two FFs in the destination array.
 *  @param[in]      p_p8SrcBuffer_pU8      Source data stream to be escaped
 *  @param[in]      p_u16SrcLen_U16        Length of the source data stream to be escaped
 *  @param[out]     p_p8DestBuffer_pU8     Destination data stream after escaping
 *  @return         Length of the escaped data stream
 *********************************************************************************************************/
uint16_t FFInBufferTransfer(const uint8_t p_p8SrcBuffer[], uint8_t p_p8DestBuffer[],uint16_t p_u16SrcLen)
{

	uint16_t t_u16SrcIndex = 0U;
	uint16_t t_u16DestIndex = 0U;
	uint16_t t_u16Index1 = 0U;
	uint16_t t_u16Index2 = 0U;
	uint16_t t_u16I = 0U;
	uint16_t t_u16SpaceBetweenFF = 0U;
	uint8_t t_u8IsHaveFirstFF = 0U;


	for(t_u16SrcIndex=0U;t_u16SrcIndex<p_u16SrcLen;t_u16SrcIndex++)
	{
		if(1U == t_u8IsHaveFirstFF)
		{
			if(0xFFU == p_p8SrcBuffer[t_u16SrcIndex])
			{
				t_u16Index2 = t_u16SrcIndex;
				p_p8DestBuffer[t_u16DestIndex]=(uint8_t)(t_u16Index2-t_u16Index1);
				t_u16DestIndex++;
				for(t_u16I=t_u16Index1+1U;t_u16I<t_u16Index2;t_u16I++)
				{
					p_p8DestBuffer[t_u16DestIndex]=p_p8SrcBuffer[t_u16I];
					t_u16DestIndex++;
				}

				t_u8IsHaveFirstFF=0U;
				t_u16Index1=0U;
				t_u16Index2=0U;
				t_u16SpaceBetweenFF=0U;
			}
			else
			{
				t_u16SpaceBetweenFF++;
				if(SPACE_BETWEEN_FF_MAX_COUNT == t_u16SpaceBetweenFF)
				{
					t_u8IsHaveFirstFF=0U;
					t_u16SpaceBetweenFF=0U;
					p_p8DestBuffer[t_u16DestIndex]=0U;
					t_u16DestIndex++;
					for(t_u16I=t_u16Index1+1U;t_u16I<=t_u16SrcIndex;t_u16I++)
					{
						p_p8DestBuffer[t_u16DestIndex]=p_p8SrcBuffer[t_u16I];
						t_u16DestIndex++;
					}
				}
				else
				{
				}
			}
		}
		else
		{
			p_p8DestBuffer[t_u16DestIndex]=p_p8SrcBuffer[t_u16SrcIndex];
			t_u16DestIndex++;

			if(0xFFU == p_p8SrcBuffer[t_u16SrcIndex])
			{

				t_u8IsHaveFirstFF=1U;
				t_u16Index1=t_u16SrcIndex;
				t_u16SpaceBetweenFF=0U;
			}
			else
			{
			}
		}
	}

	if(1U == t_u8IsHaveFirstFF)
	{
		p_p8DestBuffer[t_u16DestIndex] = 0U;
		t_u16DestIndex++;

		for(t_u16I=t_u16Index1+1U;t_u16I<p_u16SrcLen;t_u16I++)
		{
			p_p8DestBuffer[t_u16DestIndex]=p_p8SrcBuffer[t_u16I];
			t_u16DestIndex++;
		}
	}
	else
	{
	}

	return t_u16DestIndex;
}

/*********************************************************************************************************
 *  @fn             UnTransferFFInBuffer
 *  @brief          Unescape 0xFF Escaped Content
 *  @detail         The function is called to unescape FF-escaped data in the data source, 
 *                   outputting the unescaped array and returning the length of the unescaped data.
 *  @param[in]      p_p8SrcBuffer_pU8      Source data stream to be unescaped
 *  @param[in]      p_u16SrcLen_U16        Length of the source data stream to be unescaped
 *  @param[out]     p_p8DestBuffer_pU8     Destination data stream after unescaping
 *  @return         Length of the unescaped data stream
 *********************************************************************************************************/
uint16_t UnTransferFFInBuffer(const uint8_t p_p8SrcBuffer[],uint8_t p_p8DestBuffer[],uint16_t t_u16SrcLen)
{

	uint16_t t_u16SrcIndex=0U;
	uint16_t t_u16DestIndex=0U;
	uint16_t t_u16NoFFCount=0U;  
	uint16_t t_u16NextFFIndex=0U;
	uint8_t t_u8Temp=0U;
	uint8_t t_u8NowState=FIND_FIRST_FF;


	for(t_u16SrcIndex=0U;t_u16SrcIndex<t_u16SrcLen;t_u16SrcIndex++)
	{

		t_u8Temp=p_p8SrcBuffer[t_u16SrcIndex];
		switch(t_u8NowState)
		{

		case FIND_FIRST_FF:
		{

			if(0xFFU == t_u8Temp)
			{

				p_p8DestBuffer[t_u16DestIndex]=t_u8Temp;
				t_u16DestIndex++;

				t_u8NowState = FIND_SECOND_FF;
			}
			else
			{

				p_p8DestBuffer[t_u16DestIndex]=t_u8Temp;
				t_u16DestIndex++;
			}

			break;
		}

		case FIND_SECOND_FF:
		{
			if( (0xFDU==t_u8Temp) || (0xFEU==t_u8Temp) || (0xFFU==t_u8Temp) )
			{
				t_u8NowState = UN_TRANSFER_FAIL;
			}
			else
			{

				if(0U == t_u8Temp)
				{
					t_u8NowState = NO_FF_TIME;
				}
				else
				{
					if(1U == t_u8Temp)
					{
						p_p8DestBuffer[t_u16DestIndex]=0xffU;
						t_u16DestIndex++;
						t_u8NowState = FIND_FIRST_FF;
					}
					else
					{
						t_u16NextFFIndex=(t_u16SrcIndex+t_u8Temp)-1U;
						t_u8NowState = WAIT_FF_POS;
					}
				}
			}
			break;
		}
		case NO_FF_TIME:
		{
			t_u16NoFFCount++;
			if( (0xFFU==t_u8Temp) && (t_u16NoFFCount<=252U) )
			{
				t_u8NowState = UN_TRANSFER_FAIL;
			}
			else
			{
				p_p8DestBuffer[t_u16DestIndex]=t_u8Temp;
				t_u16DestIndex++;

				if(SPACE_BETWEEN_FF_MAX_COUNT == t_u16NoFFCount)
				{
					t_u16NoFFCount=0U;
					t_u8NowState = FIND_FIRST_FF;
				}
				else
				{
				}
			}
			break;
		}
		case WAIT_FF_POS:
		{
			if(0xFFU == t_u8Temp)
			{
				t_u8NowState = UN_TRANSFER_FAIL;
			}
			else
			{
				p_p8DestBuffer[t_u16DestIndex]=t_u8Temp;
				t_u16DestIndex++;
				if(t_u16SrcIndex == t_u16NextFFIndex)
				{
					p_p8DestBuffer[t_u16DestIndex]=0xffU;
					t_u16DestIndex++;
					t_u8NowState = FIND_FIRST_FF;
				}
				else
				{
				}
			}
			break;
		}
		default:
		{
			t_u8NowState = UN_TRANSFER_FAIL;
			break;
		}
		}
		if(t_u8NowState==UN_TRANSFER_FAIL)
		{
			t_u16DestIndex=0U;
			break;
		}
		else
		{
		}
	}

	if((t_u8NowState == FIND_SECOND_FF)||(t_u8NowState ==WAIT_FF_POS))
	{
		t_u16DestIndex = 0U;
	}
	else
	{

	}

	return t_u16DestIndex;
}

/*********************************************************************************************************
 *  @fn             FrameDataPrtlINIT
 *  @brief          Initialize packet protocol management data structure
 *  @detail         The function is called to initialize the packet protocol management data structure with invalid values.
 *  @param[in]      pFFFEStatStru_pp        The address of the packet protocol management structure
 *  @param[in]      p_p8FFFEBUffer_pp       Array of packet protocol buffers
 *  @param[in]      t_u16BufferSize_U16     Size of the unescaped data stream
 *  @return         EnumReturnTrue         Initialization successful
 *  @return         EnumReturnFalse        Initialization failed
 *********************************************************************************************************/
EnumReturn FRAME_DataPrtlInit(ST_FFFE_STRU *pFFFEStatStru , uint8_t* p_p8FFFEBUffer,uint16_t t_u16BufferSize)
{

	EnumReturn t_enumRet = EnumReturnFalse;
	if((pFFFEStatStru != NULL)&&(p_p8FFFEBUffer != NULL))
	{
		memset((void*)pFFFEStatStru , (int)0U , (uint64_t)sizeof(ST_FFFE_STRU));

		pFFFEStatStru->RawDataRcvBufferSize=t_u16BufferSize;
		pFFFEStatStru->RcvState=COM_WAIT_START_FF;
		pFFFEStatStru->pRawDataRcvBuf=p_p8FFFEBUffer;
		memset((void*)pFFFEStatStru->pRawDataRcvBuf,(int)0U,(uint64_t)t_u16BufferSize);
		t_enumRet = EnumReturnTrue;
	}
	else
	{

		t_enumRet = EnumReturnFalse;
	}

	return t_enumRet;
}

/*********************************************************************************************************
 *  @fn             FrameDataPrtlUNPACK_1
 *  @brief          Receive data to be unescaped character by character, 
 *                  obtain a complete FFFE frame (excluding FFFE and FFFD)
 *  @detail         The function is called to receive data to be unescaped character by character, 
 *                  obtaining a complete FFFE frame (excluding FFFE and FFFD).
 *  @param[in]      RcvChar_U8             The current received character
 *  @param[in]      pFFFEStatStru_pp        The packet protocol management structure
 *  @param[in]      t_u16RcvMaxSize_U16     The maximum length of the received data
 *  @param[out]     pRawDataRcv_pp         Pointer to the data reception buffer
 *  @return         GreaterThan 0: Indicates the length of the received complete frame, 
 *   and the received complete frame is copied to the reception buffer; 0: No complete frame data received;
 *********************************************************************************************************/
uint16_t FRAME_DataPrtlUnpack(ST_FFFE_STRU *pFFFEStatStru,uint8_t RcvChar, uint8_t pRawDataRcv[],uint16_t t_u16RcvMaxSize)
{

	uint16_t ReturnVal = 0U;

	switch(pFFFEStatStru->RcvState)
	{
	case COM_WAIT_START_FF:

		if(0xFFU != RcvChar)
		{

		}
		else
		{
			pFFFEStatStru->RcvState = COM_WAIT_START_FE;
		}
		break;
	case COM_WAIT_START_FE:

		if(0xFEU != RcvChar)
		{
			pFFFEStatStru->RcvState = COM_WAIT_START_FF;
		}
		else
		{
			pFFFEStatStru->DataCount = 0U;
			pFFFEStatStru->GotFrame = 0U;
			pFFFEStatStru->RcvState = COM_WAIT_STOP_FF;
		}
		break;
	case COM_WAIT_STOP_FF:

		if(0xFFU == RcvChar)
		{
			pFFFEStatStru->RcvState = COM_WAIT_STOP_FD;
		}
		else
		{

			if(pFFFEStatStru->DataCount >= pFFFEStatStru->RawDataRcvBufferSize)
			{
				pFFFEStatStru->DataCount = 0U;
				pFFFEStatStru->GotFrame = 0U;
				pFFFEStatStru->RcvState = COM_WAIT_START_FF;
			}
			else
			{
				pFFFEStatStru->pRawDataRcvBuf[pFFFEStatStru->DataCount] = RcvChar;
				pFFFEStatStru->DataCount++;

			}
		}
		break;
	case COM_WAIT_STOP_FD:

		switch(RcvChar)
		{
		case 0xFFU:
			pFFFEStatStru->DataCount = 0U;
			pFFFEStatStru->GotFrame = 0U;
			pFFFEStatStru->RcvState = COM_WAIT_START_FF;
			break;
		case 0xFEU:
			pFFFEStatStru->DataCount = 0U;
			pFFFEStatStru->GotFrame = 0U;
			pFFFEStatStru->RcvState = COM_WAIT_STOP_FF;
			break;
		case 0xFDU:
			pFFFEStatStru->GotFrame = 1U;
			pFFFEStatStru->RcvState = COM_WAIT_START_FF;
			break;
		default:

			if(pFFFEStatStru->DataCount >= (pFFFEStatStru->RawDataRcvBufferSize-1U))
			{
				pFFFEStatStru->DataCount = 0U;
				pFFFEStatStru->GotFrame = 0U;
				pFFFEStatStru->RcvState = COM_WAIT_START_FF;
			}
			else
			{
				pFFFEStatStru->pRawDataRcvBuf[pFFFEStatStru->DataCount] = 0xFFU;
				pFFFEStatStru->DataCount++;
				pFFFEStatStru->pRawDataRcvBuf[pFFFEStatStru->DataCount] = RcvChar;
				pFFFEStatStru->DataCount++;
				pFFFEStatStru->RcvState = COM_WAIT_STOP_FF;
			}
			break;
		}
		break;
		default:
			break;
	}

	if(1U == pFFFEStatStru->GotFrame)
	{
		if(pFFFEStatStru->DataCount <= t_u16RcvMaxSize)
		{
			ReturnVal = UnTransferFFInBuffer(pFFFEStatStru->pRawDataRcvBuf,pRawDataRcv,pFFFEStatStru->DataCount);
			pFFFEStatStru->DataCount = 0U;
			pFFFEStatStru->GotFrame = 0U;
		}
		else
		{
			ReturnVal = 0U;
			pFFFEStatStru->DataCount = 0U;
			pFFFEStatStru->GotFrame = 0U;
		}
	}
	else
	{
	}

	return ReturnVal;
}


/*********************************************************************************************************
 *  @fn             FrameDataPrtlPACK_1
 *  @brief          Data Packing Protocol
 *  @detail         The function is called to pack the target data into a protocol 
 *                  with 0xFFFE 0xFFFD + escape of 0XFF in the data content.
 *  @param[in]      p_p8SrcBuffer_pU8      Source data to be packed
 *  @param[in]      t_u16SrcLen_U16        Length of the source data to be packed
 *  @param[out]     p_p8DestBuffer_pU8     Packed data
 *  @return         Length of the packed data
 *********************************************************************************************************/
uint16_t FRAME_DataPrtlPack(const uint8_t p_p8SrcBuffer[], uint16_t t_u16SrcLen, uint8_t p_p8DestBuffer[])
{

	uint16_t t_u16Index=0U;


	p_p8DestBuffer[t_u16Index]=0xFFU;
	t_u16Index++;
	p_p8DestBuffer[t_u16Index]=0xFEU;
	t_u16Index++;

	t_u16Index += FFInBufferTransfer(p_p8SrcBuffer, p_p8DestBuffer+t_u16Index,t_u16SrcLen);

	p_p8DestBuffer[t_u16Index]=0xFFU;
	t_u16Index++;
	p_p8DestBuffer[t_u16Index]=0xFDU;
	t_u16Index++;

	return t_u16Index;
}

