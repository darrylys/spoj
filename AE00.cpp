#include<cstdio>

int main() {
	int a;
	scanf("%d",&a);
	int res = 0;
	for (int i=1; i*i <= a; i++) {
		res += (1 + (a - i*i)/i);
	}
	printf("%d\n", res);
}