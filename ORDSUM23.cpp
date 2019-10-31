#include<stdio.h>

#define ll long long
#define MOD (1000000007)
#define MAXN (1000001)

int F[MAXN];

int main() {
	F[0] = 1;
	F[1] = 0;
	F[2] = F[3] = 1;
	for (int i=4; i<MAXN; ++i) {
		F[i] = (F[i-2] + F[i-3])%MOD;
	}
	int T, N;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		printf("%d\n", F[N]);
	}
	return 0;
}