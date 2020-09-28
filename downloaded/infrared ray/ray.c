#include "ray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*定时器初始化*/
void TimeInit()
{
	 TMOD = 0x01; //定时器T1模式
	 TH0  = TimeTH0; //定时10ms
	 TL0  = TimeTL0;
	 TR0  = 1;      //启动定时器
}