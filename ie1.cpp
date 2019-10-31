#include <stdio.h>
#include <string.h>

#define MOD (2004)
//#define DEBUG

int pf[11][6] = {
	{0, -1},			//0
	{1, -1}, 			//1
	{2, -1},			//2
	{3, -1},			//3
	{2, 2, -1},			//4
	{5, -1},			//5
	{2, 3, -1},			//6
	{7, -1},			//7
	{2, 2, 2,-1},		//8
	{3, 3,-1},			//9
	{2, 5,-1}			//10
};

int primes[] = {2,3,5,7};

// C(v,c)
int C(int v, int c) {
	// N=[v, v-c+1], c!
	
	if (v < c) return 0;
	if (v == c) return 1;
	
	int Q[11];
	bool flag[11] = {0};
	
	int PFS[11];
	memset(PFS, 0, sizeof PFS);
	
	for (int i=0; i<c; ++i) {
		Q[i] = v-i;
	}
	
	for (int j=2; j<=c; ++j) {
		for (int k=0; pf[j][k] != -1; ++k) {
			PFS[pf[j][k]]++;
		}
	}
	
	for (int i=0; i<c; ++i) {
		for (int j=0; j<4; ++j) {
			while (PFS[primes[j]] > 0 && (Q[i] % primes[j] == 0)) {
				Q[i] /= primes[j];
				PFS[primes[j]]--;
			}
		}
	}
	
	#ifdef DEBUG
	printf("end: Q: [");
	for (int i=0; i<c; ++i) {
		printf("%d ", Q[i]);
	}
	printf("]\n");
	#endif
	
	int res = 1;
	for (int i=0; i<c; ++i) {
		res = (res * (Q[i]%MOD))%MOD;
	}
	
	return res;
}

int calc(int X, int * M, int N) {
	if (X < 0) return 0;
	if (X == 0) return 1;
	
	int exps[1024];
	
	int expl=1;
	int p;
	exps[0] = 0;
	for (int i=0; i<N; ++i) {
		p=expl;
		for (int j=0; j<expl; ++j) {
			if (exps[j] >= 0) {
				exps[p] = -(exps[j] + (M[i]+1));
			} else {
				exps[p] = (-exps[j] + (M[i]+1));
			}
			++p;
		}
		expl<<=1;
	}
	
	#ifdef DEBUG
	printf("EXPS: [");
	for (int i=0; i<expl; ++i) {
		printf("%d ", exps[i]);
	}
	printf("]\n");
	#endif
	
	int sum = 0;
	for (int i=0; i<expl; ++i) {
		int expv = exps[i];
		int sgn = 1;
		if (exps[i] < 0) {
			sgn = -1;
			expv = -exps[i];
		}
		sum = (sum + (sgn + MOD) * C(X - expv + N, N))%MOD;
	}
	return sum;
}

int main() {
	int N, A, B;
	int M[12];
	
	scanf("%d %d %d", &N, &A, &B);
	for (int i=0;i<N; ++i) {
		scanf("%d", &M[i]);
	}
	
	int end = calc(B, M, N);
	int start = calc(A-1, M, N);
	
	#ifdef DEBUG
	printf("start=%d, end=%d\n", start, end);
	#endif
	
	printf("%d\n", (end-start+MOD)%MOD);
}
