#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printsol(char ** nomi, int k, int *vcurr) {
	printf("{");
	for (int i = 0; i < k; i++) {
		printf("%s", nomi[vcurr[i]]);
		if (i == k - 1)
			continue;
		printf(",");
	}
	printf("}\n");
}

bool verifica(char ** nomi, int *vcurr, int i) {
	char currIniziale = nomi[vcurr[i]][0];
	for (int j = 0; j < i; j++)
		if (nomi[vcurr[j]][0] == currIniziale || nomi[vcurr[j]][0] == currIniziale - 1 ||
			nomi[vcurr[j]][0] == currIniziale + 1)
			return false;
	return true;
}

void backtracking(char ** nomi, int k, int * nsol, int * vcurr, int i, int n) {
	if (i == k) {
		printsol(nomi, k, vcurr);
		(*nsol)++;
		return;
	}

	for (int j = 0; j < n; j++) {
		vcurr[i] = j;
		if (verifica(nomi, vcurr, i))
			backtracking(nomi, k, nsol, vcurr, i + 1, n);
	}
}

int Sottogruppi(const char *filename, int k) {
	FILE * f = fopen(filename, "r");
	if (f == NULL)
		return -1;
	if (k <= 0)
		return -1;

	int n = 1;
	char ** nomi = malloc(sizeof(char *) * n);
	for (int i = 0; 1; i++) {
		nomi = realloc(nomi, sizeof(char *) * n);
		nomi[i] = malloc(20);
		if (fscanf(f, "%s", nomi[i]) == EOF)
			break;
		n++;
	}
	n--;
	nomi = realloc(nomi, sizeof(char *) * n);
	if (k > n)
		return -1;

	// preparazione e chiamata backtracking
	int nsol = 0;
	int * vcurr = malloc(k * sizeof(int));
	backtracking(nomi, k, &nsol, vcurr, 0, n);

	//free
	for (int i = 0; i < n; i++) //nomi[i] = realloc(nomi[i], strlen(nomi[i]));
		free(nomi[i]);
	free(nomi);
	free(vcurr);
	fclose(f);
	return nsol;
}