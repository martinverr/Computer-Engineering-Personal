#include "matematica.h"

double semifattoriale(char n) {
	double res = 1;
	if (n == 0 || n == 1)
		return res;

	int count = n;
	while (count > 1)
	{
		res *= count;
		count -= 2;
	}

	return res;
}

int main(void) {
	double semifatt9 = semifattoriale(9);
	double semifatt8 = semifattoriale(8);

	return 0;
}