/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>

void calculateResult(int **, char **);

int main() {
	int m, n;
	char **map;
	int **result;
	while (scanf("%d %d\n", &m, &n)) {
		
		/* terminal condition */
		if (m == 0 && n == 0) {
			break;
		}
		
		/* input */
		int i, j;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				scanf("%c", &(*(*(map+j)+i)));
			}
		}
		
		/*
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				printf("%c", &(*(*(map+j)+i)));
			}
			printf("\n");
		}
		*/
		
		calculateResult(result, map);
		
		/* output */
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				printf("%d", &(*(*(result+j)+i)));
			}
			printf("\n");
		}
		
	}
}

void calculateResult(int **result, char **map) {
	
}
/* @END_OF_SOURCE_CODE */
