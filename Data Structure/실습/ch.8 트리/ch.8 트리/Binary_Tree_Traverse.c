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

void inorder(TreeNode *root);
void preorder(TreeNode *root);
void postorder(TreeNode *root);
int get_node_count(TreeNode *node);
int get_leaf_count(TreeNode *node);
int get_height(TreeNode *node);

int main() {
	printf("중위 순회 = ");
	inorder(root);
	printf("\n");

	printf("전위 순회 = ");
	preorder(root);
	printf("\n");

	printf("후위 순회 = ");
	postorder(root);
	printf("\n");

	printf("노드의 개수: %d\n", get_node_count(root));
	printf("단말노드의 개수: %d\n", get_leaf_count(root));
	printf("트리의 높이: %d\n", get_height(root));
	return 0;
}

void inorder(TreeNode *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->data);
		inorder(root->right);
	}
}

void preorder(TreeNode *root) {
	if (root != NULL) {
		printf("[%d] ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(TreeNode *root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("[%d] ", root->data);
	}
}

int get_node_count(TreeNode *node) {
	int count = 0;
	if (node != NULL) {
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	}
	return count;
}

int get_leaf_count(TreeNode *node) {
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) {
			return 1;
		}
		else {
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
		}
	}
	return count;
}

int get_height(TreeNode *node) {
	int height = 0;
	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	}
	return height;
}