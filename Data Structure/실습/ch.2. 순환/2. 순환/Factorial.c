#include <stdio.h>

int factorial(int n);
int factorial_iter(int n);

int main() {
	
	printf("Fac value: %d\n", factorial(5));
	printf("Fac_iter value: %d\n", factorial_iter(5));
	return 0;
}

int factorial(int n) {
	if (n <= 1) {
		return 1;
	}
	else {
		return (n*factorial(n - 1));
	}
}

int factorial_iter(int n) {
	int i, value = 1;
	for (i = n; i > 0; i--) {
		value = value*i;
	}
	return value;
}