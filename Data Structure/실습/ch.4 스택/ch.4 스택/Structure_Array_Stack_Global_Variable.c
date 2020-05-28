#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100 // 스택의 최대크기

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1; // 스택 초기화

int is_empty();
int is_full();
void push(element item);
element pop();

int main() {
	push(1);
	push(2);
	push(3);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;

}

// 공백 상태 검출
int is_empty() {
	return (top == -1);
}

// 포화 상태 검출
int is_full() {
	return (top == (MAX_STACK_SIZE - 1));
}

// 삽입
void push(element item) {
	if (is_full()) {
		printf("stack is full\n");
		return;
	}
	else {
		stack[++top] = item;
	}
}

// 삭제
element pop() {
	if (is_empty()) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return stack[top--];
	}
}