#include "Babbonatale.h"

void printSol(int n, bool * vbest){
	for (int i = 0; i < n; i++) {
		printf("%d ", vbest[i]);
	}
	printf("\n");
}

unsigned int count(bool * v, int n) {
	unsigned int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] == 1)
			cnt++;
	}
	return cnt;
}


void BabboNatale(int p, int const *pacchi, int n, unsigned i, bool *vcurr, 
		bool *vbest, unsigned *max, unsigned cnt, int sum) {
	if (i == n) {
		if (sum <= p && cnt >= *max) {
			vbest = memmove(vbest, vcurr, n);
			*max = cnt;
		}
		return;
	}
	
	if (sum + pacchi[i] <= p) {
		vcurr[i] = 1;
		BabboNatale(p, pacchi, n, i + 1, vcurr, vbest, max, cnt + 1, sum + pacchi[i]);
	}

	vcurr[i] = 0;
	BabboNatale(p, pacchi, n, i + 1, vcurr, vbest, max, cnt, sum);

	if (i == 0)
		printSol(n, vbest);
}

/*
int main(void) {
	int pacchi[] = { 10, 11, 1, 3, 3};
	bool vcurr[5];
	bool vbest[5];
	unsigned int max = 0;
	BabboNatale(20, pacchi, 5, 0, vcurr, vbest, &max, 0, 0);
	
	return 0;
}
*/

/*	PS Note
*	righe 22-28 possono essere modificate per prendere come migliore
*	soluzione, tra due uguali per numero di pacchi, quella più pesante.
*	La funzione int weight(bool * v, int n) sarebbe da definire.
*
**	if (i == n) {
**		if (sum <= p && cnt >= *max) {
**			if(cnt == *max){
**				if(sum > weight(vbest, n){
**					vbest = memmove(vbest, vcurr, n);
**					*max = cnt;
**				}
**			}
**
**			else{
**				vbest = memmove(vbest, vcurr, n);
**				*max = cnt;
**			}
**		}
**		return;
**	}
*
*/