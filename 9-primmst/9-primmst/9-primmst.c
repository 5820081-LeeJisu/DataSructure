#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

typedef struct GraphType {
    int n;      // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];     // ����ġ ���
} GraphType;

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {   // ��� ���� �� �� ����ġ�� INF�� �ʱ�ȭ
            g->weight[i][j] = INF;
        }
    }
}

// �׷����� ���� �߰� �Լ�
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start][end] = w;      // start���� end�� ���� ������ ����ġ ����
    g->weight[end][start] = w;      // ������ �׷����̹Ƿ� �ݴ� ���⵵ ������ ����ġ ����
}

// Prim�� MST(�ּ� ���� Ʈ��) �˰��� �Լ�
void FindPrimMST(GraphType* g) {
    int selected[MAX_VERTICES] = { FALSE };     // MST�� ���� ���� ����
    int key[MAX_VERTICES];      // �� ������ �ּ� ����ġ ����
    int parent[MAX_VERTICES];   // �� ������ �θ� ����

    printf("Prim MST Algorithm\n");

    for (int i = 0; i < g->n; i++) {
        key[i] = INF;       // �ʱ� ����ġ�� ���Ѵ�� ����
        parent[i] = -1;     // �ʱ� �θ� -1�� ����
    }
    key[1] = 0;     // ���� ���� ���� (���� 1)

    for (int i = 0; i < g->n; i++) {
        int u = -1;
        int minKey = INF;

        // ���õ��� ���� ���� �� �ּ� ����ġ�� ���� ���� u ã��
        for (int v = 1; v < g->n; v++) {
            if (!selected[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }
        if (u == -1) break;     // �� �̻� ������ ������ ������ ����

        selected[u] = TRUE;     // ���� u�� MST�� �߰�
        printf("���� %d �߰�\n", u);

        // u�� ����� ������ ����ġ ����
        for (int v = 1; v < g->n; v++) {
            if (!selected[v] && g->weight[u][v] < key[v]) {
                key[v] = g->weight[u][v];
                parent[v] = u;
            }
        }
    }
}

// �׷��� ���� �Լ�
GraphType* GenerateGraph(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g, 11);  // 11���� �������� �׷��� �ʱ�ȭ

    // ���� �߰�
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

    return g;   // ������ �׷��� ��ȯ
}

int main(void) {
    GraphType* g;
    g = GenerateGraph();
    FindPrimMST(g);
    free(g);
    return 0;
}