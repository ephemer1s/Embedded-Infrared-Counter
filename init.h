#include "reg52.h"

#define TimeTH0 0xdc
#define TimeTL0 0x00

void TimeInit(void);  //��ʱ����ʼ��
void Int0Init(void);  //�жϳ�ʼ��
void LcdInit(void);  //Һ������ʼ��
void UartInit(void);  //�����жϳ�ʼ��