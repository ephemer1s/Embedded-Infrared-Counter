#include "reg52.h"

typedef unsigned char uchar;

#define LCD1602_DB P0
sbit LCDRS=P1^0;
sbit LCDRW=P1^1;
sbit LCDE=P1^2;

void LcdWriteCom(uchar com);
void LcdWriteData(uchar dat);
void LCD_display(char* Lcddisplay);
void Delay(uchar LCD_delay);
void Press(char *time,char *curtime,char *num);

