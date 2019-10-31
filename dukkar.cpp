/* math - Lucas Theorem on Combinatorial moduli Prime
  O(log(n)) per testcase */

#include <stdio.h>
#define ll long long
int main() {
	int T,P;ll N,sum;
	scanf("%d",&T);
	while(T--){
		scanf("%lld %d",&N,&P);
		sum=1;
		int div=0;
		ll xn=N;
		while(xn){
			div=xn%P;
			sum*=(div+1);
			xn/=P;
		}
		printf("%lld\n", N+1-sum);
	}
}
