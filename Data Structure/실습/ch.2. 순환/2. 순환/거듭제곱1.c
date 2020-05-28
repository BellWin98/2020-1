#include <stdio.h>

double slow_power(double x, int n); // 시간복잡도: O(n)
double power(double x, int n); // 시간복잡도: O(log n)

int main() {

	printf("value of x: %lf\n", slow_power(3.0, 4));
	printf("value of y: %lf\n", power(3.0, 3));

}

double slow_power(double x, int n) {

	int i;
	double r = 1.0;
	for (i = 0; i < n; i++) {

		r = r*x;

	}
	return r;
}

double power(double x, int n) {
	
	if (n == 0) {
		return 1;
	}
	else if (n % 2 == 0) {
		return power(x*x, n / 2);
	}
	else {
		return x*power(x*x, (n - 1) / 2);
	}
}