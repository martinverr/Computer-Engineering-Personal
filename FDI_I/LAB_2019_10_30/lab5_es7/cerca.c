#include "cerca.h"

int cerca_primo(const char *s, char c)
{
	int i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return -1;
}


/*
int main(void){
	const char str[] = { "bella frate" };
	char c = 'l';

	int cerca_primo_c = cerca_primo(str, c);
	return 0;
	}
	*/