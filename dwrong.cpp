#include <stdio.h>
#include <algorithm>

#define MXA 5000
#define ll long long

int num[MXA];
int den[MXA];
int idx[MXA];

bool comp(int a, int b) {
	//printf("a=%d b=%d\n", a, b);
	
	int ra = a;
	int rb = b;
	
	ll lh = (ll)num[ra] * den[rb];
	ll rh = (ll)num[rb] * den[ra];
	
	if (lh == rh) {
		return num[ra] < num[rb];
	} else {
		return lh < rh;
	}
}


int main() {
	int a, b, m, n; // (num / denom)
	
	while (1) {
		scanf("%d %d", &b, &n);
		if (b == 0 && n == 0) break;
		
		ll bn = 2LL * b * n;
		ll n2 = (ll)n * n;
		int x = 0;
		
		for (m = 1; m <= 2*n; ++m) {
			if (m != n) {
				ll top = (bn*m - (ll)b*m*m);
				
				if (top % n2 == 0) {
					a = (int) (top / n2);
					num[x] = a;
					den[x] = m;
					idx[x] = x;
					x++;
				}
				
			}
		}
		
		//printf("finish=%d\n", x);
		
		std::sort(idx, idx+x, comp);
		
		printf("%d/%d", num[idx[0]], den[idx[0]]);
		for (int i=1; i<x; ++i) {
			printf(" %d/%d", num[idx[i]], den[idx[i]]);
		}
		putchar('\n');
	}
	return 0;
}
