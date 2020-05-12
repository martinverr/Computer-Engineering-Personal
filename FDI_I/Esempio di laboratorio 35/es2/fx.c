#include "duplicate.h"

bool cifre_duplicate_hex(unsigned int n) {
	char cifreExa[10];
	sprintf(cifreExa, "%x", n);

	for (size_t i = 0; i < strlen(cifreExa); i++) {
		char nowchecking = cifreExa[i];
		for (size_t j = i+1; j < strlen(cifreExa); j++) {
			if (cifreExa[j] == nowchecking)
				return true;
		}
	}

	return false;
}

int main(void) {
	
	bool res1 = cifre_duplicate_hex(153);
	bool res2 = cifre_duplicate_hex(154);
	bool res3 = cifre_duplicate_hex(10);
	bool res4 = cifre_duplicate_hex(0);
	bool res5 = cifre_duplicate_hex(15826);



	return 0;
}