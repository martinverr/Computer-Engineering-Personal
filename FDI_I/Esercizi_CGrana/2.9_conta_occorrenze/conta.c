#include <stdlib.h>
size_t conta_occorrenze(const char *testo, const char *stringa) {
	int i = 0, match=1;
	size_t occorrenze = 0;
	if (testo == NULL || testo[0] == 0 || stringa == NULL || stringa[0] == 0)
		return 0;

	while (testo[i] != 0) {
		for (int j = 0; stringa[j] != 0 && match; j++)
			{
			if (testo[i + j] == stringa[j])
				match = 1;
			else
				match = 0;
			}
		if (match)
			occorrenze++;
		match = 1;
		i++;
	}
		return occorrenze;
}

int main(void) {
	const char testo[] = { "ciao, ciao, uno due e tre ciao" };
	const char stringa[] = { "ciao" };
	size_t res = conta_occorrenze(testo, stringa);
	return 0;
}

