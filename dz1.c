#include <stdio.h>


int sumdiv(int n);
void findcur(int current, int end);

int main() {
    int n, m;

    printf("введите два натуральных числа (начало и конец диапазона N и M): ");
    

    if (scanf("%d %d", &n, &m) != 2) {
        printf("два числа!!!!!!!!!!.\n");
        return 1;
    }

    if (n < 1 || m < 1) {
        printf("числа должны быть натуральными.\n");
        return 1;
    }

    if (n > m) {
        printf(" (N) не может быть больше (M).\n");
        return 1;
    }

    printf("цепочка чисел, у  которых сумма собственных делителей также четна:\n");
    findcur(n, m);
    printf("\n");

    return 0;
}


int sumdiv(int n) {
    if (n <= 1) {
        return 0;
    }

    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            if (i * i != n) {
                sum += n / i;
            }
        }
    }
    return sum;
}


void findcur(int current, int end) {
    if (current > end) {
        return;
    }

    if (current % 2 == 0) {
        int sum = sumdiv(current);

        if (sum % 2 == 0) {
            printf("%d ", current);
        }
    }


    findcur(current + 1, end);
}
