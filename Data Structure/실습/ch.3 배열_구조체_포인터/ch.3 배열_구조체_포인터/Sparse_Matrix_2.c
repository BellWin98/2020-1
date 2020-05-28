#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101
typedef struct {
	int row;
	int col;
	int value;
} element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows; // 행의 개수
	int cols; // 열의 개수
	int terms; // 항의 개수(0이아닌 요소의 개수)
} SparseMatrix;

SparseMatrix matrix_transpose2(SparseMatrix a);
void matrix_print(SparseMatrix a);

int main() { // 필기되어있는 행렬 그림 참고(ch.3 배열구조체포인터_4)
	SparseMatrix m = {
		{{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}},
		6,
		6,
		7
	};
	SparseMatrix result;
	result = matrix_transpose2(m); // 행 우선
	matrix_print(result);
	return 0;
}

SparseMatrix matrix_transpose2(SparseMatrix a) {
	SparseMatrix b;
	int bindex; // 행렬 b에서 현재 저장 위치
	b.rows = a.cols;
	b.cols = a.rows;
	b.terms = a.terms;
	if (a.terms > 0) {
		bindex = 0; // 1차원 배열에서의 index
		for (int c = 0; c < a.cols; c++) {
			for (int i = 0; i < a.terms; i++) {
				if (a.data[i].col == c) {
					b.data[bindex].row = a.data[i].col;
					b.data[bindex].col = a.data[i].row;
					b.data[bindex].value = a.data[i].value;
					bindex++;
				}
			}
		}
	}
	return b;
}

void matrix_print(SparseMatrix a) {
	printf("========================================\n");
	for (int i = 0; i < a.terms; i++) {
		printf("(%d, %d, %d) \n", a.data[i].row, a.data[i].col, a.data[i].value);
	}
	printf("========================================\n");
}
