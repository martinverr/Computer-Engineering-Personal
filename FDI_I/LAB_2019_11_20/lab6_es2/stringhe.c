#include <stdlib.h>

size_t lungh(const char *arr) {
	size_t l = 0;

	for (int i = 0; arr[i] != 0; i++)
	{
		l++;
	}
	return l;
}

char *concatena(const char *prima, const char *seconda) {
	
	size_t n1 = lungh(prima);
	size_t n2 = lungh(seconda);
	size_t n = n1 + n2 ;

	char *res = malloc((n+1) * sizeof(char));

	for (size_t i = 0; i < n1; i++)
	{
		res[i] = prima[i];
	}

	for (size_t i = n1; i < n1+n2; i++)
	{
		res[i] = seconda[i-n1];
	}

	res[n] = 0;
	return res;
}

int main(void) {
	char str1[] = { "Questa è la " };
	char str2[] = { "stringa risultante" };
	char *check;
	check = concatena(str1, str2);


	free(check);
	return 0;
}