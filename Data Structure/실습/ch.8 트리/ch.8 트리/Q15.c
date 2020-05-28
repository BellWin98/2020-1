#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

//			15
//		4		20
//	 1		 16	   25


TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;

void find_smaller_than_value(TreeNode *root, int value);

int main() {

	int value;

	printf("값을 입력하시오: ");
	scanf("%d", &value);
	find_smaller_than_value(root, value);

	return 0;
}

void find_smaller_than_value(TreeNode *root, int value) {
	if (root == NULL) return;
	if (root->data < value) {
		printf("%d보다 작은 노드: %d\n", value, root->data);
	}
	find_smaller_than_value(root->left, value);
	find_smaller_than_value(root->right, value);
}
