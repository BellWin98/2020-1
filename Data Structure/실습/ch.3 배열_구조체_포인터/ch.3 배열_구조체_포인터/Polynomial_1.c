#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 101 // 다항식의 최대차수 + 1
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
typedef struct {
	int degree; // 차수
	float coef[MAX_DEGREE];
} polynomial;
//polynomial a = { 5, {10,0,0,0,6,3} }; // 5->degree, 10,0,0,0,6,3->coef 로 초기화

polynomial poly_add1(polynomial A, polynomial B);
void print_poly(polynomial p);

int main() {
	polynomial a = { 5,{3,6,0,0,0,10} };
	polynomial b = { 4, {7,0,5,0,1} };
	polynomial c;
	print_poly(a);
	print_poly(b);
	c = poly_add1(a, b);
	printf("--------------------------------------\n");
	print_poly(c);
	return 0;
}

// C = A+B 여기서 A와 B는 다항식. 구조체가 반환됨.
polynomial poly_add1(polynomial A, polynomial B) {
	polynomial C; // 결과 다항식
	int Apos = 0, Bpos = 0, Cpos = 0; // 배열 인덱스 변수
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree); // 결과 다항식 차수
	while (Apos <= A.degree && Bpos <= B.degree) {
		if (degree_a > degree_b) {
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) {
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			degree_a--;
			degree_b--;
		}
		else {
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}

void print_poly(polynomial p) {
	for (int i = p.degree; i > 0; i--) {
		printf("%3.1fx^%d + ", p.coef[p.degree - i], i);
	}
	printf("%3.1f \n", p.coef[p.degree]);
}


