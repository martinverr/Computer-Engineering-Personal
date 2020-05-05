int Prodotto(int a, int b) {
	/*
	Param: <a> int, <b> int
	Return: a*b
			-1 if a or b negative
	Notes: use recursion and sum
	*/
	if (a < 0)
		return -1;
	if (b < 0)
		return -1;
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
	return a + Prodotto(a, b - 1);
	}

int main(void) {
	int res1 = Prodotto(5, 0);
	int res2 = Prodotto(5, 4);
	int res3 = Prodotto(3, 5);
	int res4 = Prodotto(1, 99);
	int res5 = Prodotto(-4, 3);
	return 0;
}