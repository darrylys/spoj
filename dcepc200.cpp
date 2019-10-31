/*
AC 0.11s 2.7M SPOJ

this super unoptimized code gets pretty good time??
TJANDRA gets 0.10s

algo:
K1*K2 = N, where K0 and K1 satisfies (Totient(K!)  mod K) !=0.  
it means that K is prime
the only possible way to (Totient(K!)  mod K) !=0, is when K is prime

K0 and K1 can be the same
so, if N is not P1 * P2 or P^2, print -1, continue;

if K0 == K1, minimum x+y = M / K0 ; K0 divides M, otherwise, print -1, continue;

else:
the equation becomes:
K0x + K1y = m

first, obtain the solutions to this equation:
K0 X + K1 Y = 1

this is solvable easily using Extended Euclid Algorithm
after that, 
the equation can be modified by multiplying m both sides

K0(mX)+K1(mY) = m

now, brute force check all possible x and y that satisfies the equation K0x + K1y = m
just pick large ranges so a good number of values can be examined.

it can be seen that (x+y) is in increasing order / decreasing order
and the smallest abs(x+y) is in the middle of the array.
and interestingly, (mX,mY) also exists in the array (if not, expand the range)
but (mX,mY) is most likely not the minimum.

however,
this pair (mX-K[1], mY+K[0]) or (mX+K[1], mY-K[0])
will is the immediate next or immediate previous pair of (mX,mY) in the array.

This allows the possibility to do a binary search in the array.
just find the smallest one using binary search

Time: O(N / ln(N) + T * N / ln(N) * lg(200000))
Space: O(sqrt(N))

*/

#include <stdio.h>

#define MXPRIME 1300
#define MOD 10000000000283LL
#define ull unsigned long long

int prime[MXPRIME];
char flag[10001];

//#define _DEBUG

inline int abs(int x) {
	return (x<0)?-x:x;
}

typedef struct {
    int x;
    int y;
} PAIR;

int min(int a, int b) {
	return (a<b)?a:b;
}

inline int min3(int a, int b, int c) {
	return min(a, min(b, c));
}

PAIR extgcd(int a, int b) {
    int x = 0, y = 1, lastx = 1, lasty = 0, q, c, cx, cy;
    while (b>1) {
        q = a/b;
        c = a%b;
        a = b;
        b = c;
        
        cx = lastx - q*x;
        lastx = x;
        x = cx;
        
        cy = lasty - q*y;
        lasty = y;
        y = cy;
    }
    
    PAIR pair;
    pair.x = x;
    pair.y = y;
    return pair;
}

int buildprime() {
    
    prime[0] = 2;
    int f = 1;
    
    for (int i=3; i<=100; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
            for (int j=i*i; j<=10000; j+=i) {
                flag[j] = 1;
            }
        }
    }
    
    for (int i=101; i<=10000; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
        }
    }
    
    return f;
}

int main() {
	
	int T, N, M, nprimes = buildprime();
	
	int fac[8];
	int exp[8];
	int nf;
	
    int K[2], pk;
    bool dead;
    
    ull FN; //useless
    
    scanf("%d", &T);
    while (T--) {
        scanf("%d %llu %d", &N, &FN, &M);
		
		#ifdef _DEBUG
		printf("\nINPUT(N=%d, M=%d)\n", N, M);
		#endif
		
        dead = false;
        pk = 0;
        
		nf = 0;
		
        for (int i=0; !dead && i < nprimes && N >= prime[i]*prime[i]; ++i) {
            if (N%prime[i] == 0) {
				
				if (nf == 2) {
					dead = true;
					break;
				}
				
				exp[nf] = 0;
				fac[nf] = prime[i];
				
				do {
					N/=prime[i];
					exp[nf]++;
					if (exp[nf] > 2) {
						dead = true;
						break;
					}
					
				} while (N%prime[i] == 0);
				
				nf++;
            }
        }
        
		if (N > 1) {
			fac[nf] = N;
			exp[nf] = 1;
			nf++;
			//K[pk++] = N;
		}
		
        if (nf > 2) {
			dead = true;
		}
        
        if (nf == 1) {
			if (exp[0] == 2) {
				K[0] = K[1] = fac[0];
			} else {
				dead = true;
			}
			
		} else {
			if (exp[0] == 1 && exp[1] == 1) {
				K[0] = fac[0];
				K[1] = fac[1];
			} else {
				dead = true;
			}
			
		}
		
		if (K[0] == K[1] && M%K[0] != 0) {
			dead = true;
		}
		
		#ifdef _DEBUG
		printf("nf=%d\n", nf);
		for (int i=0; i<nf; ++i) {
			printf("%d^%d ", fac[i], exp[i]);
		}
		putchar('\n');
		printf("K[0]=%d, K[1]=%d\n", K[0], K[1]);
		#endif
		
		if (dead) {
            printf("-1\n");
            continue;
        }
        
		#ifdef _DEBUG
		printf("P1=%d, P2=%d\n", K[0], K[1]);
		#endif
		
		int xymin;
		
		if (K[0] == K[1]) {
			xymin = M / K[0];
			
		} else {
			
			PAIR pairk = extgcd(K[0], K[1]);
			
			int x = pairk.x;
			int y = pairk.y;
			
			x = M*x;
			y = M*y;
			
			#ifdef _DEBUG
			printf("x=%d, y=%d, K0=%d, K1=%d\n", x, y, K[0], K[1]);
			#endif
			
			int u=0, v=200000, c;
			int midp = v/2;
			while (u<v) {
				
				c = (u+v)/2;
				
				int nx = x + (c-midp)*K[1];
				int ny = y - (c-midp)*K[0]; 
				#ifdef _DEBUG
				printf("______nx+ny=%d, u=%d,v=%d, c=%d, c-midp=%d\n", nx+ny, u, v, c, c-midp);
				#endif
				
				if (nx + ny < 0) {
					u = c+1;
				} else {
					v = c;
				}
				
			}
			
			#ifdef _DEBUG
			printf("u=%d, u-midp=%d\n", u, u-midp);
			#endif
			
			u -= midp;
			
			int xy1 = (x + (u-1)*K[1] - (u-1)*K[0] + y);
			int xy2 = (x + (u)*K[1] - (u)*K[0] + y);
			int xy3 = (x + (u+1)*K[1] - (u+1)*K[0] + y);
			
			#ifdef _DEBUG
			printf("min3(abs(%d),abs(%d),abs(%d))\n", xy1, xy2, xy3);
			#endif
			
			xymin = min3(abs(xy1), abs(xy2), abs(xy3));
		}
		
		#ifdef _DEBUG
		printf("xymin=%d\n", xymin);
		#endif
		
        ull hr = 1;
        for (int i=1; i<=M; ++i) {
            hr = (hr * xymin) % MOD;
        }
        
        printf("%llu\n", hr);
		
	}
}
