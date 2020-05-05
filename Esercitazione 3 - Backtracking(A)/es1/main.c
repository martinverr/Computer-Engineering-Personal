#include "Ombrelloni.h"
// vincolo: Non devono essere uno vicino all'altro


void printSol(int n, bool * vcurr, unsigned *nsol){
	printf("%d) ", *nsol);
	for (int i = 0; i < n; i++) {
		printf("%d ", vcurr[i]);
	}
	printf("\n");
}

void Ombrelloni(int k, int n, unsigned i, bool *vcurr, unsigned cnt, unsigned *nsol) {
	if (i == n) {
		if (cnt == k){
			(*nsol)++;
			printSol(n, vcurr, nsol);
		}
		return;
	}

	if (i>0 && !vcurr[i - 1]) {
		vcurr[i] = 1;
		Ombrelloni(k, n, i + 1, vcurr, cnt + 1, nsol);
	}

	if (i == 0) {
		vcurr[i] = 1;
		Ombrelloni(k, n, i + 1, vcurr, cnt + 1, nsol);
	}
	vcurr[i] = 0;
	Ombrelloni(k, n, i+1, vcurr, cnt, nsol);
}

int main(void) {
	bool vcurr[4] = { 0,0,0,0 };
	unsigned int nsol = 0;
	
	Ombrelloni(2, 4, 0, vcurr, 0, &nsol);
	
	return 0;
}