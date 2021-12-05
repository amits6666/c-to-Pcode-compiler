#include <stdio.h>

void main() {
	int a[10][4];
	int b[11];
	int i;

	a[9][2] = 12;
	i = 9;
	b[7] = 2;
	a[5][2] = a[i][b[7]];
	printf("%d\n",a[5][2]);
	return;
}
