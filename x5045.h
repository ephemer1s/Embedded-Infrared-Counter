#include "reg52.h"

typedef unsigned char uchar

sbit CS = P3^4;     //使能端
sbit SO = P1^3;     //串行数据输出端
sbit SI = P3^5;     //串行数据输入端
sbit SWR = P3^6;    //写入保护端
sbit SCK = P3^7;    //串行时钟输入端

#define WREN 0x06   //写入使能指令
#define WRDI 0x04   //写入禁止指令
#define WRSR 0x01   //写入状态寄存器指令
#define RDSR 0x05   //读取状态寄存器指令
#define WRITE 0x02  //写入存储器指令
#define READ 0x03   //读取存储器指令

void delay1ms();
void delaynms(uchar n);
void WriteCurrent(uchar dat);
uchar ReadCurrent(void);
void WriteSR(uchar rs);
void WriteSet(uchar dat,uchar addr);
uchar ReadSet(uchar addr);
void WatchDog(void);
void send_char_com(uchar ch);