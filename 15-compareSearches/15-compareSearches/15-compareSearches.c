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

// 순차 탐색
double getAverageLinearSearchCompareCount(int array[]) {
	int totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE];	// 항상 존재하는 데이터에 대해 탐색하기 위해

		int compareCount = 0;

		for (int j = 0; j < SIZE; j++) {
			compareCount++;
			if (array[j] == target) break;
		}

		totalCompare += compareCount;
	}
	return (double)totalCompare / 100;
}

// 이진탐색은 정렬된 배열을 탐색하기 때문에 퀵 정렬 사용
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

// 퀵 정렬
void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

// 퀵 정렬 비교횟수 
int getQuickSortCompareCount(int array[]) {
	compareCount = 0;
	quick_sort(array, 0, SIZE - 1);

	return compareCount;
}

// 이진 탐색
// 탐색 범위의 중간에 있는 숫자와 비교하여 탐색 범위를 절반으로 줄임 
double getAverageBinarySearchCompareCount(int array[]) {	// 배열도 포인터다!! quick_sort로 정렬한 배열을 메인에서 그대로 받아옴 변하지 않음.
	double totalCompare = 0;
	for (int i = 0; i < 100; i++) {
		int target = array[rand() % SIZE];
		int middle;
		int low = 0;
		int high = SIZE - 1;
		int compareCount = 0;

		while (low <= high) {	// 아직 숫자들이 남아 있으면
			middle = (low + high) / 2;
			compareCount++;
			if (array[middle] == target)  // 탐색 성공
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