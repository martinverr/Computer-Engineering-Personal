/*
*	commenti etc
*
*/

#include <stdlib.h>

size_t conta_spazi(const char *s) {
	size_t spazi = 0;
	
	for(int i = 0; s[i]!=0 ; i++)
		if (s[i] == ' ') {
			spazi++;
	}

	return spazi;
}

int main(void) {
	char str[] = { "prova stringa in cui contare gli spazi" };
	size_t check = conta_spazi(str);
	return 0;

}