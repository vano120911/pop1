#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printMatrix(int **arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%4d ", arr[i][j]);
        }
        printf("\n");
    }
}


void freeMatrix(int **matrix, int n) {
    if (matrix == NULL) return;
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Не указано имя файла.\n");
        fprintf(stderr, "Использование: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    FILE *file;
    int N, M;
    int **matrix = NULL;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    if (fscanf(file, "%d %d", &N, &M) != 2) {
        fprintf(stderr, " Не удалось прочитать размеры N и M из файла.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (N <= 0 || M <= 0) {
        fprintf(stderr, " Размеры N и M должны быть положительными.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    matrix = (int **)malloc(N * sizeof(int *));
    if (matrix == NULL) {
        fprintf(stderr, "Не удалось выделить память для строк.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        matrix[i] = (int *)malloc(M * sizeof(int));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Не удалось выделить память для строки %d.\n", i);

            freeMatrix(matrix, i);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (fscanf(file, "%d", &matrix[i][j]) != 1) {
                fprintf(stderr, "Не удалось прочитать элемент matrix[%d][%d].\n", i, j);
                fprintf(stderr, "Проверьте, что формат файла верный.\n");
                freeMatrix(matrix, N);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);

    printMatrix(matrix, N, M);

    int sumDiagonal = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < M; j++) { 
            if (matrix[i][j] < 0) {
                sumDiagonal += matrix[i][j];
            }
        }
    }

    printf("\n z 1 \n");
    printf("Сумма отрицательных элементов над главной диагональю: %d\n", sumDiagonal);

    if (N < 3) {
        printf("В матрице меньше 3 строк (%d), невозможно выполнить операции с 3-й строкой.\n", N);
    } else {
        int rowIndex = 2;

        int maxElement = matrix[rowIndex][0];
        int maxElementColIndex = 0;

        for (int j = 1; j < M; j++) {
            if (matrix[rowIndex][j] > maxElement) {
                maxElement = matrix[rowIndex][j];
                maxElementColIndex = j;
            }
         }
        printf("\n z 2 \n");
        printf("Максимальный элемент в 3-й строке: %d (в столбце index  %d)\n", 
                maxElement, maxElementColIndex);


        printf("\n z 3\n");
        printf("Замена на сумму %d\n",
                sumDiagonal);

        matrix[rowIndex][maxElementColIndex] = sumDiagonal;

        printMatrix(matrix, N, M);
    }

    freeMatrix(matrix, N);

    return 0;
}
