#include <stdlib.h>

size_t lungh(const char *str)
{
	size_t i = 0;
	char end = 0;
	while (!end)
	{

		if (str[i] == 0)
			end = 1;
		i++;
	}
	return  i-1;
}


int main(void) {
	char s[] = "Ecco la stringa di prova";
	size_t lenght_s = lungh(s);
	return 0;
}