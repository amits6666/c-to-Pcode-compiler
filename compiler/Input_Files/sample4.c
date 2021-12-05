#include <stdio.h>

void main() {
	int a;
	int b;

	a = 10;
	if (0) {
		a = a + 6;
	}
	else {
		a = 10 * a;
	}

	printf("%d\n", a);
	return;
}