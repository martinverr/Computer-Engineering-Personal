#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

int cifre_dec(int n) {
	int count = 0;
	while (n != 0) {
		n /= 10;
		count++;
	}
	return count;
}

char *converti(unsigned int n) {
	int cifre = cifre_dec(n);
	char *str = malloc(cifre + 1);

	sprintf(str, "%d", n);

	return str;
}

int main(void) {
	int i = 289;
	char* str = converti(i);

	free(str);
	return 0;
}