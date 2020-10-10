#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reg52.h"

#include "lcd.h"
#include "ir.h"
#include "x5045.h"
#include "init.h"

/* variable implemetation */
int cnt0, cnt1;
int maxnum, maxtime;
int curtime;
int key_phase;
char strbuf[32];
sbit buzzer = P1^5;

void LCD_refresh()
{
    char* str = strbuf;
    // reset led
    led4 = 1;
    led5 = 1;
    led6 = 1;
    led7 = 1;
    switch(key_phase){
        case 0: { // display current enter / exit
            led4 = 0;
            sprintf(str, "Total Entry:%3d Total Exit :%3d", cnt0, cnt1);
            break;
        }
        case 1: { // display current time / max time
            led5 = 0;
            sprintf(str, "Time Used  :%3d Max: %8d", curtime, maxtime);
            break;
        }
        case 2: { // display current enter number / valve
            led6 = 0;
            sprintf(str, "Total Entry:%3d Max: %8d", cnt0, maxnum);
            break;
        }
        case 3: { // display current exit number / valve
            led7 = 0;
            sprintf(str, "Total Exit :%3d Max: %8d", cnt1, maxnum);
            break;
        }
        default:break;
        }
    LCD_display(str);
}


void main(){
    bit tmp0 = 1, tmp1 = 1;
	char tcnt = 0, a = 0, b = 0;
    int i;

	/* pin init */
	led0 = 1;
	led1 = 1;
	led2 = 1;
	led3 = 1;
	buzzer = 1;

	/* module init */
	WriteSR(0x12);      //设定看门狗超时周期为600ms，不保护
    delaynms(10);       //延时10ms

	SWR = 1;
	
	LcdInit();
	TimeInit();
	Int0Init();
	UartInit();

    /* data init */
    delaynms(10);
    a = ReadSet(0x10);
    delaynms(10);
    b = ReadSet(0x11);
    maxtime = (int)a;
    maxnum = (int)b;
    curtime = 0;
    cnt0 = 0;
    cnt1 = 0;
    key_phase = 0;

    LCD_refresh();
    for(i = 0; i < 32; i++){
        strbuf[i] = 0;
    }
    
    while(1){
        delaynms(10);
        a = ReadSet(0x10);
        delaynms(10);
        b = ReadSet(0x11);
        maxtime = (int)a;
        maxnum = (int)b;
        if(curtime < maxtime){
            /* alert trigger */
            if(cnt0 > maxnum && led2){
                led2 = 0;
                buzzer = 0;
            }
            if(cnt1 > maxnum && led3){
                led2 = 0;
                buzzer = 0;
            }
            
            /* detect phase */
            if(led0 && led1){  // receive 1st sensor
                if(IsNegedge(ir0,tmp0)){
                    led0 = 0;
                }
                else if(IsNegedge(ir1,tmp1)){
                    led1 = 0;
                }
            }
            else if(!led0 && led1){  // receive 2nd
                if(IsPosedge(ir1,tmp1)){
                    led0 = 1;
                    cnt0++;
                    send_char_com(0x30);
                }
            }
            else if(led0 && !led1){  // receive 2nd
                if(IsPosedge(ir0,tmp0)){
                    led1 = 1;
                    cnt1++;
                    send_char_com(0x31);
                }
            }
            tmp0 = ir0;  // save status
            tmp1 = ir1;
        }
            
		/* LCD disp */
		if (TF0 == 1){          // if timer0 overflow             
            TF0 = 0;                // clear timer int
            TH0 = TimeTH0;          // reinit             
            TL0 = TimeTL0;          //   
            tcnt++;                 // tcnt 100
            if (tcnt/100)        // timer reach 1000ms
            {
                tcnt%=100;
                if(curtime < maxtime)
                    curtime++;
                led3 = ~(led3);     // led-timer blink
                LCD_refresh();
			}
        }
    }
}
/*按键中断*/
void key_int0() interrupt 0
{
    int i = 0;
    char* str = strbuf;
    EX0 = 0;
    EX1 = 0;
	if(key1 == 0)
	{
        /* clear screen and buffer */
		LcdWriteCom(0x01);	// clear screen
        // while(i < strlen(str))
        //     strbuf[i] = 0;	// clear buffer
        memset(strbuf, 0, sizeof(char) * 32);
        /* clear data */
        cnt0 = 0;
        cnt1 = 0;
        delaynms(10);
        key_phase = 0;
	}
    EX0 = 1;
    EX1 = 1;
}

void key_int2() interrupt 2
{
    char* str = strbuf;
    int i;
	EX0 = 0;
    EX1 = 0;
	if(key2 == 0)
	{
        // while(i <= 32)
        //     strbuf[i] = 0;	// clear buffer
        memset(strbuf, 0, sizeof(char) * 32);
        LcdWriteCom(0x01);
        delaynms(10);
        LCD_refresh();
        /* save operation */
        key_phase++;
		key_phase %= 4;
	}
    EX0 = 1;
    EX1 = 1;
}