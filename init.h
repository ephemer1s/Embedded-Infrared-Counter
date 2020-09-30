#include "reg52.h"

#define TimeTH0 0xdc
#define TimeTL0 0x00

void TimeInit(void);  //定时器初始化
void Int0Init(void);  //中断初始化
void LcdInit(void);  //液晶屏初始化
void UartInit(void);  //串行中断初始化