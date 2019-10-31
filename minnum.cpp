#include <stdio.h>
#include <string.h>

#define ll long long

int main() {
	char in[35];
	ll S = 100000000000000000LL;
	
	while (1) {
		scanf("%s", in);
		if (in[0] == '-' && in[1] == '1') {
			break;
		}
		
		int len = strlen(in);
		ll x=0, y=0, s=1;
		
		for (int i=0; len-i-1 >= 0 && i<17; ++i) {
			y = y + s * (in[len-i-1]-'0');
			s *= 10;
		}
		
		s=1;
		for (int i=17; len-i-1 >= 0; ++i) {
			x = x + s * (in[len-i-1]-'0');
			s *= 10;
		}
		
		///printf("[x=%lld y=%017lld]\n", x, y);
		
		if (x < 9) {
			ll fn = (x * S + y);
			ll dv = fn/9;
			ll md = fn%9;
			
			printf("%lld\n", dv + (md != 0));
			
		} else {
			ll r1 = x / 9;
			ll m1 = x % 9;
			
			ll sx = (m1 * S + y);
			ll r2 = sx / 9;
			ll m2 = sx % 9;
			
			if (m2 != 0) {
				r2++;
				if (r2 >= S) {
					r1 += r2/S;
					r2 %= S;
				}
			}
			
			printf("%lld%017lld\n", r1, r2);
			
		}
		
		
	}
}

