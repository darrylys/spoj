#include<stdio.h>

#define MOD 1000000007
#define ll long long


int dp[102][5000];

void makedp() {
    dp[1][0] =1;
    for (int i=2, _k; i<=100; ++i) {
        _k = (i)*(i-1)/2;
        dp[i][0] = 1;
        for (int j=1; j<i; ++j) {
            dp[i][j] = (dp[i][j-1] + dp[i-1][j])%MOD;
        }
        
        for (int j=i; j<=_k; ++j) {
            dp[i][j] = (int)(((ll)dp[i][j-1] - dp[i-1][j-i] + dp[i-1][j] + MOD)%MOD);
        }
    }
}

void printdp() {
    for (int i=1; i<=100; ++i) {
        for (int j=0; j<=i*(i-1)/2; ++j) {
            printf("%10d ", dp[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    makedp();
    //printdp();
    int t, n, k, c=1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        if (k > n*(n-1)/2) {
            printf("Case %d: 0\n", c++);
        } else {
            printf("Case %d: %d\n", c++, dp[n][k]);
        }
    }
    return 0;
}