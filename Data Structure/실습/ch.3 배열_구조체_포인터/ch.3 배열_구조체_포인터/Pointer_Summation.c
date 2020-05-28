#include <stdio.h>
#define SIZE 6

void get_integers(int list[]);
int cal_sum(int list[]);

int main() {
	int list[SIZE];
	get_integers(list);
	printf("Total Sum: %d\n", cal_sum(list));
	return 0;
}

void get_integers(int list[]) {
	printf("Input 6 integers: ");
	for (int i = 0; i < SIZE; i++) {
		scanf("%d", &list[i]); // list+i�� �ᵵ��
	}
}

int cal_sum(int *p) {
	int sum = 0;
	for (int i = 0; i < SIZE; i++) {
		sum += *(p+i); // p[i], *p++
	}
	return sum;
}