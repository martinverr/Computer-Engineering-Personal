double binomiale_double(int n, int k) {
	if (k == 0)
		return 1;
	return (double)n / k * binomiale_double(n-1, k-1);
}

int Binomiale(int n, int k) {
	if (n < 0)
		return -1;
	if (k < 0)
		return 0;
	if (n == 0)
		return 0;
	if (n < k)
		return 0;

	return (int)binomiale_double(n, k);
}
/*
int main(void) {
	int res1 = Binomiale(5, 2);
	int res2 = Binomiale(7, 3);
	return 0;
}
*/