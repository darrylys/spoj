#include <stdio.h>

#define MAXN (100005)

int dp[MAXN];
char input[MAXN];

int max(int a, int b) {
	return (a>b)?a:b;
}

int find(char* str, int N) {
	dp[0] = 0;
	dp[1] = 1;
	
	int temp[4];
	for (int i=2; i<=N; ++i) {
		// dp[i-1]
		dp[i] = 1 + dp[i-1];
		
		// dp[i-2]
		dp[i] = max(dp[i], dp[i-2] + 2 - (str[i-1]-'A' + str[i-2]-'A')); //AA
		dp[i] = max(dp[i], dp[i-2] + 4 - ('B'-str[i-1] + str[i-2]-'A')); //AB
		dp[i] = max(dp[i], dp[i-2] + 4 - (str[i-1]-'A' + 'B'-str[i-2])); //BA
		dp[i] = max(dp[i], dp[i-2] + 2 - ('B'-str[i-1] + 'B'-str[i-2])); //BB
	}
	
	return dp[N];
}

int main() {
	int T, N;
	scanf("%d",&T);
	while(T--){
		scanf("%d", &N);
		scanf("%s", input);
		printf("%d\n", find(input, N));
	}
}
