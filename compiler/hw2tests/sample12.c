#include <stdio.h>

void main() {	
	int a;
	int b;
	
	a = 1;
    while (a < 5){
        b = 1;
        while (b < 10){
            if (a == 3){
				printf("%d\n",b);
                break;
            }
            b = b * 2;
        }
        a = a + 1;
    }
    printf("%d\n",a);
	return;
}
