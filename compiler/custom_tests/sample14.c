#include <stdio.h>

void main() {
	int a;
	int b;
	
	a = 18;
	b = 958;
	
	switch(a){
		case 18:
		{
			a++;
			if(a ==18){
				printf("%d\n",12);
			}
			else{
				printf("%d\n",13);
			}
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
			if(a ==18){
				a = (a>0)?5:6;
				printf("%d\n",a);
			}
			else{
				a = (a>0)?7:8;
				printf("%d\n",a);
			}	
		}
	}
	return;
}
