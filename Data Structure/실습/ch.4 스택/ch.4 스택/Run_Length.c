#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
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
element pop(StackType *s);
element peek(StackType *s);
void runLength(StackType *s1, StackType *s2, element *ch);

int main() {
	StackType *s1, *s2;
	s1 = (StackType *)malloc(sizeof(StackType));
	s2 = (StackType *)malloc(sizeof(StackType));
	init_stack(s1);
	init_stack(s2);
	element ch[MAX_STACK_SIZE] = "";
	printf("문자열을 입력하시오: ");
	scanf("%s", ch);
	runLength(s1, s2, ch);

	free(s1);
	free(s2);
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

element pop(StackType *s) {
	if (is_empty(s)) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}

element peek(StackType *s) {
	if (is_empty(s)) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return s->data[s->top];
	}
}
void runLength(StackType *s1, StackType *s2, element *ch) {
	
	int i = 0, count = 0;
	while (ch[i] != '\0') {
		count = 0;
		char now = ch[i++];
		count++;
		while (now == ch[i] || now + ('A' - 'a') == ch[i] || now - ('A' - 'a') == ch[i]) {
			count++;
			i++;
		}
		push(s1, count + '0');
		if ('a' <= now && now <= 'z')
			push(s1, now);
		else
			push(s1, now - ('A' - 'a'));
	}

	while (!is_empty(s1)) {
		push(s2, pop(s1));
	}
	printf("압축된 문자열 : ");
	while (!is_empty(s2)) {
		printf("%c", pop(s2));
	}
	printf("\n");

}

