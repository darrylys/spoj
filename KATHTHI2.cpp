/*
AC 0.00s (!) 2.8M SPOJ

the problem is to find the global maximum of the following function:
f(N) = C(N, K) * p^K * (1-p)^(N-K) ; 0.0 < p <= 1.0

to simplify things, lets separate the case for p = 1.0 so we don't have to deal with zeros

the obvious solution is to solve 
 df(N)
------- == 0
  dN 

However, finding derivative of combinatorial is not trivial.

So, 
apply ln to f(N) and find that instead
ln f(N) = ln (C(N, K) * p^K * (1-p)^(N-K))
		= ln (N!) - ln (K!) - ln ((N-K)!) + K ln p + (N-K) ln (1-p)

apply approximation on ln (X!). ln X! ~ X ln X
		~ N ln N - K ln K - (N-K) ln (N-K) + K ln p + (N-K) ln (1-p)

now find df(N)/dN == 0 from above function
		~ ln(N) + 1 - ln(N-K) - 1 + ln(1-p) == 0
		~ ln(N / (N-K) * (1-p)) == ln 1
		~ N/(N-K)*(1-p) = 1
		~ N*(1-p) = N-K
		~ -Np = -K
		~ N = K/p
		
Now, we found that N ~~ K/p

With this in hand, we can check whether this N is the intended N by incrementing or decrementing N as needed
Adjust N so that it is what is intended by the problem.

The maximum N follows this equation
f(N-1) < f(N) > f(N+1)

So, decrement N until f(N-1) < f(N)
or increment N until f(N+1) <= f(N) (we want the SMALLEST N with largest f(N))

Interestingly, since there is only one N, the shape of the function f(N) in graph is bell-shaped
with just ONE global maximum. This limits the number increments or decrements that we did.
So far, even with K = 100 and p = 0.01, only one decrement is performed.

Space: O(~10000)
Time: O(1) per testcase

*/

#include <stdio.h>
#include <math.h>

//#define DEBUG

const int MAXN = 10010;

double LN[MAXN];

void buildLnTbl() {
	
	LN[0] = 0;
	LN[1] = 0;
	for (int i=2; i<MAXN; ++i) {
		LN[i] = LN[i-1] + log(i);
	}
	
}

// assume: p < 1.0, K <= N.
double logV(int N, double p, int K) {
	// ln( C(N,K) * p^K * (1-p)^(N-K)
	// ln(N!) - ln((N-K)!) - ln(K!) + K ln p + (N-K) ln (1-p)
	
	if (N < K) {
		// -INF
		return -100000.0;
	}
	
	double lnC;
	if (N == K) {
		lnC = 0.0;
	} else {
		lnC = LN[N] - LN[N-K] - LN[K];
	}
	
	// negative values!
	return lnC + K * log(p) + (N-K) * log(1-p);
}

int find(int K, double p) {
	
	// around 10000 if K=100, p=0.01
	int N = (int)floor(K / p);
	#ifdef DEBUG
	printf("[debug] N=%d\n", N);
	#endif
	
	double lgN = logV(N, p, K);
	double lgNp;
	
	#ifdef DEBUG
	printf("lgN=%lf\n", lgN);
	#endif
	
	// find N-1 until logV < this
	while (N > 0) {
		// find N-1
		lgNp = logV(N-1, p, K);
		#ifdef DEBUG
		printf("[-] lgNp=%lf\n", lgNp);
		#endif
		
		if (fabs(lgN-lgNp) <= 1e-9 || lgNp >= lgN) {
			lgN = lgNp;
			N--;
		} else {
			break;
		}
		
	}
	
	// find N+1 until logV < this
	while (1) {
		lgNp = logV(N+1, p, K);
		#ifdef DEBUG
		printf("[+] lgNp=%lf\n", lgNp);
		#endif
		
		if (lgNp > lgN && fabs(lgN-lgNp) > 1e-9) {
			lgN = lgNp;
			N++;
		} else {
			break;
		}
	}
	
	return N;
}

int main() {
	buildLnTbl();
	
	int T, K;
	double p;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d%lf", &K, &p);
		
		if (p > 0.99) {
			// p == 1.0
			printf("%d\n", K);
			continue;
		}
		
		printf("%d\n", find(K, p));
	}
	return 0;
}
