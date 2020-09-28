#include "reg52.h"
#include "lcd.h"
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

char* Lcddisplay="helloworld";

void main()
{
	LcdInit();
	while(1)
	{
		LCD_display(Lcddisplay);
	}
}