#include "libreria.h"

void swap(int * a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Inverti(int * v, int v_size) {
	if (v_size == 0)
		return;
	v_size--;
	if ( v >= v + v_size) {
		return;
	}

	swap(v, v + v_size);

	Inverti(v + 1, v_size - 1);
}

int main(void) {
	int vettore[] = { 0,1,2,3,4,5 };
	Inverti(vettore, 6);
	return 0;
}