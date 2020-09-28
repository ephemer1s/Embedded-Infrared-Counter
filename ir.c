#include "ir.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void TimeInit() {
	TMOD = 0x01;		// set mode T1
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;			// launch timer
}

int Negedge(sbit signal) {
	if(!flag) {
		if(!signal) {
			flag = 1;
		}
	}
	else {
		if(signal){
			flag = 0;
			return 1;
		}
	}
}

int Negedge(sbit signal, sbit probe) {
	if(!flag) {
		if(!signal) {
			flag = 1;
			probe = ~(probe);
		}
	}
	else {
		if(signal){
			flag = 0;
			probe = ~(probe);
			return 1;
		}
	}
}