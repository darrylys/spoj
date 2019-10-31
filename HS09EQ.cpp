#include <stdio.h>
#include <math.h>

#define ll long long

int main() {
	int T, N;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		
		ll sum = 0;
		for (int d=0; ; ++d) {
			ll d4 = (ll)d*d*d*d;
			if (d4 <= N) {
				
				for (int c=0; ; ++c) {
					ll c3 = (ll)c*c*c;
					
					if (c3 <= N - d4) {
						sum += (int)sqrt(N - d4 - c3) + 1;
					} else {
						break;
					}
				}
			} else {
				break;
			}
		}
		
		printf("%lld\n", sum);
	}
}
