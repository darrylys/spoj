/*
T(n, k) = t(n, k, 0) + t(n, k, 1)

t(n, k, 0) = t(n-1, k, 0) + t(n-1, k, 1)
t(n, k, 1) = t(n-1, k, 0) + t(n-1, k-1, 1)

11111110

T(2, 0) = t(2, 0, 0) + t(2, 0, 1) = 1 + 0 = 1
*/

#include<stdio.h>

int dp[105][105][2];

void fill() {
    dp[1][0][1] = 1;
    dp[1][0][0] = 1;
    
    for (int n=2; n<=100; ++n) {
        for (int k=0; k<n; ++k) {
            dp[n][k][0] = dp[n-1][k][0] + dp[n-1][k][1];
            if (k > 0) {
                dp[n][k][1] = dp[n-1][k][0] + dp[n-1][k-1][1];
            } else {
                dp[n][k][1] = dp[n-1][k][0];
            }
        }
    }
}

int main() {
    fill();
    
    int t, d, n, k;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d %d %d\n", &d, &n, &k);
        printf("%d %d\n", d, dp[n][k][0]+dp[n][k][1]);
    }
}