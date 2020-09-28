#include "reg52.h"

#define TimeTH0 0xdc    //宏定义定时器初值
#define TimeTL0 0x00 
sbit led0=P2^0;
sbit led1=P2^1;
sbit led2=P2^2;
sbit ray=P1^2;

void TimeInit();