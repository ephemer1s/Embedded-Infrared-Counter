#include "ray.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*��ʱ����ʼ��*/
void TimeInit()
{
	 TMOD = 0x01; //��ʱ��T1ģʽ
	 TH0  = TimeTH0; //��ʱ10ms
	 TL0  = TimeTL0;
	 TR0  = 1;      //������ʱ��
}