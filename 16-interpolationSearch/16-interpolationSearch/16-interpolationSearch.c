#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

int compareCount;

void generateRandomArray(int array[]) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000;
	}
}

void printArray(int* array) {
	printf("Array Sorting Result:\n");

	for (int i = 0; i < 20; i++)
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%4d ", array[i]);
	printf("\n\n");
}

// ������ - ����
int partition(int list[], int left, int right) {
	int pivot = list[left];
	int low = left + 1;
	int high = right;
	int temp;

	while (low <= high) {
		while (low <= right && list[low] <= pivot) {
			low++;
		}
		while (high >= left && list[high] > pivot) {
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
void QuickSort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		QuickSort(list, left, q - 1);
		QuickSort(list, q + 1, right);
	}
}

// ���� Ž��
// Ž�� ������ �߰��� �ִ� ���ڿ� ���Ͽ� Ž�� ������ �������� ����
double getAverageBinarySearchCompareCount(int array[]) {	
	double totalCompare = 0;
	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE];
		int middle;
		int low = 0;
		int high = SIZE - 1;
		compareCount = 0; 

		while (low <= high) {
			middle = (low + high) / 2;
			compareCount++; 

			if (array[middle] == target) {
				break;
			}
			else if (target > array[middle]) {
				low = middle + 1;
			}
			else {
				high = middle - 1;
			}
		}
		totalCompare += compareCount;
	}
	return (double)totalCompare / 1000;
}

// ���� Ž��
// ���� ��ġ�� ����Ѵٴ� �������� Ž��Ű�� �ش�Ǵ� ��ġ�� ��ʽ����� ���ϴ� ��
double getAverageInterpolationSearchCompareCount(int array[]) {
	int j = 0;
	double totalCompare = 0;

	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE];
		int middle;
		int low = 0;	// Ž���� ������ �ּ� �ε��� ��
		int high = SIZE - 1;	// Ž���� ������ �ִ� �δ콺 ��
		compareCount = 0; 

		while ((array[high] >= target) && (target > array[low])) {		// Ž�� ������ ��ȿ�� ��
			if (low == high) {	// �迭�� ������ �ϳ��� �پ����� �� (Ž�� ������ �����ٰ� �ᱹ �ϳ��� ��Ҹ� ������ ��)
				compareCount++;
				if (array[low] == target) 	// Ÿ���� �迭�� ù ��° ����� ��
					compareCount++;
				break;
			}
			
			// ���� ����, j: Ž�� ��ġ
			j = ((float)(target - array[low]) / (array[high] - array[low]) * (high - low)) + low;	
			compareCount++;

			if (target > array[j]) {
				low = j + 1;
			}
			else if (target < array[j]) {
				high = j - 1;
			}
			else {	// Ÿ���� ã���� ��
				low = j;
			}
		}
		totalCompare += compareCount;
	}
	return (double)totalCompare / 1000;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);

	QuickSort(array, 0, SIZE - 1);
	printArray(array);

	printf("Average Compare Count of Binary Search: %.2f\n", getAverageBinarySearchCompareCount(array));
	printf("Average Compare Count of Interpolation Search: %.2f\n", getAverageInterpolationSearchCompareCount(array));

	return 0;

}