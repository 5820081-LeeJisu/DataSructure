#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount, searchCount;

typedef struct Node {
	int key;
	struct Node* left, * right;
	int height;
} Node;

// ��� ����
Node* createNode(int key) {
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

// ����� ���� ���ϱ�
int getHeight(Node* nptr) {
	if (nptr == (Node*)NULL) 
		return 0;
	else 
		return nptr->height;
}

// ����� ���� �μ� ���ϱ� (���� ���� Ʈ���� ���� - ������ ���� Ʈ���� ����)
int getBalance(Node* nptr) {
	return getHeight(nptr->left) - getHeight(nptr->right);
}

// ���� Ʈ���� ����� ���� ȸ��
// ���������� ȸ�� 
Node* rotateRight(Node* y) {
	Node* x = y->left;
	Node* T3 = x->right;

	x->right = y;
	y->left = T3;

	y->height = 1 + (getHeight(y->left) > getHeight(y->right))
		? getHeight(y->left) : getHeight(y->right);

	x->height = 1 + (getHeight(x->left) > getHeight(x->right))
		? getHeight(x->left) : getHeight(x->right);

	return x;
}

// �������� ȸ��
Node* rotateLeft(Node* y) {
	Node* x = y->right;
	Node* T2 = x->left;

	x->left = y;
	y->right = T2;

	y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
		? getHeight(y->left) : getHeight(y->right)); 

	x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
		? getHeight(x->left) : getHeight(x->right));

	return x;
}

// AVLƮ���� �� Ž�� �Լ�
Node* search_AVL(Node* root, int key) {
	if (root == NULL) {
		compareCount++;
		return NULL;
	}
	
	compareCount++;
	if (root->key == key) {
		return root;
	}

	compareCount++;
	if (key > root->key) {
		return search_AVL(root->right, key);
	}
	else {
		return search_AVL(root->left, key);
	}
}

// ���� Ž�� Ʈ���� �� Ž�� Ʈ��
Node* search_binary(Node* root, int key) { 
	if (root == NULL) {
		compareCount++;
		return NULL;
	}

	compareCount++;
	if (root->key == key) {
		return root;
	}

	compareCount++;
	if (key > root->key) {
		return search_binary(root->right, key);
	}
	else {
		return search_binary(root->left, key);
	}
}

// AVLƮ���� ���� 
Node* insertNode_AVL(Node* root, int key) {
	if (root == NULL) {
		return createNode(key);
	}

	if (root->key > key) {
		root->left = insertNode_AVL(root->left, key);
	}
	else if (root->key < key) {
		root->right = insertNode_AVL(root->right, key);
	}
	else {
		return root;
	}

	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left) : getHeight(root->right));

	int balance = getBalance(root);

	if (balance >= 2) {	// �뷱���� ���� ��
		// LL ȸ��: ���������� ȸ��
		if (getBalance(root->left) >= 0) {
			return rotateRight(root);
		}
		// LR ȸ��: ���� ȸ�� --> ������ ȸ��
		else /*if (getBalance(root->left) < 0)*/ {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		//else;
	}
	// RR ȸ��: �������� ȸ��
	else if (balance <= -2) {
		if (getBalance(root->right) < 0) {
			return rotateLeft(root);
		}
		// RL ȸ��: ������ ȸ�� --> ���� ȸ��
		else {
			root->right = rotateRight(root->right); 
			rotateLeft(root); 
		}
	}
	else {
		return root;
	}
}

