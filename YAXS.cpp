/*
AC, 0.08s 2.7M SPOJ

First WA issue, forget the Case label. DAMMIT!

ad-hoc

Since the problem is to maximize one number, we don't have to share a number to another

There are 3 groups:
group 1: 1      (A)
group 2: 2, 3   (b1, b2)
group 3: 4, 5   (c1, c2)

1 can xor to 2, 3, and 4, 5
but members of group 2 cannot xor to group 3 because the result > 5, and vice versa

2 xor 4 = 6
2 xor 5 = 7
3 xor 4 = 7
3 xor 5 = 6

From here, there can only be 3 possibilities to make a number maximum
That number must be one of the 3 groups.

Transform the array to tally array
A, b1, b2, c1, c2
A = number of 1
b1 = number of 2
b2 = number of 3
c1 = number of 4
c2 = number of 5

so:
1 1 1 3 3 4 4 4 4 4 is:
A = 3
b1 = 0
b2 = 2
c1 = 5
c2 = 0

To maximize group 1, xor all members of group 2, xor all members of group 3, add them to group 1
To maximize group 2, xor all possible members of group 3, add to group 1, and add to group 2
To maximize group 3, xor all possible members of group 2, add to group 1, and add to group 3

Find the max of all 3 methods.

Space: O(1)
Time: O(T * N)
*/

#include <stdio.h>
#include <string.h>

inline int MIN(int a, int b) {
	return a<b ? a:b;
}

inline int MAX(int a, int b) {
	return a>b ? a:b;
}

int main() {
	int T, N, A, v1, v2, v3, c=1;
	int a[6];
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		memset(a, 0, sizeof(a));
		for (int i=0; i<N; ++i) {
			int x;
			scanf("%d", &x);
			a[x]++;
		}

		//A += min(c1c2); ans = max(b1,b2) + min(A, b1, b2)
		A = a[1] + MIN(a[4], a[5]);
		v1 = MAX(a[2], a[3]) + MIN(A, MIN(a[2], a[3]));

		//A += min(b1b2); ans = max(c1c2)+min(A,c1,c2)
		A = a[1] + MIN(a[2], a[3]);
		v2 = MAX(a[4], a[5]) + MIN(A, MIN(a[4], a[5]));

		//A += min(c1c2)+min(b1b2)
		v3 = a[1] + MIN(a[2], a[3]) + MIN(a[4], a[5]);

		printf("Case %d: %d\n", c++, MAX(v1, MAX(v2, v3)));
	}

	return 0;
}
