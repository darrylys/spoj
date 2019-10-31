#include <stdio.h>
#include <math.h>

#define ll long long
#define BIG (2000000000)

ll M(ll n, ll x) {
	ll res = ((n * (n-1))/2) - 2*(n-x)*x;
	if (res < 0) return -res;
	return res;
}

int main() {
	int T, N, c=1;
	scanf("%d", &T);
	
	int buf[10];
	
	while (T--) {
		scanf("%d", &N);
		
		int p = 0;
		double sqrtn = sqrt(N);
		
		buf[p++] = N>>1;
		buf[p++] = (int)floor((N + sqrtn)/2.0);
		buf[p++] = (int)ceil((N + sqrtn)/2.0);
		
		ll minv = BIG;
		for (int i=0; i<p; ++i) {
			ll can = M(N, buf[i]);
			if (minv > can) {
				minv = can;
			}
		}
		
		printf("Case %d: %lld\n", c++, minv);
		
	}
	return 0;
}
