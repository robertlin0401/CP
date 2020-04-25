/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>

void calculateResult(int **, char **, int, int);
int top(char **, int, int);
int bottom(char **, int, int);
int left(char **, int, int);
int right(char **, int, int);
int top_left(char **, int, int);
int bottom_left(char **, int, int);
int top_right(char **, int, int);
int bottom_right(char **, int, int);

int main() {
	int i, j; /* iterator */
	char useless;
	int m, n; /* input */
	char **map;
	int **result;
	int count = 1;
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
			scanf("\n");
		}
		
		/*
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				printf("%c", *(*(map+i)+j));
			}
			printf("\n");
		}
		*/
		
		calculateResult(result, map, m, n);
		
		/* output */
		printf("Field #%d:\n", count);
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				if (*(*(result+i)+j) == -1) {
					printf("*");
					continue;
				}
				printf("%d", *(*(result+i)+j));
			}
			printf("\n");
		}
		printf("\n");
		++count;
		
		/* free memory */
		for (i = 0; i < m; ++i) {
			free(*(map+i));
			free(*(result+i));
		}
		free(map);
		free(result);
	
	}
	return 0;
}

void calculateResult(int **result, char **map, int m, int n) {
	int i, j; /* iterator */
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			*(*(result+i)+j) = -1;
			if (*(*(map+i)+j) == '*') continue;
			if (i == 0) /* upper bound */
			{
				if (j == 0) /* left bound */
				{
					/* top left */
					*(*(result+i)+j) = bottom(map, i, j)
									 + right(map, i, j)
									 + bottom_right(map, i, j);
				}
				else if (j == n-1) /* right bound */
				{
					/* top right */
					*(*(result+i)+j) = bottom(map, i, j) 
									 + left(map, i, j)
									 + bottom_left(map, i, j);
				}
				else 
				{
					/* top */
					*(*(result+i)+j) = bottom(map, i, j)
									 + left(map, i, j)
									 + bottom_left(map, i, j)
									 + right(map, i, j)
									 + bottom_right(map, i, j);
				}
			}
			else if (i == m-1) /* lower bound */
			{
				if (j == 0) {
					/* bottom left */
					*(*(result+i)+j) = top(map, i, j)
									 + right(map, i, j)
									 + top_right(map, i, j);
				} else if (j == n-1) {
					/* bottom right */
					*(*(result+i)+j) = top(map, i, j) 
									 + left(map, i, j)
									 + top_left(map, i, j);
				} else {
					/* bottom */
					*(*(result+i)+j) = top(map, i, j)
									 + left(map, i, j)
									 + top_left(map, i, j)
									 + right(map, i, j)
									 + top_right(map, i, j);
				}
			}
			else
			{
				if (j == 0) {
					/* left */
					*(*(result+i)+j) = top(map, i, j)
									 + bottom(map, i, j)
									 + right(map, i, j)
									 + top_right(map, i, j)
									 + bottom_right(map, i, j);
				} else if (j == n-1) {
					/* right */
					*(*(result+i)+j) = top(map, i, j)
									 + bottom(map, i, j)
									 + left(map, i, j)
									 + top_left(map, i, j)
									 + bottom_left(map, i, j);
				} else {
					/* middle */
					*(*(result+i)+j) = top(map, i, j)
									 + bottom(map, i, j)
									 + left(map, i, j)
									 + right(map, i, j)
									 + top_left(map, i, j)
									 + bottom_left(map, i, j)
									 + top_right(map, i, j)
									 + bottom_right(map, i, j);
				}
			}
		}
	}
	return;
}

int top(char **map, int i, int j) { return (*(*(map+i-1)+j) == '*'); }
int bottom(char **map, int i, int j) { return (*(*(map+i+1)+j) == '*'); }
int left(char **map, int i, int j) { return (*(*(map+i)+j-1) == '*'); }
int right(char **map, int i, int j) { return (*(*(map+i)+j+1) == '*'); }
int top_left(char **map, int i, int j) { return (*(*(map+i-1)+j-1) == '*'); }
int bottom_left(char **map, int i, int j) { return (*(*(map+i+1)+j-1) == '*'); }
int top_right(char **map, int i, int j) { return (*(*(map+i-1)+j+1) == '*'); }
int bottom_right(char **map, int i, int j) { return (*(*(map+i+1)+j+1) == '*'); }
/* @END_OF_SOURCE_CODE */
