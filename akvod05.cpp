/*
AC 0.27s 4.0M SPOJ
algo: ad-hoc, data structure

try to do this on paper and a pattern should be evident
the output will go to a pattern of length K+1
assume that the first K numbers are
0 1 2 3 4 5 6 .. K. The next number will be K+1 and K+2nd number is 0

more generally, assume a set of k+1 numbers, a0, a1, a2, .. , ak
a1 a2 a3 ... ak-1, the next number is ak.
the next number evaluation will not account a1 so the next number will be a1.
and next = a2, and so on... The pattern repeats like this.

the pattern will be enumerated manually.
use priority_queue C++ STL to maintain list of unused number sorted ASC
use array count to maintain the number of ax in original list.
whenever a number ax is out of scope, reduce the count number.
when the count reaches zero, that means, ax may appear in the future. 
So, insert it to the priority_queue.

time complexity: O(K lg K)
space complexity: O(K)

*/

#include<stdio.h>
#include<string.h>
#include<queue>

using namespace std;

int arr[100010];
int loop[100010];
int count[100010];

int main() {
	std::priority_queue<int, std::vector<int>, std::greater<int> > smlq;
	
	int T, N, K;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &K);
		memset(count, 0, (K+1)*sizeof(count[0]));
		
		for (int i=0; i<K; ++i) {
			scanf("%d", &arr[i]);
			if (arr[i] <= K) {
				count[arr[i]]++;
			}
		}
		
		for (int i=0; i<=K; ++i) {
			if (count[i] == 0) {
				smlq.push(i);
			}
		}
		
		for (int i=0; i<=K; ++i) {
			loop[i] = smlq.top();
			//printf("loop[%d]=%d\n", i, loop[i]);
			
			smlq.pop();
			
			if (arr[i] <= K) {
				if (count[arr[i]] == 1) {
					smlq.push(arr[i]);
				}
				count[arr[i]]--;
			}
			
		}
		
		printf("%d\n", loop[N%(K+1)]);
		while (!smlq.empty()) smlq.pop();
		
	}
	
}



