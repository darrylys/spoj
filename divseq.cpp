#include <stdio.h>

#define MAXK (1001)
#define MAXN (1001)
#define MOD (1000000009)

#define ll long long

int div[MAXK][40];
int ndiv[MAXK];
int dp[MAXN][MAXK];

void buildDivs(int K) {
	for (int i=1; i<=K; ++i) {
		ndiv[i] = 0;
		for (int j=1; j*j <= i; ++j) {
			if (i%j == 0) {
				div[i][ndiv[i]++] = j;
				
				if (i/j != j) {
					div[i][ndiv[i]++] = i/j;
				}
			}
		}
	}
	
}

int get(int N, int K) {
	
	// N == 1
	for (int k=1; k<=K; ++k) {
		dp[1][k] = 1;
	}
	
	for (int i=2; i<=N; ++i) {
		
		for (int k=1; k<=K; ++k) {
			
			dp[i][k] = 0;
			
			// d|k, d != k
			for (int id=0, d; id < ndiv[k]; ++id) {
				d = div[k][id];
				if (d == k) {
					continue;
				}
				
				dp[i][k] += dp[i-1][d];
				dp[i][k] %= MOD;
			}
			
			// k|d, d != k
			for (int d=2*k; d <= K; d += k) {
				dp[i][k] += dp[i-1][d];
				dp[i][k] %= MOD;
			}
			
			
			dp[i][k] += dp[i-1][k];
			dp[i][k] %= MOD;
		}
	}
	
	int sum=0;
	for (int k=1; k<=K; ++k) {
		sum += dp[N][k];
		sum %= MOD;
	}
	return sum;
}

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	
	buildDivs(K);
	
	printf("%d\n", get(N, K));
	return 0;
}
