#include <stdlib.h>
#include <math.h>

int cifre_dec(int n) {
	int count = 0; 
	while (n != 0) {
		n /= 10;
		count++;
	}
	return count;
}

char *converti(unsigned int n) {
	int cifre = cifre_dec(n);
	int this_cifra = 0;
	char *str = malloc((cifre+1)*sizeof(char));

	for (int i = cifre-1, j=0; i>-1; i--, j++) {
		this_cifra = (int)(n / pow(10, i));
		str[j] = this_cifra + 48;
		n -= this_cifra*(int)(pow(10,i));
	}
	str[cifre] = 0;

	return str;
}


int main(void) {
	int i = 289;
	char* str=converti(i);

	free(str);
	return 0;
}