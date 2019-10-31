#include <stdio.h>

#define ll unsigned long long

typedef struct _PAIR {
	ll val;
	ll idx;
} PAIR;

PAIR arr[200];

int build(ll _a, ll _b) {
	
	ll a = _a;
	ll b = _b;
	ll n;
	ll mid;
	ll d = 0;
	ll sidx = 0;
	int i=0;
	
	while (b) {
		arr[i].val = a;
		arr[i].idx = sidx;
		
		n = a/b;
		if (n&1) {
			mid = a-(n-1)*b;
		} else {
			mid = a%b;
		}
		
		d = (n/2)*3;
		sidx = sidx + d + 1;
		a = b;
		if (mid >= b) {
			b = mid - b;
		} else {
			b = b - mid;
		}
		i++;
	}
	
	arr[i].val = a;
	arr[i].idx = sidx;
	
	return ++i;
}

int main() {
	ll A, B;
	scanf("%llu %llu", &A, &B);
	int len = build(A, B);
	arr[len].val = 0;
	arr[len].idx = arr[len-1].idx+1;
	//int len = build(281, 269);
	/*
	for (int i=0; i<=len; ++i) {
		printf("%llu %llu\n", arr[i].val, arr[i].idx);
	}
	*/
	int Q;
	int u,v,c;
	ll vq;
	bool found;
	ll res;
	scanf("%d", &Q);
	int fidx;
	while (Q--) {
		scanf("%llu", &vq);
		
		//vq++;
		
		u=0;
		v=len;
		found = false;
		while (1) {
			if (u>=v) {
				fidx = u-1;
				break;
			} else {
				c = (u+v)/2;
				if (vq > arr[c].idx) {
					u=c+1;
				} else if (vq < arr[c].idx) {
					v=c;
				} else {
					found = true;
					res = arr[c].val;
					break;
				}
			}
		}
		
		if (found) {
			printf("%llu\n", res);
			continue;
		}
		
		
		// normal case
		ll n = vq - arr[fidx].idx;
		ll ta, tb;
		
		//printf("n=%llu, vq=%llu, fidx=%d, arr[fidx].idx=%llu\n", n, vq, fidx, arr[fidx].idx);
		
		ta = arr[fidx].val;
		tb = arr[fidx+1].val;
		
		//printf("ta=%llu, tb=%llu\n", ta, tb);
		
		if (n == 1) {
			printf("%llu\n", tb);
			continue;
		}
		
		n--;
		
		if (n%3) {
			ll tx = (n/3)*2 + (n%3);
			
			//printf("tx=%llu\n", tx);
			
			printf("%llu\n", ta - tx*tb);
		} else {
			printf("%llu\n", tb);
		}
		
	}
	return 0;
}
