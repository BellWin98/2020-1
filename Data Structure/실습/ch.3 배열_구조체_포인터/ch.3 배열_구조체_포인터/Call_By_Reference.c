#include <stdio.h>

void swap(int *x, int *y);

int main() {
	int a = 1, b = 2;
	printf("Before calling swap: a=%d, b=%d\n", a, b);
	swap(&a, &b);
	printf("After calling swap: a=%d, b=%d\n", a, b);
	
	return 0;
}

void swap(int *px, int *py) {
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
}