#include "reg52.h"

sbit CS = P1^0;  //使能端
sbit SO = P1^3; //串行数据输出端
sbit SI = P1^1; //串行数据输入端
sbit SCK = P1^2; //串行时钟输入端
sbit SWR = P3^6; //写入保护端

#define WREN 0x06 //写入使能指令
#define WRDI 0x04 //写入禁止指令
#define WRSR 0x01 //写入状态寄存器指令
#define RDSR 0x05 //读取状态寄存器指令
#define WRITE 0x02 //写入存储器指令
#define READ 0x03 //读取存储器指令

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