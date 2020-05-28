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
void matchNum(StackType *s);

int main() {
	StackType *s;
	s = (StackType *)malloc(sizeof(StackType));
	init_stack(s);
	printf("¼ö½Ä: ");
	scanf("%s", s->data);
	matchNum(s);
	free(s);
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

void matchNum(StackType *s) {
	
	int count = 1;
	int i = 0;
	while (s->data[i]!=NULL) {
		if (s->data[i] == '(') {
			push(s, count);
			printf("%d ", count);
			count++;
		}
		else if (s->data[i] == ')') {
			printf("%d ", pop(s));
		}
		else {
			printf("°ýÈ£°¡ ¾Æ´Õ´Ï´Ù. \n");
			break;
		}
		i++;
	}
}