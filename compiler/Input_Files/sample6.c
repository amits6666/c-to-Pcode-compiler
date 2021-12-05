#include <stdio.h>

void main() {
	double a;

	a = 5.5;
	printf("%d\n", !5.18);
	printf("%d\n",(((a < 6.0) || (a > 7.0)) && (a == 6.0)) || 0);
	printf("%d\n",(((a <= 6.0) || (a >= 7.0)) && (a != 6.0)) || 8.8);
	printf("%f\n", - a);
	printf("%f\n", ((a + 6.5) - 6.5) * 6.5 / 6.5);
	return;
}