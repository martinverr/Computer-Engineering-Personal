#include "stringhe.h"

char *parola_piu_lunga(const char *sz) {
	int this_lenght = 0, max_lenght=0, pos_longest_word=0;

	for (int i = 0; sz[i] != 0; i++) {
		if (isblank(sz[i])) {
			if (this_lenght > max_lenght)
			{
				max_lenght = this_lenght;
				pos_longest_word=i-max_lenght;
			}
			this_lenght = 0;
		}
		else
		{
			this_lenght++;
		}
	}

	//last check(the last word has not been checked because of the terminator)
	if (this_lenght > max_lenght)
	{
		max_lenght = this_lenght;
		pos_longest_word = strlen(sz) - max_lenght;
	}

	//alloc result string
	char *res = malloc(max_lenght + 1);
	strncpy(res, sz + pos_longest_word, max_lenght);
	res[max_lenght] = 0;

	return res;
}