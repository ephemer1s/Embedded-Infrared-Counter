#include "lcd.h"
#include "ir.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void LcdInit() {
      LcdWriteCom(0x38);  // (16,2) display, (5,7) matrix, 8-bit databus
      LcdWriteCom(0x0c);  // display on | cursor blink & display off
      LcdWriteCom(0x06);  // upon write: addrp++ | cursor++ | scroll off
      LcdWriteCom(0x01);  // clear screen
      LcdWriteCom(0x80);  // define data pointer head
}


void Delay(uchar LCD_delay) { 
	uchar lcd_del;
	while(LCD_delay--) {
		lcd_del=100;
		while(lcd_del--);
	}
}


void LcdWriteCom(uchar com) {
	/* write command */
      LCDE = 0;    // energy clc
      LCDRS = 0;   // select send command
      LCDRW = 0;
      LCD1602_DB = com;   // write command
      Delay(100); 
      LCDE = 1;    // negedge, which make command available
      Delay(300);
      LCDE = 0;
}


void LcdWriteData(uchar dat) {
	/* write data */ 
      LCDE = 0;    // energy clc
      LCDRS = 1;   // select send data
      LCDRW = 0;
      LCD1602_DB = dat;   // write data
      Delay(100);
      LCDE = 1;   // negedge
      Delay(300);
      LCDE = 0;
}


void LCD_display(char* Lcddisplay)
{
	int i;
	uchar* p; 
	p = Lcddisplay;
	
	if(strlen(Lcddisplay)<16) { // display on 1 line
		LcdWriteCom(0x80); // data pointer head
		for(i = 0;i<strlen(Lcddisplay);i++) {
			LcdWriteData(*(p++));
		}
	}
	else { // display on 2 lines
		LcdWriteCom(0x80);
		for(i = 0;i<16;i++) {
			LcdWriteData(*(p++));
		}		
		LcdWriteCom(0xc0);  // 2nd line pointer head
		for(i = 16;i<strlen(Lcddisplay);i++) {
			LcdWriteData(*(p++));
		}
	}
}

void Press(char *time,char *curtime,char *num)
{
	char *display;
	char *blank=" ";
	strcpy(display, time);
	strcpy(display, blank);
	strcpy(display, curtime);
	strcpy(display, blank);
	strcpy(display, num);
	LCD_display(display);
}

/*中断初始化*/
void Int0Init()
{
	EA = 1;  //总中断
  EX0 = 1;
  IT0 = 1;  //下降沿触发中断
}

void Key1() interrupt 0
{
	 if(key1 == 0)
	 {
	 	LcdWriteCom(0x01);
	 }
}

void Key2() interrupt 0
{
	 if(key2 == 0)
	 {
	 	//display1=&cnt0;
		//LCD_display(display1);
	 }
}
