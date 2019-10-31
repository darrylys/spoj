#include <stdio.h>
#include <string.h>
#include <algorithm>

#define MAXF 1000001
#define MXN 10005
#define MOD 1000000007
#define ll long long

int freq[MAXF];
int arr[MXN];
char flag[MAXF];
int backlog[MXN];

ll bigmod(int base, int exp, int mod) {
	if (exp == 0) return 1;
	else if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	if (exp&1) {
		return (((half*half)%mod) * base)%mod;
	} else {
		return (half*half)%mod;
	}
}

int main() {
	int N;
	scanf("%d", &N);
	
	int uniqN = 0, v;
	for (int i=0; i<N; ++i) {
		scanf("%d", &v);
		if (freq[v] == 0) {
			arr[uniqN++] = v;
		}
		freq[v]++;
	}
	
	std::sort(arr, arr+uniqN);
	
	ll sum = 0;
	
	// r=1
	for (int i=0; i<uniqN; ++i) {
		// += 2^n - n - 1
		sum += (bigmod(2, freq[arr[i]], MOD) - freq[arr[i]] - 1 + MOD) % MOD;
	}
	
	sum %= MOD;
	
	// r>=2
	for (int r=2; r < MAXF; ++r) {
		//printf("r=%d\n", r);
		
		if (arr[uniqN-1]/r < arr[0]) break;
		int p = 0;
		
		for (int i=0; i<uniqN && arr[uniqN-1]/r >= arr[i]; ++i) {
			
			if (!flag[arr[i]]) {
				flag[arr[i]] = 1;
				backlog[p++] = arr[i];
				
				// root elem
				
				int seqlen = 1;
				ll dp = freq[arr[i]];
				
				//printf("[%d", arr[i]);
				
				for (ll arrj=(ll)arr[i]*r; arrj < MAXF && freq[(int)arrj] > 0; arrj *= r) {
					flag[arrj] = 1;
					seqlen++;
					dp = dp * freq[arrj];
					
					if (seqlen > 2) {
						dp += freq[arrj / r] * freq[arrj];
					}
					
					dp %= MOD;
					sum += dp;
					sum %= MOD;
					backlog[p++] = (int)arrj;
					//printf(" , %lld", arrj);
				}
				
				//putchar('\n');
				
			}
			
		}
		
		for (int i=0; i<p; ++i) {
			flag[backlog[i]] = 0;
		}
		
	}
	
	printf("%d\n", sum%MOD);
	return 0;
}
