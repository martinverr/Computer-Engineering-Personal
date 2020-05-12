#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>

char * concatena(const char *s1, const char *s2) {
	if (s1 == NULL || s2 == NULL)
		return NULL;
	size_t lenOut = strlen(s1) + strlen(s2) +1;
	char *out = malloc(lenOut);
	
	out = strcpy(out, s1);
	out = strcat(out, s2);


	return out;
}

int main(void) {
	char s1[] = { "ciao " };
	char s2[] = {"mondo"};
	char *s3 = concatena(s1, s2);

	return 0;
}