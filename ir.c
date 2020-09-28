#include <stdio.h>
#include "reg52.h"
#include "ir.h"

void TimeInit() {
	TMOD = 0x01;		// set mode T1
	TH0  = TimeTH0;	// set interval 10ms
	TL0  = TimeTL0;
	TR0  = 1;			// launch timer
}

int IsNegedge(bit cur, bit prev) {
	int res = 0;
	if(prev && !cur) res = 1;
	return res;
}

int IsPosedge(bit cur, bit prev) {
	int res = 0;
	if(!prev && cur) res = 1;
	return res;
}

int FlowOverclockAlert(int flow) {
	return 0;
}

