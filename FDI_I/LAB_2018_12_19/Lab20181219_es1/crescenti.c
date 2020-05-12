#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
bool crescente(unsigned int x) {
	char stringx[10];
	sprintf(stringx, "%d", x);

	if (strlen(stringx)==1)
		return 1;

	for (int i = 1; stringx[i] != 0; i++) {
		if (stringx[i] < stringx[i - 1])
			return 0;
	}
	return 1;
}

int main(void) {
	bool res = crescente(7);
	res = crescente(128);
	res = crescente(51);

	return 0;
}