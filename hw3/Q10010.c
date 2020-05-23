/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>

int toLowerCase(char *);
int findMap(char **map, char *input, int inputLength, int m, int n, int x, int y);
int findDirection(char **map, char *input, int inputLength, int x, int y, int index, int direction);

int main() {
	
	int iter;
	int cases, m, n, k;
	char **map;
	char *input = (char *)malloc(21 * sizeof(char));
	
	scanf("%d\n\n", &cases);
	
	while (cases) {
		
		scanf("%d %d\n", &m, &n);
		
		map = (char **)malloc(m * sizeof(char *));
		for (iter = 0; iter < m; ++iter) {
			map[iter] = (char *)malloc((n+1) * sizeof(char));
			fgets(map[iter], n+2, stdin);
			toLowerCase(map[iter]);
		}
		
		/*
			// print map
			for (iter = 0; iter < m; ++iter) {
				printf("%s\n", map[iter]);
			}
		*/
		
		scanf("%d\n", &k);
		for (iter = 0; iter < k; ++iter) {
			
			fgets(input, n+2, stdin);
			int inputLength = toLowerCase(input);
			/*
				// print input
				printf("%s\n", input);
			*/
			
			int i, j;
			int isFound = 0;
			for (i = 0; i < m; ++i) {
				for (j = 0; j < n; ++j) {
					if (findMap(map, input, inputLength, m, n, i, j)) {
						isFound = 1;
						printf("%d %d\n", i+1, j+1);
						break;
					}
				}
				if (isFound) break;
			}
			
		}
		
		--cases;
		if (cases) printf("\n");
		
		for (iter = 0; iter < m; ++iter) {
			free(map[iter]);
		}
		free(map);
		
	}
	
	free(input);
	
	return 0;
	
}

int toLowerCase(char *str) {
	int index = 0;
	while (1) {
		if (str[index] == '\0') break;
		if (str[index] == '\n') {
			str[index] = '\0';
			break;
		} else if (str[index] >= 'A' && str[index] <= 'Z') {
			str[index] -= ('A' - 'a');
		}
		++index;
	}
	return index;
}

int findMap(char **map, char *input, int inputLength, int m, int n, int x, int y) {
	int isFound = 0;
	if (x >= inputLength-1) {
		isFound += findDirection(map, input, inputLength, x, y, 0, 8);
		if (y >= inputLength-1) {
			isFound += findDirection(map, input, inputLength, x, y, 0, 1);
		}
		if (y <= n-inputLength) {
			isFound += findDirection(map, input, inputLength, x, y, 0, 7);
		}
	}
	if (x <= m-inputLength) {
		isFound += findDirection(map, input, inputLength, x, y, 0, 4);
		if (y >= inputLength-1) {
			isFound += findDirection(map, input, inputLength, x, y, 0, 3);
		}
		if (y <= n-inputLength) {
			isFound += findDirection(map, input, inputLength, x, y, 0, 5);
		}
	}
	if (y >= inputLength-1) {
		isFound += findDirection(map, input, inputLength, x, y, 0, 2);
	}
	if (y <= n-inputLength) {
		isFound += findDirection(map, input, inputLength, x, y, 0, 6);
	}
	return (isFound != 0)? 1: 0;
}

int findDirection(char **map, char *input, int inputLength, int x, int y, int index, int direction) {
	
	int xDirection, yDirection;
	if (direction % 2 == 0) {
		if (direction % 4 == 0) {
			xDirection = (direction / 4 == 1)? 1: -1;
			yDirection = 0;
		} else {
			xDirection = 0;
			yDirection = (direction / 4 == 0)? -1: 1;
		}
	} else {
		if (direction == 1 || direction == 7) {
			xDirection = -1;
		} else {
			xDirection = 1;
		}
		yDirection = (direction / 4 == 0)? -1: 1;
	}
	
	/*	section A */
	if (map[x][y] == input[index]) {
		if (inputLength == index+1) {
			return 1;
		} else {
			return findDirection(map, input, inputLength, x+xDirection, y+yDirection, index+1, direction);
		}
	} else {
		return 0;
	}
	
	/*	section B
	int iter;
	for (iter = 0; iter < inputLength; ++iter) {
		if (map[x+xDirection*iter][y+yDirection*iter] != input[iter]) {
			return 0;
		}
	}
	return 1;
	*/
	
}
/* @END_OF_SOURCE_CODE */