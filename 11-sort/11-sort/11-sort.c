#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// 랜덤 데이터 생성 
// 선택 및 버블 정렬에서 호출하기 때문에 함수를 위로 올림
void generateRandomData(int randomData[]) {
	for (int i = 0; i < SIZE; i++)
		randomData[i] = rand() % 1000;
}

// 정렬 과정 혹은 결과 출력
void print_list(int list[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

// 선택 정렬 - 최솟값을 선택해 배열에 차례로 대입하는데 이때 위치를 바꿔야 하므로 스왑 사용
void doSelectionSort(int list[]) {
	int i, least, temp;		// least: 최솟값 

	printf("Selection Sort:\n");
	for (i = 0; i <= SIZE - 1; i++) { 
		least = i;
		for (int j = i + 1; j < SIZE; j++)		// 최솟값 탐색
			if (list[j] < list[least]) least = j; 
		//temp = list[i];
		//list[i] = list[least];
		//list[least] = temp;

		SWAP(list[i], list[least], temp);

		if (( i + 10 ) % 20 == 0 || i == SIZE - 1) {	// 정렬 과정을 10부터 20단위로 출력, 마지막 번째 출력
			printf("STEP %d: ", i);
			print_list(list, SIZE);
			printf("\n");
		}
	}
}

// 삽입 정렬 - key 값을 선정해 lsit 값과 차례로 비교하며 적절한 위치에 삽입
void doInsertionSort(int list[]) {
	int i, j, key;
	int compareCount = 0;
	int averageCompare = 0;

	for (int k = 0; k < 20; k++) {
		int randomData[SIZE];	// 시도할 때마다 매번 다른 경우의 수를 만들어야 하기 때문에
		generateRandomData(randomData);		// 다시 데이터 생성
		compareCount = 0; 

		for (i = 1; i < SIZE; i++) {
			key = randomData[i];
			for (j = i - 1; j >= 0 && randomData[j] > key; j--) {	  // list랑 key 비교 이동 횟수			// (j = i - 1; j >= 0 && list[j] > key; j--)    
				if (randomData[j] > key) { 												// (반복문 조건에 중간 걸 여기로 빼냄)
					randomData[j + 1] = randomData[j];
					compareCount++;
				}
				else break;
			}
			compareCount++;
			randomData[j + 1] = key;
		}
		averageCompare += compareCount;
	}	
	
	printf("\nInsertion Sort Compare Average: %d\n", averageCompare / 20); 
	printf("Insertion Sort Result:\n");
	print_list(list, SIZE);
}

// 버블 정렬 - 인접한 2개의 값들을 비교하여 더 작은 값은 왼쪽에 큰 값은 오른쪽으로 교환함
void doBubbleSort(int list[]) {
	int i, j, temp;
	int moveCount = 0;
	int averageMove = 0; 
	int flag;			// 중간 뒤부터 정렬 안 되게 함

	for (int k = 0; k < 20; k++) {
		int randomData[SIZE];
		generateRandomData(randomData);
		moveCount = 0;  

		for (i = SIZE - 1; i > 0; i--) {
			flag = 0;
			for (j = 0; j < i; j++) {
				if (randomData[j] > randomData[j + 1]) {
					SWAP(randomData[j], randomData[j + 1], temp);
					moveCount += 3;		//swap 이동횟수 총 3번이기 때문에
					flag = 1;
				}
			}
			if (flag == 0) break;
		}
		averageMove += moveCount;
	}

	printf("\nBubble Sort Move Average: %d\n", averageMove / 20);
	printf("Bubble Sort Result:\n"); 
	print_list(list, SIZE);
}

int main() {
	int randomData[SIZE];

	srand((unsigned int)time(NULL));
	generateRandomData(randomData); 
 
	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);

	return 0;
}