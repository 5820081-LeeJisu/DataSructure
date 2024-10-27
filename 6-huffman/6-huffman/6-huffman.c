#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct Node {
	int weight;
	char ch;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct {
	Node* ptree;
	char ch;
	int key;
} element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}

void display_heap(HeapType* h) {
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

//힙(h)에 item 삽입
void insert_min_heap(HeapType* h, element item) {
	int i = ++(h->heap_size); //현재 요소의 개수(heap_size)

	//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; //새로운 노드 삽입
	display_heap(h); 
}

element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//현재 노드의 자식노드 중 더 작은 자식노드 찾기
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		//한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//이진 트리 생성
Node* make_tree(Node* left, Node* right) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = left;
	node->right = right;
	return node;
}

//단말 노드
int is_leaf(Node* root) {
	return !(root->left) && !(root->right);
}

void print_array(int arr[], int size) {
	for (int i = 0; i < size; i++)
		printf("%d", arr[i]);
	printf("\n");
}

void printCodes(Node* root, int arr[], int top) {
	//1 저장, 순환호출
	if (root->left) {
		arr[top] = 1;
		printCodes(root->left, arr, top + 1);
	}
	//0 저장, 순환호출
	if (root->right) {
		arr[top] = 0;
		printCodes(root->right, arr, top + 1);
	}
	//단말노드이면 코드 출력
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(arr, top);
	}
}

//허프만 코드 생성
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
	Node* node, * x;
	HeapType* heap;
	element e, e1, e2;

	heap = create();
	init(heap);
	for (int i = 0; i < size; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = characters[i];
		e.key = node->weight = frequencies[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}

	for (int i = 1; i < size; i++) {
		//최소값을 가지는 두 개의 노드 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		//두 개의 노드 합체
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("///%d + %d -> %d \n", e1.key, e2.key, e.key);

		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); //최종 트리

	free(heap);
	return e.ptree;
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
	Node* root = buildHuffmanTree(characters, frequencies, size);
	int arr[100], top = 0;
	printCodes(root, arr, top);
}

int main() {
	char characters[] = { 'a' , 'e', 'i', 'o', 'u', 's', 't' };
	int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
	int size = sizeof(characters) / sizeof(characters[0]);

	GenerateHuffmanCodes(characters, frequencies, size);

	return 0;
}