// Ʈ������ �ּҰ� ��� ã��
Node* getMinValueNode(Node* node) {
	Node* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// AVLƮ���� ����
Node* deleteNode_AVL(Node* root, int key) {
	// 1. �Ϲ� ���� Ž�� Ʈ�� ����
	if (root == NULL) {
		return root;
	}
	if (key < root->key) {
		root->left = deleteNode_AVL(root->left, key);
	}
	else if (key > root->key) {
		root->right = deleteNode_AVL(root->right, key);
	}
	else {
		// ��� ����
		if ((root->left == NULL) || (root->right == NULL)) { // �ڽ� ��尡 �Ѱ�
			Node* temp = root->left ? root->left : root->right; // �� �ڽĳ�带 temp�� ����Ŵ

			if (temp == NULL) { // �ڽ� ��尡 ����
				temp = root; // �޸� ������ ��
				root = NULL;  // ����(�ǵ��� �� ��)
			}
			else { // �ڽ� ��尡 �ϳ� ����
				*root = *temp; // �ϳ� �ִ� �ڽ��� �θ�� ��ġ��
			}
			free(temp);
		}
		else {
			// ������ ����Ʈ������ �ּҰ� ��� ã��
			Node* temp = getMinValueNode(root->right);
			root->key = temp->key; // Ű���� ������
			root->right = deleteNode_AVL(root->right, temp->key); // ���� �� �ּҰ��� ���� ��� ����
		}
	}

	if (root == NULL) {
		return root;
	}

	// 2. ��� ���� ����
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left) : getHeight(root->right));

	// 3. ���� �μ� ���
	int balance = getBalance(root);

	// 4. ���� ���� ȸ�� ����
	// R ȸ��
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rotateRight(root);
	}

	// LR ȸ��
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	// L ȸ��
	if (balance < -1 && getBalance(root->right) <= 0) {
		return rotateLeft(root);
	}

	// RL ȸ��
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}

// ���� Ž�� Ʈ���� ���� (AVL���� ȸ���� ���� ��)
Node* insertNode_binary(Node* root, int key) {
	if (root == NULL) 
		return createNode(key);

	if (root->key > key)
		root->left = insertNode_binary(root->left, key);
	else if (root->key < key)
		root->right = insertNode_binary(root->right, key);

	return root;
}

// ���� Ž�� Ʈ���� ���� (AVL���� ȸ���� ���� ��)
Node* deleteNode_binary(Node* root, int key) {
	if (root == NULL) 
		return root;

	if (key < root->key) 
		root->left = deleteNode_binary(root->left, key);
	else if (key > root->key) 
		root->right = deleteNode_binary(root->right, key);
	else {
		if (root->left == NULL) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			Node* temp = root->left;
			free(root);
			return temp;
		}

		Node* temp = getMinValueNode(root->right);
		root->key = temp->key;
		root->right = deleteNode_binary(root->right, temp->key); 
	}
	
	return root;
}

Node* doAVLBatch(Node *root) {
	for (int i = 0; i < 2000; i++) {
		int key = rand() % SIZE;
		int a = rand() % 3;
		switch (a) {
		case 0: 
			root = insertNode_AVL(root, key); 
			break;
		case 1: 
			root = deleteNode_AVL(root, key); 
			break;
		case 2: 
			searchCount++;	
			search_AVL(root, key); 
			break;
		}
	}
	return root;
}

Node* doBinaryBatch(Node *root) {	
	searchCount = 0;

	for (int i = 0; i < 2000; i++) {
		int a = rand() % 3;
		int key = rand() % SIZE;
		switch (a) {
		case 0:
			root = insertNode_binary(root, key); 
			break;
		case 1:
			root = deleteNode_binary(root, key);
			break;
		case 2:
			searchCount++;
			search_binary(root, key);
			break;
		}
	}
	return root;
}

// ������ȸ�� Ʈ�� free
void freeTree(Node* root) {
	if (root == NULL) return;
	if (root->left != (Node*)NULL) freeTree(root->left); 
	if (root->right != (Node*)NULL) freeTree(root->right); 
	free(root);
}

int main(int argc, char* argv[]) {
	Node* root = NULL; 
	srand(time(NULL));
	float allCount = 0.0;

	doAVLBatch(root); 
	allCount = (float)compareCount / searchCount;
	printf("average AVL compare count: %.2f\n", allCount);

	freeTree(root);
	root = NULL;
	compareCount = allCount = 0; 

	doBinaryBatch(root); 
	allCount = (float)compareCount / searchCount;
	printf("average Bin compare count: %.2f\n", allCount);

	freeTree(root);
	return 0;
}
