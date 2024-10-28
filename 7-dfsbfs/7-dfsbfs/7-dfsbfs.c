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

// 그래프 초기화
void createGraph(GraphType* g) {
    g->n = 0;   // 정점의 개수 0 
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->visited_node[v] = FALSE;     // 모든 정점을 방문하지 않은 상태로 초기화
        g->adj_list[v] = NULL;      // 인접 리스트를 NULL로 초기화
    }
}

// 그래프에 정점 삽입
void insertVertex(GraphType* g, int v) {
    if (g->n + 1 > MAX_VERTICES) return;    // 정점 수가 최대치를 넘을 때 리턴
    g->n++;
}

// 그래프에 간선 삽입
void insertEdge(GraphType* g, int tail, int head) {
    GraphNode* node;
    if ((tail >= g->n) || (head >= g->n)) return;   // 유효한 정점인지 확인
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = head;
    node->link = g->adj_list[tail];     // 인접 리스트에 간선 추가
    g->adj_list[tail] = node;
}

// 깊이 우선 탐색
int DepthFirstSearch(GraphType* g, LinkedStackType* s, int start, int end) {
    init_stack(s);
    int count = 0;

    push(s, start);     // 시작 정점 스택에 삽입
    g->visited_node[start] = TRUE;      // 시작 정점 방문한 걸로 처리
    printf("%d ", start);

    while (!is_empty_stack(s)) {
        int v = pop(s);
        GraphNode* node = g->adj_list[v];

        while (node != NULL) {
            int w = node->vertex;
            if (!g->visited_node[w]) {      // 방문하지 않은 노드일 때
                g->visited_node[w] = TRUE;
                printf("%d ", w);
                count++;

                if (w == end) {     // 탐색 성공 조건
                    printf("\n탐색 성공: %d\n", w);
                    printf("방문한 노드의 수: %d\n\n", count);
                    return TRUE;
                }

                push(s, v);     // 백트래킹
                push(s, w);
                break;
            }
            node = node->link;
        }
    }

    printf("\n탐색 실패: %d\n", end);
    return FALSE;
}

// 너비 우선 탐색
int BreadthFirstSearch(GraphType* g, LinkedQueueType* q, int start_vertex, int end_vertex) {
    GraphNode* current;
    int count = 0;

    init_queue(q);
    enqueue(q, (element)start_vertex);
    g->visited_node[start_vertex] = TRUE;

    while (!is_empty_queue(q)) {
        int v = (int)dequeue(q);
        printf("%d ", v);

        if (v == end_vertex) {      // 도착 정점에 도달했을 때
            printf("\n탐색 성공: %d\n", end_vertex);
            printf("방문한 노드의 수: %d\n\n", count);
            return TRUE;
        }

        for (current = g->adj_list[v]; current != NULL; current = current->link) {
            if (!g->visited_node[current->vertex]) {    // 방문하지 않은 정점을 큐에 삽입
                enqueue(q, (element)current->vertex);
                g->visited_node[current->vertex] = TRUE;
                count++;
            }
        }
    }

    printf("\n탐색 실패: %d\n", end_vertex);
    return FALSE;
}

// 그래프 생성, 간선 추가
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
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("| 1   : 깊이 우선 탐색    |\n");
    printf("| 2   : 너비 우선 탐색    |\n");
    printf("| 3   : 종료	          |\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    while (1) {
        printf("메뉴 입력: ");
        scanf_s("%d", &num);

        if (num == 3) return;   // 종료 조건

        printf("시작 번호와 탐색할 값 입력: ");
        scanf_s("%d %d", &start_vertex, &end_vertex);

        for (int i = 0; i < MAX_VERTICES; i++)
            g->visited_node[i] = FALSE;     // 방문 배열 초기화

        switch (num) {
        case 1:
            if (!DepthFirstSearch(g, &s, start_vertex, end_vertex))
                printf("탐색 실패\n");
            break;
        case 2:
            if (!BreadthFirstSearch(g, &q, start_vertex, end_vertex))
                printf("탐색 실패\n");
            break;
        default:
            printf("잘못된 입력\n");
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
