#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubble(int *a, int n, long long *swaps) {
    *swaps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                (*swaps)++;
            }
        }
    }
}

void insertion(int *a, int n, long long *swaps) {
    *swaps = 0;
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            (*swaps)++;
        }
        a[j + 1] = key;
    }
}

int partition(int *a, int low, int high, long long *swaps) {
    int pivot = a[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (a[j] < pivot) {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
            (*swaps)++;
        }
    }
    int t = a[i + 1];
    a[i + 1] = a[high];
    a[high] = t;
    (*swaps)++;
    return (i + 1);
}

void quickSort(int *a, int low, int high, long long *swaps) {
    if (low < high) {
        int pi = partition(a, low, high, swaps);
        quickSort(a, low, pi - 1, swaps);
        quickSort(a, pi + 1, high, swaps);
    }
}

int* gen(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = rand() % 10000;
    return arr;
}

int* dup(int *src, int n) {
    int *dest = (int*)malloc(n * sizeof(int));
    memcpy(dest, src, n * sizeof(int));
    return dest;
}

int main() {
    srand(time(NULL));
    int sizes[] = {10, 1000, 10000, 100000};
    int tests = 4;

    printf("%-10s | %-20s | %-20s | %-20s\n", "N", "Bubble (sec)", "Insert (sec)", "Quick (sec)");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < tests; i++) {
        int n = sizes[i];
        int *orig = gen(n);
        int *wrk;
        long long s_bub = 0, s_ins = 0, s_qs = 0;
        double t_bub = 0, t_ins = 0, t_qs = 0;
        clock_t start, end;

        wrk = dup(orig, n);
        start = clock();
        bubble(wrk, n, &s_bub);
        end = clock();
        t_bub = (double)(end - start) / CLOCKS_PER_SEC;
        free(wrk);

        wrk = dup(orig, n);
        start = clock();
        insertion(wrk, n, &s_ins);
        end = clock();
        t_ins = (double)(end - start) / CLOCKS_PER_SEC;
        free(wrk);

        wrk = dup(orig, n);
        start = clock();
        quickSort(wrk, 0, n - 1, &s_qs);
        end = clock();
        t_qs = (double)(end - start) / CLOCKS_PER_SEC;
        free(wrk);

        printf("%-10d | %-20f | %-20f | %-20f\n", n, t_bub, t_ins, t_qs);
        free(orig);
    }
    return 0;
}
