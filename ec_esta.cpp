#include<stdio.h>
#include<queue>

int main() {
	int T, N, a;
	scanf("%d", &T);
	while(T--){
		std::priority_queue<int, std::vector<int>, std::greater<int> > L2;
		std::priority_queue<int> L1;
		
		scanf("%d", &N);
		for (int i=0; i<N; ++i) {
			scanf("%d", &a);
			
			// inserting
			if (L1.empty() && L2.empty()) {
				L2.push(a);
				
			} else {
				int minL2 = L2.top();
				if (a < minL2) {
					L1.push(a);
				} else {
					L2.push(a);
				}
				
			}
			
			// rebalance
			if (L1.size() > L2.size()) {
				int maxL1 = L1.top();
				L1.pop();
				L2.push(maxL1);
				
			} else if (L2.size() > L1.size()+1) {
				int minL2 = L2.top();
				L2.pop();
				L1.push(minL2);
			}
			
			// print output
			if (L1.size() == L2.size()) {
				int maxL1 = L1.top();
				int minL2 = L2.top();
				
				unsigned int sum = (unsigned int)maxL1+minL2;
				printf("%d%s", sum>>1, (sum&1) ? ".5\n" : "\n");
				
			} else {
				int minL2 = L2.top();
				printf("%d\n", minL2);
			}
			
		}
		
	}
}




