#include <stdio.h>
#include "reg52.h"
#include "lcd.h"
#include "ir.h"

void run(){
	/* variable implemetation */
	int flag = 0, cnt = 0;

	/* pin init */
	led0 = 1;
	led1 = 1;

	/* loop */
	while (1){     
		if(cnt > 10){
			led1 = 0;
		}
		if(!flag){
			if(!ray1){
				flag = 1;
				led0 = ~(led0);
			}
		}
		else{
			if(ray1){
				flag = 0;
				led0 = ~(led0);
				cnt++;
			}
		}
	}
}

void main(){
		run();
}