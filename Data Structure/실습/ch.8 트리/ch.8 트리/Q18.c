#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
	element key;
	struct TreeNode *left, *right;
} TreeNode;

TreeNode* new_node(int item);
TreeNode* insert_node(TreeNode *node, int key);
void inorder(TreeNode *root);

int main() {

	TreeNode *root = NULL;
	int arr[11] = { 11,3,4,1,56,5,6,2,98,32,23 };
	int size = sizeof(arr) / sizeof(int);

	for (int i = 0; i < size; i++) {
		root = insert_node(root, arr[i]);
	}

	inorder(root);

	return 0;

}

TreeNode* new_node(int item) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode *node, int key) {
	if (node == NULL) return new_node(key);

	if (key < node->key) {
		node->left = insert_node(node->left, key);
	}
	else if (key > node->key) {
		node->right = insert_node(node->right, key);
	}

	return node;
}

void inorder(TreeNode *root) {
	if (root != NULL) {
		inorder(root->left);
		// root->key++;
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}
