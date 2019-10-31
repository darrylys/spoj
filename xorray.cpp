// AC 0.40s 3.1M SPOJ
// See VECTAR1 for algo analysis

#include <cstdio>
#include <cmath>
#include <algorithm>

#define ll long long
//#define _DEBUG

const int MAXV = 100005;
const int MAXL = 100;

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

int getLargest2en(int X) {
	
	ll last=0;
	for (ll i=1; i<=X; i<<=1) {
		last=i;
	}
	
	return (int)last;
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
	int T, N, M, oN, oM, P;
	int ncols;
	int nrows;
	int cellCol, cellRow, nNodePos;
	
	scanf("%d %d", &T, &P);
	buildFac(MAXV, P);
	
	while (T--) {
		scanf("%d%d", &N, &M);
		//N++; M++; 
		oN=N; oM=M;
		
		cellCol = cellRow = 0;
		nNodePos = 0;
		
		// LOOP is OK
		while (M>0 && N>0) {
			ncols = std::max(M, N);
			nrows = std::min(M, N);
			
			int start = cellCol ^ cellRow;
			
			// reduce ncols with the largest possible 2^n
			int boxw = getLargest2en(ncols);
			
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
		
		std::sort(node, node+nNodePos, compNode);
		
		#ifdef _DEBUG
		printf("sorted node locations\n");
		for (int i=0; i<nNodePos; ++i) {
			printf("NODE %d %s %d\n", node[i].tn, (node[i].isBegin ? "[" : ")"), node[i].val);
		}
		#endif
		
		ll sum=getSum(nNodePos, P);
		
		printf("%lld\n", sum);
	}
}

