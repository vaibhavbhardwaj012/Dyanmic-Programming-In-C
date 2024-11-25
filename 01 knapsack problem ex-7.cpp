#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(int N, int W, int profit[], int weight[]) {
    int dp[N + 1][W + 1];
    for (int i = 0; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i - 1] <= w)
                dp[i][w] = max(profit[i - 1] + dp[i - 1][w - weight[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    printf("Maximum profit: %d\n", dp[N][W]);
}

int main() {
    int profit1[] = {2, 3, 1, 4}, weight1[] = {3, 4, 6, 5};
    knapsack(4, 8, profit1, weight1);

    int profit2[] = {60, 100, 120}, weight2[] = {10, 20, 30};
    knapsack(3, 50, profit2, weight2);

    int profit3[] = {2, 5, 8, 1}, weight3[] = {10, 15, 6, 9};
    knapsack(4, 50, profit3, weight3);

    return 0;
}

