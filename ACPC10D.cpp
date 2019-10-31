#include<cstdio>
#define INFINITY 1000000000
int graph[100010][3];
int dp[100010][3];

int min(int a, int b) {
	return (a<b)?a:b;
}

int main() {
	int n, cntr=1;
	while (scanf("%d",&n) && n) {
		for (int i=0; i<n; i++) {
			scanf("%d%d%d",&graph[i][0],&graph[i][1],&graph[i][2]);
		}
		dp[0][0] = INFINITY;
		dp[0][1] = graph[0][1];
		dp[0][2] = graph[0][2];
		if (dp[0][1] + graph[0][2] < dp[0][1]) {
			dp[0][2] = dp[0][1] + graph[0][2];
		} else {
            dp[0][2] = INFINITY;
		}
        //printf("%d %d %d\n", dp[0][0], dp[0][1], dp[0][2]);
		for (int i=1; i<n; i++) {
			dp[i][0] = min(dp[i-1][0], dp[i-1][1]) + graph[i][0];
			dp[i][1] = min(dp[i][0], min(dp[i-1][0], min(dp[i-1][1], dp[i-1][2]))) + graph[i][1];
			dp[i][2] = min(dp[i][1], min(dp[i-1][1], dp[i-1][2])) + graph[i][2];
			//printf("%d %d %d\n", dp[i][0], dp[i][1], dp[i][2]);
		}

		printf("%d. %d\n", cntr++, dp[n-1][1]);
	}
}
