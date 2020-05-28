#include <stdio.h>

int ack(int m, int n);
int ack2(int m, int n);

int main() {

	printf("%d\n", ack(3, 2));
	printf("%d\n", ack2(3, 2));
	return 0;
}

int ack(int m, int n) {

	if (m == 0) {
		return n + 1;
	}
	
	if (n == 0) {
		return ack(m - 1, 1);
	}

	return ack(m - 1, ack(m, n - 1));
}

int ack2(int m, int n) {

	while (m != 0) {
		if (n == 0) {
			n = 1;
		}
		else {
			n = ack(m, n - 1);
		}
		m = m - 1;
	}
	return n + 1;
}