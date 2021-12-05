#include <stdio.h>

void main() {
	int a[2];
	int b[2][2];
    int i;
	int j;

    i = 0;
    while (i < 2) {
        j = 0;
        while (j < 2) {
            b[i][j] = (i+1)*50+(j+1)*20;
            j = j + 1;
        }
        i = i + 1;
    }
	printf("%d\n", b[0][0] + b[1][1]);
	return;
}
