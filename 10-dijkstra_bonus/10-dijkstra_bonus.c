#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100   
#define INF 1000000   

typedef struct GraphNode {
    int vertex, weight;
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType {
    int n;	// ������ ����
    struct GraphNode* adj_list[MAX_VERTICES];
} GraphType;

typedef struct {
    int vertex, distance;
} HeapNode;

typedef struct {
    HeapNode heap[MAX_VERTICES];
    int heap_size;
} MinHeap;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int found_index = 0;
int found_order[MAX_VERTICES];

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->n = 10;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

// ����
void insert_edge(GraphType* g, int start, int end, int w) {
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->vertex = end;
    newNode->weight = w;
    newNode->next = g->adj_list[start];
    g->adj_list[start] = newNode;
}

// �� �ʱ�ȭ
void init_minheap(MinHeap* h) {
    h->heap_size = 0;
}

// ��ȯ
void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// �ּ� �� ������
void min_heapify(MinHeap* h, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->heap_size && h->heap[left].distance < h->heap[smallest].distance)      //���� �ڽ� ���� �� �۴ٸ�
        smallest = left;
    if (right < h->heap_size && h->heap[right].distance < h->heap[smallest].distance)   //������ �ڽ� ���� �� �۴ٸ�
        smallest = right;

    if (smallest != index) {    // �θ� ��� ���� �ڽ� ��� ���� �ٸ���
        swap(&h->heap[index], &h->heap[smallest]);  // ��ȯ ��
        min_heapify(h, smallest);   // �� ������
    }
}

// ����
void insert_minheap(MinHeap* h, int vertex, int distance) {
    int i = h->heap_size++;
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;

    while (i && h->heap[i].distance < h->heap[(i - 1) / 2].distance) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// ����
HeapNode delete_minheap(MinHeap* h) {
    HeapNode min_edge = h->heap[0];
    h->heap[0] = h->heap[--h->heap_size];
    min_heapify(h, 0);
    return min_edge;
}

// ���� distance, found ���
void print_dijkstra(int n) {
    printf("Distance: ");
    for (int j = 1; j <= n; j++) {
        if (distance[j] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[j]);
    }
    printf("\nFound:    ");
    for (int j = 1; j <= n; j++) {
        printf(" %d ", found[j]);
    }
    printf("\n\n");
}

// �ִ� ��� ã��
void dijkstra(GraphType* g, int start) {
    MinHeap h;
    init_minheap(&h);

    for (int i = 0; i < MAX_VERTICES; i++) { // �ʱ�ȭ
        distance[i] = INF;
        found[i] = 0;
    }
    distance[start] = 0;
    insert_minheap(&h, start, 0);

    while (h.heap_size > 0) {       // ���� ������� �ʴ� ���� ��� �ݺ�
        HeapNode u = delete_minheap(&h);    // �ּ� �Ÿ� ���� ����

        if (found[u.vertex]) continue;      // �̹� �湮�ߴ� �����̸� �н�
        found[u.vertex] = 1;        // ���� �湮 ó��
        found_order[found_index++] = u.vertex;

        print_dijkstra(g->n); // ���� ���� ���

        for (GraphNode* v = g->adj_list[u.vertex]; v != NULL; v = v->next) {     // ���� ���� Ž��
            if (!found[v->vertex] && distance[u.vertex] + v->weight < distance[v->vertex]) {    // �湮���� �ʰų� ���ο� ��ΰ� �� ª���� �Ÿ� ������Ʈ
                distance[v->vertex] = distance[u.vertex] + v->weight;   // ���ο� �Ÿ��� ������Ʈ �ϰ� 
                insert_minheap(&h, v->vertex, distance[v->vertex]);     // ���� ����
            }
        }
    }

    printf("found order: ");    // �湮�� ���� ���
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

// �׷��� ����
GraphType* GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);

    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    return g;
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    dijkstra(g, 1);

    free(g);
    return 0;
}