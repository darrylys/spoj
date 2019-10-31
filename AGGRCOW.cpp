#include<cstdio>
#include<algorithm>

using namespace std;

int stall[100005];

bool isfine(int diff, int stall_num, int req) {
	int prev = stall[0];
	
	int num = 1;
	for (int i=1; i<stall_num; i ++) {
		if (stall[i] - prev < diff) continue;
		prev = stall[i];
		num++;
	}
	
	return num>=req;
}

int main() {
	int test, n, c;
	scanf("%d", &test);
	while (test--) {
		scanf("%d %d", &n, &c);
		
		for (int i=0; i<n; i++) {
			scanf("%d", &stall[i]);
		}
		
		sort(stall, stall+n);
		int min = 1;
		int max = stall[n-1];
		int mid;
		while (max > min) {
			mid = min + (max-min+1)/2;
			if (isfine(mid, n, c)) {
				min = mid;
			} else {
				max = mid-1;
			}
		}
		
		printf("%d\n", min);
	}
	return 0;
}