#include "bcd.h"

//unsigned short bin2bcd(unsigned short val){
//	char this_cifra=0;
//	unsigned res = 0;
//
//
//	for (int i = 4; i > 0; i--) {
//		this_cifra = val / (int)(pow(10,i));
//		res += this_cifra;
//		res <<= 4;
//		val -= this_cifra * (int)(pow(10, i));
//	}
//
//	this_cifra = (char)val;
//	res += this_cifra;
//
//	return res;
//}


unsigned short bin2bcd(unsigned short val) {
	char str[6];
	unsigned int res = 0;
	
	sprintf(str, "%d", val);
	int i = 0;
	while(str[i]!=0){
		res += str[i]-48;
		if (str[i + 1] == 0)
			break;
		res <<= 4;
		i++;
	}
	return res;
}
