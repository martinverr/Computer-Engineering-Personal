#include "array.h"

int main(void) {
	double v1[3] = { 0,3,6 };
	double v2[3] = { 1,0,4 };
	double *sommav1v2 = array_somma(v1, v2, 3);
	return 0;
}