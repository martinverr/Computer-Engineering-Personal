#include <math.h>

unsigned int inverti(unsigned int i) {
	if (i == 0)
		return 0;

	unsigned int res = 0;
	int thisCifra = 0;
	for (int cifra = 0; cifra <10; cifra++)
	{
		res += i % 10;
		if (i < 10) {
			break;
		}
		res *= 10;
		i /= 10;
	}

	return res;
}

int main(void) {
	unsigned int num1 = inverti(724);
	unsigned int num2 = inverti(0);
	unsigned int num3 = inverti(5);
	unsigned int num4 = inverti(2700123);
	return 0;
}