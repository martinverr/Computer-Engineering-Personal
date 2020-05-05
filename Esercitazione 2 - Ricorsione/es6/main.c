int Divisione(int a, int b) {
	/*
	Param: <a> int, <b> int
	Return: a/b
			-1 if a or b negative
			-1 if impossible
	Notes: use recursion and minus
	*/
	if (a < 0)
		return -1;
	if (b < 0)
		return -1;
	if (a == 0)
		return 0;
	if (b == 0)
		return -1;
	if (b == 1)
		return a;
	if (a - b < 0)	// recursive base
		return 0;
	return 1 + Divisione(a-b, b);
	}

int main(void) {
	int res1 = Divisione(5, 0);
	int res2 = Divisione(20, 4);
	int res3 = Divisione(3, 5);
	int res4 = Divisione(99, 1);
	int res5 = Divisione(-4, 3);
	return 0;
}