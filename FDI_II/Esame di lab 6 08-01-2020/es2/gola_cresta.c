#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printsol(int * currSol, int n) {
	printf("(");
	for (int i = 0; i < n; i++) {
		printf("%d", currSol[i]);
		if (i != n - 1)
			printf(", ");
	}
	printf("), ");
}

bool verifica1(int n, int * currSol) {
	bool passed = true;
	for (int i = 2; i < n; i++) {
		if (//not condizione 1
			!(
				currSol[i - 1] > currSol[i] &&
				currSol[i - 1] > currSol[i - 2])
			)
			passed = false;
	}
	return passed;
}

bool verifica2(int n, int * currSol) {
	bool passed = true;
	for (int i = 2; i < n; i++) {
		if (//not condizione 2
			!(
				currSol[i - 1] < currSol[i] &&
				currSol[i - 1] < currSol[i - 2])
			)
			passed = false;
	}
	return passed;
}

void backtracking(size_t n, int * currSol, int step) {
	if (step == n) {
		if (verifica1(n, currSol) || verifica2(n, currSol))
			printsol(currSol, n);
		return;
	}

	for (int i = 0; i < 3; i++) {
			currSol[step] = i;
			backtracking(n, currSol, step + 1);
	}
}

void GolaCresta(size_t n) {
	int * sol = malloc(n * sizeof(int));

	backtracking(n, sol, 0);

	free(sol);
}

/*
int main(void) {
	GolaCresta(3);
	return 0;
}
*/
