#include <stdio.h>

int get_gcd(int u, int v);
int gcd_modulus(int u, int v);
int gcd_recursion(int u, int v);

int main() {
	int a, b;
	printf("input numbers: ");
	scanf_s("%d %d", &a, &b);
	printf("gcd of %d & %d is: %d\n", a, b, get_gcd(a, b));
	printf("gcd_mod of %d & %d is: %d\n", a, b, gcd_modulus(a, b));
	printf("gcd_rec of %d & %d is: %d\n", a, b, gcd_recursion(a, b));
}

int get_gcd(int u, int v) {
	int temp;
	while (u) {
		if (u < v) {
			temp = u;
			u = v;
			v = temp;
		}
		u = u - v;
	}
	return v;
}

int gcd_modulus(int u, int v) {
	int t;
	while (v) {
		t = u%v;
		u = v;
		v = t;
	}
	return u;
}

int gcd_recursion(int u, int v) {
	if (v == 0) {
		return u;
	}
	else {
		return gcd_recursion(v, u%v);
	}
}