#include<stdio.h>
#include<string.h>

double dp[1<<16];
bool flag[1<<16];
double p[16][16];
int twoexp[29];

void fil() {
	for (int i=0; i<18; ++i) {
		twoexp[(1<<i)%29] = i;
		//printf("%d=%d=%d\n", 1<<i, (1<<i)%29, i);
	}
}

double func(int fishUsed, int n) {
	//printf("fishused=%d, n=%d\n", fishUsed, n);
	
	if (flag[fishUsed]) {
		return dp[fishUsed];
	}
	
	flag[fishUsed] = true;
	
	// base case
	if (n == 1) {
		
		//printf("n=1, %d\n", fishUsed);
		
		int exp = twoexp[fishUsed%29];
		return dp[fishUsed] = p[exp][0];
	}
	
	int b = fishUsed;
	double sum = 0;
	while (b > 0) {
		int fish = b & (-b);
		int fishcode = twoexp[fish%29];
		
		sum += p[fishcode][n-1] * func(fishUsed - fish, n-1);
		
		b -= fish;
	}
	
	return dp[fishUsed] = sum;
}

int main() {
	fil();
	int T, n;
	scanf("%d",&T);
	while(T--){
		scanf("%d", &n);
		memset(flag, false, sizeof(flag));
		for (int fish=0; fish<n; ++fish) {
			for (int aq=0; aq<n; ++aq) {
				scanf("%lf", &p[fish][aq]);
			}
		}
		printf("%.9lf\n", func((1<<n)-1, n));
	}
	return 0;
}
