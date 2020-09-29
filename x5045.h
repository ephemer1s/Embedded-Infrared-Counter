#include "reg52.h"

sbit CS = P1^0;  //ʹ�ܶ�
sbit SO = P1^3; //�������������
sbit SI = P1^1; //�������������
sbit SCK = P1^2; //����ʱ�������
sbit SWR = P3^6; //д�뱣����

#define WREN 0x06 //д��ʹ��ָ��
#define WRDI 0x04 //д���ָֹ��
#define WRSR 0x01 //д��״̬�Ĵ���ָ��
#define RDSR 0x05 //��ȡ״̬�Ĵ���ָ��
#define WRITE 0x02 //д��洢��ָ��
#define READ 0x03 //��ȡ�洢��ָ��

void delay1ms();
void delaynms(unsigned char n);
void WriteCurrent(unsigned char dat);
unsigned char ReadCurrent(void);
void WriteSR(unsigned char rs);
void WriteSet(unsigned char dat,unsigned char addr);
unsigned char ReadSet(unsigned char addr);
void WatchDog(void);
void InitUart(void);
void send_char_com(unsigned char ch);