#include<stdio.h>

#define ull unsigned long long
#define MOD 1000000007

int dp[105][105][305];
char flag[105][105][305];

int calc(int N, int P, int K) {
    if (K<0 || N<0 || P<0) return 0;
    
    if (flag[N][P][K]) return dp[N][P][K];
    
    flag[N][P][K] = 1;
    
    if (N == 0) return dp[N][P][K] = 0;
    if (P >= N) return dp[N][P][K] = 0;
    if (K == 1 && P >= 1) return dp[N][P][K] = 0;
    if (K == 1 && P == 0) return dp[N][P][K] = 1;
    if (N == 1 && P == 0) return dp[N][P][K] = K;
    
    return dp[N][P][K] = (int)(((ull)K*((ull)calc(N-1,P,K) - calc(N-1,P,K-1) + MOD) 
        + calc(N-1,P-1,K-1) + calc(N,P,K-1))%MOD);
}

int main() {
    int t, N, P, K;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &N, &K, &P);
        printf("%d\n", calc(N, P, K));
    }
    return 0;
}
