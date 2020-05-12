#include <ctype.h>

int is_date(const char*s) {
	if(s==NULL)
		if (isalnum(s[0]) && isalnum(s[1]))
			if (s[2] == '/')
				if (isalnum(s[3]) && isalnum(s[4]))
					if (s[5] == '/')
						if (isalnum(s[6]) && isalnum(s[7]) && isalnum(s[6]) && isalnum(s[7]))
							return 1;
	return 0;
}