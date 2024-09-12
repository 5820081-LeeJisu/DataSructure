#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* tree) {
	int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}
	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int* tree, int i, int index) {
	if (i < index) {
		printf("[%2d]", tree[i]);
		ArrayPreOrder(tree, 2 * i + 1, index);
		ArrayPreOrder(tree, 2 * i + 2, index);
	}
}

void ArrayInOrder(int* tree, int i, int index) {
	if (i < index) {
		ArrayInOrder(tree, 2 * i + 1, index);
		printf("[%2d]", tree[i]);
		ArrayInOrder(tree, 2 * i + 2, index);
	}
}

void ArrayPostOrder(int* tree, int i, int index) {
	if (i < index) {
		ArrayPostOrder(tree, 2 * i + 1, index);
		ArrayPostOrder(tree, 2 * i + 2, index);
		printf("[%2d]", tree[i]);
	}
}

void ArrayOrders(int* tree, int index) {
	printf("1. Array\n");
	printf("전위 순회: ");
	ArrayPreOrder(tree, 0, index);
	printf("\n");
	printf("중위 순회: ");
	ArrayInOrder(tree, 0, index);
	printf("\n");
	printf("후위 순회: ");
	ArrayPostOrder(tree, 0, index);
	printf("\n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	if (direction == 0) {
		node->left = newNode;
	}
	else if (direction == 1) {
		node->right = newNode;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
	if (root != NULL) {
		printf("[%2d]", root->data);
		LinkPreOrder(root->left);
		LinkPreOrder(root->right);
	}
}

void LinkInOrder(TreeNode* root) {
	if (root != NULL) {
		LinkInOrder(root->left);
		printf("[%2d]", root->data);
		LinkInOrder(root->right);
	}
}

void LinkPostOrder(TreeNode* root) {
	if (root != NULL) {
		LinkPostOrder(root->left);
		LinkPostOrder(root->right);
		printf("[%2d]", root->data);
	}
}

void LinkOrders(TreeNode* root) {
	printf("2. Link\n");
	printf("전위 순회: ");
	LinkPreOrder(root);
	printf("\n");
	printf("중위 순회: ");
	LinkInOrder(root);
	printf("\n");
	printf("후위 순회: ");
	LinkPostOrder(root);
	printf("\n");
}

int main() {
	int arr[15];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL; 
	root->right = NULL; 

	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	ArrayOrders(arr, 15);
	LinkOrders(root);

	free(root);

	return 0;
}
