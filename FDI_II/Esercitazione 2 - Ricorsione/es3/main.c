int * Minimo(int *vec, int len) {
	/*
	param:	<vec> array of int
			<len> lenght of array <vec>

	return: the pointer to the minimum element of array <vec>
	Notes: We assume vec is always != NULL and len >= 1
	*/

	if (len == 1)	// recurs base
		return vec;
	if (vec[len-1] < vec[0])
		vec[0] = vec[len-1]; // vec[0] is our minimum
	return Minimo(vec, len-1);
}

int main(void) {
	int vector[5] = { 49, -4, 0, 3, 1 };
	int * min = Minimo(vector,5);
	return 0;
}