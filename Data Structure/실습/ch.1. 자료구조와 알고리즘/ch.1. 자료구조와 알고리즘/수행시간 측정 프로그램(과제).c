#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, end;
double duration;
int i, j;
int sum = 0;

void clock_function();
void time_function();

int main(void) {
	clock_function();
	time_function();
}

//clock() �Լ� ���
void clock_function() {

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

//time()�Լ� ���
void time_function() {

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