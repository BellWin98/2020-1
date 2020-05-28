#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

struct {
	float coef;
	int expon;
}terms[MAX_TERMS] = { {8,3},{7,1},{1,0},{10,3},{3,2},{1,0} };
int avail=6;

char compare(int a, int b);
void attach(float coef, int expon);
void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce);
void print_poly(int s, int e);

int main() {
	int As = 0, Ae = 2, Bs = 3, Be = 5, Cs, Ce; // As: A배열의 시작, Ae: A배열의 끝
	poly_add2(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	printf("------------------------------------------\n");
	print_poly(Cs, Ce);
	return 0;
}

// 두 개의 정수를 비교
char compare(int a, int b) {
	if (a > b) {
		return '>';
	}
	else if (a == b) {
		return '==';
	}
	else {
		return '<';
	}
}

void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "항의 개수가 너무 많음\n");
		exit(1);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}

void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce) { // C는 값이 변화(A+B)하기 때문에 포인터형식. 
	float tempcoef;
	*Cs = avail;
	while (As <= Ae&&Bs <= Be) {
		switch (compare(terms[As].expon,terms[Bs].expon)){
		case '>': // A의 차수 > B의 차수
			attach(terms[As].coef, terms[As].expon);
			As++;
			break;
		case '=': // A의 차수 == B의 차수
			tempcoef = terms[As].coef + terms[Bs].coef;
			if (tempcoef) {
				attach(tempcoef, terms[As].expon);
				As++;
				Bs++;
				break;
			}
		case '<': // A의 차수 < B의 차수
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++;
			break;
		}
	}
	// A의 나머지 항들을 이동함
	for (; As <= Ae; As++) {
		attach(terms[As].coef, terms[As].expon);
	}
	// B의 나머지 항들을 이동함
	for (; Bs <= Be; Bs++) {
		attach(terms[Bs].coef, terms[Bs].expon);
	}
	*Ce = avail - 1;
}

void print_poly(int s, int e) {
	for (int i = s; i < e; i++) {
		printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
	}
	printf("%3.1fx^%d\n", terms[e].coef, terms[e].expon);
}