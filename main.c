#include <stdio.h>
#include "reg52.h"

#include "lcd.h"
#include "ir.h"

void run(){
	/* variable implemetation */
	int tmp0 = 1, tmp1 = 1;
	int cnt0 = 0, cnt1 = 0;
	int maxnum = 10;
	/* pin init */
	led0 = 1;
	led1 = 1;
	led2 = 1;
	led3 = 1;

	/* loop */
	while (1){
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
			}
		}
		else if(led0 && !led1){  // receive 2nd
			if(IsPosedge(ir0,tmp0)){
				led1 = 1;
				cnt1++;
			}
		}
		tmp0 = ir0;  // save status
		tmp1 = ir1;
	}
}

void main(){
		run();
}