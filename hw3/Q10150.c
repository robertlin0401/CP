/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct doublet {
	char *str;
	struct doublet *next;
};

int checkDoublet(char *, char *);
void printResult(struct doublet *);

int main() {
	
	/* declaration */
	int i, j;	/* iterator */
	struct doublet *head = NULL;
	char *str = (char *)malloc(17 * sizeof(char));
	
	/* read doublet */
	while (gets(str)) {
		if (!str[0]) break;
		struct doublet *newDoublet = (struct doublet *)malloc(sizeof(struct doublet));
		newDoublet->str = (char *)malloc(17 * sizeof(char));
		strcpy(newDoublet->str, str);
		newDoublet->next = NULL;
		if (!head) {
			head = newDoublet;
		} else {
			struct doublet *ptr = head;
			while (ptr->next) {
				ptr = ptr->next;
			}
			ptr->next = newDoublet;
		}
	}
	
	/*
		// print doublet
		struct doublet *ptr = head;
		while (ptr) {
			printf("%s\n", ptr->str);
			ptr = ptr->next;
		}
	*/
	
	/* test case */
	int firstCase = 1;
	str = (char *)malloc(34 * sizeof(char));
	while (gets(str)) {
		
		if (firstCase) {
			firstCase = 0;
		} else {
			printf("\n");
		}
		
		char *str1, *str2;
		str1 = strtok(str, " ");
		str2 = strtok(NULL, " ");
		
		struct doublet *result = (struct doublet *)malloc(sizeof(struct doublet));
		struct doublet *ptr = head;
		while (ptr) {
			if (strcmp(ptr->str, str1) == 0) {
				result->str = ptr->str;
				result->next = NULL;
				break;
			}
			ptr = ptr->next;
		}
		if (!ptr) {
			printf("No solution.\n");
			continue;
		}
		
		struct doublet *ptrResult = result;
		while (1) {
			struct doublet *ptrDoublet = head;
			struct doublet *newResult = (struct doublet *)malloc(sizeof(struct doublet));
			while (ptrDoublet) {
				if (checkDoublet(ptrDoublet->str, ptrResult->str)) {
					struct doublet *checkResult = result;
					while (checkResult) {
						if (strcmp(checkResult->str, ptrDoublet->str) == 0) break;
						checkResult = checkResult->next;
					}
					if (!checkResult) {
						newResult->str = ptrDoublet->str;
						newResult->next = NULL;
					}
				}
				ptrDoublet = ptrDoublet->next;
			}
			if (!newResult->str) {
				printf("No solution.\n");
				break;
			} else {
				ptrResult->next = newResult;
				ptrResult = ptrResult->next;
				if (strcmp(newResult->str, str2) == 0) {
					printResult(result);
					break;
				}
			}
		}
		
		while (result) {
			struct doublet *temp = result;
			result = result->next;
			free(temp);
		}
		
	}
	
	return 0;
}



int checkDoublet(char *str1, char *str2) {
	int iter;
	int isDoublet = 0;
	for (iter = 0; iter < 17; ++iter) {
		if (str1[iter] != str2[iter]) {
			isDoublet += 1;
		}
	}
	if (isDoublet == 1) {
		return 1;
	} else {
		return 0;
	}		
}

void printResult(struct doublet *result) {
	while (result) {
		printf("%s\n", result->str);
		result = result->next;
	}
}
/* @END_OF_SOURCE_CODE */