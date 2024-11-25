#include <stdio.h>
#include <string.h>

void printLCS(int dp[][100], char *S1, char *S2, int m, int n) {
    if (m == 0 || n == 0)
        return;
    if (S1[m - 1] == S2[n - 1]) {
        printLCS(dp, S1, S2, m - 1, n - 1);
        printf("%c", S1[m - 1]);
    } else if (dp[m - 1][n] > dp[m][n - 1])
        printLCS(dp, S1, S2, m - 1, n);
    else
        printLCS(dp, S1, S2, m, n - 1);
}

void LCS(char *S1, char *S2) {
    int m = strlen(S1), n = strlen(S2);
    int dp[100][100];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
        }
    }
    printf("LCS Length: %d\nLCS: ", dp[m][n]);
    printLCS(dp, S1, S2, m, n);
    printf("\n");
}

int main() {
    char S1[] = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    char S2[] = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    LCS(S1, S2);
    return 0;
}

