#include <stdio.h>

#define ll long long
#define MOD 100003

#define MXN 501

int C[MXN][MXN];
int f[MXN][MXN];
int LF[MXN];

int gc(int n, int r) {
	if (n<r) return 0;
	return C[n][r];
}

inline int max(int a, int b) {
	return (a>b)?a:b;
}

void buildC() {
	C[0][0] = 1;
	
	for (int n=1; n<MXN; ++n) {
		C[n][0] = C[n][n] = 1;
		for (int i=1; i<n; ++i) {
			C[n][i] = C[n-1][i-1] + C[n-1][i];
			if (C[n][i] >= MOD) {
				C[n][i] -= MOD;
			}
		}
	}
	
}

int main() {
	buildC();
	
	for (int i=2; i<MXN; ++i) {
		
		f[i][1] = 1;
		f[i][i-1] = 1;
		
		for (int j=2, st; j<i-1; ++j) {
			
			f[i][j] = 0;
			st = max(1, 2*j-i);
			for (int k=st; k<j; ++k) {
				f[i][j] += ((ll)f[j][k] * gc(i-j-1, j-k-1)) % MOD;
			}
			if (f[i][j] >= MOD) {
				f[i][j] %= MOD;
			}
		}
	}
	
	for (int i=2; i<MXN; ++i) {
		for (int j=1; j<i; ++j) {
			LF[i] += f[i][j];
		}
		if (LF[i] >= MOD) {
			LF[i] %= MOD;
		}
	}
	
	int T, N, c=1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d\n", &N);
		
		printf("Case #%d: %d\n", c++, LF[N]);
	}
	/*
	for (int i=2; i<50; ++i) {
		for (int j=1; j<i; ++j) {
			printf("%lld\t", f[i][j]);
		}
		printf("\n");
	}
	
	for (int i=2; i<50; ++i) {
		printf("%d\n", LF[i]);
	}
	*/
}

