#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	clock_t start, end;
	double duration;
	int i, j;
	int sum = 0;

	start = clock(); //�ð� ���� ����

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 10000; j++) {
			sum += i * j;
		}
	}

	end = clock(); //�ð� ���� ��
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%f\n", duration);
	return 0;
}
