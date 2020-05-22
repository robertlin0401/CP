/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct doublet {
	char *str;
	struct doublet *next;
};

struct doublet *getResult(struct doublet *head, int doubletCount, char *endStr, int *isPickedConst, char *nowStr);
int isDoublet(char *str1, char *str2);
void simplifyResult(struct doublet *result);
void printResult(struct doublet *result);

int main() {
	
	/* declaration */
	int i, j;	/* iterator */
	int doubletCount = 0;
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
		++doubletCount;
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
	int *isPicked = (int *)malloc(doubletCount * sizeof(int));
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
		
		int count = 0;
		struct doublet *result = (struct doublet *)malloc(sizeof(struct doublet));
		struct doublet *ptr = head;
		while (ptr) {
			if (strcmp(ptr->str, str1) == 0) {
				result->str = ptr->str;
				result->next = NULL;
				break;
			}
			ptr = ptr->next;
			++count;
		}
		if (!ptr) {
			printf("No solution.\n");
			continue;
		}
		
		for (i = 0; i < doubletCount; ++i) {
			isPicked[i] = (i == count)? 1: 0;
		}
		result->next = getResult(head, doubletCount, str2, isPicked, str1);
		simplfyResult(result);
		printResult(result);
		
		while (result) {
			struct doublet *temp = result->next;
			free(result);
			result = temp;
		}
		
	}
	
	free(isPicked);
	free(str);
	
	return 0;
}

struct doublet *getResult(struct doublet *head, int doubletCount, char *endStr, int *isPickedConst, char *nowStr) {
	
	if (strcmp(nowStr, endStr) == 0) {
		return NULL;
	}
	
	int iter;
	int *isPicked = (int *)malloc(doubletCount * sizeof(int));
	for (iter = 0; iter < doubletCount; ++iter) {
		isPicked[iter] = isPickedConst[iter];
	}
	
	int count = 0;
	struct doublet *ptrDoublet = head;
	struct doublet *newResult = (struct doublet *)malloc(sizeof(struct doublet));
	while (ptrDoublet) {
		if (!isPicked[count]) {
			if (isDoublet(ptrDoublet->str, nowStr)) {
				isPicked[count] = 1;
				newResult->str = ptrDoublet->str;
				newResult->next = getResult(head, doubletCount, endStr, isPicked, newResult->str);
				if (!newResult->next && strcmp(newResult->str, endStr) != 0) {
					isPicked[count] = 0;
				} else {
					free(isPicked);
					return newResult;
				}
			}
		}
		ptrDoublet = ptrDoublet->next;
		++count;
	}
	
	free(isPicked);
	free(newResult);
	return NULL;
	
}

int isDoublet(char *str1, char *str2) {
	int iter;
	int count = 0;
	for (iter = 0; iter < 17; ++iter) {
		if (!str1[iter]) break;
		if (str1[iter] != str2[iter]) {
			count += 1;
		}
		if (count > 1) return 0;
	}
	if (count == 1) {
		return 1;
	} else {
		return 0;
	}		
}

void simplifyResult(struct doublet *result) {
	
}

void printResult(struct doublet *result) {
	if (!result->next) {
		printf("No solution.\n");
		return;
	}
	while (result) {
		printf("%s\n", result->str);
		result = result->next;
	}
}
/* @END_OF_SOURCE_CODE */