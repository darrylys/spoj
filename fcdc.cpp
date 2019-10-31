#include <stdio.h>

#define ll long long

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	ll faca = 1, facb = 1;
	int fa;
	for (int i=1; i<=a; ++i) {
		faca = (faca * i) % a;
		facb = (facb * i) % b;
		if (faca == 0) {
			fa = i;
			break;
		}
	}
	int sum = /*faca == 0 && */facb != 0;
	for (int i=fa+1; i<b; ++i) {
		//faca = (faca * i) % a;
		facb = (facb * i) % b;
		sum += /*faca == 0 && */facb != 0;
	}
	printf("%d\n", sum);
}
