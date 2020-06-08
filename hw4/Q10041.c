/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int i, j, iter; 	/* iterator */
	
	/* number of test cases */
	int cases;
	scanf("%d", &cases);
	
	/* loop for cases */
	for (iter = 0; iter < cases; ++iter) {
		
		/* read input */
		int relatives;
		scanf("%d", &relatives);
		
		int *roads = (int *)malloc(relatives * sizeof(int));
		for (i = 0; i < relatives; ++i) {
			scanf("%d", roads+i);
		}
		
		/*	// print input
			for (i = 0; i < relatives; ++i) {
				printf("%d ", *(roads+i));
			}
			printf("\n");
		*/
		
		/* calculate */
		int distance = 99999999;
		for (i = 0; i < relatives; ++i) {
			int sum = 0;
			for (j = 0; j < relatives; ++j) {
				sum += abs(roads[i] - roads[j]);
			}
			if (sum < distance) {
				distance = sum;
			}
		}
		
		/* output */
		printf("%d\n", distance);
		
		/* deallocation */
		free(roads);
		
	}
	
	return 0;
}
/* @END_OF_SOURCE_CODE */