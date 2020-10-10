#include "reg52.h"

#define LCD1602_DB P0
sbit LCDRS=P1^0;
sbit LCDRW=P1^1;
sbit LCDE=P1^2;

sbit key1 = P3^2;
sbit key2 = P3^3;

void LcdInit(void);  //“∫æß∆¡≥ı ºªØ
void LcdWriteCom(unsigned char com);
void LcdWriteData(unsigned char dat);
void LCD_display(char* Lcddisplay);
void Delay(unsigned char LCD_delay);
// void Press(char *time,char *curtime,char *num);