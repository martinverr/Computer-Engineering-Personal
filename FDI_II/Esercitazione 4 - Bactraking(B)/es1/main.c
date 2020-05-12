#include "torrecartoni.h"

int main(void) {

	cartone pacchi[3] = { {.p = 10,.a = 20,.l = 40} ,
					{.p = 10,.a = 10,.l = 8} ,
					{.p = 9,.a = 3,.l = 5 } };

	TorreCartoni(pacchi, 3);

	return 0;
}