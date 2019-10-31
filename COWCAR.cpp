#include<stdio.h>
#include<algorithm>

#define MAXN 50010

using namespace std;

int lane[MAXN];
int S[MAXN];

int separate(int n, int m, int d, int l) {
	sort(S, S+n);
	
	int currentlane = 0, ms;
	int sum = 0;
	
	for (int i=0; i<n; ++i) {
		
		ms = (S[i] - d*lane[currentlane] < 0)? 0:S[i] - d*lane[currentlane];
		if (ms >= l) {
			++lane[currentlane];
			++sum;
		}
		
		++currentlane;
		currentlane %= m;
	}
	
	return sum;
}

int main() {
	int n, m, d, l;
	
	scanf("%d %d %d %d", &n, &m, &d, &l);
	
	for (int i=0; i<n; ++i) scanf("%d", &S[i]);
	printf("%d\n", separate(n,m,d,l));
	return 0;
}