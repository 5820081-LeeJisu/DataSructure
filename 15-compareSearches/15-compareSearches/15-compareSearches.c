#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int compareCount;

void generateRandomArray(int array[]) {
	for (int i = 0; i < 1000; i++) {
		array[i] = rand() % 1000;
	}
}

void printArray(int* array) {
	printf("Array Sorting Result:\n");

	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

// ���� Ž��
double getAverageLinearSearchCompareCount(int array[]) {
	int totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE];	// �׻� �����ϴ� �����Ϳ� ���� Ž���ϱ� ����

		int compareCount = 0;

		for (int j = 0; j < SIZE; j++) {
			compareCount++;
			if (array[j] == target) break;
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100;
}

// ����Ž���� ���ĵ� �迭�� Ž���ϱ� ������ �� ���� ���
int partition(int list[], int left, int right) {
	int pivot = list[left];
	int low = left + 1;
	int high = right;
	int temp;

	while (low <= high) {
		compareCount++;
		while (low <= right && list[low] <= pivot) {
			compareCount++;
			low++;
		}
		while (high >= left && list[high] > pivot) {
			compareCount++;
			high--;
		}
		if (low < high) {
			SWAP(list[low], list[high], temp);
		}
	}
	SWAP(list[left], list[high], temp);
	
	return high;
}

// �� ����
void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// �� ���� ��Ƚ�� 
int getQuickSortCompareCount(int array[]) {
	compareCount = 0;
	quick_sort(array, 0, SIZE - 1);

	return compareCount;
}

// ���� Ž��
// Ž�� ������ �߰��� �ִ� ���ڿ� ���Ͽ� Ž�� ������ �������� ���� 
double getAverageBinarySearchCompareCount(int array[]) {	// �迭�� �����ʹ�!! quick_sort�� ������ �迭�� ���ο��� �״�� �޾ƿ� ������ ����.
	double totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE];
		int middle;
		int low = 0;
		int high = SIZE - 1;
		int compareCount = 0;

		while (low <= high) {	// ���� ���ڵ��� ���� ������
			middle = (low + high) / 2;
			compareCount++;
			if (array[middle] == target)  // Ž�� ����
				break;
			else if (target > array[middle])  
				low = middle + 1;
			else 
				high = middle - 1;
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100;
}


int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];

	generateRandomArray(array);

	printf("Average Linear Search Compare Count %.2f\n", getAverageLinearSearchCompareCount(array));

	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);

	printf("Average Binary Search Compare Count: %.2f\n\n", getAverageBinarySearchCompareCount(array));

	printArray(array);

	return 0;

}