#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;
typedef struct {
	element data;
	struct DListNode *llink;
	struct DListNode *rlink;
} DListNode;

void init(DListNode *phead);
void print_dlist(DListNode *phead);
void dinsert(DListNode *before, element data);
void ddelete(DListNode *head, DListNode *removed);

int main() {
	DListNode *head = (DListNode *)malloc(sizeof(DListNode));
	init(head);
	printf("추가 단계\n");
	for (int i = 0; i < 5; i++) {
		dinsert(head, i);
		print_dlist(head);
	}

	printf("삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		print_dlist(head);
		ddelete(head, head->rlink);
	}
	free(head);
	return 0;
}

void init(DListNode *phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

void print_dlist(DListNode *phead) {
	DListNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |->", p->data);
	}
	printf("\n");
}

void dinsert(DListNode *before, element data) {
	DListNode *new_node = (DListNode *)malloc(sizeof(DListNode));
	new_node->data = data;
	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before->rlink = new_node;

}

void ddelete(DListNode *head, DListNode *removed) {
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}


