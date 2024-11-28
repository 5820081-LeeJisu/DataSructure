#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_SIZE 1000 
#define SIZE 100 
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int sorted[SIZE];	// �߰� ������ �ʿ�
int rounds, isFirst = 0;
double totalComparisons, totalMoveCount = 0;
int comparisonCount, moveCount = 0;

void generateRandomArray(int array[]) {
	for (int i = 0; i < 100; i++) {
		array[i] = rand() % 1000;
	}
}

// ���� ���� ���
void printList(int array[]) {
	if (rounds % 10 == 0 && isFirst == 0) {
		for (int i = 40; i < 60; i++)
			printf("%d ", array[i]);
		printf("\n\n");
	}
	rounds++;
}

// ���� ��� ���
void printArray(int array[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
		if ((i + 1) % 20 == 0) printf("\n");
	}
	printf("\n");
}

// ��յ��ϰ� ����
// 1. ����Ʈ�� ù ��° ��Ұ� pivot
// 2. �ǹ����� ���� ��ҵ��� ��� �ǹ��� �����̷� �ű�. �ǹ����� ū ��ҵ��� ��� �ǹ��� ���������� �ű�.
// (�ǹ����� ���� ��) (�ǹ�) (�ǹ����� ū ��) �� ���·� ���ĵ�
int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];	

	do {
		// �ǹ����� ū ���� ã�� ������ ����
		do {
			low++;
			comparisonCount++;
			moveCount++;
		} while (low <= right && list[low] < pivot);

		// �ǹ����� ���� ���� ã�� ������ ����
		do {
			high--;
			comparisonCount++;
			moveCount++;
		} while (high >= left && list[high] > pivot);

		// low�� high�� �������� �ʾҴٸ� ����
		if (low < high) {
			SWAP(list[low], list[high], temp);
			moveCount += 3;
			printList(list);	
		}
	} while (low < high);

	SWAP(list[left], list[high], temp);		// �ǹ��� ���ڸ��� ��ġ
	moveCount += 3;
	printList(list);	

	return high;	// �ǹ��� ��ġ ��ȯ
}

// ���Լ��� ������� ���� �迭 ó��
// ���� �迭�� ���ҵ� ������ ��/������ ���� �迭�� �ε����� ���ÿ� Ǫ�õ�
// ���� �迭�� �������� ó���� (���� �ֱ� ��Ƽ���� ���� ó����)
void doQuickSort(int list[], int first, int last) {
	int size = last - first + 1;	// ���� ��� ũ��
	int* stack = (int*)malloc(size * sizeof(int));	

	if (!stack) { 
		printf("�޸� �Ҵ� ����\n");
		return;
	}

	int top = -1;

	// �ʱ� ������ ���ÿ� ����
	stack[++top] = first;
	stack[++top] = last;

	while (top >= 0) {	// ������ ��� ���� ���� ������ �ݺ�
		last = stack[top--];	// ���� ��
		first = stack[top--];	// ���� ����

		// �迭�� �����ϰ� �ǹ��� ��ġ ��ȯ
		int p = partition(list, first, last);

		// ���� �κ� �迭�� �����ϸ� ���ÿ� ����
		if (p - 1 > first) {
			stack[++top] = first;
			stack[++top] = p - 1;
		}

		// ������ �κ� �迭�� �����ϸ� ���ÿ� ����
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