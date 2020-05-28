#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	time_t start, end;
	double duration;
	int i, j;
	int sum = 0;

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
