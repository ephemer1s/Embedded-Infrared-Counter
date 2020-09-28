#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*初始化函数*/
void LcdInit()

{
      LcdWriteCom(0x38);  //设置16*2显示，5*7点阵，8位数据线
      LcdWriteCom(0x0c);  //显示开，光标不闪烁，光标不显示
      LcdWriteCom(0x06);  //写入数据后，地址指针加1，光标加1，且屏幕不移动
      LcdWriteCom(0x01);  //清屏
      LcdWriteCom(0x80);  //设置数据指针起点
}

/*延时函数*/
void Delay(uchar LCD_delay)
{ 
	uchar lcd_del;
	while(LCD_delay--)
	{
		lcd_del=100;
		while(lcd_del--);
	}
}

/*写命令函数*/
void LcdWriteCom(uchar com)
{
      LCDE = 0;    //使能清零
      LCDRS = 0;   //选择发送命令
      LCDRW = 0;
      LCD1602_DB = com;   //写入命令
      Delay(100); 
      LCDE = 1;   //下降沿，使指令有效
      Delay(300);
      LCDE = 0;
}

/*写数据函数*/
void LcdWriteData(uchar dat)

{

      LCDE = 0;    //使能清零
      LCDRS = 1;   //选择发送数据
      LCDRW = 0;
      LCD1602_DB = dat;   //写入数据
      Delay(100);
      LCDE = 1;   //下降沿，使指令有效
      Delay(300);
      LCDE = 0;

}

/*显示函数*/
void LCD_display(char* Lcddisplay)
{
	int i;
	uchar* p; 
	p = Lcddisplay;
	
	if(strlen(Lcddisplay)<16)  //显示一行
	{
		LcdWriteCom(0x80);  //数据指针起点
		for(i = 0;i<strlen(Lcddisplay);i++)
		{
			LcdWriteData(*(p++));
		}
	}
	else  //显示两行
	{
		LcdWriteCom(0x80);
		for(i = 0;i<16;i++)
		{
			LcdWriteData(*(p++));
		}		
		LcdWriteCom(0xc0);  //第二行起点
		for(i = 16;i<strlen(Lcddisplay);i++)
		{
			LcdWriteData(*(p++));
		}
	}
}

