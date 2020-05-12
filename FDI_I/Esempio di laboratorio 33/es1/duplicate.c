#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool cifre_duplicate(unsigned long long n) {
	char cifre[10];
	sprintf(cifre, "%lld", n);
	char tocompare;
	size_t lenght = strlen(cifre);

	for (int j = 0; j < lenght; j++) {
		tocompare = cifre[j];
		for (int i = 0; i < lenght; i++) {
			if(i!=j)
				if (cifre[i] == tocompare)
					return true;
		}
	}


	return false;
}

int main(void) {
	cifre_duplicate(1231);
	cifre_duplicate(357);
	cifre_duplicate(1000);

	return 0;
}