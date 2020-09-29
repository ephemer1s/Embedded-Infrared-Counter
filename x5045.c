#include "x5045.h"
// #include "ir.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ��ʱ���� */
void delay1ms()
{
    unsigned char i,j; 
    for(i=0;i<10;i++)
    for(j=0;j<33;j++);   
}
void delaynms(unsigned char n)
{
    unsigned char i;
    for(i=0;i<n;i++)
        delay1ms();
}

/* д��EEPROM */
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

/* ��EEPROM�������� */
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

/* д״̬�Ĵ��� */
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

/* д���ݲ��� */
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

/* �����ݲ��� */
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

/* ���Ź���λ */
void WatchDog(void)
{
    CS=1;
    CS=0;
    CS=1;
}

/* �򴮿ڷ����ַ� */
void send_char_com(unsigned char ch)
{
    SBUF = ch;
    while(!TI);
    TI = 0;
}


/* serial communicate : PC =====> C51 =====>X5045 */
void receive_char_com() interrupt 4
{
    char serial_res;
    if(RI == 1)  // receive from serial
    {
        serial_res = SBUF;
        RI = 0;  // clear signal bit
    }
    if(TI == 1)TI = 0;  // receive complete

    WriteSet(serial_res, 0x10);  // save to addr on eeprom
    send_char_com(ReadSet(0x10));
}
