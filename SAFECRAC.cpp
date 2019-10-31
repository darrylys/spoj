#include<stdio.h>

#define MAXN 100010
#define MOD 1000000007
#define DEBUG

int dp[MAXN][10];
int sum[MAXN];
int adj[10][5] = {
    {7,-1},
    {2,4,-1},
    {1,3,5,-1},
    {2,6,-1},
    {1,5,7,-1},
    {2,4,6,8,-1},
    {3,5,9,-1},
    {4,8,0,-1},
    {5,7,9,-1},
    {6,8,-1}
};


int main() {
    
    for (int i=0; i<10; ++i) {
        dp[1][i] = 1;
    }
    sum[1] = 10;
    
    for (int i=2; i<=100000; ++i) {
        sum[i] = 0;
        for (int j=0; j<10; ++j) {
            dp[i][j] = 0;
            for (int k=0; adj[j][k] != -1; ++k) {
                dp[i][j] += dp[i-1][adj[j][k]];
                dp[i][j] %= MOD;
            }
            sum[i] += dp[i][j];
            sum[i] %= MOD;
        }
    }
    
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", sum[n]);
    }
    
}