#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_SIZE 1000 
#define ARRAY_SIZE 100 

// 랜덤 데이터 생성
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < 100; i++) {
        array[i] = rand() % 1000;
    }
}

// 과정 또는 결과 출력
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%3d ", array[i]);
        if ((i + 1) % 20 == 0) printf("\n");
    }
    printf("\n");
}

// 삽입 정렬 - key 값을 선정해 lsit 값과 차례로 비교하며 적절한 위치에 삽입
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int i, j, key;
    int comparison, moves;
    int sumComparison = 0;
    int sumMoves = 0; 

    for (int k = 0; k < 20; k++) {
        comparison = 0, moves = 0;

        for (i = 1; i < ARRAY_SIZE; i++) {
            key = array[i];
            moves++; 
            for (j = i - 1; j >= 0 && array[j] > key; j--) {	 // list랑 key 비교 이동 횟수		    
                if (array[j] > key) { 	 					
                    array[j + 1] = array[j];
                    comparison++; 
                    moves++; 
                }
                else break;
            }
            comparison++; 
            array[j + 1] = key;
            moves++;  
        }

        if (k == 0) {
            printf("Sorted insertionArray:\n");
            printArray(array);
        }

        sumComparison += comparison;
        sumMoves += moves; 

        generateRandomNumbers(array);   // 위가 아닌 아래에 써야 기존 array를 출력하고 2번째 시도부터 랜덤 생성할 수 있음
    }
    *comparisonCount = sumComparison / 20; 
    *moveCount = sumMoves / 20;
}

// 쉘 정렬 - 임의의 간격(gap)만큼 떨어진 값과 위치 바꿈
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int gap, i, j, temp;
    int comparison, moves;
    int sumComparison = 0;
    int sumMoves = 0;

    for (int k = 0; k < 20; k++) {
        comparison = 0, moves = 0;

        if (gapType == 2) { 
            for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {     // 간격이 1이 될 때까지 1/2씩 줄임
                for (i = gap; i < ARRAY_SIZE; i++) {
                    temp = array[i];
                    moves++; 
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap];
                        comparison++;
                        moves++; 
                    }
                    comparison++;      // 실패한 비교 포함
                    array[j] = temp;
                    moves++;
                }
                if (k == 0) { 
                    printf("Sorting with gap = %d:\n", gap);
                    for (int i = 0; i < 20; i++) {
                        printf("%2d ", array[i]);
                    }
                    printf("...\n\n");
                }
            }
            if (k == 0) { 
                printf("Sorted shellArray (gap = 2):\n");
                printArray(array);
            }
        }

        else if (gapType == 3) {
            for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) {
                for (i = gap; i < ARRAY_SIZE; i++) {
                    temp = array[i];
                    moves++; 
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap];
                        comparison++; 
                        moves++;
                    }
                    comparison++;  // 실패한 비교 포함
                    array[j] = temp;
                    moves++;
                }
                if (k == 0) {
                    printf("Sorting with gap = %d:\n", gap);
                    for (int i = 0; i < 20; i++) {
                        printf("%2d ", array[i]);
                    }
                    printf("...\n\n");
                }
            }
            if (k == 0) {
                printf("Sorted shellArray (gap = 3):\n");
                printArray(array);
            }
        }
        sumComparison += comparison;
        sumMoves += moves;

        generateRandomNumbers(array);
    }
    *comparisonCount = sumComparison / 20; 
    *moveCount = sumMoves / 20; 
}

int main() {
    int array[ARRAY_SIZE];
    int shell2[ARRAY_SIZE];
    int shell3[ARRAY_SIZE]; 
    int insert[ARRAY_SIZE]; 

    int comparisonCount, moveCount;

    srand(time(NULL));
    generateRandomNumbers(array);

    // 데이터 결과값을 같게 해주기 위해
    for (int i = 0; i < ARRAY_SIZE; i++) {  
        shell2[i] = array[i];
        shell3[i] = array[i];
        insert[i] = array[i];
    }

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(shell2, 2, &comparisonCount, &moveCount); 
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(shell3, 3, &comparisonCount, &moveCount);  
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(insert, &comparisonCount, &moveCount); 
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}