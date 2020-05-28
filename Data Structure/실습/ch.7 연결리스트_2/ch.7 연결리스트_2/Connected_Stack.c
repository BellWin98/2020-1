#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;
typedef struct {
	element data;
	struct StackNode *link;
} StackNode;

typedef struct {
	StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s);
int is_empty(LinkedStackType *s);
int is_full(LinkedStackType *s);
void push(LinkedStackType *s, element item);
void print_stack(LinkedStackType *s);
element pop(LinkedStackType *s);
element peek(LinkedStackType *s);

int main() {
	LinkedStackType *s = (LinkedStackType *)malloc(sizeof(LinkedStackType));
	init(s);
	push(s, 1); print_stack(s);
	push(s, 2); print_stack(s);
	push(s, 3); print_stack(s);
	pop(s); print_stack(s);
	pop(s); print_stack(s);
	
	free(s);
	return 0;
}

void init(LinkedStackType *s) {
	s->top = NULL;
}

int is_empty(LinkedStackType *s) {
	return (s->top == NULL);
}

int is_full(LinkedStackType *s) {
	return 0;
}

void push(LinkedStackType *s, element item) {
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

void print_stack(LinkedStackType *s) {
	for (StackNode *p = s->top; p != NULL; p = p->link) {
		printf("%d->", p->data);
	}
	printf("NULL\n");
}

element pop(LinkedStackType *s) {
	if (is_empty(s)) {
		printf("Stack is empty\n");
		return;
	}
	else {
		StackNode *temp = s->top;
		int data = temp->data;
		s->top = s->top->link;
		free(temp);
		return data;
	}
}

element peek(LinkedStackType *s) {
	if (is_empty(s)) {
		printf("Stack is empty\n");
		return;
	}
	else {
		return s->top->data;
	}
}






