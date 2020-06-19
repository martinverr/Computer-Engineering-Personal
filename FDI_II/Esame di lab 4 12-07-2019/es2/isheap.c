#include "heap_int.h"

bool IsHeap(element *h) {
	if (h == NULL || h[0] == 0)
		return true;

	int len = h[0];
	for (int i = 1; i < len / 2 + 2; i++) {
		element padre = h[i];
		
		if (Left(i) <= len && padre < h[Left(i)])
			return false;
		if (Right(i) <= len && padre < h[Right(i)])
			return false;
	}
	return true;
}
/*
int main(void) {
	element prova[] = { 4,6,1,3,4 };
	bool res = IsHeap(prova);
}
*/