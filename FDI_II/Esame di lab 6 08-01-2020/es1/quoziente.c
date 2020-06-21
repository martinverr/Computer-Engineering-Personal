#include <stdlib.h>

int Quoziente(size_t x, size_t y) {
	if (y == 0)
		return -1;
	
	if (y < x)
		return 0;

	return 1 + Quoziente(x - y, y);
}



/* Se fossero stati contemplati i negativi
if (x < 0)
	return Quoziente(-x, y);
if (y < 0)
	return Quoziente(x, -y);
*/