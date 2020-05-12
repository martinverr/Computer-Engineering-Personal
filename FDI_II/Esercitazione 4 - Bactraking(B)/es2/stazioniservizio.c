#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 0.05 l / km
// 30 l
// criterio: minore spesa

// strutture dati ausiliare
struct piano {
	int * stops;
	double spesa;
};
//fx ausiliare
void printSol(int n, struct piano * sol) {
	for (int i = 0; i < n; i++) {
		if (sol->stops[i])
			printf("%d ", i);
	}
	printf("\nSpesa totale: %f", sol->spesa);
}

void resolveStazioniServizio(double m, int n, double * d, double * p, int i, struct piano * currsol, struct piano * bestsol, double oil, double cost) {
	if (i == n) {
		// check if valid
		if (bestsol->stops[0] == -1 || bestsol->spesa >= cost) {
			bestsol->spesa = cost;
			bestsol->stops = memcpy(bestsol->stops, currsol->stops, sizeof(int) * n);
			// bestsol->stops = memmove(bestsol->stops, currsol->stops, sizeof(double) * n);
		}
		return;
	}

	oil -= d[i] * 0.05;	// update oil available (sub the oil used for d[i] km * 0.05 l/km)
	if (oil < 0)
		return;

	// resolve next step i+1 filling in this stop
	currsol->stops[i] = 1;
	resolveStazioniServizio(m, n, d, p, i + 1, currsol, bestsol, 30, cost + p[i] * (30 - oil));

	// resolve next step i+1 NOT filling in this stop
	currsol->stops[i] = 0;
	resolveStazioniServizio(m, n, d, p, i + 1, currsol, bestsol, oil, cost);
}

// fx soluione
void StazioniServizio(double m, int n, double * d, double * p) {
	struct piano * bestsol = malloc(sizeof(struct piano));
	bestsol->stops = malloc(n * sizeof(int));
	bestsol->stops[0] = -1; // flag che ci consente di capire se avremo trovato una soluzione

	struct piano * currsol = malloc(sizeof(struct piano));
	currsol->stops = malloc(n * sizeof(int));

	resolveStazioniServizio(m, n, d, p, 0, currsol, bestsol, 30, 0);

	if (bestsol->stops[0] == -1)
		printf("Non esistono soluzioni");
	else
		printSol(n, bestsol);

	free(bestsol->stops);
	free(currsol->stops);
	free(bestsol);
	free(currsol);

}

int main(void) {

	double d[5] = { 260, 284, 308, 332, 356 };
	double p[5] = { 35, 35, 33, 29, 33 };

	StazioniServizio(1540, 5, d, p);

	return 0;
}