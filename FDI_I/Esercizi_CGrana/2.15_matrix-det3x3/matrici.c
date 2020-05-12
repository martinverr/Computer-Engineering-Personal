
double det3x3(double *matr) {
	double det = 0;

	det += matr[0] * matr[4] * matr[8];
	det += matr[1] * matr[5] * matr[6];
	det += matr[2] * matr[3] * matr[7];
	det -= matr[2] * matr[4] * matr[6];
	det -= matr[1] * matr[3] * matr[8];
	det -= matr[0] * matr[5] * matr[7];

	return det;
}

int main(void) {
	double matr[3*3] = {
		1, 2, 3,
		1, 1, 1,
		1, 2, 1,
	};
	double detmatr = det3x3(matr);
	return 0;
}

	