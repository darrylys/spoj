#include <stdio.h>
#include <string.h>

#define ll long long

ll dp[20][10][16];

void build() {
	for (int i=0; i<=9; ++i) {
		dp[1][i][i] = 1;
	}
	
	for (int i=2; i<=19; ++i) {
		for (int d=0; d<=9; ++d) {
			for (int di=0; di<=9; ++di) {
				for (int x=0; x<=15; ++x) {
					dp[i][d][d ^ x] += dp[i-1][di][x];
				}
			}
		}
	}
}

ll find0(char* in, int len) {
	
	ll sum = 0;
	int exh = 0;
	for (int l = 0; l < len; ++l) {
		for (int d = 0; d+'0'<in[l]; ++d) {
			sum += dp[len-l][d][exh];
		}
		exh ^= (in[l]-'0');
	}
	return sum;
}

ll find(ll A) {
	char buf[25];
	
	ll s = A;
	int len = 0;
	while (s) {
		s /= 10;
		len++;
	}
	
	s = A;
	int slen = len;
	while (s) {
		buf[--len] = s%10 + '0';
		s /= 10;
	}
	
	return find0(buf, slen);
}

int main() {
	build();
	/*
	for (int i=0; i<=9; ++i) {
		for (int x=0; x<=15; ++x) {
			printf("dp[%d][%d][%d]=%lld\n", 19, i, x, dp[19][i][x]);
		}
		printf("\n");
	}
	
	char buf[23];
	*/
	int T;
	ll A, B;
	
	scanf("%d",&T);
	while(T--){
		scanf("%lld %lld", &A, &B);
		ll aliceA = find(A);
		ll aliceB = find(B+1);
		
		printf("%lld %lld\n", B+1-A-aliceB+aliceA, aliceB-aliceA);
	}
	return 0;
}

