#include "terna.h"

bool is_terna_pitagorica(unsigned int v[3]) {
	int a = v[0], b = v[1], c = v[2];

	return (a*a == b * b + c * c || b * b == a * a + c * c || c * c == a * a + b * b);
}

int main(void) {
	int v[3] = { 3,4,5 };
	int w[3] = { 1,4,5 };

	bool resv = is_terna_pitagorica(v);
	bool resw = is_terna_pitagorica(w);

	return 0;
}