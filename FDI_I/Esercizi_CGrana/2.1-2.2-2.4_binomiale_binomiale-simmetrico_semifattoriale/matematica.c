double binomiale(double n, double k) {
	double fattn = 1, fattk = 1, fattnk = 1;
	int i = n - k;

	while (n)
	{
		fattn *= n;
		n--;
	}
	while (k)
	{
		fattk *= k;
		k--;
	}

	while (i)
	{
		fattnk *= i;
		i--;
	}
	return fattn / (fattk * fattnk);
}

double binomialesimmetrico(double n, double k, double h) {
	double fattn = 1, fattk = 1, fatth = 1;

	while (n)
	{
		fattn *= n;
		n--;
	}
	while (k)
	{
		fattk *= k;
		k--;
	}

	while (h)
	{
		fatth *= h;
		h--;
	}
	return fattn / (fattk * fatth);
}

double fattoriale(char n) {
	double res = 1;
	while (n > 1) {
		res *= n;
		n--;
	}
	return res;
}

double semifattoriale(char n) {
	double res = 1;
	while (n > 1) {
		res *= n;
		n -= 2;
	}
	return res;
}

/*
int main(void) {
	char m = 9;
	double n = 5, k = 3, h=2;

	double bin_simm_nkh = binomialesimmetrico(n, k, h);
	double bin_nk = binomiale(n, k);
	double fattorialen = fattoriale(n);
	double semifattorialen = semifattoriale(m);

	return 0;
}
*/