#include "prezzototale.h"

void printsol(const articolo * articles, size_t size, int * sol){
	for (size_t i = 0; i < size; i++)
		if(sol[i])
			printf("%s, ", articles[i].nome);
	printf("\n");
}

void backtracking(const articolo * articles, size_t size, int maxSum, int currSum, int currStep, int * currArticles) {
	if (currStep == size) {
		if(currSum == maxSum)
			printsol(articles, size, currArticles);
		return;
	}

	if (currSum + articles[currStep].prezzo <= maxSum) {
		currArticles[currStep] = 1;
		backtracking(articles, size, maxSum, currSum + articles[currStep].prezzo, currStep + 1, currArticles);
	}
	
	currArticles[currStep] = 0;
	backtracking(articles, size, maxSum, currSum, currStep + 1, currArticles);
}

void TrovaArticoli(const articolo* a, size_t a_size, int sum) {
	if (a == NULL)
		return;

	int * solcurr = malloc(sizeof(int) * a_size);
	backtracking(a, a_size, sum, 0, 0, solcurr);

	free(solcurr);
}

/*
int main(void) {

	int sum = 50;
	articolo articoli[] = { {"Monopoli", 20}, {"Carcassone", 30}, {"Perudo", 20} };
	TrovaArticoli(articoli, 3, 50);

	return 0;
}
*/