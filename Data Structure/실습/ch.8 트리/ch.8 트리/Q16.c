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

int get_count_one_child(TreeNode* root);

int main() {

	printf("자식노드 하나만 있는 노드의 개수: %d\n", get_count_one_child(root));
	return 0;
}

int get_count_one_child(TreeNode* root) {
	if (root == NULL) return 0;
	int count = 0;
	if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
		count++;
	count = count + get_count_one_child(root->left) + get_count_one_child(root->right);
	return count;
}
