#include<stdio.h>

#define ll long long int

int getint() {
	int n=0; char c=getchar();
	while (c<'0' || c>'9') c=getchar();
	while (c>='0' && c<='9') {
		n = n*10 + c-'0';
		c=getchar();
	}
	return n;
}

int main() {
	ll sum=0;
	
	int n=getint();
	int a, b;
	
	a=getint();
	
	while (--n) {
		b=getint();
		
		sum += (a>b)?a:b;
		a=b;
	}
	printf("%lld\n", sum);
	return 0;
}