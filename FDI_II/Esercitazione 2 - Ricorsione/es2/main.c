int Fibonacci(n) {
	/*
	param: <n>
	return the Fibonacci of n: F(n) = (F(n-1) + F(n-2))
				F(0) = 0
				F(1) = 1
	if <n> is 0 or a negative number return -1
	*/

	if (n < 0)
		return -1;
	if (n == 0)
		return 0;
	if (n == 1)	//recurs base
		return 1;
	return Fibonacci(n-1) + Fibonacci(n-2);
}

int main(void) {
	int res1 = Fibonacci(5);
	int res2 = Fibonacci(0);
	int res3 = Fibonacci(-5);
	int res4 = Fibonacci(1);
	int res5 = Fibonacci(10);
	return 0;
}