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

//clock() 함수 사용
void clock_function() {

	start = clock(); //시간 측정 시작

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 10000; j++) {
			sum += i * j;
		}
	}

	end = clock(); //시간 측정 끝
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%f\n", duration);
	return 0;
}

//time()함수 사용
void time_function() {

	start = time(NULL); // 시간 측정 시작

	for (i = 0; i < 500000; i++) {
		for (j = 0; j < 10000; j++) {
			sum += i * j;
		}
	}

	end = time(NULL); // 시간 측정 끝
	duration = (double)(end - start);
	printf("%f\n", duration); //결과 출력
	return 0;
}