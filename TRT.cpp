#include<cstdio>

int _max(int a, int b) {return (a>b)?a:b;}

int main() {
    int n;
    scanf("%d",&n);
    int v[n];
    for (int i=0;i<n;i++) {
        scanf("%d", &v[i]);
    }
    int dp[n+1][n+1];
    int a = 1;
    dp[0][n] = 0;
    for (int col = n-1; col >= 0; col--) {
        dp[0][col] = dp[0][col+1] + a*v[col];
        for (int c = 1; c<=(n-col); c++) {
            dp[c][col+c] = _max(dp[c-1][col+c] + a*v[c-1], dp[c][col+c+1] + a*v[c+col]);
        }
        dp[n-col][n] = dp[n-col-1][n] + a*v[n-col-1];
        a++;
    }
    int max = -1;
    for (int i=0;i<=n;i++) {
        if (dp[i][i] > max) max = dp[i][i];
    }
    printf("%d\n", max);
}
