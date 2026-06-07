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


typedef struct
{
    uint32_t (*pUserFunc)(uint8_t a, uint8_t b, int vtor, int* c, int d);
    PHBs* (*pGetMotorStatus)(uint32_t *PHA, PHBs * PHB, int *PHC, uint32_t **Key, uint32_t Count);
    uint32_t (*pTestFunc)(void);
}FUNCLIB;


uint32_t TestFunc(void);
uint32_t    UserFunc(uint8_t a, uint8_t b, int vtor, int* c, int d);
PHBs* GetMotorStatus(uint32_t *PHA, PHBs * PHB, int *PHC, uint32_t **Key, uint32_t Count);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* FUNC_LIB_H */

/******************* Copyright (C) 2022 Spintrol Electronic Technology (Shanghai) Co., Ltd. ***** END OF FILE ****/
