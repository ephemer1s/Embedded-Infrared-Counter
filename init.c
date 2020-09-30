#include "init.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*��ʱ����ʼ��*/
void TimeInit(void)
{
	TMOD = 0x21;    //��ʱ��0Ϊ��ʽ1����ʱ��1Ϊ��ʽ2
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;			// launch timer
    TH1 = 0xFD; //������Ϊ9600
    TL1 = 0xFD;
    SCON = 0x50; //10λUART���������
    PCON &= 0xEF;
    TR1 = 1; //������ʱ��
}

/*�ⲿ�жϳ�ʼ��*/
void Int0Init(void)
{
    EA = 1;  //���ж�
    EX0 = 1;
    IT0 = 1;  //�½��ش����ж�
}

/*Һ������ʼ��*/
void LcdInit(void) {
      LcdWriteCom(0x38);  // (16,2) display, (5,7) matrix, 8-bit databus
      LcdWriteCom(0x0c);  // display on | cursor blink & display off
      LcdWriteCom(0x06);  // upon write: addrp++ | cursor++ | scroll off
      LcdWriteCom(0x01);  // clear screen
      LcdWriteCom(0x80);  // define data pointer head
}

/*�����жϳ�ʼ��*/
void UartInit(void)
{
	EA = 1;  //���ж�
	ES = 1;  //�����ж�
}
