unsigned long long Fattoriale(int n) {
	/*
	Param: <n>
	Return: n!
	Notes: use recursion
	*/
	if (n == 0)	// recurs base
		return 1;
	return n * Fattoriale(n-1);
	}

int main(void) {
	unsigned long long res1 = Fattoriale(30);
	unsigned long long res2 = Fattoriale(1);
	unsigned long long res3 = Fattoriale(0);
	unsigned long long res4 = Fattoriale(5);
	unsigned long long res5 = Fattoriale(3);
	return 0;
}