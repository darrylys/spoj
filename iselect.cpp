#include <stdio.h>

#define ll long long
#define MAXN 10006
#define SML (-(1LL<<62))

ll f[MAXN][4];
int A[MAXN];
int B[MAXN];

inline char fl(char first, char last) {
	return (first<<1) + last;
}

inline ll max(ll a, ll b) {
	return (a>b)? a:b;
}

inline ll max3(ll a, ll b, ll c) {
	return max(max(a,b),c);
}

int main() {
	int N, T;
	scanf("%d",&T);
	while (T--) {
		scanf("%d",&N);
		for (int i=0; i<N; ++i) {
			scanf("%d", &A[i]);
		}
		for (int i=0; i<N; ++i) {
			scanf("%d", &B[i]);
		}
		
		f[0][fl(0,0)] = -B[0];
		f[0][fl(0,1)] = SML;
		f[0][fl(1,0)] = SML;
		f[0][fl(1,1)] = A[0];
		
		if (N > 1) {
		
			f[1][fl(0,0)] = -B[0] - B[1];
			f[1][fl(0,1)] = -B[0] + A[1];
			f[1][fl(1,0)] = A[0] - B[1];
			f[1][fl(1,1)] = SML;
			
			for (int i=2; i<N-1; ++i) {
				f[i][fl(0,0)] = max(f[i-1][fl(0,0)], f[i-1][fl(0,1)]) - B[i];
				f[i][fl(0,1)] = f[i-1][fl(0,0)] + A[i];
				f[i][fl(1,0)] = max(f[i-1][fl(1,0)], f[i-1][fl(1,1)]) - B[i];
				f[i][fl(1,1)] = f[i-1][fl(1,0)] + A[i];
			}
			
			if (N > 2) {
			int i = N-1;
				f[i][fl(0,0)] = max(f[i-1][fl(0,0)], f[i-1][fl(0,1)]) - B[i];
				f[i][fl(0,1)] = f[i-1][fl(0,0)] + A[i];
				f[i][fl(1,0)] = max(f[i-1][fl(1,0)], f[i-1][fl(1,1)]) - B[i];
				f[i][fl(1,1)] = SML;
			}
		}
		
		printf("%lld\n", max3(f[N-1][fl(0,0)], f[N-1][fl(0,1)], f[N-1][fl(1,0)]));
		
	}
	
	return 0;
}

