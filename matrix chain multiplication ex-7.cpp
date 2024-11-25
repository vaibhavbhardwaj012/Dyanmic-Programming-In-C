#include <stdio.h>
#include <limits.h>

void printParenthesis(int i, int j, int n, int *brackets, char *name) {
    if (i == j) {
        printf("%c", (*name)++);
        return;
    }
    printf("(");
    printParenthesis(i, *((brackets + i * n) + j), n, brackets, name);
    printParenthesis(*((brackets + i * n) + j) + 1, j, n, brackets, name);
    printf(")");
}

void matrixChainOrder(int p[], int n) {
    int m[n][n], brackets[n][n];
    for (int i = 1; i < n; i++) m[i][i] = 0;
    for (int l = 2; l < n; l++) {
        for (int i = 1; i < n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    brackets[i][j] = k;
                }
            }
        }
    }
    char name = 'A';
    printf("Optimal Parenthesization: ");
    printParenthesis(1, n - 1, n, (int *)brackets, &name);
    printf("\nMinimum cost: %d\n", m[1][n - 1]);
}

int main() {
    int arr1[] = {40, 20, 30, 10, 30};
    matrixChainOrder(arr1, 5);

    int arr2[] = {10, 30, 5, 60};
    matrixChainOrder(arr2, 4);

    return 0;
}

