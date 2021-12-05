#include <stdio.h>

void main() {
	double i;
	double j;
	double k;
	
	i = 10.0;
	j = 5.0;
	k = 3.0;
	while (i >= 0) {
		k = k + 2.0;
		if (k > i) {
			while (j <= 10.0) {
				j = j + 1.0;
				printf("%f\n", j);
			}
		}
		else {
			k = k - 1.0;
		};
		i = i - 1.0;
		printf("%f\n", i);
	}
	return;
}