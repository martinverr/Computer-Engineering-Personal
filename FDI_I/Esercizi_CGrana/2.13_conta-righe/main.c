#include "righe.h"
int main(void) {
	FILE *f = fopen("prova1.txt", "r");
	if (f == NULL)
		return -1;
	int res = conta_righe(f);

	return 0;
}