#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
    int visited_node[MAX_VERTICES];
} GraphType;

typedef struct StackNode {
    int data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

typedef GraphNode* element;

typedef struct QueueNode {
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct {
    QueueNode* front, * rear;
} LinkedQueueType;

int is_empty_stack(LinkedStackType* s) {
    return (s->top == NULL);
}

int is_empty_queue(LinkedQueueType* q) {
    return (q->front == NULL);
}

void init_stack(LinkedStackType* s) {
    s->top = NULL;
}

void init_queue(LinkedQueueType* q) {
    q->front = q->rear = NULL;
}

void push(LinkedStackType* s, int item) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

int pop(LinkedStackType* s) {
    if (is_empty_stack(s)) return -1;
    StackNode* temp = s->top;
    int data = temp->data;
    s->top = temp->link;
    free(temp);
    return data;
}

void enqueue(LinkedQueueType* q, element item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = item;
    temp->link = NULL;
    if (is_empty_queue(q)) {
        q->front = temp;
        q->rear = temp;
    }
    else {
        q->rear->link = temp;
        q->rear = temp;
    }
}

element dequeue(LinkedQueueType* q) {
    if (is_empty_queue(q)) exit(1);
    QueueNode* temp = q->front;
    element data = temp->data;
    q->front = q->front->link;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return data;
}

// �׷��� �ʱ�ȭ
void createGraph(GraphType* g) {
    g->n = 0;   // ������ ���� 0 
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->visited_node[v] = FALSE;     // ��� ������ �湮���� ���� ���·� �ʱ�ȭ
        g->adj_list[v] = NULL;      // ���� ����Ʈ�� NULL�� �ʱ�ȭ
    }
}

// �׷����� ���� ����
void insertVertex(GraphType* g, int v) {
    if (g->n + 1 > MAX_VERTICES) return;    // ���� ���� �ִ�ġ�� ���� �� ����
    g->n++;
}

// �׷����� ���� ����
void insertEdge(GraphType* g, int tail, int head) {
    GraphNode* node;
    if ((tail >= g->n) || (head >= g->n)) return;   // ��ȿ�� �������� Ȯ��
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = head;
    node->link = g->adj_list[tail];     // ���� ����Ʈ�� ���� �߰�
    g->adj_list[tail] = node;
}

// ���� �켱 Ž��
int DepthFirstSearch(GraphType* g, LinkedStackType* s, int start, int end) {
    init_stack(s);
    int count = 0;

    push(s, start);     // ���� ���� ���ÿ� ����
    g->visited_node[start] = TRUE;      // ���� ���� �湮�� �ɷ� ó��
    printf("%d ", start);

    while (!is_empty_stack(s)) {
        int v = pop(s);
        GraphNode* node = g->adj_list[v];

        while (node != NULL) {
            int w = node->vertex;
            if (!g->visited_node[w]) {      // �湮���� ���� ����� ��
                g->visited_node[w] = TRUE;
                printf("%d ", w);
                count++;

                if (w == end) {     // Ž�� ���� ����
                    printf("\nŽ�� ����: %d\n", w);
                    printf("�湮�� ����� ��: %d\n\n", count);
                    return TRUE;
                }

                push(s, v);     // ��Ʈ��ŷ
                push(s, w);
                break;
            }
            node = node->link;
        }
    }

    printf("\nŽ�� ����: %d\n", end);
    return FALSE;
}

// �ʺ� �켱 Ž��
int BreadthFirstSearch(GraphType* g, LinkedQueueType* q, int start_vertex, int end_vertex) {
    GraphNode* current;
    int count = 0;

    init_queue(q);
    enqueue(q, (element)start_vertex);
    g->visited_node[start_vertex] = TRUE;

    while (!is_empty_queue(q)) {
        int v = (int)dequeue(q);
        printf("%d ", v);

        if (v == end_vertex) {      // ���� ������ �������� ��
            printf("\nŽ�� ����: %d\n", end_vertex);
            printf("�湮�� ����� ��: %d\n\n", count);
            return TRUE;
        }

        for (current = g->adj_list[v]; current != NULL; current = current->link) {
            if (!g->visited_node[current->vertex]) {    // �湮���� ���� ������ ť�� ����
                enqueue(q, (element)current->vertex);
                g->visited_node[current->vertex] = TRUE;
                count++;
            }
        }
    }

    printf("\nŽ�� ����: %d\n", end_vertex);
    return FALSE;
}

// �׷��� ����, ���� �߰�
void GenerateLinkedGraph(GraphType* g) {
    insertEdge(g, 0, 2);
    insertEdge(g, 0, 4);
    insertEdge(g, 0, 5);
    insertEdge(g, 0, 6);
    insertEdge(g, 0, 9);
    insertEdge(g, 1, 4);
    insertEdge(g, 1, 5);
    insertEdge(g, 1, 7);
    insertEdge(g, 1, 10);
    insertEdge(g, 2, 3);
    insertEdge(g, 2, 4);
    insertEdge(g, 3, 4);
    insertEdge(g, 3, 5);
    insertEdge(g, 4, 5);
    insertEdge(g, 4, 6);
    insertEdge(g, 4, 7);
    insertEdge(g, 6, 7);
    insertEdge(g, 6, 8);
    insertEdge(g, 7, 10);
    insertEdge(g, 8, 9);
    insertEdge(g, 8, 10);
}

void menu(GraphType* g) {
    int num = 0;
    int start_vertex, end_vertex;
    LinkedStackType s;
    LinkedQueueType q;
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("| 1   : ���� �켱 Ž��    |\n");
    printf("| 2   : �ʺ� �켱 Ž��    |\n");
    printf("| 3   : ����	          |\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    while (1) {
        printf("�޴� �Է�: ");
        scanf_s("%d", &num);

        if (num == 3) return;   // ���� ����

        printf("���� ��ȣ�� Ž���� �� �Է�: ");
        scanf_s("%d %d", &start_vertex, &end_vertex);

        for (int i = 0; i < MAX_VERTICES; i++)
            g->visited_node[i] = FALSE;     // �湮 �迭 �ʱ�ȭ

        switch (num) {
        case 1:
            if (!DepthFirstSearch(g, &s, start_vertex, end_vertex))
                printf("Ž�� ����\n");
            break;
        case 2:
            if (!BreadthFirstSearch(g, &q, start_vertex, end_vertex))
                printf("Ž�� ����\n");
            break;
        default:
            printf("�߸��� �Է�\n");
        }
    }
}

int main() {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    createGraph(g);
    for (int i = 0; i < 11; i++)
        insertVertex(g, i);
    GenerateLinkedGraph(g);
    menu(g);
    free(g);
    return 0;
}
