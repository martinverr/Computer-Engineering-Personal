#include <stdlib.h>
// #include <assert.h>

* Monete(int *t, int size, int b) {
/*
	La funzione accetta come parametri un array t di valori che
	rappresentano i tagli di monete disponibili (ad esempio 50, 20, 10, 5, 2
	e 1 centesimo/i), la sua dimensione size, e un budget b espresso in
	centesimi. La funzione deve trovare il numero minimo intero di monete
	necessarie per formulare il budget, allocare dinamicamente un array
	delle stesse dimensioni di t dove scrivere il quantitativo di monete di
	ogni tipo necessarie per raggiungere il budget .
*/
	if (t == NULL || b <= 0)
		return NULL;

	int * res = calloc(size, sizeof(int));

	int index = 0;
	while (index < size) {
		if (b >= t[index]) {
			b -= t[index];
			res[index]++;
		}
		else
			index++;
	}
	
	// assert(b == 0); //if triggered, probably amount b cannot be resolved with greedy method
	return res;
}

/*
int main(void) {
	int banconote[] = { 50, 20, 10, 5, 2, 1 };
	
	int * res1 = Monete(banconote, 6, 126);
	int * res2 = Monete(banconote, 6, -10);
	int * res3 = Monete(banconote, 6, 0);
	int * res4 = Monete(NULL, 0, 250);
	int * res5 = Monete(banconote, 6, 500);

	return 0;
}
*/