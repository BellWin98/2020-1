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

// ����Ʈ��
/*TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };*/

// ����Ʈ�� X
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 35, NULL, NULL };
TreeNode n4 = { 30, NULL, &n3 };
TreeNode n5 = { 16, NULL, NULL };
TreeNode n6 = { 25, NULL, &n4 };
TreeNode n7 = { 20, &n5, &n6 };
TreeNode n8 = { 15, &n2, &n7 };

TreeNode *root = &n8;

int get_height(TreeNode *node);
int isBalanced(TreeNode* node);

int main() {

	printf("Ʈ���� ����: %d\n", get_height(root));
	if (isBalanced(root)) {
		printf("����Ʈ�� �Դϴ�.\n");
	}
	else {
		printf("����Ʈ���� �ƴմϴ�.\n");
	}
	return 0;
}

int get_height(TreeNode *node) {
	int height = 0;
	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	}
	return height;
}

int isBalanced(TreeNode *node) {
	if (node == NULL)
		return 1;
	int leftHeight = get_height(node->left);
	int rightHeight = get_height(node->right);
	//���� ����Ʈ���� �����ʼ���Ʈ���� �������� 2�̻� ���� �ʰ� �� �� ������ �������� ��� ��
	if ((leftHeight - rightHeight <= 1) && (leftHeight - rightHeight >= -1)) {
		return 1;
	}
	return 0;
}