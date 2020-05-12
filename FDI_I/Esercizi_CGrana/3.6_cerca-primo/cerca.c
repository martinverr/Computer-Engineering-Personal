#include <string.h>

char *cerca_primo(char*s, const char*list){
	if (strlen(s) == 0 || strlen(list) == 0)
		return NULL;

	char *res = &s[strlen(s)];	//pointer to the zero of s string

	char *match = NULL;
	char found = 0;
	for (size_t i = 0; i < strlen(list); i++) {
		match = strchr(s, list[i]);
		if (match != NULL && match < res) {
			res = match;
			found = 1;
			}
				
	}

	if (found)
		return res;
	else
		return NULL;
}

int main(void) {
	char stringa[] = {"aereo"};
	char cerca[] = { "dyr" };
	char *risultato = cerca_primo(stringa, cerca);

	char stringa2[] = { "Stringa più complessa" };
	char cerca2[] = { "at" };
	char *risultato2 = cerca_primo(stringa2, cerca2);

	return 0;
}