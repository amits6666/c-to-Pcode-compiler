#include <stdio.h>

void main() {
	int a;
	int *b;
	
	a = 10;
	b = 5;
	
	if(0){
		a = a + 6;
	} else{
		(*b) = 10*a;
	}
	printf("%d\n",a);
	return;
}
