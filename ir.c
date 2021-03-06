#include <stdio.h>
#include "reg52.h"
#include "ir.h"

// get negative edge
int IsNegedge(bit cur, bit prev) {
	int res = 0;
	if(prev && !cur) res = 1;
	return res;
}

// get positive edge
int IsPosedge(bit cur, bit prev) {
	int res = 0;
	if(!prev && cur) res = 1;
	return res;
}

