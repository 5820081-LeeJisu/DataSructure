#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100 

int sorted[SIZE];	// 추가 공간 필요
int rounds = 0;		// 과정 출력 줄(라인)
int isFirst = 0;
int totalComparisons, totalMoves = 0;
int comparisonCount, moveCount = 0;

void generateRandomArray(int array[]) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++) { 
		array[i] = rand() % 1000;
	}
}

// 과정 출력
void printList(int array[]) {
	if (rounds % 10 == 0 && isFirst == 0) {		// 10번에 한번만 출력
		for (int i = 0; i < 10; i++)	// 0 ~ 9값
			printf("%3d ", array[i]);
		printf("| ");
		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)	 // (중앙 - 1) ~ (중앙 + 10)
			printf("%3d ", array[i]);
		printf("\n\n");
	}
}

// 결과 출력
void printArray(int list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
		if ((i + 1) % 20 == 0) 
			printf("\n");
	}
	printf("\n");
}

// 두 개의 정렬된 부분 배열을 합병
void merge(int list[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left, l; 
	// i: 정렬된 왼쪽리스트에 대한 인덱스
	// j: 정렬된 오른쪽리스트에 대한 인덱스
	// k: 정렬될 리스트에 대한 인덱스

	// 분할 정렬된 두 배열을 병합
	while (i <= mid && j <= right) {
		comparisonCount++;
		if (list[i] <= list[j])		// 왼쪽 배열의 현재 원소가 작거나 같으면
			sorted[k++] = list[i++];	// 왼쪽 원소를 병합 결과에 추가
		else 
			sorted[k++] = list[j++];	// 오른쪽 원소를 병합 결과에 추가
		moveCount++;
	}
	
	// 왼쪽 배열이 모두 병합됐을 때, 오른쪽 배열의 나머지 원소 복사
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			moveCount++;
		}
	}
	// 오른쪽 배열이 모두 병합됐을 때, 왼쪽 배열의 나머지 원소 복사
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			moveCount++;
		}
	}

	// 병합된 결과를 원본 배열에 복사
	for (int l = left; l <= right; l++) {
		list[l] = sorted[l];
		moveCount++;
	}

	rounds++;	// 병합 완료 후 단계 증가
	printList(list);
}

// 분할 --> 정복 --> 결합
// 1. 하나의 리스트를 두 개의 균등한 크기로 분할
// 2. 분할된 부분 리스트를 정렬
// 3. 두 개의 정렬된 부분 리스트 합하면 전체가 정렬된 리스트 완성
void doMergeSort(int list[], int left, int right) {
	int curr_size, left_start;

	// 단계별로 배열의 크기를 두 배씩 키워가며 정렬
	for (curr_size = 1; curr_size <= SIZE - 1; curr_size *= 2) {
		// 부분 배열의 시작 인덱스 설정
		for (left_start = 0; left_start < SIZE - 1; left_start += 2 * curr_size) {
			// 현재 부분 배열의 중간 지점 계산
			int mid = left_start + curr_size - 1;

			// 현재 부분 배열의 끝 지점 계산
			//전체 배열 크기를 초과하지 않도록 보정
			int right_end = (left_start + 2 * curr_size - 1 < SIZE - 1) ? left_start + 2 * curr_size - 1 : SIZE - 1;	
			
			// 현재 부분 배열의 크기가 정렬 대상이 아니라면 합병 생략  
			if (left_start + curr_size - 1 >= SIZE - 1)		
				continue;

			// 부분 배열들을 합병하여 정렬
			merge(list, left_start, mid, right_end);
		}
	}
}

int main() {
	srand((unsigned int)time(NULL));
	int array[SIZE];

	for (int i = 0; i < 20; i++) {
		generateRandomArray(array);
		comparisonCount = 0;
		moveCount = 0;

		if (i == 0) {
			printf("Merge Sort Run\n");
			doMergeSort(array, 0, SIZE - 1);

			printf("Result\n");
			printArray(array, SIZE);
			isFirst++;
		}
		else {
			doMergeSort(array, 0, SIZE - 1);
		}
		totalComparisons += comparisonCount;
		totalMoves += moveCount;
	}

	printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
	printf("Average Moves: %.2f\n", totalMoves / 20.0);

	return 0;
}