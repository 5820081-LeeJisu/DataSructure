#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100 

int sorted[SIZE];	// �߰� ���� �ʿ�
int rounds = 0;		// ���� ��� ��(����)
int isFirst = 0;
int totalComparisons, totalMoves = 0;
int comparisonCount, moveCount = 0;

void generateRandomArray(int array[]) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++) { 
		array[i] = rand() % 1000;
	}
}

// ���� ���
void printList(int array[]) {
	if (rounds % 10 == 0 && isFirst == 0) {		// 10���� �ѹ��� ���
		for (int i = 0; i < 10; i++)	// 0 ~ 9��
			printf("%3d ", array[i]);
		printf("| ");
		for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++)	 // (�߾� - 1) ~ (�߾� + 10)
			printf("%3d ", array[i]);
		printf("\n\n");
	}
}

// ��� ���
void printArray(int list[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
		if ((i + 1) % 20 == 0) 
			printf("\n");
	}
	printf("\n");
}

// �� ���� ���ĵ� �κ� �迭�� �պ�
void merge(int list[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left, l; 
	// i: ���ĵ� ���ʸ���Ʈ�� ���� �ε���
	// j: ���ĵ� �����ʸ���Ʈ�� ���� �ε���
	// k: ���ĵ� ����Ʈ�� ���� �ε���

	// ���� ���ĵ� �� �迭�� ����
	while (i <= mid && j <= right) {
		comparisonCount++;
		if (list[i] <= list[j])		// ���� �迭�� ���� ���Ұ� �۰ų� ������
			sorted[k++] = list[i++];	// ���� ���Ҹ� ���� ����� �߰�
		else 
			sorted[k++] = list[j++];	// ������ ���Ҹ� ���� ����� �߰�
		moveCount++;
	}
	
	// ���� �迭�� ��� ���յ��� ��, ������ �迭�� ������ ���� ����
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
			moveCount++;
		}
	}
	// ������ �迭�� ��� ���յ��� ��, ���� �迭�� ������ ���� ����
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
			moveCount++;
		}
	}

	// ���յ� ����� ���� �迭�� ����
	for (int l = left; l <= right; l++) {
		list[l] = sorted[l];
		moveCount++;
	}

	rounds++;	// ���� �Ϸ� �� �ܰ� ����
	printList(list);
}

// ���� --> ���� --> ����
// 1. �ϳ��� ����Ʈ�� �� ���� �յ��� ũ��� ����
// 2. ���ҵ� �κ� ����Ʈ�� ����
// 3. �� ���� ���ĵ� �κ� ����Ʈ ���ϸ� ��ü�� ���ĵ� ����Ʈ �ϼ�
void doMergeSort(int list[], int left, int right) {
	int curr_size, left_start;

	// �ܰ躰�� �迭�� ũ�⸦ �� �辿 Ű������ ����
	for (curr_size = 1; curr_size <= SIZE - 1; curr_size *= 2) {
		// �κ� �迭�� ���� �ε��� ����
		for (left_start = 0; left_start < SIZE - 1; left_start += 2 * curr_size) {
			// ���� �κ� �迭�� �߰� ���� ���
			int mid = left_start + curr_size - 1;

			// ���� �κ� �迭�� �� ���� ���
			//��ü �迭 ũ�⸦ �ʰ����� �ʵ��� ����
			int right_end = (left_start + 2 * curr_size - 1 < SIZE - 1) ? left_start + 2 * curr_size - 1 : SIZE - 1;	
			
			// ���� �κ� �迭�� ũ�Ⱑ ���� ����� �ƴ϶�� �պ� ����  
			if (left_start + curr_size - 1 >= SIZE - 1)		
				continue;

			// �κ� �迭���� �պ��Ͽ� ����
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