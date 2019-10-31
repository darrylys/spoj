#include <stdio.h>
#include <string.h>

#define ll long long

const ll INV2 = 500000004;
const int MOD = 1000000007;

int main() {
	int N, ai;
	int bufsum[35];
	
	memset(bufsum, 0, sizeof(bufsum));
	scanf("%d", &N);
	
	for (int i=0; i<N; ++i) {
		scanf("%d", &ai);
		for (int i=0; ai>0; ++i, ai/=2) {
			bufsum[i] += ai&1;
		}
	}
	
	ll e2 = 1;
	ll P = 0;
	ll P1, P2;
	for (int i=0; i<32; ++i) {
		P1 = (INV2 * bufsum[i]) % MOD;
		P2 = (e2 * (bufsum[i]-1)) % MOD;
		
		P +=  (P1 * P2)%MOD;
		e2 <<= 1;
	}
	
	printf("%lld\n", P%MOD);
	
}
