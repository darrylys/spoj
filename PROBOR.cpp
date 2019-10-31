#include <stdio.h>

#define MAXN 105
#define MAXD 31

double dp[MAXN][MAXD+5]; //the prob if bit = 1

int main() {
    double p;
    int n;
    
    int num1;
    int num2;
    
    scanf("%lf %d", &p, &n);
    
    scanf("%d", &num1);
    
    if (n == 1) {
        printf("%d.00\n", num1);
        return 0;
    }
    
    scanf("%d", &num2);
    
    //printf("%d %d %lf\n", num1, num2, p);
    
    int d = 0;
    while (num1 || num2) {
        
        if ((num1&1) == (num2&1)) {
            dp[0][d] = (double)(num1&1);
            //printf("dp[0][%d]=%lf\n", d, dp[0][d]);
        } else {
            dp[0][d] = (1.0-p);
            //printf("dp[0][%d]=%lf\n", d, dp[0][d]);
        }
        
        num1 >>= 1;
        num2 >>= 1;
        d++;
    }
    
    double exp;
    
    for (int i=2; i<n; ++i) {
        scanf("%d", &num2);
        
        //printf("num2=%d\n", num2);
        
        d = 0;
        while (d<MAXD) {
            
            if (num2&1) {
                //p(bit=1 | i=n) = p(bit=1 | i=n-1) + p(bit=0 | i=n-1) * (1-prob)
                dp[i-1][d] = dp[i-2][d] + (1.0-dp[i-2][d]) * (1.0-p);
                //printf("dp[%d][%d] = %lf\n", i-1, d, dp[i-1][d]);
            } else {
                dp[i-1][d] = (1-p)*dp[i-2][d];
                //printf("dp[%d][%d] = %lf\n", i-1, d, dp[i-1][d]);
            }
            num2 >>= 1;
            d++;
        }
    }
    
    exp = 0.0;
    for (int j=0; j<MAXD; ++j) {
        exp += (1<<j) * (dp[n-2][j]);
    }
    
    printf("%.2lf\n", exp);
    return 0;
}