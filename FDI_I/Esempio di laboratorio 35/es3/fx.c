#include "stringhe.h"

char *zfill(const char *str, size_t n) {
	if (str == NULL)
		return NULL;
	size_t lenstring = strlen(str);
	if (lenstring >= n) {
		char *res = malloc(strlen(str) + 1);
		strcpy(res, str);
		res[strlen(str)] = 0;
		return res;
	}

	char *res = malloc(n+1);

	for (size_t i = 0; i < n-lenstring; i++) {
		res[i] = '0';
	}
	res[n-lenstring] = 0;
	strcat(res, str);

	return res;
}

int main(void) {
	
	char *res1 = zfill("ciao", 10);
	char *res2 = zfill("ciao", 1);

	return 0;
}