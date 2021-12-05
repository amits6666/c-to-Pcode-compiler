#include <stdio.h>

void main() {
	int i;
	int j;
	int b;
	
	i = 5;
    while (i > 0) {
        j = 1;
        while (j < i) {
            printf("%d\n", j++);
        }
        i = i-1;
    }
	
    if (0){
        printf("%d\n", 15);
    }
	
    if (1) {
        printf("%d\n", 42);
    } else {
        printf("%d\n", 16);
    }
	
    switch (55) {
        case 1:
		{
			printf("%d\n", 0); 
			break;
		}
            
		case 55:
		{
			break;
		}
			
		case -8:
		{
			printf("%d\n", 1); 
			printf("%d\n", 2); 
			break;
		}
			
    }
	
    i = (5*6)+0;
    i *= -1;
    printf("%d\n", i); 
    b = 1;
    b = !b;
    b = b || (i < 0);
    printf("%d\n", b); 
	
	return;
}
