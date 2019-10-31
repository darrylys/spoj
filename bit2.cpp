#include <stdio.h>

#define ll long long

int findb(ll N) {
	int b=1;
	for (; (ll)b*(1LL<<(b-1)) <= N ; ++b);
	
	return b;
}

ll findK(ll N) {
	int b = findb(N)-1;
	
	int noOf1InPrefix = 0;
	ll prefix = 0;
	
	ll bitNo = 1LL << b;
	ll prevsum = 0;
	
	//printf("bitNo=%lld, b=%d\n", bitNo, b);
	
	for (int cb=b; cb>0; --cb) {
		ll zeroPart = (ll)noOf1InPrefix*bitNo + prevsum + (ll)cb*(1LL<<(cb-1));
		if (N > zeroPart) {
			// nextbit=1
			prevsum = zeroPart;
			noOf1InPrefix++;
			prefix = (prefix<<1) + 1;
		} else {
			// nextbit=0
			prefix = (prefix<<1);
		}
		bitNo >>= 1;
		
		//printf("prevsum=%lld\n", prevsum);
	}
	
	// last leaf
	ll lo = noOf1InPrefix*bitNo + prevsum + 0;
	ll hi = lo + 1 + noOf1InPrefix;
	
	//printf("lo=%lld, hi=%lld\n", lo, hi);
	
	if (N == lo) {
		return (prefix<<1);
	} else if (N == hi) {
		return ((prefix<<1) + 1);
	} else {
		return -1;
	}
	
}


int main() {
	
	int T;
	ll N, r;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &N);
		r = findK(N);
		if (r == -1) {
			printf("Does Not Exist.\n");
		} else {
			printf("%lld\n", r);
		}
	}
	
	return 0;
}
