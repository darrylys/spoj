/*
TLE
running time in office laptop: 0.46s, home laptop: 0.53s
TLE in SPOJ, 0.25s, SPOJ machine ~75% faster than office laptop
maxinput: 0.88s, now 0.77s

whew, finally AC 0.14s 14M
This problem requires a lot of constant optimizations!
and I meant A LOT!

It is probably impossible to solve this in Java / python.
even in C++, heavy constant optimization is required

algo:
10^500 is around 1700 bits.
so, one f(N) | N ~ 10^500 will be around 1700.
From this, it is possible to brute force all K for all values <= 1700.

after that, a list of numbers where the f(x) = k is obtained.
to calculate the result, convert N to binary number
and for each bit 1, \sum all BinomCombin(remainLength, list[i] - existing 1 bits)

algo is not hard, other things are...
note: fast IO is not very useful here

difficulties:
N is 10^500
Find out how to convert N to binary number

optimizations:
normal test case
Not using any STL (0.82s -> 0.77s)
reduce number of function calls (0.77s -> 0.61s)
reduce number of ifs (0.41s -> 0.31s)
fast IO is not very useful
reduce the number of MOD operations (reduce 0.1s)
reduce the use of long long (reduce 0.1s)
for K >= 6, print 0 directly

note:
{ if (X) X -= MOD; } is actually more expensive than just X %= MOD all the time.

all N=499 digits test case
after all those (0.88s)
defer mod operation til the very end during summing the BinomCombin (0.88s -> 0.52s)
	0.52s in heavy test, 0.22s in normal test.

*/

#include <stdio.h>
#include <string.h>

#define ll long long
//#define _DEBUG
//#define _TIMEIT

#ifdef _TIMEIT
#include <time.h>
#endif

//using namespace std;

const int K = 11;
const int MAXL = 1700;
const int MAXN = 510;
const int MOD = 1000000007;
const int CR = 1000000000;

int listK[K][MAXL];
int listKsize[K];
int minK[MAXL];
int Cc[MAXL][MAXL];
char bit[MAXL];
char Nbuf[510];
int Cbuf[2][MAXN];

void buildC() {
	
	for (int i=0; i<MAXL; ++i) {
		Cc[i][0] = Cc[i][i] = 1;
		for (int j=1; j<i; ++j) {
			Cc[i][j] = (Cc[i-1][j] + Cc[i-1][j-1])%MOD;
			//if (Cc[i][j] >= MOD) Cc[i][j] -= MOD;
		}
	}
	
}

// change to direct access, 0.77 -> 0.61s
//int C(int n, int k) {
//	if (n < k) return 0;
//	return Cc[n][k];
//}

int f(int x) {
	if (minK[x]) {
		return minK[x];
	}
	
	int b = x;
	int s = 0;
	while (b) {
		s++;
		b -= (-b)&b;
	}
	if (s == 1) {
		return minK[x] = 1;
	}
	
	return minK[x] = 1 + f(s);
}

void build() {
	int k;
	
	listK[0][0] = 1;
	listKsize[0] = 1;
	
	minK[1] = 1;
	for (int i=2; i<MAXL; ++i) {
		minK[i] = f(i);
		if (minK[i] <= 10) {
			//listK[minK[i]].push_back(i);
			listK[minK[i]][listKsize[minK[i]]++] = i;
		}
	}
}

int bigint2bin(char * N, int len, char * bitbuf) {
	
	int bufc = 0; // [2]
	int bufi = 0; // [len]
	int part = 0;
	int e10 = 1;
	
	// ok
	for (int i=len-1; i>=0; --i) {
		if (e10 >= CR) {
			//part += e10 * (N[i]-'0');
			Cbuf[bufc][bufi++] = part;/*(int)(part % CR);*/
			part = N[i]-'0';
			e10 = 10;
		} else {
			part += e10 * (N[i]-'0');
			e10 *= 10;
		}
	}
	
	Cbuf[bufc][bufi++] = part;
	
	// incr 1
	for (int i=0; i<bufi; ++i) {
		//buf[bufc][i]++;
		if (++Cbuf[bufc][i] >= CR) {
			Cbuf[bufc][i] = 0;
		} else {
			break;
		}
	}
	
	#ifdef _DEBUG
	printf("buf=[");
	for (int i=bufi-1; i>=0; --i) {
		printf("%09d ", Cbuf[bufc][i]);
	}
	printf("]\n");
	#endif
	
	// OK
	int bitlen = 0;
	while (bufi > 0) {
		
		int lc = 0;
		int tc = 0;
		int nbufc = bufc^1;
		
		for (int i=bufi-1; i>=0; --i) {
			tc += Cbuf[bufc][i];
			Cbuf[nbufc][i] = tc>>1;
			lc = tc&1;
			tc = lc * CR;
		}
		
		bitbuf[bitlen++] = lc;
		
		while (bufi > 0 && Cbuf[nbufc][bufi-1] == 0) {
			bufi--;
		}
		
		bufc = nbufc;
		
	}
	
	return bitlen;
}

// costliest operation...
// 0.77 s!, target < 0.4s (SPOJ is around 2x faster)
int find(char * bitbuf, int bitlen, int K) {
	
	ll sum = 0;
	int exk = 0;
	int stv = 0;
	int lksz = listKsize[K-1];
	int * list = listK[K-1];
	int t;
	
	for (int i=bitlen-1; i>=0 && stv<lksz; --i) {
		if (bitbuf[i]) {
			
			for (int j=stv; j<lksz; ++j) {
				if (list[j] < exk) {
					stv++;
					continue;
				}
				
				t = list[j]-exk;
				if (i < t) {
					break;
				}
				
				//sum += C(i, listK[K-1][j]-exk);
				//sum = (sum + Cc[i][t])%MOD;
				sum = sum + Cc[i][t];
				//if (sum >= MOD) sum -= MOD;
			}
			
			exk++;
			
		}
	}
	
	return (int)(sum%MOD);
}

int main() {
	#ifdef _TIMEIT
	const clock_t begin_time = clock();
	#endif
	
	// small
	{ build(); }
	{ buildC(); }
	
	#ifdef _DEBUG
	for (int i=0; i<=10; ++i) {
		printf("k=%d, size=%d\n", i, listKsize[i]);
		for (int j=0; j<listKsize[i]; ++j) {
			printf("\t%d", listK[i][j]);
		}
		putchar('\n');
	}
	#endif
	
	int T;
	int K;
	
	scanf("%d", &T);
	while (T--) {
		//scanf("%s %d", buf, &K);
		// replace with getchar
		char in;
		while ((in=getchar()) < '0' || in > '9');
		int lenbuf = 0;
		do {
			Nbuf[lenbuf++] = in;
		} while ((in=getchar()) >= '0' && in <= '9');
		Nbuf[lenbuf] = '\0';
		
		scanf("%d", &K);
		
		if (K >= 6) {
			printf("0\n");
			continue;
		}
		
		#ifdef _DEBUG
		printf("N=[%s], K=%d\n", Nbuf, K);
		#endif
		
		int bitlen = bigint2bin(Nbuf, lenbuf, bit);
		
		#ifdef _DEBUG
		printf("bitlen=%d, bit=[", bitlen);
		for (int i=bitlen-1; i>=0; --i) {
			putchar(bit[i]+'0');
		}
		printf("]\n");
		#endif
		
		int sum = find(bit, bitlen, K);
		
		printf("%d\n", sum);
		
	}
	
	#ifdef _TIMEIT
	fprintf(stderr, "whole %lf\n",  float( clock () - begin_time ) /  CLOCKS_PER_SEC);
	#endif
	
}
