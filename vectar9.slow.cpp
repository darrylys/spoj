// AC but terrible performance
// most basic algo uses inclusion-exclusion + binary search but performance is 5.81s, slowest in SPOJ

#include <stdio.h>

#define ll long long
#define LIM (304250263527211LL)
#define e2 (1<<13)

const int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
const int nprime = 13;

ll _get(ll X, ll tv, int n, int sgn) {
	
	if (n == nprime) {
		return sgn * (X / tv);
	}
	
	ll tn = _get(X, tv, n+1, sgn);
	ll ti = _get(X, tv*prime[n], n+1, -sgn); 
	
	return tn + ti;
}

ll _get2(ll X) {
	
	ll sum = 0, s;
	int p, o;
	
	for (int i=1; i<e2; ++i) {
		
		int x = i;
		
		p=0;
		o=0;
		s=1;
		while (x) {
			if (x&1) {
				s *= prime[p];
				o++;
			}
			p++;
			x >>= 1;
		}
		
		if (o&1) {
			sum += X/s;
		} else {
			sum -= X/s;
		}
	}
	
	return sum;
}

ll get(ll X) {
	//return X - _get(X, 1, 0, 1);
	return _get2(X);
}

ll find(ll K) {
	
	ll u=2, v=LIM, c;
	
	while (1) {
		if (u >= v) {
			return u;
		} else {
			c = (u+v)/2;
			
			ll val = get(c);
			if (val >= K) {
				v = c;
			} else if (val < K) {
				u = c+1;
			}
		}
	}
	
}

int main() {
	
	int T; ll K;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &K);
		printf("%lld\n", find(K));
	}
	
}
