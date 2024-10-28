#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MAX_ELEMENT 200 
#define INF 1000

struct Edge {   // ������ ��Ÿ���� ����ü
    int start, end, weight;
};

typedef struct GraphType {
    int n;  // ���� ������ ����
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef int vertex;

typedef struct DListNode {	// ���߿��� ��� Ÿ��
    vertex data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

typedef struct {
    struct Edge heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

int parent[MAX_VERTICES];  // �θ� ��� 

void set_init(int n) {
    if (n > MAX_VERTICES)  // �߰�
        return;

    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr�� ���ϴ� ���� ��ȯ
int set_find(int curr) {
    if (curr < 0 || curr >= MAX_VERTICES)
        return -1;

    if (parent[curr] == -1)  // �߰�
        return curr;        // ��Ʈ

    while (parent[curr] != -1)
        curr = parent[curr];

    return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��
void set_union(int a, int b) {
    int root1 = set_find(a);  // ��� a�� ��Ʈ ã��
    int root2 = set_find(b);  // ��� b�� ��Ʈ ã��
    if (root1 != root2)     // ��ġ��
        parent[root1] = root2;
}

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end, int w) {
    if (g->n < 2 * MAX_VERTICES) { // �迭 ���� üũ
        g->edges[g->n].start = start;
        g->edges[g->n].end = end;
        g->edges[g->n].weight = w;
        g->n++;
    }
    else
        printf("Error: Maximum edges exceeded.\n");
}

// qsort()�� ���Ǵ� �Լ�
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

// kruskal�� �ּ� ��� ���� Ʈ��
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0;         // ������� ���õ� ������ ��   
    int uset, vset;                // ���� u�� ���� v�� ���� ��ȣ
    struct Edge e;

    set_init(MAX_VERTICES);   // ��� ������ ���� �ʱ�ȭ
    qsort(g->edges, g->n, sizeof(struct Edge), compare);    // ������ ���� �ּ�, ����� ����, ����� ũ��, ���� �Լ�

    printf("Quick Based kruskal  \n");
    int i = 0;

    // ������ �� < (n-1)
    while (edge_accepted < (g->n - 1) && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);        // ���� u�� ���� ��ȣ 
        vset = set_find(e.end);          // ���� v�� ���� ��ȣ

        if (uset != vset) {             // ���� ���� ������ �ٸ���
            printf("edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);        // �ΰ��� ������ ��ģ��.
        }
        i++;
    }
}

// ���߿��Ḯ��Ʈ �ʱ�ȭ
void init_Dlist(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

// ���߿��Ḯ��Ʈ ��� �߰�
void insert_Dlist(DListNode* before, vertex data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

// �� �ʱ�ȭ
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// ���� ���� ��(����)���� �߰��ϱ�
void insert_min_heap(HeapType* h, struct Edge item) {
    int i = ++(h->heap_size);
    while ((i != 1) && (item.weight < h->heap[i / 2].weight)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// ������ ���� ��(����)���� ����
struct Edge delete_min_heap(HeapType* h) {
    int parent = 1, child = 2;
    struct Edge item = h->heap[1];
    struct Edge temp = h->heap[(h->heap_size)--];

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].weight > h->heap[child + 1].weight))
            child++;
        if (temp.weight <= h->heap[child].weight)
            break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// min-heap��� kruskal
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;

    HeapType heap;
    DListNode mst;
    init_Dlist(&mst);

    init_heap(&heap);
    set_init(MAX_VERTICES);

    printf("\nMinHeap Based kruskal\n"); 

    for (int i = 0; i < g->n; i++)
        insert_min_heap(&heap, g->edges[i]);

    while (edge_accepted < (g->n - 1) && heap.heap_size > 0) {
        e = delete_min_heap(&heap);
        uset = set_find(e.start);
        vset = set_find(e.end);

        if (uset != vset) {
            printf("edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
            insert_Dlist(&mst, e.weight);  // �ּҽ���Ʈ���� ���� ����ġ ����
        }
    }
}

// �׷����� �����ϴ� �Լ�
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    //return g;
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);   // �׷��� ���� �Լ�

    QuickKruskal(g);    // quick ��� kruskal
    MinHeapKruskal(g);  // minheap ��� kruskal

    free(g);
    return 0;
}
