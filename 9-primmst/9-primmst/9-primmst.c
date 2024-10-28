#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphType {
    int n;      // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];     // 가중치 행렬
} GraphType;

// 그래프 초기화 함수
void graph_init(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {   // 모든 정점 쌍 간 가중치를 INF로 초기화
            g->weight[i][j] = INF;
        }
    }
}

// 그래프에 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start][end] = w;      // start에서 end로 가는 간선의 가중치 설정
    g->weight[end][start] = w;      // 무방향 그래프이므로 반대 방향도 동일한 가중치 설정
}

// Prim의 MST(최소 신장 트리) 알고리즘 함수
void FindPrimMST(GraphType* g) {
    int selected[MAX_VERTICES] = { FALSE };     // MST에 포함 여부 저장
    int key[MAX_VERTICES];      // 각 정점의 최소 가중치 저장
    int parent[MAX_VERTICES];   // 각 정점의 부모 저장

    printf("Prim MST Algorithm\n");

    for (int i = 0; i < g->n; i++) {
        key[i] = INF;       // 초기 가중치를 무한대로 설정
        parent[i] = -1;     // 초기 부모를 -1로 설정
    }
    key[1] = 0;     // 시작 정점 선택 (정점 1)

    for (int i = 0; i < g->n; i++) {
        int u = -1;
        int minKey = INF;

        // 선택되지 않은 정점 중 최소 가중치를 가진 정점 u 찾기
        for (int v = 1; v < g->n; v++) {
            if (!selected[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        if (u == -1) break;     // 더 이상 선택할 정점이 없으면 종료

        selected[u] = TRUE;     // 정점 u를 MST에 추가
        printf("정점 %d 추가\n", u);

        // u와 연결된 정점의 가중치 갱신
        for (int v = 1; v < g->n; v++) {
            if (!selected[v] && g->weight[u][v] < key[v]) {
                key[v] = g->weight[u][v];
                parent[v] = u;
            }
        }
    }
}

// 그래프 생성 함수
GraphType* GenerateGraph(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g, 11);  // 11개의 정점으로 그래프 초기화

    // 간선 추가
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

    return g;   // 생성한 그래프 반환
}

int main(void) {
    GraphType* g;
    g = GenerateGraph();
    FindPrimMST(g);
    free(g);
    return 0;
}