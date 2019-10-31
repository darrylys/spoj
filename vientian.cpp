#include <stdio.h>
/*
AC 0.04s 2.6M SPOJ, not a very good time, plenty of 0.00s solvers but oh whatever...

algo:
standard DP memoization algo.

Analysis
there are 3 towers and divided to 3 functionalities: source tower, dest tower and auxiliary tower
let F(N, S, A, T) means minimum moves required to move a pile sized N from tower S to tower T using tower A as auxiliary

there are only 2 possible moves to do this, directly means moving the plate directly without the use of auxiliary. If this is impossible, then it is INFINITE cost:
	1) 	move pile (N-1) to tower A, 
		move base from S to T directly (in this case, we CANNOT use A because pile (N-1) is there)
		and last, move pile (N-1) from A to T.
		
	2)	move pile (N-1) to T
		move base from S to A directly (we cannot use the auxiliary (T) here because pile (N-1) is placed there right now)
		move pile (N-1) to S
		move base from A to T directly
		lastly, move pile (N-1) to T
 
find the minimum of the two possible moves and you're done.

*/

#include <string.h>

#define ll long long
#define INF (-2)

ll dp[40][3][3]; // [N][src_tower][targ_tower]
char map[3][4]; // [src][dest]
int cost[3][3];

ll F(int N, int srctow, int auxtow, int desttow) {
	if (dp[N][srctow][desttow] != -1) {
		return dp[N][srctow][desttow];
	}
	
	if (N == 1) {
		return dp[1][srctow][desttow] = cost[srctow][desttow];
	}
	
	// s1
	ll s1[3];
	s1[0] = F(N-1, srctow, desttow, auxtow);
	s1[1] = (map[srctow][desttow] != 9 ? 1 : INF);//F(1, srctow, auxtow, desttow);
	s1[2] = F(N-1, auxtow, srctow, desttow);
	
	ll ss1 = 0;
	for (int i=0; i<3; ++i) {
		if (s1[i] == INF) {
			ss1 = INF;
			break;
		} else {
			ss1 += s1[i];
		}
	}
	
	// s2
	ll s2[5];
	s2[0] = F(N-1, srctow, auxtow, desttow);
	s2[1] = (map[srctow][auxtow] != 9 ? 1 : INF);//F(1, srctow, desttow, auxtow);
	s2[2] = F(N-1, desttow, auxtow, srctow); 
	s2[3] = (map[auxtow][desttow] != 9 ? 1 : INF);//F(1, auxtow, srctow, desttow); // if impossible in auxtow (N-1 is there), this should be INF!
	s2[4] = F(N-1, srctow, auxtow, desttow);
	
	ll ss2 = 0;
	for (int i=0; i<5; ++i) {
		if (s2[i] == INF) {
			ss2 = INF;
			break;
		} else {
			ss2 += s2[i];
		}
	}
	
	if (ss1 == INF && ss2 == INF) {
		return dp[N][srctow][desttow] = INF;
	} else if (ss1 == INF) {
		return dp[N][srctow][desttow] = ss2;
	} else if (ss2 == INF) {
		return dp[N][srctow][desttow] = ss1;
	} else {
		return dp[N][srctow][desttow] = (ss1 < ss2) ? ss1 : ss2;
	}
	
}

int min(int a, int b) {
	return (a<b) ? a:b;
}

void initc(int s, int a, int t) {
	if (s == t) cost[s][t] = 0;
	else {
		cost[s][t] = min(map[s][t], map[s][a] + map[a][t]);
		if (cost[s][t] >= 9) cost[s][t] = INF;
	}
}

int main() {
	int T, N;
	scanf("%d", &T);
	while (T--) {
		for (int i=0; i<3; ++i) {
			scanf("%s", map[i]);
		}
		scanf("%d", &N);
		
		memset(dp, -1, sizeof(dp));
		
		for (int i=0; i<3; ++i) {
			for (int j=0; j<3; ++j) {
				map[i][j] -= '0';
				
				if (i != j && map[i][j] == 0) {
					map[i][j] = 9;
				}
			}
		}
		
		initc(0, 1, 2);
		initc(0, 2, 1);
		initc(1, 0, 2);
		initc(1, 2, 0);
		initc(2, 0, 1);
		initc(2, 1, 0);
		
		//printf("COST\n");
		//for (int i=0; i<3; ++i) {
		//	for (int j=0; j<3; ++j) {
		//		printf("%d\t", cost[i][j]);
		//	}
		//	printf("\n");
		//}
		
		
		ll res = F(N, 0, 1, 2);
		if (res == INF) {
			printf("Epic Fail...\n");
		} else {
			printf("%lld\n", res);
		}
		
	}
	return 0;
}

