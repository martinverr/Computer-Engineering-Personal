#include <stdio.h>
#include <stdlib.h>

void printSol(char * sol, int n) {
	printf("{ ");
	printf("%s", sol);
	printf(" }, ");
}

void backtrackingResolution(int n, int curr, char * sol) {
	if (curr == n) {
		sol[n] = 0;
		printSol(sol, n);
		return;
	}

	for (int j = 'a'; j <= 'a'+n-1; j++) {
		sol[curr] = j;
		backtrackingResolution(n, curr + 1, sol);
	}
}

void BacktrackStr(int n) {
	if (n <= 0 || n > 26)
		return;

	char * str = malloc(n + 1);
	backtrackingResolution(n, 0, str);
	free(str);
}

int main(void) {
	BacktrackStr(2);
	return 0;
}