/*
very cool problem
this problem is actually easy but quite disguised.
note that if X >= sqrt(B), brute force is sufficient.
and for X < sqrt(B), there is a trivial DP solution.

final complexity
if X >= sqrt(B): O(sqrt(B)*log(B))
else: O(|digits|(X*log(B) + log(B))) == O(|digit| * X * log(B))

*/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define ll long long
#define MXN (12)
#define LIMX (320000)
//#define _DEBUG

ll max(ll a, ll b) { return (a>b) ? a:b; }
ll min(ll a, ll b) { return (a<b) ? a:b; }
ll _10e[MXN];
ll dp[MXN][LIMX];

void build10e() {
	_10e[0] = 1;
	for (int i=1; i<MXN; ++i) {
		_10e[i] = 10*_10e[i-1];
	}
}

void build(int X, char * usabledigits, int ndigits) {
	
	// L=1;
	for (int i=0; i<ndigits; ++i) {
		dp[1][(usabledigits[i]-'0')%X]++;
	}
	
	// L>1
	for (int L=2; L<MXN; ++L) {
		for (int mX=0; mX<X; ++mX) {
			dp[L][mX] = 0;
			for (int i=0; i<ndigits; ++i) {
				dp[L][mX] += dp[L-1][(mX - (((usabledigits[i]-'0')*_10e[L-1])%X) + X)%X];
			}
		}
	}
	
	#ifdef _DEBUG
	printf("build\nMOD=");
	for (int i=0; i<X; ++i) {
		printf("\t%d", i);
	}
	printf("\n");
	
	for (int L=1; L<MXN; ++L) {
		printf("%d", L);
		for (int i=0; i<X; ++i) {
			printf("\t%d", dp[L][i]);
		}
		printf("\n");
	}
	printf("\n");
	#endif
	
}

int ll2intarr(ll X, int * buf) {
	int len = 0;
	if (X) {
		len = ll2intarr(X/10, buf);
		buf[len] = X%10;
		return len+1;
	} else {
		return 0;
	}
}

ll getByDP(int X, ll N, char * usabledigits, int ndigits) {
	
	int nbuf[15];
	int nlen = ll2intarr(N, nbuf);
	
	#ifdef _DEBUG
	printf("N -> intarray: [");
	for (int i=0; i<nlen; ++i) {
		printf("%d", nbuf[i]);
	}
	printf("]\n");
	#endif
	
	ll sum = 0;
	int prevmod = 0;
	bool found = false;
	
	for (int pl=0; !found && pl < nlen-1; ++pl) {
		
		for (int i=0; i<ndigits; ++i) {
			
			if (usabledigits[i]-'0' < nbuf[pl]) {
				#ifdef _DEBUG
				printf("prevmod=%d, pl=%d, usabledigit=%d\n", prevmod, pl, usabledigits[i]-'0');
				printf("dp[%d][%d]=%d\n", 
					nlen-pl-1,
					(2*X - prevmod - (((usabledigits[i]-'0')*_10e[nlen-pl-1])%X)) % X,
					dp[nlen-pl-1][ (2*X - prevmod - (((usabledigits[i]-'0')*_10e[nlen-pl-1])%X)) % X]
				);
				#endif
				
				sum += dp[nlen-pl-1][ (2*X - prevmod - (((usabledigits[i]-'0')*_10e[nlen-pl-1])%X)) % X];
			} else {
				
				if (usabledigits[i]-'0' == nbuf[pl]) {
					// add prevmod for highest allowable digit
					prevmod = (prevmod + (usabledigits[i]-'0')*_10e[nlen-pl-1])%X;
				} else {
					found = true;
				}
				
				break;
			}
		}
	}
	
	// last 10 checks
	for (int i=0; !found && i<ndigits; ++i) {
		if (usabledigits[i]-'0' < nbuf[nlen-1]) {
			sum += (prevmod + usabledigits[i]-'0')%X == 0;
		}
	}
	
	return sum;
}


// if X >= sqrt(B);
ll bruteForce(ll X, ll A, ll B, char * digitflag) {
	#ifdef _DEBUG
	printf("bruteForce: %lld\n", X);
	#endif
	
	ll nox = 0;
		
	ll st;
	if (A%X) {
		st = A - A%X + X;
	} else {
		st = A;
	}
	
	#ifdef _DEBUG
	printf("check starts from: %lld in range [%lld, %lld], st mod X=%lld\n", st, A, B, st%X);
	#endif
	
	for (ll i = st; i <= B; i += X) {
		ll sx = i;
		int v = 1;
		
		#ifdef _DEBUG
		printf("check %lld ", i);
		#endif
		
		while (sx) {
			if (!digitflag[sx%10]) {
				v = 0;
				break;
			}
			sx /= 10;
		}
		
		#ifdef _DEBUG
		printf("%d\n", v);
		#endif
		nox += v;
	}
	
	return nox;
}

int main() {
	ll X, A, B;
	char usabledigits[13];
	char sorteddigits[13];
	char digitflag[13] = {0};
	
	scanf("%lld %lld %lld", &X, &A, &B);
	scanf("%s", usabledigits);
	
	int diglen = strlen(usabledigits);
	for (int i=0; i<diglen; ++i) {
		digitflag[usabledigits[i]-'0'] = 1;
	}
	int p=0;
	for (int i=0; i<10; ++i) {
		if (digitflag[i]) {
			sorteddigits[p++] = i+'0';
		}
	}
	
	#ifdef _DEBUG
	printf("digitflag: \n[");
	for (int i=0; i<10; ++i) {
		printf("%d\t", i);
	}
	printf("]\n[");
	for (int i=0; i<10; ++i) {
		printf("%d\t", digitflag[i]);
	}
	printf("]\nsorteddigits: [");
	for (int i=0; i<p; ++i) {
		putchar(sorteddigits[i]);
	}
	printf("]\n");
	#endif
	
	if (p == 10) {
		// all digits are usable, just do it!
		printf("%lld\n", B/X - (A-1)/X);
		return 0;
	}
	
	ll res;
	
	if (X >= sqrt(B)) {
		res = bruteForce(X, A, B, digitflag);
		
	} else {
		int iX = (int)X;
		
		build10e();
		build(iX, sorteddigits, p);
		ll start = getByDP(iX, A, sorteddigits, p);
		ll end = getByDP(iX, B+1, sorteddigits, p);
		
		#ifdef _DEBUG
		printf("start=%lld, end=%lld\n", start, end);
		#endif
		
		res = end - start;
		
	}
	
	printf("%lld\n", res);
	
}

