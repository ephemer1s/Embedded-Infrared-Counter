#include "reg52.h"

#define TimeTH0 0xdc
#define TimeTL0 0x00 

sbit led0 = P2^0;
sbit led1 = P2^1;
sbit led2 = P2^2;
sbit ir0 = P1^0;
sbit ir1 = P1^1;

void TimeInit();
int NegedgeDet(sbit signal);
int NegedgeDet(sbit signal, sbit probe);