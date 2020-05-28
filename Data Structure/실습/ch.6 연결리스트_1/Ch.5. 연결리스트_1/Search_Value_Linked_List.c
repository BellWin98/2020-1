#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element data;
	struct ListNode *link;
} ListNode;

ListNode* insert_first(ListNode *head, element value);
void print_list(ListNode *head);
ListNode* search_list(ListNode *head, element x);

int main() {
	ListNode *head = NULL;
	int input_value, search_value;

	printf("Input Number: ");
	scanf("%d", &input_value);
	head = insert_first(head, input_value);
	print_list(head);

	printf("Input Number: ");
	scanf("%d", &input_value);
	head = insert_first(head, input_value);
	print_list(head);
	
	printf("Input Number: ");
	scanf("%d", &input_value);
	head = insert_first(head, input_value);
	print_list(head);

	printf("Number to search: ");
	scanf("%d", &search_value);
	
	if (search_list(head, search_value) != NULL) {
		printf("You found %d in the list\n", search_value);
	}
	else {
		printf("%d is not in the list\n", search_value);
	}

	return 0;
}

ListNode* insert_first(ListNode *head, element value) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

void print_list(ListNode *head) {
	for (ListNode *p = head; p != NULL; p = p->link) {
		printf("%d->", p->data);
	}
	printf("NULL \n");
}

ListNode* search_list(ListNode *head, element x) {
	ListNode *p = head;

	while (p != NULL) {
		if (p->data == x) {
			return p;
		}
		p = p->link;
	}
	return NULL;
}


