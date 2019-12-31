#include <stdio.h>

int main() {
	int i, j;
	while (scanf("%d %d", &i, &j) != EOF) {
		int cycle = 0;
		int n;
		for (n = i; n <= j; ++n) {
			int count = 1;
			int temp = n;
			while (temp != 1) {
				++count;
				if (temp & 1) { // odd
					temp = 3 * temp + 1;
				} else {
					temp >>= 1;
				}
			}
			if (count > cycle) {
				cycle = count;
			}
		}
		printf("%d %d %d\n", i, j, cycle);
	}
}
