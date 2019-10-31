#include<stdio.h>

#define ll long long

// 1e15
#define UPPER (1000000000000LL)

int gcd(int a, int b) {
	if (b == 0) return a;
	else return gcd(b, a%b);
}

int lcm(int a, int b) {
	return a / gcd(a,b) * b;
}

ll qn(ll N, int a, int lcmab, int lcmabc) {
	return N/a - N/lcmab + N/lcmabc;
}

ll findN(int A, int B, int C, int _N, int lcmab, int lcmabc) {
	ll u=1, v=UPPER, c, N = _N;
	
	while(1) {
		if (u>=v) {
			return u;
		} else {
			c = u + (v-u)/2;
			ll key = qn(c, A, lcmab, lcmabc);
			if (key < N) {
				u = c+1;
			} else {
				v = c;
			}
		}
	}
}

int main() {
	int A, B, C, M, N;
	scanf("%d %d %d %d", &A, &B, &C, &M);
	int lcmab = lcm(A,B);
	int lcmabc = lcm(lcmab, C);
	
	while(M--) {
		scanf("%d", &N);
		printf("%lld\n", findN(A, B, C, N, lcmab, lcmabc));
	}
}

