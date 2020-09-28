#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*��ʼ������*/
void LcdInit()

{
      LcdWriteCom(0x38);  //����16*2��ʾ��5*7����8λ������
      LcdWriteCom(0x0c);  //��ʾ������겻��˸����겻��ʾ
      LcdWriteCom(0x06);  //д�����ݺ󣬵�ַָ���1������1������Ļ���ƶ�
      LcdWriteCom(0x01);  //����
      LcdWriteCom(0x80);  //��������ָ�����
}

/*��ʱ����*/
void Delay(uchar LCD_delay)
{ 
	uchar lcd_del;
	while(LCD_delay--)
	{
		lcd_del=100;
		while(lcd_del--);
	}
}

/*д�����*/
void LcdWriteCom(uchar com)
{
      LCDE = 0;    //ʹ������
      LCDRS = 0;   //ѡ��������
      LCDRW = 0;
      LCD1602_DB = com;   //д������
      Delay(100); 
      LCDE = 1;   //�½��أ�ʹָ����Ч
      Delay(300);
      LCDE = 0;
}

/*д���ݺ���*/
void LcdWriteData(uchar dat)

{

      LCDE = 0;    //ʹ������
      LCDRS = 1;   //ѡ��������
      LCDRW = 0;
      LCD1602_DB = dat;   //д������
      Delay(100);
      LCDE = 1;   //�½��أ�ʹָ����Ч
      Delay(300);
      LCDE = 0;

}

/*��ʾ����*/
void LCD_display(char* Lcddisplay)
{
	int i;
	uchar* p; 
	p = Lcddisplay;
	
	if(strlen(Lcddisplay)<16)  //��ʾһ��
	{
		LcdWriteCom(0x80);  //����ָ�����
		for(i = 0;i<strlen(Lcddisplay);i++)
		{
			LcdWriteData(*(p++));
		}
	}
	else  //��ʾ����
	{
		LcdWriteCom(0x80);
		for(i = 0;i<16;i++)
		{
			LcdWriteData(*(p++));
		}		
		LcdWriteCom(0xc0);  //�ڶ������
		for(i = 16;i<strlen(Lcddisplay);i++)
		{
			LcdWriteData(*(p++));
		}
	}
}

