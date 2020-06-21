#include <stdlib.h>
#include <stdio.h>

void recHailstone(int t, size_t * numOfEl) {
	if (t == 1) {
		(*numOfEl)++;
		return ;
	}

	if (t % 2 == 0) {
		printf("%d, ", t / 2);
		(*numOfEl)++;
		recHailstone(t / 2, numOfEl);
	}
	else {
		printf("%d, ", t * 3 + 1);
		(*numOfEl)++;
		recHailstone(3 * t + 1, numOfEl);
	}

}
size_t Hailstone(int t) {
	if (t <= 0)
		return 0;

	printf("%d, ", t);
	
	size_t numOfEl = 0;
	recHailstone(t, &numOfEl);

	return numOfEl;
}