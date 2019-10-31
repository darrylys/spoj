#include <stdio.h>
#include <math.h>

#define ll long long

int D[1001];
ll big = 100000000000000000LL;
int hfbig = 1000000000;

ll minv(ll a, ll b) {
	return (a<b)?a:b;
}

ll floorsqrt(ll X) {
	// X max ~ 10^16
	
	ll u=1, v=minv(hfbig, X), c;
	while (1) {
		if (u >= v) {
			return u-1;
		} else {
			c=(u+v)/2;
			if (X > c*c) {
				u = c+1;
			} else if (X < c*c) {
				v = c;
			} else {
				return c;
			}
		}
	}
	
}

int get(int d, ll T) {
	
	// seems problem!
	
	//double half = sqrt((ll)(2*d-1)*(2*d-1) + T*8);
	//int halff = (int)floor(half);
	ll r = (ll)(2*d-1)*(2*d-1) + T*8;
	//printf("r=%lld ", r);
	
	ll halff = floorsqrt(r);
	
	int sk = (1-2*d + halff)/2;
	//printf("sqrt(%lld)=%lld, sk=%d\n", r, halff, sk);
	return sk;
}

ll find(int nD, int K) {
	ll u=1, v=big, c;
	
	while(1) {
		if (u >= v) {
			return u-1;
		} else {
			c = (u+v)/2;
			
			//printf("[%lld,%lld] c=%lld\n", u, v, c);
			
			ll Tk = 0;
			for (int i=0; i<nD; ++i) {
				int temp = get(D[i], c);
				Tk += temp;
				
				if (K <= Tk) {
					v = c;
					break;
				}
			}
			
			if (K > Tk) {
				u = c+1; 
			}
			
		}
		
	}
	
}

int main() {
	int T, N, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);
		for (int i=0; i<N; ++i) {
			scanf("%d", &D[i]);
		}
		
		printf("%lld\n", find(N, K)+1);
		
	}
}
