int ProdottoNegativi(int a, int b) {
	/*
	Param: <a> int, <b> int
	Return: a*b
	Notes: use recursion and sum
	*/
	if (a < 0)
		return -ProdottoNegativi(-a,b);
	if (b < 0)
		return -ProdottoNegativi(a, -b);
	if (a == 1)
		return b;
	if (b == 1)
		return a;
	if (a < b) {	// swap a and b to save loops if a<b
		int temp = a;
		a = b;
		b = temp;
	}
	if (a == 0 || b == 0)
		return 0;
	return a + ProdottoNegativi(a, b - 1);
	}

int main(void) {
	int res1 = ProdottoNegativi(5, 0);
	int res2 = ProdottoNegativi(5, 4);
	int res3 = ProdottoNegativi(3, 5);
	int res4 = ProdottoNegativi(1, 99);
	int res5 = ProdottoNegativi(-4, 3);
	int res6 = ProdottoNegativi(-5, -10);
	return 0;
}