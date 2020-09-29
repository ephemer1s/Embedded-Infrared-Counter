#include <stdio.h>
#include "ir.h"

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


