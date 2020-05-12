#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>

char *trim(const char *str) {
	if (str == NULL)
		return NULL;
	int begin = 0, end=0;
	int lenght = strlen(str);


	for (int i = 0; str[i] == ' '; i++) {
		begin++;
	}

	for (int i = lenght - 1; str[i] == ' '; i--) {
		end++;
	}
	if (begin == end && begin == lenght) {
		char *result = malloc(1);
		result[0] = 0;
		return result;
	}
	int finalLenght = lenght - begin - end;
	char *result = malloc(finalLenght + 1);

	for (int i = 0; i < finalLenght; i++) {
		result[i] = str[i+begin];
	}
	result[finalLenght] = 0;

	return result;
}

int main(void) {
	char s1[] = { "senza spazi" };
	char s2[] = { " prima" };
	char s3[] = { "dopo " };
	char s4[] = { " a b " };
	char s5[] = { "   " };

	char *s1b = trim(s1);
	char *s2b = trim(s2);
	char *s3b = trim(s3);
	char *s4b = trim(s4);
	char *s5b = trim(s5);
	char *s6b = trim(NULL);
	return 0;
}