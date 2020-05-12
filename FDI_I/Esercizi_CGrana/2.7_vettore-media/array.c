#include <stdlib.h>
#include "array.h"
double media(double *arr, size_t n) {
	double media = 0;
	for (size_t i=0; i < n; i++) {
		media += arr[i];
	}
	return media / n;
}


/*
int main(void) {
	double vett[] = { 3,6,9 };
	double res = media(vett, 3);
	return 0;
}
*/