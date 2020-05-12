
#include "rational.h"
int main(void) {

	struct rational res=
	{
		0,1,
	};

	struct rational add2 =
	{
		1,2,
	};

	struct rational add1=
	{
		3,5,
	};

	rational_sum(&res, &add1, &add2);

	return 0;
}