#include <stdio.h>

#define MAXN (2001)
#define ll long long
#define MOD (1000000007)

int x2e[MAXN];

int build2exp() {
	x2e[0] = 1;
	for (int i=1; i<MAXN; ++i) {
		x2e[i] = (x2e[i-1]<<1)%MOD;
	}
}

int find(int N) {
	int sum = 0;
	
	for (int i=1; i<=N; ++i) {
		ll lef = (x2e[N/i-1]-1+MOD)%MOD;
		ll rig = x2e[N-i-(N/i)+1];
		sum = (sum + lef * rig)%MOD;
	}
	
	return sum;
}

int main() {
	build2exp();
	
	int T, xn, c=1;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &xn);
		printf("Case %d: %d\n", c++, find(xn<<1));
	}
	return 0;
}
