/*
AC 0.00s 5.2M SPOJ

algo:
simulation

the idea is to generate the sequence bit by bit, finding out
whether the next bit is 0 or 1.

observations:
1.	the initial sequence of bits for smallest uroborus number will be
	0000...0; n zeros.
	since each number should only appear once, n zeros at the beginning will always
	produce the smallest uroborus number.

2.	since the beginning is n zeros, the end will be n ones.
	it is required to delay ones as much as possible, so put them in the end
	
3.	from (1) and (2), when encountered bit sequences of 1*0*, ignore them
	because they have been produced.

algo:
Array L[2^N], isUsed[2^N]

L <- [0]
isUsed <- [FALSE]

L[0] = 0
isUsed[0] = true

set last elements of L to be numbers with binary representation of format 1*0* of length N bits
and set the isUsed as true for those numbers

Now, generate the rest of the numbers
the next number will be either:
1. (L[i-1] * 2) mod 2^N
2. (L[i-1] * 2 + 1) mod 2^N

for each step of generation, always prefer the 1st option to the 2nd
because we want the smallest uroborus number.

if 1st option is used, go for 2nd option

loop until end

time & space complexity: O( T + 15*2^15 )

*/

#include <stdio.h>

//#define _DEBUG

int gbuf[16][1<<15];
bool gused[16][1<<15];

// assume buf and used is memsetted to 0/(false)
void fill(int n, int * buf, bool * used) {
	
	#ifdef _DEBUG
	printf("fill(%d)\n", n);
	#endif
	
	used[0] = true;
	
	int mask = (1<<n)-1;
	int last = 1<<n;
	for (int st = ((1<<(n-1))-1)<<1, i=1; st > 0; st=(st<<1)&mask, ++i) {
		used[st] = true;
		buf[last - n + i] = st;
	}
	
	int i = 1;
	int s = 0;
	buf[0] = 0;
	while (i <= (last - n)) {
		
		int next = (s<<1)&mask;
		
		if (!used[next]) {
			buf[i] = next;
		} else {
			buf[i] = next+1;
		}
		
		s = buf[i];
		used[buf[i]] = true;
		i++;
		
	}
	
	#ifdef _DEBUG
	printf("buf:\n");
	for (int i=0; i<(1<<n); ++i) {
		printf("%d\n", buf[i]);
	}
	#endif

}

void build() {
	for (int i=1; i<=15; ++i) {
		fill(i, gbuf[i], gused[i]);
	}
}

int main() {
	build();
	
	int N, K;
	while (scanf("%d %d", &N, &K) && N) {
		printf("%d\n", gbuf[N][K]);
	}
	
	return 0;
}