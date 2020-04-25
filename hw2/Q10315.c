/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getCategory(char **);
int *getValue(char **);
int getPairIndex(int *, int);
int *getRemaining(int *, int, int, int);
int isPair(int *, int);			/* C89 does not have bool type */
int isTwoPairs(int *);			/* C89 does not have bool type */
int isThreeOfAKind(int *);		/* C89 does not have bool type */
int isStraight(int *);			/* C89 does not have bool type */
int isFlush(char **);			/* C89 does not have bool type */
int isFullHouse(int *);			/* C89 does not have bool type */
int isFourOfAKind(int *);		/* C89 does not have bool type */
int isStraightFlush(char **);	/* C89 does not have bool type */
void isSameCategory(int *, int *, int);
void compareHighCard(int *, int *, int);
void comparePair(int *, int *, int);
void compareTwoPairs(int *, int *);
void compareThreeOfAKind(int *, int *);
void compareStraight(int *, int *);
void compareFlush(int *, int *);
void compareFullHouse(int *, int *);
void compareFourOfAKind(int *, int *);
void compareStraightFlush(int *, int *);

int main() {
	
	/* declaration */
	char *str;	/* input */
	char **black, **white;	/* hands */
	int i;	/* iterator */
	
	/* allocation */
	str = (char *)malloc(30 * sizeof(char));
	black = (char **)malloc(5 * sizeof(char *));
	white = (char **)malloc(5 * sizeof(char *));
	for (i = 0; i < 5; ++i) {
		black[i] = (char *)malloc(2 * sizeof(char));
		white[i] = (char *)malloc(2 * sizeof(char));
	}
	
	/* loop */
	while (gets(str) != NULL) {
		
		/* string processing */
		int count = 0;
		char *temp = (char *)malloc(10 * sizeof(char));
		temp = strtok(str, " ");
		while (temp != NULL) {
			if (count < 5) {
				strncpy(black[count], temp, 2);
			} else {
				strncpy(white[count-5], temp, 2);
			}
			++count;
			temp = strtok(NULL, " ");
		}
		free(temp);
		/*
			// print hands
			for (i = 0; i < 10; ++i) {
				if (i == 5) printf("\n");
				if (i < 5) {
					printf("%s ", black[i]);
				} else {
					printf("%s ", white[i-5]);
				}
			}
			printf("\n");
		*/
		
		/* check categoty */
		int blackCategory = getCategory(black);
		int whiteCategory = getCategory(white);
		/*
			// print categories
			printf("%d %d\n", blackCategory, whiteCategory);
		*/
		
		/* calculate result */
		if (blackCategory > whiteCategory) {
			printf("Black wins.\n");
		} else if (blackCategory < whiteCategory) {
			printf("White wins.\n");
		} else {
			int *blackValue = getValue(black);
			int *whiteValue = getValue(white);
			isSameCategory(blackValue, whiteValue, blackCategory);
			free(blackValue);
			free(whiteValue);
		}
		
	}
	
	return 0;
}

int getCategory(char **hand) {
	int category = 0;
	int *value = getValue(hand);
	if (isPair(value, 5)) category = 1;
	if (isTwoPairs(value)) category = 2;
	if (isThreeOfAKind(value)) category = 3;
	if (isStraight(value)) category = 4;
	if (isFlush(hand)) category = 5;
	if (isFullHouse(value)) category = 6;
	if (isFourOfAKind(value)) category = 7;
	if (isStraightFlush(hand)) category = 8;
	free(value);
	return category;
}

