#include<stdio.h>

#define INV2 (500000004)
#define MOD (1000000007)
#define MAXN (2502)
#define ll long long

int C[MAXN][MAXN];
//int _GCD[MAXN][MAXN];

inline int gcd(int a, int b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

void build() {
	for (int i=0; i<MAXN; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j=1; j<i; ++j) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
			if (C[i][j] >= MOD) C[i][j] -= MOD;
		}
	}
	/*
	for (int i=1; i<MAXN; ++i) {
		for (int j=1; j<=i; ++j) {
			_GCD[i][j] = gcd(i,j);
		}
	}
	*/
}

int find(int N) {
	int sum = 0;
	
	for (int i=1; i<=N; ++i) {
		int insum = 0;
		for (int j=1; j<=N; ++j) {
			insum = ((ll)insum + (ll)gcd(i,j) * C[N][j])%MOD;
		}
		
		sum = ((ll)sum + (ll)C[N][i]*insum)%MOD;
	}
	
	int decsum = 0;
	
	for (int i=1; i<=N; ++i) {
		decsum = (decsum + (ll)i * C[N][i])%MOD;
	}
	
	return ((ll)(sum - decsum + MOD) * INV2)%MOD;
}

int main() {
	build();
	
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		printf("%d\n", find(N));
	}
}
