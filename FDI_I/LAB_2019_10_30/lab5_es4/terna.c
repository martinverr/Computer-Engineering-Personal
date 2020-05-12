#include <stdbool.h>


bool is_terna_pitagorica(unsigned int a, unsigned int b, unsigned int c) {
	a *= a;
	b *= b;
	c *= c;
	if (a == b + c)
		return 1;
	if (b == a + c)
		return 1;
	if (c == a + b)
		return 1;
	return 0;
}


int main(void) {
	int a = 4, b = 5, c = 3;
	int ternapit=is_terna_pitagorica(a, b, c);
	return 0;
}