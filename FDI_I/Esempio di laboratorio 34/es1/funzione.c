#include "funzione.h"

bool is_date(const char *s){
	if (s == NULL || strlen(s) != 10)
		return false;
	
	if (!isdigit(s[0]) || !isdigit(s[1]) ||
		!isdigit(s[3]) || !isdigit(s[4]) ||
		!isdigit(s[6]) || !isdigit(s[7]) || !isdigit(s[8]) || !isdigit(s[9]))
		return false;

	if (s[2] != '/' || s[5] != '/')
		return false;
	
	return true;
}