#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element data;
	struct ListNode *link;
} ListNode;

void print_list(ListNode *head);
ListNode* insert_first(ListNode *head, element data);
ListNode* insert_last(ListNode *head, element data);
int get_length(ListNode *head);
ListNode* search(ListNode *head, element data);

int main() {
	ListNode *head = NULL;

	head = insert_last(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 40);
	head = insert_first(head, 10);
	print_list(head);
	printf("노드의 개수: %d\n", get_length(head));
	if (search(head, 40) != NULL) {
		printf("찾고자 하는 숫자가 리스트안에 존재.\n");
	}

	return 0;
}

void print_list(ListNode *head) {
	ListNode *p;

	if (head == NULL) return;
	p = head->link;
	do {
		printf("%d->", p->data);
		p = p->link;
	} while (p != head);
	printf("%d\n", p->data); // 마지막 노드 출력
}

ListNode* insert_first(ListNode *head, element data) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
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

ListNode* insert_last(ListNode *head, element data) {
	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) {
		head = node;
		node->link = head;
	}
	else {
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

int get_length(ListNode *head) {
	ListNode *p = head;
	int count = 0;
	if (head == NULL) {
		return 0;
	}
	else {
		do {
			if (p->data != NULL) {
				count++;
			}
			p = p->link;
		} while (p != head);
	}
	return count;
}

ListNode* search(ListNode *head, element data) {
	
	/*ListNode *p = L;
	do {
		if (p->data == data) {
			return p;
		}
		p = p->link;
	} while (p != L);
	return NULL;*/
	ListNode *p, *first;
	if (head == NULL) return NULL;
	p = first = head->link;
	do {
		if (p->data == data) return p;
		p = p->link;
	} while (p != first);
	return NULL;
}

