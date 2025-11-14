#include <stdio.h>
#include <limits.h>
#define N 4


void printMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[N][N] = {
        { 1, -2,  3, -4},
        { 6,  7, -8,  9},
        { 1,  2,  3, 99},
        {-5,  4, -3,  2}
    };

    printf("--- Исходная матрица ---\n");
    printMatrix(matrix);

    int sumNegativeDiagonal = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (matrix[i][j] < 0) {
                sumNegativeDiagonal += matrix[i][j];
            }
        }
    }

    printf("\n[z 1]\n");
    printf("Сумма отрицательных элементов над главной диагональю: %d\n", sumNegativeDiagonal);
    int rowIndex = 2;

    int maxElement = matrix[rowIndex][0];
    int maxElementColIndex = 0;

    for (int j = 1; j < N; j++) {
        if (matrix[rowIndex][j] > maxElement) {
            maxElement = matrix[rowIndex][j];
            maxElementColIndex = j;
        }
    }
    printf("\n[z 2]\n");

    printf("Максимальный элемент в 3-й строке (индекс %d): %d\n", rowIndex, maxElement);

    printf("\n[z 3]\n");
    printf("Замена элемента matrix[%d][%d] (значение %d) на сумму %d\n", 
           rowIndex, maxElementColIndex, maxElement, sumNegativeDiagonal);

    matrix[rowIndex][maxElementColIndex] = sumNegativeDiagonal;


    printf("\n--- Итоговая матрица ---\n");
    printMatrix(matrix);

    return 0;
}
