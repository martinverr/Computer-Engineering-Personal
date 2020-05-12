#include "complessi.h"

void prodotto_complesso(struct complesso *comp1, const struct complesso *comp2) {
	/*
	*	(a+ib)(c+id)=(ac-bd)+i(ad+bc)
	*/

	double a = comp1->re, b = comp1->im;
	double c = comp2->re, d = comp2->im;

	struct complesso temp = { comp1->re, comp1->im };
	comp1->re = a * c - b * d;
	comp1->im = a * d + b * c;
}

int main(void){
	struct complesso a = { 1,1 };
	struct complesso b = { -1,0 };
	prodotto_complesso(&a, &b);
	}