#include <stdio.h>

void main() {
	int a;
	int b;
	a = 1;
	b = 2;

	printf("%d\n", a);
	a = b * 0 + 0 / a + 15 - 8;
	printf("%d\n", a);
	a = ((a * 0 > 0) ? 1 : 2) + ((a * 0 > 0) ? 2 : 1);
	printf("%d\n", a);
	a = 0 * b + 3;
	printf("%d\n", a);
	a *= 0 * b + 5 - 5;
	printf("%d\n", a);
	a *= b * 0 + 6 - 5;
	printf("%d\n", a);
	a = b*(2*2);
	printf("%d\n", a);
	return;
}
