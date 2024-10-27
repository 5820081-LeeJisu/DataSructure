#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;
typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, *rear;
} LinkedQueueType;

void init(LinkedQueueType* root) {
	root->front = root->rear = NULL;
}

int is_empty(LinkedQueueType* root) {
	return (root->front == NULL);
}

void enqueue(LinkedQueueType* q, element item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = item;
	temp->link = NULL;
	if (is_empty(q)) {
		q->front = temp;
		q->rear = temp;
	}
	else {
		q->rear->link = temp;
		q->rear = temp;
	}
}

element dequeue(LinkedQueueType* q) {
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) {
		exit(1);
	}
	else {
		data = temp->data;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return data;
	}
}

int GetSumOfNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* nptr = root;
	int sum_node = 0;
	init(&q);

	while (nptr != NULL || !is_empty(&q)) {
		while (nptr != NULL) {
			enqueue(&q, nptr); 
			nptr = nptr->left;
		}
		nptr = dequeue(&q); 
		sum_node += nptr->data;
		if (nptr != NULL) {
			nptr = nptr->right;
		}
	}
	return sum_node;
}

int GetNumberOfNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* nptr = root;
	int count = 0;
	init(&q);

	while (nptr != NULL || !is_empty(&q)) {
		while (nptr != NULL) {
			enqueue(&q, nptr);
			nptr = nptr->left;
		}
		nptr = dequeue(&q);
		count++;
		if (nptr != NULL) {
			nptr = nptr->right;
		}
	}
	return count;
}

int power_of_two(int height) {
	int result = 1;
	for (int i = 0; i < height; i++) {
		result *= 2;
	}
	return result;
}

int GetHeightOfTree(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* nptr = root;
	int height = 0;
	init(&q);
	enqueue(&q, nptr);

	if (root == NULL) return 0;

	while (!is_empty(&q)) {
		int level = 0; 
		for (int i = 0; i < power_of_two(height); i++) {
			if (!is_empty(&q)) {
				nptr = dequeue(&q);
				if (nptr->left != NULL) {
					enqueue(&q, nptr->left);
				}
				if (nptr->right != NULL) {
					enqueue(&q, nptr->right);
				}
				level++; 
			}
		}
		if (level > 0) { 
			height++;
		}
	}
	return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* nptr = root;
	int leaf_node = 0;
	init(&q);

	if (root == NULL) return 0;
	enqueue(&q, nptr);
	while (!is_empty(&q)) {
		nptr = dequeue(&q);
		if (nptr->left == NULL && nptr->right == NULL) {
			leaf_node++;
		}
		if (nptr->left != NULL) {
			enqueue(&q, nptr->left);
		}
		if (nptr->right != NULL) {
			enqueue(&q, nptr->right);
		}
	}
	return leaf_node;
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

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);   
	GetNumberOfLeafNodes(root); 

	printf("Sum of nodes: %d\n", GetSumOfNodes(root));
	printf("Number of nodes: %d\n", GetNumberOfNodes(root));
	printf("Height of Tree: %d\n", GetHeightOfTree(root));
	printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root)); 

	free(root);

	return 0;
}