#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int coef;
	int expon;
	struct ListNode *link;
} ListNode;

typedef struct {
	int size;
	ListNode *head;
	ListNode *tail;
} ListType;

void error(char *message);
ListType* create();
void insert_last(ListType *plist, int coef, int expon);
void poly_add(ListType *plist1, ListType *plist2, ListType *plist3);
void poly_print(ListType *plist);

int main() {

}

void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

