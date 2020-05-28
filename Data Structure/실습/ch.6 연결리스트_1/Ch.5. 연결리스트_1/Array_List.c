#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
	element array[MAX_LIST_SIZE];
	int size;
} ArrayListType;

void error(char *message);
void init(ArrayListType *L);
int is_empty(ArrayListType *L);
int is_full(ArrayListType *L);
element get_entry(ArrayListType *L, int pos);
void print_list(ArrayListType *L);
void insert_last(ArrayListType *L, element item);
void insert(ArrayListType *L, int pos, element item);
element delete(ArrayListType *L, int pos);

int main() {
	ArrayListType *list;
	list = (ArrayListType *)malloc(sizeof(ArrayListType));
	init(list);
	insert(list, 0, 10); print_list(list);
	insert(list, 0, 20); print_list(list);
	insert(list, 0, 30); print_list(list);
	insert_last(list, 40); print_list(list);
	printf("%d\n", get_entry(list, 3));
	delete(list, 0); print_list(list);

	free(list);
	return 0;
}

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(ArrayListType *L) {
	L->size = 0;
}

int is_empty(ArrayListType *L) {
	return L->size == 0;
}

int is_full(ArrayListType *L) {
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType *L, int pos) {
	if (pos < 0 || pos >= L->size) {
		error("Location error");
	}
	return L->array[pos];
}

void print_list(ArrayListType *L) {
	int i;
	for (i = 0; i < L->size; i++) {
		printf("%d->", L->array[i]);
	}
	printf("\n");
}

void insert_last(ArrayListType *L, element item) {
	if (L->size >= MAX_LIST_SIZE) {
		error("List Overflow");
	}
	L->array[L->size++] = item;
}

void insert(ArrayListType *L, int pos, element item) {
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = L->size - 1; i >= pos; i--) {
			L->array[i + 1] = L->array[i];
		}
		L->array[pos] = item;
		L->size++;
	}
}

element delete(ArrayListType *L, int pos) {
	element temp;

	if (pos < 0 || pos >= L->size) {
		error("Location Error");
	}
	temp = L->array[pos];
	for (int i = pos + 1; i < L->size; i++) {
		L->array[i - 1] = L->array[i];
	}
	L->size--;
	return temp;
}