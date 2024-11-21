#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTAL_SIZE 1000 
#define ARRAY_SIZE 100 

// ���� ������ ����
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < 100; i++) {
        array[i] = rand() % 1000;
    }
}

// ���� �Ǵ� ��� ���
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%3d ", array[i]);
        if ((i + 1) % 20 == 0) printf("\n");
    }
    printf("\n");
}

// ���� ���� - key ���� ������ lsit ���� ���ʷ� ���ϸ� ������ ��ġ�� ����
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
            for (j = i - 1; j >= 0 && array[j] > key; j--) {	 // list�� key �� �̵� Ƚ��		    
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

        generateRandomNumbers(array);   // ���� �ƴ� �Ʒ��� ��� ���� array�� ����ϰ� 2��° �õ����� ���� ������ �� ����
    }
    *comparisonCount = sumComparison / 20; 
    *moveCount = sumMoves / 20;
}

// �� ���� - ������ ����(gap)��ŭ ������ ���� ��ġ �ٲ�
void doShellSort(int array[], int gapType, int* comparisonCount, int* moveCount) {
    int gap, i, j, temp;
    int comparison, moves;
    int sumComparison = 0;
    int sumMoves = 0;

    for (int k = 0; k < 20; k++) {
        comparison = 0, moves = 0;

        if (gapType == 2) { 
            for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {     // ������ 1�� �� ������ 1/2�� ����
                for (i = gap; i < ARRAY_SIZE; i++) {
                    temp = array[i];
                    moves++; 
                    for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                        array[j] = array[j - gap];
                        comparison++;
                        moves++; 
                    }
                    comparison++;      // ������ �� ����
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
                    comparison++;  // ������ �� ����
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

    // ������ ������� ���� ���ֱ� ����
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