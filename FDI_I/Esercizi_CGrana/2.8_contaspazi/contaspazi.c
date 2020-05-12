#include <stdlib.h>

size_t conta_spazi(const char *arr) {
	int i = 0, spazi=0;
	while (arr[i] != 0) {
		if(arr[i]==' ')
			spazi++;
		i++;
	}
	return spazi;
}


/*
int main(void) {
	char vett[] = {"Qua ci sono 5 spazi giusto?"};
	size_t res = conta_spazi(vett, 3);
	return 0;
}
*/