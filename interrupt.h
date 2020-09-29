#include "reg52.h"

sbit key1 = P3^2;
sbit key2 = P3^3;

void intkey1();
void intkey2();