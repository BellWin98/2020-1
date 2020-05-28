#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#pragma warning(disable: 4996)

typedef struct {
	int data;
	struct TreeNode *left, *right;
} TreeNode;

//			15
//		4		20
//	 1		 16	   25
#define SIZE 100
int top = -1;
TreeNode *stack[SIZE];

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;

void push(TreeNode *p);
TreeNode* pop();
int inorder_sum(TreeNode *root);
int get_sum(TreeNode* root);

int main() {

	printf("³ëµå ÃÑÇÕ: %d\n", get_sum(root));
	return 0;
}

void push(TreeNode *p) {
	if (top < SIZE - 1) {
		stack[++top] = p;
	}
}

TreeNode* pop() {
	TreeNode *p = NULL;
	if (top >= 0) {
		p = stack[top--];
	}
	return p;
}

int inorder_sum(TreeNode *root) {
	int sum = 0;
	int temp;
	while (1) {
		for (; root; root = root->left) {
			push(root);
		}
		root = pop();
		if (!root) break;
		temp = root->data;
		sum += temp;
		root = root->right;
	}
	return sum;
}

int get_sum(TreeNode* root) {
	if (root == NULL)
		return 0;
	int sum = root->data;
	sum = sum + get_sum(root->left) + get_sum(root->right);
	return sum;
}