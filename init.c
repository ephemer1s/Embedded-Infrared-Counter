#include "init.h"
// #include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*定时器初始化*/
void TimeInit(void)
{
	TMOD = 0x21;    //定时器0为方式1，定时器1为方式2
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;			// launch timer
    TH1 = 0xFD; //波特率为9600
    TL1 = 0xFD;
    SCON = 0x50; //10位UART，允许接收
    PCON &= 0xEF;
    TR1 = 1; //启动定时器
}

/*外部中断初始化*/
void Int0Init(void)
{
    EA = 1;  //总中断
    EX0 = 1;
    IT0 = 1;  //下降沿触发中断
}

/*串行中断初始化*/
void UartInit(void)
{
	EA = 1;  //总中断
	ES = 1;  //串行中断
}
