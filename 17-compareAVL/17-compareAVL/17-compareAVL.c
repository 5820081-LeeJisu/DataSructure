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

// 노드 생성
Node* createNode(int key) {
	Node* nptr = (Node*)malloc(sizeof(Node));
	nptr->key = key;
	nptr->right = nptr->left = (Node*)NULL;
	nptr->height = 1;
	return nptr;
}

// 노드의 높이 구하기
int getHeight(Node* nptr) {
	if (nptr == (Node*)NULL) 
		return 0;
	else 
		return nptr->height;
}

// 노드의 균형 인수 구하기 (왼쪽 서브 트리의 높이 - 오른쪽 서브 트리의 높이)
int getBalance(Node* nptr) {
	return getHeight(nptr->left) - getHeight(nptr->right);
}

// 균형 트리로 만들기 위해 회전
// 오른쪽으로 회전 
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

// 왼쪽으로 회전
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

// AVL트리일 때 탐색 함수
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

// 이진 탐색 트리일 때 탐색 트리
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

// AVL트리에 삽입 
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

	if (balance >= 2) {	// 밸런스가 깨질 때
		// LL 회전: 오른쪽으로 회전
		if (getBalance(root->left) >= 0) {
			return rotateRight(root);
		}
		// LR 회전: 왼쪽 회전 --> 오른쪽 회전
		else /*if (getBalance(root->left) < 0)*/ {
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		//else;
	}
	// RR 회전: 왼쪽으로 회전
	else if (balance <= -2) {
		if (getBalance(root->right) < 0) {
			return rotateLeft(root);
		}
		// RL 회전: 오른쪽 회전 --> 왼쪽 회전
		else {
			root->right = rotateRight(root->right); 
			rotateLeft(root); 
		}
	}
	else {
		return root;
	}
}

// 트리에서 최소값 노드 찾기
Node* getMinValueNode(Node* node) {
	Node* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// AVL트리에 삭제
Node* deleteNode_AVL(Node* root, int key) {
	// 1. 일반 이진 탐색 트리 삭제
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
		// 노드 삭제
		if ((root->left == NULL) || (root->right == NULL)) { // 자식 노드가 한개
			Node* temp = root->left ? root->left : root->right; // 그 자식노드를 temp가 가리킴

			if (temp == NULL) { // 자식 노드가 없음
				temp = root; // 메모리 해제할 것
				root = NULL;  // 리턴(되돌려 줄 것)
			}
			else { // 자식 노드가 하나 있음
				*root = *temp; // 하나 있는 자식을 부모로 대치함
			}
			free(temp);
		}
		else {
			// 오른쪽 서브트리에서 최소값 노드 찾기
			Node* temp = getMinValueNode(root->right);
			root->key = temp->key; // 키값만 복사함
			root->right = deleteNode_AVL(root->right, temp->key); // 이제 그 최소값을 가진 노드 삭제
		}
	}

	if (root == NULL) {
		return root;
	}

	// 2. 노드 높이 갱신
	root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
		? getHeight(root->left) : getHeight(root->right));

	// 3. 균형 인수 계산
	int balance = getBalance(root);

	// 4. 균형 유지 회전 수행
	// R 회전
	if (balance > 1 && getBalance(root->left) >= 0) {
		return rotateRight(root);
	}

	// LR 회전
	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}

	// L 회전
	if (balance < -1 && getBalance(root->right) <= 0) {
		return rotateLeft(root);
	}

	// RL 회전
	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}

// 이진 탐색 트리에 삽입 (AVL에서 회전만 빼면 됨)
Node* insertNode_binary(Node* root, int key) {
	if (root == NULL) 
		return createNode(key);

	if (root->key > key)
		root->left = insertNode_binary(root->left, key);
	else if (root->key < key)
		root->right = insertNode_binary(root->right, key);

	return root;
}

// 이진 탐색 트리에 삭제 (AVL에서 회전만 빼면 됨)
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

// 후위순회로 트리 free
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
