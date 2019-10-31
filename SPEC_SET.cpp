#include <stdio.h>

#define ll long long

int lvk[35];

// ok!
int getlevel(ll n, int k) {
	
	ll tchn = 1;
	int level = -1;
	
	while (1) {
		if (tchn > n) {
			break;
		}
		level++;
		tchn *= k;
	}
	
	return level;
}

int find(int n, int k) {
	//printf("find(%d,%d)\n", n, k);
	
	int level = getlevel(n, k);
	lvk[0] = 1;
	for (int i=1; i<=level; ++i) {
		lvk[i] = lvk[i-1]*k;
	}
	
	int root = 0;
	int clvl = 0;
	int remn = n - lvk[level];
	int pc = -1;
	int basen = -1;
	int pv = 0;
	
	//printf("INITIAL: pc=%d, basen=%d, root=%d, pv=%d, remn=%d, clvl=%d\n", pc, basen, root, pv, remn, clvl);
	
	while (clvl <= level) {
		
		pc = remn / lvk[level-clvl];
		if (root) {
			// rem
			basen = root * k;
			root = basen + pc;
			pv = root - pv;
			
		} else {
			// special case on 1,2,3
			pv = pc+1;
			root = pc+1;
		}
		
		remn -= pc * lvk[level-clvl];
		//printf("pc=%d, basen=%d, root=%d, pv=%d, remn=%d, clvl=%d\n", pc, basen, root, pv, remn, clvl);
		
		clvl++;
		
		
		
	}
	
	return pv;
}

int main() {
	int T, N, K;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d", &N, &K);
		if (K == 1) printf("0\n");
		else printf("%d\n", find(N,K));
	}
	
}
