#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

typedef struct {
	StackType s1, s2;
} QueueType;


void init_stack(StackType *s);
int is_empty(StackType *s);
int is_full(StackType *s);
void Stack_push(StackType *s, element item);
element Stack_pop(StackType *s);
void Queue_init(QueueType *q);
void Queue_push(QueueType *q, int item);
int Queue_pop(QueueType *q);


int main() {

	QueueType *q;
	q = (QueueType *)malloc(sizeof(QueueType));

	Queue_init(q);
	Queue_push(q, 5);
	Queue_push(q, 4);
	Queue_push(q, 3);
	printf("%d\n", Queue_pop(q));
	printf("%d\n", Queue_pop(q));
	printf("%d\n", Queue_pop(q));

	free(q);
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

void Stack_push(StackType *s, element item) {
	if (is_full(s)) {
		printf("stack is full\n");
		return;
	}
	else {
		s->data[++(s->top)] = item;
	}
}

element Stack_pop(StackType *s) {
	if (is_empty(s)) {
		printf("stack is empty\n");
		exit(1);
	}
	else {
		return s->data[(s->top)--];
	}
}

void Queue_init(QueueType *q) {
	q->s1.top = -1;
	q->s2.top = -1; 
}

void Queue_push(QueueType *q, int item) {
	Stack_push(&(q->s1), item);
	return;
}

int Queue_pop(QueueType *q) {
	if (is_empty(&(q->s2))) {
		while (!is_empty(&(q->s1))) {
			Stack_push(&(q->s2), Stack_pop(&(q->s1)));
		}
	}
	return Stack_pop(&(q->s2));
}