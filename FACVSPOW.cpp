#include<stdio.h>
#include<math.h>

#define LIM 2800000

double smfac[LIM+1];

int getint() {
    char c;
    int x = 0;
    while ((c=getchar()) < '0' || c > '9') ;
    do {
        x = x*10 + c-'0';
    } while ((c=getchar()) >= '0' && c <= '9') ;
    return x;
}   

int main () {
    smfac[1] = 0.0;
    for (int i=2; i<=LIM; ++i) {
        smfac[i] = smfac[i-1] + log(i);
    }
    
    int t = getint();
    while (t--) {
        int a = getint();
        int u=1, v=LIM+1, c;
        double loga = log(a);
        while (u<v) {
            c = (u+v)>>1;
            if (smfac[c] > c*loga) {
                v = c;
            } else {
                u = c+1;
            }
        }
        printf("%d\n", u);
    }
}
