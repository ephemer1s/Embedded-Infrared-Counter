#include <stdio.h>
#include "reg52.h"

#include "lcd.h"
#include "ir.h"
#include "x5045.h"

#define TimeTH0 0xdc
#define TimeTL0 0x00 

/*�жϳ�ʼ��*/
void Int0Init()
{
	EA = 1;   	//���ж�
	EX0 = 1;
	IT0 = 1;  	//�½��ش����ж�
}

void UartInit()
{
	EA = 1;  //���ж�
	ES = 1;  //�����ж�
}


void LcdInit() {
      LcdWriteCom(0x38);  // (16,2) display, (5,7) matrix, 8-bit databus
      LcdWriteCom(0x0c);  // display on | cursor blink & display off
      LcdWriteCom(0x06);  // upon write: addrp++ | cursor++ | scroll off
      LcdWriteCom(0x01);  // clear screen
      LcdWriteCom(0x80);  // define data pointer head
}

/*��ʱ����ʼ��*/
void TimeInit()
{
	TMOD = 0x21;    //��ʱ��0Ϊ��ʽ1����ʱ��1Ϊ��ʽ2
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;		// launch timer
    TH1 = 0xFD;     //������Ϊ9600
    TL1 = 0xFD;
    SCON = 0x50;    //10λUART���������
    PCON &= 0xEF;
    TR1 = 1;        //������ʱ��
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
	WriteSR(0x12);      //�趨���Ź���ʱ����Ϊ600ms��������
  	delaynms(10);       //��ʱ10ms
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
		
		/*Һ������ʾ*/
		if (TF0 == 1){     	//�ж�T0�Ƿ����                 
			TF0 = 0;           //�����жϱ�־
			TH0 = TimeTH0;     //���¸���ֵ             
			TL0 = TimeTL0;             
			curtime++;         //��ǰʱ���һ��
			if (curtime >= 100){   //�ж�T0����Ƿ�ﵽ1000��
				p=&cnt0;
				LCD_display(p);
				cnt0=0;
				curtime=0;
			}
		}
  }
}