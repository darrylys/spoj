/*
AC 0.00s 2.6M SPOJ
algo: math
let A = pa1*pa2*..*pan
let B = pb1*pb2*..*pbn
case 1: gcd(A,B) = 1
	gcd(A+B, lcm(A,B))
	lcm(A,B)=pa1*pa2*...*pan*pb1*pb2*...*pbn
	A+B has no shared primes that are within set A U B from lcm(A,B) above
	assume that A+B = pa1 * K, thus (A+B) mod pa1 = 0; however,
	(A+B) mod pa1 is not 0 because B mod pa1 is not 0 which is a contradiction that A+B is pa1*(X)
	thus, the result will be relatively prime for this case
case 2: gcd(A,B)>1
	take out gcd(A,B) from both of them and the analysis is reduced to case 1.
	the result will be gcd(A,B)
	
be careful of unnecessary zeros, i.e. trailing zeros to the right.
for example: 
	0100000 should be printed 01.
	0100001 should be printed 0100001.

*/

#include <cstdio>
#include <cstring>
#include <algorithm>
int main() {
	int T;
	scanf("%d", &T);
	char A[1002], B[1002], R[1002];
	while (T--) {
		scanf("%s%s", A, B);
		int m = std::min(strlen(A), strlen(B));
		int nz=0;
		for (int i=0; i<m; ++i) {
			R[i]=((A[i]-'0')&(B[i]-'0'))+'0';
			if (R[i] == '1') nz = i+1;
		}
		R[nz]='\0';
		if (nz) printf("%s\n", R);
		else printf("relatively prime\n");
	}
	return 0;
}
