#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	time_t start, end;
	double duration;
	int i, j;
	int sum = 0;

	start = time(NULL); // �ð� ���� ����

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 10000; j++) {
			sum += i * j;
		}
	}

	end = time(NULL); // �ð� ���� ��
	duration = (double)(end - start);
	printf("%f\n", duration); //��� ���
	return 0;
}
