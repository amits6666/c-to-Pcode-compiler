#include <stdio.h>

struct D{
	int e[20];
	struct D* p;
};

struct B{
	struct D* c;
	struct D d;
};

struct A{
	int i;
	struct B b;
};

void main() {
	struct A a;

    a.b.d.p = &(a.b.d);
	a.i = 0;
	while (a.i < 20) {
        a.b.d.e[a.i] = a.i;
        a.i = a.i + 1;
    }

    printf("%d\n", (*(a.b.d.p)).e[a.i-1]);
	return;
}
