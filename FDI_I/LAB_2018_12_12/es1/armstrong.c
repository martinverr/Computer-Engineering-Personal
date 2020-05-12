#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

bool armstrong(size_t a) {
	char cifre[10];
	size_t sommaQuadrati = 0;
	int k = sprintf(cifre, "%d", a);
	for (int i = 0; cifre[i] != 0; i++) {
		sommaQuadrati += (size_t)pow((cifre[i] - 48), k);
	}

	if (sommaQuadrati == a)
		return true;
	return false;
}

int main(void) {
	size_t n = 153;
	armstrong(n);

	return 0;
}