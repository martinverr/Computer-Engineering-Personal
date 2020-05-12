void encrypt(char *s, unsigned int n) {
	for (int i = 0; i < n; i++) {
		s[i] = s[i] ^ 0xAA;
	}
}


/*
*	TEST: "porcodio" has to be encrypted to
*	a string of the type "xxxxxxio"
*	and to be de-encrypted back to "porcodio"
*
*	int main(void) {
*	char s[] = { "porcodio" };
*	encrypt(s, 6);
*	encrypt(s, 6);
*	return 0;
*	}
*/