#include<stdio.h>
#include<string.h>

#define ll long long

ll dp[2][50005];
int an[50];

int find1(ll x) {
	int ones = 0;
	while(x) {
		x -= x&(-x);
		ones++;
	}
	
	return ones;
}

void find(int N, int res[2]) {
	
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
	
	int maxv = 0;
	int maxi = 0;
	for (int i=1, o; i<=sum; ++i) {
		
		o = find1(dp[curri][i]);
		if (o > maxv) {
			maxv = o;
			maxi = i;
		}
		
	}
	
	res[0] = maxv;
	res[1] = maxi;
}

int main() {
	int T, N, res[2];
	scanf("%d",&T);
	while(T--){
		scanf("%d", &N);
		for (int i=0; i<N; ++i) {
			scanf("%d", &an[i]);
		}
		find(N, res);
		printf("%d %d\n", res[0], res[1]);
	}
	return 0;
}
