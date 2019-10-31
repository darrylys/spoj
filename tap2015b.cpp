#include <stdio.h>

#define ll long long

int chk(int N, int K, ll C) {
	
	ll sum = 0;
	int k = 0;
	for (int n=1; n<=N; ++n) {
		sum += (2*n-1);
		if (sum >= C) {
			++k;
			sum = 0;
		}
	}
	
	if (k >= K) {
		return 1;
	} else {
		return -1;
	}
}

ll find(int N, int K) {
	// max C = N*N
	ll u=1, v=(ll)N*N+1, c;
	
	while (u<v) {
		c = (u+v)/2;
		
		int r = chk(N, K, c);
		if (r == 1) {
			u = c+1;
		} else {
			v = c;
		}
	}
	
	return u-1;
}

int main() {
	int N, K;
	
	while (scanf("%d %d", &N, &K) != EOF) {
		printf("%lld\n", find(N, K));
	}
	return 0;
}

