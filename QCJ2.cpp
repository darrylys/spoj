#include<stdio.h>

#define MAXN 101
#define MOD 761238923

int dp[110][110];

void build() {
    dp[1][0] = dp[1][1] = 1;
    
    for (int n=2; n<MAXN; ++n) {
    
        dp[n][0] = 1;
        for (int k=1; k<n; ++k) {
            dp[n][k] = (dp[n][k-1] + dp[n-1][k])%MOD;
        }
        
        dp[n][n] = dp[n][n-1];
    }
}

int main() {
    build();
    
    int x;
    while(scanf("%d", &x) && x) {
        printf("%d\n", dp[x][x]);
    }
    return 0;
}