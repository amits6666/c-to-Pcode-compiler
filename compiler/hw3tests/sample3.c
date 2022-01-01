#include <stdio.h>

void main() {
	int x;
	int a;
	int b;
	x = 2;
	a = 1;
	b = 3;

	printf("%d\n", x);
	x = a + (5-5);
	printf("%d\n", x);
	x = 0 + a;
	printf("%d\n", x);
	x = a + 5;
	printf("%d\n", x);
	x = b - (10*0);
	printf("%d\n", x);
	x = (18-2*9) - b;
	printf("%d\n", x);
	x = b - 5;
	printf("%d\n", x);
	x = 0 / a;
	printf("%d\n", x);
	x = a / 1;
	printf("%d\n", x);
	x = 0 * a;
	printf("%d\n", x);
	x = a * 0;
	printf("%d\n", x);
	x = a * (18-17);
	printf("%d\n", x);
	x = 1 * a;
	printf("%d\n", x);
	x = 0 && a;
	printf("%d\n", x);
	x = a && 0;
	printf("%d\n", x);
	x = a && (18 - 17);
	printf("%d\n", x);
	x = 1 && a;
	printf("%d\n", x);
	x = 0 || a;
	printf("%d\n", x);
	x = a || 0;
	printf("%d\n", x);
	x = a || (25 - 17);
	printf("%d\n", x);
	x = 222 || a;
	printf("%d\n", x);
	a *= 1;
	printf("%d\n", a);
	a /= 1;
	printf("%d\n", a);
	a += 0;
	printf("%d\n", a);
	a -= 0;
	printf("%d\n", a);
	
	return;
}
