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

void insert(int *a, int n, long long *swaps) {
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

void merge(int *a, int l, int m, int r, long long *swaps) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
        } else {
            a[k++] = R[j++];
        }
        (*swaps)++;
    }
    while (i < n1) { a[k++] = L[i++]; (*swaps)++; }
    while (j < n2) { a[k++] = R[j++]; (*swaps)++; }

    free(L);
    free(R);
}

void mergeSort(int *a, int l, int r, long long *swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m, swaps);
        mergeSort(a, m + 1, r, swaps);
        merge(a, l, m, r, swaps);
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

    printf("%-10s | %-20s | %-20s | %-20s\n", "N", "Bubble (sec)", "Insert (sec)", "Merge (sec)");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < tests; i++) {
        int n = sizes[i];
        int *orig = gen(n);
        int *wrk;
        long long s_bub = 0, s_ins = 0, s_mrg = 0;
        double t_bub = 0, t_ins = 0, t_mrg = 0;
        clock_t start, end;

        wrk = dup(orig, n);
        start = clock();
        bubble(wrk, n, &s_bub);
        end = clock();
        t_bub = (double)(end - start) / CLOCKS_PER_SEC;
        free(wrk);

        wrk = dup(orig, n);
        start = clock();
        insert(wrk, n, &s_ins);
        end = clock();
        t_ins = (double)(end - start) / CLOCKS_PER_SEC;
        free(wrk);

        wrk = dup(orig, n);
        start = clock();
        mergeSort(wrk, 0, n - 1, &s_mrg);
        end = clock();
        t_mrg = (double)(end - start) / CLOCKS_PER_SEC;
        free(wrk);

        printf("%-10d | %-20f | %-20f | %-20f\n", n, t_bub, t_ins, t_mrg);
        
        free(orig);
    }
    return 0;
}
