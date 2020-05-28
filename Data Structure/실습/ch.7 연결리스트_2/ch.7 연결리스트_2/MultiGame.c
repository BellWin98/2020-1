#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[100];
typedef struct {
	element data;
	struct ListNode *link;
} ListNode;

ListNode* insert_first(ListNode *head, element data);

int main() {
	ListNode *head = NULL;
	head = insert_first(head, "Kim");
	head = insert_first(head, "Han");
	head = insert_first(head, "Lee");

	ListNode *p = head;
	for (int i = 0; i < 10; i++) {
		printf("현재차례 = %s\n", p->data);
		p = p->link;
	}

	return 0;
}

ListNode* insert_first(ListNode *head, element data) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	strcpy(node->data, data);
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
	}
	return head; // 변경된 헤드 포인터 반환
}