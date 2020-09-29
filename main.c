#include <stdio.h>
#include "reg52.h"

#include "lcd.h"
#include "ir.h"
#include "x5045.h"

#define TimeTH0 0xdc
#define TimeTL0 0x00 

/*中断初始化*/
void Int0Init()
{
	EA = 1;   	//总中断
	EX0 = 1;
	IT0 = 1;  	//下降沿触发中断
}

void UartInit()
{
	EA = 1;  //总中断
	ES = 1;  //串行中断
}


void LcdInit() {
      LcdWriteCom(0x38);  // (16,2) display, (5,7) matrix, 8-bit databus
      LcdWriteCom(0x0c);  // display on | cursor blink & display off
      LcdWriteCom(0x06);  // upon write: addrp++ | cursor++ | scroll off
      LcdWriteCom(0x01);  // clear screen
      LcdWriteCom(0x80);  // define data pointer head
}

/*定时器初始化*/
void TimeInit()
{
	TMOD = 0x21;    //定时器0为方式1，定时器1为方式2
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;		// launch timer
    TH1 = 0xFD;     //波特率为9600
    TL1 = 0xFD;
    SCON = 0x50;    //10位UART，允许接收
    PCON &= 0xEF;
    TR1 = 1;        //启动定时器
}

void main(){

	char a,b;  // x com
	char *p;   // timer pointer
	/* variable implemetation */
	int tmp0 = 1, tmp1 = 1;
	char cnt0 = 0, cnt1 = 0;
	int maxnum = 10;
	/* pin init */
	led0 = 1;
	led1 = 1;
	led2 = 1;
	led3 = 1;
	
	/* module init */
	WriteSR(0x12);      //设定看门狗超时周期为600ms，不保护
  	delaynms(10);       //延时10ms
	SWR = 1;

	LcdInit();
	TimeInit();
	Int0Init();
	UartInit();
	
	/* loop */
	while(1){
		/* alert trigger */
		if(cnt0 > maxnum && led2){
			led2 = 0;
		}
		if(cnt1 > maxnum && led3){
			led3 = 0;
		}
		
		/* detect phase */
		// should be moved to imdependent function in ir.c
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
				// WriteSet(0x30,0x10);
				// delaynms(10);
				// a=ReadSet(0x10);
				send_char_com(0x30);  // serial send
				WatchDog();
			}
		}
		else if(led0 && !led1){  // receive 2nd
			if(IsPosedge(ir0,tmp0)){
				led1 = 1;
				cnt1++;
				// WriteSet(0x31,0x10);
        		// delaynms(10);
	    		// b=ReadSet(0x10);
	   	  		send_char_com(0x31);  // serial send
        		WatchDog();
			}
		}
		/* save status */
		tmp0 = ir0;
		tmp1 = ir1;
		
		/*液晶屏显示*/
		if (TF0 == 1){     	//判断T0是否溢出                 
			TF0 = 0;           //清零中断标志
			TH0 = TimeTH0;     //重新赋初值             
			TL0 = TimeTL0;             
			curtime++;         //当前时间加一秒
			if (curtime >= 100){   //判断T0溢出是否达到1000次
				p=&cnt0;
				LCD_display(p);
				cnt0=0;
				curtime=0;
			}
		}
  }
}