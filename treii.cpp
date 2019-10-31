/*

This problem is easy, why there are so little solvers (as of submitting this, 9 solvers)
basically, uses DP
since every node in a same level must have same direct children, applied to the whole tree
creates a tree where each child of a node must consist of exact same subtree recursively

lets say root has n children.
each subtree must be exactly the same. just copy pasted.

formula:

f(N) = \sigma d | (N-1) f((N-1)/d)
1 <= N <= 1000

just precompute everything.

*/

#include <stdio.h>

#define MOD (1000000007)
#define MAXN (1001)

int f[MAXN];

int main() {
	
	f[1] = 1;
	for (int i=2; i<MAXN; ++i) {
		
		f[i] = 0;
		
		int N = i-1;
		for (int j=1; j*j<=N; ++j) {
			
			if (N%j == 0) {
				
				int le = j;
				int gt = N/j;
				
				f[i] += f[le];
				f[i] %= MOD;
				
				if (le != gt) {
					f[i] += f[gt];
					f[i] %= MOD;
					
				}
			}
			
		}
	}
	
	int N, c=1;
	while (scanf("%d", &N) != EOF) {
		printf("Case %d: %d\n", c++, f[N]);
	}
	
	return 0;
}
