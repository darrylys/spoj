#include<stdio.h>
#include<string.h>

#define MOD (1000000007)
#define MAXN (1002)
#define ll long long

int dp[MAXN][MAXN];
int asum[MAXN]; // sum to N, EXCLUSIVE!. asum[N] = sum(ai[0..N])
int ai[MAXN];

int F(int ndim, int side) {
	if (dp[ndim][side] != -1) return dp[ndim][side];
	
	if (ndim == 2) {
		return dp[ndim][side] = (((ll)asum[side] * (asum[side]-1))/2)%MOD;
	}
	
	if (ndim == 1) {
		return dp[ndim][side] = asum[side];
	}
	
	if (side < ((ndim>>1) + (ndim&1))) {
		return dp[ndim][side] = 0;
	}
	
	return dp[ndim][side] = (
		(ll)((ai[side])*(ai[side]-1)/2) * F(ndim-2, side-1) +
		(ll)(ai[side]) * F(ndim-1, side-1) +
		F(ndim, side-1)
	)%MOD;
}

int main() {
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		for (int i=1; i<=N; ++i) {
			scanf("%d", &ai[i]);
		}
		asum[0] = 0;
		for (int i=1; i<=N; ++i) {
			asum[i] = asum[i-1] + ai[i];
		}
		memset(dp, -1, sizeof(dp));
		printf("%d\n", F(N-1, N));
	}
}
