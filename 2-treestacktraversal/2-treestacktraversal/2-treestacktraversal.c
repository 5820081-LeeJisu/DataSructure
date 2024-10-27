#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;
typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
	StackNode* TopNode;
} LinkedStackType;

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

void init(LinkedStackType* s) {
	s->top = NULL;
}

int is_empty(LinkedStackType* s) {
	return (s->top == NULL);
}

int is_full(LinkedStackType* s) {
	return 0;
}

void push(LinkedStackType* s, element item) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	if (is_empty(s)) return NULL;
	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;

	free(temp);
	return data;
}

void itr_inpreder_traveral(TreeNode* root) {
	LinkedStackType s;
	TreeNode* nptr = root;

	init(&s);

	while (nptr != NULL || !is_empty(&s)) {
		while (nptr != NULL) {
			push(&s, nptr);
			printf("push(%2d)", nptr->data);
			nptr = nptr->left;
		}
		nptr = pop(&s);
		if (nptr != NULL) {
			printf("pop(%2d)", nptr->data);
			nptr = nptr->right;
		}
		printf("\n");
	}
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

void LinkPreOrder(LinkedStackType* s) {
	//Stack에서 본인 노드 가져옴
	TreeNode* current = s->top->data;

	printf("pop(%d) ", current->data);
	pop(s);
	printf("visit(%d)\n", current->data);

	if (current->left != NULL) {
		printf("push(%d) ", current->left->data);
		push(s, current->left);
		LinkPreOrder(s);
	}

	if (current->right != NULL) {
		printf("push(%d) ", current->right->data);
		push(s, current->right);
		LinkPreOrder(s);
	}

	return;
}

void LinkInOrder(LinkedStackType* s) {
	TreeNode* current = s->top->data;

	if (current->left != NULL) {
		printf("push(%d) ", current->left->data);
		push(s, current->left);
		LinkInOrder(s);
	}

	printf("pop(%d) ", current->data);
	pop(s);
	printf("visit(%d)\n", current->data);

	if (current->right != NULL) {
		printf("push(%d) ", current->right->data);
		push(s, current->right);
		LinkInOrder(s);
	}

	return;
}

void LinkPostOrder(LinkedStackType* s) {
	TreeNode* current = s->top->data;

	if (current->left != NULL) {
		printf("push(%d) ", current->left->data);
		push(s, current->left);
		LinkPostOrder(s);
	}

	if (current->right != NULL) {
		printf("push(%d) ", current->right->data);
		push(s, current->right);
		LinkPostOrder(s);
	}

	printf("pop(%d) ", current->data);
	pop(s);
	printf("visit(%d)\n", current->data);

}

void LinkOrders(TreeNode* root) {
	LinkedStackType* s = (LinkedStackType*)malloc(sizeof(LinkedStackType));
	init(s);

	printf("전위 순회:\n");
	printf("push(%d) ", root->data);
	push(s, root);

	LinkPreOrder(s);
	printf("\n");

	printf("중위 순회:\n");
	printf("push(%d) ", root->data);
	push(s, root);

	LinkInOrder(s);
	printf("\n");

	printf("후위 순회:\n");
	printf("push(%d) ", root->data);
	push(s, root);

	LinkPostOrder(s);
	printf("\n");
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	root->left = NULL;
	root->right = NULL;

	GenerateLinkTree(root);
	LinkOrders(root);

	free(root);

	return 0;
}
