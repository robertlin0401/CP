/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>

void swap(int *, int *);

int main() {
	int n, temp; /* iterator */
	int i, j; /* input */
	int isSwapped;
	int cycle;
	int count;
	while (scanf("%d %d", &i, &j) != EOF) {
		
		/* validation check */
		if (!(i < 1000000 && i > 0) || !(j < 1000000 && j > 0)) {
			printf("Invalid input\n");
			continue;
		}
		
		/* swap */
		isSwapped = 0;
		if (i > j) {
			swap(&i, &j);
			isSwapped = 1;
		}
		
		/* calculate */
		cycle = 0;
		for (n = i; n <= j; ++n) {
			count = 1;
			temp = n;
			while (temp != 1) {
				++count;
				if (temp & 1) { /* odd */
					temp = 3 * temp + 1;
				} else {
					temp >>= 1;
				}
			}
			if (count > cycle) {
				cycle = count;
			}
		}
		
		/* output */
		if (isSwapped) swap(&i, &j);
		printf("%d %d %d\n", i, j, cycle);
		
	}
	return 0;
}

void swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
/* @END_OF_SOURCE_CODE */
