#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 6
typedef struct {
	short r;
	short c;
} element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

element here = { 1,0 }, entry = { 1,0 };
char maze[MAZE_SIZE][MAZE_SIZE] = {
	{ '1','1','1','1','1','1' },
	{ 'e','0','1','0','0','1' },
	{ '1','0','0','0','1','1' },
	{ '1','0','1','0','1','1' },
	{ '1','0','1','0','0','x' },
	{ '1','1','1','1','1','1' },
};

void init_stack(StackType *s);
int is_empty(StackType *s);
int is_full(StackType *s);
void push(StackType *s, element item);
element pop(StackType *s);
element peek(StackType *s);
void push_loc(StackType *s, int r, int c);
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]);

int main() {
	int i = 0, r, c;
	StackType *s;
	s = (StackType *)malloc(sizeof(StackType));
	init_stack(s);
	here = entry;
	element road[MAX_STACK_SIZE] = {""};
	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;
		maze[r][c] = '.'; // 지나온 길
		road[i].r = r; // 경로 저장
		road[i++].c = c;
		maze_print(maze);
		push_loc(s, r - 1, c);
		push_loc(s, r + 1, c);
		push_loc(s, r, c - 1);
		push_loc(s, r, c + 1);
		
		if (is_empty(s)) {
			printf("실패\n");
			return;
		}
		else {
			here = pop(s);
		}
	}
	for (int k = 0; k < i; k++)
		printf("경로 : [%d %d] \n", road[k].r, road[k].c);

	printf("성공\n");
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

void push_loc(StackType *s, int r, int c) {
	if (r < 0 || c < 0) {
		return;
	}
	if (maze[r][c] != '1'&&maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

