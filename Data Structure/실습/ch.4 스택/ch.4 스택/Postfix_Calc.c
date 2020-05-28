#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
typedef char element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

void init_stack(StackType *s);
int is_empty(StackType *s);
int is_full(StackType *s);
void push(StackType *s, element item);
int pop(StackType *s);
int eval(char exp[]);

int main() {
	int result;
	printf("����ǥ����� 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("������� %d\n", result);
	return 0;
}

void init_stack(StackType *s) {
	s->top = -1;
}

int is_empty(StackType *s) {
	return s->top == -1;
}

int is_full(StackType *s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item) {
	if (is_full(s)) {
		printf("stack is full\n");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}

int pop(StackType *s) {
	if (is_empty(s)) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}

int eval(char exp[]) {
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	StackType s;
	char ch;
	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if ((ch != '+')&&(ch != '-')&&(ch != '*')&&(ch != '/')) {
			value = ch - '0'; // ���ڿ����� ���ڸ� ��¥ ���ڷ� �ٲ��ִ� �۾�
			push(&s, value);
		}
		else { // �������̸� �ǿ����ڸ� ���ÿ��� ����
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) {
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);

}