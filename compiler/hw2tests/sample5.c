#include <stdio.h>

void main() {
	int a[1];
	int* b;
	int** c;
	int*** d;

	b = 5;
	c = 6;
	d = 7;
	
	a[0] = 8;
	printf("%d\n",(***d)[0]);
	return;
}
