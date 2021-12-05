#include <stdio.h>

void main() {
	int a;
	int b;
	
	a = 18;
	b = 958;
	
	switch(a){
		case 18:
		{
			printf("%d\n",0);
			break;
		}
		case 2:
		{
			printf("%d\n",1);
			break;
		}	
		case 30:
		{
			printf("%d\n",2);
			printf("%d\n",3);
			break;	
		}	
	}
	
	switch(b){
		case 958:
		{
			printf("%d\n",4);
			break;	
		}
	}
	return;
}
