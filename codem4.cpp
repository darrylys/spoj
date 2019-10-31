#include <stdio.h>
#include <string.h>

int dp[32][32];
int arr[32];

int max(int a, int b) {
	return (a > b) ? a : b;
}

int min(int a, int b) {
	return (a < b) ? a : b;
}

int clever(int a, int b) {
	if (dp[a][b] != -1) {
		return dp[a][b];
	}
	
	if (b - a == 1) {
		return dp[a][b] = max(arr[a], arr[b]);
	}
	
	if ((b - a + 1) % 2 == 0) {
		// P1 turn
		return dp[a][b] = max(arr[a] + clever(a+1, b), arr[b] + clever(a, b-1));
	} else {
		// P2 turn
		return dp[a][b] = min(clever(a+1, b), clever(a, b-1));
	}
}

int stupid(int a, int b) {
	if (dp[a][b] != -1) {
		return dp[a][b];
	}
	
	if (b - a == 1) {
		return dp[a][b] = max(arr[a], arr[b]);
	}
	
	if ((b - a + 1) % 2 == 0) {
		// P1 turn
		return dp[a][b] = max(arr[a] + stupid(a+1, b), arr[b] + stupid(a, b-1));
	} else {
		// P2 turn
		return dp[a][b] = max(stupid(a+1, b), stupid(a, b-1));
	}
}

void set2m1(int n) {
	for (int i=0; i<n; ++i) {
		for (int j=0; j<n; ++j) {
			dp[i][j] = -1;
		}
	}
}

int main() {
	int T, n;
	scanf("%d",&T);
	while (T--) {
		scanf("%d", &n);
		for (int i=0; i<n; ++i) {
			scanf("%d", &arr[i]);
		}
		set2m1(n);
		int stsc = stupid(0, n-1);
		
		set2m1(n);
		int clsc = clever(0, n-1);
		
		printf("%d %d\n", stsc, clsc);
	}
	return 0;
}
