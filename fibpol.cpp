#include <stdio.h>

#define ll long long
#define T9 (1000000000)
#define T18 (1000000000000000000LL)

ll fib[50];
ll fib2[50];

int main() {
	fib[0] = 0;
	fib[1] = 1;
	
	int len1=0;
	for (int i=2; ; ++i) {
		fib[i] = fib[i-1] + fib[i-2];
		
		len1=i;
		if (fib[i] > T9) break;
	}
	
	//for (int i=0; i<=len1; ++i) {
	//	printf("%lld ", fib[i]);
	//}
	//putchar('\n');
	
	int len2=0;
	for (int i=0; i <= len1; i+=2) {
		fib2[i>>1] = fib[i] * fib[i+1];
		
		len2 = i>>1;
	}
	//for (int i=0; i<=len2; ++i) {
	//	printf("%lld ", fib2[i]);
	//}
	//putchar('\n');
	
	
	
	int T; ll A;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &A);
		
		int u=0, v=len2+1, c;
		while (1) {
			if (u >= v) {
				printf("0\n");
				break;
			}
			
			c=(u+v)/2;
			if (fib2[c] > A) {
				v=c;
			} else if (fib2[c] < A) {
				u=c+1;
			} else {
				printf("1\n");
				break;
			}
			
		}
		
	}
	
}
