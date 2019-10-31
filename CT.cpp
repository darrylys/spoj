/*
AC 0.0s 2.6M SPOJ

algo:

this algo is not optimized at all. Heck, it is not even meant to be submitted at all.
Actually meant for brute force algorithm to confirm the formula

the algo is divided to 3 phases
1. handle kxk sized boxes with each has 4 triangle variants
	|\
	|_\ type
	
2. handle 2kxk sized boxes
	 /\
	/__\ type. two triangles from case 1) glued together

3. nasty part, handling misc oriented boxes

after analyzing enough, it can be seen that some triangles are confined in a single box
boxes that need attention are kxk boxes, 2kxk boxes and misc boxes
these box sizes are chosen in a way that the triangle formed must use the box entirely.
basically, the dimension of the box is the minimum size that can hold said triangle entirely.

the algo simply enumerate all possible boxes.

complexity: O(WH), slow algorithm
*/

#include <stdio.h>

#define ll long long

int main() {
	int T;
	scanf("%d", &T);
	
	while (T--) {
		int W, H;
		scanf("%d %d", &W, &H);
		
		ll sum=0;
		
		ll tsum = 0;
		for (int i=0; i<W && i<H; ++i) {
			tsum += (W-i)*(H-i);
		}
		sum += 4*tsum;
		
		tsum = 0;
		for (int i=0; i<W && 2*i+1<H; ++i) {
			tsum += (W-i)*(H-2*i-1);
		}
		sum += 2*tsum;
		
		tsum = 0;
		for (int i=0; i<H && 2*i+1<W; ++i) {
			tsum += (H-i)*(W-2*i-1);
		}
		sum += 2*tsum;
		
		printf("sum after 1x1 boxes = %d\n", sum);
		
		tsum = 0;
		for (int w=1; w<=W; ++w) {
			for (int h=w+1; h<=H; ++h) {
				
				int f1 = 0;
				if (W-w-h+1 > 0 && H-h+1 > 0) {
					printf("%d\t%d\n", (W-w-h+1), (H-h+1));
					
					f1 = (W-w-h+1)*(H-h+1);
				}
				
				tsum += f1;
			}
		}
		printf("W,H switched\n");
		for (int w=1; w<=H; ++w) {
			for (int h=w+1; h<=W; ++h) {
				
				int f2 = 0;
				if (H-w-h+1 > 0 && W-h+1 > 0) {
					printf("%d\t%d\n", (H-w-h+1), (W-h+1));
					
					f2 = (H-w-h+1)*(W-h+1);
				}
				
				tsum += f2;
			}
		}
		sum += 4*tsum;
		
		printf("%lld\n", sum);
	}
}
