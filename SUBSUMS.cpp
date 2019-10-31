#include<stdio.h>
#include<algorithm>

using namespace std;

int outer[(1<<17)+10]; //sml
int inner[(1<<17)+10]; //bigg
int data[40];

int build(int a, int b, int* sa, int* da) { //OK
	int str, c;
	for (int i=0; i<(1<<(b-a)); ++i) {
		
		str = i;
		sa[i] = 0;
		for (int j=b-1; j>=a; --j) {
			c = str&1;
			
			if (c) {
				sa[i] += da[j];
			}
			
			str >>= 1;
		}
	}
	
	return (1<<(b-a));
}

void print_binary(int x) {
	if (x > 0) {
		print_binary(x>>1);
		putchar((x&1)+'0');
	}
}

int bsearch_largest(int* arr, int a, int b, int key) {	//returns the index
	int u=a, v=b, c;
	
	while (u<v) {
		c = (u+v)/2;
		
		if (arr[c] > key) {
			v = c;
		} else {
			u = c+1;
		}
	}
	
	return u;
}

int bsearch_smallest(int* arr, int a, int b, int key) {	//returns the index
	int u=a, v=b, c;
	
	while (u<v) {
		c = (u+v)/2;
		
		if (arr[c] < key) {
			u = c+1;
		} else {
			v = c;
		}
	}
	
	return u;
}

int main() {
	int n, a, b;
	long long int sum = 0;
	
	scanf("%d %d %d", &n, &a, &b);
	
	for (int i=0; i<n; ++i) {
		scanf("%d", &data[i]);
	}
	
	int outerlen = build(0, n/2, outer, data);
	int innerlen = build(n/2, n, inner, data);
	
	/*
	for (int i=0; i<innerlen; ++i) {
		print_binary(i);
		printf(" : %d\n", inner[i]);
	}
	*/
	sort(inner, inner+innerlen);
	
	
	for (int i=0; i<outerlen; ++i) {
		sum += bsearch_largest(inner, 0, innerlen, b-outer[i]) - 
			bsearch_smallest(inner, 0, innerlen, a-outer[i]);
	}
	
	printf("%lld\n", sum);
	return 0;
}