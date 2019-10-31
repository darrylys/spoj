#include<stdio.h>

#define MAXN 1000100

int dp[MAXN][2];
char str[MAXN];

int solve(int n, int l, int d) {
    if (str[n-1] == '0') {
        dp[n-1][0] = 1;
        dp[n-1][1] = 0;
    } else {
        dp[n-1][0] = 1;
        dp[n-1][1] = 1;
    }
    
    for (int i=n-2; i>=0; --i) {
        if (str[i] == '0') {
            dp[i][0] = dp[i+1][0] + dp[i+1][1];
            dp[i][1] = dp[i+1][1];
        } else {
            dp[i][1] = dp[i+1][0] + dp[i+1][1];
            dp[i][0] = dp[i+1][0];
        }
        dp[i][0] %= d;
        dp[i][1] %= d;
    }
    
    return dp[0][0];
}

int main() {
    int t, n, l, d;
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d %d %d", &n, &l, &d);
        getchar();
        
        for (int i=0; i<n-l; ++i) str[i]='0';
        for (int i=n-l; i<n; ++i) {
            str[i]=getchar();
        }
        str[n]='\0';
        //printf("%s\n", str);
        printf("%d\n", solve(n, l, d));
    }
}