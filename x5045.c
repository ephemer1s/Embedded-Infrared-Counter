#include "x5045.h"
#include "ir.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*��ʱ����*/
void delay1ms()
{
  unsigned char i,j; 
  for(i=0;i<10;i++)
  for(j=0;j<33;j++);   
 }
void delaynms(unsigned char n){
  unsigned char i;
  for(i=0;i<n;i++)
	delay1ms();
}

/*д��EEPROM*/
void WriteCurrent(unsigned char dat)
{
  unsigned char i;
  SCK=0;                 //ֹͣʱ��
  for(i = 0; i < 8; i++)  //ѭ��8λ
  {
    SI=(bit)(dat&0x80);   //��λ��ȡ���λ
    SCK=0;
    SCK=1;             //����������
    dat<<=1;  //����һλ����Ϊ������������λ
  }
}

/*��EEPROM��������*/
unsigned char ReadCurrent(void)
{
   unsigned char i;
   unsigned char x=0x00;
   SCK=1;
   for(i = 0; i < 8; i++)
   {
     SCK=1;               //�½��ض���
     SCK=0;
     x<<=1;  //����һλ����Ϊ�ȶ����������λ
    x|=(unsigned char)SO;  //��λ��������ֵ��x
   }
   return(x);
 }

/*д״̬�Ĵ���*/
void WriteSR(unsigned char rs)
{
  CS=0;
  WriteCurrent(WREN);  //����д��
  CS=1;
  CS=0; //��������ʹ�ܶ�
  WriteCurrent(WRSR);
  WriteCurrent(rs);   //д��״̬�Ĵ���ָ��
  CS=1;
}

/*д���ݲ���*/
void WriteSet(unsigned char dat,unsigned char addr)
{
  SCK=0;
  CS=0;
  WriteCurrent(WREN);
  CS=1;
  CS=0;
  WriteCurrent(WRITE);  //д��洢��
  WriteCurrent(addr);   //д��ָ����ַ
  WriteCurrent(dat);    //д������
  CS=1;
  SCK=0;
}

/*�����ݲ���*/
unsigned char ReadSet(unsigned char addr)
{
 unsigned char dat;
  SCK=0;
  CS=0;
  WriteCurrent(READ);
  WriteCurrent(addr);  //ָ���������ڵĵ�ַ
  dat=ReadCurrent();
  CS=1;
  SCK=0;
  return dat;
 }

/*���Ź���λ*/
void WatchDog(void)
{
  CS=1;
  CS=0;
  CS=1;
}

/*��ʱ����ʼ��*/
void TimeInit(void)
{
	TMOD = 0x21;    //��ʱ��0Ϊ��ʽ1����ʱ��1Ϊ��ʽ2
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;			// launch timer
  TH1 = 0xFD; //������Ϊ9600
  TL1 = 0xFD;
  SCON = 0x50; //10λUART����������
  PCON &= 0xEF;
  TR1 = 1; //������ʱ��
}

/*�򴮿ڷ����ַ�*/
void send_char_com(unsigned char ch)
{
  SBUF = ch;
  while(!TI);
  TI = 0;
}

/*�жϳ�ʼ��*/
void UartInit()
{
	EA = 1;  //���ж�
	ES = 1;  //�����ж�
}

/*����������ַ�����Ƭ������ͨ����Ƭ�����͸�x5045*/
void receive_char_com() interrupt 4
{
  int i;
	char num, a;
	
  if(RI == 1)     //�յ�����
  {
    num = SBUF;
    RI = 0;       //�����־λ
  }
  if(TI == 1)  //�������
  {TI = 0;}
	WriteSet(num,0x13);
	a = ReadSet(0x13);
	send_char_com(a);

}