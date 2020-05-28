#include <stdio.h>

/*#define MAX_ELEMENTS 100
int scores[MAX_ELEMENTS];*/	// 자료구조

int get_max_score(int scores[], int scores_len) 	// 학생의 숫자는 n
{
	int i, len, largest;
	largest = scores[0];	// 알고리즘
	len = scores_len / sizeof(int);

	for (i = 1; i<len; i++) {
		if (scores[i] > largest) {
			largest = scores[i];
		}
	}
	return largest;
}

int main(void) {
	int num[] = {48, 26, 34 ,5, 60, 85, 32, 5};

	printf("%d\n", get_max_score(num, sizeof(num)));


	return 0;

}



