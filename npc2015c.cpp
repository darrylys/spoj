#include <stdio.h>
#include <string.h>

#define MOD (1000000007)
#define MAXN 1005
#define MAXK 105

unsigned int dp[MAXN][MAXK][3];
bool flag[MAXN][MAXK][3];

unsigned int get(int N, int K, int lm) {
	if (K < 0) {
		return 0;
	}
	
	if (flag[N][K][lm]) {
		return dp[N][K][lm];
	}
	
	flag[N][K][lm] = true;
	
	if (N == 0) {
		return dp[N][K][lm] = 0;
	}
	
	if (K == 0) {
		if (lm == 0) return dp[N][K][lm] = 1;
		else return dp[N][K][lm] = 0;
	}
	
	if (N == 1 && K >= 1) {
		return dp[N][K][lm] = 1;
	}
	
	/*f(n,k,0) = f(n-1,k,0)+f(n-1,k,1)+f(n-1,k,2)
	f(n,k,1) = f(n-1,k-1,0)+f(n-1,k-1,2)
	f(n,k,2) = f(n-1,k-1,0)+f(n-1,k-1,1)*/
	
	if (lm == 0) {
		return dp[N][K][0] = (get(N-1, K, 0) + get(N-1, K, 1) + get(N-1, K, 2))%MOD;
	} else if (lm == 1) {
		return dp[N][K][1] = (get(N-1, K-1, 0) + get(N-1, K-1, 2))%MOD;
	} else {
		return dp[N][K][2] = (get(N-1, K-1, 0) + get(N-1, K-1, 1))%MOD;
	}
	
}

int main() {
	int T, N, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);
		if (N <= 2) {
			printf("1\n");
		} else {
			printf("%u\n", (get(N-2, K, 0) + get(N-2, K, 1) + get(N-2, K, 2))%MOD);
		}
	}
	
}
