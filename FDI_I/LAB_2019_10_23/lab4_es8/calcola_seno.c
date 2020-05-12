double fatt(n) {
	unsigned int res = 1;
	while (n > 1)
	{
		res *= n;
		n--;
	}
	return res;
}


int pot_dimenouno_allan(int n) {
	if (n % 2)
		return -1;
	else
		return 1;
}


double pot(double base, int esp)
{
	double res = 1;
	for (esp; esp > 0; esp--)
	{
		res *= base;
	}
	return res;
}

double calcola_seno(double x) {
	double senx = 0;
	
	for (double n = 0; n < 20; n++)
	{
		senx+=(pot_dimenouno_allan(n) / fatt(2 * n + 1))*pot(x, 2 * n + 1);
	}
	return senx;
}
/*
int main(void) {
	double x = 0.2;
	double senx = calcola_seno(x);
	return 0;
}
*/