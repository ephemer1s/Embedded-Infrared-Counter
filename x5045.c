#include "x5045.h"
// #include "ir.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 延时函数 */
void delay1ms()
{
    uchar i,j; 
    for(i=0;i<10;i++)
    for(j=0;j<33;j++);   
}
void delaynms(uchar n)
{
    uchar i;
    for(i=0;i<n;i++)
        delay1ms();
}

/* 写入EEPROM */
void WriteCurrent(uchar dat)
{
    uchar i;
    SCK=0;                 //停止时钟
    for(i = 0; i < 8; i++)  //循环8位
    {
        SI=(bit)(dat&0x80);   //按位与取最高位
        SCK=0;
        SCK=1;             //上升沿锁存
        dat<<=1;  //左移一位，因为先锁存的是最高位
    }
}

/* 从EEPROM读出数据 */
uchar ReadCurrent(void)
{
    uchar i;
    uchar x=0x00;
    SCK=1;
    for(i = 0; i < 8; i++)
    {
        SCK=1;               //下降沿读出
        SCK=0;
        x<<=1;  //左移一位，因为先读出的是最高位
        x|=(uchar)SO;  //按位或运算后幅值给x
    }
    return(x);
}

/* 写状态寄存器 */
void WriteSR(uchar rs)
{
    CS=0;
    WriteCurrent(WREN);  //允许写入
    CS=1;
    CS=0; //重新拉低使能端
    WriteCurrent(WRSR);
    WriteCurrent(rs);   //写入状态寄存器指令
    CS=1;
}

/* 写数据操作 */
void WriteSet(uchar dat,uchar addr)
{
    SCK=0;
    CS=0;
    WriteCurrent(WREN);
    CS=1;
    CS=0;
    WriteCurrent(WRITE);  //写入存储器
    WriteCurrent(addr);   //写入指定地址
    WriteCurrent(dat);    //写入数据
    CS=1;
    SCK=0;
}

/* 读数据操作 */
uchar ReadSet(uchar addr)
{
    uchar dat;
    SCK=0;
    CS=0;
    WriteCurrent(READ);
    WriteCurrent(addr);  //指定数据所在的地址
    dat=ReadCurrent();
    CS=1;
    SCK=0;
    return dat;
}

/* 看门狗复位 */
void WatchDog(void)
{
    CS=1;
    CS=0;
    CS=1;
}

/* 向串口发送字符 */
void send_char_com(uchar ch)
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
