#include <stdio.h>

int fib(int n);
int fib_iter(int n);
int fib_iter2(int n, int f[]);

int main() {
	int arr[100] = { 0, };
	printf("fib of n: %d\n", fib(6));
	printf("fib_iter of n: %d\n", fib_iter(40));
	printf("fib_iter2 of n: %d\n", fib_iter2(40, arr));
}

int fib(int n) {
		printf("fib(%d) is called\n", n);
	if (n == 0) {
		return 0;
	}
	else if (n == 1) {
		return 0;
	}
	else {
		return fib(n - 1) + fib(n - 2);
	}
}

int fib_iter(int n) {
	if (n == 0) {
		return 0;
	}
	else if (n <= 2) {
		return 1;
	}
	long f0 = 0, f1 = 1, f2 = 1;
	for (int i = 3; i <= n; i++) {
		f0 = f1;
		f1 = f2;
		f2 = f1 + f0;
	}
	return f2;
}

int fib_iter2(int n, int f[]) {
	int i;
	f[n + 1];
	f[0] = 0;
	f[1] = 1;
	if (n >= 2) {
		for (i = 2; i <= n; i++) {
			f[i] = f[i - 1] + f[i - 2];
		}
	}
	return f[n];
}