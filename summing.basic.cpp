/*
running in this computer: 1.50s. too slow?
AC in spoj (0.11s, 232M)

algorithm:
find the Xth element of the series.
the position of element in form 3^x is (I found this by accident):
	f(x) = (\sigma i=0..x floor(i*log2(3))) + x
I found it!

basically, the number of elements SMALLER than 3^x can be enumerated using the following way:
3^0 * (1 + 2 + 2^2 + 2^3 + ... + 2^(floor(log2(3^x))))
3^1 * (1 + 2 + 2^2 + 2^3 + ... + 2^(floor(log2(3^(x-1)))))
...
3^(x-1) * (1 + 2)

the total number of terms of above enumeration is simply
1 + floor(x * log2(3)) +
1 + floor((x-1) * log2(3)) + 
...
1 + floor(1 * log2(3))
which is f(x).


after finding the position
we just have to enumerate all numbers between 3^x and 3^(x+1)
the total number will be around 2*sqrt(X) because growth rate of f(x) is about sqrt(X)/2

call c++ nth_element to find the number at Xth position

after the number is obtained, it is simple matter to find the total sum.

point of caution:
the complexity must be kept in O(C*sqrt(X)) where C is some constant.
don't use bigmod or whatever that is.
c++ nth_element is ON average, linear.

*/

#include <cstdio>
#include <cmath>
#include <algorithm>

using std::nth_element;

#define ll long long
//#define MAXN (10000003)
//#define _DEBUG

#ifdef _DEBUG
#include <time.h>
#endif

const int MAXN = 20000003;
const double LOG3 = log(3) / log(2);

typedef struct _N {
	int e2;
	int e3;
} EN;

//ll pos3[MAXN];
EN en[MAXN];
int exp3[MAXN];

bool comp2(const EN &a, const EN &b) {
	if (a.e2 == b.e2 && a.e3 == b.e3) {
		return false;
	}
	return (a.e2 + a.e3*LOG3) < (b.e2 + b.e3*LOG3);
}

int comp(const EN &a, const EN &b) {
	if (a.e2 == b.e2 && a.e3 == b.e3) {
		return 0;
	}
	if ((a.e2 + a.e3*LOG3) > (b.e2 + b.e3*LOG3)) {
		return 1;
	} else {
		return -1;
	}
}

int findPos3(ll X, int K, ll &pos3v) {
	
	ll sum = 0;
	
	int v3 = 1;
	for (int i=0; ; ++i) {
		
		int v = floor(i * LOG3);
		sum += v;
		//pos3[i] = sum + i;
		
		exp3[i] = v3;
		v3 = (3LL * v3)%K;
		
		//if (pos3[i] >= X) {
		if (sum+i >= X) {
			return i;
		} else {
			pos3v = sum+i;
		}
	}
}

int getNumbers(int maxSmallerE3) {
	
	EN low;
	low.e2 = 0;
	low.e3 = maxSmallerE3;
	
	EN high;
	high.e2 = 0;
	high.e3 = maxSmallerE3+1;
	
	EN temp;
	
	int e2 = 0;
	int e3 = maxSmallerE3;
	int cv;
	int i;
	
	for (i=0; e3 >= 0; ++i) {
		
		temp.e2 = e2;
		temp.e3 = e3;
		
		cv = comp(temp, high);
		
		if (cv < 0) {
			en[i].e2 = temp.e2;
			en[i].e3 = temp.e3;
			e2++;
			
		} else {
			// cv > 0 here. impossible for == high
			e3--;
			i--;
			
		}
		
	}
	
	return i;
}

int main() {
	#ifdef _DEBUG
	const clock_t begin_time = clock();
	#endif
	
	ll X;
	int K;
	
	scanf("%lld %d", &X, &K);
	
	ll pos3m1;
	int pos = findPos3(X, K, pos3m1);
	//int rank = (int)(X - pos3[pos-1]); // rank is 1-based.
	int rank = (int)(X - pos3m1);
	// rank=1 = 1st smallest, rank=2 = 2nd smallest, etc...
	
	#ifdef _DEBUG
	printf("lastPos=%d, rank=%d\n", pos, rank);
	#endif
	
	int n = getNumbers(pos-1);
	
	#ifdef _DEBUG
	printf("n=%d\n", n);
	//for (int i=0; i<n; ++i) {
	//	printf("val=2^%d * 3^%d = %lld\n", en[i].e2, en[i].e3, (ll)te2[en[i].e2] * te3[en[i].e3]);
	//}
	#endif
	
	// how to find the nth smallest in O(n)? 10^7 is too big, will TLE
	// idea, use c++ nth_element.
	// this works! yeah!
	nth_element(en, en+rank-1, en+n, comp2);
	
	#ifdef _DEBUG
	//printf("nth_element, found: 2^%d * 3^%d = %lld\n", en[rank-1].e2, en[rank-1].e3, (ll)te2[en[rank-1].e2] * te3[en[rank-1].e3]);
	printf("nth_element, found: 2^%d * 3^%d\n", en[rank-1].e2, en[rank-1].e3);
	#endif
	
	// enumerate the similar way to the getNumbers method
	// find the max 2exp.
	// X = en[rank-1], 2^x, x = floor(log2(X))
	// when exp 3 increments, the 2^x is divided by 2 until not passing X
	
	EN big2;
	big2.e2 = 0;
	big2.e3 = pos-1;
	
	int cv;
	int e2sumMod = 0;
	int e2expMod = 1;
	int sum = 0;
	
	#ifdef _DEBUG
	printf("start working on calculation\n");
	#endif
	
	for (int i=0; i<pos; ++i) {
		
		// add 2^x until reaches X
		
		while (1) {
			cv = comp(big2, en[rank-1]);
			if (cv <= 0) {
				e2sumMod += e2expMod;
				e2sumMod %= K;
				e2expMod = (e2expMod<<1)%K;
				big2.e2++;
			} else {
				break;
			}
		}
		
		//#ifdef _DEBUG
		//printf("3^%d, %d, e2sumMod=%d, e2expMod=%d\n", big2.e3, exp3[big2.e3], e2sumMod, e2expMod);
		//#endif
		
		sum += ((ll)exp3[big2.e3] * e2sumMod)%K;
		sum %= K;
		
		big2.e3--;
		
	}
	
	printf("%d\n", sum);
	
	#ifdef _DEBUG
	printf("%lf\n",  float( clock () - begin_time ) /  CLOCKS_PER_SEC);
	#endif
	
}
