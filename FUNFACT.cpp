#include<stdio.h>
#include<math.h>

#define _2PI 6.28318530718

int main() {
    int t, x;
    
    double C = 0.5 * log(_2PI);
    double LN10 = log(10);
    double kv, fv;
    
    scanf ("%d", &t);
    while (t--) {
        scanf("%d", &x);
        
        int u=1, v=1000000000, c;
        fv = x * LN10;
        
        while (u<v) {
            c = (u+v)>>1;
            kv = (c+0.5)*log(c) - c + C;
            if (kv < fv) {
                u = c+1;
            } else {
                v = c;
            }
        }   
        printf("%d\n", u-1);
    }
}
