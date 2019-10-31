#include <stdio.h>

int main() {
	int T, N;
	double max05, min1, min0, x, middlmax, middlmin;
	int middlnum;
	bool found;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		if (N == 1) {
			scanf("%lf", &x);
			printf("not found\n");
			continue;
		}
		
		max05 = 0.0;
		min1 = 2.0;
		min0 = 2.0;
		middlnum = 0;
		middlmax = 0.0;
		middlmin = 2.0;
		found = false;
		
		while (N--) {
			scanf("%lf", &x);
			if (!found) {
			
				if (x <= 0.5) {
					if (x < min0) {
						min0 = x;
					}
					if (x > max05) {
						max05 = x;
					}
					if (x + min1 < 2.0) {
						found = true;
					}
					if (x + middlmax < 2.0 && x + middlmax > 1.0) {
						found = true;
					}
					
				} else if (x >= 1.0) {
					if (x < min1) {
						min1 = x;
					}
					if (x + min0 < 2.0) {
						found = true;
					}
					
					if (x + middlmin < 2.0) {
						found = true;
					}
					
				} else {
					middlnum++;
					
					if (middlnum == 2) {
						found = true;
					}
					
					if (x > middlmax) {
						middlmax = x;
					}
					
					if (x < middlmin) {
						middlmin = x;
					}
					
					if (x + max05 > 1.0) {
						found = true;
					}
					
					if (x + min1 < 2.0) {
						found = true;
					}
				}
			}
		}
		
		if (found) {
			printf("found\n");
		} else {
			printf("not found\n");
		}
	}
}
