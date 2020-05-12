#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int felice(unsigned int val) {
	char cifre[10] = { 0 };
	char quadrati[10] = { 0 };
	int sommaQuadrati;
	sprintf(cifre, "%d", val);

	while (1) {
		sommaQuadrati = 0;
		for (int i = 0; i < 10; i++) {
			quadrati[i] = (cifre[i] - 48)*(cifre[i] - 48);
			if (quadrati[i] == 0)
				break;
			sommaQuadrati += quadrati[i];
		}
		if (sommaQuadrati == 0 || sommaQuadrati == 4)
			return 0;
		if (sommaQuadrati == 1)
			return 1;
		sprintf(cifre, "%d", sommaQuadrati);
	}
	return 0;

}

int main(void) {
	unsigned int val = 123456789;
	int res = felice(val);
	return 0;
}