
unsigned int fatt(val) {
	unsigned int fatt = 1;
	if (val == 0 || val == 1)
		return 1;

	for (int n=val; n > 1; n--) {
		fatt *= n;
	}

	return fatt;
}

double pot(double base, double exp) {
	double res = 1;
	for (exp; exp > 0; exp--) {
		res *= base;
	}

	return res;
}

double coseno(double x) {
	double cos = 0;
	/*
	cos=sum from n=0 to inf of
							(-1)^n
							-------x^(2n)
							(2n)!

	EXTERN LIBRARIES NOT ALLOWED
	*/
	double numeratore;
	double denominatore;
	for (int n = 0; n < 10; n++) {
		if (n % 2)
			numeratore = -1;
		else
			numeratore = 1;
	denominatore = fatt(2 * n);
		cos += (numeratore/denominatore)*pot(x, 2 * n);
	}

	return cos;
}

int main(void) {
	double cos60=coseno(3.14159265 / 3);
	return 0;
}