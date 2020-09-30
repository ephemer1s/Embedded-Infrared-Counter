#include <stdio.h>
#include "reg52.h"

#include "lcd.h"
#include "ir.h"
#include "x5045.h"
#include "init.h"

void main(){

	char *blank = " ", *time = "10s", *curtime1 = "5s", *num = "10";
	// char a,b;
	char *p;
	char curtime = 0;
	/* variable implemetation */
	int tmp0 = 1, tmp1 = 1;
	char cnt0 = 0, cnt1 = 0;
	int maxnum = 10;
	/* pin init */
	led0 = 1;
	led1 = 1;
	led2 = 1;
	led3 = 1;
	
	/*初始化*/
	WriteSR(0x12);      //设定看门狗超时周期为600ms，不保护
    delaynms(10);       //延时10ms

	SWR = 1;
	
	LcdInit();
	TimeInit();
	Int0Init();
	UartInit();
	
    while(1){
		/* alert trigger */
		if(cnt0 > maxnum && led2){
			led2 = 0;
		}
		if(cnt1 > maxnum && led3){
			led3 = 0;
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
				// WriteSet(0x30,0x10);
				// delaynms(10);
				// a=ReadSet(0x10);
				// send_char_com(a);    //向串口发送数据
				// WatchDog();          //看门狗复位
                ES = 0;
                send_char_com(0x30);
                ES = 1;
			}
		}
		else if(led0 && !led1){  // receive 2nd
			if(IsPosedge(ir0,tmp0)){
				led1 = 1;
				cnt1++;
				// WriteSet(0x31,0x10);
                // delaynms(10);
	    	    // b=ReadSet(0x10);
	   	        // send_char_com(b);    //向串口发送数据
                // WatchDog();          //看门狗复位
                ES = 0;
                send_char_com(0x31);
                ES = 1;
			}
		}
		tmp0 = ir0;  // save status
		tmp1 = ir1;
		
		/*液晶屏显示*/
		if (TF0 == 1){     	//判断T0是否溢出                 
		TF0 = 0;           //清零中断标志
		TH0 = TimeTH0;     //重新赋初值             
		TL0 = TimeTL0;             
		curtime++;         //当前时间加一秒
		if (curtime >= 100)   //判断T0溢出是否达到100次
		{
			p=&cnt0;
			LCD_display(p);
			cnt0=0;
			curtime=0;
			}
        }
		
		
    /*按键中断*/
    
		
  }
}