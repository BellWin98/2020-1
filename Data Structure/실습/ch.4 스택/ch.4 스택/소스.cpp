#include<stdio.h>
#define MAX_SIZE 100

typedef struct Stacktype {
	char stack[MAX_SIZE];
	int top;
};

void Stack_init(Stacktype* s) {
	s->top = -1;
}

void Stack_push(Stacktype* s, char item) {
	s->stack[++(s->top)] = item;
	return;
}

bool is_empty(Stacktype* s) {
	return s->top == -1;
}

int Stack_pop(Stacktype* s) {
	char t = s->stack[s->top];
	s->stack[s->top] = 0;
	s->top--;
	return t;
}

int main(void) {
	printf("정수를 입력하시오. : ");
	char input[MAX_SIZE];
	scanf_s("%s", input, sizeof(input));

	Stacktype s1, s2;
	Stack_init(&s1);
	Stack_init(&s2);

	int i = 0, count = 0;
	while (input[i] != NULL) {
		count = 0;
		char now = input[i++];
		count++;
		while (now == input[i] || now + ('A' - 'a') == input[i] || now - ('A' - 'a') == input[i]) {
			count++;
			i++;
		}
		Stack_push(&s1, count + '0');
		if ('a' <= now && now <= 'z')
			Stack_push(&s1, now);
		else
			Stack_push(&s1, now - ('A' - 'a'));
	}

	while (!is_empty(&s1)) {
		Stack_push(&s2, Stack_pop(&s1));
	}
	printf("출력 : ");
	while (!is_empty(&s2)) {
		printf("%c", Stack_pop(&s2));
	}
	return 0;
}