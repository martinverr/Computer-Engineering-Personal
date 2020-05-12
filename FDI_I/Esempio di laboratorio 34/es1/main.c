#include "funzione.h"

int main(void) {

	char str1[] = { "11/12/2000" };
	char str2[] = { "11/12/20" };
	char str3[] = { "11-12-2000" };

	bool res1 = is_date(str1);
	bool res2 = is_date(str2);
	bool res3 = is_date(str3);

	return 0;
}