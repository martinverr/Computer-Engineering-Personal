#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int x = 266;
	char s[] = "prova";
	FILE *f;
	f = fopen("out1", "wt");
	fprintf(f, "%i\n%s", x, s);		//266 0x13 0x10 prova	-> 3+2+5=10
									//'2''6''6' 13 10 'p' 'r' 'o' 'v' 'a'
	
	fclose(f);
	f = fopen("out2", "wb");		
	fprintf(f, "%i\n%s", x, s);		//266 0x10 prova		-> 9
									//'2''6'6' 10 'p' 'r' 'o' 'v' 'a'
	fclose(f);
	f = fopen("out3", "wt");
	fwrite(&x, sizeof x, 1, f);		//4		0x0d 0x0A 0x01 0x00 0x00			-> 4
	fwrite(&s, sizeof s, 1, f);		//6		'p' r' 'o' 'v' 'a' '\0'			-> 6
									//10 byte
	fclose(f);
	f = fopen("out4", "wb");
	fwrite(&x, sizeof x, 1, f);
	fwrite(&s, sizeof s, 1, f);
									//come prima -1 (no 0x0d)
	fclose(f);
	return 0;
}