int *getValue(char **hand) {
	int *result = (int *)malloc(5 * sizeof(int));
	int i, j;
	/* convert character to integer */
	for (i = 0; i < 5; ++i) {
		if (hand[i][0] == 'A') {
			result[i] = 14;		/* A is the largest */
		} else if (hand[i][0] == 'T') {
			result[i] = 10;
		} else if (hand[i][0] == 'J') {
			result[i] = 11;
		} else if (hand[i][0] == 'Q') {
			result[i] = 12;
		} else if (hand[i][0] == 'K') {
			result[i] = 13;
		} else {
			result[i] = hand[i][0] - '0';
		}
	}
	/* sort from small to large */
	for (i = 0; i < 4; ++i) {
		for (j = i+1; j < 5; ++j) {
			if (result[i] > result[j]) {
				int temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
	return result;
}

int getPairIndex(int *value, int length) {
	int iter;
	for (iter = 0; iter < length-1; ++iter) {
		if (value[iter] == value[iter+1]) return iter;
	}
	return 5;
}

int *getRemaining(int *value, int length, int index, int pairLength) {
	int *remaining = (int *)malloc((length-pairLength) * sizeof(int));
	int iter, count = 0;
	for (iter = 0; iter < length; ++iter) {
		if (iter == index) {
			iter += pairLength - 1;
			continue;
		}
		remaining[count] = value[iter];
		++count;
	}
	return remaining;
}

int isPair(int *value, int length) {
	int iter;
	for (iter = 0; iter < length-1; ++iter) {
		if (value[iter] == value[iter+1]) return 1;
	}
	return 0;
}

int isTwoPairs(int *value) {
	/* check first pair */
	int index = getPairIndex(value, 5);
	if (index == 5) return 0;
	/* check second pair */
	int *remaining = getRemaining(value, 5, index, 2);
	if (isPair(remaining, 3)) {
		free(remaining);
		return 1;
	} else {
		free(remaining);
		return 0;
	}
}

int isThreeOfAKind(int *value) {
	int iter;
	for (iter = 0; iter < 3; ++iter) {
		if (value[iter] == value[iter+1] && value[iter+1] == value[iter+2]) return 1;
	}
	return 0;
}

int isStraight(int *value) {
	int iter;
	for (iter = 0; iter < 4; ++iter) {
		if (value[iter] != value[iter+1] - 1) return 0;
	}
	return 1;
}

int isFlush(char **hand) {
	/* get suit */
	char *suit = (char *)malloc(5 * sizeof(char));
	int iter;
	for (iter = 0; iter < 5; ++iter) {
		suit[iter] = hand[iter][1];
	}
	/* check flush */
	for (iter = 0; iter < 4; ++iter) {
		if (suit[iter] != suit[iter+1]) {
			free(suit);
			return 0;
		}
	}
	free(suit);
	return 1;
}

int isFullHouse(int *value) {
	if (isTwoPairs(value) && isThreeOfAKind(value)) {
		int count = 0;
		int iter;
		for (iter = 0; iter < 4; ++iter) {
			if (value[iter] == value[4]) ++count;
		}
		if(count == 1 || count == 2) return 1;
	}
	return 0;
}

int isFourOfAKind(int *value) {
	if (isTwoPairs(value) && isThreeOfAKind(value)) {
		int count = 0;
		int iter;
		for (iter = 0; iter < 4; ++iter) {
			if (value[iter] == value[4]) ++count;
		}
		if(count == 0 || count == 3) return 1;
	}
	return 0;
}

int isStraightFlush(char **hand) {
	if (isStraight(getValue(hand)) && isFlush(hand)) {
		return 1;
	} else {
		return 0;
	}
}

void isSameCategory(int *black, int *white, int category) {
	switch (category) {
		case 0:
			compareHighCard(black, white, 5); break;
		case 1:
			comparePair(black, white, 2); break;
		case 2:
			compareTwoPairs(black, white); break;
		case 3:
			compareThreeOfAKind(black, white); break;
		case 4:
			compareStraight(black, white); break;
		case 5:
			compareFlush(black, white); break;
		case 6:
			compareFullHouse(black, white); break;
		case 7:
			compareFourOfAKind(black, white); break;
		case 8:
			compareStraightFlush(black, white); break;	
	}
}

void compareHighCard(int *black, int *white, int length) {
	int iter;
	for (iter = length-1; iter >= 0; --iter) {
		if (black[iter] > white[iter]) {
			printf("Black wins.\n");
			return;
		} else if (black[iter] < white[iter]) {
			printf("White wins.\n");
			return;
		}
	}
	printf("Tie.\n");
}

void comparePair(int *black, int *white, int pairLength) {
	/* compare pair */
	int blackPairIndex = getPairIndex(black, 5);
	int whitePairIndex = getPairIndex(white, 5);
	if (black[blackPairIndex] > white[whitePairIndex]) {
		printf("Black wins.\n");
		return;
	} else if (black[blackPairIndex] < white[whitePairIndex]) {
		printf("White wins.\n");
		return;
	}
	/* compare remaining */
	int *blackRemaining = getRemaining(black, 5, blackPairIndex, pairLength);
	int *whiteRemaining = getRemaining(white, 5, whitePairIndex, pairLength);
	compareHighCard(blackRemaining, whiteRemaining, 5-pairLength);
	free(blackRemaining);
	free(whiteRemaining);
}

void compareTwoPairs(int *black, int *white) {
	int blackPairs[2], whitePairs[2];
	int blackPairIndex, whitePairIndex;
	int *blackRemaining, *whiteRemaining;
	/* get first pair */
	blackPairIndex = getPairIndex(black, 5);
	whitePairIndex = getPairIndex(white, 5);
	blackPairs[0] = black[blackPairIndex];
	whitePairs[0] = white[whitePairIndex];
	blackRemaining = getRemaining(black, 5, blackPairIndex, 2);
	whiteRemaining = getRemaining(white, 5, whitePairIndex, 2);
	/* get second pair */
	blackPairIndex = getPairIndex(blackRemaining, 3);
	whitePairIndex = getPairIndex(whiteRemaining, 3);
	blackPairs[1] = black[blackPairIndex];
	whitePairs[1] = white[whitePairIndex];
	free(blackRemaining);
	free(whiteRemaining);
	blackRemaining = getRemaining(black, 3, blackPairIndex, 2);
	whiteRemaining = getRemaining(white, 3, whitePairIndex, 2);
	/* compare pairs */
	int iter;
	for (iter = 1; iter >= 0; ++iter) {
		if (blackPairs[iter] > whitePairs[iter]) {
			printf("Black wins.\n");
			free(blackRemaining);
			free(whiteRemaining);
			return;
		} else if (blackPairs[iter] < whitePairs[iter]) {
			printf("White wins.\n");
			free(blackRemaining);
			free(whiteRemaining);
			return;
		}
	}
	/* compare remaining */
	compareHighCard(blackRemaining, whiteRemaining, 1);
	free(blackRemaining);
	free(whiteRemaining);
}

void compareThreeOfAKind(int *black, int *white) {
	comparePair(black, white, 3);
}

void compareStraight(int *black, int *white) {
	compareHighCard(black, white, 5);
}

void compareFlush(int *black, int *white) {
	compareHighCard(black, white, 5);
}

void compareFullHouse(int *black, int *white) {
	if (black[2] > white[2]) {
		printf("Black wins.\n");
	} else if (black[2] < white[2]) {
		printf("White wins.\n");
	}
}

void compareFourOfAKind(int *black, int *white) {
	comparePair(black, white, 4);
}

void compareStraightFlush(int *black, int *white) {
	compareStraight(black, white);
}
/* @END_OF_SOURCE_CODE */