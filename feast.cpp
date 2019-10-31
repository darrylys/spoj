#include <stdio.h>
#include <string.h>

#define ll long long

ll LF[55][5005];
int CV[5005]; // coin value
int CN[5005]; // no of coin

// C = multiplier. coins needed
ll flf(int S, int C, int coinIdx, int nfCoin) {
	if (S == 0) return 1;
	if (S < 0 || (S > 0 && coinIdx == nfCoin)) return 0;
	if (C > CN[coinIdx] || S < CV[coinIdx]) return flf(S, C, coinIdx+1, nfCoin);
	
	if (LF[coinIdx][S] != -1) return LF[coinIdx][S];
	
	return LF[coinIdx][S] = flf(S - CV[coinIdx], C, coinIdx+1, nfCoin) + flf(S, C, coinIdx+1, nfCoin);
}

ll sum(int S, int N) {
	int mxcv = -1;
	for (int i=0; i<N; ++i) {
		if (mxcv < CN[i]) mxcv = CN[i];
	}
	
	ll cm = 0;
	for (int i=1; i<=mxcv; ++i) {
		//memset(LF, -1, sizeof(LF[0][0]) * N * S);
		if (S % i == 0) {
			cm += flf(S/i, i, 0, N);
		}
	}
	return cm;
}

int main() {
	int T, S, N, c=1;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d", &S, &N);
		memset(LF, -1 , sizeof(LF[0][0]) * 5005 * 55);
		for (int i=0; i<N; ++i) scanf("%d %d", &CV[i], &CN[i]);
		printf("Case %d: %lld\n", c++, sum(S, N));
	}
	return 0;
}
