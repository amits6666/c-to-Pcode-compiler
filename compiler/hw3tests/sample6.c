#include <stdio.h>

void main() {
	int x;
	int a;
	int b;
	x = 1 - 1 * (5 * 3);
	a = 1;
	b = 3;
	printf("%d\n", x);
	x += ((5 + 3 - 2 * 7) * 0); 
	printf("%d\n", x);
	x *= (15 - 14);
	printf("%d\n", x);
	x *= (15 - 15);
	printf("%d\n", x);
	x *= (a * 0);
	printf("%d\n", x);
	x += (2 > 1 ? 0 : 1);
	printf("%d\n", x);
	x = 0 / a;
	printf("%d\n", x);
	x = (13 * 2) == (2 < 4);
	printf("%d\n", x);
	x = (a && 1) + (a && 0) + (a || 1) + (a || 0);
	printf("%d\n", x);
	x = (0 && a) + (1 && a) + (1 || a) + (0 || a);
	printf("%d\n", x);
	x = (a * 1) + (0 / b);
	printf("%d\n", x);
	x = 10 + 34;
	printf("%d\n", x);
	x = 10 + (a * 0 ? 1 : 2);
	printf("%d\n", x);
	x -= 10 - (a * 0 ? 1 : 10);
	printf("%d\n", x);
	x -= 10 - (a > 0 ? 1 : 10);
	printf("%d\n", x);
	x -= (10 * 2 * 3) - (a > 0 ? 1 + 2 : 10 - 1);
	printf("%d\n", x);
	x = (10 * 2 * 3) + (a / a) + (a - (3 - 2)*a);
	printf("%d\n", x);
	return;
}
