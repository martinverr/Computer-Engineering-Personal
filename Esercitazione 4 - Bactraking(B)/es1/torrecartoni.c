#include "torrecartoni.h"

//fx ausiliarie 
bool notIn(int k, int * currsol, int n) {
	for (int i = 0; i < n; i++) {
		if (k == currsol[i])
			return false;
	}
	return true;
}

int geth(cartone *c, int  * bestsol, int n) {
	int h = 0;
	for (int i = 0; i < n; i++)
		if (bestsol[i] != -1)
			h += c[bestsol[i]].a;

	return h;
}

void printsol(cartone *c, int  * bestsol, int n) {
	// stampa soluzione
	int h = 0;
	for (int i = n-1; i > 0; i--) {
		if (bestsol[i] != -1)
			printf("\t%d\n", bestsol[i]);
	}
	printf("Altezza: %d\n", geth(c, bestsol, n));
}


void backtraking(cartone *c, int n, int * currsol, unsigned int currWeight, int i, int  * bestsol) {
	if (i < 0) {
		if (geth(c, currsol, n) > geth(c, bestsol, n))
			bestsol = memmove(bestsol, currsol, sizeof(int)*n);
		return;
	}

	for (int k = 0; k < n; k++) {	// puo' essere ottimizzato: se in un ciclo non troviamo un k
									// possibile(con un flag) allora passiamo dal passo i a 0 direttamente
		if (notIn(k, currsol, n) && c[k].l >= currWeight) {
			currsol[i] = k;
			backtraking(c, n, currsol, currWeight + c[k].p, i - 1, bestsol);
		}
	}
	currsol[i] = -1;
	backtraking(c, n, currsol, currWeight, i - 1, bestsol);
}

// fx soluione
void TorreCartoni(cartone *c, int n) {
	int * currsol = malloc(sizeof(int) * n);
	int * bestsol = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) { // bestsol start as [-1,-1,-1,...,-1]
		bestsol[i] = -1;
	}
	backtraking(c, n, currsol, 0, n-1, bestsol);

	free(currsol);
	printsol(c, bestsol, n);
	free(bestsol);
}