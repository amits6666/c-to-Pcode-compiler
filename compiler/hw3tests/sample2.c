#include <stdio.h>

void main() {
	int a;
	a = 3;

	switch (a) {
	case 1:
	{
		printf("%d\n", 1);
		break;
	}
	case 2:
	{
		printf("%d\n", 2);
		break;
	}
	}

	switch (1) {
	case 1:
	{
		printf("%d\n", 13 + 12 - 5);
		break;
	}
	case 2:
	{
		printf("%d\n", 2);
		break;
	}
	}

	switch (1 + 1) {
	case 1:
	{
		printf("%d\n", 1);
		break;
	}
	case 2:
	{
		printf("%d\n", 2);
		break;
	}
	}

	switch (16 + 8) {
	case 1:
	{
		printf("%d\n", 1);
		break;
	}
	case 2:
	{
		printf("%d\n", 2);
		break;
	}
	}

	return;
}
