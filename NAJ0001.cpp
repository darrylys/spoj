#include <stdio.h>
#include <vector>
#include <string.h>

#define MAXN 1000005
#define MAXV 1001
#define ll long long

using std::vector;

vector<int> pv[MAXV];
vector<ll> csum[MAXV];
int pf[MAXN];
int pfac[20][2];
int arr[MAXN];

void sieve() {
	
	for (int i=3; i*i < MAXN; i+=2) {
		if (!pf[i]) {
			pf[i] = i;
			for (int j=i*i; j < MAXN; j += 2*i) {
				pf[j] = i;
			}
		}
	}
	
}

int enumerate(int tx, int li, int xli, int idx) {
	if (tx > 1000) return 0;
	
	if (li == xli) {
		pv[tx].push_back(idx);
		return 1;
	}
	
	int ml = 1, e;
	for (int i=0; i<=pfac[li][1]; ++i) {
		e = enumerate(tx * ml, li+1, xli, idx);
		if (!e) break;
		ml *= pfac[li][0];
	}
	
	return tx <= 1000;
}

void split(int idx, int x) {
	
	int pn = x;
	
	int exp = 0;
	int lp = 0;
	int li = 0;
	
	while ((pn&1) == 0) {
		pn >>= 1;
		exp++;
	}
	
	if (exp) {
		pfac[0][0] = 2;
		pfac[0][1] = exp;
		li = 1;
	}
	
	while (pn > 1) {
		
		lp = pf[pn];
		
		if (lp == 0) {
			// prime number remains.
			if (pn <= 1000) {
				pfac[li][0] = pn;
				pfac[li][1] = 1;
				li++;
			}
			
			break;
		}
		
		exp = 0;
		while (pn % lp == 0) {
			pn /= lp;
			exp++;
		}
		
		pfac[li][0] = lp;
		pfac[li][1] = exp;
		li++;
		
	}
	/*
	printf("%d=", x);
	for (int i=0; i<li; ++i) {
		printf("%d^%d ", pfac[i][0], pfac[i][1]);
	}
	putchar('\n');
	*/
	enumerate(1, 0, li, idx);
	/*
	for (int i=0; i<=1000; ++i) {
		if (pv[i].size()) {
			printf("div=%d || ", i);
			
			int sz = pv[i].size();
			
			for (int j=0; j<sz; ++j) {
				printf("%d ", pv[i][j]);
			}
			putchar('\n');
		}
	}
	*/
}

void clear() {
	for (int i=0; i<MAXV; ++i) {
		pv[i].clear();
		csum[i].clear();
	}
}

void buildcsum() {
	for (int i=0; i<MAXV; ++i) {
		
		int arx = pv[i].size();
		ll tsum = 0;
		csum[i].push_back(0);
		for (int j=0; j<arx; ++j) {
			tsum += arr[pv[i][j]];
			csum[i].push_back(tsum);
		}
	}
	/*
	printf("\nbuildsum\n");
	for (int i=0; i<MAXV; ++i) {
		int arx = csum[i].size();
		
		printf("i=%d, n=%d ||", i, arx);
		for (int j=0; j<arx; ++j) {
			printf(" %lld", csum[i][j]);
		}
		putchar('\n');
	}
	*/
}

ll binary_search(int V, int x) {
	int u=0, v=pv[V].size(), c;
	
	while (1) {
		if (u >= v) {
			// u-1
			return csum[V][u];
		} else {
			c = (u+v)>>1;
			
			if (x < pv[V][c]) {
				v = c;
			} else if (x > pv[V][c]) {
				u = c+1;
			} else {
				return csum[V][c+1];
			}
			
		}
	}
}

int main() {
	sieve();
	
	int T, N, M, V, x, y, c=1;
	ll sumx, sumy;
	scanf("%d", &T);
	while (T--) {
		clear();
		
		scanf("%d %d", &N, &M);
		for (int i=0; i<N; ++i) {
			scanf("%d", &arr[i]);
			split(i, arr[i]);
		}
		
		buildcsum();
		
		printf("Case #%d\n", c++);
		while (M--) {
			scanf("%d %d %d", &V, &x, &y);
			sumx = binary_search(V, x-2);
			sumy = binary_search(V, y-1);
			
			printf("%lld\n", sumy - sumx);
		}
		putchar('\n');
		
	}
	//split(0, 999983);
	
}


