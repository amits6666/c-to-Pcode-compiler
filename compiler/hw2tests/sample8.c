#include <stdio.h>

struct B{
	int c;
	int d;
};

struct A{
	struct B b;
};

void main() {
    struct A a;
	struct A e[2][2][2][2][2][2][2][2];


	e[0][1][0][1][0][1][1][0].b.c = 1;
	e[0][1][0][1][0][1][1][0].b.d = 1;
	printf("%d\n",e[0][1][0][1][0][1][1][0].b.c + e[0][1][0][1][0][1][1][0].b.d);

	return;
}
