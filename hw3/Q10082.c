/* @JUDGE_ID: 1127525 */

/* @BEGIN_OF_SOURCE_CODE */
#include <stdio.h>

int main() {
	char inputTable[43] = {
		'1','2','3','4','5','6','7','8','9','0','-','=',
		'W','E','R','T','Y','U','I','O','P','[',']','\\',
		'S','D','F','G','H','J','K','L',';','\'',
		'X','C','V','B','N','M',',','.','/'
	};
	char outputTable[43] = {
		'`','1','2','3','4','5','6','7','8','9','0','-',
		'Q','W','E','R','T','Y','U','I','O','P','[',']',
		'A','S','D','F','G','H','J','K','L',';',
		'Z','X','C','V','B','N','M',',','.'
	};
	char ch;
	while (ch = getc(stdin)) {
		if (ch == EOF) break;
		int index;
		for (index = 0; index < 43; ++index) {
			if (ch == inputTable[index]) break;
		}
		if (index == 43) {
			putc(ch, stdout);
		} else {
			putc(outputTable[index], stdout);
		}
	}
	return 0;
}
/* @END_OF_SOURCE_CODE */