#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )

// ���� ������ ���� 
// ���� �� ���� ���Ŀ��� ȣ���ϱ� ������ �Լ��� ���� �ø�
void generateRandomData(int randomData[]) {
	for (int i = 0; i < SIZE; i++)
		randomData[i] = rand() % 1000;
}

// ���� ���� Ȥ�� ��� ���
void print_list(int list[], int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

// ���� ���� - �ּڰ��� ������ �迭�� ���ʷ� �����ϴµ� �̶� ��ġ�� �ٲ�� �ϹǷ� ���� ���
void doSelectionSort(int list[]) {
	int i, least, temp;		// least: �ּڰ� 

	printf("Selection Sort:\n");
	for (i = 0; i <= SIZE - 1; i++) { 
		least = i;
		for (int j = i + 1; j < SIZE; j++)		// �ּڰ� Ž��
			if (list[j] < list[least]) least = j; 
		//temp = list[i];
		//list[i] = list[least];
		//list[least] = temp;

		SWAP(list[i], list[least], temp);

		if (( i + 10 ) % 20 == 0 || i == SIZE - 1) {	// ���� ������ 10���� 20������ ���, ������ ��° ���
			printf("STEP %d: ", i);
			print_list(list, SIZE);
			printf("\n");
		}
	}
}

// ���� ���� - key ���� ������ lsit ���� ���ʷ� ���ϸ� ������ ��ġ�� ����
void doInsertionSort(int list[]) {
	int i, j, key;
	int compareCount = 0;
	int averageCompare = 0;

	for (int k = 0; k < 20; k++) {
		int randomData[SIZE];	// �õ��� ������ �Ź� �ٸ� ����� ���� ������ �ϱ� ������
		generateRandomData(randomData);		// �ٽ� ������ ����
		compareCount = 0; 

		for (i = 1; i < SIZE; i++) {
			key = randomData[i];
			for (j = i - 1; j >= 0 && randomData[j] > key; j--) {	  // list�� key �� �̵� Ƚ��			// (j = i - 1; j >= 0 && list[j] > key; j--)    
				if (randomData[j] > key) { 												// (�ݺ��� ���ǿ� �߰� �� ����� ����)
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

// ���� ���� - ������ 2���� ������ ���Ͽ� �� ���� ���� ���ʿ� ū ���� ���������� ��ȯ��
void doBubbleSort(int list[]) {
	int i, j, temp;
	int moveCount = 0;
	int averageMove = 0; 
	int flag;			// �߰� �ں��� ���� �� �ǰ� ��

	for (int k = 0; k < 20; k++) {
		int randomData[SIZE];
		generateRandomData(randomData);
		moveCount = 0;  

		for (i = SIZE - 1; i > 0; i--) {
			flag = 0;
			for (j = 0; j < i; j++) {
				if (randomData[j] > randomData[j + 1]) {
					SWAP(randomData[j], randomData[j + 1], temp);
					moveCount += 3;		//swap �̵�Ƚ�� �� 3���̱� ������
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