#include <stdio.h>

/*#define MAX_ELEMENTS 100
int scores[MAX_ELEMENTS];*/	// �ڷᱸ��

int get_max_score(int scores[], int scores_len) 	// �л��� ���ڴ� n
{
	int i, len, largest;
	largest = scores[0];	// �˰���
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



