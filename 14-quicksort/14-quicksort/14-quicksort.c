#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_SIZE 1000 
#define SIZE 100 
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int sorted[SIZE];	// 추가 공간이 필요
int rounds, isFirst = 0;
double totalComparisons, totalMoveCount = 0;
int comparisonCount, moveCount = 0;

void generateRandomArray(int array[]) {
	for (int i = 0; i < 100; i++) {
		array[i] = rand() % 1000;
	}
}

// 정렬 과정 출력
void printList(int array[]) {
	if (rounds % 10 == 0 && isFirst == 0) {
		for (int i = 40; i < 60; i++)
			printf("%d ", array[i]);
		printf("\n\n");
	}
	rounds++;
}

// 정렬 결과 출력
void printArray(int array[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
		if ((i + 1) % 20 == 0) printf("\n");
	}
	printf("\n");
}

// 비균등하게 분할
// 1. 리스트의 첫 번째 요소가 pivot
// 2. 피벗보다 작은 요소들은 모두 피벗의 왼쪽이로 옮김. 피벗보다 큰 요소들은 모두 피벗의 오른쪽으로 옮김.
// (피벗보다 작은 값) (피벗) (피벗보다 큰 값) 의 형태로 정렬됨
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];	

	do {
		// 피벗보다 큰 값을 찾을 때까지 증가
		do {
			low++;
			comparisonCount++;
			moveCount++;
		} while (low <= right && list[low] < pivot);

		// 피벗보다 작은 값을 찾을 때까지 감소
		do {
			high--;
			comparisonCount++;
			moveCount++;
		} while (high >= left && list[high] > pivot);

		// low와 high가 교차하지 않았다면 스왑
		if (low < high) {
			SWAP(list[low], list[high], temp);
			moveCount += 3;
			printList(list);	
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);		// 피벗을 제자리에 배치
	moveCount += 3;
	printList(list);	

	return high;	// 피벗의 위치 반환
}

// 후입선출 방식으로 하위 배열 처리
// 하위 배열이 분할될 때마다 왼/오른쪽 하위 배열의 인덱스가 스택에 푸시됨
// 하위 배열은 역순으로 처리됨 (가장 최근 파티션이 먼저 처리됨)
void doQuickSort(int list[], int first, int last) {
	int size = last - first + 1;	// 정렬 대상 크기
	int* stack = (int*)malloc(size * sizeof(int));	

	if (!stack) { 
		printf("메모리 할당 실패\n");
		return;
	}

	int top = -1;

	// 초기 범위를 스택에 저장
	stack[++top] = first;
	stack[++top] = last;

	while (top >= 0) {	// 스택이 비어 있지 않을 때까지 반복
		last = stack[top--];	// 범위 끝
		first = stack[top--];	// 범위 시작

		// 배열을 분할하고 피벗의 위치 반환
		int p = partition(list, first, last);

		// 왼쪽 부분 배열이 존재하면 스택에 저장
		if (p - 1 > first) {
			stack[++top] = first;
			stack[++top] = p - 1;
		}

		// 오른쪽 부분 배열이 존재하면 스택에 저장
		if (p + 1 < last) {
			stack[++top] = p + 1;
			stack[++top] = last;
		}
	}
	free(stack); 
}

int main() {
	srand(time(NULL));
	int array[SIZE];

	for (int i = 0; i < 20; i++) {
		generateRandomArray(array);
		comparisonCount = 0;
		moveCount = 0;

		if (i == 0) {
			printf("Quick Sort Run\n");
			doQuickSort(array, 0, SIZE - 1);

			printf("Result\n");
			printArray(array, SIZE);
			isFirst++;
		}
		else {
			doQuickSort(array, 0, SIZE - 1);
		}
		totalComparisons += comparisonCount;
		totalMoveCount += moveCount;
	}

	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

	return 0;
}