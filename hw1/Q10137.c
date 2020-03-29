/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>

void calculateResult(int **, char **);

int main() {
	int i, j; /* iterator */
	int m, n; /* input */
	char **map;
	int **result;
	while (1) {
		
		/* input */
		scanf("%d %d\n", &m, &n);
		
		/* terminal condition */
		if (m == 0 && n == 0) {
			break;
		}
		
		/* allocate memery */
		map = (char **)malloc(m * sizeof(char *));
		result = (int **)malloc(m * sizeof(int *));
		for (i = 0; i < m; ++i) {
			*(map+i) = (char *)malloc(n * sizeof(char));
			*(result+i) = (int *)malloc(n * sizeof(int));
		}
		
		/* input */
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%c", &(*(*(map+i)+j)));
			}
		}
		
		/*
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				printf("%c", &(*(*(map+i)+j)));
			}
			printf("\n");
		}
		*/
		
		calculateResult(result, map);
		
		/* output */
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				printf("%d", &(*(*(result+i)+j)));
			}
			printf("\n");
		}
		
		/* free memory */
		for (i = 0; i < m; ++i) {
			free(*(map+i));
			free(*(result+i));
		}
		free(map);
		free(result);
		
	}
}

void calculateResult(int **result, char **map) {
	
}
/* @END_OF_SOURCE_CODE */
