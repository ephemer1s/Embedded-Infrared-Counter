#include "reg52.h"

sbit led0 = P2^0;
sbit led1 = P2^1;
sbit led2 = P2^2;
sbit led3 = P2^3;
// sbit led4 = P2^4;
// sbit led5 = P2^5;
// sbit led6 = P2^6;
// sbit led7 = P2^7;

sbit ir0 = P1^6;
sbit ir1 = P1^7;

int IsNegedge(bit cur, bit prev);
int IsPosedge(bit cur, bit prev);
