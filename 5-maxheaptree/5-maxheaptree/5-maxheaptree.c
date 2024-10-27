#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
	int key;
} element;

typedef struct TreeNode {
	int data;
	int heap_size;
	struct TreeNode* right, * left;
	element heap[MAX_SIZE];
} TreeNode;

TreeNode* create_heap() {
	return (TreeNode*)malloc(sizeof(TreeNode)); //�� ����
}

void init_heap(TreeNode* h) {
	h->heap_size = 0; //�ʱ�ȭ
}

void display_heap(TreeNode* h) {
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

int InsertMaxHeapTree(TreeNode* h, element item) {
	int i = ++(h->heap_size);
	h->heap[i] = item;
	int count = 0;

	//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (h->heap[i / 2].key < h->heap[i].key)) {
		display_heap(h);
		element current = h->heap[i / 2];
		h->heap[i / 2] = h->heap[i]; // i/2�� �θ���, i�� �ڽĳ��
		h->heap[i] = current;
		i /= 2;
		count++;
	}
	return count;
}

element DeleteHeap(TreeNode* h) {
	int parent = 1;
	int child = 2;
	element item = h->heap[1];	//���� ���� �ִ� �� (���� ū ��)
	element temp = h->heap[(h->heap_size)--];
	int count = 1;

	h->heap[parent] = temp;

	display_heap(h);

	while (child <= h->heap_size) {
		//���� ����� �ڽĳ�� �� �� ū �ڽĳ�� ã��
		if ((child <= h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		//�� �ܰ� �Ʒ��� �̵�
		element node = h->heap[parent];
		h->heap[parent] = h->heap[child];
		h->heap[child] = node;
		display_heap(h);

		parent = child;
		child *= 2;
		count++;
	}
	h->heap[parent] = temp;
	printf("��尡 �̵��� Ƚ��: %d\n\n", count);
	return item;
}

void PrintTreeLevel(TreeNode* h) {
	printf("Ʈ�� ������ ���\n");

	int level = 1;
	int nodesInLevel = 1;
	int nodesPrinted = 0;

	printf("[%d] ", level);

	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
		nodesPrinted++;

		if (nodesPrinted == nodesInLevel) {
			printf("\n");
			level++;
			nodesInLevel *= 2;
			nodesPrinted = 0;

			if (i < h->heap_size) {
				printf("[%d] ", level);
			}
		}
	}
	printf("\n\n");
}

TreeNode* generateMaxHeapTree(int inputData[], int size) {
	TreeNode* root = create_heap();
	init_heap(root);
	element item;

	for (int i = 0; i < size; i++) {
		item.key = inputData[i];
		InsertMaxHeapTree(root, item);
	}
	return root;
}

void runUserInterface(TreeNode* root) {
	char menu;
	element insert_value;

	TreeNode* heap = create_heap();

	printf("�ѤѤѤѤѤѤѤѤѤѤѤ�\n");
	printf("| i   : ��� �߰�     |\n");
	printf("| d   : ��� ����     |\n");
	printf("| p   : ������ ���   |\n");
	printf("| c   : ����          |\n");
	printf("�ѤѤѤѤѤѤѤѤѤѤѤ�\n");

	while (1) {
		printf("�޴� �Է�: ");
		scanf_s("%c", &menu);
		getchar();

		switch (menu) {
		case 'i':
			printf("�߰��� �� �Է�: ");
			scanf_s("%d", &insert_value.key);
			getchar();

			int count = InsertMaxHeapTree(root, insert_value);
			display_heap(root);
			printf("��尡 �̵��� Ƚ��: %d\n\n", count);
			break;
		case 'd':
			DeleteHeap(root);
			break;
		case 'p':
			PrintTreeLevel(root);
			break;
		case 'c':
			free(heap);
			return;
		};
	}
}

int main() {
	int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 5 };
	int size = sizeof(inputData) / sizeof(inputData[0]);

	TreeNode* root = generateMaxHeapTree(inputData, size);

	runUserInterface(root);

	free(root);
	return 0;
}