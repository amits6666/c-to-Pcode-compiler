#include <stdio.h>

void main() {
	int i;

	i = 1;
	do {
		printf("%d\n", i);
		i = i + 1;
	}while (i < 10);
	return;
}