/*
AC, 1.92s 4.3M SPOJ unoptimized

algo:
Since there are no update operations, the queries can be rearranged as much as we like.
This algo uses a minor modification to MO's algorithm
See here: https://blog.anudeep2011.com/mos-algorithm/
and fenwick tree (BIT), code copied from: https://www.topcoder.com/community/data-science/data-science-tutorials/binary-indexed-trees/

the main algorithm is still MO, but the only difference is using BIT in its add and remove operations
whenever adding a new number to BIT, we need to find the following: 
the total number <= new number - K and 
total number >= new number + K.
These numbers have absolute difference to the new number >= K.

just keep an array maintaining the tally count of each number.
and make it a BIT.

BIT can easily implement the operations in lg(max(A))

by MO algorithm analysis, time complexity O((N+M) sqrt(N) lg(max(A)))

*/

#include <cstdio>
#include <cmath>
#include <algorithm>

#define ll long long
//#define _DEBUG
//#define _TIMED

#ifdef _TIMED
#include <time.h>
#endif

using namespace std;

typedef struct _P {
	int L, R;
	int bn;
	int qn;
} PII;

const int MAXV = 100010;
const int MAXL = 50010;

PII query[MAXL];

// fenwick tree //start from 1
int f3[MAXV];
int arr[MAXL];
ll qans[MAXL];

bool comp(const PII& a, const PII& b) {
	if (a.bn != b.bn) {
		return a.bn < b.bn;
	}
	return (a.R < b.R);
}

void update(int idx, int val, int maxVal){
    while (idx <= maxVal){
        f3[idx] += val;
        idx += (idx & -idx);
    }
}

int read(int idx){
    int sum = 0;
    while (idx > 0){
        sum += f3[idx];
        idx -= (idx & -idx);
    }
    return sum;
}

int main() {
	#ifdef _TIMED
	clock_t START = clock();
	#endif
	
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	
	int maxVal = -1;
	int minVal = 200000;
	for (int i=0; i<N; ++i) {
		scanf("%d", &arr[i]);
		if (arr[i] > maxVal) {
			maxVal = arr[i];
		}
		if (arr[i] < minVal) {
			minVal = arr[i];
		}
	}
	
	#ifdef _DEBUG
	printf("N=%d, M=%d, K=%d\n", N, M, K);
	printf("maxVal=%d, minVal=%d\n", maxVal, minVal);
	#endif
	
	if (K > maxVal - minVal) {
		while (M--) {
			printf("0\n");
		}
		return 0;
	}
	
	int sqrv = sqrt(N);
	
	#ifdef _DEBUG
	printf("sqrv=%d\n", sqrv);
	#endif
	
	for (int i=0, l, r; i<M; ++i) {
		scanf("%d %d", &l, &r);
		
		query[i].qn = i;
		query[i].L = l-1;
		query[i].R = r-1;
		query[i].bn = query[i].L / sqrv;
	}
	
	sort(query, query + M, comp);
	
	#ifdef _DEBUG
	printf("sorted query: \n");
	for (int i=0; i<M; ++i) {
		printf("{ qn=%d, L=%d, R=%d, bn=%d }\n", query[i].qn, query[i].L, query[i].R, query[i].bn);
	}
	#endif
	
	ll ans = 0;
	int tn = 0;
	int lp = 0;
	int rp = -1;
	
	for (int i=0; i<M; ++i) {
		
		int L = query[i].L;
		int R = query[i].R;
		
		#ifdef _DEBUG
		printf("Query: {%d %d}\n", query[i].L, query[i].R);
		#endif
		
		while (rp < R) {
			rp++;
			
			ans += read(max(0, arr[rp]-K));
			ans -= read(min(maxVal, arr[rp]+K-1));
			ans += tn;
			
			update(arr[rp], 1, maxVal);
			tn++;
		}
		
		while (rp > R) {
			update(arr[rp], -1, maxVal);
			tn--;
			
			ans -= read(max(0, arr[rp]-K));
			ans += read(min(maxVal, arr[rp]+K-1));
			ans -= tn;
			
			rp--;
		}
		
		while (lp < L) {
			update(arr[lp], -1, maxVal);
			tn--;
			
			ans -= read(max(0, arr[lp]-K));
			ans += read(min(maxVal, arr[lp]+K-1));
			ans -= tn;
			
			lp++;
		}
		
		while (lp > L) {
			lp--;
			
			ans += read(max(0, arr[lp]-K));
			ans -= read(min(maxVal, arr[lp]+K-1));
			ans += tn;
			
			update(arr[lp], 1, maxVal);
			tn++;
		}
		
		//printf("%lld\n", ans);
		qans[query[i].qn] = ans;
		
	}
	
	for (int i=0; i<M; ++i) {
		printf("%lld\n", qans[i]);
	}
	
	
	#ifdef _TIMED
	double T_ELAPSED = (double)(clock() - START) / CLOCKS_PER_SEC;
	fprintf(stderr, "%lf\n", T_ELAPSED);
	#endif
}
