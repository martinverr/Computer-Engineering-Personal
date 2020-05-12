#include "rational.h"

unsigned int mcd(int a, unsigned int b) {
	if (a == 0 || b == 0 || a==1 || b==1)
		return 1;
	if (a < 0)
		a = -a;

	int temp = 0;
	while (a != b) {
		if (a < b){
			temp = b;
			b = a;
			a = temp;
		}
		a -= b;
	}

	return a;
}

void rational_sum(struct rational *sum, const struct rational *first,
	const struct rational *second) {

	//sum
	sum->num = first->num*second->den + second->num*first->den;
	sum->den = first->den*second->den;

	//in case of 0
	if (sum->num == 0)
		sum->den = 1;

	//min fraction
	unsigned int mcdNumDen = mcd(sum->num, sum->den);
	sum->num /= mcdNumDen;
	sum->den /= mcdNumDen;
}