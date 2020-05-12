
unsigned int fatt(val) {
	unsigned int fatt = 1;
	if (val == 0 || val == 1)
		return 1;

	for (int n = val; n > 1; n--) {
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
		cos += (numeratore / denominatore)*pot(x, 2 * n);
	}

	return cos;
}

double seno_iperbolico(double x) {
	double senh = 0;
	/*
	sen=sum from n=0 to inf of
							   1
							-------x^(2n+1)
							(2n+1)!

	EXTERN LIBRARIES NOT ALLOWED
	*/
	double numeratore=1;
	double denominatore;
	for (int n = 0; n < 10; n++) {
		denominatore = fatt(2 * n + 1);
		senh += (numeratore / denominatore)*pot(x, 2 * n + 1);
	}

	return senh;
}

double seno(double x) {
	double sen = 0;
	/*
	sen=sum from n=0 to inf of
							(-1)^n
							-------x^(2n+1)
							(2n+1)!

	EXTERN LIBRARIES NOT ALLOWED
	*/
	double numeratore;
	double denominatore;
	for (int n = 0; n < 10; n++) {
		if (n % 2)
			numeratore = -1;
		else
			numeratore = 1;
		denominatore = fatt(2 * n + 1);
		sen += (numeratore / denominatore)*pot(x, 2 * n + 1);
	}

	return sen;
}