/* AC
algo:
there are 2 cases in this problem
when score is ( 25, <= 23 ) and ( >25, >25 )
when the final scoreboard is (25, X<=23), it can only be accomplished
by going from score (0, 0) to (24, X) then finishes with (25, X) in any configuration
This is simply BinomCombin(24 + X, X).

second case when (24, 24) is met.
In this case, notice that in order to get to the end score, the sequence must be the following
term: A = A wins, B = B wins

(AB)(AB)(BA)(BA)(AA / BB)
Assuming the end game score is (X+2, X).
The sequence between (24, 24) to near end game (X, X) is always in this pattern:
If A wins the first round, next one MUST be B.
likewise, if B wins, A wins next because when the absolute diff of A and B score is 2, the game ends there.
and the final sequence before the end game score, either A wins twice or B wins twice. No other possibilities exist.

There are two possible sequences, (AB) or (BA). So, it is simply 2^(X-24)
The sequence between (0,0) to (24,24) is same as the first case (BinomCombin(48, 24))
So, the result = BinomCombin(48, 24) * 2^(X-24)

Impossible cases. Print 0 for these cases.
This can be manually enumerated. Just remember the conditions:
1. no one reaches 25 in end game
2. end in 24,25 or 25,24
3. either team reaches above 25 in end game and the other team' score absolute diff is not 2


*/ 


#include <cstdio>
#include <algorithm>

using std::min;
using std::max;

#define MOD (1000000007)
#define MAXC (50)
#define ll long long

int C[MAXC][MAXC];

ll bigmod(int base, int exp, int mod) {
	if (exp == 0 || base == 1) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	half = (half*half)%mod;
	if (exp&1) {
		half = (half*base)%mod;
	}
	return half;
}

void buildC() {
	for (int i=0; i<MAXC; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j=1; j<i; ++j) {
			C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
		}
	}
}

int main() {
	buildC();
	
	int T, A, B;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &A, &B);
		
		int minv = min(A, B);
		int maxv = max(A, B);
		
		//printf("A=%d B=%d minv=%d maxv=%d\n", A, B, minv, maxv);
		
		if (maxv > 25) {
			
			if (maxv - minv != 2) {
				printf("0\n");
				
			} else {
				// for pos <24,24>
				int p24 = C[48][24];
				
				// now, pos is <24,24>
				int a24 = bigmod(2, minv-24, MOD);
				
				//printf("p24=%d, a24=%d\n", p24, a24);
				
				printf("%d\n", (int)(((ll)p24 * a24)%MOD));
				
			}
		} else {
			if (A != 25 && B != 25) {
				printf("0\n");
				
			} else {
				if (maxv - minv < 2) {
					printf("0\n");
					
				} else {
					printf("%d\n", C[maxv + minv - 1][minv]);
					
				}
				
			}
			
			
		}
		
	}
}
