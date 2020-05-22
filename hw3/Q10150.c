/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct doublet {
	char *str;
	int index;
	struct doublet *next;
};

struct doublet *getResult(struct doublet **list, int listIndex, int doubletCount, char *endStr, int *isPickedConst, char *nowStr);
int isDoublet(char *str1, char *str2);
void simplifyResult(struct doublet *result);
void printResult(struct doublet *result);

int main() {
	
	/* declaration */
	int i, j;	/* iterator */
	int doubletCount = 0;
	struct doublet *head = NULL;
	struct doublet **list;
	char *str = (char *)malloc(17 * sizeof(char));
	
	/* read doublet */
	while (gets(str)) {
		if (!str[0]) break;
			struct doublet *newDoublet = (struct doublet *)malloc(sizeof(struct doublet));
		newDoublet->str = (char *)malloc(17 * sizeof(char));
		strcpy(newDoublet->str, str);
		newDoublet->index = doubletCount;
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
	
	/* generate adjacent list */
	list = (struct doublet **)malloc(doubletCount * sizeof(struct doublet *));
	struct doublet *ptrDoublet = head;
	for (i = 0; i < doubletCount; ++i) {
		struct doublet *ptrList = NULL;
		struct doublet *ptrElement = head;
		for (j = 0; j < doubletCount; ++j) {
			if (i == j) {
				ptrElement = ptrElement->next;
				continue;
			}
			if (isDoublet(ptrDoublet->str, ptrElement->str)) {
				struct doublet *element = (struct doublet *)malloc(sizeof(struct doublet));
				element->str = ptrElement->str;
				element->index = ptrElement->index;
				element->next = NULL;
				if (!ptrList) {
					ptrList = element;
					list[i] = ptrList;
				} else {
					ptrList->next = element;
					ptrList = ptrList->next;
				}
			}
			ptrElement = ptrElement->next;
		}
		ptrDoublet = ptrDoublet->next;
	}
	
	/*
		// print adjacent list
		for (i = 0; i < doubletCount; ++i) {
			struct doublet *ptr = list[i];
			printf("%d\n", i);
			while (ptr) {
				printf("%s\n", ptr->str);
				ptr = ptr->next;
			}
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
		
		struct doublet *result = (struct doublet *)malloc(sizeof(struct doublet));
		struct doublet *ptr = head;
		while (ptr) {
			if (strcmp(ptr->str, str1) == 0) {
				result->str = ptr->str;
				result->index = ptr->index;
				result->next = NULL;
				break;
			}
			ptr = ptr->next;
		}
		if (!ptr) {
			printf("No solution.\n");
			continue;
		}
		
		
		for (i = 0; i < doubletCount; ++i) {
			isPicked[i] = (i == result->index)? 1: 0;
		}
		result->next = getResult(list, result->index, doubletCount, str2, isPicked, str1);
		simplifyResult(result);
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

struct doublet *getResult(struct doublet **list, int listIndex, int doubletCount, char *endStr, int *isPickedConst, char *nowStr) {
	
	if (strcmp(nowStr, endStr) == 0) {
		return NULL;
	}
	
	int iter;
	int *isPicked = (int *)malloc(doubletCount * sizeof(int));
	for (iter = 0; iter < doubletCount; ++iter) {
		isPicked[iter] = isPickedConst[iter];
	}
	
	struct doublet *ptrList = list[listIndex];
	struct doublet *newResult = (struct doublet *)malloc(sizeof(struct doublet));
	while (ptrList) {
		if (!isPicked[ptrList->index]) {
			isPicked[ptrList->index] = 1;
			newResult->str = ptrList->str;
			newResult->index = ptrList->index;
			newResult->next = getResult(list, newResult->index, doubletCount, endStr, isPicked, newResult->str);
			if (!newResult->next && strcmp(newResult->str, endStr) != 0) {
				isPicked[ptrList->index] = 0;
			} else {
				free(isPicked);
				return newResult;
			}
		}
		ptrList = ptrList->next;
	}
	
	free(isPicked);
	free(newResult);
	return NULL;
	
}

int isDoublet(char *str1, char *str2) {
	int iter;
	int count = 0;
	for (iter = 0; iter < 17; ++iter) {
		if (!str1[iter] || !str2[iter]) {
			if (!str1[iter] && !str2[iter]) {
				break;
			} else {
				return 0;
			}
		}
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