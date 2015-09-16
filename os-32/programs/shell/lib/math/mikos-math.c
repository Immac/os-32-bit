#include "mikos-math.h"

int MikosLib_Math_Min(int x , int y) {
	return x < y ? x : y;
}

int MikosLib_Math_Max(int x , int y) {
	return x > y ? x : y;
}

unsigned int MikosLib_Math_UnsignedMin(unsigned int x , unsigned int y) {
	return x < y ? x : y;
}

unsigned int MikosLib_Math_UnsignedMax(unsigned int x , unsigned int y) {
	return x > y ? x : y;
}
