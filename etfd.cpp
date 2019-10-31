#include <stdio.h>
#include <vector>

using namespace std;

#define ll long long
#define MAXN 1000005

int fp[MAXN];
int phi[MAXN];
int d[MAXN];
vector<int> ka[21];

void build() {
	fp[1] = 1;
	for (int i=2; i<MAXN; ++i) {
		if (fp[i] == 0) {
			fp[i] = i;
			
			if ((ll)i*i < MAXN) {
				for (int j=i*i; j<MAXN; j+=i) {
					fp[j] = i;
				}
			}
		}
	}
	
	phi[1] = 1;
	for (int i=2; i<MAXN; ++i) {
		if (i == fp[i]) {
			// prime!
			phi[i] = i-1;
		} else {
			int fp2 = fp[i] * fp[i];
			if (i % fp2) {
				phi[i] = (fp[i]-1) * phi[i / fp[i]];
			} else {
				phi[i] = fp[i] * phi[i / fp[i]];
			}
		}
	}
	
	for (int i=2; i<MAXN; ++i) {
		d[i] = 1 + d[phi[i]];
	}
	
	for (int i=1; i<MAXN; ++i) {
		if (d[i] < 20) {
			ka[d[i]].push_back(i);
		}
	}
}

int find(int x, int k) {
	int u = 0, v = ka[k].size(), c;
	
	while (true) {
		if (u >= v) {
			return u-1;
		} else {
			c = (u+v)>>1;
			if (ka[k][c] < x) {
				u = c+1;
			} else if (ka[k][c] > x) {
				v = c;
			} else {
				return c-1;
			}
		}
	}
}

int main() {
	build();
	/*
	printf("PHI[\t");
	for (int i=0; i<100; ++i) {
		printf("%d\t", phi[i]);
	}
	
	printf("\nd[\t");
	for (int i=0; i<100; ++i) {
		printf("%d\t", d[i]);
	}
	*/
	/*
	printf("\nkarray\n");
	for (int i=0; i<10; ++i) {
		
		int sz = ka[i].size();
		printf("K[%d].size=%d\t", i, sz);
		for (int j=0; j<sz; ++j) {
			printf("%d\t", ka[i][j]);
		}
		printf("\n");
		
	}
	*/
	
	int T, m, n, k;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d", &m, &n, &k);
		//printf("m=%d n=%d k=%d\n", m, n, k);
		
		/*int sz = ka[k].size();
		printf("K[%d].size=%d\t", k, sz);
		for (int j=0; j<sz; ++j) {
			printf("%d\t", ka[k][j]);
		}
		printf("\n");
		*/
		
		int fm = find(m, k);
		//printf("find(%d, %d) = %d\n", m, k, fm);
		
		int fn = find(n+1, k);
		//printf("find(%d, %d) = %d\n", n+1, k, fn);
		
		printf("%d\n", fn-fm);
		
		//printf("\n");
	}
	
	return 0;
}

