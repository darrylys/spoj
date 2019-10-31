#include<stdio.h>

#define MOD 1000000007

int dp[22][100010];

inline int getdp(int N, int M) {
    if (M<=0) return 0;
    else return dp[N][M];
}

void build() {
    for (int M=1; M<=100005; ++M) {
        dp[0][M] = 1;
    }
    for (int N=1; N<=20; ++N) {
        for (int M=1; M<=100005; ++M) {
            dp[N][M] = getdp(N-1, M-N) + getdp(N, M-N-1);
            if (dp[N][M] >= MOD) dp[N][M] -= MOD;
        }
    }
}

int main() {
    build();
    
    int t, N, M;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &N, &M);
        
        int sum = 0;
        for (int i=0; i<=N; ++i) {
            sum += dp[N][M-i+1];
            if (sum >= MOD) sum -= MOD;
        }
        printf("%d\n", sum);
    }
    
}
