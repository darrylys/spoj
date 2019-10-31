/*
Implementation using lucas theorem similar to spoj/dukkar.
After obtaining formula from dukkar, just improve it to accomodate dukkar2. Easy.
O(k) per testcase
*/

#include <stdio.h>

#define MOD (1000000007)
#define ll long long
#define INV2 (500000004)
#define MAXK (1024)

int digit[MAXK];
int pexp[MAXK];

int main() {
	int T, k, P, nx, N, pe, fxs, sum;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &P, &k);
		N = 0;
		pe = 1;
		sum = 0;
		
		int lastd, carry = 1;
		int Pbase = ((ll)P * (P+1) / 2)%MOD;
		
		pexp[0] = 1;
		for (int i=1; i<k; ++i) {
			pexp[i] = ((ll)pexp[i-1] * Pbase)%MOD;
		}
		
		for (int i=0; i<k; ++i) {
			scanf("%d", &nx);
			N += ((ll)nx*pe)%MOD;
			N %= MOD;
			pe = ((ll)pe*P)%MOD;
			digit[i] = nx;
		}
		
		int accum = 1;
		for (int i=k-1; i>=0; --i) {
			ll digsq = ((((ll)digit[i])*(digit[i]+1)/2)%MOD);
			ll mid = (digsq * pexp[i])%MOD;
			fxs = (mid * accum)%MOD;
			
			//fxs = ((ll)accum * ((((((ll)digit[i])*(digit[i]+1)/2)%MOD) * pexp[i])%MOD))%MOD;
			sum += fxs;
			sum %= MOD;
			accum = ((ll)accum * (digit[i]+1))%MOD;
		}
		printf("%lld\n", (((ll)N * (N+1) / 2) - sum + MOD)%MOD);
	}
}
