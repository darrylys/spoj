#include <stdio.h>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;

vector<int> vc[202];
vector<int> rem;
ll minsum[2][202]; // [n&1][k] for space opt
const ll BIG = 1LL<<62;

int gcd(int a, int b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

int lcm(int a, int b) {
	return a / gcd(a,b) * b;
}

ll min(ll a, ll b) {
	return a<b ? a:b;
}

int main() {
	int N, K;
	ll sumz = 0;
	scanf("%d %d", &N, &K);
	
	for (int i=0, ai; i<N; ++i) {
		scanf("%d", &ai);
		sumz += ai;
		vc[ai%K].push_back(ai);
	}
	
	for (int i=0; i<2; ++i) {
		for (int j=0; j<202; ++j) {
			minsum[i][j] = BIG;
		}
	}
	
	for (int i=1; i<K; ++i) {
		sort(vc[i].begin(), vc[i].end());
		
		int vsz = vc[i].size();
		int blocksize = lcm(K, i) / i;
		
		for (int j=0; j < vsz && j < blocksize; ++j) {
			rem.push_back(vc[i][j]);
		}
	}
	
	//printf("INITIAL [");
//	for (int i=1; i<K; ++i) {
//		printf("%lld ", minsum[0][i]);
//	}
//	printf("]\n");
	
	int remsz = rem.size(), lastcn;
	
	if (remsz) {
		minsum[0][rem[0]%K] = rem[0];
		
		for (int i=1, cn, pn; i<remsz; ++i) {
			cn = i&1;  //curr n
			pn = cn^1; //prev n (n-1)
			
	//		printf("rem[%d]=%d [", i, rem[i]);
			
			int initk = rem[i]%K;
			minsum[cn][initk] = min(minsum[cn][initk], rem[i]);
			
			for (int j=1, tg; j<K; ++j) {
				
				tg = (j+rem[i])%K;
				if (tg) {
					minsum[cn][tg] = min(minsum[cn][tg], minsum[pn][j] + rem[i]); // taking rem[i]
				}
				minsum[cn][j] = min(minsum[cn][j], minsum[pn][j]); // not taking rem[i]
				
				
			}
			
	//		for (int j=1; j<K; ++j) {
	//			printf("%lld ", minsum[cn][j]);
	//		}
			
	//		printf("]\n");
			
			lastcn = cn;
		}
	}
	
	int sumzmod = sumz % K;
	minsum[lastcn][0] = 0;
	
	ll maxsum[202];
	
	for (int i=0; i<K; ++i) {
		if (minsum[lastcn][(sumzmod-i+K)%K] >= sumz) {
			printf("-1 ");
		} else {
			printf("%lld ", sumz - minsum[lastcn][(sumzmod-i+K)%K]);
		}
	}
	putchar('\n');
	return 0;
}

