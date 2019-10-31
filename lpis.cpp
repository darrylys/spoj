#include <stdio.h>

#define MAXN (1000002)
#define MAXA (100000)

int maxl[MAXN];
int arr[MAXA];

int max(int a, int b) {
	return a>b ? a:b;
}

int find(int N) {
	for (int i=0; i<N; ++i) {
		maxl[arr[i]] = max(maxl[arr[i]], max(1, maxl[arr[i]-1]+1));
	}
	int rx = 1;
	for (int i=1; i<MAXN; ++i) {
		rx = max(rx, maxl[i]);
	}
	return rx;
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i=0; i<N; ++i) {
		scanf("%d", &arr[i]);
	}
	printf("%d\n", find(N));
}
