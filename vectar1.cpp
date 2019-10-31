// AC 0.00 in SPOJ, 2.6M, rank 1. really?

/*
Complexity: O(T * log(M+N) * log(log(M+N)))

Observations:
1. XOR just permutes the values in one row
2. the XOR matrix is symmetric
3. if exists a box with size 2^n*2^n, the values in one row is closed (See Ring definition for open / closed)
	all rows have in that box have same values, just permuted.
4. a box of size 2^n can be constructed to a box with size 2^2n with the following method
	let X <- that box
	a new box of size 2^2n can be constructed as follows:
		X Y
		Y X
	where Y = X with all of its values + 2^n.
	
	for example, 
	
	X = |0 1|
		|1 0|
	Y = |2 3| (all elements in X added by 2)
		|3 2|
	a new box can be constructed as follows:
	(X) [Y] = |(0 1) [2 3]|
	[Y] (X)   |(1 0) [3 2]|
			  |[2 3] (0 1)|
			  |[3 2] (1 0)|

To solve the problem, we need another observation:
from the problem statement, it is clear that if i^j > k^l; then A[i,j] > A[k,l]
then, we know for sure that the largest value must be placed in largest xor value.
if it's not, then by pigeonhole principle, the smaller ones must be placed in larger xor value, violating the rule.
From here, we can guess that the matrix configuration would be like this:
xor = 0, n1 smallest values here
xor = 1, next n2 smallest values here
....
xor = largest, last nx smalest values here

since all numbers are distinct and we have no defined relationship for numbers with the same xor, they can be permuted freely
therefore, the total number of matrix configuration is simply
n1! * n2! * n3! * ... * nx!

the algorithm will be:
find how many cells with xor = 0, find its factorial
find how many cells with xor = 1, find its factorial
find how many cells with xor = 2, find its factorial
...
find how many cells with xor = last, find its factorial
multiply them all.

This gives very simple algorithm in log(M+N), sketched as follows:
we just have to find the largest box size 2^n in MxN. Since the values within one row of this box is closed, all rows contain same numbers. Just permuted.
if the box does not fit, keep the width (2^n) and increment all numbers in [a,b) by the height
else, duplicate the box to the down and the right. increment all numbers in [a+2^n, b+2^n) by (height-2^n + ncols-2^n)
process the remaining space the same way.

we can use segment tree for range updates provided the maximum xor value is not big (1023) but it's kinda overkill.
there is a maximum of O(log(N+M)) segment tree operations.
And we only need to find the values once, at the ending.
So, it's overkill. You can use segment tree with coordinate compression probably but I don't know how to use it now.
Dynamic segment tree should be used but still overkill.

instead, why not just compute the ranges the same way we solved POSTERS in SPOJ?
sort the ranges from left to right and incrementally add the values by sweeping the ranges from left to right.
Since there are only maximum O(log(M+N)) ranges, sorting is just O(log(M+N) log(log(M+N))).
and only required O(log(M+N)) space.

*/


#include <cstdio>
#include <cmath>
#include <algorithm>

#define ll long long
//#define _DEBUG

const int MAXD = 1001;
const int MAXV = 1<<10;
const int MAXL = 100;
const int MOD = 1000000007;

int n2e[MAXV];
int fac[MAXV];

typedef struct _N {
	int tn;
	bool isBegin;
	int val;
} NODE;

NODE node[MAXL];

bool compNode(const NODE& a, const NODE& b) {
	if (a.tn == b.tn) {
		return (!a.isBegin ? true : b.isBegin);
	}
	return a.tn < b.tn;
}

// bigmod func. 0^0 = 1
ll bigmod(int base, int exp, int mod) {
	if (exp == 0 || base == 1) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	half = (half*half)%mod;
	if (exp&1) {
		half = (half*base)%mod;
	}
	return half;
}

// factorial precompute func
void buildFac(int maxf, int mod) {
	fac[0] = 1;
	for (int i=1; i<maxf; ++i) {
		fac[i] = (int)(((ll)fac[i-1] * i)%mod);
	}
}

// VECTAR1 only. for XORRAY, replace this with bit manip, floor(log2(X)) or find manually 2^x
// OK
void build2e() {
	n2e[0]=0;
	int s=1;
	
	for (int i=1; i<MAXV; ++i) {
		if ((s<<1) <= i) {
			s <<= 1;
		}
		n2e[i] = s;
	}
}

