/*
AC 0.12s 8.9M SPOJ

algo: classic DP
some sicko decided to put memory limit 16MB
so, don't use normal boolean dp flag, make it bitwise
this is not adding difficulty, just making it cumbersome!

let F(k, n) = boolean function, is it possible to divide [n, N] integers with k division
where for each division, Li <= Si <= Ui
where Si = sum of all elements in ith division

F(k, n) = \min pos=n..N ( F(k+1, pos+1) )
break the equation on first F that returns true.
record the pos.

base cases:
F(k = K, n > N) = false
F(k = K, n <= N) = [Lk <= S[n, N] <= Uk]
S[n, N] = an + a(n+1) + ... + aN
Sk = S[n, N]

print all pos.

*/

#include <stdio.h>
//#include <ctime>

#define MAXL (5005)
#define ll long long
#define OK (1)
#define ERR (-1)
#define UNK (0)

// caught MLE (this is ~24MB, max 16MB)
char dpf[MAXL][MAXL/8+1];
char dp[MAXL][MAXL/8+1];
int dpm[MAXL];
int A[MAXL]; // 0-based
ll S[MAXL]; // \sigma A[a, b] = S[b] - S[a-1]
int L[MAXL];
int U[MAXL];

bool F(int k, int K, int n, int N, int * m) {
	if (k <= K && n > N) {
		return false;
	}
	
	if (dpf[k][n>>3] & (1<<(n&7))) {
		return (dp[k][n>>3] & (1<<(n&7))) != 0;
	}
	
	dpf[k][n>>3] |= 1<<(n&7);
	
	if (k == K) { // last element
		ll s = S[N] - S[n-1];
		if (L[k] <= s && s <= U[k]) {
			m[k] = N;
			dp[k][n>>3] |= 1<<(n&7);
			return true;
		} else {
			return false;
		}
	}
	
	int u=n, v=N+1, c, st=n;
	// binary search wrong!
	// i dunno what happened but comment this, and I got AC.
	/*while (1) {
		if (u>=v) {
			st = u-1;
			break;
		} else {
			c = (u+v)>>1;
			if (S[c] - S[n-1] >= L[k]) {
				v = c;
			} else 
				//if (S[c] - S[n-1] < L[k]) 
				{
				u = c+1;
			}
		}
	}
	
	if (st < n) st = n;
	*/
	ll s0 = 0;
	for (int i=st; i<=N ;++i) {
		s0 += A[i-1];
		if (s0 < L[k]) continue;
		if (s0 > U[k]) break;
		
		bool res = F(k+1, K, i+1, N, m);
		if (res) {
			m[k] = i;
			
			dp[k][n>>3] |= 1<<(n&7);
			return true;
		}
		
	}
	
	return false;
	
}

int main() {
	//using namespace std;
	//clock_t begin = clock();
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	for (int i=0; i<N; ++i) {
		scanf("%d", &A[i]);
	}
	
	S[0] = 0;
	for (int i=1; i<=N; ++i) {
		S[i] = S[i-1] + A[i-1];
	}
	
	for (int i=1; i<=K; ++i) {
		scanf("%d %d", &L[i], &U[i]);
	}
	
	bool res = F(1, K, 1, N, dpm);
	if (!res) {
		printf("-1\n");
	} else {
		for (int i=1; i<K; ++i) {
			printf("%d", dpm[i]);
			if (i < K-1) {
				putchar(' ');
			}
		}
		putchar('\n');
	}
	
	//clock_t end = clock();
	//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	//
	//fprintf(stderr, "elapsed=%lf\n", elapsed_secs);
	
	return 0;
}

