#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }

int knapsackBacktrack(int W, int wt[], int val[], int n, int idx) {
    if (idx == n || W == 0) return 0;

    if (wt[idx] > W)
        return knapsackBacktrack(W, wt, val, n, idx + 1);

    return max(val[idx] + knapsackBacktrack(W - wt[idx], wt, val, n, idx + 1),
               knapsackBacktrack(W, wt, val, n, idx + 1));
}

int main() {
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    printf("Backtracking: Maximum value: %d\n", knapsackBacktrack(W, wt, val, n, 0));
    return 0;
}

