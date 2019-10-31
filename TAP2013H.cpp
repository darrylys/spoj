#include <stdio.h>
#include <vector>

using namespace std;

#define MAXN 1000005

int sump[MAXN];
int ord[MAXN];
vector<int> kidx[MAXN];

void build() {
	
	for (int i=2; i<MAXN; i++) {
		
		if (sump[i] == 0) {
			ord[i] = 1;
			for (int j=i; j<MAXN; j+=i) {
				sump[j] += i;
			}
		} else {
			ord[i] = 1 + ord[sump[i]];
		}
		
		kidx[ord[i]].push_back(i);
	}
}

int find(int E, int K) {
	int u=0, v=kidx[K].size(), c;
	
	if (v == 0) return 0;
	
	while (1) {
		if (u >= v) {
			//found at u-1
			return u;
		} else {
			c = (u+v)/2;
			if (E > kidx[K][c]) {
				u=c+1;
			} else if (E < kidx[K][c]) {
				v=c;
			} else {
				return c+1;
			}
		}
	}
}

int main() {
	build();
	
	int T, A, B, K;
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d", &A, &B, &K);
		printf("%d\n", find(B, K) - find(A-1, K));
	}
	return 0;
	
}
