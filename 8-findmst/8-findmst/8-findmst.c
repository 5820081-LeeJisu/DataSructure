#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MAX_ELEMENT 200 
#define INF 1000

struct Edge {   // 간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct GraphType {
    int n;  // 현재 간선의 개수
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

typedef int vertex;

typedef struct DListNode {	// 이중연결 노드 타입
    vertex data;
    struct DListNode* llink;
    struct DListNode* rlink;
} DListNode;

typedef struct {
    struct Edge heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

int parent[MAX_VERTICES];  // 부모 노드 

void set_init(int n) {
    if (n > MAX_VERTICES)  // 추가
        return;

    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr가 속하는 집합 반환
int set_find(int curr) {
    if (curr < 0 || curr >= MAX_VERTICES)
        return -1;

    if (parent[curr] == -1)  // 추가
        return curr;        // 루트

    while (parent[curr] != -1)
        curr = parent[curr];

    return curr;
}

// 두개의 원소가 속한 집합을 합친다
void set_union(int a, int b) {
    int root1 = set_find(a);  // 노드 a의 루트 찾기
    int root2 = set_find(b);  // 노드 b의 루트 찾기
    if (root1 != root2)     // 합치기
        parent[root1] = root2;
}

// 그래프 초기화 
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w) {
    if (g->n < 2 * MAX_VERTICES) { // 배열 범위 체크
        g->edges[g->n].start = start;
        g->edges[g->n].end = end;
        g->edges[g->n].weight = w;
        g->n++;
    }
    else
        printf("Error: Maximum edges exceeded.\n");
}

// qsort()에 사용되는 함수
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);
}

// kruskal의 최소 비용 신장 트리
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0;         // 현재까지 선택된 간선의 수   
    int uset, vset;                // 정점 u와 정점 v의 집합 번호
    struct Edge e;

    set_init(MAX_VERTICES);   // 모든 정점에 대해 초기화
    qsort(g->edges, g->n, sizeof(struct Edge), compare);    // 정렬할 값의 주소, 요소의 개수, 요소의 크기, 기준 함수

    printf("Quick Based kruskal  \n");
    int i = 0;

    // 간선의 수 < (n-1)
    while (edge_accepted < (g->n - 1) && i < g->n) {
        e = g->edges[i];
        uset = set_find(e.start);        // 정점 u의 집합 번호 
        vset = set_find(e.end);          // 정점 v의 집합 번호

        if (uset != vset) {             // 서로 속한 집합이 다르면
            printf("edge (%d, %d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);        // 두개의 집합을 합친다.
        }
        i++;
    }
}

// 이중연결리스트 초기화
void init_Dlist(DListNode* phead) {
    phead->llink = phead;
    phead->rlink = phead;
}

// 이중연결리스트 노드 추가
void insert_Dlist(DListNode* before, vertex data) {
    DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
    newnode->data = data;
    newnode->llink = before;
    newnode->rlink = before->rlink;
    before->rlink->llink = newnode;
    before->rlink = newnode;
}

// 힙 초기화
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// 힙에 작은 수(엣지)부터 추가하기
void insert_min_heap(HeapType* h, struct Edge item) {
    int i = ++(h->heap_size);
    while ((i != 1) && (item.weight < h->heap[i / 2].weight)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

// 힙에서 작은 수(엣지)부터 삭제
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

// min-heap기반 kruskal
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
            insert_Dlist(&mst, e.weight);  // 최소신장트리에 엣지 가중치 저장
        }
    }
}

// 그래프를 생성하는 함수
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

    GenerateGraph(g);   // 그래프 생성 함수

    QuickKruskal(g);    // quick 기반 kruskal
    MinHeapKruskal(g);  // minheap 기반 kruskal

    free(g);
    return 0;
}
