#include "reg52.h"

typedef unsigned char uchar

sbit CS = P3^4;     //ʹ�ܶ�
sbit SO = P1^3;     //�������������
sbit SI = P3^5;     //�������������
sbit SWR = P3^6;    //д�뱣����
sbit SCK = P3^7;    //����ʱ�������

#define WREN 0x06   //д��ʹ��ָ��
#define WRDI 0x04   //д���ָֹ��
#define WRSR 0x01   //д��״̬�Ĵ���ָ��
#define RDSR 0x05   //��ȡ״̬�Ĵ���ָ��
#define WRITE 0x02  //д��洢��ָ��
#define READ 0x03   //��ȡ�洢��ָ��

void delay1ms();
void delaynms(uchar n);
void WriteCurrent(uchar dat);
uchar ReadCurrent(void);
void WriteSR(uchar rs);
void WriteSet(uchar dat,uchar addr);
uchar ReadSet(uchar addr);
void WatchDog(void);
void send_char_com(uchar ch);