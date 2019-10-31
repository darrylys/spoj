#include<stdio.h>
#include<string.h>

#define ll long long
#define MAXN (60005)

ll dp[2][MAXN];
int an[60];

int find1(ll x) {
	int ones = 0;
	while(x) {
		x -= x&(-x);
		ones++;
	}
	
	return ones;
}

int find(int N) {
	
	int sum = 0;
	for (int i=0; i<N; ++i) {
		sum += an[i];
	}
	
	memset(dp[0], 0, (sum+1)*sizeof(dp[0][0]));
	memset(dp[1], 0, (sum+1)*sizeof(dp[1][0]));
	
	int previ, curri;
	for (int i=0; i<N; ++i) {
		
		curri = i&1;
		previ = curri^1;
		
		// stage 1, do addition to existing values.
		for (int j=1; j<=sum; ++j) {
			
			if (dp[previ][j]) {
				dp[curri][j + an[i]] = dp[previ][j] << 1;
			}
		}
		
		// stage 2, combine with prev values.
		for (int j=1; j<=sum; ++j) {
			dp[curri][j] |= dp[previ][j];
		}
		
		// stage 3, add sole an[i];
		dp[curri][an[i]] |= 1;
		
		memset(dp[previ], 0, (sum+1)*sizeof(dp[previ][0]));
	}
	
	return curri;
}

int main() {
	int T, N, Q, q, sum = 0;
	
	while(1){
		scanf("%d %d", &N, &Q);
		if (N == 0 && Q == 0) break;
		
		sum = 0;
		for (int i=0; i<N; ++i) {
			scanf("%d", &an[i]);
			sum += an[i];
		}
		
		int ci = find(N);
		
		while (Q--) {
			scanf("%d", &q);
			
			if (q > sum || q <= 0 || dp[ci][q] == 0) {
				printf("That's impossible!\n");
				continue;
			}
			
			ll tval = dp[ci][q];
			//printf("tval=%lld\n", tval);
			int x = 1, xi = 0;
			int res[70];
			
			while (tval) {
				if (tval & 1) {
					res[xi++] = x;
				}
				x++;
				tval >>= 1;
			}
			
			printf("%d", res[0]);
			for (int i=1; i<xi; ++i) {
				printf(" %d", res[i]);
			}
			
			putchar('\n');
		}
	}
	return 0;
}