void add(int tn, bool isBegin, int v, int pos) {
	node[pos].tn = tn;
	node[pos].isBegin = isBegin;
	node[pos].val = v;
}

// seems OK.
ll getSum(int nNodePos, int mod) {
	
	#ifdef _DEBUG
	printf("getSum(%d, %d)\n", nNodePos, mod);
	#endif
	
	int val=0;
	int T=0;
	
	int tlen, tval;
	ll sum=1;
	
	for (int i=0; i<nNodePos; ++i) {
		
		tlen = node[i].tn - T;
		
		#ifdef _DEBUG
		printf("analyze: fac[%d]^%d\n", val, tlen);
		#endif
		
		if (val > 1 && tlen) {
			sum = (sum * bigmod(fac[val], tlen, mod))%mod;
		}
		
		T = node[i].tn;
		if (node[i].isBegin) {
			val += node[i].val;
		} else {
			val -= node[i].val;
		}
	}
	
	return sum;
}

int main() {
	build2e();
	buildFac(MAXV, MOD);
	
	int T, N, M, oN, oM;
	int ncols;
	int nrows;
	int cellCol, cellRow, nNodePos;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &M);
		N++; M++; oN=N; oM=M;
		
		cellCol = cellRow = 0;
		nNodePos = 0;
		
		// LOOP is OK
		while (M>0 && N>0) {
			ncols = std::max(M, N);
			nrows = std::min(M, N);
			
			int start = cellCol ^ cellRow;
			
			// reduce ncols with the largest possible 2^n
			int boxw = n2e[ncols];
			
			#ifdef _DEBUG
			printf("ncols=%d, nrows=%d, cellCol=%d, cellRow=%d, startAt=%d, boxw=%d\n", 
				ncols, nrows, cellCol, cellRow, start, boxw);
			#endif
			
			
			// check if full block is possible
			if (boxw <= nrows) {
				
				// if possible, duplicate block to the right and down
				
				// add box
				add(start, true, boxw, nNodePos++);
				add(start+boxw, false, boxw, nNodePos++);
				#ifdef _DEBUG
				printf("add range [%d, %d) val %d\n", start, start+boxw, boxw);
				#endif
				
				
				// right and down
				int remRight = ncols - boxw;
				int remDown = nrows - boxw;
				//add(1, 0, max2e, start+boxw, start+2*boxw, remRight+remDown);
				add(start+boxw, true, remRight+remDown, nNodePos++);
				add(start+2*boxw, false, remRight+remDown, nNodePos++);
				#ifdef _DEBUG
				printf("remRight=%d, remDown=%d\n", remRight, remDown);
				printf("add range [%d, %d) val %d\n", start+boxw, start+2*boxw, remRight+remDown);
				#endif
				
				// update position and remaining blocks
				cellCol += boxw;
				cellRow += boxw;
				N = ncols - boxw;
				M = nrows - boxw;
				
			} else {
				
				// add to segment tree
				//add(1, 0, max2e, start, start+boxw, nrows);
				add(start, true, nrows, nNodePos++);
				add(start+boxw, false, nrows, nNodePos++);
				#ifdef _DEBUG
				printf("add range [%d, %d) val %d\n", start, start+boxw, nrows);
				#endif
				
				// update position and remaining blocks
				cellCol += boxw;
				N = ncols - boxw;
				M = nrows;
				
			}
			
			
		}
		
		// VECTAR1 only, decrement 0 by 1, [1-M] 1x and [1-N] 1x;
		// [0,M] -1
		add(0, true, -1, nNodePos++);
		add(oM, false, -1, nNodePos++);
		
		// [1,N] -1
		add(1, true, -1, nNodePos++);
		add(oN, false, -1, nNodePos++);
		
		std::sort(node, node+nNodePos, compNode);
		
		#ifdef _DEBUG
		printf("sorted node locations\n");
		for (int i=0; i<nNodePos; ++i) {
			printf("NODE %d %s %d\n", node[i].tn, (node[i].isBegin ? "[" : ")"), node[i].val);
		}
		#endif
		
		ll sum=getSum(nNodePos, MOD);
		
		printf("%lld\n", sum);
	}
}

