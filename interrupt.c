#include "lcd.h"
#include "ir.h"
#include "x5045.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/* clear LCD screen */
void intkey1() interrupt 0
{
	if(key1 == 0)
	{
		LcdWriteCom(0x01);
	}
}

/* switch display */
//not workable
void intkey2() interrupt 0
{
	if(key2 == 0)
	{
		//display1=&cnt0;
		//LCD_display(display1);
	}
}
