/**
AC 0.03s 2.8M SPOJ C++ 4.3.2

algo: DP

Several observations:
1.	The (start, end) string pair can always be reduced to (000* (all zeros), end")
2.	the end" string can be constructed by comparing the start and end string character by character
	end"[i] == 1 iff start[i] != end[i] and end"[i] == 0 otherwise.
3.	by doing brute-force on the problem, it can be seen that the number of ways is determined by
	the number of 1s in the string and NOT by the position. As long as the string contains the same
	number of 1s, the number of ways is the same.
	The state is thus: (K, S) where S is the number of 1s.
4.	The next problem is to find the source of (K,S) from (K-1,S*)

Now, given M, the number of bits allowed to flip and (K,S) the DP state
find the DP equation.

let f(K,S) is the number of ways to transform an all-zeros string to a binary string with S number of 1s in K steps using the stated operation.

now, 
S = 0000***001111***11111
M =      11**1111
X =          1111

let X is the overlapping region between S and M. That is, the number of 1s in S that is allowed to be flipped
X is in [0, min(M, S)].

L = length of string (strlen(start))
S =  0000***00 (1111***11111)
M =       11** (1111
W = (0*   11*1)(0000***11111)
    1          2

now, if we do S XOR M, we get W.
that is to say, we can create S from W as one of the source strings; i.e. W can be transformed using stated operation to S
We need to find how many possible W are there. Since the number of 1s all possible W is the same, the number of ways to create W is also the same.
the number of 1s in W:
	= S - X + M - X 
	= S + M - 2X

look at W(1) == (0*   11*1)
W can be all possible strings that has (M-X) number of 1s in a (L-S) length string.

look at W(2) == (0000***11111)
W can be all possible strings that has (X) number of 0s in an S-length string.

The total number of possible W is C(S, X) * C(L - S, M - X) for C is binomial combination function.

so, the DP is
f(K, S) = \sigma x in [0, min(M, S)] ( f(K-1, S + M - 2x) * C(S, x) * C(L - S, M - x) )
remember the boundary conditions. if S + M - 2x > L, then f(K, S + M - 2x) = 0.

Space: O(K*L)
Time: O(T*K*L*M)
*/

#include <stdio.h>
#include <string.h>

#define MOD 1000000009
#define ll long long
#define MAXL 105
//#define DEBUG

int C[MAXL][MAXL];
char start[MAXL];
char end[MAXL];
int dp[MAXL][MAXL];

void buildC() {
	for (int i=0; i<MAXL; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j=1; j<i; ++j) {
			C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
		}
	}
}

int main() {
	buildC();
	
	int T, M, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%s%s%d%d", start, end, &M, &K);
		
		int len = strlen(start);
		
		// observation 1 and 2
		int en1 = 0;
		for (int i=0; i<len; ++i) {
			en1 += start[i]^end[i];
		}
		
		memset(dp, 0, sizeof(dp));
		
		dp[0][0] = 1;
		for (int k=1; k<=K; ++k) {
			for (int s=0, min; s<=len; ++s) {
				min = (s < M) ? s : M;
				for (int x=min, ts; x >= 0 ; --x) {
					ts = s + M - 2*x;
					if (ts <= len) {
						dp[k][s] = ((ll)dp[k][s] + (ll)dp[k-1][ts] * (( (ll)C[s][x] * (ll)C[len-s][M-x])%MOD))%MOD;
					} else {
						break;
					}
				}
			}
		}
		
		#ifdef DEBUG
		printf("\n======================================\n");
		printf("\t");
		for (int s=0; s<=len; ++s) {
			printf("%d\t", s);
		}
		printf("\n");
		
		for (int k=0; k<=K; ++k) {
			printf("%d", k);
			for (int s=0; s<=len; ++s) {
				printf("\t%d", dp[k][s]);
			}
			printf("\n");
		}
		#endif
		
		printf("%d\n", dp[K][en1]);
		
	}
	return 0;
}
