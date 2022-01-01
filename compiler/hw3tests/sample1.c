#include <stdio.h>

void main() {
	int a;
	a = 40;
	if (a / 2) {
		printf("%d\n", 1);
	}

	if (a*(5 - 5)) {
		printf("%d\n", 2);
	}

	if (a / (5 + 2)) {
		printf("%d\n", 3);
	}

	if (10) {
		printf("%d\n", 4);
	}

	if (5 - 5) {
		printf("%d\n", 5 + 13 - 1);
	}
	else {
		printf("%d\n", 6 * 2);
	}

	if (5 + 5) {
		printf("%d\n", 7 * 2 * 2);
	}
	else {
		printf("%d\n", 8);
	}

	return;
}

