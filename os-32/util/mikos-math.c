#include "mikos-math.h"

int Math_Min(int x , int y) {
	return x < y ? x : y;
}

int Math_Max(int x , int y) {
	return x > y ? x : y;
}

unsigned int Math_UnsignedMin(unsigned int x , unsigned int y) {
	return x < y ? x : y;
}

unsigned int Math_UnsignedMax(unsigned int x , unsigned int y) {
	return x > y ? x : y;
}
