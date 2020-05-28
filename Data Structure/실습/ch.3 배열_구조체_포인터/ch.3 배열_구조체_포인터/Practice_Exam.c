#pragma warning(disable: 4996)
#include <stdio.h>
#define ROWS 3
#define COLS 4

int fsum_1(int a[][COLS]);
int fsum_2(int(*p)[COLS]);
int fsum_3(int *p);

int main() {
	int arr[ROWS][COLS] = { {1,2,3,4}, {5,6,7,8}, {9,10,11,12} };
	int sum1 = fsum_1(arr);
	int sum2 = fsum_2(arr);
	int sum3 = fsum_3(arr[0]);

	printf("sum1 = %d\n", sum1);
	printf("sum2 = %d\n", sum2);
	printf("sum3 = %d\n", sum3);

	return 0;
}

int fsum_1(int a[][COLS]) {
	int sum = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += a[i][j];
		}
	}
	return sum;
}

int fsum_2(int(*p)[COLS]) {
	int sum = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			sum += p[i][j];
		}
	}
	return sum;
}

int fsum_3(int *p) {
	int sum = 0;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++){
			sum += *p++;
		}
	}
	return sum;
}