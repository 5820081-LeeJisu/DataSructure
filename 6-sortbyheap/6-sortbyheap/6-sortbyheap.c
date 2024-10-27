#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// �迭 �� �� ��Ҹ� ��ȯ�ϴ� �Լ�
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// �� ���´� �θ��尡 �ڽĳ�庸�� ū ���¸� �����ؾ� �Ѵ�.
// �ڽĳ�尡 �θ��庸�� ū ��� �ڸ��� �ٲ� �� ���¸� �������ش�.
// �ڽ� ��� �� �� ū ��带 �θ���� �ڸ��� �ٲ۴�.
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // ���� ��带 �θ� ���� ����
    int left = 2 * i + 1;  // ���� �ڽ� ���
    int right = 2 * i + 2; // ������ �ڽ� ���

    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    if (largest != i) {
        swap(inputData, i, largest);
        resortHeap(inputData, n, largest); // ��� ȣ���Ͽ� �� ���¸� ����
    }
}

// ���ο� ��Ҹ� ���� �߰��ϰ� �ִ� ������ ������
void BuildMaxHeap(int heap[], int n, int value) {
    heap[n] = value; // ���� ���� �� �� �߰�
    int i = n;

    // �θ� ���� ���Ͽ� �� ���¸� �����ϱ� ���� ��������� �� ������
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// �ִ� ���� �����ϰ� �����ϴ� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    int heap[MAX_SIZE];
    int heapSize = 0;

    // �Է� �����͸� �ִ� ������ ��ȯ
    for (int i = 0; i < n; i++) {
        //max heap ����
        BuildMaxHeap(heap, heapSize, inputData[i]);
        heapSize++;
        // ���� �߰��� �� ���� �� ���� ���
        for (int j = 0; j < heapSize; j++) {
            printf("%d ", heap[j]);
        }
        printf("\n");
    }

    //�ϳ��� ������ ��Ʈ(�ִ밪)�� �����ϰ� ����
    for (int i = heapSize - 1; i >= 0; i--) {
        swap(heap, 0, i);  // ��Ʈ(�ִ밪)�� ������ ���� ��
        resortHeap(heap, i, 0);  // �� ������
        // ���� ���� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", heap[j]);
        }
        printf("\n");
        inputData[i] = heap[i]; 
    }


}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    //�� ���� ����
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    //���ĵ� ��� ���
    printf("Sorted Array: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
