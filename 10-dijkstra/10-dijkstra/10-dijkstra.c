#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 // 무한대 (연결이 없는 경우)

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // 시작정점으로부터의 최단경로 거리
int found[MAX_VERTICES];    // 방문한 정점 표시

// 그래프 초기화 함수
void graph_init(GraphType* g, int n) {
    g->n = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) { // 모든 정점 쌍 간 가중치를 INF로 초기화
            g->weight[i][j] = INF;
        }
    }
}

// 그래프에 간선 추가 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start][end] = w;      // start에서 end로 가는 간선의 가중치 설정
    g->weight[end][start] = w;      // 무방향 그래프이므로 반대 방향도 동일한 가중치 설정
}

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 1; i <= n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 1; i <= g->n; i++) {
        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf("Found:    ");
    for (int i = 1; i <= g->n; i++)
        printf("%2d ", found[i]);
    printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
    int u, w;
    int* node = (GraphType*)malloc(sizeof(int)*g->n);  // Found Order 

    for (int i = 1; i <= g->n; i++) {  // 초기화
        distance[i] = INF; //g->weight[start][i];
        found[i] = FALSE;
    }

    distance[start] = 0;

    for (int i = 0; i < g->n; i++) {
        u = choose(distance, g->n, found);
        node[i] = u;
        found[u] = TRUE;
        print_status(g); 
        for (w = 1; w <= g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", node[i]);
    }
    printf("\n");

    free(node);
}

// 그래프 생성 함수
GraphType* GenerateGraph(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));

    graph_init(g, 10);  // 10개의 정점으로 그래프 초기화

    // 각 간선 추가
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    return g;   // 생성한 그래프 반환
}

int main(void) {
    GraphType* g;
    g = GenerateGraph();
    shortest_path(g, 1);  // 시작 정점을 1로 설정
    free(g);
    return 0;
}

