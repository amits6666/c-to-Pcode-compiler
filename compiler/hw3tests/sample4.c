#include <stdio.h>

void main() {
	int a;
	int b;

	a = (0 ? 5 : 2);
	printf("%d\n", a);
	b = (1 ? 5 : 2);
	printf("%d\n", b);

	for (a = 5 + 3 * 2 + a + 12 * 3; a < (2 * 3 * 5 * 2); a++) {
		printf("%d\n", a);
	}
	return;
}
