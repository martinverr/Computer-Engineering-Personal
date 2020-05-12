#include "stringhe.h"

char *title(const char *str) {
	if (str == NULL)
		return NULL;
	char *res = malloc(strlen(str) + 1);

	//copy
	for (size_t i = 0; i < strlen(str) + 1; i++) {
		res[i] = str[i];
	}

	//if first letter of a word not in capital turn in capital letter
	if (isalpha(res[0]))
		res[0] = toupper(res[0]);

	for (size_t i = 1; i < strlen(str); i++) {
		if (
			isalpha(res[i])		&&		
			(!isalpha(res[i-1]))
			) 
		{
			res[i]=toupper(res[i]);
		}
	}

	return res;
}

int main(void) {
	char *prova = title(" prova Con piu' parole");


	return 0;
}