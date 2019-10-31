#include<stdio.h>
#include<string.h>

#define ll long long
#define MOD (1000000007)
#define MAXN (50)

typedef struct _MATRIX {
	int m[MAXN][MAXN];
	int n;
} M;

M ID;

void buildIdentityM(M& a) {
	memset(a.m, 0, sizeof(a.m));
	for (int i=0; i<a.n; ++i) a.m[i][i] = 1;
}

void matMul(M& a, M& b, M& result) {
	result.n = a.n;
	
	for (int i=0; i<a.n; ++i) {
		for (int j=0; j<b.n; ++j) {
			result.m[i][j] = 0;
			for (int k=0; k<result.n; ++k) {
				result.m[i][j] += ((ll)a.m[i][k] * b.m[k][j])%MOD;
				result.m[i][j] %= MOD;
			}
		}
	}
}

M matMulExp(M& base, int exp, int mod) {
	if (exp == 0) {
		return ID;
	}
	
	if (exp == 1) {
		return base;
	}
	
	M half = matMulExp(base, exp>>1, mod);
	M half2;
	matMul(half, half, half2);
	
	if (exp&1) {
		M half3;
		matMul(half2, base, half3);
		return half3;
	} else {
		return half2;
	}
}

M buildOp1M(int N, int K) {
	M op;
	op.n = N;
	
	memset(op.m, 0, sizeof(op.m));
	
	for (int c=0; c<N; ++c) {
		for (int r=0; r<K; ++r) {
			if (r&1) {
				op.m[(r+c)%N][c] = MOD-1;
				//op.m[(r+c)%N][c] = -1;
			} else {
				op.m[(r+c)%N][c] = 1;
			}
			
		}
	}
	
	return op;
}

M buildOp2M(int N) {
	M op;
	op.n = N;
	
	memset(op.m, 0, sizeof(op.m));
	for (int i=0; i<N; i+=2) {
		op.m[i+1][i] = 1;
		op.m[i][i+1] = 1;
	}
	if (N&1) {
		op.m[N-1][N-1] = 1;
	}
	
	return op;
}

void printM(M& a) {
	for (int i=0; i<a.n; ++i) {
		for (int j=0; j<a.n; ++j) {
			printf("%d\t", a.m[i][j]);
		}
		putchar('\n');
	}
}

int main() {
	buildIdentityM(ID);
	
	int N, K, T, EXP;
	int seq[MAXN];
	scanf("%d", &T);
	
	while (T--) {
		scanf("%d %d %d", &N, &K, &EXP);
		
		for (int i=0; i<N; ++i) {
			scanf("%d", &seq[i]);
			if (seq[i] < 0) seq[i] += MOD;
		}
		
		M op1 = buildOp1M(N,K);
		M op2 = buildOp2M(N);
		
		//printf("Op1\n"); printM(op1);
		//printf("\nOp2\n"); printM(op2);
		
		M opt;
		matMul(op1, op2, opt);
		
		M last = matMulExp(opt, EXP, MOD);
		
		for (int c=0; c<N; ++c) {
			ll sum = 0;
			for (int i=0; i<N; ++i) {
				sum += ((ll)seq[i] * last.m[i][c])%MOD;
			}
			printf("%d ", sum%MOD);
		}
		putchar('\n');
		
	}
	
	
	return 0;
}
