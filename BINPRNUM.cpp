/*
AC 0.05s 2.7M SPOJ

let
	f(n, 0) = binary protean number length n which starts at 0. e.g. 000, 010, 001, 01001, ...
	f(n, 1) = binary protean number length n which starts at 1. e.g. 100, 1010, 1001, 10, 1, ...

thus, we can construct the recurrence relation as follows
f(n,0) = f(n-1,1) + f(n-1,0)
f(n,1) = f(n-1,0)

f(1,0) = 1
f(1,1) = 1

which is simply basic fibonacci sequence with f(0) = 1 and f(1) = 1.

K'th protean binary is the sum of i'th fibonacci sequence where (len-i)'th digit of L is 1.
assuming that the L is indexed this way:
          1   ...
01234567890123...
dddddddddddddd...
which is basically normal way to index strings.

e.g.
pos=0123
num=1010 is 7th by:
	fib(4-0) + fib(4-2) = 5 + 2 = 7

*/

#include <stdio.h>
#include <string.h>

#define ll long long
#define MAXL (91)

ll fib[MAXL];
char L[MAXL+3];

int main() {
	fib[0] = 1;
	fib[1] = 1;
	for (int i=2; i<MAXL; ++i) {
		fib[i]=fib[i-1]+fib[i-2];
	}
	int T,c=1;
	scanf("%d", &T);
	while (T--) {
		int len = strlen(L);
		ll sum=0;
		for (int i=0; i<len; ++i) {
			if (L[i] == '1') {
				sum += fib[len-i];
			}
		}
		printf("Case %d: %lld\n", c++, sum);
	}
}
