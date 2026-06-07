#ifndef COMMONFUN_FRAMEDATAPRTL_H_
#define COMMONFUN_FRAMEDATAPRTL_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdint.h>

typedef enum
{
    EnumReturnTrue = 0x55,
    EnumReturnFalse = 0xAA,
    EnumReturnNull = 0x00
}EnumReturn;

typedef struct
{
  uint8_t* pRawDataRcvBuf;
  uint16_t RawDataRcvBufferSize;
  uint8_t RcvState ;
  uint8_t GotFrame ;
  uint16_t DataCount ;
}ST_FFFE_STRU;

EnumReturn FRAME_DataPrtlInit(ST_FFFE_STRU *pFFFEStatStru , uint8_t* p_p8FFFEBUffer,uint16_t t_u16BufferSize);

uint16_t FRAME_DataPrtlPack(const uint8_t p_p8SrcBuffer[], uint16_t t_u16SrcLen, uint8_t p_p8DestBuffer[]);
uint16_t FRAME_DataPrtlUnpack(ST_FFFE_STRU *pFFFEStatStru,uint8_t RcvChar, uint8_t pRawDataRcv[],uint16_t t_u16RcvMaxSize);

#ifdef __cplusplus
}
#endif


#endif /*COMMONFUN_FRAMEDATAPRTL_H_ */
