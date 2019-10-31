// AC
// algo:
// implements the following recursive formula:
// f(H) = f(H-1) * (\sigma i=0...(H-1) f(i)) ; f(0) = 1
// precompute the whole thing and answer per query in O(1)

#include <stdio.h>

#define MOD (1000000007)
#define ll long long
#define MAXN (10000001)

int S[MAXN];

int main() {
	S[0] = 1;
	int ssum = S[0];
	
	for (int i=1; i<MAXN; ++i) {
		S[i] = ((ll)S[i-1] * ssum)%MOD;
		ssum = (ssum + S[i])%MOD;
	}
	
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		printf("%d\n", S[N]);
	}
	
}
