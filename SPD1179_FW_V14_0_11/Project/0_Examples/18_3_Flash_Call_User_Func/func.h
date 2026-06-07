#ifndef FUNC_LIB_H
#define FUNC_LIB_H

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

typedef struct PHB
{
  uint32_t voltage;
  uint16_t phase;
}PHBs;


typedef struct FunLibStruct
{
    uint32_t (*pUserFunc)(uint8_t a, uint8_t b, int vtor, int* c, int d);
    PHBs* (*pGetMotorStatus)(uint32_t *PHA, PHBs * PHB, int *PHC, uint32_t **Key, uint32_t Count);
    uint32_t (*pTestFunc)(void);
}FUNCLIB;


const FUNCLIB *ThirdFuncLib = (FUNCLIB *)(0x1000F000);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* FUNC_LIB_H */

/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
