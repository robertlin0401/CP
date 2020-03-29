/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>

void swap(int *, int *);

int main() {
	int i, j;
	while (scanf("%d %d", &i, &j) != EOF) {
		
		/* validation check */
		if (!(i < 1000000 && i > 0) || !(j < 1000000 && j > 0)) {
			printf("Invalid input\n");
			break;
		}
		
		/* swap */
		int isSwapped = 0;
		if (i > j) {
			swap(&i, &j);
			isSwapped = 1;
		}
		
		/* calculate */
		int cycle = 0;
		int n;
		for (n = i; n <= j; ++n) {
			int count = 1;
			int temp = n;
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
}

void swap(int *a, int *b) {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}
/* @END_OF_SOURCE_CODE */
