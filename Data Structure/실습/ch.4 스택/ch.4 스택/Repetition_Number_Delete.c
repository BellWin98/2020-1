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
void repetionNumberDelete(StackType *s1, StackType *s2, element *ch);

int main() {
	StackType *s1, *s2;
	s1 = (StackType *)malloc(sizeof(StackType));
	s2 = (StackType *)malloc(sizeof(StackType));
	init_stack(s1);
	init_stack(s2);
	element ch[MAX_STACK_SIZE] = "";
	printf("정수를 입력하시오: ");
	scanf("%s", ch);
	repetionNumberDelete(s1, s2, ch);
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

void repetionNumberDelete(StackType *s1, StackType *s2, element *ch) {
	int i = 0;

	while (ch[i] != '\0') {
		if (ch[i] != ch[i+1]) {
			push(s1->data, ch[i]-'0'); // if ch[i] == '1' then ch[i]-'0' is actual 1
		}
		i++;
	}
	while (!is_empty(s1)) {
		push(s2, pop(s1));
	}
	printf("출력 : ");
	while (!is_empty(s2)) {
		printf("%d", pop(s2));
	}
	printf("\n");
}