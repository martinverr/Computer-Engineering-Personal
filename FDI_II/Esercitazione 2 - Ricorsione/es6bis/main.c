int DivisioneNegativi(int a, int b) {
	/*
	Param: <a> int, <b> int
	Return: a/b
			-1 if impossible
	Notes: use recursion and minus
	*/
	if (a == 0)
		return 0;
	if (b == 0)
		return -1;
	if (b == 1)
		return a;
	
	if (a < 0)
		return -DivisioneNegativi(-a, b);
	if (b < 0)
		return -DivisioneNegativi(a, -b);

	if (a - b < 0)	// recursive base
		return 0;
	return 1 + DivisioneNegativi(a-b, b);
	}

int main(void) {
	int res1 = DivisioneNegativi(5, 0);
	int res2 = DivisioneNegativi(20, 4);
	int res3 = DivisioneNegativi(3, 5);
	int res4 = DivisioneNegativi(99, 1);
	int res5 = DivisioneNegativi(-4, 3);
	int res6 = DivisioneNegativi(-30, -9);
	return 0;
}