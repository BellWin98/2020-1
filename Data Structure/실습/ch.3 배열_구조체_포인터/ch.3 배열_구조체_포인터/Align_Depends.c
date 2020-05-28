#include <stdio.h>
#include <stdlib.h>

// 같은 자료형끼리 선언해주는게 메모리 절약!
struct AlignDepends {
	char c; // packing 3 more bytes
	int i;
};

struct AlignDepends2 {
	char c1; // packing 3 more bytes
	int i;
	char c2; // packing 3 more bytes
};

struct AlignDepends3 {
	char c1, c2; // packing 2 more bytes
	int i;
};

int main() {
	// size_t는 '이론상 가장 큰 사이즈를 담을 수 있는 unsigned 데이터 타입'으로 정의된다.
	// 즉, 32비트 머신에서는 32비트 사이즈의 unsigned 정수형(int가 아니라 그냥 '정수'를 의미한다)
	// 64비트 머신에서는 64비트 사이즈의 unsigned 정수형(unsigned long long)이다. 
	// 향후 등장할지도 모르는 128비트 머신이라던가 더 큰 머신이 존재한다면 그에 따라 더 큰 사이즈가 될 것이다.
	// 이 내용은, 동영상 파일같이 4기가를 넘어가는 파일들을 처리하거나 큰 데이터를 처리하려 할 때 이 사실을 반드시 알고 있는게 좋다.
	// 어설프게 unsigned int인줄 알고 int나 unsigned int로 형변환을 해서 사용하다가 범위를 벗어나는 버그를 발생시킬 가능성도 있기 때문이다.

	size_t i = sizeof(int);
	size_t size = sizeof(struct AlignDepends);
	size_t size2 = sizeof(struct AlignDepends2);
	size_t size3 = sizeof(struct AlignDepends3);
	printf("%d\n", i);
	printf("%d\n", size);
	printf("%d\n", size2);
	printf("%d\n", size3);
	return 0;
}