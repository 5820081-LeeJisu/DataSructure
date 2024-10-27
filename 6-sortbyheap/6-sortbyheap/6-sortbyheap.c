#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 배열 내 두 요소를 교환하는 함수
void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 힙 상태는 부모노드가 자식노드보다 큰 상태를 유지해야 한다.
// 자식노드가 부모노드보다 큰 경우 자리를 바꿔 힙 상태를 유지해준다.
// 자식 노드 중 더 큰 노드를 부모노드와 자리를 바꾼다.
void resortHeap(int inputData[], int n, int i) {
    int largest = i; // 현재 노드를 부모 노드로 간주
    int left = 2 * i + 1;  // 왼쪽 자식 노드
    int right = 2 * i + 2; // 오른쪽 자식 노드

    if (left < n && inputData[left] > inputData[largest])
        largest = left;

    if (right < n && inputData[right] > inputData[largest])
        largest = right;

    if (largest != i) {
        swap(inputData, i, largest);
        resortHeap(inputData, n, largest); // 재귀 호출하여 힙 상태를 유지
    }
}

// 새로운 요소를 힙에 추가하고 최대 힙으로 재정렬
void BuildMaxHeap(int heap[], int n, int value) {
    heap[n] = value; // 힙의 끝에 새 값 추가
    int i = n;

    // 부모 노드와 비교하여 힙 상태를 유지하기 위해 상향식으로 힙 재정렬
    while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

// 최대 힙을 구성하고 정렬하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    int heap[MAX_SIZE];
    int heapSize = 0;

    // 입력 데이터를 최대 힙으로 변환
    for (int i = 0; i < n; i++) {
        //max heap 생성
        BuildMaxHeap(heap, heapSize, inputData[i]);
        heapSize++;
        // 힙에 추가된 후 현재 힙 상태 출력
        for (int j = 0; j < heapSize; j++) {
            printf("%d ", heap[j]);
        }
        printf("\n");
    }

    //하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = heapSize - 1; i >= 0; i--) {
        swap(heap, 0, i);  // 루트(최대값)를 끝으로 보낸 후
        resortHeap(heap, i, 0);  // 힙 재정렬
        // 정렬 과정 출력
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

    //힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    //정렬된 결과 출력
    printf("Sorted Array: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
