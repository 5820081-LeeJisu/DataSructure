#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 // ���Ѵ� (������ ���� ���)

typedef struct GraphType {
    int n; // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // �����������κ����� �ִܰ�� �Ÿ�
int found[MAX_VERTICES];    // �湮�� ���� ǥ��

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g, int n) {
    g->n = n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) { // ��� ���� �� �� ����ġ�� INF�� �ʱ�ȭ
            g->weight[i][j] = INF;
        }
    }
}

// �׷����� ���� �߰� �Լ�
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start][end] = w;      // start���� end�� ���� ������ ����ġ ����
    g->weight[end][start] = w;      // ������ �׷����̹Ƿ� �ݴ� ���⵵ ������ ����ġ ����
}

// �湮���� ���� ���� �߿��� �ִ� ��θ� ������ ������ ����
int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 1; i <= n; i++) {
        if (distance[i] < min && !found[i]) {    // �湮���� ���� ���� �� �ּڰ��� ã��
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;      // �ִ� ��� ������ �ε��� ��ȯ
}

// ���� ���� ���
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

// �ִ� ��� ã��
void shortest_path(GraphType* g, int start) {
    int u, w;
    int* node = (GraphType*)malloc(sizeof(int) * g->n);   // ������ ã�� ������ ������ �迭 

    // distance�� found �迭 �ʱ�ȭ
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }

    distance[start] = 0;    // ���� ������ �Ÿ� �ʱ�ȭ

    for (int i = 0; i < g->n; i++) {
        u = choose(distance, g->n, found);  // �ִ� ����� ���� ����
        node[i] = u;    // ���õ� ������ ������� ����
        found[u] = TRUE;    // �ش� ������ �湮 ó��
        print_status(g);    // ���� ���� ���
        for (w = 1; w <= g->n; w++) {
            if (!found[w]) {    // �湮���� ���� ������ ���� ���ο� ��ΰ� ���� �Ÿ����� ª���� ������Ʈ
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

// �׷��� ���� �Լ�
GraphType* GenerateGraph(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));

    graph_init(g, 10);  // 10���� �������� �׷��� �ʱ�ȭ

    // �� ���� �߰�
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

    return g;   // ������ �׷��� ��ȯ
}

int main(void) {
    GraphType* g;
    g = GenerateGraph();
    shortest_path(g, 1);  // ���� ������ 1�� ����
    free(g);
    return 0;
}

