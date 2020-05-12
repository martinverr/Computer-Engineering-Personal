#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

size_t conta_parole(const char *s) {
	size_t words = 0;
	int count = 0;

	while (s[count] != 0) {
		if (isspace(s[count]) && isalnum(s[count+1]))
		{
			words++;
		}
		count++;
	}

	return words;
}

int main(void) {
	char stringa1[] = { "  Questa e' una stringa lunga 45 caratteri.  " };
	size_t res1 = conta_parole(stringa1);
}