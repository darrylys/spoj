/*
AC 0.55s 2.7M SPOJ C++ 4.3.2

Algo: math

Problem: find how many of (a*x+b)%M, (a*(x+1)+b)%M, ..., (a*(x+n)b)%M in in range [c, d]
assume x = 0 and c = 0.

use brute force and the pattern can be found
The sequence can be grouped into chunks of increasing continuous subsequences.

For example, look at  2, 5, 8, 11, 14 (a=2, b=3)
taken mod 5.  This is 2, 0, 3, 1, 4 when taken mod 5, so the chunks
are <2>, then <0, 3>, then <1, 4>

The first and last chunks are different and can be dealt separately as special case.
The number of dots for each chunk is either floor(d/a) or floor(d/a)+1.

let p = number of chunks with floor(d/a) number of dots
let q = number of chunks with floor(d/a)+1 number of dots

the number of dots is thus (p+q)*(floor(d/a)) + q.

(p+q) is easy to obtain. This is the number of "wraparounds"
Basically, floor((a*N+b)/M) - 1 (already excluding the first and last chunks)

to obtain q, notice that q consists of the lowest dots and notice that
when the lowest dots is in range [0, j] with j = [0, a-1], the number of dots in that chunk is floor(d/a)+1
j can be easily calculated.

Also, notice that the dots in the lowest positions in every chunk creates another arithmetic sequence under modulo a'.
This subproblem is the same problem we solve, just different parameters so we can recurse it.
Straightforward recursion is too slow because the new modulus (a') can be a-1. So, split the case into two.

If a' < a-a', recurse using a'
else, recurse using (a-a') which means working the arithmetic sequence backwards.

This allows the subproblem to be a/2 at max.

let F(a, b, M, d, N) =  the number of (b)%M, (a+b)%M, (2a+b)%M, ..., (a*N+b)%M in in range [0, d]

Base Cases: when M mod a == 0.

Space: O(lg(N))
Time: O(lg(N))
*/

#include <stdio.h>

typedef long long ll;

inline ll max(ll a, ll b) {
	return (a>b) ? a:b;
}

inline ll min(ll a, ll b) {
	return (a<b) ? a:b;
}

ll F(ll a, ll b, ll M, ll c, ll N) {
	//printf(">> F(a=%lld, b=%lld, M=%lld, c=%lld, N=%lld)\n" ,  a, b, M, c , N);
	
	if (N < 0 || c < 0) {
		return 0;
	}
	
	if (a == 0) {
		if (c >= b) {
			return N+1;
		} else {
			return 0;
		}
	}
	
	ll p1, p2, p3, p4;
	
	ll aNb = a*N+b;
	ll aNbM = aNb%M;
	
	//printf("aNb=%lld, aNbM=%lld\n", aNb, aNbM);
	
	if ((M%a) == 0) {
		
		ll nchunk = max(aNb/M - 1, 0);
		//printf("nchunk=%lld\n" , nchunk);
		
		//# chunk last
		if (aNb >= M) {
			if (c >= b) {
				p1 = max((c - b) / a + 1, 0);
			} else {
				p1 = 0;
			}
			
			if (c <= aNbM) {
				
				//printf("c=%lld, a*N+b=%lld, (a*N+b)%%M=%lld, ((a*N+b)%%M)%%a=%lld, a=%lld\n" , c, a*N+b, (a*N+b)%M, ((a*N+b)%M)%a, a);
				if (c < (aNbM)%a) {
					p2 = 0;
				} else {
					p2 = (c - (aNbM)%a)/a + 1;
				}
			} else {
				p2 = (aNbM/a) + 1;
			}
		} else {
			if (min(c, aNb) < b) {
				p1 = 0;
			} else {
				p1 = max((min(c, aNb) - b) / a + 1, 0);
			}
			p2 = 0;
		}
		//# middles
		ll base = (aNbM)%a;
		//printf("c=%lld, base=%lld\n", c, base);
		
		if (c >= base) {
			p3 = (((c-base)/a)+1)*nchunk;
		} else {
			p3 = 0;
		}
		//printf("p1=%lld, p2=%lld, p3=%lld\n" , p1, p2, p3);
		
		return p1 + p2 + p3;
	}
	
	if (aNb >= M) {
		if (c >= b) {
			p1 = max((c - b) / a + 1, 0);
		} else {
			p1 = 0;
		}
		
		if (c <= aNbM) {
			
			//printf("c=%lld, a*N+b=%lld, (a*N+b)%%M=%lld, ((a*N+b)%%M)%%a=%lld, a=%lld\n" , c, a*N+b, (a*N+b)%M, ((a*N+b)%M)%a, a);
			if (c < (aNbM)%a) {
				p2 = 0;
			} else {
				p2 = (c - (aNbM)%a)/a + 1;
			}
		} else {
			p2 = (aNbM/a) + 1;
		}
	} else {
		if (min(c, aNb) < b) {
			p1 = 0;
		} else {
			p1 = max((min(c, aNb) - b) / a + 1, 0);
		}
		p2 = 0;
	}
	
	ll nchunks = max((aNb/M) - 1, 0);
	p3 = (c/a) * nchunks;
	p4 = 0;
	
	//printf("p1=%lld, p2=%lld, nchunk=%lld, p3=%lld\n" , p1, p2, nchunks, p3);
	
	if (nchunks > 0) {
		ll r = M%a;
		ll bt, xt;
		
		if (a-r < r) {
			//printf("a-r < r, r=%lld, a-r=%lld\n" , r, a-r);
			
			if ((M-b)%a == 0) {
				bt = 0;
				
			} else {
				xt = (M-b)/a + 1;
				bt = (a * xt + b)%M;
				
				//printf("xt=%lld\n" , xt);
			}
			//printf("bt=%d\n" , bt);
			
			p4 = F(a-r, bt, a, c%a, nchunks-1);
		} else {
			//printf("a-r >= r, r=%lld, a-r=%lld\n" , r, a-r);
			
			ll xm = N - aNbM/a - 1;
			xt = xm - ((a*xm+b)%M)/a;
			bt = (a*xt+b)%M;
			
			//printf("xm=%lld, xt=%lld, bt=%lld\n", xm, xt, bt);
			
			p4 = F(r, bt, a, c%a, nchunks-1);
		
		}
		//printf("p4=%lld\n" , p4);
	}
	
	return p1+p2+p3+p4;
	
}

int main() {
	int T;
	ll a,b,x,n,c,d,m;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %lld %lld %lld %lld %lld", &a,&b,&x,&n,&c,&d,&m);
		//# 0,1,2,3,4,5,6
		//# a,b,x,n,c,d,m
		
		//# a,b,M,d,N
		ll bxnd = F(a, b, m, d, x+n);
		ll bxnc = F(a, b, m, c-1, x+n);
		ll bxd = F(a, b, m, d, x-1);
		ll bxc = F(a, b, m, c-1, x-1);
		
		//printf("bxnd=%lld, bxnc=%lld, bxd=%lld, bxc=%lld\n", bxnd , bxnc , bxd , bxc);
		
		//# try one case first #a, b, M, c, N
		printf("%lld\n" , (bxnd - bxnc - bxd + bxc));
	}
}
