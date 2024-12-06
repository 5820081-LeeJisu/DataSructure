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

// 퀵정렬 - 분할
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

// 퀵 정렬
void QuickSort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		QuickSort(list, left, q - 1);
		QuickSort(list, q + 1, right);
	}
}

// 이진 탐색
// 탐색 범위의 중간에 있는 숫자와 비교하여 탐색 범위를 절반으로 줄임
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

// 보간 탐색
// 값과 위치는 비례한다는 가정에서 탐색키에 해당되는 위치를 비례식으로 구하는 것
double getAverageInterpolationSearchCompareCount(int array[]) {
	int j = 0;
	double totalCompare = 0;

	for (int i = 0; i < 1000; i++) {
		int target = array[rand() % SIZE];
		int middle;
		int low = 0;	// 탐색할 범위의 최소 인덱스 값
		int high = SIZE - 1;	// 탐색할 범위의 최대 인댁스 값
		compareCount = 0; 

		while ((array[high] >= target) && (target > array[low])) {		// 탐색 범위가 유효할 때
			if (low == high) {	// 배열의 범위가 하나로 줄어들었을 때 (탐색 범위를 좁히다가 결국 하나의 요소만 남았을 때)
				compareCount++;
				if (array[low] == target) 	// 타겟이 배열의 첫 번째 요소일 때
					compareCount++;
				break;
			}
			
			// 보간 공식, j: 탐색 위치
			j = ((float)(target - array[low]) / (array[high] - array[low]) * (high - low)) + low;	
			compareCount++;

			if (target > array[j]) {
				low = j + 1;
			}
			else if (target < array[j]) {
				high = j - 1;
			}
			else {	// 타겟을 찾았을 때
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