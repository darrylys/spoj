#include <stdio.h>
#include <algorithm>

#define ll long long
#define MAXN 100004

using namespace std;

ll a[MAXN];

int main() {
	int N;
	
	scanf("%d", &N);
	for (int i=0; i<N; ++i) {
		scanf("%lld", &a[i]);
	}
	
	if (N == 1) {
		printf("0 0\n");
		return 0;
	}
	
	sort(a, a+N);
	
	if (a[0] == a[N-1]) {
		// all numbers are the same
		ll nz = ((ll)N*(N-1)) / 2;
		printf("%lld %lld\n", nz, nz);
		return 0;
	}
	
	// sentinel
	a[N] = 1LL<<62;
	
	// find min
	
	int pariz = 0; // equal elements when minsofar = 0
	ll mincount = 0;
	ll minsofar = 1LL<<62;
	
	//for (int i=0; i<=N; ++i) {
	//	printf("%lld ", a[i]);
	//}
	//putchar('\n');
	
	for (int i=1; i<=N; ++i) {
		
		if (minsofar == 0) {
			if (a[i] == a[i-1]) {
				pariz++;
			} else {
				mincount += ((ll)pariz)*(pariz-1)/2;
				pariz = 1;
			}
			
		} else {
			
			if (a[i]-a[i-1] < minsofar) {
				mincount = 1;
				minsofar = a[i]-a[i-1];
				
				if (minsofar == 0) {
					pariz = 2;
					mincount = 0;
				}
				
			} else if (a[i]-a[i-1] == minsofar) {
				mincount++;
				
			}
		}
	}
	
	printf("%lld ", mincount);
	
	// find max
	int smlcount = 1;
	for (int i=1; i<N && a[i] == a[0]; ++i) {
		smlcount++;
	}
	
	int bigcount = 1;
	for (int i=N-2; i>=0 && a[i] == a[N-1]; --i) {
		bigcount++;
	}
	
	printf("%lld\n", (ll)smlcount * bigcount);
	
}